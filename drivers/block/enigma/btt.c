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
#include "enigma_smc.h"
#include <linux/mutex.h>
#include <linux/rwlock.h>


#define NEEDS_ENDEC		1

struct enigma_cb enigma_cb;
enigma_lock btt_lock;

// in-place en/decryption
// TODO: move this to TZ
// note: the in address cannot be a stack addr
static int endec_btt_entry(u8 *in, int endec, struct skcipher_request *_req) {
	int err, keylen;
	/* ECB DES 64 -- blk size = 8 must be aligned */
	/*u8 iv[8];*/
	u8 iv[enigma_cb.keylen];
	keylen = enigma_cb.keylen;
	memset(iv, 0, keylen);
	struct scatterlist sg;
	struct skcipher_request *req = _req;
	struct crypto_skcipher *tfm = enigma_cb.cipher;
	if (!req) {
		req = skcipher_request_alloc(tfm, GFP_KERNEL);
	}
	if (IS_ERR(req)) {
		lwg("cannot allocate req...\n");
		return 0;
	}
	/* make iv (i.e. nonce) uniformly 0  */
	/*sg_init_one(&sg, in, BTT_ENTRY_SIZE);*/
	/* the size must be the multiple of block size, e.g. 16 */
	sg_init_one(&sg, in, 4096);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, &sg, &sg, 4096, iv);

	if (endec == BTT_ENC) {
		err = crypto_skcipher_encrypt(req);
	} else if (endec == BTT_DEC) {
		err = crypto_skcipher_decrypt(req);
	}
	if (err) {
		pr_err("Error encrypting btt entry...\n");
	}
	if (!_req)
		skcipher_request_free(req);
	return 0;
}

static int encrypt_btt_entry(btt_e *entry) {
#if NEEDS_ENDEC
	return endec_btt_entry((u8 *)entry, BTT_ENC, NULL);
#else
	return 0;
#endif
}

int decrypt_btt_entry(btt_e *e_block) {

#if NEEDS_ENDEC
	u8 *entry = kmalloc(sizeof(btt_e), GFP_KERNEL);
	/* TODO: seems non-avoidable memory move.. we have to do world switch anyway */
	memcpy(entry, e_block, sizeof(btt_e));
	endec_btt_entry((u8 *)entry, BTT_DEC, NULL);
	memcpy(e_block, entry, sizeof(btt_e));
	kfree(entry);
#else
	/* empty body */
#endif
	return 0;
}

static struct mutex* get_mtx_for_device(int lo) {
	return &enigma_cb.btt_mtx[lo];
}

static int _update_btt(btt_e *btt, btt_e vblk, btt_e e_blk) {
	if (!btt) {
		return BTT_UPDATE_FAIL;
	}
	btt[vblk] = e_blk;
	return 0;
}

int update_btt(int dev_id, btt_e vblk, btt_e e_blk) {
	/*lwg("update [%d]: [%d] -> [%x]\n", dev_id, vblk, e_blk);*/
	int ret;
	btt_e *btt = get_btt_for_device(dev_id);
	/*struct mutex *mtx = get_mtx_for_device(dev_id);*/
	/*mutex_lock(mtx);*/
	ret =	_update_btt(btt, vblk, e_blk);
	/*mutex_unlock(mtx);*/
	return 0;
}

btt_e *alloc_btt(unsigned long size) {
	unsigned long alloc_size = size * sizeof(btt_e);
	btt_e *ret = kmalloc(alloc_size, GFP_KERNEL);
	if (!ret) {
		lwg("try vmalloc instead... size = %ld\n", alloc_size);
		ret = vmalloc(alloc_size);
		if (!ret) {
			lwg("still cannot alloc btt!!\n");
			return NULL;
		}
	}
	lwg("btt [entries:%ld] allocated...\n", size);
	return ret;
}


