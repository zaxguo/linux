#ifndef _ENIGMA_H
#define _ENIGMA_H
#include <linux/types.h>
#include <linux/crypto.h>
#include <linux/arm-smccc.h>
#include "enigma_types.h"
#include "enigma_smc.h"
#include "../../drivers/tee/optee/optee_smc.h"
#include <linux/mutex.h>

//#define BTT_SIZE (6001)
#define BTT_SIZE (80001)
#define BTT_ENTRY_SIZE (sizeof(btt_e))
#define MAX_DEV		15

#define BTT_ENC 0
#define BTT_DEC	1

#define lwg(fmt, ...) printk("lwg:%s:%d: " fmt, __func__, __LINE__, ##__VA_ARGS__);

//#define lwg(fmt, ...) 0;
/* 4-byte unsigned int */
typedef uint32_t btt_e;

struct enigma_cb {
	btt_e *btt[MAX_DEV];
	struct mutex btt_mtx[MAX_DEV];
	struct crypto_skcipher *cipher;
	uint8_t actual;
};

struct lookup_result {
	bool shared;
	btt_e block;
};

extern struct enigma_cb enigma_cb;

int init_btt_for_device(int lo_number);
int copy_btt(int from, int to);
btt_e *alloc_btt(unsigned long size);
int free_btt(btt_e *btt);
int update_btt(int dev_id, btt_e vblk, btt_e eblk);
int init_enigma_cb(void);
int decrypt_btt_entry(btt_e *btt);
int lookup_block(int lo, btt_e vblock, struct lookup_result *re);

static inline int has_enigma_cb(void) {
	return (enigma_cb.cipher != NULL);
}

static inline int has_btt_for_device(int lo_number) {
	return (enigma_cb.btt[lo_number] != NULL);
}

static inline btt_e *get_btt_for_device(int lo_number) {
	return enigma_cb.btt[lo_number];
}

static inline int pblk_allocated(btt_e pblock) {
	return (pblock != NULL_BLK) && (pblock != FILEDATA);
}

#endif

