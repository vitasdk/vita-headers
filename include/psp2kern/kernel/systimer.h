/**
 * \kernelgroup{SceSystimer}
 * \usage{psp2kern/kernel/systimer.h,SceSystimerForDriver_stub}
 */

#ifndef _PSP2KERN_SYSTIMER_H_
#define _PSP2KERN_SYSTIMER_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SceInt32 SceSysTimerId;

typedef void (*SceSysTimerCallback)(SceSysTimerId timer, void* pUserData);

typedef enum SceSysTimerType {
    SCE_SYSTIMER_TYPE_LONG = 1, //!< 64-bit timer
    SCE_SYSTIMER_TYPE_WORD = 2  //!< 32-bit timer
} SceSysTimerType;

typedef enum SceSysTimerClockSource {
    SCE_SYSTIMER_CLOCK_SOURCE_SYS    = 0, //!< 190/222MHz Frequency. Controlled by kscePower[Get|Set]SysClockFrequency
    SCE_SYSTIMER_CLOCK_SOURCE_48MHZ  = 3, //!< 48MHz Frequency. Used by GpuEs4 and Threadmgr timers
} SceSysTimerClockSource;

/**
 * @brief Allocate one of the system's timers.
 *
 * @param timerType - One of ::SceSysTimerType.
 *
 * @return The id of the new timer on success, < 0 on error.
 */
SceSysTimerId ksceKernelSysTimerAlloc(SceSysTimerType timerType);
/**
 * @brief Free an allocated system timer
 * 
 * @param timerId - The timer to free.
 * 
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerFree(SceSysTimerId timerId);

/**
 * @brief Start a timer.
 *
 * @param timerId - The target timer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerStartCount(SceSysTimerId timerId);
/**
 * @brief Stop a timer.
 *
 * @param timerId - The target timer.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerStopCount(SceSysTimerId timerId);

/**
 * @brief Configure the source clock signal for a timer.
 * 
 * @par The final input clock is determined as such:
 * @code
 * inputClock = sourceClock / (prescaleFactor + 1)
 * @endcode
 *
 * @param timerId        - The target timer.
 * @param clockSource    - The source of the clock signal.
 * @param prescaleFactor - The prescale factor applied to the clock signal.
 * 
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerSetClockSource(SceSysTimerId timerId, SceSysTimerClockSource clockSource, SceUInt8 prescaleFactor);
/**
 * @brief Set the timer interval.
 * 
 * The interval determines the count at which the timer will overflow to 0, and an interrupt will be fired.
 *
 * @param timerId  - The target timer.
 * @param interval - The timer interval.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerSetInterval(SceSysTimerId timerId, SceKernelSysClock interval);
/**
 * @brief Set the interrupt callback handler for the timer.
 *
 * @param timerId   - The target timer.
 * @param callback  - The callback function.
 * @param targetCPU - The CPU cores the interrupt can be handled from.
 * @param pUserData - User data to be passed to the callback.
 * 
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerSetHandler(SceSysTimerId timerId, SceSysTimerCallback callback, SceUInt32 targetCPU, void *pUserData);

/**
 * @brief Get the timer count value.
 *
 * @param timerId - The target timer.
 * @param pCount  - The variable to store the count to.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerGetCount(SceSysTimerId timerId, SceKernelSysClock *pCount);
/**
 * @brief Set the timer count value.
 *
 * @param timerId - The target timer.
 * @param count   - The count to set.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerSetCount(SceSysTimerId timerId, SceKernelSysClock count);
/**
 * @brief Reset the timer count.
 *
 * @param timerId - The target timer.
 * 
 * @return 0 on success, < 0 on error.
 */
int ksceKernelSysTimerResetCount(SceSysTimerId timerId);

#ifdef __cplusplus
}
#endif

#endif