#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "oram.h"
#include <math.h>
#include <string.h>
#include <openssl/aes.h>
#include <errno.h>
#include <time.h>

#define BILLION		1E9
#define NEED_ENC	1

/* global vars */
int *pos_map;
int **path_map;
struct stash *stash;
struct oram_tree_param *param;
struct bucket **buckets;

static const unsigned char key[] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

AES_KEY enc_key, dec_key;


/* a flat array representation of bucket tree on disk
 * node #:		0   1		2		3		....
 * file off:	0   4*512	2*4*512 3*4*512	...
 * tree:
 *				0
 *			  /   \
 *		     1     2
 *		    / \   / \
 *		   3   4  5  6
 *
 * */
static loff_t get_bucket_file_off(int bucket_no) {
	return (bucket_no * (BUCKET_SIZE * BLOCK_SIZE));
}

static int get_leaf_offset() {
	return param->leaf_offset;
}

static int get_random_leaf(struct oram_tree_param *param) {
	return ((rand() % param->blocks) + param->leaf_offset);
}

static void print_path(int *path, int tree_height) {
	for (int i = 0; i < tree_height; i++) {
		printf("[%d] ", path[i]);
	}
	printf("\n");
	return;
}

static void dump_bucket(int bid) {
	struct bucket *bkt = buckets[bid];
	printf("[%d:%p] contains: ", bid, bkt);
	for (int i = 0; i < BUCKET_SIZE; i++) {
		printf("%d ", bkt->b_list[i]);
	}
	printf("\n");
}

/* debug */
static void display_path(int blk) {
	int pos = pos_map[blk];
	int *path = path_map[pos - param->leaf_offset];
	printf("real block %d path:", blk);
	for (int i = 0; i < param->height + 1; i++) {
		struct bucket *bkt = buckets[path[i]];
		printf("[%d:", path[i]);
		for(int j = 0; j < BUCKET_SIZE; j++) {
			printf("%d ", bkt->b_list[j]);
		}
		printf("], ");
	}
	printf("\n");
}

static void insert_path(int *path, int idx) {
	int *tmp = malloc(sizeof(int) * (param->height + 1));
	memcpy(tmp, path, sizeof(int) * (param->height + 1));
	path_map[idx] = tmp;
	/* debugging -- print height + 1 nodes as path */
	/*printf("inserting at %d --- %p\n", idx, path_map + idx);*/
	print_path(path_map[idx], param->height + 1);
}


/* pre-compute the paths from root to leaves */
static void leaf_path(int curr_node, int curr_height, int tree_height, int *path) {
	path[curr_height] = curr_node;
	if (curr_height == tree_height) {
		insert_path(path, curr_node - param->leaf_offset);
		return;
	}
	curr_height++;
	leaf_path(2 * curr_node + 1, curr_height, tree_height, path);
	leaf_path(2 * curr_node + 2, curr_height, tree_height, path);
}

static int init_position_map(int blocks) {
	int i, tree_height;
	unsigned long total_buckets;
	tree_height = param->height;
	total_buckets = (unsigned long)pow(2., (double)tree_height + 1) - 1;
	buckets = malloc(sizeof(struct bucket *) * (total_buckets));
	for (i = 0; i < total_buckets; i++) {
		struct bucket *bkt = malloc(sizeof(struct bucket));
		memset(bkt->b_list, DUMMY_BLK, sizeof(uint32_t) * BUCKET_SIZE);
		buckets[i] = bkt;
	}
	/* position map
	 * 0 -> leaf 3
	 * 1 -> leaf 4
	 * each block is mapped to a leaf node */
	pos_map = malloc(sizeof(int) * blocks);
	lwg("tree_height = %d, total_buckets = %ld\n", tree_height, total_buckets);
	for (i = 0; i < blocks; i++) {
		/* must be a leaf node hence the offset after random draw  */
		int bucket = get_random_leaf(param);
		int found;
		pos_map[i] = bucket;
		struct bucket *bkt = buckets[bucket];
		found = 0;
		for (int j = 0; j < BUCKET_SIZE; j++) {
			if (bkt->b_list[j] == DUMMY_BLK) {
				bkt->b_list[j] = i;
				found = 1;
				break;
			}
		}
		if (!found) {
			printf("-------------failing to fill buckets during init!!\n");
		}
		lwg("[%d] -> [%d]\n", i, pos_map[i]);
	}
	int *path = malloc(sizeof(int) * (tree_height + 1));
	leaf_path(0, 0, tree_height, path);
	free(path);
	return 0;
}

