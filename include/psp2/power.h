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
SceInt32 scePowerRegisterCallback(SceUID cbid);

/**
 * Unregister a callback
 *
 * @param cbid - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 scePowerUnregisterCallback(SceUID cbid);

/**
 * Returns battery charging status
 *
 * @return SCE_TRUE if under charge, SCE_FALSE otherwise
 */
SceInt32 scePowerIsBatteryCharging(void);

/**
 * Returns battery life percentage
 *
 * @return Battery life percentage
 */
SceInt32 scePowerGetBatteryLifePercent(void);

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
SceInt32 scePowerSetConfigurationMode(SceUInt32 conf);

/**
 * Check if a suspend is required
 *
 * @return SCE_TRUE if suspend is required, SCE_FALSE otherwise
 */
SceInt32 scePowerIsSuspendRequired(void);

/**
 * Check if AC is plugged in
 *
 * @return SCE_TRUE if plugged in, SCE_FALSE otherwise
 */
SceInt32 scePowerIsPowerOnline(void);

/**
 * Returns battery life time
 *
 * @return Battery life time in minutes
 */
SceInt32 scePowerGetBatteryLifeTime(void);

/**
 * Returns battery remaining capacity
 *
 * @return battery remaining capacity in mAh (milliampere hour)
 */
SceInt32 scePowerGetBatteryRemainCapacity(void);

/**
 * Returns battery state
 *
 * @return SCE_TRUE if battery is low, SCE_FALSE otherwise
 */
SceInt32 scePowerIsLowBattery(void);

/**
 * Returns battery full capacity
 *
 * @return battery full capacity in mAh (milliampere hour)
 */
SceInt32 scePowerGetBatteryFullCapacity(void);

/**
 * Returns battery temperature
 *
 * @return temperature in degrees celcius * 100
 */
SceInt32 scePowerGetBatteryTemp(void);

/**
 * Returns battery voltage
 *
 * @return battery voltage in mV (millivolts)
 */
SceInt32 scePowerGetBatteryVolt(void);

/**
 * Returns battery state of health
 *
 * @return battery state of health percent
 */
SceInt32 scePowerGetBatterySOH(void);

/**
 * Returns battery cycle count
 *
 * @return battery cycle count
 */
SceInt32 scePowerGetBatteryCycleCount(void);

/**
 * Returns CPU clock frequency
 *
 * @return CPU clock frequency in Mhz
 */
SceInt32 scePowerGetArmClockFrequency(void);

/**
 * Returns BUS clock frequency
 *
 * @return BUS clock frequency in Mhz
 */
SceInt32 scePowerGetBusClockFrequency(void);

/**
 * Returns GPU clock frequency
 *
 * @return GPU clock frequency in Mhz
 */
SceInt32 scePowerGetGpuClockFrequency(SceInt32 *corefreq, SceInt32 *mpfreq);

/**
 * Returns GPU crossbar clock frequency
 *
 * @return GPU crossbar clock frequency in Mhz
 */
SceInt32 scePowerGetGpuXbarClockFrequency(void);

/**
 * Requests PS Vita to do a cold reset
 *
 * @return always 0
 */
SceInt32 scePowerRequestColdReset(void);

/**
 * Requests PS Vita to go into standby
 *
 * @return always 0
 */
SceInt32 scePowerRequestStandby(void);

/**
 * Requests PS Vita to suspend
 *
 * @return always 0
 */
SceInt32 scePowerRequestSuspend(void);

/**
 * Request display on
 *
 * @return always 0
 */
SceInt32 scePowerRequestDisplayOn(void);

/**
 * Request display off
 *
 * @return always 0
 */
SceInt32 scePowerRequestDisplayOff(void);

/**
 * Sets CPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 scePowerSetArmClockFrequency(SceInt32 freq);

/**
 * Sets BUS clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 scePowerSetBusClockFrequency(SceInt32 freq);

/**
 * Sets GPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 scePowerSetGpuClockFrequency(SceInt32 corefreq, SceInt32 mpfreq);

/**
 * Sets GPU crossbar clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 scePowerSetGpuXbarClockFrequency(SceInt32 freq);

/**
 * Sets wireless features usage
 *
 * @param enabled - SCE_TRUE to enable, SCE_FALSE to disable
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 scePowerSetUsingWireless(SceInt32 usewireless);

/**
 * Gets wireless features usage
 *
 * @return SCE_TRUE if enabled, SCE_FALSE otherwise
 */
SceInt32 scePowerGetUsingWireless(void);

SceInt32 scePowerBatteryUpdateInfo(void);
SceInt32 scePowerCancelRequest(void);
SceInt32 scePowerGetBatteryChargingStatus(void);
SceInt32 scePowerGetBatteryElec(SceInt32 *pElec);
SceInt32 scePowerGetCaseTemp(void);
SceInt32 scePowerIsBatteryExist(void);
SceInt32 scePowerIsRequest(void);
SceInt32 scePowerSetIdleTimerCount(SceUInt64 ullCount);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_POWER_H_ */
