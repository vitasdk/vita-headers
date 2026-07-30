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
 *                       ::ksceSblSmSchedProxyEnableCry2ArmInterrupt.
 * @param status - Scheduler status. FW 3.60 consumers clear bit 0x8 before
 *                 testing for ::SCE_SM_STATUS_RUNNING; the bit's meaning is
 *                 not known.
 * @param result - Secure-module result or error code.
 *
 * The handler's return value is ignored on FW 3.60.
 */
typedef int sceSblSmSchedProxyIntrHandler(SceSmSchedRequestId req_id, int interrupt_index, int callback_arg, int status, int result);

/**
 * Secure-module lifecycle states.
 *
 * FW 3.60 SceSblAuthMgr and SceSblSsSmComm clear bit 0x8 before comparing a
 * callback status with ::SCE_SM_STATUS_RUNNING. The meaning of that bit is not
 * known.
 */
typedef enum SceSmStatus {
	SCE_SM_STATUS_SUSPENDED              = 0x1,
	SCE_SM_STATUS_RUNNING                = 0x2,
	SCE_SM_STATUS_STOPPED                = 0x3,
	SCE_SM_STATUS_START_RESUME_REQUESTED = 0x6,
	SCE_SM_STATUS_SUSPENDING             = 0x7,
	SCE_SM_STATUS_SUSPEND_REQUESTED      = 0xB
} SceSmStatus;

/**
 * Sends a value to a secure-module scheduler mailbox through SMC 0x133.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param mailval - Value to send.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedCallFunc(SceSmSchedRequestId req_id, int mailbox_id, SceUInt32 mailval);

/**
 * Requests an F00D status change through SMC 0x130.
 *
 * @param req_id - Scheduler request ID.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyChangeF00DStatus(SceSmSchedRequestId req_id);

/**
 * Disables a scheduler interrupt handler through SMC 0x139.
 *
 * @param req_id - Scheduler request ID.
 * @param interrupt_index - Interrupt index in the range 0 through 3.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyDisableCry2ArmInterrupt(SceSmSchedRequestId req_id, int interrupt_index);

/**
 * Registers a scheduler interrupt handler through SMC 0x138.
 *
 * @param req_id - Scheduler request ID.
 * @param interrupt_index - Interrupt index in the range 0 through 3.
 * @param cb - Required interrupt handler.
 * @param callback_arg - Value passed unchanged as the handler's third
 *                       argument.
 *
 * If a notification is already pending, the handler is invoked before this
 * function executes the secure-monitor command.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyEnableCry2ArmInterrupt(SceSmSchedRequestId req_id, int interrupt_index, sceSblSmSchedProxyIntrHandler *cb, int callback_arg);

/**
 * Executes an indexed F00D command through SMC 0x13C.
 *
 * All four arguments are forwarded to the secure monitor. On FW 3.60,
 * SceSdif uses command index 3 during a host-controller reset and SceSblSsMgr
 * uses command index 4 during a system event; both pass zero for the remaining
 * arguments. Their purposes are unknown.
 *
 * @param command_index - Secure-monitor command index.
 * @param arg1 - First opaque command argument.
 * @param arg2 - Second opaque command argument.
 * @param arg3 - Third opaque command argument.
 *
 * @return Secure-monitor result.
 */
int ksceSblSmSchedProxyExecuteF00DCommand(SceUInt32 command_index, int arg1, int arg2, int arg3);

/**
 * Reads the ARM-to-Cry command register through SMC 0x134.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param pMailval - Required output for the register value.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyGetCommandF00DRegister(SceSmSchedRequestId req_id, int mailbox_id, SceUInt32 *pMailval);

/**
 * Queries a secure-module request through SMC 0x12F.
 *
 * @param req_id - Scheduler request ID.
 * @param result - Required output for the secure-module result and scheduler
 *                 status. Unlike ::ksceSblSmSchedProxyWait, this function does
 *                 not release the request record.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyGetStatus(SceSmSchedRequestId req_id, SceSblSmCommPair *result);

/**
 * Initializes the scheduler proxy.
 *
 * Initialization is performed only when called on CPU 0.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSmSchedProxyInitialize(void);

/**
 * Starts a secure-module scheduler request through SMC 0x12D.
 *
 * @param priority - Boolean priority: 0 for high priority, 1 for low priority.
 * @param sm_self_paddr - Physical address of an array of ::SceKernelPARange
 *                        entries. The pointer type is retained for source
 *                        compatibility.
 * @param num_pa_range - Number of entries in the physical-address range array.
 * @param invoke_input - Optional four-word input copied verbatim. NULL
 *                       forwards four zero words.
 * @param pCtx - Required launch context. FW 3.60 reads only self_type,
 *               media_type, and the program authority ID and capability from
 *               spawner_self_auth_info.
 * @param pReqId - Required scheduler request-ID output.
 *
 * @return Secure-monitor result or a negative scheduler/kernel error.
 */
int ksceSblSmSchedProxyInvoke(SceBool priority, void *sm_self_paddr, SceUInt32 num_pa_range, SceSmInvokeDataBlockInput *invoke_input, SceSblSmCommContext130 *pCtx, SceSmSchedRequestId *pReqId);

/**
 * Reads a Cry-to-ARM mailbox through SMC 0x137.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param pMailval - Required output for the mailbox value.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyReadCry2Arm(SceSmSchedRequestId req_id, int mailbox_id, SceUInt32 *pMailval);

/**
 * Uninitializes the scheduler proxy.
 *
 * Uninitialization is performed only when called on CPU 0.
 *
 * @return Secure-monitor result or 0 when called on another CPU.
 */
int ksceSblSmSchedProxyUninitialize(void);

/**
 * Waits for a secure-module request to complete through SMC 0x12E.
 *
 * @param req_id - Scheduler request ID.
 * @param result - Required output for the secure-module result and scheduler
 *                 status. The request record is released before this function
 *                 returns.
 *
 * @return Secure-monitor result or a negative scheduler/kernel error.
 */
int ksceSblSmSchedProxyWait(SceSmSchedRequestId req_id, SceSblSmCommPair *result);

/**
 * Writes an ARM-to-Cry mailbox through SMC 0x135.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param mailval - Value to write.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyWriteArm2Cry(SceSmSchedRequestId req_id, int mailbox_id, SceUInt32 mailval);

/**
 * Writes a Cry-to-ARM mailbox through SMC 0x136.
 *
 * @param req_id - Scheduler request ID.
 * @param mailbox_id - Mailbox ID in the range 1 through 3.
 * @param mailval - Value to write.
 *
 * @return Secure-monitor result or a negative scheduler validation error.
 */
int ksceSblSmSchedProxyWriteCry2Arm(SceSmSchedRequestId req_id, int mailbox_id, SceUInt32 mailval);

/**
 * No-op export on FW 3.60.
 *
 * @return 0x800F0425.
 */
int SceSblSmSchedProxyForKernel_1DFC8624(void);

/**
 * No-op export on FW 3.60.
 *
 * @return 0x800F0425.
 */
int SceSblSmSchedProxyForKernel_984EC9D1(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SM_SCHED_H_ */
