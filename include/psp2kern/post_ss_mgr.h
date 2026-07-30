/**
 * \kernelgroup{SceSblPostSsMgr}
 * \usage{psp2kern/post_ss_mgr.h,SceSblPostSsMgrForDriver_stub SceSblFwLoaderForDriver_stub}
 */

#ifndef _PSP2KERN_POST_SS_MGR_H_
#define _PSP2KERN_POST_SS_MGR_H_

#include <vitasdk/build_utils.h>
#include <psp2common/sblpostssmgr.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceSblSealedKey {
	char magic[8];                  //!< "pfsSKKey".
	SceUInt8 major_version;         //!< Must be 2.
	SceUInt8 minor_version;         //!< Must be 0.
	SceUInt8 padding[6];            //!< Must be zero.
	SceUInt8 iv[0x10];
	SceUInt8 encrypted_key[0x10];
	SceUInt8 hmac[0x20];
} SceSblSealedKey;
VITASDK_BUILD_ASSERT_EQ(0x50, SceSblSealedKey); // size is from FW 3.60

typedef struct SceSblKeystone {
	char magic[8];                  //!< "keystone".
	SceUInt16 type;                 //!< Must be 2.
	SceUInt16 version;              //!< Supported values are 0 and 1.
	SceUInt8 padding[0x14];         //!< Must be zero.
	SceUInt8 passcode_digest[0x20];
	SceUInt8 keystone_digest[0x20];
} SceSblKeystone;
VITASDK_BUILD_ASSERT_EQ(0x60, SceSblKeystone); // size is from FW 3.60

typedef struct SceSblDebugKeystone {
	char magic[8];                  //!< "keystone".
	SceUInt16 type;                 //!< Must be 1.
	SceUInt16 version;              //!< Must be 0.
	SceUInt8 padding[4];            //!< Must be zero.
	SceUInt8 iv[0x10];
	SceUInt8 encrypted_secret[0x20];
} SceSblDebugKeystone;
VITASDK_BUILD_ASSERT_EQ(0x40, SceSblDebugKeystone); // size is from FW 3.60

typedef struct SceSblCloudDataKeyRing {
	char magic[8];                  //!< "CloudBU".
	SceUInt32 version;              //!< Supported values are 0 and 1.
	SceUInt8 opaque_header_data[4]; //!< Copied unchanged; not interpreted by the
	                               //!< FW 3.60 provider or known importer.
	SceUInt8 p[0x80];               //!< RSA prime p.
	SceUInt8 q[0x80];               //!< RSA prime q.
	SceUInt8 dp[0x80];              //!< d mod (p - 1).
	SceUInt8 dq[0x80];              //!< d mod (q - 1).
	SceUInt8 qp[0x80];              //!< q^-1 mod p.
	SceUInt8 opaque_trailer_data[0x10]; //!< Copied unchanged; not interpreted by the
	                                   //!< FW 3.60 provider or known importer.
} SceSblCloudDataKeyRing;
VITASDK_BUILD_ASSERT_EQ(0x2A0, SceSblCloudDataKeyRing); // size is from FW 3.60

typedef struct SceSblCloudDataRsaValue {
	SceUInt32 words[0x40];          //!< Zero-padded little-endian 32-bit words.
	SceSize size;                   //!< Number of significant source bytes, up to 0x100.
} SceSblCloudDataRsaValue;
VITASDK_BUILD_ASSERT_EQ(0x104, SceSblCloudDataRsaValue); // size is from FW 3.60

typedef struct SceSblCloudDataSignCryptHandle {
	SceSblCloudDataRsaValue modulus;
	SceSblCloudDataRsaValue exponent;
} SceSblCloudDataSignCryptHandle;
VITASDK_BUILD_ASSERT_EQ(0x208, SceSblCloudDataSignCryptHandle); // size is from FW 3.60

typedef struct SceSblRsaDataParam {
	void *data;           //!< Data buffer.
	unsigned int size;    //!< Data size in bytes.
} SceSblRsaDataParam;
VITASDK_BUILD_ASSERT_EQ(8, SceSblRsaDataParam);

