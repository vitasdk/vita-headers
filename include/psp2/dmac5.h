/**
 * \usergroup{SceSblDmac5Mgr}
 * \usage{psp2/dmac5.h,SceSblSsMgr_stub}
 */

#ifndef _PSP2_DMAC5_H_
#define _PSP2_DMAC5_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceSblDmac5EncDecParam { // size is 0x18-bytes
	const void *src; //<! The operation input buffer
	void *dst;       //<! The operation output buffer
	SceSize length;  //<! The src data length
	const void *key; //<! The key data
	SceSize keysize; //<! The key size in bits
	void *iv;        //<! The initialization vector
} SceSblDmac5EncDecParam;

typedef struct SceSblDmac5HashTransformContext { // size is 0x28-bytes
	SceUInt32 state[8];
	SceUInt64 length;
} SceSblDmac5HashTransformContext;

typedef struct SceSblDmac5HashTransformParam { // size is 0x18-bytes
	const void *src; //<! The operation input buffer
	void *dst;       //<! The operation output buffer
	SceSize length;  //<! The src data length
	const void *key; //<! The key data
	SceSize keysize; //<! The key size in bits
	void *ctx;       //<! SceSblDmac5HashTransformContext Or another context of size 0x10-bytes
} SceSblDmac5HashTransformParam;

/**
 * @brief Execute DMAC5 encdec command
 *
 * @param[inout] param   - The encdec param.
 * @param[in]    command - The DMAC5 encdec command.
 *
 * @return 0 on success, else < 0.
 */
int sceSblDmac5EncDec(SceSblDmac5EncDecParam *param, SceUInt32 command);


/**
 * @brief Execute DMAC5 hash transform command
 *
 * @param[inout] param   - The encdec param.
 * @param[in]    command - The DMAC5 hash base command.
 * @param[in]    extra   - The DMAC5 extra command.
 *
 * @return 0 on success, else < 0.
 */
int sceSblDmac5HashTransform(SceSblDmac5HashTransformParam *param, SceUInt32 command, SceUInt32 extra);


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
