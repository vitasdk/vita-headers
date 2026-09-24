/**
 * \kernelgroup{SceSblSmSchedProxy}
 * \usage{psp2kern/kernel/sm_sched.h,SceSblSmSchedProxyForKernel_stub}
 */

#ifndef _PSP2KERN_KERNEL_SM_SCHED_H_
#define _PSP2KERN_KERNEL_SM_SCHED_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/sm_comm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Secure-module scheduler interrupt handler.
 *
 * @param req_id - Scheduler request ID.
 * @param interrupt_index - Interrupt index in the range 0 through 3.
 * @param callback_arg - Value supplied to
 *                       ::ksceSblSmSchedProxyRegisterIntrHandler.
 * @param status - Scheduler status. FW 3.60 callers clear bit 0x8 before
 *                 testing for ::SCE_SM_STATUS_RUNNING; the bit's purpose is
 *                 unknown.
 * @param result - Secure-module result or error code.
 *
 * The handler's return value is ignored on FW 3.60.
 */
typedef int SceSblSmSchedProxyIntrHandler(SceSmSchedRequestId req_id, SceUInt32 interrupt_index, int callback_arg, SceUInt32 status, int result);

/** Previous VitaSDK type name retained for backwards compatibility. */
typedef SceSblSmSchedProxyIntrHandler sceSblSmSchedProxyIntrHandler;

/** Scheduler-proxy errors identified on FW 3.60. */
typedef enum SceSblSmSchedProxyErrorCode {
	SCE_SM_SCHED_PROXY_ERROR_RESOURCE_LIMIT             = 0x800F040C,
	SCE_SM_SCHED_PROXY_ERROR_INVALID_ARGUMENT           = 0x800F0416,
	SCE_SM_SCHED_PROXY_ERROR_NOT_SUPPORTED              = 0x800F0425,
	SCE_SM_SCHED_PROXY_ERROR_NOT_INITIALIZED            = 0x800F0426,
	SCE_SM_SCHED_PROXY_ERROR_REQUEST_ALREADY_STOPPED    = 0x800F0429, //!< FW 3.60 callers treat this as an already stopped request.
	SCE_SM_SCHED_PROXY_ERROR_REQUEST_NOT_FOUND          = 0x800F042B,
	SCE_SM_SCHED_PROXY_ERROR_HANDLER_ALREADY_REGISTERED = 0x800F042E
} SceSblSmSchedProxyErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, SceSblSmSchedProxyErrorCode); // size is from FW 3.60

/**
 * Secure-module scheduler lifecycle states.
 *
 * FW 3.60 SceSblAuthMgr and SceSblSsSmComm clear bit 0x8 before comparing a
 * callback status with ::SCE_SM_STATUS_RUNNING. The purpose of that bit is
 * unknown.
 *
 * A request enters ::SCE_SM_STATUS_READY when created or after suspension
 * completes. The normal scheduling path is
 * ::SCE_SM_STATUS_READY -> ::SCE_SM_STATUS_START_RESUME_REQUESTED ->
 * ::SCE_SM_STATUS_RUNNING. Preemption follows ::SCE_SM_STATUS_RUNNING ->
 * ::SCE_SM_STATUS_SUSPEND_REQUESTED -> ::SCE_SM_STATUS_SUSPENDING ->
 * ::SCE_SM_STATUS_READY. A request that finishes normally enters
 * ::SCE_SM_STATUS_STOPPED. An explicit force-stop or scheduler shutdown puts
 * it in ::SCE_SM_STATUS_FORCE_STOPPED.
 */
typedef enum SceSmStatus {
	SCE_SM_STATUS_READY                  = 0x1,
	SCE_SM_STATUS_RUNNING                = 0x2,
	SCE_SM_STATUS_STOPPED                = 0x3,
	SCE_SM_STATUS_FORCE_STOPPED          = 0x4,
	SCE_SM_STATUS_START_RESUME_REQUESTED = 0x6,
	SCE_SM_STATUS_SUSPENDING             = 0x7,
	SCE_SM_STATUS_SUSPEND_REQUESTED      = 0xB
} SceSmStatus;
VITASDK_BUILD_ASSERT_EQ(1, SceSmStatus); // size is from FW 3.60