typedef struct SceSblRsaPublicKeyParam {
	const void *n;        //!< Pointer to the 0x100-byte RSA modulus.
	const void *k;        //!< Pointer to the RSA exponent.
} SceSblRsaPublicKeyParam;
VITASDK_BUILD_ASSERT_EQ(8, SceSblRsaPublicKeyParam);

typedef struct SceSblRsaPrivateKeyParam {
	int reserved[4];      //!< Unused on FW 3.60.
	void *p;              //!< Pointer to the 0x80-byte RSA prime p.
	void *q;              //!< Pointer to the 0x80-byte RSA prime q.
	void *dp;             //!< d mod (p - 1).
	void *dq;             //!< d mod (q - 1).
	void *qp;             //!< q^-1 mod p.
} SceSblRsaPrivateKeyParam;
VITASDK_BUILD_ASSERT_EQ(0x24, SceSblRsaPrivateKeyParam);

/**
 * Create an RSA-2048 signature.
 *
 * @param[out] rsa_signature - Receives a 0x100-byte signature.
 * @param[in] hash - Hash to sign.
 * @param[in] private_key - RSA private key.
 * @param[in] type - Signature type: 2, 4, 5, 0xB, 0xC, 0xD, or 0xE.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblRSA2048CreateSignature(SceSblRsaDataParam *rsa_signature, SceSblRsaDataParam *hash, SceSblRsaPrivateKeyParam *private_key, int type);

/**
 * Verify an RSA-2048 signature.
 *
 * @param[in] rsa_signature - 0x100-byte signature.
 * @param[in] hash - Hash to verify.
 * @param[in] public_key - RSA modulus and exponent.
 * @param[in] type - Signature type: 2, 4, 5, 0xB, 0xC, 0xD, or 0xE.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblRSA2048VerifySignature(SceSblRsaDataParam *rsa_signature, SceSblRsaDataParam *hash, SceSblRsaPublicKeyParam *public_key, int type);

/**
 * Initialize the coredump key store.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblCoredumpKeyStoreInitialize(void);

/**
 * Securely clear and finalize the coredump key store.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblCoredumpKeyStoreFinalize(void);

/**
 * Get a coredump HMAC-SHA-256 key.
 *
 * @param[in] key_id - Key ID from 1 through 3.
 * @param[in] key_size - Must be 0x20.
 * @param[out] key - Receives the key.
 */
int ksceSblCoredumpGetHmacKey(SceUInt32 key_id, SceSize key_size, void *key);

/**
 * Get a coredump AES-128 key.
 *
 * @param[in] key_id - Key ID from 1 through 4, 0x10000001, or 0x10000002.
 * @param[in] key_size - Must be 0x10.
 * @param[out] key - Receives the key.
 */
int ksceSblCoredumpGetAesKey(SceUInt32 key_id, SceSize key_size, void *key);

/**
 * Create a sealed-key blob containing a newly generated secret.
 *
 * @param[out] sealed_key - Receives a ::SceSblSealedKey structure.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrEncryptSealedkey(SceSblSealedKey *sealed_key);

/**
 * Authenticate a sealed-key blob and decrypt its secret.
 *
 * @param[in] sealed_key - Sealed-key blob to decrypt.
 * @param[out] secret - Receives exactly 0x10 bytes.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrDecryptSealedkey(const SceSblSealedKey *sealed_key, SceUInt8 *secret);

/**
 * Encrypt a secret into a debug keystone.
 *
 * @param[in] secret - Exactly 0x20 input bytes.
 * @param[out] keystone - Receives a ::SceSblDebugKeystone structure.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrDebugEncryptKeystone(const SceUInt8 *secret, SceSblDebugKeystone *keystone);

/**
 * Authenticate and decrypt a debug keystone.
 *
 * @param[in] keystone - Debug keystone to decrypt.
 * @param[out] secret - Receives exactly 0x20 bytes.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrDebugDecryptKeystone(const SceSblDebugKeystone *keystone, SceUInt8 *secret);

/**
 * Verify a keystone without a passcode.
 *
 * @param[in] keystone - Keystone to verify.
 * @param[in] version - Expected ::SceSblKeystone::version value. Must be 0 or 1.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrVerifyKeystone(const SceSblKeystone *keystone, int version);

/**
 * Verify a keystone using a passcode.
 *
 * @param[in] keystone - Keystone to verify.
 * @param[in] passcode - Exactly 0x20 passcode bytes.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrVerifyKeystoneWithPasscode(const SceSblKeystone *keystone, const SceUInt8 *passcode);

/**
 * Transform an application key using the portability key.
 *
 * @param[in] input - Input key. Its size must be 0x10 or 0x20.
 * @param[out] output - Receives the transformed key and copied size.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrGenerateAppKey(const SceSblAppKey *input, SceSblAppKey *output);

/**
 * Get the cloud-data encryption and decryption key ring.
 *
 * @param[out] key_ring - Receives a ::SceSblCloudDataKeyRing structure.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblSsMgrCloudDataGetEncDecCryptHandle(SceSblCloudDataKeyRing *key_ring);

/**
 * Get one cloud-data RSA signing handle.
 *
 * @param[in] mode - Must be 1.
 * @param[in] index - Handle index, 0 or 1.
 * @param[out] handle - Receives the modulus and exponent.
 */
