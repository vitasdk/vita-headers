/**
 * \usergroup{SceSblGcAuthMgr}
 * \usage{psp2/sblgcauthmgr.h,SceSblGcAuthMgr_stub SceLibKernel_stub}
 */

#ifndef _PSP2_SBLGCAUTHMGR_H_
#define _PSP2_SBLGCAUTHMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceMediaIdType01 {
	char enc_data[0x10]; //!< First 0x10 bytes returned by secure command 0x23.
	char enc_data_cmac[0x10]; //!< Remaining 0x10 bytes returned by secure command 0x23.
} SceMediaIdType01;
VITASDK_BUILD_ASSERT_EQ(0x20, SceMediaIdType01); // size is from FW 3.60

typedef struct _sceSblGcAuthMgrGetMediaIdType01_opt {
	SceSize mediaIdSize; //!< Number of bytes to copy to pMediaId. Maximum size is 0x20 bytes.
	SceUInt32 unused; //!< Copied from user memory but actually unused on FW 3.60.
} _sceSblGcAuthMgrGetMediaIdType01_opt;
VITASDK_BUILD_ASSERT_EQ(0x8, _sceSblGcAuthMgrGetMediaIdType01_opt); // size is from FW 3.60

typedef struct ScePcactActivationKeyData {
	short magic; //!< Must be 0x0211.
	char mode; //!< Must match the mode used to create the challenge. Valid values are 0, 1, and 2.
	char reserved[0xD]; //!< Must be zeroed.
	char protectedKeyData[0x30]; //!< Protected payload used to derive the activation key.
	char verificationTag[0x10]; //!< Tag verified before the protected payload is accepted.
} ScePcactActivationKeyData;
VITASDK_BUILD_ASSERT_EQ(0x50, ScePcactActivationKeyData); // size is from FW 0.990

typedef struct ScePcactActivationData {
	ScePcactActivationKeyData keyData; //!< Key data verified against the saved challenge state.
	char act_dat[0x1040]; //!< Activation payload written after key verification.
} ScePcactActivationData;
VITASDK_BUILD_ASSERT_EQ(0x1090, ScePcactActivationData); // size is from FW 0.990

typedef struct ScePcactGetChallengeOpt {
	SceSize epasswordSize; //!< Maximum size is 0x20 bytes.
	SceSize challengeSize; //!< Maximum size is 0x80 bytes.
	char reserved[8]; //!< Copied from user memory but actually unused on FW 3.60.
} ScePcactGetChallengeOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, ScePcactGetChallengeOpt); // size is from FW 0.990-3.740.011

typedef struct SceSblGcAuthMgrPkgVryInfo {
	SceSize hashSize; //!< Number of hash bytes to copy. Maximum size is 0x14 bytes.
	SceSize sigSize; //!< Number of signature bytes to copy. Maximum size is 0x28 bytes.
	SceUInt64 reserved; //!< Copied from user memory but actually unused on FW 3.60.
} SceSblGcAuthMgrPkgVryInfo;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSblGcAuthMgrPkgVryInfo); // size is from FW 3.60

/**
 * Get the 0x20-byte type 01 media ID produced by the game-card authentication state.
 *
 * @param[out] pMediaId - Output media ID.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblGcAuthMgrGetMediaIdType01(SceMediaIdType01 *pMediaId);

/**
 * Install PC activation data.
 *
 * @param[in] act_data - Pointer to a 0x1090-byte activation object.
 * @param[in] act_data_size - Must be 0x1090.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblGcAuthMgrPcactActivation(const ScePcactActivationData *act_data, SceSize act_data_size);

/**
 * Create a PC activation challenge.
 *
 * @param[in] mode - One of the values 0, 1, or 2.
 * @param[in] epassword - Pointer to a 0x20-byte input.
 * @param[out] challenge - Pointer to a 0x80-byte output.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblGcAuthMgrPcactGetChallenge(SceUInt32 mode, const char *epassword, char *challenge);

/**
 * Verify a package ECDSA-160 signature.
 *
 * @param[in] pHash - Pointer to a 0x14-byte SHA-1 digest.
 * @param[in] pSig - Pointer to a 0x28-byte ECDSA signature.
 *
 * @return 0 if the signature is valid, < 0 on error.
 */
int sceSblGcAuthMgrPkgVry(const char *pHash, const char *pSig);

int _sceSblGcAuthMgrGetMediaIdType01(SceMediaIdType01 *pMediaId, const _sceSblGcAuthMgrGetMediaIdType01_opt *pOpt);
int _sceSblGcAuthMgrPcactActivation(const ScePcactActivationData *act_data, SceSize act_data_size);
int _sceSblGcAuthMgrPcactGetChallenge(SceUInt32 mode, const char *epassword, char *challenge, ScePcactGetChallengeOpt *pOpt);
int _sceSblGcAuthMgrPkgVry(const char *pHash, const char *pSig, SceSblGcAuthMgrPkgVryInfo *pInfo);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLGCAUTHMGR_H_ */
