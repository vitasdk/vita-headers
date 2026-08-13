/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_H_
#define _PSP2KERN_KERNEL_THREADMGR_H_

#include <psp2kern/kernel/threadmgr/thread.h>
#include <psp2kern/kernel/threadmgr/cond.h>
#include <psp2kern/kernel/threadmgr/mutex.h>
#include <psp2kern/kernel/threadmgr/fast_mutex.h>
#include <psp2kern/kernel/threadmgr/lw_cond.h>
#include <psp2kern/kernel/threadmgr/lw_mutex.h>
#include <psp2kern/kernel/threadmgr/event_flags.h>
#include <psp2kern/kernel/threadmgr/semaphores.h>
#include <psp2kern/kernel/threadmgr/msg_pipe.h>
#include <psp2kern/kernel/threadmgr/callback.h>
#include <psp2kern/kernel/threadmgr/misc.h>
#include <psp2kern/kernel/threadmgr/workqueues.h>
#include <psp2kern/kernel/threadmgr/debugger.h>
#include <psp2kern/kernel/threadmgr/vfp.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Kernel timer callback.
 *
 * @param[in] common Value supplied to ::ksceKernelRegisterTimer.
 *
 * @return 0 to unregister the timer. Any nonzero value is interpreted as an
 * unsigned delay in microseconds and rearms it; delays smaller than 200
 * microseconds are rounded up to 200.
 */
typedef int (*SceKernelTimerFunction)(int common);

/**
 * Changes a thread's CPU affinity mask.
 *
 * @param[in] threadId Thread identifier, or 0 for the current thread.
 * @param[in] cpuAffinityMask New CPU affinity mask.
 *
 * @return The previous low four-bit affinity mask, or < 0 on error. The result
 * uses the low-mask encoding even when cpuAffinityMask uses the high-word
 * encoding.
 */
SceInt32 ksceKernelChangeThreadCpuAffinityMask(SceUID threadId, SceInt32 cpuAffinityMask);

/**
 * Clears event bits by ANDing the current pattern with the supplied pattern.
 *
 * @param[in] eventId Event identifier.
 * @param[in] clearPattern Pattern to retain. Passing 0 clears all bits. Bit
 * 0x00010000 is reserved and is rejected when set.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelClearEvent(SceUID eventId, SceUInt32 clearPattern);

/**
 * Gets a timer's base time.
 *
 * @param[in] timerId Timer identifier.
 *
 * @return 0 while the timer is stopped, its base time while active, or
 * UINT64_MAX on error.
 */
SceUInt64 ksceKernelGetTimerBaseWide(SceUID timerId);

/**
 * Gets a timer's current time.
 *
 * @param[in] timerId Timer identifier.
 *
 * @return The current time, or UINT64_MAX on error.
 */
SceUInt64 ksceKernelGetTimerTimeWide(SceUID timerId);

/**
 * Registers a kernel timer callback.
 *
 * @param[in] name Timer name.
 * @param[in] delay Initial delay in microseconds.
 * @param[in] function Callback of type ::SceKernelTimerFunction.
 * @param[in] common Value passed to the callback.
 *
 * @return Timer identifier on success, or < 0 on error.
 */
int ksceKernelRegisterTimer(char *name, SceUInt32 delay, void *function, int common);

/**
 * Starts a timer.
 *
 * @param[in] timerId Timer identifier.
 *
 * @return 0 if started, 1 if already active, or < 0 on error.
 */
int ksceKernelStartTimer(SceUID timerId);

/**
 * Stops a timer.
 *
 * @param[in] timerId Timer identifier.
 *
 * @return 1 if stopped, 0 if already stopped, or < 0 on error.
 */
int ksceKernelStopTimer(SceUID timerId);

/**
 * Waits for an event pattern.
 *
 * @param[in] eventId Event identifier.
 * @param[in] waitPattern Pattern to wait for.
 * @param[out] pResultPattern Optional matched-pattern output.
 * @param[out] pUserData Optional event user-data output.
 * @param[in,out] pTimeout Optional timeout in microseconds.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelWaitEvent(SceUID eventId, SceUInt32 waitPattern, SceUInt32 *pResultPattern, SceUInt64 *pUserData, SceUInt32 *pTimeout);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_H_ */
