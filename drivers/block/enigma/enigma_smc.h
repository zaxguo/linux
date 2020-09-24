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

/* lwg: the calling convention of SMC */
#define ENIGMA_RD	0x0
#define ENIGMA_WR	0x1
#define ENIGMA_SMC_CALL \
	OPTEE_SMC_STD_CALL_VAL(0) // the "0" marks it is our SMC

#endif
