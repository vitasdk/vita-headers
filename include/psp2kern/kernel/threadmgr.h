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
 * @return 0 to release the alarm object. A nonzero value is treated as an
 * unsigned delay in microseconds. It rearms the alarm relative to its previous
 * deadline. Delays below 200 microseconds are rounded up to 200.
 */
typedef SceInt32 (*SceKernelTimerFunction)(SceInt32 common);

/**
 * Changes a thread's CPU affinity mask.
 *
 * @param[in] thread_id Thread identifier, or 0 for the current thread.
 * @param[in] cpu_affinity_mask New CPU affinity mask. Kernel callers may use
 * bits 0-3 or the corresponding bits 16-19, but may not combine the two
 * encodings. Value 0x40000000 selects the current CPU.
 *
 * @return The previous affinity mask in bits 0-3, or < 0 on error. The result
 * uses bits 0-3 even when cpu_affinity_mask uses bits 16-19.
 */
SceInt32 ksceKernelChangeThreadCpuAffinityMask(SceUID thread_id, SceInt32 cpu_affinity_mask);

/**
 * Clears event bits by ANDing the current pattern with the supplied pattern.
 *
 * @param[in] event_id Event identifier.
 * @param[in] clear_pattern Bits to retain. Passing 0 clears all bits. Bit
 * 0x00010000 is reserved; setting it causes an error.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelClearEvent(SceUID event_id, SceUInt32 clear_pattern);

/**
 * Gets the time from which a timer is measured.
 *
 * @param[in] timer_id Timer identifier.
 *
 * @return While running, the process-time value from which the timer is
 * measured; 0 while stopped; or UINT64_MAX on error.
 */
SceUInt64 ksceKernelGetTimerBaseWide(SceUID timer_id);

/**
 * Gets a timer's current time.
 *
 * @param[in] timer_id Timer identifier.
 *
 * @return The current time, or UINT64_MAX on error.
 */
SceUInt64 ksceKernelGetTimerTimeWide(SceUID timer_id);

/**
 * Creates and immediately schedules a kernel alarm callback.
 *
 * @param[in] name Required alarm name.
 * @param[in] delay Initial delay in microseconds.
 * @param[in] function Callback of type ::SceKernelTimerFunction.
 * @param[in] common Value passed to the callback.
 *
 * @return Alarm identifier on success, or < 0 on error.
 */
SceUID ksceKernelRegisterTimer(const char *name, SceUInt32 delay, SceKernelTimerFunction function, SceInt32 common);

/**
 * Starts a timer.
 *
 * @param[in] timer_id Timer identifier.
 *
 * @return 0 if started, 1 if already active, or < 0 on error.
 */
int ksceKernelStartTimer(SceUID timer_id);

/**
 * Stops a timer.
 *
 * @param[in] timer_id Timer identifier.
 *
 * @return 1 if stopped, 0 if already stopped, or < 0 on error.
 */
int ksceKernelStopTimer(SceUID timer_id);

/**
 * Waits for an event pattern without running thread callbacks.
 *
 * @param[in] event_id Event identifier.
 * @param[in] wait_pattern Pattern to wait for.
 * @param[out] result_pattern Optional output for the matched pattern.
 * @param[out] user_data Optional output for the event's user data.
 * @param[in,out] timeout Optional timeout in microseconds.
 *
 * @return 0 on success, or < 0 on error.
 */
int ksceKernelWaitEvent(SceUID event_id, SceUInt32 wait_pattern, SceUInt32 *result_pattern, SceUInt64 *user_data, SceUInt32 *timeout);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_H_ */
