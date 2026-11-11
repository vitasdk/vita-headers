/**
 * \kernelgroup{SceSblSmComm}
 * \usage{psp2kern/kernel/sm_comm.h,SceSblSmCommForKernel_stub}
 */

#ifndef _PSP2KERN_KERNEL_SM_COMM_H_
#define _PSP2KERN_KERNEL_SM_COMM_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SceUInt32 SceSmSchedRequestId; //!< Secure-module scheduler request ID.

typedef int SceSblSmCommId; //!< Signed VitaSDK type for ::SceSmSchedRequestId; -1 means no active request.

typedef struct SceSblSmCommPair {
	int result; //!< Result or error returned by the secure module.
	int status; //!< Secure-module scheduler state; one of ::SceSmStatus.
} SceSblSmCommPair;
VITASDK_BUILD_ASSERT_EQ(8, SceSblSmCommPair);

/**
 * Startup data whose meaning is defined by the secure module.
 *
 * The FW 3.60 scheduler copies all four words unchanged into the secure-module
 * startup command. It does not interpret the words; their meanings are defined
 * by the secure module being started. QAF supplies `{ 0xFF, 0, 0, 0 }`, while every
 * other reviewed FW 3.60 caller passes NULL and therefore supplies four zeros.
 */
typedef struct SceSmInvokeDataBlockInput {
	SceUInt32 words[4];
} SceSmInvokeDataBlockInput;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSmInvokeDataBlockInput); // size is from FW 3.60

/**
 * Identity and media context used to start a secure module.
 *
 * FW 3.60 forwards only \a self_type, \a media_type, and the program
 * authority ID and capability from \a spawner_self_auth_info. The remaining
 * fields are not forwarded or modified. All reviewed SceSblSmComm callers
 * initialize the structure to zero, set bits 0-3 of \a self_type to 2,
 * and obtain \a media_type from ACMgr or use value 2 for an embedded image.
 * Because both SceSblSmComm start exports supply physical image ranges, the
 * scheduler invocation tag in bits 12 through 15 of \a self_type must be zero
 * on FW 3.60.
 */
typedef struct SceSblSmCommContext130 {
	SceUInt32 reserved0;                          //!< Ignored on FW 3.60.
	SceUInt32 self_type;                          //!< SELF type and scheduler invocation tag.
	SceSelfAuthInfo spawner_self_auth_info;       //!< The program authority ID and capability are forwarded.
	SceSelfAuthInfo reserved_self_auth_info;      //!< Ignored on FW 3.60.
	SceUInt32 media_type;                         //!< Media type of the secure-module SELF.
	SceUInt32 reserved1;                          //!< Ignored on FW 3.60.
} SceSblSmCommContext130;
VITASDK_BUILD_ASSERT_EQ(0x130, SceSblSmCommContext130); // size is from FW 0.931.010-3.740.011

/**
 * Starts a secure module from a file.
 *
 * This function reads at most 0x20000 bytes, copies the SELF into private
 * kernel memory, converts that image to physical ranges, and starts a scheduler
 * request. You may reuse or free the path, startup data, and context after
 * this function returns. A successful request remains active until
 * ::ksceSblSmCommStopSm is called.
 *
 * This function blocks and must be called from a kernel thread, not interrupt
 * context. FW 3.60 supports at most 32 SceSblSmComm requests. It reserves a
 * slot before validating or loading the image and does not restore the slot
 * semaphore after a failed start. Repeated failures can therefore prevent
 * further starts until the module is reloaded.
 *
 * @param priority - 0 for high priority, 1 for low priority.
 *                   Other values are rejected with 0x800F0416 on FW 3.60.
 * @param sm_self_path - Path to the secure module SELF.
 * @param invoke_input - Optional data forwarded to the scheduler proxy. Passing
 *                      NULL forwards four zero words.
 * @param ctx_130 - Required pointer to a structure with a layout equivalent to
 *                  ::SceSblSmCommContext130. Still declared as ::SceAuthInfo
 *                  for backwards compatibility.
 * @param req_id - Required request-ID output. Still declared as
 *                 ::SceSblSmCommId for backwards compatibility. Only use the
 *                 value when the function succeeds.
 *
 * @return 0 on success. Returns 0x800F0016 when the file exceeds 0x20000
 *         bytes, 0x800F0005 after a short read, 0x800F000C after an image
 *         allocation failure, or another negative scheduler, I/O, or kernel
 *         error.
 */
