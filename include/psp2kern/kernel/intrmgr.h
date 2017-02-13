/**
 * \kernelgroup{SceIntrMgr}
 * \usage{psp2kern/kernel/intrmgr.h,?}
 */

#ifndef _PSP2_KERNEL_INTRMGR_H_
#define _PSP2_KERNEL_INTRMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*intr_callback)(int code, int arg);

typedef struct reg_intr_opt2 {
	uint32_t size; // 0x28
	uint32_t unk_4;
	uint32_t unk_8;
	uint32_t unk_C;
	intr_callback *fptr0; // function pointer
	intr_callback *fptr1; // function pointer
	intr_callback *fptr2; // function pointer
	uint32_t unk_1C;
	uint32_t unk_20;
	uint32_t unk_24;
} reg_intr_opt2;

typedef struct reg_intr_opt {
	uint32_t size; // 0x14
	uint32_t num;
	reg_intr_opt2 *opt2;
	uint32_t unk_C;
	uint32_t unk_10;
} reg_intr_opt;

typedef int (*intr_callback_func)(int unk, void *userCtx);

int ksceKernelRegisterIntrHandler(int intr_code, const char *name, int interrupt_type,
	intr_callback_func *func, void *userCtx, int priority, int targetcpu, reg_intr_opt *opt);

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_INTRMGR_H_ */

