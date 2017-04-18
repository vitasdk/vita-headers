/**
 * \kernelgroup{SceIntrMgr}
 * \usage{psp2kern/kernel/intrmgr.h,SceIntrmgrForDriver_stub}
 */

#ifndef _PSP2_KERNEL_INTRMGR_H_
#define _PSP2_KERNEL_INTRMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*SceKernelIntrOptParam2Callback)(int intr_code, int subintr_code);

typedef struct SceKernelIntrOptParam2 {
	uint32_t size; // 0x28
	uint32_t unk_4;
	uint32_t unk_8;
	uint32_t unk_C;
	SceKernelIntrOptParam2Callback *fptr0; // function pointer
	SceKernelIntrOptParam2Callback *enable_subinterrupt_cb;
	SceKernelIntrOptParam2Callback *fptr2; // function pointer
	uint32_t unk_1C;
	uint32_t unk_20;
	uint32_t unk_24;
} SceKernelIntrOptParam2;

typedef struct SceKernelIntrOptParam {
	uint32_t size; // 0x14
	uint32_t num;
	SceKernelIntrOptParam2 *opt2;
	uint32_t unk_C;
	uint32_t unk_10;
} SceKernelIntrOptParam;

typedef int (*SceKernelIntrHandler)(int unk, void *userCtx);
typedef int (*SceKernelSubIntrHandler)(void *arg, int unk0, int unk1);

int ksceKernelRegisterIntrHandler(int intr_code, const char *name, int interrupt_type,
	SceKernelIntrHandler *handler, void *userCtx, int priority, int targetcpu, SceKernelIntrOptParam *opt);
int ksceKernelReleaseIntrHandler(int intr_code);
int ksceKernelMaskIntr(int intr_code);
int ksceKernelUnmaskIntr(int intr_code);
int ksceKernelSetIntrMasked(int intr_code, int masked);
int ksceKernelGetIntrMasked(int intr_code, int *masked);
int ksceKernelIsIntrPending(int intr_code);
int ksceKernelClearIntrPending(int intr_code);
int ksceKernelSetIntrPriority(int intr_code, unsigned char priority);
int ksceKernelSetIntrTarget(int intr_code, int cpu_target_list);
int ksceKernelTriggerSGI(int intr_code, unsigned int target_list_filter, unsigned int cpu_target_list);
int ksceKernelIsIntrAllowedInCurrentContext(int intr_code);
int ksceKernelRegisterSubIntrHandler(int intr_code, int subintr_code, const char *name,
	SceKernelSubIntrHandler handler, void *register_arg);
int ksceKernelTriggerSubIntr(int intr_code, int subintr_code, void *subintr_arg);
int ksceKernelEnableSubIntr(int intr_code, int subintr_code);
int ksceKernelDisableSubIntr(int intr_code, int subintr_code);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_INTRMGR_H_ */

