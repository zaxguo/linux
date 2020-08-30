#include <linux/slab.h>
#include <linux/gfp.h>
#include <linux/crypto.h>
#include <crypto/skcipher.h>
#include <crypto/aes.h>
#include <linux/scatterlist.h>
#include <linux/err.h>
#include <linux/random.h>
#include "enigma.h"

loff_t *btt;

struct enigma_cb enigma_cb;

int alloc_btt(unsigned long size) {
	btt = kmalloc(sizeof(btt_e) * size, GFP_KERNEL);
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

int free_btt(btt_e *btt) {
	kfree(btt);
	return 0;
}

static int init_enigma_crypto(struct crypto_skcipher *cipher) {
	int err;
	struct crypto_skcipher *tfm = NULL;
	// lwg: symmetric key
	u8 key[64];
	tfm = crypto_alloc_skcipher("xts(aes)", 0, 0);
	if (IS_ERR(tfm)) {
		pr_err("Error allocating xts(aes) handle: %ld\n", PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}
	err = crypto_skcipher_setkey(tfm, key, sizeof(key));
	if (err) {
		pr_err("Error setting key: %d\n", err);
	}
	cipher = tfm;
	return 0;
}

int init_enigma_cb (void) {
	int ret;
	struct enigma_cb* cb = &enigma_cb;
	ret = init_enigma_crypto(cb->cipher);
}

// in-place encryption
static int encrypt_btt_entry(u8 *in) {
	int err;
	u8 iv[16];
	struct scatterlist sg;
	struct skcipher_request *req = NULL;
	struct crypto_skcipher *tfm = enigma_cb.cipher;
	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	get_random_bytes(iv, sizeof(iv));
	sg_init_one(&sg, in, BTT_ENTRY_SIZE);
	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG |
			CRYPTO_TFM_REQ_MAY_SLEEP,
			NULL, NULL);
	skcipher_request_set_crypt(req, &sg, &sg, BTT_ENTRY_SIZE, NULL);
	err = crypto_skcipher_encrypt(req);
	if (err) {
		pr_err("Error encrypting btt entry...\n");
	}
	skcipher_request_free(req);
	return 0;
}