/**
 * Set bits in an ARM-to-Cry scheduler mailbox through SMC 0x133.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param mail_mask - Bits to set.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedCallFunc(SceSmSchedRequestId req_id, SceUInt32 mailbox_id, SceUInt32 mail_mask);

/**
 * Forcibly stop a secure-module scheduler request through SMC 0x130.
 *
 * ::SCE_SM_STATUS_READY and ::SCE_SM_STATUS_SUSPENDING requests are first
 * moved to ::SCE_SM_STATUS_READY and then enter
 * ::SCE_SM_STATUS_FORCE_STOPPED.
 * ::SCE_SM_STATUS_RUNNING and ::SCE_SM_STATUS_START_RESUME_REQUESTED requests
 * issue secure control command 0x501 and transition through internal states
 * 0xC and 0x9 before reaching ::SCE_SM_STATUS_FORCE_STOPPED.
 *
 * @param req_id - Scheduler request ID.
 *
 * @return 0 on success, ::SCE_SM_SCHED_PROXY_ERROR_REQUEST_ALREADY_STOPPED
 *         when the request is not in a stoppable state, or another negative
 *         scheduler validation error.
 */
int ksceSblSmSchedProxyForceStop(SceSmSchedRequestId req_id);

/** Previous VitaSDK name retained for backwards compatibility. */
#define ksceSblSmSchedProxyChangeF00DStatus ksceSblSmSchedProxyForceStop

/**
 * Release a scheduler interrupt handler through SMC 0x139.
 *
 * @param req_id - Scheduler request ID.
 * @param interrupt_index - Interrupt index in the range 0 through 3.
 *
 * The local handler slot is cleared before the secure-monitor call and is not
 * restored if that call fails.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyReleaseIntrHandler(SceSmSchedRequestId req_id, SceUInt32 interrupt_index);

/** Previous VitaSDK name retained for backwards compatibility. */
#define ksceSblSmSchedProxyDisableCry2ArmInterrupt ksceSblSmSchedProxyReleaseIntrHandler

/**
 * Register a scheduler interrupt handler through SMC 0x138.
 *
 * @param req_id - Scheduler request ID.
 * @param interrupt_index - Interrupt index in the range 0 through 3.
 * @param handler - Interrupt handler; must be non-NULL.
 * @param callback_arg - Value passed unchanged as the handler's third
 *                       argument.
 *
 * If a notification is already pending, the handler is called before this
 * function executes the secure-monitor command. The handler remains installed
 * locally if the secure-monitor call fails.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyRegisterIntrHandler(SceSmSchedRequestId req_id, SceUInt32 interrupt_index, SceSblSmSchedProxyIntrHandler *handler, int callback_arg);

/** Previous VitaSDK name retained for backwards compatibility. */
#define ksceSblSmSchedProxyEnableCry2ArmInterrupt ksceSblSmSchedProxyRegisterIntrHandler

/**
 * Execute a secure scheduler control command selected by index through
 * SMC 0x13C.
 *
 * FW 3.60 accepts command indices 0 through 4 and writes control values 0xB01
 * through 0xF01 respectively to the secure scheduler control register. The
 * three remaining arguments are forwarded by the non-secure proxy but ignored
 * by the secure handler.
 *
 * SceSdif uses command index 3 while resetting the eMMC host controller.
 * SceSblSsMgr uses command index 4 at the end of the 0x20F-through-0x200
 * system-suspend event sequence. These call sites do not establish the exact
 * hardware purposes of either command.
 *
 * @param command_index - Secure-monitor command index.
 * @param unused1 - Ignored on FW 3.60; set to 0.
 * @param unused2 - Ignored on FW 3.60; set to 0.
 * @param unused3 - Ignored on FW 3.60; set to 0.
 *
 * @return 0 on success, ::SCE_SM_SCHED_PROXY_ERROR_INVALID_ARGUMENT for an
 *         index greater than 4, or ::SCE_SM_SCHED_PROXY_ERROR_NOT_INITIALIZED.
 */
int ksceSblSmSchedProxyExecuteSKCommand(SceUInt32 command_index, SceUInt32 unused1, SceUInt32 unused2, SceUInt32 unused3);

/** Previous VitaSDK name retained for backwards compatibility. */
#define ksceSblSmSchedProxyExecuteF00DCommand ksceSblSmSchedProxyExecuteSKCommand

/**
 * Read an ARM-to-Cry mailbox through SMC 0x134.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param mail_value - Receives the register value; must be non-NULL.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyReadArm2Cry(SceSmSchedRequestId req_id, SceUInt32 mailbox_id, SceUInt32 *mail_value);

/** Previous VitaSDK name retained for backwards compatibility. */
#define ksceSblSmSchedProxyGetCommandF00DRegister ksceSblSmSchedProxyReadArm2Cry

