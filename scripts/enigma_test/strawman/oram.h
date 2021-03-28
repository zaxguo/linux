#include <stdint.h>
#define BUCKET_SIZE 4
#define BLOCK_SIZE	(1 << 9)
#define READ	0
#define WRITE	1
#define DUMMY_BLK	(-1)

#define min(a,b) (a >= b) ? (b) : (a)


struct bucket {
	uint32_t b_list[BUCKET_SIZE];
};

struct oram_tree_param {
	int height;
	int block_size;
	int blocks;
	int leaf_offset;
	int *pos_map;
	int *stash;
};

struct stash {
	int *b_list;
	int size;
};

int create_oram_tree(char *orig_file);
