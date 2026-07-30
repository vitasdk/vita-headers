/**
 * \usergroup{SceLibKernel}
 * \usage{psp2/kernel/libkernel.h,SceLibKernel_stub}
 */

#ifndef _PSP2_KERNEL_LIBKERNEL_H_
#define _PSP2_KERNEL_LIBKERNEL_H_

#include <psp2/types.h>
#include <psp2/kernel/ssp.h>
#include <psp2common/kernel/backtrace.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Terminates execution after a stack-protector check fails. */
__attribute__((__noreturn__))
void __stack_chk_fail(void);

/**
 * Gets a thread backtrace.
 *
 * @param[in] threadId Thread ID, or ::SCE_KERNEL_BACKTRACE_CONTEXT_CURRENT.
 * @param[out] pCallFrameBuffer Buffer that receives the call frames.
 * @param[in] numBytesBuffer Size of the call-frame buffer in bytes.
 * @param[out] pNumReturn Optional pointer that receives the number of frames.
 * @param[in] mode Bitwise OR of ::SceKernelBacktraceMode values.
 *
 * @return The call-stack depth on success, 0 when
 * ::SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED is used, or < 0 on error.
 */
SceInt32 sceKernelBacktrace(SceUID threadId, SceKernelCallFrame *pCallFrameBuffer, SceSize numBytesBuffer, SceUInt32 *pNumReturn, SceInt32 mode);

/**
 * Gets a backtrace of the calling thread.
 *
 * @param[out] pCallFrameBuffer Buffer that receives the call frames.
 * @param[in] numBytesBuffer Size of the call-frame buffer in bytes.
 * @param[out] pNumReturn Optional pointer that receives the number of frames.
 * @param[in] mode Bitwise OR of ::SceKernelBacktraceMode values.
 *
 * @return The call-stack depth on success, 0 when
 * ::SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED is used, or < 0 on error.
 */
SceInt32 sceKernelBacktraceSelf(SceKernelCallFrame *pCallFrameBuffer, SceSize numBytesBuffer, SceUInt32 *pNumReturn, SceInt32 mode);

/**
 * Cancels all threads currently waiting on a timer.
 *
 * @param[in] timerId Timer identifier.
 * @param[out] numWaitThreads Optional pointer that receives the number of
 * canceled waiters.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelCancelTimer(SceUID timerId, SceUInt32 *numWaitThreads);

/**
 * Gets a timer's reference process time.
 *
 * @param[in] timerId Timer identifier.
 * @param[out] baseTime Required pointer that receives 0 while the timer is
 * stopped, or its reference process time with ::SceKernelSysClock semantics
 * while it is active.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetTimerBase(SceUID timerId, SceUInt64 *baseTime);

/**
 * Gets the remaining duration before an armed timer event.
 *
 * @param[in] timerId Timer identifier.
 * @param[out] remainingTime Required pointer that receives a value with
 * ::SceKernelSysClock semantics.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetTimerEventRemainingTime(SceUID timerId, SceUInt64 *remainingTime);

/**
 * Gets size-prefixed timer information.
 *
 * @param[in] timerId Timer identifier.
 * @param[in,out] pInfo Pointer to a ::SceKernelTimerInfo structure. Its
 * leading size field selects the number of bytes returned.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetTimerInfo(SceUID timerId, void *pInfo);

/**
 * Gets the current timer time.
 *
 * @param[in] timerId Timer identifier.
 * @param[out] timerTime Required pointer that receives a value with
 * ::SceKernelSysClock semantics.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetTimerTime(SceUID timerId, SceUInt64 *timerTime);

/**
 * Prints call frames for the current process.
 *
 * @param[in] pCallFrame Call frames to print.
 * @param[in] numFrames Number of entries in pCallFrame.
 *
 * @return 0 on success, or < 0 on error.
 */
SceInt32 sceKernelPrintBacktrace(SceKernelCallFrame *pCallFrame, SceUInt32 numFrames);

/**
 * Arms a timer event after a relative interval.
 *
 * @param[in] timerId Timer identifier.
 * @param[in] type One of ::SceKernelTimerType.
 * @param[in] interval Required relative interval with ::SceKernelSysClock
 * semantics.
 * @param[in] repeat Nonzero to rearm the event periodically.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelSetTimerEvent(SceUID timerId, int type, SceUInt64 *interval, SceBool repeat);

/**
 * Sets the current timer time.
 *
 * @param[in] timerId Timer identifier.
 * @param[in,out] timerTime Required pointer containing the new timer time with
 * ::SceKernelSysClock semantics. For callers targeting SDK version 2.00 or
 * newer, it receives the previous timer time on return; older target SDK
 * versions do not receive that value.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelSetTimerTime(SceUID timerId, SceUInt64 *timerTime);

/**
 * Waits until any requested event bit is present.
 *
 * @param[in] eventId Event identifier.
 * @param[in] waitPattern Pattern of bits to wait for.
 * @param[out] pResultPattern Optional pointer that receives the matched bits.
 * @param[out] pUserData Optional pointer that receives the event's user data.
 * @param[in,out] pTimeout Optional timeout in microseconds. If the call
 * blocks, it receives the remaining duration; it receives 0 when the timeout
 * expires.
 *
 * @return 0 on success, or < 0 on error.
 */
SceInt32 sceKernelWaitEvent(SceUID eventId, SceUInt32 waitPattern, SceUInt32 *pResultPattern, SceUInt64 *pUserData, SceUInt32 *pTimeout);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_LIBKERNEL_H_ */
