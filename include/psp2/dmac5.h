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

/*
 * Basic
 */
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x0            (0x0)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x1            (0x1)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x2            (0x2)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x4            (0x4)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x8            (0x8)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x10           (0x10)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x20           (0x20)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x100          (0x100)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x200          (0x200)
#define SCE_SBL_DMAC5_COMMAND_BASIC_0x300          (0x300)

/*
 * stdc
 */
#define SCE_SBL_DMAC5_COMMAND_MEMCPY               (SCE_SBL_DMAC5_COMMAND_BASIC_0x0)
#define SCE_SBL_DMAC5_COMMAND_MEMSET               (SCE_SBL_DMAC5_COMMAND_BASIC_0x4 | SCE_SBL_DMAC5_COMMAND_BASIC_0x8)

/*
 * Random number generator
 */
#define SCE_SBL_DMAC5_COMMAND_RNG                  (SCE_SBL_DMAC5_COMMAND_BASIC_0x4)

/*
 * Secure hash algorithm
 */
#define SCE_SBL_DMAC5_COMMAND_SHA                  (SCE_SBL_DMAC5_COMMAND_BASIC_0x1 | SCE_SBL_DMAC5_COMMAND_BASIC_0x2)
#define SCE_SBL_DMAC5_COMMAND_HASH_BIT_SIZE_SHA1   (SCE_SBL_DMAC5_COMMAND_BASIC_0x0  & 0x18)
#define SCE_SBL_DMAC5_COMMAND_HASH_BIT_SIZE_SHA224 (SCE_SBL_DMAC5_COMMAND_BASIC_0x8  & 0x18)
#define SCE_SBL_DMAC5_COMMAND_HASH_BIT_SIZE_SHA256 (SCE_SBL_DMAC5_COMMAND_BASIC_0x10 & 0x18)
#define SCE_SBL_DMAC5_COMMAND_SHA1                 (SCE_SBL_DMAC5_COMMAND_SHA | SCE_SBL_DMAC5_COMMAND_HASH_BIT_SIZE_SHA1)
#define SCE_SBL_DMAC5_COMMAND_SHA224               (SCE_SBL_DMAC5_COMMAND_SHA | SCE_SBL_DMAC5_COMMAND_HASH_BIT_SIZE_SHA224)
#define SCE_SBL_DMAC5_COMMAND_SHA256               (SCE_SBL_DMAC5_COMMAND_SHA | SCE_SBL_DMAC5_COMMAND_HASH_BIT_SIZE_SHA256)

#define SCE_SBL_DMAC5_COMMAND_HMAC_SHA             (SCE_SBL_DMAC5_COMMAND_BASIC_0x20)
#define SCE_SBL_DMAC5_COMMAND_HMAC_SHA1            (SCE_SBL_DMAC5_COMMAND_HMAC_SHA | SCE_SBL_DMAC5_COMMAND_SHA1)
#define SCE_SBL_DMAC5_COMMAND_HMAC_SHA224          (SCE_SBL_DMAC5_COMMAND_HMAC_SHA | SCE_SBL_DMAC5_COMMAND_SHA224)
#define SCE_SBL_DMAC5_COMMAND_HMAC_SHA256          (SCE_SBL_DMAC5_COMMAND_HMAC_SHA | SCE_SBL_DMAC5_COMMAND_SHA256)

/*
 * Aes
 */
#define SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_128     (SCE_SBL_DMAC5_COMMAND_BASIC_0x100 & 0x300)
#define SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_192     (SCE_SBL_DMAC5_COMMAND_BASIC_0x200 & 0x300)
#define SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_256     (SCE_SBL_DMAC5_COMMAND_BASIC_0x300 & 0x300)

#define SCE_SBL_DMAC5_COMMAND_AES_ECB_ENC          (SCE_SBL_DMAC5_COMMAND_BASIC_0x1)
#define SCE_SBL_DMAC5_COMMAND_AES_ECB_DEC          (SCE_SBL_DMAC5_COMMAND_BASIC_0x2)
#define SCE_SBL_DMAC5_COMMAND_AES_128_ECB_ENC      (SCE_SBL_DMAC5_COMMAND_AES_ECB_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_128)
#define SCE_SBL_DMAC5_COMMAND_AES_128_ECB_DEC      (SCE_SBL_DMAC5_COMMAND_AES_ECB_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_128)
#define SCE_SBL_DMAC5_COMMAND_AES_192_ECB_ENC      (SCE_SBL_DMAC5_COMMAND_AES_ECB_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_192)
#define SCE_SBL_DMAC5_COMMAND_AES_192_ECB_DEC      (SCE_SBL_DMAC5_COMMAND_AES_ECB_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_192)
#define SCE_SBL_DMAC5_COMMAND_AES_256_ECB_ENC      (SCE_SBL_DMAC5_COMMAND_AES_ECB_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_256)
#define SCE_SBL_DMAC5_COMMAND_AES_256_ECB_DEC      (SCE_SBL_DMAC5_COMMAND_AES_ECB_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_256)

