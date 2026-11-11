/**
 * \usergroup{SceSblDmac5Mgr}
 * \usage{psp2/dmac5.h,SceSblSsMgr_stub}
 */

#ifndef _PSP2_DMAC5_H_
#define _PSP2_DMAC5_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/sblssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceSblDmac5EncDecParam { // size is 0x18-bytes
	const void *src; //!< Input buffer.
	void *dst;       //!< Output buffer.
	SceSize length;  //!< Length of the input data.
	const void *key; //!< Key data.
	SceSize keysize; //!< Key size in bits.
	void *iv;        //!< Initialization vector.
} SceSblDmac5EncDecParam;
VITASDK_BUILD_ASSERT_EQ(0x18, SceSblDmac5EncDecParam);

typedef struct SceSblDmac5HashTransformParam { // size is 0x18-bytes
	const void *src; //!< Input buffer.
	void *dst;       //!< Output buffer.
	SceSize length;  //!< Length of the input data.
	const void *key; //!< Key data.
	SceSize keysize; //!< Key size in bits.
	void *ctx;       //!< Pointer to a ::SceSblDmac5HashTransformContext, or a ::SceSblDmac5AesCmacContext for AES-CMAC.
} SceSblDmac5HashTransformParam;
VITASDK_BUILD_ASSERT_EQ(0x18, SceSblDmac5HashTransformParam);

/**
 * @brief Execute DMAC5 encdec command
 *
 * @param[in]     param  - Operation parameters. The destination and IV buffers
 *                         they point to are written.
 * @param[in]    command - The DMAC5 encdec command.
 *
 * @return 0 on success, else < 0.
 */
int sceSblDmac5EncDec(const SceSblDmac5EncDecParam *param, SceUInt32 command);

/**
 * Execute a user-mode DMAC5 cipher operation using an AuthMgr-derived key.
 *
 * The calling process must be a system program. Key sizes of 128 and 256 bits
 * are supported on FW 3.60. A 192-bit size passes this wrapper's validation but
 * is rejected by the AuthMgr key loader. CBC and CTR operations read their
 * 16-byte IV from ::SceSblDmac5EncDecParam::iv and replace it with the updated
 * IV.
 *
 * @param[in] param - Required operation parameters. The structure is only read;
 *                    the destination and IV buffers it points to are written.
 * @param[in] key_id - AuthMgr key identifier.
 * @param[in] command - DMAC5 cipher command word.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblDmac5EncDecKeyGen(const SceSblDmac5EncDecParam *param, SceUInt32 key_id, SceUInt32 command);


/**
 * @brief Execute DMAC5 hash transform command
 *
 * @param[in]     param  - Operation parameters. The destination and context
 *                         buffers they point to may be written.
 * @param[in]    command - The DMAC5 hash base command.
 * @param[in]    flags   - Bitwise OR of ::SceSblDmac5HashFlag values. Use 0
 *                         for a complete one-shot operation, 0x400 for the
 *                         first streaming chunk, 0xC00 for an intermediate
 *                         chunk, and 0x800 for the final chunk.
 *
 * @return 0 on success, else < 0.
 */
int sceSblDmac5HashTransform(const SceSblDmac5HashTransformParam *param, SceUInt32 command, SceUInt32 flags);

/**
 * Execute a user-mode keyed DMAC5 hash operation using an AuthMgr-derived key.
 *
 * The calling process must be a system program and
 * ::SceSblDmac5HashTransformParam::src must be 0x40-byte aligned. The key size
 * must be 128 or 256 bits. SHA-family commands use a 0x28-byte
 * ::SceSblDmac5HashTransformContext; AES-CMAC uses a 0x10-byte
 * ::SceSblDmac5AesCmacContext.
 *
 * @param[in] param - Required operation parameters. The structure is only read;
 *                    the output and context buffers it points to may be written.
 * @param[in] key_id - AuthMgr key identifier.
 * @param[in] command - DMAC5 hash or MAC command word.
 * @param[in] flags - Bitwise OR of ::SceSblDmac5HashFlag values.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblDmac5HmacKeyGen(const SceSblDmac5HashTransformParam *param, SceUInt32 key_id, SceUInt32 command, SceUInt32 flags);


static inline int sceSblDmac5AesCbcEnc(const void *src, void *dst, SceSize length, const void *key, SceSize keysize, void *iv)
{
	SceSblDmac5EncDecParam param = {.src = src, .dst = dst, .length = length, .key = key, .keysize = keysize, .iv = iv};

	return sceSblDmac5EncDec(
		&param,
		1 | 8 | (((keysize << 2) - 0x100) & 0x300)
	);
}

static inline int sceSblDmac5AesCbcDec(const void *src, void *dst, SceSize length, const void *key, SceSize keysize, void *iv)
{
	SceSblDmac5EncDecParam param = {.src = src, .dst = dst, .length = length, .key = key, .keysize = keysize, .iv = iv};

	return sceSblDmac5EncDec(
		&param,
		2 | 8 | (((keysize << 2) - 0x100) & 0x300)
	);
}

static inline int sceSblDmac5AesCtrEnc(const void *src, void *dst, SceSize length, const void *key, SceSize keysize, void *iv)
{
	SceSblDmac5EncDecParam param = {.src = src, .dst = dst, .length = length, .key = key, .keysize = keysize, .iv = iv};

	return sceSblDmac5EncDec(
		&param,
		1 | 0x20 | (((keysize << 2) - 0x100) & 0x300)
	);
}

static inline int sceSblDmac5AesCtrDec(const void *src, void *dst, SceSize length, const void *key, SceSize keysize, void *iv)
{
	SceSblDmac5EncDecParam param = {.src = src, .dst = dst, .length = length, .key = key, .keysize = keysize, .iv = iv};

	return sceSblDmac5EncDec(
		&param,
		2 | 0x20 | (((keysize << 2) - 0x100) & 0x300)
	);
}

static inline int sceSblDmac5Sha256Digest(const void *src, void *dst, SceSize length)
{
	SceSblDmac5HashTransformContext ctx;
	SceSblDmac5HashTransformParam param = {.src = src, .dst = dst, .length = length, .key = NULL, .keysize = 0, .ctx = &ctx};

	ctx.state[0] = __builtin_bswap32(0x6a09e667);
	ctx.state[1] = __builtin_bswap32(0xbb67ae85);
	ctx.state[2] = __builtin_bswap32(0x3c6ef372);
	ctx.state[3] = __builtin_bswap32(0xa54ff53a);
	ctx.state[4] = __builtin_bswap32(0x510e527f);
	ctx.state[5] = __builtin_bswap32(0x9b05688c);
	ctx.state[6] = __builtin_bswap32(0x1f83d9ab);
	ctx.state[7] = __builtin_bswap32(0x5be0cd19);
	ctx.length = 0LL;

	return sceSblDmac5HashTransform(
		&param,
		3 | 0x10, 0x800
	);
}


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_DMAC5_H_ */
