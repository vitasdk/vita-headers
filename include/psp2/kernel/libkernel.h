/**
 * \usergroup{SceLibKernel}
 * \usage{psp2/kernel/libkernel.h,SceLibKernel_stub}
 */

#ifndef _PSP2_KERNEL_LIBKERNEL_H_
#define _PSP2_KERNEL_LIBKERNEL_H_

#include <psp2/types.h>
#include <psp2/kernel/ssp.h>
#include <psp2/sblgcauthmgr.h>
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
 * @param[in] thread_id Thread ID, or ::SCE_KERNEL_BACKTRACE_CONTEXT_CURRENT.
 * @param[out] call_frame_buffer Buffer that receives the call frames, or NULL
 *                              when \a num_bytes_buffer is 0.
 * @param[in] num_bytes_buffer Size of the call-frame buffer in bytes. A non-NULL
 *                           buffer must hold at least one frame.
 * @param[out] num_frames Optional pointer that receives the number of frames
 *                        written to the output buffer.
 * @param[in] mode Bitwise OR of ::SceKernelBacktraceMode values.
 *
 * @return With ::SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED, 0 on success.
 * Otherwise, the complete call-stack depth on success, even when the output
 * buffer is too small to contain every frame. Returns < 0 on error.
 */
SceInt32 sceKernelBacktrace(SceUID thread_id, SceKernelCallFrame *call_frame_buffer, SceSize num_bytes_buffer, SceUInt32 *num_frames, SceInt32 mode);

/**
 * Gets a backtrace of the calling thread.
 *
 * @param[out] call_frame_buffer Buffer that receives the call frames, or NULL
 *                              when \a num_bytes_buffer is 0.
 * @param[in] num_bytes_buffer Size of the call-frame buffer in bytes. A non-NULL
 *                           buffer must hold at least one frame.
 * @param[out] num_frames Optional pointer that receives the number of frames
 *                        written to the output buffer.
 * @param[in] mode Bitwise OR of ::SceKernelBacktraceMode values.
 *
 * @return With ::SCE_KERNEL_BACKTRACE_MODE_DONT_EXCEED, 0 on success.
 * Otherwise, the complete call-stack depth on success, even when the output
 * buffer is too small to contain every frame. Returns < 0 on error.
 */
SceInt32 sceKernelBacktraceSelf(SceKernelCallFrame *call_frame_buffer, SceSize num_bytes_buffer, SceUInt32 *num_frames, SceInt32 mode);

/**
 * Disarms a timer event and cancels all waits on the timer.
 *
 * @param[in] timer_id Timer identifier.
 * @param[out] num_wait_threads Optional pointer that receives the number of
 * threads whose waits were canceled.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelCancelTimer(SceUID timer_id, SceUInt32 *num_wait_threads);

/**
 * Gets a timer's reference process time.
 *
 * @param[in] timer_id Timer identifier.
 * @param[out] base_time Must be non-NULL. Receives 0 while the timer is stopped,
 * or its reference process time as a ::SceKernelSysClock value while it is active.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetTimerBase(SceUID timer_id, SceKernelSysClock *base_time);

/**
 * Gets the remaining duration before an armed timer event.
 *
 * @param[in] timer_id Timer identifier.
 * @param[out] remaining_time Must be non-NULL. Receives the remaining duration
 * as a ::SceKernelSysClock value.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetTimerEventRemainingTime(SceUID timer_id, SceKernelSysClock *remaining_time);

/**
 * Gets timer information.
 *
 * @param[in] timer_id Timer identifier.
 * @param[in,out] info Must point to a ::SceKernelTimerInfo structure.
 * Its first field, \c size, sets the exact number of bytes copied to and from
 * the structure, up to the full 0x60-byte structure on FW 3.60.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetTimerInfo(SceUID timer_id, SceKernelTimerInfo *info);

/**
 * Gets the current timer time.
 *
 * @param[in] timer_id Timer identifier.
 * @param[out] timer_time Must be non-NULL. Receives the current timer time
 * as a ::SceKernelSysClock value.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelGetTimerTime(SceUID timer_id, SceKernelSysClock *timer_time);

/**
 * Prints call frames for the current process.
 *
 * @param[in] call_frame Call frames to print. Must be non-NULL even when
 *                       \a num_frames is 0.
 * @param[in] num_frames Number of entries in call_frame.
 *
 * @return 0 on success, or < 0 on error.
 */
