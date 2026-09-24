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

/** USB device states observed on FW 3.60. */
typedef enum ScePowerBatteryUsbStatus {
	SCE_POWER_BATTERY_USB_STATUS_DISCONNECTED = 0, //!< Controller teardown or disconnect.
	SCE_POWER_BATTERY_USB_STATUS_ACTIVE       = 2, //!< Controller activation, bus reset, or unconfigured resume.
	SCE_POWER_BATTERY_USB_STATUS_CONFIGURED   = 3, //!< Configured bus or configured resume.
	SCE_POWER_BATTERY_USB_STATUS_SUSPENDED    = 4  //!< USB suspend or charging-stop state.
} ScePowerBatteryUsbStatus;

/**
 * Simulated battery state used by ::kscePowerSetBatteryFakeStatus.
 *
 * When \a discharge_time is nonzero, FW 3.60 linearly decreases the reported
 * remaining capacity from \a remaining_capacity to zero over that many
 * microseconds. A zero duration keeps the simulated capacity constant.
 */
typedef struct ScePowerBatteryFakeStatus {
	SceSize size;                 //!< Must be `sizeof(ScePowerBatteryFakeStatus)`.
	SceUInt32 remaining_capacity;  //!< Initial remaining capacity in mAh. See ::kscePowerSetBatteryFakeStatus.
	SceUInt32 full_capacity;       //!< Full capacity in mAh; 0 is treated as 2000.
	SceUInt32 discharge_time;      //!< Simulated discharge duration in microseconds, or zero to keep the capacity constant.
} ScePowerBatteryFakeStatus;
VITASDK_BUILD_ASSERT_EQ(0x10, ScePowerBatteryFakeStatus); // size is from FW 3.60

/**
 * Idle callback called by ScePower's periodic idle worker.
 *
 * @param[in] index Idle-callback slot from 0 through 7.
 * @param[in] idle_time Number of elapsed microseconds, truncated to 32 bits.
 *                     Zero reports that activity reset a previously expired
 *                     callback.
 * @param[in] user_data Value supplied to ::kscePowerSetIdleCallback.
 */
typedef void (*ScePowerIdleCallback)(SceUInt32 index, SceUInt32 idle_time, void *user_data);

/**
 * Process-idle callback called by ScePower's periodic idle worker.
 *
 * @param[in] pid Process whose idle state changed.
 * @param[in] idle_time Number of elapsed microseconds, truncated to 32 bits.
 *                     Zero reports activity after a previous expiration.
 * @param[in] user_data Value supplied to ::kscePowerSetProcessIdleCallback.
 */
typedef void (*ScePowerProcessIdleCallback)(ScePID pid, SceUInt32 idle_time, void *user_data);

/**
 * Clear ScePower's USB-charging request.
 *
 * This clears the software request and wakes the battery worker. It does not
 * issue the separate immediate-stop Syscon command used by
 * ::kscePowerBatteryStopUsbCharging.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerBatteryDisableUsbCharging(void);

/**
 * Enable ScePower's USB-charging request.
 *
 * @return The previous request state (0 or 1), or 0 while battery polling is
 *         suspended.
 */
int kscePowerBatteryEnableUsbCharging(void);

/**
 * Increment the reference count that prevents charging.
 *
 * The first forbid request cancels a pending re-enable timer and wakes the
 * battery worker.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerBatteryForbidCharging(void);

/**
 * Decrement the reference count that prevents charging, if it is nonzero.
 *
 * Releasing the last forbid request schedules charging to be reconsidered
 * after five seconds.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerBatteryPermitCharging(void);

/**
 * Set the USB device state reported to Syscon.
 *
 * @param[in] usb_status USB device state. Normally one of
 * ::ScePowerBatteryUsbStatus. Only the low eight bits are sent to Syscon; the
 * value is not range-checked.
 *
 * @return 0 if battery polling is suspended, -1 if another request is
 * pending, or the asynchronous Syscon request result.
 */
int kscePowerBatterySetUsbStatus(int usb_status);

/**
 * Request that Syscon stop USB charging immediately.
 *
 * The command is issued only while the USB-charging request is enabled. This
 * function does not clear that request; use
 * ::kscePowerBatteryDisableUsbCharging for that purpose.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerBatteryStopUsbCharging(void);

/**
 * Get one process's ARM-clock request.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 *
 * @return The requested frequency in MHz, or a negative process-local-storage
 *         error.
 */
