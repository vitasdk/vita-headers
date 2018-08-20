/**
 * \usergroup{ScePower}
 * \usage{psp2/power.h,ScePower_stub}
 */


#ifndef _PSP2_POWER_H_
#define _PSP2_POWER_H_

#include <psp2/types.h>


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
	
typedef enum ScePowerCallbackType {
	/** indicates the power button was pushed, putting the unit into suspend mode */
	SCE_POWER_CB_POWER_SWITCH     = 0x80000000,
	/** ? screen on after off ? **/
	SCE_POWER_CB_UNK_1            = 0x00600000,
	/** ? screen off ? **/
	SCE_POWER_CB_UNK_2            = 0x00400000,
	/** indicates the unit has finish resuming from suspend mode */
	SCE_POWER_CB_RESUME_COMPLETE  = 0x00040000,
	/** indicates the unit is resuming from suspend mode */
	SCE_POWER_CB_RESUMING         = 0x00020000,
	/** indicates the unit is suspending, seems to occur due to inactivity */
	SCE_POWER_CB_SUSPENDING       = 0x00010000,
	/** indicates the unit is plugged into an AC outlet */
	SCE_POWER_CB_AC_POWER         = 0x00001000,
	/** indicates the battery is in low state */
	SCE_POWER_CB_LOWBATTERY       = 0x00000100,
	/** indicates there is a battery present in the unit */
	SCE_POWER_CB_BATTERY_EXIST    = 0x00000080
} ScePowerCallbackType;

/* GPU, WLAN/COM configuration setting */
typedef enum ScePowerConfigurationMode {
	SCE_POWER_CONFIGURATION_MODE_A   = 0x00000080U, /* GPU clock normal, WLAN/COM enabled */
	SCE_POWER_CONFIGURATION_MODE_B   = 0x00000800U, /* GPU clock high, WLAN/COM disabled */
	SCE_POWER_CONFIGURATION_MODE_C   = 0x00010880U, /* GPU clock high, WLAN/COM enabled (drains battery faster) */
} ScePowerConfigurationMode;

/** Callback function prototype */
typedef void (*ScePowerCallback)(int notifyId, int notifyCount, int powerInfo);

/**
 * Registers a ScePower Callback
 *
 * @param cbid - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int scePowerRegisterCallback(SceUID cbid);

/**
 * Unregister a callback
 *
 * @param cbid - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int scePowerUnregisterCallback(SceUID cbid);

/**
 * Returns battery charging status
 *
 * @return SCE_TRUE if under charge, SCE_FALSE otherwise
 */
SceBool scePowerIsBatteryCharging(void);

/**
 * Returns battery life percentage
 *
 * @return Battery life percentage
 */
int scePowerGetBatteryLifePercent(void);

/**
 * Set power configuration mode between:
 *
 * Mode A - This is the normal mode at process start-up. The clock frequency of the GPU core is the "normal" clock frequency. The WLAN/COM can be used.
 * Mode B - This mode accelerates the GPU clock frequency. The clock frequency of the GPU core is the "high" clock frequency. The WLAN/COM cannot be used.
 * Mode C - This mode accelerates the GPU clock frequency, and also uses the WLAN/COM. The clock frequency of the GPU core is the "high" clock frequency, and use of the WLAN/COM is possible. The screen (touchscreen) brightness, however, is limited. Also, camera cannot be used.
 *
 * @param conf One of ::ScePowerConfigurationMode
 *
 * @return 0 on success
 */
int scePowerSetConfigurationMode(int conf);

/**
 * Check if a suspend is required
 *
 * @return SCE_TRUE if suspend is required, SCE_FALSE otherwise
 */
SceBool scePowerIsSuspendRequired(void);

/**
 * Check if AC is plugged in
 *
 * @return SCE_TRUE if plugged in, SCE_FALSE otherwise
 */
SceBool scePowerIsPowerOnline(void);

/**
 * Returns battery life time
 *
 * @return Battery life time in seconds
 */
int scePowerGetBatteryLifeTime(void);

/**
 * Returns battery remaining capacity
 *
 * @return battery remaining capacity in mAh (milliampere hour)
 */
int scePowerGetBatteryRemainCapacity(void);

/**
 * Returns battery state
 *
 * @return SCE_TRUE if battery is low, SCE_FALSE otherwise
 */
SceBool scePowerIsLowBattery(void);

/**
 * Returns battery full capacity
 *
 * @return battery full capacity in mAh (milliampere hour)
 */
int scePowerGetBatteryFullCapacity(void);

/**
 * Returns battery temperature
 *
 * @return temperature in degrees celcius * 100
 */
int scePowerGetBatteryTemp(void);

/**
 * Returns battery voltage
 *
 * @return battery voltage in mV (millivolts)
 */
int scePowerGetBatteryVolt(void);

/**
 * Returns battery state of health
 *
 * @return battery state of health percent
 */
int scePowerGetBatterySOH(void);

/**
 * Returns battery cycle count
 *
 * @return battery cycle count
 */
int scePowerGetBatteryCycleCount(void);

/**
 * Returns CPU clock frequency
 *
 * @return CPU clock frequency in Mhz
 */
int scePowerGetArmClockFrequency(void);

/**
 * Returns BUS clock frequency
 *
 * @return BUS clock frequency in Mhz
 */
int scePowerGetBusClockFrequency(void);

/**
 * Returns GPU clock frequency
 *
 * @return GPU clock frequency in Mhz
 */
int scePowerGetGpuClockFrequency(void);

/**
 * Returns GPU crossbar clock frequency
 *
 * @return GPU crossbar clock frequency in Mhz
 */
int scePowerGetGpuXbarClockFrequency(void);

/**
 * Requests PS Vita to do a cold reset
 *
 * @return always 0
 */
int scePowerRequestColdReset(void);

/**
 * Requests PS Vita to go into standby
 *
 * @return always 0
 */
int scePowerRequestStandby(void);

/**
 * Requests PS Vita to suspend
 *
 * @return always 0
 */
int scePowerRequestSuspend(void);

/**
 * Request display on
 *
 * @return always 0
 */
int scePowerRequestDisplayOn(void);
	
/**
 * Request display off
 *
 * @return always 0
 */
int scePowerRequestDisplayOff(void);

/**
 * Sets CPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetArmClockFrequency(int freq);

/**
 * Sets BUS clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetBusClockFrequency(int freq);

/**
 * Sets GPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetGpuClockFrequency(int freq);

/**
 * Sets GPU crossbar clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetGpuXbarClockFrequency(int freq);

/**
 * Sets wireless features usage
 *
 * @param enabled - SCE_TRUE to enable, SCE_FALSE to disable
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetUsingWireless(SceBool enabled);

/**
 * Gets wireless features usage
 *
 * @return SCE_TRUE if enabled, SCE_FALSE otherwise
 */
int scePowerGetUsingWireless(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_POWER_H_ */