SceInt32 sceKernelPrintBacktrace(const SceKernelCallFrame *call_frame, SceUInt32 num_frames);

/**
 * Arms a timer event after a relative interval.
 *
 * @param[in] timer_id Timer identifier.
 * @param[in] type Notification behavior selected from ::SceKernelTimerType.
 * @param[in] interval Must be non-NULL. Points to the relative interval
 * expressed as a ::SceKernelSysClock value.
 * @param[in] repeat Nonzero to rearm the event periodically.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelSetTimerEvent(SceUID timer_id, SceKernelTimerType type, const SceKernelSysClock *interval, SceBool repeat);

/**
 * Sets the current timer time.
 *
 * @param[in] timer_id Timer identifier.
 * @param[in,out] timer_time Must be non-NULL. Contains the new timer time as a
 * ::SceKernelSysClock value. For callers targeting SDK version 2.00 or newer,
 * it receives the previous timer time on return; older target SDK versions do
 * not receive that value.
 *
 * @return 0 on success, or < 0 on error.
 */
int sceKernelSetTimerTime(SceUID timer_id, SceKernelSysClock *timer_time);

/**
 * Gets the 0x20-byte type 01 media ID produced by the game-card authentication state.
 *
 * @param[out] media_id - Output media ID.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblGcAuthMgrGetMediaIdType01(SceMediaIdType01 *media_id);

/**
 * Installs PC activation data.
 *
 * The key envelope is verified against the saved challenge state before the
 * trailing 0x1040-byte activation payload is written.
 *
 * @param[in] act_data - Pointer to a 0x1090-byte activation object.
 * @param[in] act_data_size - Must be 0x1090.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblGcAuthMgrPcactActivation(const ScePcactActivationData *act_data, SceSize act_data_size);

/**
 * Creates a PC activation challenge.
 *
 * @param[in] mode - Challenge mode. Mode 0 is rejected until the previously
 *                   recorded expiration tick has passed. Mode 1 requires
 *                   that no readable activation data exists and records a
 *                   new expiration. Mode 2 bypasses the expiration check.
 * @param[in] epassword - Pointer to a 0x20-byte input buffer.
 * @param[out] challenge - Receives the 0x80-byte challenge.
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblGcAuthMgrPcactGetChallenge(SceUInt32 mode, const SceUInt8 *epassword, ScePcactChallenge *challenge);

/**
 * Verifies a package ECDSA-160 signature.
 *
 * @param[in] hash - Pointer to a 0x14-byte SHA-1 digest.
 * @param[in] signature - Pointer to a 0x28-byte ECDSA signature.
 *
 * @return 0 if the signature is valid, < 0 on error.
 */
int sceSblGcAuthMgrPkgVry(const SceUInt8 *hash, const SceUInt8 *signature);

/**
 * Waits until any requested event bit is present.
 *
 * When the event has the auto-clear attribute, the matched bits are removed
 * after a successful wait. This function does not dispatch callbacks while
 * blocked.
 *
 * @param[in] event_id Event identifier.
 * @param[in] wait_pattern Pattern of bits to wait for.
 * @param[out] result_pattern Optional pointer that receives the matched bits.
 * @param[out] user_data Optional pointer that receives the event's user data.
 * @param[in,out] timeout Optional timeout in microseconds. If the call
 * blocks, it receives the remaining duration; it receives 0 when the timeout
 * expires. It is left unchanged when the wait is satisfied immediately.
 *
 * @return 0 on success, or < 0 on error.
 */
SceInt32 sceKernelWaitEvent(SceUID event_id, SceUInt32 wait_pattern, SceUInt32 *result_pattern, SceUInt64 *user_data, SceUInt32 *timeout);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_LIBKERNEL_H_ */