static int insert_stash(struct stash *s, int blk) {
	for (int i = 0; i < s->size; i++) {
		if (s->b_list[i] == DUMMY_BLK) {
			s->b_list[i] = blk;
			s->cnt++;
			return i;
		}
	}
	return -1;
}

static int remove_stash(struct stash *s, int idx) {
	int blk = s->b_list[idx];
	s->b_list[idx] = DUMMY_BLK;
	s->cnt--;
	return blk;
}



/* file IO */
static void _rw_bucket(int bid, int op) {
	int ret = 0;
	loff_t off = get_bucket_file_off(bid);
	loff_t size = BUCKET_SIZE * param->block_size;
	char *buf = malloc(size);
	memset(buf, 0, size);
	if (op == READ) {
		ret = pread(param->img, buf, size, off);
#if NEED_ENC
		int total = 0;
		do {
			/* 16B block cipher */
			unsigned int *pt = (unsigned int*)(buf + total);
			lwg("decrypting [%hhx %hhx %hhx] => ", *pt, *(pt+1), *(pt+2));
			AES_decrypt(buf + total, buf + total, &dec_key);
			lwg("[%hhx %hhx %hhx]\n", *(pt), *(pt+1), *(pt+2));
			total += 16;
		} while (total < size);
#endif
	} else if (op == WRITE) {
#if NEED_ENC
		int total = 0;
		do {
			/* 16B block cipher */
			unsigned int *pt = (unsigned int*)(buf + total);
			lwg("encrypting [%hhx %hhx %hhx] => ", *pt, *(pt+1), *(pt+2));
			AES_encrypt(buf + total, buf + total, &enc_key);
			lwg("[%hhx %hhx %hhx]\n", *(pt), *(pt+1), *(pt+2));
			total += 16;
		} while (total < size);
#endif
		ret = pwrite(param->img, buf, size, off);
	}
	if (ret != size) {
		lwg("can only %s %d bytes! (required %ld bytes)\n",
				(op == READ) ? "read" : "write",
				ret,
				size);
	}
	free(buf);
}

static void read_bucket(int bid, struct stash *s) {
	struct bucket *bkt = buckets[bid];
	_rw_bucket(bid, READ);
	lwg("read %d bucket into stash:", bid);
	for (int i = 0; i < BUCKET_SIZE; i++) {
		int blk = bkt->b_list[i];
		if (blk == DUMMY_BLK) {
			/* read but discard */
			continue;
		}
		lwg("%d ", blk);
		if (insert_stash(stash, blk) == -1) {
			lwg("fail to insert %d to stash!!! stash full!\n", blk);
		}
	}
	lwg("\n");
}

/* write the tmp stash into bucket , size = tmp stash size */
static void write_bucket(int bid, int *_s, int size) {
	struct bucket *bkt = buckets[bid];
	int i;
	_rw_bucket(bid, WRITE);
	if (size > 0) {
		lwg("write bucket %d with ", bid);
		for (i = 0; i < size; i++) {
			lwg("%d ", _s[i]);
			bkt->b_list[i] = _s[i];
		}
		while(i < BUCKET_SIZE) {
			/* fill dummies */
			bkt->b_list[i++] = DUMMY_BLK;
		}
		lwg(", dummies = %d\n", BUCKET_SIZE - size);
	} else {
		for (i = 0; i < BUCKET_SIZE; i++) {
			bkt->b_list[i] = DUMMY_BLK;
		}
		lwg("write bucket %d with all %d dummies\n", bid, BUCKET_SIZE - size);
	}
}


static int _create_oram_tree(char *img, loff_t file_size, int block_size, int bucket_size) {
	loff_t img_size;
	int blks, ret, img_file, height, total_buckets;
	img_file = open(img, O_RDWR|O_CREAT);
	if (img_file < 0) {
		printf("error opening oram image! ret = %d\n", img_file);
		exit(0);
	}
	/* set encrypt key */
	lwg("setting keys..\n");
	AES_set_encrypt_key(key, 128, &enc_key);
	AES_set_decrypt_key(key,128,&dec_key);
	/* storage size is at least bucket_size * number_of_blocks */
	param = malloc(sizeof(struct oram_tree_param));
	param->img = img_file;
	blks = (int)(file_size/block_size) + 1;
	height  = (int)log2((double)blks) + 1;
	param->blocks = blks;
	param->block_size = block_size;
	param->height = height;
	param->leaf_offset = (int)pow(2., height) - 1;
	/* fill up the file */
	total_buckets = (unsigned long)pow(2., (double)height+ 1) - 1;
	img_size = total_buckets * bucket_size * block_size;
	ret = fallocate(img_file, 0, 0, img_size);
	for (int i = 0; i < total_buckets; i++) {
		/* dirty initialize */
		_rw_bucket(i, WRITE);
	}
	lwg("file size = %ld, blocks = %d, oram image size = %ld\n", file_size, blks, img_size);
	if (ret) {
		printf("fallocate goes wrong... ret = %d\n", ret);
	}
	/* stash szie taken from Fig 3 of the paper */
	stash = malloc(sizeof(struct stash));
	stash->size = 20;
	stash->cnt = 0;
	stash->cnt = 0;
	stash->b_list = malloc(sizeof(int) * (20));
	memset(stash->b_list, DUMMY_BLK, sizeof(int) * 20);
	path_map = malloc(sizeof(int *) * param->leaf_offset);
    /*AES_decrypt(enc_out, dec_out, &dec_key);*/
	/* init position map for client */
	init_position_map(blks);
	return blks;
}


