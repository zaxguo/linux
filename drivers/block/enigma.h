#ifndef _ENIGMA_H
#define _ENIGMA_H
#include <linux/types.h>
#include <linux/crypto.h>

#define BTT_SIZE (30001)
#define BTT_ENTRY_SIZE (sizeof(btt_e))
#define LOOP_DEV_NUM	10

#define BTT_ENC 0
#define BTT_DEC	1

#define lwg(fmt, ...) printk("lwg:%s:%d: " fmt, __func__, __LINE__, ##__VA_ARGS__);

typedef loff_t btt_e;

struct enigma_cb {
	loff_t *btt[LOOP_DEV_NUM];
	struct crypto_skcipher *cipher;
};

extern struct enigma_cb enigma_cb;

int init_btt_for_device(int lo_number);
btt_e *alloc_btt(unsigned long size);
int free_btt(btt_e *btt);
int init_enigma_cb(void);
int decrypt_btt_entry(btt_e *btt);

static inline int has_enigma_cb(void) {
	return (enigma_cb.cipher != NULL);
}

static inline int has_btt_for_device(int lo_number) {
	return (enigma_cb.btt[lo_number] != NULL);
}

static inline btt_e *get_btt_for_device(int lo_number) {
	return enigma_cb.btt[lo_number];
}

#endif

