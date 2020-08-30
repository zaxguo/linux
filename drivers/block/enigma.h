#ifndef _ENIGMA_H
#define _ENIGMA_H
#include <linux/types.h>
#include <linux/crypto.h>

#define BTT_SIZE (30001)

#define BTT_ENTRY_SIZE (sizeof(btt_e))

typedef loff_t btt_e;

struct enigma_cb {
	loff_t *btt;
	struct crypto_skcipher *cipher;
};

extern struct enigma_cb enigma_cb;

extern loff_t *btt;
int init_btt(void);
int alloc_btt(unsigned long size);
int free_btt(loff_t *btt);

#endif

