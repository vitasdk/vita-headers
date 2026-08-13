/**
 * \kernelgroup{SceSblSsMgr}
 * \usage{psp2kern/kernel/ssmgr.h,SceSblSsMgrForDriver_stub SceSblSsMgrForKernel_stub SceQafMgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SSMGR_H_
#define _PSP2KERN_KERNEL_SSMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/sblssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceConsoleId { // size is 0x10
	uint16_t unk; //!< Its purpose is unknown; ignored on FW 3.60 and by observed importers.
	uint16_t company_code;
	uint16_t product_code;
	uint16_t product_sub_code;
	union {
		struct {
			uint8_t unk2: 2; //!< Not interpreted by observed FW 3.60 importers.
			uint8_t factory_code: 6;
		};
		uint8_t chassis_check;
	};
	uint8_t unk3[7]; //!< Its purpose is unknown; ignored on FW 3.60 and by observed importers.
} SceConsoleId;
VITASDK_BUILD_ASSERT_EQ(0x10, SceConsoleId);

typedef struct ScePsCode {
	uint16_t company_code;
	uint16_t product_code;
	uint16_t product_sub_code;
	uint16_t factory_code;
} ScePsCode;
VITASDK_BUILD_ASSERT_EQ(8, ScePsCode);

int ksceSblAimgrGetConsoleId(SceConsoleId *cid);
int ksceSblAimgrGetOpenPsId(SceOpenPsId *open_psid);
int ksceSblAimgrGetPscode(ScePsCode *pscode);

int ksceSblRngPseudoRandomNumber(void *result, SceSize size);

int ksceSblDmac5AesCbcDec(const void *src, void *dst, int size, const void *key, int key_size, void *iv, int mask_enable);
int ksceSblDmac5AesCbcEnc(const void *src, void *dst, int size, const void *key, int key_size, void *iv, int mask_enable);
int ksceSblDmac5AesCtrDec(const void *src, void *dst, int size, const void *key, int key_size, void *iv, int mask_enable);

#define ksceSblSsMgrAesCtrDecrypt ksceSblDmac5AesCtrDec

typedef struct ScePortabilityData { // size is 0x24
	SceSize msg_size;           // max size is 0x20
	uint8_t msg[0x20];
} ScePortabilityData;
VITASDK_BUILD_ASSERT_EQ(0x24, ScePortabilityData);

int ksceSblSsDecryptWithPortability(SceUInt32 key_type, void *iv, ScePortabilityData *src, ScePortabilityData *dst);

typedef struct SceSblSsCreatePassPhraseParam {
	SceUInt32 reserved; //!< Known FW 3.60 caller sets this to 0; forwarded to the secure module.
	SceSize size; //!< Size of this structure; ignored on FW 3.60.
	char accountIdText[0x10]; //!< Lowercase hexadecimal representation of the account ID.
} SceSblSsCreatePassPhraseParam;
VITASDK_BUILD_ASSERT_EQ(0x18, SceSblSsCreatePassPhraseParam); // size is from FW 3.60

typedef enum SceSblSsNvsDataType {
	SCE_SBL_SS_NVS_DATA_SYSTEM_LANGUAGE = 0,
	SCE_SBL_SS_NVS_DATA_WLAN_BT = 1,
	SCE_SBL_SS_NVS_DATA_UNK_482 = 2, //!< One-byte value at NVS offset 0x482; semantics remain unidentified.
	SCE_SBL_SS_NVS_DATA_KIBAN_ID = 3,
	SCE_SBL_SS_NVS_DATA_SAFEMODE_FLAGS = 4,
	SCE_SBL_SS_NVS_DATA_USE_INT_STOR = 5
} SceSblSsNvsDataType;

int ksceSblAimgrGetPscode2(ScePsCode *pPsCode);
int ksceSblAimgrGetVisibleId(SceVisibleId *pVisibleId);
int ksceSblDmac5AesCbcDecNP(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, void *iv, SceUInt32 key_id, SceUInt32 mask_enable);
int ksceSblDmac5AesCbcEncNP(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, void *iv, SceUInt32 key_id, SceUInt32 mask_enable);

/**
 * @param[inout] ctx - A pointer to a 0x10-byte AES-CMAC chaining context.
 * @param[in] flags - Bitwise OR of ::SceSblDmac5HashFlag values.
 */
