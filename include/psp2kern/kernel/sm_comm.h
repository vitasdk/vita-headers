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

typedef int SceSblSmCommId; //!< Signed VitaSDK spelling of ::SceSmSchedRequestId; -1 represents no active request.

typedef struct SceSblSmCommPair {
	int result; //!< Secure-module result or error code.
	int status; //!< One of ::SceSmStatus.
} SceSblSmCommPair;
VITASDK_BUILD_ASSERT_EQ(8, SceSblSmCommPair);

/**
 * Optional data forwarded when starting a secure module.
 *
 * The FW 3.60 scheduler proxy copies all four words verbatim. Their individual
 * purposes are unknown.
 */
typedef struct SceSmInvokeDataBlockInput {
	int unk0;
	int unk4;
	int unk8;
	int unkC;
} SceSmInvokeDataBlockInput;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSmInvokeDataBlockInput); // size is from FW 3.60

typedef struct SceSblSmCommContext130 {
	SceUInt32 unk_0;                              //!< Ignored on FW 3.60.
	SceUInt32 self_type;                          //!< Forwarded unchanged on FW 3.60.
	SceSelfAuthInfo spawner_self_auth_info;       //!< Its program authority ID and capability are
	                                              //!< forwarded on FW 3.60.
	SceSelfAuthInfo spawned_self_auth_info;       //!< Ignored on FW 3.60.
	SceUInt32 media_type;                         //!< Forwarded unchanged on FW 3.60.
	SceUInt32 unk_0x12C;                          //!< Ignored on FW 3.60.
} SceSblSmCommContext130;
VITASDK_BUILD_ASSERT_EQ(0x130, SceSblSmCommContext130); // size is from FW 0.931.010-3.740.011

/**
 * Starts a secure module from a file.
 *
 * @param priority - Boolean priority: 0 for high priority, 1 for low priority.
 * @param sm_self_path - Path to the secure module SELF.
 * @param invoke_input - Optional data forwarded to the scheduler proxy. Passing
 *                      NULL forwards four zero words.
 * @param ctx_130 - Pointer to a structure with a layout equivalent to ::SceSblSmCommContext130.
 * @param req_id - Required output that receives a value of type ::SceSmSchedRequestId.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSmCommStartSmFromFile(SceUInt32 priority, const char *sm_self_path, const SceSmInvokeDataBlockInput *invoke_input, SceAuthInfo *ctx_130, SceSblSmCommId *req_id);

/**
 * Starts a secure module from a memory image.
 *
 * @param priority - Boolean priority: 0 for high priority, 1 for low priority.
 * @param sm_self - Secure module SELF image. The image may not exceed 0x20000 bytes.
 * @param sm_self_size - Size of the secure module SELF image.
 * @param invoke_input - Pointer-sized value containing either 0 or a pointer to
 *                      ::SceSmInvokeDataBlockInput. The integer type is retained
 *                      for backwards compatibility.
 * @param ctx_130 - Required secure-module launch context.
 * @param req_id - Required scheduler request-ID output.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSmCommStartSmFromData(SceBool priority, const void *sm_self, SceSize sm_self_size, int invoke_input, SceSblSmCommContext130 *ctx_130, SceSmSchedRequestId *req_id);

/**
 * Executes a function in a running secure module.
 *
 * @param req_id - Secure-module scheduler request ID.
 * @param func_id - Function ID sent to the secure module.
 * @param pResponse - Optional output for the secure-module response value.
 * @param pData - In/out payload buffer. Required when \p dataSize is nonzero.
 * @param dataSize - Payload size, which may not exceed 0xFC0 bytes.
 *
 * @return 0 on transport success, < 0 on transport error. A secure-module
 *         response is returned separately through \p pResponse.
 */
int ksceSblSmCommCallFunc(SceSblSmCommId req_id, SceUInt32 func_id, SceUInt32 *pResponse, void *pData, SceSize dataSize);

/**
 * Stops a running secure module and releases its communication slot.
 *
 * @param req_id - Secure-module scheduler request ID.
 * @param result - Required output for the secure-module result and scheduler
 *                 status.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblSmCommStopSm(SceSblSmCommId req_id, SceSblSmCommPair *result);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SM_COMM_H_ */
