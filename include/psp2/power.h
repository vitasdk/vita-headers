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
	/** indicates the unit is using battery as power source */
	SCE_POWER_CB_BATTERY_MODE          = 0x00000000,
	/** indicates the battery is in low state */
	SCE_POWER_CB_LOW_BATTERY           = 0x00000100,
	/** indicates the unit is using an AC outlet as power source */
	SCE_POWER_CB_AC_POWER_MODE         = 0x00001000,
	/** indicates the unit has been shutdown **/
	SCE_POWER_CB_SHUTDOWN              = 0x00010000,
	/** indicates the application resumed after being put in suspend from a LiveArea event **/
	SCE_POWER_CB_RESUME_LIVEAREA       = 0x00200000,
	/** indicates the unit entered suspend mode **/
	SCE_POWER_CB_SUSPENDING            = 0x00400000,
	/** indicates the unit resumed from suspend mode **/
	SCE_POWER_CB_RESUMING              = 0x00800000,
	/** indicates the system is taking a screenshot **/
	SCE_POWER_CB_SCREENSHOT_TRIGGER    = 0x04000000,
	/** indicates the system shown the Quick Menu screen **/
	SCE_POWER_CB_QUICK_MENU_TRIGGER    = 0x10000000,
	/** indicates the PS button was pushed **/
	SCE_POWER_CB_PS_BUTTON_PRESS       = 0x20000000,
	/** indicates the system shown the shutdown screen **/
	SCE_POWER_CB_SHUTDOWN_MENU_TRIGGER = 0x40000000,
	/** indicates the system shown the unlock screen **/
	SCE_POWER_CB_UNLOCK_MENU_TRIGGER   = 0x80000000,
} ScePowerCallbackType;

/* GPU, WLAN/COM configuration setting */
typedef enum ScePowerConfigurationMode {
	SCE_POWER_CONFIGURATION_MODE_A   = 0x00000080U, /* GPU clock normal, WLAN/COM enabled */
	SCE_POWER_CONFIGURATION_MODE_B   = 0x00000800U, /* GPU clock high, WLAN/COM disabled */
	SCE_POWER_CONFIGURATION_MODE_C   = 0x00010880U, /* GPU clock high, WLAN/COM enabled (drains battery faster) */
} ScePowerConfigurationMode;

/** Callback function prototype */
typedef void (*ScePowerCallback)(int notifyId, int notifyCount, int powerInfo, void* userData);

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
 * @return Battery life time in minutes
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
