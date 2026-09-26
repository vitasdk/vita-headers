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

int ksceSblAimgrGetConsoleId(SceConsoleId *cid);
int ksceSblAimgrGetOpenPsId(SceOpenPsId *open_psid);
int ksceSblAimgrGetPscode(ScePsCode *pscode);

int ksceSblRngPseudoRandomNumber(void *result, SceSize size);

int ksceSblDmac5AesCbcDec(const void *src, void *dst, int size, const void *key, int key_size, void *iv, int mask_enable);
int ksceSblDmac5AesCbcEnc(const void *src, void *dst, int size, const void *key, int key_size, void *iv, int mask_enable);
int ksceSblDmac5AesCtrDec(const void *src, void *dst, int size, const void *key, int key_size, void *iv, int mask_enable);

#define ksceSblSsMgrAesCtrDecrypt ksceSblDmac5AesCtrDec

int ksceSblSsDecryptWithPortability(SceUInt32 key_type, const void *iv, const ScePortabilityData *src, ScePortabilityData *dst);

/**
 * Retrieve the secondary platform security code from aimgr_sm.
 *
 * The four 16-bit fields are returned in host byte order. This operation is
 * available only when the product-mode check allows it.
 *
 * @param[out] ps_code - Required eight-byte output.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAimgrGetPscode2(ScePsCode *ps_code);

/**
 * Retrieve the 32-byte visible identifier from aimgr_sm.
 *
 * @param[out] visible_id - Required output buffer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAimgrGetVisibleId(SceVisibleId *visible_id);

/**
 * Decrypt data using AES-CBC and an AuthMgr-derived key.
 *
 * @param[in] src - Input data.
 * @param[out] dst - Output data.
 * @param[in] size - Data size; must be a multiple of 0x10.
 * @param[in] key - Key material supplied to AuthMgr.
 * @param[in] key_length - Key size in bits: 128 or 256. AuthMgr rejects 192 bits on FW 3.60.
 * @param[in,out] iv - Required 16-byte IV, updated after the operation.
 * @param[in] key_id - AuthMgr key identifier: 0, 0x10000, 0x10001,
 *                     0x20000, or 0x20001.
 * @param[in] mask_enable - Nonzero to enable the DMAC memory-access mask.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblDmac5AesCbcDecNP(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, void *iv, SceUInt32 key_id, SceBool mask_enable);

/**
 * Encrypt data using AES-CBC and an AuthMgr-derived key.
 *
 * Parameters and return values are the same as
 * ::ksceSblDmac5AesCbcDecNP.
 */
int ksceSblDmac5AesCbcEncNP(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, void *iv, SceUInt32 key_id, SceBool mask_enable);

