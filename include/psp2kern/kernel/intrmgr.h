/**
 * \kernelgroup{SceIntrMgr}
 * \usage{psp2kern/kernel/intrmgr.h,SceIntrmgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_INTRMGR_H_
#define _PSP2KERN_KERNEL_INTRMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*SceKernelIntrHandler)(int unk, void *userCtx);
typedef int (*SceKernelSubIntrHandler)(void *subintr_arg, void *register_arg, unsigned char intr_priority);

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

typedef struct SceKernelIntrOptParam {
	uint32_t size; // 0x14
	uint32_t num;
	SceKernelIntrOptHandlers *handlers;
	uint32_t unk_C;
	uint32_t unk_10;
} SceKernelIntrOptParam;

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
int ksceKernelIsIntrAllowedInCurrentContext(int intr_code);
int ksceKernelRegisterSubIntrHandler(int intr_code, int subintr_code, const char *name,
	SceKernelSubIntrHandler handler, void *register_arg);
int ksceKernelReleaseSubIntrHandler(int intr_code, int subintr_code);
int ksceKernelTriggerSubIntr(int intr_code, int subintr_code, void *subintr_arg);
int ksceKernelEnableSubIntr(int intr_code, int subintr_code);
int ksceKernelDisableSubIntr(int intr_code, int subintr_code);

#define ksceKernelMaskIntr(intr_code) ksceKernelDisableIntr(intr_code)
#define ksceKernelSetIntrMasked(intr_code, masked) ksceKernelEnableIntr(intr_code)
#define ksceKernelUnmaskIntr(intr_code) ksceKernelEnableIntr(intr_code)
#define ksceKernelGetIntrMasked ksceKernelSuspendIntr

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_INTRMGR_H_ */

