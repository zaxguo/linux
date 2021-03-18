#ifndef _ENIGMA_SMC_H
#define _ENIGMA_SMC_H

/* Note this file will be statically linked to OPTEE directory as a shared header -- we cannot include any header from Linux in this file! */

/* calling convention of enigma smc:
 * arm_smccc_smc(ENIGMA_SMC_CALL,
 *				op, payload, priv,
 *				0x0, 0x0, 0x0, 0x0, &res)
 *
 * r0: ENIGMA_SMC_CALL: integrated with existing OPTEE calling convention so that the smc exception can be captured by TZ
 * r1: op: either read/write block requests (ENIGMA_RD/WR)
 * r2: payload: the _encrypted_ phy block entry after BTT lookup
 * r3: private: can be used to pass shm buf address, etc.
 *
 * */

#define NULL_BLK	((uint32_t)-1)
#define FILEDATA	((uint32_t)-2)
/* from linux/blk_types.h, add _ to avoid redeclaration */
enum _req_opf {
	/* read sectors from the device */
	_REQ_OP_READ		= 0,
	/* write sectors to the device */
	_REQ_OP_WRITE		= 1,
	/* flush the volatile write cache */
	_REQ_OP_FLUSH		= 2,
	/* discard sectors */
	_REQ_OP_DISCARD		= 3,
	/* get zone information */
	_REQ_OP_ZONE_REPORT	= 4,
	/* securely erase sectors */
	_REQ_OP_SECURE_ERASE	= 5,
	/* seset a zone write pointer */
	_REQ_OP_ZONE_RESET	= 6,
	/* write the same sector many times */
	_REQ_OP_WRITE_SAME	= 7,
	/* write the zero filled sector many times */
	_REQ_OP_WRITE_ZEROES	= 9,

	/* increment block ref count in TEE */
	_REQ_OP_INC_REF = 10,

	/* SCSI passthrough using struct scsi_request */
	_REQ_OP_SCSI_IN		= 32,
	_REQ_OP_SCSI_OUT		= 33,
	/* Driver private requests */
	_REQ_OP_DRV_IN		= 34,
	_REQ_OP_DRV_OUT		= 35,
	_REQ_OP_LAST,
};


/* lwg: the calling convention of SMC */
#define ENIGMA_RD	_REQ_OP_READ
#define ENIGMA_WR	_REQ_OP_WRITE
#define ENIGMA_INCR _REQ_OP_INC_REF
#define ENIGMA_LOOKUP_BTT	(ENIGMA_INCR+1)

#define ENIGMA_SMC_CALL \
	OPTEE_SMC_STD_CALL_VAL(0) // the "0" marks it is our SMC
#define ENIGMA_FAST_CALL \
	OPTEE_SMC_FAST_CALL_VAL(12)

#endif
