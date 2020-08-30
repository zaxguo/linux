#include "enigma.h"
#include <linux/slab.h>
#include <linux/gfp.h>

loff_t *btt;

int alloc_btt(unsigned long size) {
	btt = kmalloc(sizeof(loff_t) * size, GFP_KERNEL);
	if (!btt) {
		/* TODO: error handling */
		return -1;
	}
	return 0;
}

int init_btt() {
	if (!btt) {
		int i, ret;
		printk("lwg:%s:%d:initializing btt..\n", __func__, __LINE__);
		ret = alloc_btt(BTT_SIZE);
		if (!ret) {
			/* TODO: handle BTT allocation failed */
		}
		/* init BTT entries */
		for (i = 0; i < BTT_SIZE; i++) {
			btt[i] = i;
		}
		printk("btt init...\n");
		return 0;
	} else {
		printk("btt already exists..\n");
		return -1;
	}
}

int free_btt(loff_t *btt) {
	kfree(btt);
	return 0;
}