/**
 * Query a secure-module request through SMC 0x12F.
 *
 * @param req_id - Scheduler request ID.
 * @param result - Receives the secure-module result and scheduler status;
 *                  must be non-NULL. Unlike ::ksceSblSmSchedProxyWait, this
 *                  function does not release the request record.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyGetStatus(SceSmSchedRequestId req_id, SceSblSmCommPair *result);

/**
 * Initialize the scheduler proxy.
 *
 * Initialization runs only when this function is called on CPU 0.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSmSchedProxyInitialize(void);

/**
 * Start a secure-module scheduler request through SMC 0x12D.
 *
 * @param priority - Boolean priority: 0 for high priority, 1 for low priority.
 * @param pa_ranges_paddr - Physical address of an array of
 *                          ::SceKernelPARange entries. It is required when
 *                          `(context->self_type & 0xF000) == 0` and must be 0
 *                          when that value is 0x1000.
 * @param pa_range_count - Number of entries in the physical-address range
 *                         array. It must be 0 when
 *                         `(context->self_type & 0xF000) == 0x1000`.
 * @param invoke_input - Optional four-word startup data, copied unchanged.
 *                       The secure module defines their meaning; the scheduler
 *                       does not interpret them. NULL passes four zero words.
 * @param context - Launch context; must be non-NULL. FW 3.60 reads only self_type,
 *               media_type, and the program authority ID and capability from
 *               spawner_self_auth_info.
 * @param request_id - Receives the scheduler request ID; must be non-NULL.
 *
 * Values of `context->self_type & 0xF000` other than 0 or 0x1000 are rejected.
 * A request ID is assigned before the shared-buffer and secure-monitor work;
 * callers may therefore receive an assigned ID even when a later step fails.
 * The proxy can track at most 64 concurrent request records.
 *
 * @return Secure-monitor result or a negative scheduler/kernel error.
 */
int ksceSblSmSchedProxyInvoke(SceBool priority, SceUIntPtr pa_ranges_paddr, SceSize pa_range_count, const SceSmInvokeDataBlockInput *invoke_input, const SceSblSmCommContext130 *context, SceSmSchedRequestId *request_id);

/**
 * Read a Cry-to-ARM mailbox through SMC 0x137.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param mail_value - Receives the mailbox value; must be non-NULL.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyReadCry2Arm(SceSmSchedRequestId req_id, SceUInt32 mailbox_id, SceUInt32 *mail_value);

/**
 * Uninitialize the scheduler proxy.
 *
 * Uninitialization runs only when this function is called on CPU 0.
 *
 * @return Secure-monitor result or 0 when called on another CPU.
 */
int ksceSblSmSchedProxyUninitialize(void);

/**
 * Wait for a secure-module request to complete through SMC 0x12E.
 *
 * @param req_id - Scheduler request ID.
 * @param result - Receives the secure-module result and scheduler status;
 *                  must be non-NULL. The request record is released before
 *                  this function returns.
 *
 * @return Secure-monitor result or a negative scheduler/kernel error.
 */
int ksceSblSmSchedProxyWait(SceSmSchedRequestId req_id, SceSblSmCommPair *result);

/**
 * Clear bits in an ARM-to-Cry mailbox through SMC 0x135.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param mail_mask - Bits to clear.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyClearArm2Cry(SceSmSchedRequestId req_id, SceUInt32 mailbox_id, SceUInt32 mail_mask);

/** Previous VitaSDK name retained for backwards compatibility. */
#define ksceSblSmSchedProxyWriteArm2Cry ksceSblSmSchedProxyClearArm2Cry

/**
 * Clear bits in a Cry-to-ARM mailbox through SMC 0x136.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param mail_mask - Bits to clear.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyClearCry2Arm(SceSmSchedRequestId req_id, SceUInt32 mailbox_id, SceUInt32 mail_mask);

/** Previous VitaSDK name retained for backwards compatibility. */
#define ksceSblSmSchedProxyWriteCry2Arm ksceSblSmSchedProxyClearCry2Arm

/**
 * Does nothing on FW 3.60.
 *
 * @return Always 0x800F0425 on FW 3.60.
 */
int SceSblSmSchedProxyForKernel_1DFC8624(void);

/**
 * Does nothing on FW 3.60.
 *
 * @return Always 0x800F0425 on FW 3.60.
 */
int SceSblSmSchedProxyForKernel_984EC9D1(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SM_SCHED_H_ */
