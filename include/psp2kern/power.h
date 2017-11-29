/**
 * \kernelgroup{ScePower}
 * \usage{psp2kern/power.h,ScePowerForDriver_stub}
 */

#ifndef _PSP2_KERN_POWER_H_
#define _PSP2_KERN_POWER_H_

#include <psp2kern/types.h>

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
int kscePowerRegisterCallback(SceUID cbid);

/**
 * Unregister a callback
 *
 * @param cbid - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int kscePowerUnregisterCallback(SceUID cbid);

/**
 * Returns battery charging status
 *
 * @return SCE_TRUE if under charge, SCE_FALSE otherwise
 */
SceBool kscePowerIsBatteryCharging(void);

/**
 * Returns battery life percentage
 *
 * @return Battery life percentage
 */
int kscePowerGetBatteryLifePercent(void);

/**
 * Check if a suspend is required
 *
 * @return SCE_TRUE if suspend is required, SCE_FALSE otherwise
 */
SceBool kscePowerIsSuspendRequired(void);

/**
 * Check if AC is plugged in
 *
 * @return SCE_TRUE if plugged in, SCE_FALSE otherwise
 */
SceBool kscePowerIsPowerOnline(void);

/**
 * Returns battery life time
 *
 * @return Battery life time in seconds
 */
int kscePowerGetBatteryLifeTime(void);

/**
 * Returns battery remaining capacity
 *
 * @return battery remaining capacity in mAh (milliampere hour)
 */
int kscePowerGetBatteryRemainCapacity(void);

/**
 * Returns battery state
 *
 * @return SCE_TRUE if battery is low, SCE_FALSE otherwise
 */
SceBool kscePowerIsLowBattery(void);

/**
 * Returns battery full capacity
 *
 * @return battery full capacity in mAh (milliampere hour)
 */
int kscePowerGetBatteryFullCapacity(void);

/**
 * Returns battery temperature
 *
 * @return temperature in degrees celcius * 100
 */
int kscePowerGetBatteryTemp(void);

/**
 * Returns battery voltage
 *
 * @return battery voltage in mV (millivolts)
 */
int kscePowerGetBatteryVolt(void);

/**
 * Returns battery state of health
 *
 * @return battery state of health percent
 */
int kscePowerGetBatterySOH(void);

/**
 * Returns battery cycle count
 *
 * @return battery cycle count
 */
int kscePowerGetBatteryCycleCount(void);

/**
 * Returns CPU clock frequency
 *
 * @return CPU clock frequency in Mhz
 */
int kscePowerGetArmClockFrequency(void);

/**
 * Returns BUS clock frequency
 *
 * @return BUS clock frequency in Mhz
 */
int kscePowerGetBusClockFrequency(void);

/**
 * Returns GPU clock frequency
 *
 * @return GPU clock frequency in Mhz
 */
int kscePowerGetGpuClockFrequency(void);

/**
 * Returns GPU crossbar clock frequency
 *
 * @return GPU crossbar clock frequency in Mhz
 */
int kscePowerGetGpuXbarClockFrequency(void);

/**
 * Requests PS Vita to do a cold reset
 *
 * @return always 0
 */
int kscePowerRequestColdReset(void);

/**
 * Requests PS Vita to go into standby
 *
 * @return always 0
 */
int kscePowerRequestStandby(void);

/**
 * Requests PS Vita to suspend
 *
 * @return always 0
 */
int kscePowerRequestSuspend(void);

/**
 * Request display off
 *
 * @return always 0
 */
int kscePowerRequestDisplayOff(void);

/**
 * Sets CPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int kscePowerSetArmClockFrequency(int freq);

/**
 * Sets BUS clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int kscePowerSetBusClockFrequency(int freq);

/**
 * Sets GPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int kscePowerSetGpuClockFrequency(int freq);

/**
 * Sets GPU crossbar clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int kscePowerSetGpuXbarClockFrequency(int freq);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERN_POWER_H_ */