int ksceSblSsMgrCloudDataGetSignCryptHandle(SceUInt32 mode, SceUInt32 index, SceSblCloudDataSignCryptHandle *handle);

/**
 * Securely clear the cloud-data encryption and signing key rings.
 *
 * @return SCE_OK.
 */
int ksceSblSsMgrCloudDataStop(void);

/**
 * Load an authenticated firmware image.
 *
 * @param[in] e_phnum - Must be 1 on FW 3.60.
 * @param[out] destination - Destination buffer.
 * @param[in] max_size - Destination capacity.
 * @param[out] loaded_size - Receives the number of bytes loaded.
 */
int ksceSblFwLoaderLoad(int e_phnum, void *destination, SceSize max_size, SceSize *loaded_size);

/**
 * Lock and authenticate a firmware image.
 *
 * @param[in] path - Firmware SELF path.
 * @param[in] reserved - Must be zero on FW 3.60.
 */
SceInt32 ksceSblFwLoaderLock(const char *path, int reserved);

int ksceSblFwLoaderUnlock(void);

/**
 * Get the activation key.
 *
 * @param[out] key - Receives a ::SceSblActivationKey structure.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblLicMgrGetActivationKey(SceSblActivationKey *key);

/**
 * Get the cached license state.
 *
 * @return -1 if uninitialized, 0 if activated, 1 if expired, or 2 for the
 * backup-battery condition.
 */
int ksceSblLicMgrGetLicenseStatus(void);

/**
 * Activate a development kit from an activation file.
 *
 * @param[in] afv_path - NUL-terminated path, at most 255 bytes excluding the
 * terminating NUL.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrActivate(char *afv_path);

/**
 * Get the 32-bit activation expiration date.
 *
 * @param[out] expire_date - Receives the expiration date.
 * @param[in] read_from_nvs - Nonzero refreshes the value from NVS.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrGetExpireDate(int *expire_date, SceBool read_from_nvs);

/**
 * Disable SD mode through the PM secure module.
 *
 * @param[in] reserved - Must be zero on FW 3.60.
 */
int _ksceSblPostSsMgrExecutePmSmF00dCommand(SceUInt32 reserved);

int ksceSblPostSsMgrExecutePmSmF00dCommand(SceBool enable);
int ksceSblPostSsMgrExecutePmSmF00dCommand8(SceUInt8 *product_mode);
int ksceSblPostSsMgrExecutePmSmSdF00dCommand(void);

/**
 * Set the 32-bit CP physical RTC value.
 *
 * @param[in] rtc - New physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrSetCpRtc(int rtc);

/**
 * Set the CP logical RTC.
 *
 * @param[in] rtc - Logical RTC value on implementations that support the
 * operation.
 *
 * @note FW 3.60 does not implement this operation and returns 0x800F1025.
 */
int ksceSblRtcMgrSetCpRtcLogical(int rtc);