int kscePowerGetArmClockFrequencyProc(ScePID pid);

/**
 * Get one process's bus-clock request.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 *
 * @return The requested frequency in MHz, or a negative process-local-storage
 *         error.
 */
int kscePowerGetBusClockFrequencyProc(ScePID pid);

/**
 * Get the applied camera-bus clock frequency.
 *
 * @return The frequency in MHz, rounded up to a supported level, or zero for
 *         the released/default state.
 */
int kscePowerGetCameraBusClockFrequency(void);

/**
 * Get the most recent compatibility-clock request.
 *
 * This returns the caller-supplied request, not necessarily the physical
 * frequency selected by the clock hardware.
 *
 * @return The last requested frequency in MHz.
 */
int kscePowerGetCompatClockFrequency(void);

/**
 * Get the applied DMAC5 clock frequency.
 *
 * @return The frequency in MHz, rounded up to a supported level, or zero while
 *         DMAC5 is disabled.
 */
int kscePowerGetDmac5ClockFrequency(void);

/**
 * Get the applied GPU core and MP clock frequencies.
 *
 * @param[out] core_frequency Optional output for the GPU core frequency in MHz.
 * @param[out] mp_frequency Optional output for the GPU MP frequency in MHz.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerGetGpuClockFrequencyInternal(SceInt32 *core_frequency, SceInt32 *mp_frequency);

/**
 * Get one process's GPU-clock request.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 *
 * @return The requested frequency in MHz, or a negative process-local-storage
 *         error.
 */
int kscePowerGetGpuClockFrequencyProc(ScePID pid);

/**
 * Get one process's GPU-crossbar clock request.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 *
 * @return The requested frequency in MHz, or a negative process-local-storage
 *         error.
 */
int kscePowerGetGpuXbarClockFrequencyProc(ScePID pid);

/**
 * Get the combined power-switch policy.
 *
 * FW 3.60 keeps separate kernel and Vsh/user policy values and returns their
 * bitwise OR. Only bits 0 through 2 can be set through the two exported
 * setters.
 *
 * @return The combined policy value from 0 through 7.
 */
int kscePowerGetPowerSwMode(void);

/**
 * Get the most recent Venezia-clock request.
 *
 * @return The last requested frequency in MHz, including zero.
 */
int kscePowerGetVeneziaClockFrequency(void);

/**
 * Get the most recent VIP-clock request.
 *
 * @return The last requested frequency in MHz, including zero.
 */
int kscePowerGetVipClockFrequency(void);

/**
 * Get the wakeup factor captured during the most recent resume sequence.
 *
 * Callers on FW 3.60 interpret the low seven bits as the wake-reason value.
 * The remaining bits are returned unchanged.
 *
 * @return The raw wakeup factor.
 */
int kscePowerGetWakeupFactor(void);

/**
 * Request that the display be turned on.
 *
 * FW 3.60 queues the request only for the Shell process or a system program;
 * other callers are silently ignored.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerRequestDisplayOn(void);

/**
 * Queue an asynchronous hibernate request.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerRequestHibernate(void);

/**
 * Request that an in-progress suspend sequence resume or abort sleeping.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerRequestResume(void);

/**
 * Set one process's ARM-clock request.
 *
 * ScePower applies the maximum request among active processes. FW 3.60 accepts
 * frequencies from 1 through 444 MHz; values between hardware levels select
 * the next level.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         frequency, or a negative process/clock-control error.
 */
int kscePowerSetArmClockFrequencyProc(ScePID pid, int frequency);

/**
 * Enable or disable simulated battery values.
 *
 * A NULL parameter disables simulation. For a non-NULL parameter, \a size
 * must be 0x10. If \a remaining_capacity is zero, FW 3.60 starts from the real
 * remaining capacity when it is available; otherwise it starts from
 * \a full_capacity.
 *
 * @param[in] fake_status Simulated state, or NULL to disable it.
 *
 * @return 0 on success, or ::SCE_POWER_ERROR_INVALID_VALUE if \a size is not
 *         0x10.
 */
int kscePowerSetBatteryFakeStatus(const ScePowerBatteryFakeStatus *fake_status);

/**
 * Set one process's bus-clock request.
 *
 * ScePower applies the maximum request among active processes. FW 3.60 accepts
 * frequencies from 1 through 222 MHz and rounds upward to 55, 83, 111, 166,
 * or 222 MHz.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         frequency, or a negative process/clock-control error.
 */
