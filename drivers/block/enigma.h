#ifndef _ENIGMA_H
#define _ENIGMA_H
#include <linux/types.h>

#define BTT_SIZE (4096)

extern loff_t *btt;
int init_btt(void);
int alloc_btt(unsigned long size);
int free_btt(loff_t *btt);

#endif

