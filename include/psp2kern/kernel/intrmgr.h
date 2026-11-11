/**
 * \kernelgroup{SceIntrMgr}
 * \usage{psp2kern/kernel/intrmgr.h,SceIntrmgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_INTRMGR_H_
#define _PSP2KERN_KERNEL_INTRMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*SceKernelIntrHandler)(int unk, void *userCtx);
typedef int (*SceKernelSubIntrHandler)(void *subintr_arg, void *register_arg, unsigned char intr_priority);

/**
 * Primary interrupt-hook handler installed by ::ksceKernelRegisterIntrHookHandler.
 *
 * @param[in] intr_code - Registered interrupt code.
 * @param[in] user_ctx - Context supplied to ::ksceKernelRegisterIntrHandler.
 * @param[in] intr_priority - Registered interrupt priority.
 *
 * @return Interrupt-handler result.
 */
typedef int (*SceKernelIntrHookHandler)(int intr_code, void *user_ctx, int intr_priority);

typedef int (*SceKernelIntrOptHandlersCb1)(int intr_code, int subintr_code);
typedef int (*SceKernelIntrOptHandlersCb2)(int intr_code, int subintr_code, void *arg);
typedef int (*SceKernelIntrOptHandlersCb3)(int intr_code, int subintr_code, SceKernelSubIntrHandler handler, void *register_arg);

typedef struct SceKernelIntrOptHandlers {
	uint32_t size; // 0x28
	SceKernelIntrOptHandlersCb3 *pre_register_subintr_cb;
	SceKernelIntrOptHandlersCb3 *post_register_subintr_cb;
	SceKernelIntrOptHandlersCb1 *release_subintr_cb;
	SceKernelIntrOptHandlersCb1 *fptr0;
	SceKernelIntrOptHandlersCb1 *enable_subintr_cb;
	SceKernelIntrOptHandlersCb1 *disable_subintr_cb;
	SceKernelIntrOptHandlersCb2 *fptr3;
	SceKernelIntrOptHandlersCb1 *fptr4;
	SceKernelIntrOptHandlersCb1 *fptr5;
} SceKernelIntrOptHandlers;
VITASDK_BUILD_ASSERT_EQ(0x28, SceKernelIntrOptHandlers);

typedef struct SceKernelIntrOptParam {
	uint32_t size; // 0x14
	uint32_t num;
	SceKernelIntrOptHandlers *handlers;
	uint32_t unk_C;
	uint32_t unk_10;
} SceKernelIntrOptParam;
VITASDK_BUILD_ASSERT_EQ(0x14, SceKernelIntrOptParam);

int ksceKernelRegisterIntrHandler(int intr_code, const char *name, int interrupt_type,
	SceKernelIntrHandler handler, void *user_ctx, int priority, int target_cpu, SceKernelIntrOptParam *opt);
int ksceKernelReleaseIntrHandler(int intr_code);

int ksceKernelEnableIntr(int intr_code);
int ksceKernelDisableIntr(int intr_code);

int ksceKernelResumeIntr(int intr_code, int enabled);
int ksceKernelSuspendIntr(int intr_code, int *enabled);

int ksceKernelIsIntrPending(int intr_code);
int ksceKernelClearIntrPending(int intr_code);
int ksceKernelSetIntrPriority(int intr_code, int priority);
int ksceKernelGetIntrPriority(int intr_code, int *priority);
int ksceKernelSetIntrTarget(int intr_code, int cpu_target_list);
int ksceKernelGetIntrTarget(int intr_code, int *cpu_target_list);
int ksceKernelTriggerSGI(int intr_code, unsigned int target_list_filter, unsigned int cpu_target_list);
int ksceKernelIsIntrAllowedInCurrentContext(void);
int ksceKernelRegisterSubIntrHandler(int intr_code, int subintr_code, const char *name,
	SceKernelSubIntrHandler handler, void *register_arg);
int ksceKernelReleaseSubIntrHandler(int intr_code, int subintr_code);
int ksceKernelTriggerSubIntr(int intr_code, int subintr_code, void *subintr_arg);
int ksceKernelEnableSubIntr(int intr_code, int subintr_code);
int ksceKernelDisableSubIntr(int intr_code, int subintr_code);

int ksceKernelQueryIntrHandlerInfo(unsigned int intr_code, unsigned int a2, int a3);


/* For backwards compatibility */

#define ksceKernelMaskIntr(intr_code) ksceKernelDisableIntr(intr_code)
#define ksceKernelSetIntrMasked(intr_code, masked) ksceKernelEnableIntr(intr_code)
#define ksceKernelUnmaskIntr(intr_code) ksceKernelEnableIntr(intr_code)
#define ksceKernelGetIntrMasked ksceKernelSuspendIntr