int kscePowerSetBusClockFrequencyProc(ScePID pid, int frequency);

/**
 * Set the camera-bus clock.
 *
 * FW 3.60 accepts 0 through 166 MHz. Zero selects the released/default state;
 * positive values are rounded upward to 41, 67, 83, 133, or 166 MHz.
 *
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         value, or a negative clock/voltage-control error.
 */
int kscePowerSetCameraBusClockFrequency(int frequency);

/**
 * Set the compatibility/Allegrex clock request.
 *
 * The meaningful requests are 0, 222, and 333 MHz. Zero releases the override,
 * 222 selects the low compatibility selector, and 333 selects the high
 * selector. FW 3.60 accepts every other signed value below 334 except
 * 222, including negative values, but all of them select the same hardware
 * mode as 333 while the getter returns the supplied value.
 *
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for a value greater
 *         than 333, or a negative clock/voltage error.
 */
int kscePowerSetCompatClockFrequency(int frequency);

/**
 * Set the maximum display brightness.
 *
 * @param[in] max_brightness Brightness limit in internal units. FW 3.60
 * normally uses 0x10000, or 0xC4EC when reducing brightness at high GPU clock
 * speeds. A value of 1 is treated as 2. Other values are not checked.
 *
 * @return Always 0.
 */
int kscePowerSetDisplayMaxBrightness(int max_brightness);

/**
 * Set the DMAC5 clock.
 *
 * FW 3.60 accepts 0 through 166 MHz. Zero disables/releases the clock;
 * positive values are rounded upward to 41, 83, 133, or 166 MHz.
 *
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         value, or a negative clock/voltage-control error.
 */
int kscePowerSetDmac5ClockFrequency(int frequency);

/**
 * Set the GPU core and MP clocks directly.
 *
 * Supplying zero for both frequencies disables the pair. Otherwise each value
 * is rounded upward to 41, 55, 83, 111, 166, or 222 MHz; a zero value is
 * treated as a request at or below 41 MHz. The resulting core frequency must
 * not exceed the resulting MP frequency. During an actual
 * selector change FW 3.60 quiesces Grab clients 8 through 11, waits at least
 * three microseconds, programs the clock, and releases those clients.
 *
 * @param[in] core_frequency GPU core frequency in MHz.
 * @param[in] mp_frequency GPU MP frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an invalid pair,
 *         or a negative clock/voltage-control error.
 */
int kscePowerSetGpuClockFrequencyInternal(SceInt32 core_frequency, SceInt32 mp_frequency);

/**
 * Set one process's GPU-clock request.
 *
 * ScePower applies the maximum request among active processes to both the GPU
 * core and MP clocks. FW 3.60 accepts frequencies from 1 through 222 MHz.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         frequency, or a negative process/clock-control error.
 */
int kscePowerSetGpuClockFrequencyProc(ScePID pid, int frequency);

/**
 * Set one process's GPU-crossbar clock request.
 *
 * ScePower applies the maximum request among active processes. FW 3.60 accepts
 * frequencies from 1 through 166 MHz; the effective hardware level is at most
 * 83, 111, or 166 MHz.
 *
 * @param[in] pid Process ID, or 0 for the current process.
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         frequency, or a negative process/clock-control error.
 */
int kscePowerSetGpuXbarClockFrequencyProc(ScePID pid, int frequency);

/**
 * Configure one of the eight global idle callbacks.
 *
 * FW 3.60 stores only the low 16 bits of \a flags. Bit 0x200 makes the slot's
 * activity timestamp reset only when its corresponding explicit tick bit is
 * supplied. Bit 0x400 makes resets conditional on the current display/input
 * policy. The purpose of other flag bits is unknown. The callback is called
 * once after \a duration expires and again with an idle time of zero if later
 * activity resets the expired slot.
 *
 * @param[in] index Slot from 0 through 7. A tick for this slot uses
 *                  `1U << index` with ::kscePowerTick.
 * @param[in] flags Idle policy flags.
 * @param[in] duration Expiration interval in microseconds, or zero to use the
 *                     global fallback interval.
 * @param[in] callback Callback to install, or NULL to clear the slot.
 * @param[in] user_data Value passed to \a callback.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an invalid index,
 *         or ::SCE_POWER_ERROR_ALREADY_REGISTERED when replacing a non-NULL
 *         callback with another non-NULL callback.
 */
