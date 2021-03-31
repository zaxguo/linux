#include <stdint.h>
#define BUCKET_SIZE 4
#define BLOCK_SIZE	(1 << 9)
#define READ	0
#define WRITE	1
#define DUMMY_BLK	(-1)
#define MIN(a,b) (((a)<(b))?(a):(b))


//#define lwg(fmt, ...) printf("%s:%d: "fmt, __func__, __LINE__, ##__VA_ARGS__);
//#define lwg(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define lwg(fmt, ...) 0

extern struct oram_tree_param *param;

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
	int img;
};

struct stash {
	int *b_list;
	int size;
	int cnt;
};

int create_oram_tree(char *orig_file);
void oram_access(int op, int bid, void *data);
