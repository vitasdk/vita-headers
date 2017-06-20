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

typedef enum ScePowerCallbackType {
	/** indicates the unit is suspending, seems to occur due to inactivity */
	SCE_POWER_CB_SUSPENDING       = 0x00010000,
	/** indicates the unit is resuming from suspend mode */
	SCE_POWER_CB_RESUMING         = 0x00020000,
	/** indicates the unit has finish resuming from suspend mode */
	SCE_POWER_CB_RESUME_COMPLETE  = 0x00040000
} ScePowerCallbackType;

/* Callbacks */

/** Callback function prototype */
typedef void (*ScePowerCallback)(int notifyId, int notifyCount, int powerInfo);

/* Prototypes */

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
 * Set configuration mode ?
 *
 * @param mode - The mode to set
 *
 * @return ?
 */
int scePowerSetConfigurationMode(int mode);

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_POWER_H_ */