int kscePowerSetIdleCallback(SceUInt32 index, int flags, SceUInt64 duration, ScePowerIdleCallback callback, void *user_data);

/**
 * Set the Vsh/user power-switch policy slot.
 *
 * The value is combined with the kernel slot set by
 * ::kscePowerSetPowerSwMode2. The individual meanings of bits 0 through 2 are
 * internal to FW 3.60's standby-button state machine.
 *
 * @param[in] mode Policy value from 0 through 7.
 *
 * @return 0 on success, or ::SCE_POWER_ERROR_INVALID_VALUE if other bits are
 *         set.
 */
int kscePowerSetPowerSwMode(int mode);

/**
 * Set the kernel power-switch policy slot.
 *
 * The value is combined with the Vsh/user slot set by
 * ::kscePowerSetPowerSwMode. The individual meanings of bits 0 through 2 are
 * internal to FW 3.60's standby-button state machine.
 *
 * @param[in] mode Policy value from 0 through 7.
 *
 * @return 0 on success, or ::SCE_POWER_ERROR_INVALID_VALUE if other bits are
 *         set.
 */
int kscePowerSetPowerSwMode2(int mode);

/**
 * Install the process-idle callback used for every tracked process.
 *
 * Passing NULL disables notifications. FW 3.60 replaces the current callback
 * and user-data value without synchronization or duplicate-registration
 * checks.
 *
 * @param[in] callback Callback to install, or NULL.
 * @param[in] user_data Value passed to \a callback.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerSetProcessIdleCallback(ScePowerProcessIdleCallback callback, void *user_data);

/**
 * Set the PS button hold threshold.
 *
 * @param[in] push_time_us Hold threshold in microseconds. FW 3.60 defaults to
 * 1000000 microseconds and does not range-check this value.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerSetPsButtonPushTime(int push_time_us);

/**
 * Set the standby/power button hold threshold.
 *
 * @param[in] push_time_us Hold threshold in microseconds. FW 3.60 defaults to
 * 2000000 microseconds, or 4000000 in the special Sysroot mode selected during
 * initialization, and does not range-check this value.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerSetStandbyButtonPushTime(int push_time_us);

/**
 * Set the system clock request.
 *
 * FW 3.60 accepts 1 through 222 MHz. Requests up to 190 select the 190 MHz
 * level; requests from 191 through 222 select the 222 MHz level. The getter
 * returns the supplied request rather than the selected level.
 *
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         value, or a negative clock/voltage-control error.
 */
int kscePowerSetSysClockFrequency(int frequency);

/**
 * Set the Venezia clock request.
 *
 * FW 3.60 accepts 0 through 333 MHz and selects the next level from 41, 55,
 * 83, 111, 166, 222, and 333 MHz. Zero disables/releases the clock. The getter
 * returns the supplied request rather than the selected level.
 *
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         value, or a negative clock/voltage-control error.
 */
int kscePowerSetVeneziaClockFrequency(int frequency);

/**
 * Set the VIP clock request.
 *
 * FW 3.60 accepts 0 through 222 MHz and selects the next level from 41, 55,
 * 83, 111, 166, and 222 MHz. Zero disables/releases the clock. The getter
 * returns the supplied request rather than the selected level.
 *
 * @param[in] frequency Requested frequency in MHz.
 *
 * @return 0 on success, ::SCE_POWER_ERROR_INVALID_VALUE for an out-of-range
 *         value, or a negative clock/voltage-control error.
 */
int kscePowerSetVipClockFrequency(int frequency);

/**
 * Record activity for ScePower idle tracking.
 *
 * Bits 0 through 7 select the corresponding global idle-callback slots. Bit 0
 * additionally refreshes the current process's idle timestamp. Other bits are
 * ignored and the value is not range-checked.
 *
 * @param[in] type Bitmask of idle-callback slots to refresh.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerTick(SceUInt32 type);

/**
 * Set ScePower's software WLAN-active flag.
 *
 * This does not directly enable WLAN hardware.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerWlanActivate(void);

/**
 * Clear ScePower's software WLAN-active flag.
 *
 * This does not directly disable WLAN hardware.
 *
 * @return Always 0 on FW 3.60.
 */
int kscePowerWlanDeactivate(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_POWER_H_ */