/**
 * Get the 32-bit CP logical RTC value.
 *
 * @param[out] rtc - Receives the logical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblRtcMgrGetCpRtcLogical(int *rtc);

/**
 * Get the 32-bit CP physical RTC value.
 *
 * @param[out] rtc - Receives the physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblRtcMgrGetCpRtcPhysical(int *rtc);

/**
 * Open an SPSFO file in a mapped memory block.
 *
 * @param[in] path - SPSFO path.
 * @param[out] result - Receives the opened context.
 */
int ksceSblPostSsMgrInitializeSpfsoCtx(const char *path, SceSblSpfsoContext *result);

/**
 * Close an SPSFO context and release its mapped memory block.
 *
 * @param[in,out] ctx - Opened SPSFO context.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPostSsMgrReleaseSpfsoCtx(SceSblSpfsoContext *ctx);

/**
 * Verify an opened SPSFO file.
 *
 * @param[in] ctx - Opened SPSFO context.
 * @param[out] payload - Receives the verified payload address through the
 * existing 32-bit pointer slot.
 * @param[out] payload_size - Receives the verified payload size in bytes.
 */
int ksceSblPostSsMgrVerifySpfsoCtx(SceSblSpfsoContext *ctx, int *payload, int *payload_size);

/**
 * Verify and persist an encrypted Utoken.
 *
 * @param[in] buf - Pointer to a ::SceUtoken buffer.
 * @param[in] size - Must be at least 0x800; exactly 0x800 bytes are consumed.
 */
int ksceSblUtMgrExecuteUtokenSmCommand1(char *buf, SceSize size);

/**
 * Get the Utoken type-11 self-authorization override.
 *
 * @param[out] self_auth_info - Receives a ::SceUtokenSelfAuthInfo structure.
 */
int ksceSblUtMgrGetTrilithiumBuffer(SceUtokenSelfAuthInfo *self_auth_info);

int ksceSblUtMgrHasComTestFlag(void);
int ksceSblUtMgrHasNpTestFlag(void);
int ksceSblUtMgrHasStoreFlag(void);

/** Get Utoken flag bit 1. Its purpose is unknown. */
int ksceSblUtMgrHasFlag1(void);

/** Get Utoken flag bit 6, which allows QAF PUP processing when set. */
int ksceSblUtMgrHasFlag6(void);

/** Get Utoken flag bit 7. Its purpose is unknown. */
int ksceSblUtMgrHasFlag7(void);

/** Get Utoken flag bit 8. Its purpose is unknown. */
int ksceSblUtMgrHasFlag8(void);

/** Get Utoken flag bit 9. Its purpose is unknown. */
int ksceSblUtMgrHasFlag9(void);

/**
 * Check whether a process is allowed to use COM test mode.
 *
 * @param[in] pid - Process whose program authority ID is checked.
 */
SceBool ksceSblUtMgrIsAllowComTest(SceUID pid);

/**
 * Check whether a program authority ID is in the Utoken debug whitelist.
 */
SceBool ksceSblUtMgrIsAllowProgramDebug(SceUInt64 program_authority_id);

int ksceSblUtMgrResetUtokenFile(void);

#define ksceSblPmMgrSetSdModeOff              _ksceSblPostSsMgrExecutePmSmF00dCommand
#define ksceSblPmMgrSetProductMode             ksceSblPostSsMgrExecutePmSmF00dCommand
#define ksceSblPmMgrGetProductModeFromNVS      ksceSblPostSsMgrExecutePmSmF00dCommand8
#define ksceSblPmMgrAuthEtoI                   ksceSblPostSsMgrExecutePmSmSdF00dCommand
#define ksceSblRtcMgrSetCpRtcPhysical          ksceSblPostSsMgrSetCpRtc
#define ksceSblSpsfoMgrOpen                    ksceSblPostSsMgrInitializeSpfsoCtx
#define ksceSblSpsfoMgrClose                   ksceSblPostSsMgrReleaseSpfsoCtx
#define ksceSblSpsfoMgrVerify                  ksceSblPostSsMgrVerifySpfsoCtx
#define ksceSblUtMgrGetSelfAuthInfo            ksceSblUtMgrGetTrilithiumBuffer

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_POST_SS_MGR_H_ */
