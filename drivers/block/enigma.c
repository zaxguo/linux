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

// in-place dencryption
static int endec_btt_entry(u8 *in, int endec) {
	int err;
	u8 iv[16];
	struct scatterlist sg;
	struct skcipher_request *req = NULL;
	struct crypto_skcipher *tfm = enigma_cb.cipher;
	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	if (IS_ERR(req)) {
		printk("lwg:%s:%d: cannot allocate req...\n", __func__, __LINE__);
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

int decrypt_btt_entry(btt_e *entry) {
	return endec_btt_entry((u8 *)entry, BTT_DEC);
}


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
		ret = alloc_btt(BTT_SIZE);
		if (!ret) {
			/* TODO: handle BTT allocation failed */
		}
		/* lwg: this is a dummy BTT - init BTT entries */
		for (i = 0; i < BTT_SIZE; i++) {
			btt[i] = i;
			encrypt_btt_entry(btt + i);
		}
		printk("lwg:%s:%d:btt initialization complete..\n", __func__, __LINE__);
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

int init_enigma_cb (void) {
	int ret;
	struct enigma_cb* cb = &enigma_cb;
	ret = init_enigma_crypto(&cb->cipher);
	printk("enigma_cb initialized tfm -- %p\n", enigma_cb.cipher);
	return 0;
}


