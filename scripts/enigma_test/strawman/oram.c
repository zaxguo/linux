#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "oram.h"

static int _create_oram_tree(char *img, loff_t file_size, int block_size, int bucket_size) {
	loff_t img_size;
	int blks, ret, img_file;
	img_file = open(img, O_RDWR|O_CREAT);
	if (ret < 0) {
		printf("error creating oram image!\n");
		exit(0);
	}
	/* storage size is bucket_size * number_of_blocks */
	img_size = ((int)(file_size/block_size) + 1) * bucket_size;
	ret = fallocate(img_file, 0, 0, img_size);


}

int create_oram_tree(char *orig_file) {
	loff_t size;
	int ret = open(orig_file, O_RDONLY);
	size = lseek(ret, 0, SEEK_END);
	_create_oram_tree("oram.img", size, 1 << 9, 4);
	return 0;
}
