/**
 * \kernelgroup{SceSblPostSsMgr}
 * \usage{psp2kern/post_ss_mgr.h,SceSblPostSsMgrForDriver_stub}
 */

#ifndef _PSP2KERN_POST_SS_MGR_H_
#define _PSP2KERN_POST_SS_MGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceSblRsaDataParam {
	void *data;
	unsigned int size;
} SceSblRsaDataParam;

typedef struct SceSblRsaPublicKeyParam {
	const void *n;
	const void *k; // e/d
} SceSblRsaPublicKeyParam;

typedef struct SceSblRsaPrivateKeyParam {
	int unk_0x00;
	int unk_0x04;
	int unk_0x08;
	int unk_0x0C;
	void *p;
	void *q;
	void *dp; // d % (p - 1)
	void *dq; // d % (q - 1)
	void *qp; // q^-1 % p
} SceSblRsaPrivateKeyParam;


/**
 * Create the new RSA signature
 *
 * @param[inout] rsa_signature - The RSA signature result
 * @param[in]             hash - The RSA signature hash
 * @param[in]      private_key - The RSA private key
 * @param[in]             type - The RSA signature type. [2, 4, 5, 0xB, 0xC, 0xD, 0xE]
 *
 * @return SCE_OK on success, < 0 on error
 */
int ksceSblRSA2048CreateSignature(SceSblRsaDataParam *rsa_signature, SceSblRsaDataParam *hash, SceSblRsaPrivateKeyParam *private_key, int type);

/**
 * Verufy the new RSA signature
 *
 * @param[in] rsa_signature - The RSA signature input
 * @param[in]          hash - The RSA signature hash
 * @param[in]    public_key - The RSA public key
 * @param[in]          type - The RSA signature type. [2, 4, 5, 0xB, 0xC, 0xD, 0xE]
 *
 * @return SCE_OK on success, < 0 on error
 */
int ksceSblRSA2048VerifySignature(SceSblRsaDataParam *rsa_signature, SceSblRsaDataParam *hash, SceSblRsaPublicKeyParam *public_key, int type);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_POST_SS_MGR_H_ */
