/**
 * \kernelgroup{SceSblAIMgr}
 * \usage{psp2kern/sblaimgr.h,SceSblAIMgrForDriver_stub}
 */

#ifndef _PSP2KERN_SBLAIMGR_H_
#define _PSP2KERN_SBLAIMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceProductCode {
  SCE_PRODUCT_CODE_NONE     = 0x00000000,
  SCE_PRODUCT_CODE_TEST     = 0x100, // Internal Test Unit
  SCE_PRODUCT_CODE_TOOL     = 0x101, // Development kit
  SCE_PRODUCT_CODE_DEX      = 0x102, // Testing kit
  SCE_PRODUCT_CODE_CEX_J1   = 0x103, // Japan
  SCE_PRODUCT_CODE_CEX_UC2  = 0x104, // united ctates
  SCE_PRODUCT_CODE_CEX_CEL  = 0x105,
  SCE_PRODUCT_CODE_CEX_KR2  = 0x106,
  SCE_PRODUCT_CODE_CEX_CEK  = 0x107,
  SCE_PRODUCT_CODE_CEX_MX2  = 0x108,
  SCE_PRODUCT_CODE_CEX_AU3  = 0x109,
  SCE_PRODUCT_CODE_CEX_E12  = 0x10A,
  SCE_PRODUCT_CODE_CEX_TW1  = 0x10B, // taiwan
  SCE_PRODUCT_CODE_CEX_RU3  = 0x10C,
  SCE_PRODUCT_CODE_CEX_CN9  = 0x10D,
  SCE_PRODUCT_CODE_CEX_HK5  = 0x10E,
  SCE_PRODUCT_CODE_CEX_RSV1 = 0x10F,
  SCE_PRODUCT_CODE_CEX_RSV2 = 0x110,
  SCE_PRODUCT_CODE_CEX_RSV3 = 0x111
} SceProductCode;

/**
 * @brief Get service/manufacturing information (factory/minimum firmware).
 *
 * @param[out] info - The info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAimgrGetSMI(SceUInt32 *info);

/**
 * @brief Get product code.
 *
 * @return see:SceProductCode.
 */
int ksceSblAimgrGetProductCode(void);

/* Macro for backward compatibility */
#define ksceSblAimgrGetTargetId() ksceSblAimgrGetProductCode()

/**
 * @brief Get product sub code.
 *
 * @return product sub code value.
 */
int ksceSblAimgrGetProductSubCode(void);

/**
 * @brief Get system type state.
 *
 * @return If product code is TEST, 1. else 0.
 */
int ksceSblAimgrIsTest(void);

/**
 * @brief Get system type state.
 *
 * @return If product code is TOOL, 1. else 0.
 */
int ksceSblAimgrIsTool(void);

/**
 * @brief Get system type state.
 *
 * @return If product code is DEX, 1. else 0.
 */
int ksceSblAimgrIsDEX(void);

/**
 * @brief Get system type state.
 *
 * @return If product code is CEX, 1. else 0.
 */
int ksceSblAimgrIsCEX(void);

/**
 * @brief Get system type state.
 *
 * @return If device is vita, 1. else 0.
 */
int ksceSblAimgrIsVITA(void);

/**
 * @brief Get system type state.
 *
 * @return If device is dolce, or PSTV emu enabled, 1. else 0.
 */
int ksceSblAimgrIsDolce(void);

/**
 * @brief Get system type state.
 *
 * @return If device is vita, 1. else 0.
 */
int ksceSblAimgrIsGenuineVITA(void);

/**
 * @brief Get system type state.
 *
 * @return If device is dolce, 1. else 0.
 */
int ksceSblAimgrIsGenuineDolce(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_SBLAIMGR_H_ */