/**
 * Compute AES-CMAC using an AuthMgr-derived key.
 *
 * @param[in] src - Input data.
 * @param[out] dst - Optional 16-byte MAC output.
 * @param[in] length - Input size.
 * @param[in] key - Key material supplied to AuthMgr.
 * @param[in] keysize - Key size in bits: 128 or 256.
 * @param[in,out] ctx - Optional 0x10-byte AES-CMAC chaining context.
 * @param[in] key_id - AuthMgr key identifier: 0, 0x10000, 0x10001,
 *                     0x20000, or 0x20001.
 * @param[in] mask_enable - Nonzero to enable the DMAC memory-access mask.
 * @param[in] flags - Bitwise OR of ::SceSblDmac5HashFlag values.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblDmac5AesCmacNP(const void *src, void *dst, SceSize length, const void *key, SceSize keysize, SceSblDmac5AesCmacContext *ctx, SceUInt32 key_id, SceBool mask_enable, SceUInt32 flags);

/**
 * Compute AES-CMAC using a preloaded DMAC5 key slot.
 *
 * @param[in] src - Input data.
 * @param[out] dst - Optional 16-byte MAC output.
 * @param[in] size - Input size.
 * @param[in] keyslot - One of ::SceSblDmac5Keyslot.
 * @param[in] key_length - Key size in bits: 128, 192, or 256.
 * @param[in,out] ctx - Optional 0x10-byte chaining context.
 * @param[in] mask_enable - Nonzero to enable the DMAC memory-access mask.
 * @param[in] flags - Bitwise OR of ::SceSblDmac5HashFlag values.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblDmac5AesCmacWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyslot, SceSize key_length, SceSblDmac5AesCmacContext *ctx, SceBool mask_enable, SceUInt32 flags);

/**
 * Encrypt or decrypt data using AES-CTR and a caller-supplied key.
 *
 * @param[in] src - Input data.
 * @param[out] dst - Output data.
 * @param[in] size - Data size.
 * @param[in] key - AES key.
 * @param[in] key_length - Key size in bits: 128, 192, or 256.
 * @param[in,out] iv - Required 16-byte counter, updated after the operation.
 * @param[in] mask_enable - Nonzero to enable the DMAC memory-access mask.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblDmac5AesCtrEnc(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, void *iv, SceBool mask_enable);

/**
 * Decrypt data using AES-ECB and a caller-supplied key.
 *
 * @param[in] src - Input data.
 * @param[out] dst - Output data.
 * @param[in] size - Data size; must be a multiple of 0x10.
 * @param[in] key - AES key.
 * @param[in] key_length - Key size in bits: 128, 192, or 256.
 * @param[in] mask_enable - Nonzero to enable the DMAC memory-access mask.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblDmac5AesEcbDec(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, SceBool mask_enable);

/**
 * Decrypt data using AES-ECB and an AuthMgr-derived key.
 *
 * @param[in] src - Input data.
 * @param[out] dst - Output data.
 * @param[in] size - Data size; must be a multiple of 0x10.
 * @param[in] key - Key material supplied to AuthMgr.
 * @param[in] key_length - Key size in bits: 128 or 256.
 * @param[in] key_id - AuthMgr key identifier: 0, 0x10000, 0x10001,
 *                     0x20000, or 0x20001.
 * @param[in] mask_enable - Nonzero to enable the DMAC memory-access mask.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblDmac5AesEcbDecNP(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, SceUInt32 key_id, SceBool mask_enable);

/**
 * Decrypt data using AES-ECB and a preloaded DMAC5 key slot.
 *
 * @param[in] keyslot - One of ::SceSblDmac5Keyslot.
 *
 * Other parameters and return values are the same as
 * ::ksceSblDmac5AesEcbDec.
 */
int ksceSblDmac5AesEcbDecWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyslot, SceSize key_length, SceBool mask_enable);

/** Encrypt data using AES-ECB and a caller-supplied key. */
int ksceSblDmac5AesEcbEnc(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, SceBool mask_enable);

/** Encrypt data using AES-ECB and an AuthMgr-derived 128- or 256-bit key. */
int ksceSblDmac5AesEcbEncNP(const void *src, void *dst, SceSize size, const void *key, SceSize key_length, SceUInt32 key_id, SceBool mask_enable);

/**
 * Encrypt data using AES-ECB and a preloaded DMAC5 key slot.
 *
 * @param[in] keyslot - One of ::SceSblDmac5Keyslot.
 */
int ksceSblDmac5AesEcbEncWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyslot, SceSize key_length, SceBool mask_enable);

/**
 * Decrypt data using DES or 3DES-CBC and a preloaded DMAC5 key slot.
 *
 * @param[in] keyslot - One of ::SceSblDmac5Keyslot.
 * @param[in,out] iv - Required eight-byte IV, updated after the operation.
 */
int ksceSblDmac5DesCbcDecWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyslot, SceSize key_length, void *iv, SceBool mask_enable);

/** Encrypt data using DES or 3DES-CBC and a preloaded DMAC5 key slot. */
int ksceSblDmac5DesCbcEncWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyslot, SceSize key_length, void *iv, SceBool mask_enable);

/** Decrypt data using DES or 3DES-ECB and a preloaded DMAC5 key slot. */
int ksceSblDmac5DesEcbDecWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyslot, SceSize key_length, SceBool mask_enable);

/** Encrypt data using DES or 3DES-ECB and a preloaded DMAC5 key slot. */
int ksceSblDmac5DesEcbEncWithKeyslot(const void *src, void *dst, SceSize size, SceUInt32 keyslot, SceSize key_length, SceBool mask_enable);

