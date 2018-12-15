/**
 * \kernelgroup{SceUtils}
 * \usage{psp2kern/kernel/utils.h,SceKernelUtilsForDriver_stub}
 */


#ifndef _PSP2_KERNEL_UTILS_H_
#define _PSP2_KERNEL_UTILS_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_SHA1_BLOCK_SIZE    64
#define SCE_SHA1_DIGEST_SIZE   20
#define SCE_SHA224_BLOCK_SIZE  64
#define SCE_SHA224_DIGEST_SIZE 28
#define SCE_SHA256_BLOCK_SIZE  64
#define SCE_SHA256_DIGEST_SIZE 32

typedef struct SceSha1Context {
	uint32_t h[5];
	uint16_t usRemains;
	uint16_t usComputed;
	uint64_t ullTotalLen;
	char buf[SCE_SHA1_BLOCK_SIZE];
	char result[SCE_SHA1_DIGEST_SIZE];
	uint32_t pad;
} SceSha1Context;

typedef struct SceSha224Context {
	uint32_t h[8];
	uint32_t pad;
	uint16_t usRemains;
	uint16_t usComputed;
	uint64_t ullTotalLen;
	char buf[SCE_SHA224_BLOCK_SIZE];
	char result[SCE_SHA224_DIGEST_SIZE];
	uint32_t pad2;
} SceSha224Context;

typedef struct SceSha256Context {
	uint32_t h[8];
	uint32_t pad;
	uint16_t usRemains;
	uint16_t usComputed;
	uint64_t ullTotalLen;
	char buf[SCE_SHA256_BLOCK_SIZE];
	char result[SCE_SHA256_DIGEST_SIZE];
} SceSha256Context;

struct SceDeflatePartialInputParam;

typedef struct SceDeflatePartialInputParam {
	uint32_t size;
	const void *pBufEnd;
	void *cookie;
	const void *(* SceDeflateDecompressPartialInputCallback)(struct SceDeflatePartialInputParam* param, uint32_t outputsize);
} SceDeflatePartialInputParam;

typedef struct {
	uint8_t data[976];
} SceAesContext;

int ksceSha1BlockInit(SceSha1Context *pContext);
int ksceSha1BlockUpdate(SceSha1Context *pContext, const void *plain, uint32_t len);
int ksceSha1BlockResult(SceSha1Context *pContext, char *digest);
int ksceSha1Digest(const void *plain, uint32_t len, char *result);

int ksceSha224BlockInit(SceSha224Context *pContext);
int ksceSha224BlockUpdate(SceSha224Context *pContext, const void *plain, uint32_t len);
int ksceSha224BlockResult(SceSha224Context *pContext, char *digest);
int ksceSha224Digest(const void *plain, uint32_t len, char *result);

int ksceSha256BlockInit(SceSha256Context *pContext);
int ksceSha256BlockUpdate(SceSha256Context *pContext, const void *plain, uint32_t len);
int ksceSha256BlockResult(SceSha256Context *pContext, char *digest);
int ksceSha256Digest(const void *plain, uint32_t len, char *result);

int ksceHmacSha1Digest(const unsigned char *key, uint32_t key_len, const void *plain, uint32_t len, char *result);
int ksceHmacSha224Digest(const unsigned char *key, uint32_t key_len, const void *plain, uint32_t len, char *result);
int ksceHmacSha256Digest(const unsigned char *key, uint32_t key_len, const void *plain, uint32_t len, char *result);

/**
 * @param[out] dst - dst buf
 * @param[in] dst_size - dst buf size
 * @param[in] src - Gzip compressed data
 * @param[out] crc32 - crc32 when decompressed
 *
 * @return decompressed size on success, < 0 on error.
 */
int ksceGzipDecompress(void *dst, uint32_t dst_size, const void *src, uint32_t *crc32);

/**
 * @brief Check magic of Gzip header
 *
 * @param[in] src - Gzip compressed data
 *
 * @return 1 on success,  0 is not Gzip data.
 */
int ksceGzipIsValid(const void *src);

/**
 * @brief Get filename etc. in Gzip data
 *
 * @param[in] src - Gzip compressed data
 * @param[out] extra - Get information on extra-field
 * @param[out] name - Get filename information
 * @param[out] comment - Get comment information
 * @param[out] crc - Get CRC16 information
 * @param[out] data - Get compressed data start address
 *
 * @return 0 on success, < 0 on error.
 */
int ksceGzipGetInfo(const void *src, const void **extra, const char **name, const char **comment, unsigned short *crc, const void **data);

/**
 * @brief Get filename string address
 *
 * @param[in] src - Gzip compressed data
 *
 * @return string address on success, NULL on error.
 */
const char *ksceGzipGetName(const void *src);

/**
 * @brief Get comment string address
 *
 * @param[in] src - Gzip compressed data
 *
 * @return string address on success, NULL on error.
 */
const char *ksceGzipGetComment(const void *src);

/**
 * @brief Get compressed data start address
 *
 * @param[in] src - Gzip compressed data
 *
 * @return compressed data address on success, NULL on error.
 */
const void *ksceGzipGetCompressedData(const void *src);

/**
 * @brief Get filename etc. in Zlib data
 *
 * @param[in] src - Zlib compressed data
 * @param[out] cmf - Get CMF (Compression Method and flags)
 * @param[out] flg - Get FLG (FLaGs)
 * @param[out] dictid - Get DictId
 * @param[out] data - Get compressed data start address
 *
 * @return 0 on success, < 0 on error.
 */
int ksceZlibGetInfo(const void *src, unsigned char *cmf, unsigned char *flg, unsigned int *dictid, const void **data);

/**
 * @brief Get compressed data start address
 *
 * @param[in] src - Gzip compressed data
 *
 * @return compressed data address on success, NULL on error.
 */
const void *ksceZlibGetCompressedData(const void *src);

/**
 * @param[out] dst - dst buf
 * @param[in] dst_size - dst buf size
 * @param[in] src - Zlib compressed data
 * @param[out] adler32 - adler32 when decompressed
 *
 * @return decompressed size on success, < 0 on error.
 */
int ksceZlibDecompress(void *dst, uint32_t dst_size, const void *src, uint32_t *adler32);

/**
 * @param[out] dst - dst buf
 * @param[in] dst_size - dst buf size
 * @param[in] src - Deflate compressed data
 * @param[out] next - next data
 *
 * @return decompressed size on success, < 0 on error.
 */
int ksceDeflateDecompress(void *dst, uint32_t dst_size, const void *src, const void **next);
int ksceDeflateDecompressPartial(void *dst, unsigned int dst_size, const void *src, const void **next, SceDeflatePartialInputParam *cbInfo);

/**
 * @param[out] ctx - out key data, etc...
 * @param[in] blocksize - 128 or 192 or 256
 * @param[in] keysize - 128 or 192 or 256
 * @param[in] key - key data
 *
 * @return 0 on success, < 0 on error.
 */
int ksceAesInit1(SceAesContext *ctx, int blocksize, int keysize, const void *key);
int ksceAesInit2(SceAesContext *ctx, int blocksize, int keysize, const void *key);
int ksceAesInit3(SceAesContext *ctx, int blocksize, int keysize, const void *key);

int ksceAesDecrypt1(SceAesContext *ctx, const void *src, void *dst);
int ksceAesDecrypt2(SceAesContext *ctx, const void *src, void *dst);

int ksceAesEncrypt1(SceAesContext *ctx, const void *src, void *dst);
int ksceAesEncrypt2(SceAesContext *ctx, const void *src, void *dst);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_UTILS_H_ */
