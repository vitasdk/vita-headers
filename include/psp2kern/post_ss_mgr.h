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
	char magic[8];                  //!< Must be "pfsSKKey".
	SceUInt8 major_version;         //!< Set to 2 when generated; legacy values 0 and 1 are also accepted.
	SceUInt8 minor_version;         //!< Must be 0 for the supported versions.
	SceUInt8 reserved[6];           //!< Set to 0 by ::ksceSblPostSsMgrEncryptSealedkey.
	SceUInt8 iv[0x10];
	SceUInt8 encrypted_key[0x10];
	SceUInt8 hmac[0x20];
} SceSblSealedKey;
VITASDK_BUILD_ASSERT_EQ(0x50, SceSblSealedKey); // size is from FW 3.60

typedef struct SceSblKeystone {
	char magic[8];                  //!< Must be "keystone".
	SceUInt16 type;                 //!< Must be 2.
	SceUInt16 version;              //!< Supported values are 0 and 1.
	SceUInt8 reserved[0x14];        //!< Included in the keystone HMAC.
	SceUInt8 passcode_digest[0x20];
	SceUInt8 keystone_digest[0x20];
} SceSblKeystone;
VITASDK_BUILD_ASSERT_EQ(0x60, SceSblKeystone); // size is from FW 3.60

typedef struct SceSblDebugKeystone {
	char magic[8];                  //!< Must be "keystone".
	SceUInt16 type;                 //!< Must be 1.
	SceUInt16 version;              //!< Set to 0 when encrypted and ignored when decrypted.
	SceUInt8 reserved[4];           //!< Set to 0 when encrypted and ignored when decrypted.
	SceUInt8 iv[0x10];
	SceUInt8 encrypted_secret[0x20];
} SceSblDebugKeystone;
VITASDK_BUILD_ASSERT_EQ(0x40, SceSblDebugKeystone); // size is from FW 3.60