/**
 * @brief Generate random bytes using DMAC5.
 *
 * @param[out] output_buffer - Output buffer; required when \a size is nonzero.
 * @param[in] size - Number of bytes to generate. Must be at most 0x40.
 * @param[in] mask_enable - Nonzero to apply the DMAC access mask.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblDmac5Rnd(void *output_buffer, SceSize size, SceBool mask_enable);

/**
 * Compute or continue a SHA-1 digest.
 *
 * @param[in] src - Input data.
 * @param[out] dst - Optional 20-byte digest output.
 * @param[in] length - Input size.
 * @param[in,out] ctx - Optional 0x28-byte SHA chaining context.
 * @param[in] mask_enable - Nonzero to enable the DMAC memory-access mask.
 * @param[in] flags - Bitwise OR of ::SceSblDmac5HashFlag values.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblDmac5Sha1(const void *src, void *dst, SceSize length, SceSblDmac5HashTransformContext *ctx, SceBool mask_enable, SceUInt32 flags);

/**
 * Compute or continue a SHA-1 HMAC using an AuthMgr-derived 256-bit key.
 *
 * @param[in] key - 0x20-byte key material supplied to AuthMgr.
 * @param[in] key_id - AuthMgr key identifier: 0, 0x10000, 0x10001,
 *                     0x20000, or 0x20001.
 *
 * Other parameters and return values are the same as ::ksceSblDmac5Sha1.
 */
int ksceSblDmac5Sha1HmacNP(const void *src, void *dst, SceSize length, const void *key, SceSblDmac5HashTransformContext *ctx, SceUInt32 key_id, SceBool mask_enable, SceUInt32 flags);

/**
 * Compute or continue a SHA-1 HMAC using a caller-supplied 0x20-byte key.
 */
int ksceSblDmac5Sha1HmacTransform(const void *src, void *dst, SceSize length, const void *key, SceSblDmac5HashTransformContext *ctx, SceBool mask_enable, SceUInt32 flags);

/**
 * Compute or continue a SHA-256 HMAC using a caller-supplied 0x20-byte key.
 *
 * \a dst receives 0x20 bytes for a completed operation.
 */
int ksceSblDmac5Sha256Hmac(const void *src, void *dst, SceSize length, const void *key, SceSblDmac5HashTransformContext *ctx, SceBool mask_enable, SceUInt32 flags);

/**
 * Read an arbitrary Syscon NVS range in chunks of at most eight bytes.
 *
 * @param[in] offset - NVS byte offset.
 * @param[out] buffer - Destination buffer. It may be NULL only when \a size is 0.
 * @param[in] size - Number of bytes to read.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblNvsReadData(SceUInt32 offset, void *buffer, SceSize size);

/**
 * Write an arbitrary Syscon NVS range in chunks of at most eight bytes.
 *
 * @param[in] offset - NVS byte offset.
 * @param[in] buffer - Source buffer. It may be NULL only when \a size is 0.
 * @param[in] size - Number of bytes to write.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblNvsWriteData(SceUInt32 offset, const void *buffer, SceSize size);

/**
 * Copy the 16 cached QA-flag bytes.
 *
 * @param[out] buffer - Required 0x10-byte output buffer.
 *
 * @return 0 on success, < 0 when the QAF state is unavailable.
 */
int ksceSblQafManagerGetQAFlags(SceUInt8 buffer[0x10]);

/**
 * Copy the active QAF profile name.
 *
 * Values of \a max_len above 0x18 are treated as 0x18. The resulting string is
 * always NUL-terminated within the selected range.
 *
 * @param[out] buffer - Required profile-name buffer.
 * @param[in] max_len - Number of writable bytes; must be nonzero.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblQafManagerGetQafName(char *buffer, SceSize max_len);

/** @return 1 when QA configuration allows IDU automatic updates, otherwise 0. */
int ksceSblQafMgrIsAllowControlIduAutoUpdate(void);

/** @return 1 when QA configuration allows decrypted boot-configuration loading, otherwise 0. */
int ksceSblQafMgrIsAllowDecryptedBootConfigLoad(void);

/** @return 1 when QA configuration allows DTCP-IP reset operations, otherwise 0. */
int ksceSblQafMgrIsAllowDtcpIpReset(void);

/** @return 1 when QA configuration allows `host0:` access, otherwise 0. */
int ksceSblQafMgrIsAllowHost0Access(void);

/** @return 1 when QA configuration allows retaining core files, otherwise 0. */
int ksceSblQafMgrIsAllowKeepCoreFile(void);

/** @return 1 when QA configuration allows loading MagicGate components, otherwise 0. */
int ksceSblQafMgrIsAllowLoadMagicGate(void);

