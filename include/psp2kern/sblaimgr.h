/**
 * \kernelgroup{SceSblAIMgr}
 * \usage{psp2kern/sblaimgr.h,SceSblAIMgrForDriver_stub}
 */

#ifndef _PSP2_KERNEL_SBLACMGR_H_
#define _PSP2_KERNEL_SBLACMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceDeviceTargetId {
  SCE_TARGET_ID_NONE     = 0x00000000,
  SCE_TARGET_ID_TEST     = 0x100, // Internal Test Unit
  SCE_TARGET_ID_TOOL     = 0x101, // Development kit
  SCE_TARGET_ID_DEX      = 0x102, // Testing kit
  SCE_TARGET_ID_CEX_J1   = 0x103, // Japan
  SCE_TARGET_ID_CEX_UC2  = 0x104, // united ctates
  SCE_TARGET_ID_CEX_CEL  = 0x105,
  SCE_TARGET_ID_CEX_KR2  = 0x106,
  SCE_TARGET_ID_CEX_CEK  = 0x107,
  SCE_TARGET_ID_CEX_MX2  = 0x108,
  SCE_TARGET_ID_CEX_AU3  = 0x109,
  SCE_TARGET_ID_CEX_E12  = 0x10A,
  SCE_TARGET_ID_CEX_TW1  = 0x10B, // taiwan
  SCE_TARGET_ID_CEX_RU3  = 0x10C,
  SCE_TARGET_ID_CEX_CN9  = 0x10D,
  SCE_TARGET_ID_CEX_HK5  = 0x10E,
  SCE_TARGET_ID_CEX_RSV1 = 0x10F,
  SCE_TARGET_ID_CEX_RSV2 = 0x110,
  SCE_TARGET_ID_CEX_RSV3 = 0x111
} SceDeviceTargetId;

/**
 * @brief Get service/manufacturing information(factory fw).
 *
 * @param[out] info - The info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAimgrGetSMI(SceUInt32 *info);

/**
 * @brief Get target id.
 *
 * @return SceDeviceTargetId
 */
int ksceSblAimgrGetTargetId(void);

/**
 * @brief Get system type state.
 *
 * @return If target id is TEST, 1. else 0.
 */
int ksceSblAimgrIsTest(void);

/**
 * @brief Get system type state.
 *
 * @return If target id is TOOL, 1. else 0.
 */
int ksceSblAimgrIsTool(void);

/**
 * @brief Get system type state.
 *
 * @return If target id is DEX, 1. else 0.
 */
int ksceSblAimgrIsDEX(void);

/**
 * @brief Get system type state.
 *
 * @return If target id is CEX, 1. else 0.
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

#endif /* _PSP2_KERNEL_SBLAIMGR_H_ */