#define SCE_SBL_DMAC5_COMMAND_AES_CBC              (SCE_SBL_DMAC5_COMMAND_BASIC_0x8)
#define SCE_SBL_DMAC5_COMMAND_AES_CBC_ENC          (SCE_SBL_DMAC5_COMMAND_AES_CBC | SCE_SBL_DMAC5_COMMAND_AES_ECB_ENC)
#define SCE_SBL_DMAC5_COMMAND_AES_CBC_DEC          (SCE_SBL_DMAC5_COMMAND_AES_CBC | SCE_SBL_DMAC5_COMMAND_AES_ECB_DEC)
#define SCE_SBL_DMAC5_COMMAND_AES_128_CBC_ENC      (SCE_SBL_DMAC5_COMMAND_AES_CBC_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_128)
#define SCE_SBL_DMAC5_COMMAND_AES_128_CBC_DEC      (SCE_SBL_DMAC5_COMMAND_AES_CBC_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_128)
#define SCE_SBL_DMAC5_COMMAND_AES_192_CBC_ENC      (SCE_SBL_DMAC5_COMMAND_AES_CBC_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_192)
#define SCE_SBL_DMAC5_COMMAND_AES_192_CBC_DEC      (SCE_SBL_DMAC5_COMMAND_AES_CBC_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_192)
#define SCE_SBL_DMAC5_COMMAND_AES_256_CBC_ENC      (SCE_SBL_DMAC5_COMMAND_AES_CBC_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_256)
#define SCE_SBL_DMAC5_COMMAND_AES_256_CBC_DEC      (SCE_SBL_DMAC5_COMMAND_AES_CBC_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_256)

#define SCE_SBL_DMAC5_COMMAND_AES_CTR              (SCE_SBL_DMAC5_COMMAND_BASIC_0x10)
#define SCE_SBL_DMAC5_COMMAND_AES_CTR_ENC          (SCE_SBL_DMAC5_COMMAND_AES_CTR | SCE_SBL_DMAC5_COMMAND_AES_ECB_ENC)
#define SCE_SBL_DMAC5_COMMAND_AES_CTR_DEC          (SCE_SBL_DMAC5_COMMAND_AES_CTR | SCE_SBL_DMAC5_COMMAND_AES_ECB_DEC)
#define SCE_SBL_DMAC5_COMMAND_AES_128_CTR_ENC      (SCE_SBL_DMAC5_COMMAND_AES_CTR_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_128)
#define SCE_SBL_DMAC5_COMMAND_AES_128_CTR_DEC      (SCE_SBL_DMAC5_COMMAND_AES_CTR_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_128)
#define SCE_SBL_DMAC5_COMMAND_AES_192_CTR_ENC      (SCE_SBL_DMAC5_COMMAND_AES_CTR_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_192)
#define SCE_SBL_DMAC5_COMMAND_AES_192_CTR_DEC      (SCE_SBL_DMAC5_COMMAND_AES_CTR_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_192)
#define SCE_SBL_DMAC5_COMMAND_AES_256_CTR_ENC      (SCE_SBL_DMAC5_COMMAND_AES_CTR_ENC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_256)
#define SCE_SBL_DMAC5_COMMAND_AES_256_CTR_DEC      (SCE_SBL_DMAC5_COMMAND_AES_CTR_DEC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_256)

#define SCE_SBL_DMAC5_COMMAND_AES_CMAC             (SCE_SBL_DMAC5_COMMAND_BASIC_0x1 | SCE_SBL_DMAC5_COMMAND_BASIC_0x2 | SCE_SBL_DMAC5_COMMAND_BASIC_0x8 | SCE_SBL_DMAC5_COMMAND_BASIC_0x10 | SCE_SBL_DMAC5_COMMAND_BASIC_0x20)
#define SCE_SBL_DMAC5_COMMAND_AES_128_CMAC         (SCE_SBL_DMAC5_COMMAND_AES_CMAC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_128)
#define SCE_SBL_DMAC5_COMMAND_AES_192_CMAC         (SCE_SBL_DMAC5_COMMAND_AES_CMAC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_192)
#define SCE_SBL_DMAC5_COMMAND_AES_256_CMAC         (SCE_SBL_DMAC5_COMMAND_AES_CMAC | SCE_SBL_DMAC5_COMMAND_AES_BIT_SIZE_256)

typedef struct SceDmac5EncdecParam {
	const void *src;
	void       *dst;
	SceSize     size;
	const void *key;
	SceSize     key_bit_size;
	void       *iv;
} SceDmac5EncdecParam;

/**
 * @brief Execute DMAC5 command
 *
 * @param[inout] param   - The encdec param.
 * @param[in]    command - The dmac5 command. See:SCE_SBL_DMAC5_COMMAND_*
 *
 * @return 0 on success, else < 0.
 */
int sceSblDmac5EncDec(SceDmac5EncdecParam *param, int command);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_DMAC5_H_ */