static void oram_access(int op, int blk_id, void *buf) {
	int *path;
	int x = pos_map[blk_id];
	/* remap */
	pos_map[blk_id] = get_random_leaf(param);
	path = path_map[x - param->leaf_offset];
	lwg("remap %d from %d bucket to %d bucket.\n", blk_id, x, pos_map[blk_id]);
	/*print_path(path, param->height + 1);*/
	for (int i = 0; i < param->height + 1; i++) {
		int bid = path[i];
		/* read into stash */
		read_bucket(bid, stash);
	}

	if (op == WRITE) {
		/* copy data to be written into block on stash */
	}

	for (int i = param->height; i >= 0; i--) {
		/* S' */
		int *_s = malloc(sizeof(int) * 20);
		int s_size = 0;
		/* generate S' */
		for (int j = 0; j < stash->size; j++) {
			int block = stash->b_list[j];
			if (block == DUMMY_BLK) {
				continue;
			}
			int _x = pos_map[block];
			int *_x_path = path_map[_x - param->leaf_offset];
			lwg("orig_path[%d]=%d, new_path[%d]=%d\n", i, path[i], i, _x_path[i]);
			/* intersect */
			if (_x_path[i] == path[i]) {
				_s[s_size++] = block;
				lwg("intersect, block %d put into tmp stash\n", block);
			}
		}
		/*printf("tmp stash size = %d, local stash size = %d\n", s_size, stash->cnt);*/
		/* S = S - S' */
		int *s = stash->b_list;
		s_size = MIN(s_size, BUCKET_SIZE);
		if (s_size > 0) {
			lwg("remove ");
			for (int j = 0; j < s_size; j++) {
				int blk = _s[j];
				for (int k = 0; k < stash->size; k++) {
					if (blk == s[k]) {
						remove_stash(stash, k);
						lwg("%d ", blk);
						break;
					}
				}
			}
			lwg("from stash...\n");
		}
		/* write bucket */
		write_bucket(path[i], _s, s_size);
		free(_s);
	}
}

int create_oram_tree(char *orig_file) {
	loff_t size;
	int ret = open(orig_file, O_RDONLY);
	if (ret > 0) {
		size = lseek(ret, 0, SEEK_END);
	} else {
		/* test only */
		size = 512 * 100;
	}
	return _create_oram_tree("oram.img", size, 1 << 9, BUCKET_SIZE);
}

static void measure_baseline(int blks) {
	char *buf = malloc(param->block_size);
	int blk_sz = param->block_size;
	for(int i = 0; i < blks; i++) {
		pread(param->img, buf, blk_sz, blk_sz * i);
		/*display_path(0);*/
	}
	free(buf);
}

static void measure_oram(int blks) {
	for(int i = 0; i < blks; i++) {
		oram_access(0, i, NULL);
		/*display_path(0);*/
	}
}

int main() {
	int blks = create_oram_tree('test.txt');
	printf("file size = %d...\n", blks * param->block_size);
	struct timespec start, end;
	double delta;
	clock_gettime(CLOCK_MONOTONIC, &start);
	measure_oram(blks);
	clock_gettime(CLOCK_MONOTONIC, &end);
	delta = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/BILLION;
	printf("ORAM takes %f seconds to finish..\n", delta);

	clock_gettime(CLOCK_MONOTONIC, &start);
	measure_baseline(blks);
	clock_gettime(CLOCK_MONOTONIC, &end);
	delta = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/BILLION;
	printf("Baseline takes %f seconds to finish..\n", delta);


	return 0;
}