/** @return 1 when QA configuration allows Marlin testing, otherwise 0. */
int ksceSblQafMgrIsAllowMarlinTest(void);

/** @return 1 when QA configuration allows Near testing, otherwise 0. */
int ksceSblQafMgrIsAllowNearTest(void);

/** @return 1 when QA configuration allows showing PSPEmu QA information, otherwise 0. */
int ksceSblQafMgrIsAllowPSPEmuShowQAInfo(void);

/** @return 1 when QA configuration allows Remote Play debugging, otherwise 0. */
int ksceSblQafMgrIsAllowRemotePlayDebug(void);

/** @return 1 when QA configuration allows system-application debugging, otherwise 0. */
int ksceSblQafMgrIsAllowSystemAppDebug(void);

/**
 * Generate exactly 0x40 bytes of DMAC5 genuine-random output.
 *
 * @param[out] dest - Required 0x40-byte output buffer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblRngGenuineRandomNumber(void *dest);

/**
 * Create a 0x200-byte CMA pass phrase through aimgr_sm command 5.
 *
 * The function copies the 16 account-ID characters, IdStorage leaf 0x44, and
 * the current secure tick into the secure-module request. It does not inspect
 * ::SceSblSsCreatePassPhraseParam::size.
 *
 * @param[in] param - Required 0x18-byte input parameters.
 * @param[out] pass_phrase - Required 0x200-byte output buffer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSsCreatePassPhrase(const SceSblSsCreatePassPhraseParam *param, void *pass_phrase);

/**
 * Encrypt a portability message.
 *
 * On FW 3.60 only key type 0 succeeds; after validating the current process's
 * SELF authentication information, it copies the plaintext message unchanged.
 * Key types 1 through 20 return an invalid-argument error without invoking a
 * secure module. The input and output message sizes must match, be at most
 * 0x20, and be multiples of 0x10.
 *
 * @param[in] key_type - Portability key type, from 0 through 20.
 * @param[in] iv - Required 0x10-byte IV.
 * @param[in] plain_msg - Required plaintext message.
 * @param[in,out] enc_msg - Required output whose
 *                          ::ScePortabilityData::msg_size is initialized to
 *                          the plaintext message size.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceSblSsEncryptWithPortability(SceUInt32 key_type, const void *iv, const ScePortabilityData *plain_msg, ScePortabilityData *enc_msg);

/**
 * Read the NVS value selected by \a type.
 *
 * \a size must be 1, 2, 4, 8, 16, or 32 and must be at least the selected
 * value's size. Only that value's bytes are copied.
 *
 * @param[in] type - NVS value to read.
 * @param[out] data - Required output buffer.
 * @param[in] size - Caller buffer size, subject to the limits above.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSsGetNvsData(SceSblSsNvsDataType type, void *data, SceSize size);

/**
 * Fill a memory range and return \a dest.
 *
 * @param[out] dest - Destination memory.
 * @param[in] value - Byte value; only the low eight bits are used.
 * @param[in] size - Number of bytes to write.
 *
 * @return \a dest.
 */
void *ksceSblSsMemset(void *dest, int value, SceSize size);

/**
 * @brief Execute a DMAC5 hash-family command.
 *
 * @param[in] src - Input data.
 * @param[out] dst - Optional command-dependent digest or MAC output.
 * @param[in] size - Input size.
 * @param[in,out] ctx - Command-dependent chaining context. SHA-family commands
 * use a ::SceSblDmac5HashTransformContext; AES-CMAC uses a 0x10-byte context.
 * @param[in] mask_enable - Nonzero to apply the DMAC access mask.
 * @param[in] command - DMAC5 base command.
 * @param[in] flags - Bitwise OR of ::SceSblDmac5HashFlag values.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSsMgrExecuteDmac5HashCommand(const void *src, void *dst, SceSize size, void *ctx, SceBool mask_enable, SceUInt32 command, SceUInt32 flags);

/**
 * Write the NVS value selected by \a type.
 *
 * \a size follows the same validation rules as ::ksceSblSsGetNvsData.
 * Only the selected value's bytes are written.
 *
 * @param[in] type - NVS value to write.
 * @param[in] data - Required source buffer.
 * @param[in] size - Caller buffer size, subject to the limits above.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSsSetNvsData(SceSblSsNvsDataType type, const void *data, SceSize size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SSMGR_H_ */
