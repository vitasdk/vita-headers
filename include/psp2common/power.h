/**
 * \kernelgroup{ScePower}
 * \usage{psp2common/power.h}
 */

#ifndef _PSP2COMMON_POWER_H_
#define _PSP2COMMON_POWER_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ScePowerErrorCode {
	SCE_POWER_ERROR_INVALID_VALUE           = 0x802B0000,
	SCE_POWER_ERROR_ALREADY_REGISTERED      = 0x802B0001,
	SCE_POWER_ERROR_CALLBACK_NOT_REGISTERED = 0x802B0002,
	SCE_POWER_ERROR_CANT_SUSPEND            = 0x802B0003,
	SCE_POWER_ERROR_NO_BATTERY              = 0x802B0100,
	SCE_POWER_ERROR_DETECTING               = 0x802B0101
} ScePowerErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, ScePowerErrorCode);

typedef enum ScePowerCallbackType {
	SCE_POWER_CB_AFTER_SYSTEM_RESUME   = 0x00000080, /* TODO: confirm */
	SCE_POWER_CB_BATTERY_ONLINE        = 0x00000100,
	SCE_POWER_CB_THERMAL_SUSPEND       = 0x00000200, /* TODO: confirm */
	SCE_POWER_CB_LOW_BATTERY_SUSPEND   = 0x00000400, /* TODO: confirm */
	SCE_POWER_CB_LOW_BATTERY           = 0x00000800,
	SCE_POWER_CB_POWER_ONLINE          = 0x00001000,
	SCE_POWER_CB_SYSTEM_SUSPEND        = 0x00010000,
	SCE_POWER_CB_SYSTEM_RESUMING       = 0x00020000,
	SCE_POWER_CB_SYSTEM_RESUME         = 0x00040000,
	SCE_POWER_CB_UNK_0x100000          = 0x00100000, /* Related to proc_event::display_switch */
	SCE_POWER_CB_APP_RESUME            = 0x00200000,
	SCE_POWER_CB_APP_SUSPEND           = 0x00400000,
	SCE_POWER_CB_APP_RESUMING          = 0x00800000, /* TODO: confirm */
	SCE_POWER_CB_BUTTON_PS_START_PRESS = 0x04000000,
	SCE_POWER_CB_BUTTON_PS_POWER_PRESS = 0x08000000,
	SCE_POWER_CB_BUTTON_PS_HOLD        = 0x10000000,
	SCE_POWER_CB_BUTTON_PS_PRESS       = 0x20000000,
	SCE_POWER_CB_BUTTON_POWER_HOLD     = 0x40000000,
	SCE_POWER_CB_BUTTON_POWER_PRESS    = 0x80000000,
	SCE_POWER_CB_VALID_MASK_KERNEL     = 0xFCF71F80,
	SCE_POWER_CB_VALID_MASK_SYSTEM     = 0xFCF71F80,
	SCE_POWER_CB_VALID_MASK_NON_SYSTEM = 0x00361180
} ScePowerCallbackType;
VITASDK_BUILD_ASSERT_EQ(4, ScePowerCallbackType);

/* GPU, WLAN/COM configuration setting */
typedef enum ScePowerConfigurationMode {
	SCE_POWER_CONFIGURATION_MODE_A = 0x00000080U, /* GPU clock normal, WLAN/COM enabled */
	SCE_POWER_CONFIGURATION_MODE_B = 0x00000800U, /* GPU clock high, WLAN/COM disabled */
	SCE_POWER_CONFIGURATION_MODE_C = 0x00010880U, /* GPU clock high, WLAN/COM enabled (drains battery faster) */
	__SCE_POWER_CONFIGURATION_MODE = 0xFFFFFFFF
} ScePowerConfigurationMode;
VITASDK_BUILD_ASSERT_EQ(4, ScePowerConfigurationMode);

/* Callbacks */

/** Callback function prototype */
typedef void (*ScePowerCallback)(int notifyId, int notifyCount, int powerInfo, void* userData);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_POWER_H_ */
