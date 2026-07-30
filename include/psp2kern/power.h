/**
 * \kernelgroup{ScePower}
 * \usage{psp2kern/power.h,ScePowerForDriver_stub}
 */

#ifndef _PSP2KERN_POWER_H_
#define _PSP2KERN_POWER_H_

#include <psp2common/power.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 * @return Battery life time in minutes
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
 * Returns Sys clock frequency
 *
 * @return Sys clock frequency in Mhz
 */
int kscePowerGetSysClockFrequency(void);

/**
 * Returns GPU crossbar clock frequency
 *
 * @return GPU crossbar clock frequency in Mhz
 */
int kscePowerGetGpuXbarClockFrequency(void);

/**
 * Requests PS Vita to do a soft reset
 *
 * @return always 0
 */
int kscePowerRequestSoftReset(void);

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
 * Set the screen brightness.
 * @see ::sceAVConfigSetDisplayBrightness for userland counterpart.
 *
 * @param brightness Brightness that the screen will be set to (range 21-65536, 0 turns off the screen).
 *
 * @return ?
 */
int kscePowerSetDisplayBrightness(int brightness);

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

int kscePowerBatteryDisableUsbCharging(void);
int kscePowerBatteryEnableUsbCharging(void);
int kscePowerBatteryForbidCharging(void);
int kscePowerBatteryPermitCharging(void);

/**
 * Sets the USB device state reported to Syscon.
 *
 * @param[in] usb_status USB device state. Known FW 3.60 values are 0 for
 * disconnected, 2 for active or reset, 3 for configured, and 4 for suspended.
 * Only the low eight bits are sent to Syscon; the value is not range-checked.
 *
 * @return 0 if battery polling is suspended, -1 if another request is
 * pending, or the asynchronous Syscon request result.
 */
int kscePowerBatterySetUsbStatus(int usb_status);

int kscePowerBatteryStopUsbCharging(void);
int kscePowerGetArmClockFrequencyProc(SceUID pid);
int kscePowerGetBusClockFrequencyProc(SceUID pid);
int kscePowerGetCameraBusClockFrequency(void);
int kscePowerGetCompatClockFrequency(void);
int kscePowerGetDmac5ClockFrequency(void);
int kscePowerGetGpuClockFrequencyInternal(SceInt32 *corefreq, SceInt32 *mpfreq);
int kscePowerGetGpuClockFrequencyProc(SceUID pid);
int kscePowerGetGpuXbarClockFrequencyProc(SceUID pid);
int kscePowerGetPowerSwMode(void);
int kscePowerGetVeneziaClockFrequency(void);
int kscePowerGetVipClockFrequency(void);
int kscePowerGetWakeupFactor(void);
int kscePowerRequestDisplayOn(void);
int kscePowerRequestHibernate(void);
int kscePowerRequestResume(void);
int kscePowerSetArmClockFrequencyProc(SceUID pid, int clock);
int kscePowerSetBatteryFakeStatus(int status);
int kscePowerSetBusClockFrequencyProc(SceUID pid, int clock);
int kscePowerSetCameraBusClockFrequency(int clock);
int kscePowerSetCompatClockFrequency(int clock);

/**
 * Sets the maximum display brightness.
 *
 * @param[in] max_brightness Maximum brightness in the internal scale. FW 3.60
 * uses 0x10000 as the normal full-scale ceiling and 0xC4EC as a reduced
 * high-GPU-clock ceiling. A value of 1 is normalized to 2; other values are
 * not range-checked.
 *
 * @return Always 0.
 */
int kscePowerSetDisplayMaxBrightness(int max_brightness);

int kscePowerSetDmac5ClockFrequency(int clock);
int kscePowerSetGpuClockFrequencyInternal(SceInt32 corefreq, SceInt32 mpfreq);
int kscePowerSetGpuClockFrequencyProc(SceUID pid, int clock);
int kscePowerSetGpuXbarClockFrequencyProc(SceUID pid, int clock);
int kscePowerSetIdleCallback(SceUInt32 idx, int inhibit_reset, SceUInt64 duration, void *idle_cb, int idle_cb_info_5);
int kscePowerSetPowerSwMode(int mode);
int kscePowerSetPowerSwMode2(int mode);
int kscePowerSetProcessIdleCallback(int idle_cb_info_1, int idle_cb_info_2);

/**
 * Sets the PS button hold threshold.
 *
 * @param[in] push_time_us Hold threshold in microseconds. FW 3.60 defaults to
 * 1000000 microseconds and does not range-check this value.
 *
 * @return Always 0.
 */
int kscePowerSetPsButtonPushTime(int push_time_us);

/**
 * Sets the standby/power button hold threshold.
 *
 * @param[in] push_time_us Hold threshold in microseconds. FW 3.60 defaults to
 * 2000000 microseconds, or 4000000 in the special Sysroot mode selected during
 * initialization, and does not range-check this value.
 *
 * @return Always 0.
 */
int kscePowerSetStandbyButtonPushTime(int push_time_us);

int kscePowerSetSysClockFrequency(int clock);
int kscePowerSetVeneziaClockFrequency(int clock);
int kscePowerSetVipClockFrequency(int clock);
int kscePowerTick(SceUInt32 type);
int kscePowerWlanActivate(void);
int kscePowerWlanDeactivate(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_POWER_H_ */