int ksceSblSmCommStartSmFromFile(SceUInt32 priority, const char *sm_self_path, const SceSmInvokeDataBlockInput *invoke_input, SceAuthInfo *ctx_130, SceSblSmCommId *req_id);

/**
 * Starts a secure module from a memory image.
 *
 * The supplied image is copied into private kernel memory before the scheduler
 * request is created. You may reuse or free the image, startup data, and
 * context after this function returns. A successful request remains active
 * until ::ksceSblSmCommStopSm is called.
 *
 * Like ::ksceSblSmCommStartSmFromFile, this function blocks and must be called
 * from a kernel thread, not interrupt context. It shares the same 32-request
 * limit and failure to restore the slot semaphore after a failed start.
 *
 * @param priority - 0 for high priority, 1 for low priority.
 *                   Other values are rejected with 0x800F0416 on FW 3.60.
 * @param sm_self - Required secure-module SELF image when \a sm_self_size is
 *                  nonzero.
 * @param sm_self_size - Size of the secure module SELF image.
 * @param invoke_input - Optional startup data. Passing NULL forwards four zero
 *                      words.
 * @param ctx_130 - Required secure-module launch context.
 * @param req_id - Required request-ID output. Only use the value when the
 *                 function succeeds.
 *
 * @return 0 on success. Returns 0x800F0016 when \a sm_self_size exceeds
 *         0x20000, 0x800F000C after an image allocation failure, or another
 *         negative scheduler or kernel error.
 */
int ksceSblSmCommStartSmFromData(SceBool priority, const void *sm_self, SceSize sm_self_size, const SceSmInvokeDataBlockInput *invoke_input, const SceSblSmCommContext130 *ctx_130, SceSmSchedRequestId *req_id);

/**
 * Executes a function in a running secure module.
 *
 * FW 3.60 copies exactly \a data_size bytes into the request's private
 * 0x1000-byte command buffer, sends \a func_id through scheduler mailbox 1,
 * waits for completion, and copies the same number of bytes back. You may
 * reuse or free the data and response buffers after this function returns.
 * The return value reports transport success or failure, not the secure
 * module's result.
 *
 * A request has only one command buffer and completion event flag, with no
 * per-request lock. Do not run calls using the same \a req_id concurrently;
 * this includes calls to ::ksceSblSmCommStopSm.
 * Callers must also enforce the 0xFC0 limit themselves: the FW 3.60 size check
 * adds 0x40 before comparing against 0x1000 and does not guard that addition
 * against unsigned overflow.
 *
 * Function ID 0xFFFFFFFF is reserved for the asynchronous stop protocol. That
 * value makes the function return after sending the mailbox command, without
 * waiting for a reply or copying data back. Use ::ksceSblSmCommStopSm instead.
 * For an ordinary command, FW 3.60 maps mailbox completion values 2, 4, and 8
 * to 0x800F0002, 0x800F0001, and 0x800F0005 respectively; another nonzero
 * completion value is mapped to 0x800F0016.
 *
 * @param req_id - Secure-module scheduler request ID.
 * @param func_id - Function ID sent to the secure module.
 * @param response - Optional output for the secure-module response value.
 * @param data - In/out payload buffer. Required when \p data_size is nonzero.
 * @param data_size - Payload size in bytes, which may not exceed 0xFC0.
 *
 * @return 0 on transport success. Returns 0x800F0026 if \a req_id does not
 *         identify an active communication slot, 0x800F000C when the checked
 *         command size is too large, or another negative scheduler or kernel
 *         error. On transport success the secure-module result is returned
 *         separately through \a response.
 */
int ksceSblSmCommCallFunc(SceSblSmCommId req_id, SceUInt32 func_id, SceUInt32 *response, void *data, SceSize data_size);

/**
 * Stops a running secure module and releases its communication slot.
 *
 * FW 3.60 sends the asynchronous function ID 0xFFFFFFFF, frees the command
 * buffer and completion event, releases the SceSblSmComm slot, and waits for
 * the scheduler's final result. Scheduler error 0x800F0429 means the request
 * is treated as already stopped; cleanup and the wait still proceed.
 * Once this cleanup begins, \a req_id must not be reused even if the
 * final wait returns an error.
 *
 * @param req_id - Secure-module scheduler request ID.
 * @param result - Required output. Its first word receives the secure-module
 *                 result and its second word receives the final scheduler
 *                 state.
 *
 * @return 0 on transport and cleanup success, or a negative command,
 *         scheduler, semaphore, or kernel error.
 */
int ksceSblSmCommStopSm(SceSblSmCommId req_id, SceSblSmCommPair *result);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SM_COMM_H_ */
