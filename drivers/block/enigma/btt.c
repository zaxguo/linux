#include <linux/slab.h>
#include <linux/gfp.h>
#include <linux/crypto.h>
#include <crypto/skcipher.h>
#include <crypto/aes.h>
#include <linux/scatterlist.h>
#include <linux/err.h>
#include <linux/random.h>
#include "enigma.h"
#include "enigma_types.h"



struct enigma_cb enigma_cb;

// in-place dencryption
// TODO: move this to TZ
// note: the in address cannot be a stack addr
static int endec_btt_entry(u8 *in, int endec) {
	int err;
	u8 iv[16];
	struct scatterlist sg;
	struct skcipher_request *req = NULL;
	struct crypto_skcipher *tfm = enigma_cb.cipher;
	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	if (IS_ERR(req)) {
		lwg("cannot allocate req...\n");
		return 0;
	}
	/* make iv (i.e. nonce) uniformly 0  */
	sg_init_one(&sg, in, BTT_ENTRY_SIZE);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, &sg, &sg, BTT_ENTRY_SIZE, iv);

	if (endec == BTT_ENC) {
		err = crypto_skcipher_encrypt(req);
	} else if (endec == BTT_DEC) {
		err = crypto_skcipher_decrypt(req);
	}
	if (err) {
		pr_err("Error encrypting btt entry...\n");
	}
	skcipher_request_free(req);
	return 0;
}

static int encrypt_btt_entry(btt_e *entry) {
	return endec_btt_entry((u8 *)entry, BTT_ENC);
}

int decrypt_btt_entry(btt_e *e_block) {
	u8 *entry = kmalloc(sizeof(btt_e), GFP_KERNEL);
	/* TODO: seems non-avoidable memory move.. we have to do world switch anyway */
	memcpy(entry, e_block, sizeof(btt_e));
	endec_btt_entry((u8 *)entry, BTT_DEC);
	memcpy(e_block, entry, sizeof(btt_e));
	kfree(entry);
	return 0;
}


btt_e *alloc_btt(unsigned long size) {
	btt_e *ret = kmalloc(sizeof(btt_e) * size, GFP_KERNEL);
	if (!ret) {
		/* TODO: error handling */
		return NULL;
	}
	return ret;
}

int init_btt_for_device(int lo_number) {
	struct enigma_cb *cb;
	if (!has_enigma_cb()) {
		lwg("enigma_cb is uninitialized!\n");
		return -1;
	}
	cb = &enigma_cb;
	if (!has_btt_for_device(lo_number)) {
		int i, ret;
		btt_e *_btt;
		_btt = alloc_btt(BTT_SIZE);
		if (!ret) {
			/* TODO: handle BTT allocation failed */
		}
		/* lwg: this is a dummy BTT - init BTT entries */
		for (i = 0; i < BTT_SIZE; i++) {
			_btt[i] = i;
			encrypt_btt_entry(_btt + i);
		}
		cb->btt[lo_number] = _btt;
		lwg("btt initialization for [%d] complete..\n", lo_number);
		return 0;
	} else {
		lwg("btt for [%d] already exists..\n", lo_number);
		return -1;
	}
}

int free_btt(btt_e *btt) {
	kfree(btt);
	return 0;
}

static int init_enigma_crypto(struct crypto_skcipher **cipher) {
	int err;
	struct crypto_skcipher *tfm = NULL;
	// lwg: symmetric key
	u8 key[64];
	/* lwg: des has cipher block size of 8B */
	tfm = crypto_alloc_skcipher("ecb(des)", 0, 0);
	if (IS_ERR(tfm)) {
		pr_err("Error allocating crypto handle: %ld\n", PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}
	err = crypto_skcipher_setkey(tfm, key, sizeof(key));
	if (err) {
		pr_err("Error setting key: %d\n", err);
	}
	*cipher = tfm;
	return 0;
}

static btt_e _lookup_block(btt_e *btt, btt_e vblock) {
	return btt[vblock];
}

/* lookup_result will be shared
 * */
static int alloc_block(int lo, btt_e vblock, struct lookup_result *re) {
	/* TODO: send req to TZ */
	return 0;
}

int lookup_block(int lo, btt_e vblock, struct lookup_result *re) {
	if (!has_enigma_cb()) {
		return LOOKUP_FAIL;
	}
	btt_e *btt = get_btt_for_device(lo);
	btt_e pblock = _lookup_block(btt, vblock);
	if (!pblk_allocated(pblock)) {
		/* this sends the req to tz */
		struct lookup_result tmp;
		int err = alloc_block(lo, vblock, &tmp);
		if (err == ALLOC_FAIL) {
			re->block = NULL_BLK;
			re->shared = false;
			return LOOKUP_FAIL;
		}
	}
	re->block = pblock;
	/* TODO: xxx */
	re->shared = false;
	return 0;
}

int init_enigma_cb (void) {
	int ret;
	struct enigma_cb* cb = &enigma_cb;
	ret = init_enigma_crypto(&cb->cipher);
	printk("enigma_cb initialized tfm -- %p\n", enigma_cb.cipher);
	printk(KERN_INFO "lwg: enigma cb initialized..\n");
	return 0;
}