int ksceSblDmac5AesCmacNP(const void *src, void *dst, SceSize length, const void *key, SceSize keysize, SceSblDmac5HashTransformContext *ctx, SceUInt32 key_id, SceBool mask_enable, SceUInt32 flags);
int ksceSblDmac5AesCmacWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyring_id, SceSize key_length, void *iv, SceUInt32 mask_enable, SceUInt32 flags);
int ksceSblDmac5AesCtrEnc(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, void *iv, SceUInt32 mask_enable);
int ksceSblDmac5AesEcbDec(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, SceUInt32 mask_enable);
int ksceSblDmac5AesEcbDecNP(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, SceUInt32 key_id, SceUInt32 mask_enable);
int ksceSblDmac5AesEcbDecWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyring_id, SceSize key_length, SceUInt32 mask_enable);
int ksceSblDmac5AesEcbEnc(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, SceUInt32 mask_enable);
int ksceSblDmac5AesEcbEncNP(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, SceUInt32 key_id, SceUInt32 mask_enable);
int ksceSblDmac5AesEcbEncWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyring_id, SceSize key_length, SceUInt32 mask_enable);
int ksceSblDmac5DesCbcDecWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyring_id, SceSize key_length, void *iv, SceUInt32 mask_enable);
int ksceSblDmac5DesCbcEncWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyring_id, SceSize key_length, void *iv, SceUInt32 mask_enable);
int ksceSblDmac5DesEcbDecWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyring_id, SceSize key_length, SceUInt32 mask_enable);
int ksceSblDmac5DesEcbEncWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyring_id, SceSize key_length, SceUInt32 mask_enable);

/**
 * @brief Generate random bytes using DMAC5.
 *
 * @param[out] pOutputBuffer - Output buffer.
 * @param[in] size - Number of bytes to generate. Must be at most 0x40.
 * @param[in] mask_enable - Nonzero to apply the DMAC access mask.
 */
int ksceSblDmac5Rnd(char *pOutputBuffer, int size, int mask_enable);
int ksceSblDmac5Sha1(const void *src, void *dst, SceSize length, SceSblDmac5HashTransformContext *ctx, SceUInt32 mask_enable, SceUInt32 flags);
int ksceSblDmac5Sha1HmacNP(const void *src, void *dst, SceSize length, const void *key, SceSblDmac5HashTransformContext *ctx, SceUInt32 key_id, SceBool mask_enable, SceUInt32 flags);
int ksceSblDmac5Sha1HmacTransform(const void *src, void *dst, SceSize length, const void *key, SceSblDmac5HashTransformContext *ctx, SceBool mask_enable, SceUInt32 flags);
int ksceSblDmac5Sha256Hmac(const void *src, void *dst, SceSize length, const void *key, SceSblDmac5HashTransformContext *ctx, SceBool mask_enable, SceUInt32 flags);
int ksceSblNvsReadData(int offset, char *buffer, int size);
int ksceSblNvsWriteData(int offset, char *buffer, int size);
int ksceSblQafManagerGetQAFlags(char buffer[0x10]);
int ksceSblQafManagerGetQafName(char *buffer, unsigned int max_len);
int ksceSblQafMgrIsAllowControlIduAutoUpdate(void);
int ksceSblQafMgrIsAllowDecryptedBootConfigLoad(void);
int ksceSblQafMgrIsAllowDtcpIpReset(void);
int ksceSblQafMgrIsAllowHost0Access(void);
int ksceSblQafMgrIsAllowKeepCoreFile(void);
int ksceSblQafMgrIsAllowLoadMagicGate(void);
int ksceSblQafMgrIsAllowMarlinTest(void);
int ksceSblQafMgrIsAllowNearTest(void);
int ksceSblQafMgrIsAllowPSPEmuShowQAInfo(void);
int ksceSblQafMgrIsAllowRemotePlayDebug(void);
int ksceSblQafMgrIsAllowSystemAppDebug(void);
int ksceSblRngGenuineRandomNumber(char *dest);
int ksceSblSsCreatePassPhrase(SceSblSsCreatePassPhraseParam *pParam, void *pPassPhrase);
SceInt32 ksceSblSsEncryptWithPortability(SceUInt32 key_type, void *iv, ScePortabilityData *plain_msg, ScePortabilityData *enc_msg);
int ksceSblSsGetNvsData(SceSblSsNvsDataType type, void *pData, SceSize size);
void ksceSblSsMemset(char *dest, char value, SceSize size);

/**
 * @brief Execute a DMAC5 hash-family command.
 *
 * @param[inout] ctx - Command-dependent chaining context. SHA-family commands
 * use a ::SceSblDmac5HashTransformContext; AES-CMAC uses a 0x10-byte context.
 * @param[in] mask_enable - Nonzero to apply the DMAC access mask.
 * @param[in] command - DMAC5 base command.
 * @param[in] flags - Bitwise OR of ::SceSblDmac5HashFlag values.
 */
int ksceSblSsMgrExecuteDmac5HashCommand(const void *src, void *dst, SceSize size, void *ctx, SceUInt32 mask_enable, SceUInt32 command, SceUInt32 flags);
int ksceSblSsSetNvsData(SceSblSsNvsDataType type, void *pData, SceSize size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SSMGR_H_ */