static inline void init_mtx_for_device(struct enigma_cb *cb, int lo) {
	struct mutex *mtx = &cb->btt_mtx[lo];
	mutex_init(mtx);
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
			if (lo_number == cb->actual) {
				/* sectors are linearly mapped in actual */
				_btt[i] = i;
			} else {
				_btt[i] = NULL_BLK;
			}
			/*encrypt_btt_entry(_btt + i);*/
		}
		cb->btt[lo_number] = _btt;
		lwg("btt initialization for [%d] complete..\n", lo_number);
		init_mtx_for_device(cb, lo_number);
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

static int init_enigma_crypto(const char *alg, struct crypto_skcipher **cipher, uint8_t keylen) {
	int err;
	struct crypto_skcipher *tfm = NULL;
	// lwg: 64bit for des
	/*u8 key[8];*/
	/* 128bit for aes */
	u8 key[keylen];
	memset(key, 0, keylen);
	/* lwg: des has cipher block size of 8B */
	tfm = crypto_alloc_skcipher(alg, 0, 0);
	if (IS_ERR(tfm)) {
		pr_err("Error allocating crypto handle: %ld\n", PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}
	/*lwg("gonna call %pf key size = %d\n", tfm->setkey, sizeof(*key));*/
	err = crypto_skcipher_setkey(tfm, key, sizeof(key));
	if (err) {
		pr_err("Error setting key: %d\n", err);
	}
	*cipher = tfm;
	lwg("enigma crypto sucessfully set, cipher = %s, key size:%d bits...\n", alg, sizeof(key)* 8);
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

btt_e lookup_block(int lo, btt_e vblock, struct lookup_result *re) {
	if (!has_enigma_cb()) {
		return LOOKUP_FAIL;
	}
	btt_e *btt = get_btt_for_device(lo);
	btt_e pblock = _lookup_block(btt, vblock);
#if 0
	/* normal world does not care if the block is allocated or not */
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
#endif
	return pblock;
}

static inline void incr_blk_ref(btt_e pblk) {
	struct arm_smccc_res res;
	arm_smccc_smc(ENIGMA_SMC_CALL, ENIGMA_INCR, (uint32_t) pblk, 0x0, 0x0, 0x0, 0x0, 0x0, &res);
}


/* copy btt to another device */
int copy_btt(int from, int to) {
	int i;
	btt_e *from_btt = get_btt_for_device(from);
	btt_e *to_btt = get_btt_for_device(to);
	memcpy(to_btt, from_btt, BTT_SIZE * sizeof(btt_e));
	for (i = 0; i < (int)BTT_SIZE; i++) {
		btt_e pblk = to_btt[i];
		if (pblk_allocated(pblk)) {
			incr_blk_ref(pblk);
		}
	}
	lwg("copied btt from [%d] to [%d]\n", from, to);
	return 0;
}

int encrypt_btt(int dev_id) {
	int i, pages;
	btt_e before,after;
	btt_e *entry = get_btt_for_device(dev_id);
	u64 start, delta;
	start = jiffies;
	struct skcipher_request *req = skcipher_request_alloc(enigma_cb.cipher, GFP_KERNEL);
	if (!req) {
		lwg("fail to alloc cipher reuqest!\n");
	}
	pages = (BTT_SIZE * BTT_ENTRY_SIZE) >> 12;
	for (i = 0; i < pages; i++, entry += (1 << 10)) {
		/*before = *entry;*/
		endec_btt_entry((u8 *)entry, BTT_ENC, req);
		/* lwg: used to verify endec works */
		/*endec_btt_entry((u8 *)entry, BTT_DEC, req);*/
		/*after = *entry;*/
		/*lwg("before: %ld --  after: %16lx\n", before, after);*/
	}
	delta = jiffies - start;
	lwg("takes %d ms to encrypt btt\n", jiffies_to_msecs(delta));
	return i;
}


int init_enigma_cb (void) {
	int ret;
	struct enigma_cb* cb = &enigma_cb;
	cb->keylen = 32;
	const char *alg = "xts(aes)";
	ret = init_enigma_crypto(alg,&cb->cipher, cb->keylen);
	cb->actual = 0;
	mutex_init(&btt_lock);
	lwg("enigma cb initialized..\n");
	return 0;
}