typedef struct SceSblCloudDataKeyRing {
	char magic[8];                  //!< Magic value "CloudBU" followed by a NUL byte.
	SceUInt32 version;              //!< Supported values are 0 and 1.
	SceUInt8 opaque_header_data[4]; //!< Copied unchanged; not interpreted by the
	                               //!< FW 3.60 implementation or known importer.
	SceUInt8 p[0x80];               //!< RSA prime p.
	SceUInt8 q[0x80];               //!< RSA prime q.
	SceUInt8 dp[0x80];              //!< d mod (p - 1).
	SceUInt8 dq[0x80];              //!< d mod (q - 1).
	SceUInt8 qp[0x80];              //!< q^-1 mod p.
	SceUInt8 opaque_trailer_data[0x10]; //!< Copied unchanged; not interpreted by the
	                                   //!< FW 3.60 implementation or known importer.
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
	const void *n;        //!< Pointer to the RSA modulus.
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

/** Hash algorithms accepted by the RSA PKCS #1 v1.5 helpers. */
typedef enum SceSblRsaHashType {
	SCE_SBL_RSA_HASH_TYPE_MD2    = 0x2,
	SCE_SBL_RSA_HASH_TYPE_MD5    = 0x4,
	SCE_SBL_RSA_HASH_TYPE_SHA1   = 0x5,
	SCE_SBL_RSA_HASH_TYPE_SHA256 = 0xB,
	SCE_SBL_RSA_HASH_TYPE_SHA384 = 0xC,
	SCE_SBL_RSA_HASH_TYPE_SHA512 = 0xD,
	SCE_SBL_RSA_HASH_TYPE_SHA224 = 0xE
} SceSblRsaHashType;

/**
 * Create an RSA-2048 signature.
 *
 * @param[out] rsa_signature - Receives a 0x100-byte signature.
 * @param[in] hash - Hash to sign.
 * @param[in] private_key - RSA private key.
 * @param[in] type - One of ::SceSblRsaHashType. Declared as an integer for
 *                   backwards compatibility.
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
 * @param[in] type - One of ::SceSblRsaHashType. Declared as an integer for
 *                   backwards compatibility.
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
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblCoredumpGetHmacKey(SceUInt32 key_id, SceSize key_size, void *key);

/**
 * Get a coredump AES-128 key.
 *
 * @param[in] key_id - Key ID from 1 through 4, 0x10000001, or 0x10000002.
 * @param[in] key_size - Must be 0x10.
 * @param[out] key - Receives the key.
 *
 * @return SCE_OK on success, < 0 on error.
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
 * Validate the header and decrypt a debug keystone.
 *
 * Unlike ::ksceSblPostSsMgrVerifyKeystone, this function does not
 * authenticate the encrypted data or check the version or reserved fields.
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
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblSsMgrCloudDataGetSignCryptHandle(SceUInt32 mode, SceUInt32 index, SceSblCloudDataSignCryptHandle *handle);

/**
 * Securely clear the cloud-data encryption and signing key rings.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblSsMgrCloudDataStop(void);

/**
 * Load an authenticated firmware image.
 *
 * Call ::ksceSblFwLoaderLock first and ::ksceSblFwLoaderUnlock afterward.
 * On FW 3.60, the saved path can be used for only one load attempt. To load
 * another image, repeat the lock/load/unlock sequence.
 *
 * @param[in] e_phnum - Must be 1 on FW 3.60.
 * @param[out] destination - Destination buffer.
 * @param[in] max_size - Destination capacity.
 * @param[out] loaded_size - Receives the number of bytes loaded.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblFwLoaderLoad(int e_phnum, void *destination, SceSize max_size, SceSize *loaded_size);

/**
 * Lock and authenticate a firmware image.
 *
 * This function acquires the module's shared lock, which is held until
 * ::ksceSblFwLoaderUnlock is called.
 *
 * @param[in] path - NUL-terminated firmware SELF path of at most 255 bytes.
 * @param[in] reserved - Must be zero on FW 3.60.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblFwLoaderLock(const char *path, int reserved);

/**
 * Release the firmware-loader lock and discard the saved path.
 *
 * @return SCE_OK on success, < 0 if no load sequence is active.
 */
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
 *                       terminating NUL. FW 3.60 accepts paths under
 *                       `host0:`, `ux0:/data/activate/`, and
 *                       `ur0:/temp/activation`.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblLicMgrActivateDevkit(const char *afv_path);

/**
 * Get the cached activation expiration time or refresh it from NVS.
 *
 * @param[out] expire_date - When \a read_from_nvs is zero, receives the
 *                           cached absolute expiration time. Otherwise receives
 *                           the refreshed number of seconds remaining.
 * @param[in] read_from_nvs - Nonzero reads and verifies the NVS activation data.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblLicMgrGetExpireDate(int *expire_date, SceBool read_from_nvs);

/**
 * Disable SD mode through the PM secure module.
 *
 * @param[in] reserved - Must be zero on FW 3.60.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPmMgrSetSdModeOff(SceUInt32 reserved);

/**
 * Enter or leave manufacturing mode through the PM secure module.
 *
 * Only bit 0 of \a enable is used on FW 3.60.
 * The boot-time cached value returned by the user getters is not updated.
 *
 * @param[in] enable - Nonzero to enter manufacturing mode; zero to leave it.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPmMgrSetProductMode(SceBool enable);

/**
 * Read the raw product-mode byte from NVS through the PM secure module.
 *
 * Values written by the FW 3.60 product-mode operations correspond to
 * ::SceSblProductMode.
 *
 * @param[out] product_mode - Receives exactly one byte.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPmMgrGetProductModeFromNVS(SceUInt8 *product_mode);

/**
 * Perform the EtoI jig-authentication exchange through `pm_sm_sd.self`.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblPmMgrAuthEtoI(void);

/**
 * Set the 32-bit CP physical RTC value.
 *
 * @param[in] rtc - New physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblRtcMgrSetCpRtcPhysical(int rtc);

/**
 * Set the CP logical RTC.
 *
 * @param[in] rtc - Logical RTC value on implementations that support the
 * operation.
 *
 * @note FW 3.60 does not implement this operation and returns 0x800F1025.
 *
 * @return Always 0x800F1025 on FW 3.60.
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
 * FW 3.60 accepts files up to 0x8000 bytes on `gro0:`, `ur0:`, and `ux0:`.
 * `host0:` is accepted on non-CEX systems when QAF permits host access.
 *
 * @param[in] path - NUL-terminated SPSFO path of at most 255 bytes.
 * @param[out] context - Receives the opened context.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblSpsfoMgrOpen(const char *path, SceSblSpsfoContext *context);

/**
 * Close an SPSFO context and release its mapped memory block.
 *
 * The context is not cleared after its memory block is released.
 *
 * @param[in,out] context - Context returned by ::ksceSblSpsfoMgrOpen.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblSpsfoMgrClose(SceSblSpsfoContext *context);

/**
 * Verify an opened SPSFO file.
 *
 * The returned payload points inside the context's mapped memory and remains
 * valid only until ::ksceSblSpsfoMgrClose is called.
 * AuthMgr requires the mapped base address to be 0x20-byte aligned. It verifies
 * the file through secure command 8 before the payload is returned.
 *
 * @param[in] context - Context returned by ::ksceSblSpsfoMgrOpen.
 * @param[out] payload - Receives the verified payload address.
 * @param[out] payload_size - Receives the verified payload size in bytes.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblSpsfoMgrVerify(SceSblSpsfoContext *context, void **payload, SceSize *payload_size);

/**
 * Verify an encrypted Utoken and write it to storage.
 *
 * @param[in] utoken - Encrypted Utoken.
 * @param[in] size - Must be at least 0x800; exactly 0x800 bytes are used.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblUtMgrVerifyAndStoreUtoken(const SceUtoken *utoken, SceSize size);

/**
 * Get the Utoken type-11 self-authorization override.
 *
 * The output pointer must be non-NULL. FW 3.60 returns 0x800F1A02 when the
 * initialized Utoken does not contain a valid type-11 segment. AuthMgr uses
 * this override after SELF authentication for programs in the 0x2F0 PAID
 * family, replacing the program authority ID, capability, attribute, and
 * shared-secret fields together.
 *
 * @param[out] self_auth_info - Receives a ::SceUtokenSelfAuthInfo structure.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceSblUtMgrGetSelfAuthInfo(SceUtokenSelfAuthInfo *self_auth_info);

/** Check whether the initialized Utoken contains a COM-test PAID. */
int ksceSblUtMgrHasComTestFlag(void);

/**
 * Check whether NP-test policy is enabled.
 *
 * This is enabled by Utoken flag bit 11 or by the Utoken name
 * `UT_TRILITHIUM_FLAG` on FW 3.60.
 */
int ksceSblUtMgrHasNpTestFlag(void);

/**
 * Check whether Utoken flag bit 4 enables Store-mode policy.
 *
 * Callers use this flag for Store-specific DRM/save-data policy, privileged
 * update authorization, and the alternate advertisement-network clock.
 */
int ksceSblUtMgrHasStoreFlag(void);

/**
 * Get Utoken flag bit 1.
 *
 * SceSblACMgr uses this as an additional permission for selected FSELF
 * operations, including PSM-program, USB-serial, and virtual-machine policy.
 */
int ksceSblUtMgrHasFlag1(void);

/**
 * Get Utoken flag bit 6.
 *
 * SceSblUpdateMgr accepts this flag alongside QAF, COM-test, and Store
 * authorization for update containers marked as requiring privileged update
 * policy.
 */
int ksceSblUtMgrHasFlag6(void);

/**
 * Get Utoken flag bit 7.
 *
 * AppMgr uses this flag to allow save-data mounting to continue when
 * keystone verification fails.
 */
int ksceSblUtMgrHasFlag7(void);

/**
 * Get Utoken flag bit 8.
 *
 * SceSblACMgr uses this as the FSELF fallback for its capability-134 policy.
 * The broader purpose of the flag is unknown.
 */
int ksceSblUtMgrHasFlag8(void);

/**
 * Get Utoken flag bit 9.
 *
 * AppMgr requires this flag for the PAID-specific operation that mounts a
 * special save-data path and reads its `ACCOUNT_ID`.
 */
int ksceSblUtMgrHasFlag9(void);

/**
 * Check whether a process is allowed to use COM test mode.
 *
 * @param[in] pid - Process whose program authority ID is checked.
 *
 * @return 1 when the process matches the Utoken COM-test PAID, or 0 otherwise.
 */
SceBool ksceSblUtMgrIsAllowComTest(SceUID pid);

/**
 * Check whether a program authority ID is in the Utoken debug whitelist.
 *
 * @param[in] program_authority_id - Nonzero program authority ID to check
 *                                   against the 32-entry whitelist.
 *
 * @return 1 when allowed, or 0 otherwise.
 */
SceBool ksceSblUtMgrIsAllowProgramDebug(SceUInt64 program_authority_id);

/**
 * Overwrite and remove the stored Utoken file.
 *
 * Already parsed Utoken flags remain cached on FW 3.60 until the module is
 * reinitialized.
 */
int ksceSblUtMgrResetUtokenFile(void);

#define ksceSblPostSsMgrActivate                   ksceSblLicMgrActivateDevkit
#define ksceSblPostSsMgrGetExpireDate              ksceSblLicMgrGetExpireDate
#define _ksceSblPostSsMgrExecutePmSmF00dCommand    ksceSblPmMgrSetSdModeOff
#define ksceSblPostSsMgrExecutePmSmF00dCommand     ksceSblPmMgrSetProductMode
#define ksceSblPostSsMgrExecutePmSmF00dCommand8    ksceSblPmMgrGetProductModeFromNVS
#define ksceSblPostSsMgrExecutePmSmSdF00dCommand   ksceSblPmMgrAuthEtoI
#define ksceSblPostSsMgrSetCpRtc                    ksceSblRtcMgrSetCpRtcPhysical
#define ksceSblPostSsMgrInitializeSpfsoCtx          ksceSblSpsfoMgrOpen
#define ksceSblPostSsMgrReleaseSpfsoCtx             ksceSblSpsfoMgrClose
#define ksceSblPostSsMgrVerifySpfsoCtx              ksceSblSpsfoMgrVerify
#define ksceSblUtMgrExecuteUtokenSmCommand1         ksceSblUtMgrVerifyAndStoreUtoken
#define ksceSblUtMgrGetTrilithiumBuffer             ksceSblUtMgrGetSelfAuthInfo
#define ksceSblUtMgrHasPSMTestFlag                  ksceSblUtMgrHasFlag1
#define ksceSblUtMgrHasSystemDataFilePlayReadyFlag  ksceSblUtMgrHasFlag8

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_POST_SS_MGR_H_ */
