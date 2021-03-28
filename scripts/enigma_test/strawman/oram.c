#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "oram.h"
#include <math.h>
#include <string.h>


/* global var */
int *pos_map;
int **path_map;
struct stash *stash;
struct oram_tree_param *param;
struct bucket **buckets;

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
	printf("%s:%d:tree_height = %d, total_buckets = %ld\n", __func__, __LINE__, tree_height, total_buckets);
	for (i = 0; i < blocks; i++) {
		/* must be a leaf node hence the offset after random draw  */
		int bucket = get_random_leaf(param);
		pos_map[i] = bucket;
		buckets[bucket]->b_list[0] = i;
		printf("%s:%d: [%d] -> [%d]\n", __func__, __LINE__, i, pos_map[i]);
	}
	int *path = malloc(sizeof(int) * (tree_height + 1));
	leaf_path(0, 0, tree_height, path);
	free(path);
	return 0;
}


static int _create_oram_tree(char *img, loff_t file_size, int block_size, int bucket_size) {
	loff_t img_size;
	int blks, ret, img_file, height;
	img_file = open(img, O_RDWR|O_CREAT);
	if (ret < 0) {
		printf("error creating oram image!\n");
		exit(0);
	}
	/* storage size is at least bucket_size * number_of_blocks */
	param = malloc(sizeof(struct oram_tree_param));
	blks = (int)(file_size/block_size) + 1;
	img_size = blks * bucket_size;
	height  = (int)log2((double)blks) + 1;
	printf("%s:%d: file size = %ld, blocks = %d\n", __func__, __LINE__, file_size, blks);
	ret = fallocate(img_file, 0, 0, img_size);
	param->blocks = blks;
	param->block_size = block_size;
	param->height = height;
	param->leaf_offset = (int)pow(2., height) - 1;
	/* stash szie taken from Fig 3 of the paper */
	stash = malloc(sizeof(struct stash));
	stash->size = 0;
	stash->b_list = malloc(sizeof(int) * (20));
	path_map = malloc(sizeof(int *) * param->leaf_offset);
	/* init position map for client */
	init_position_map(blks);
}

static void oram_access(int op, int blk_id, void *buf) {
	int *path;
	int x = pos_map[blk_id];
	/* remap */
	pos_map[blk_id] = get_random_leaf(param);
	path = path_map[x - param->leaf_offset];
	printf("picking %d bucket (leaf node)..., path:", x);
	print_path(path, param->height + 1);
	for (int i = 0; i < param->height + 1; i++) {
		int bid = path[i];
		/* read into stash */
		printf("read %d bucket into stash\n", bid);
		/*dump_bucket(bid);*/
		stash->b_list[i] = bid;
		++stash->size;
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
				int bid = stash->b_list[j];
				struct bucket *bkt = buckets[bid];
				for (int k = 0; k < BUCKET_SIZE; k++) {
					int block = bkt->b_list[k];
					if (block == DUMMY_BLK) {
						/*printf("dummy block -- no position map entry\n");*/
						continue;
					} else {
						int _x = pos_map[block];
						int *_x_path = path_map[_x - param->leaf_offset];
						printf("orig_path[%d]=%d, new_path[%d]=%d\n", i, path[i], i, _x_path[i]);
						/* intersect */
						if (_x_path[i] == path[i]) {
							_s[s_size++] = block;
							printf("block %d put into new stash\n", block);
						}
					}
				}
		}
		printf("tmp stash size = %d, local stash size = %d\n", s_size, stash->size);
		/* S = S - S' */
		int *s = stash->b_list;
		int found = 0;
		for (int j = 0; j < min(s_size, BUCKET_SIZE); j++) {
			int blk = _s[j];
			for (int k = 0; k < stash->size; k++) {
				if (blk == s[k]) {
					s[k] = DUMMY_BLK;
					found++;
					break;
				}
			}
		}
		stash->size -= found;
		/* write bucket */
		printf("to write ");
		for (int i = 0; i < min(s_size, BUCKET_SIZE); i++) {
			printf("%d ", _s[i]);
		}
		printf("to bucket %d\n", path[i]);
	}
}

int create_oram_tree(char *orig_file) {
	loff_t size;
	int ret = open(orig_file, O_RDONLY);
	if (ret > 0) {
		size = lseek(ret, 0, SEEK_END);
	} else {
		/* test only */
		size = 512 * 10;
	}
	_create_oram_tree("oram.img", size, 1 << 9, BUCKET_SIZE);
	return 0;
}

int main() {
	create_oram_tree('test.txt');
	oram_access(0, 0, NULL);
	return 0;
}