/**
 * Query a subinterrupt controller's occurrence state.
 *
 * The controller-specific callback registered for \a intr_code supplies the
 * result. IntrMgr calls it while holding the parent interrupt's spinlock.
 *
 * @param[in] intr_code - Parent interrupt code, from 0 through 255.
 * @param[in] subintr_code - Subinterrupt index registered for the parent.
 *
 * @return The controller-specific result, ::SCE_KERNEL_ERROR_ILLEGAL_INTRCODE
 *         for an invalid parent or subinterrupt index, or
 *         ::SCE_KERNEL_ERROR_NOTFOUND_HANDLER when the parent, operation table,
 *         or occurrence callback is not registered.
 */
int ksceKernelIsSubInterruptOccurred(int intr_code, int subintr_code);

/**
 * Replace a registered primary interrupt handler with a hook.
 *
 * Only one hook can be installed for each interrupt. On success, IntrMgr saves
 * the current handler internally, writes it to \a old_handler, and atomically
 * installs \a new_handler. The hook receives the interrupt code, the context
 * supplied when the primary handler was registered, and the registered
 * interrupt priority.
 *
 * @param[in] intr_code - Interrupt code, from 0 through 255.
 * @param[in] new_handler - Required replacement handler.
 * @param[out] old_handler - Required output that receives the replaced handler.
 *
 * @return 0 on success, ::SCE_KERNEL_ERROR_ILLEGAL_CONTEXT when installing a
 *         hook is not allowed in the current context,
 *         ::SCE_KERNEL_ERROR_ILLEGAL_INTRCODE for an invalid interrupt code,
 *         ::SCE_KERNEL_ERROR_ILLEGAL_HANDLER for a NULL \a new_handler,
 *         ::SCE_KERNEL_ERROR_INVALID_ARGUMENT for a NULL \a old_handler,
 *         ::SCE_KERNEL_ERROR_FOUND_HANDLER when a hook is already installed,
 *         or ::SCE_KERNEL_ERROR_NOTFOUND_HANDLER when no primary handler is
 *         registered.
 */
int ksceKernelRegisterIntrHookHandler(int intr_code, SceKernelIntrHookHandler new_handler,
	SceKernelIntrHookHandler *old_handler);

/**
 * Remove an interrupt hook and restore the internally saved primary handler.
 *
 * @param[in] intr_code - Interrupt code, from 0 through 255.
 *
 * @return 0 on success, ::SCE_KERNEL_ERROR_ILLEGAL_CONTEXT when removing a
 *         hook is not allowed in the current context,
 *         ::SCE_KERNEL_ERROR_ILLEGAL_INTRCODE for an invalid interrupt code, or
 *         ::SCE_KERNEL_ERROR_NOTFOUND_HANDLER when no hook is installed.
 */
int ksceKernelReleaseIntrHookHandler(int intr_code);

/**
 * Call a subinterrupt controller's resume operation.
 *
 * The controller-specific callback defines what \a state means and which
 * results it returns for success or error.
 *
 * @param[in] intr_code - Parent interrupt code, from 0 through 255.
 * @param[in] subintr_code - Subinterrupt index registered for the parent.
 * @param[in] state - Controller-specific resume state.
 *
 * @return The controller-specific result, ::SCE_KERNEL_ERROR_ILLEGAL_INTRCODE
 *         for an invalid parent or subinterrupt index, or
 *         ::SCE_KERNEL_ERROR_NOTFOUND_HANDLER when the parent, operation table,
 *         or resume callback is not registered.
 */
int ksceKernelResumeSubIntr(int intr_code, int subintr_code, int state);

/**
 * Call a subinterrupt controller's suspend operation.
 *
 * The controller-specific callback defines how \a arg is used and which
 * results it returns for success or error. \a arg must be non-NULL. For example,
 * SceSdif's implementation ignores \a arg and performs the same action as
 * disabling that subinterrupt.
 *
 * @param[in] intr_code - Parent interrupt code, from 0 through 255.
 * @param[in] subintr_code - Subinterrupt index registered for the parent.
 * @param[in,out] arg - Required controller-specific argument.
 *
 * @return The controller-specific result, ::SCE_KERNEL_ERROR_ILLEGAL_INTRCODE
 *         for an invalid parent or subinterrupt index, 0x80020001 for a NULL
 *         \a arg, or ::SCE_KERNEL_ERROR_NOTFOUND_HANDLER when the parent,
 *         operation table, or suspend callback is not registered.
 */
int ksceKernelSuspendSubIntr(int intr_code, int subintr_code, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_INTRMGR_H_ */
