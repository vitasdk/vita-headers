/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu/corelock.h}
 */


#ifndef _PSP2KERN_KERNEL_CPU_CORELOCK_H_
#define _PSP2KERN_KERNEL_CPU_CORELOCK_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceCorelockContext {
	int lock;
	int16_t core_count;
	int16_t last_wait_core;
} SceCorelockContext;
VITASDK_BUILD_ASSERT_EQ(8, SceCorelockContext);

void ksceKernelCorelockInitialize(SceCorelockContext *ctx);

void ksceKernelCorelockLock(SceCorelockContext *ctx, SceUInt32 core);
void ksceKernelCorelockUnlock(SceCorelockContext *ctx);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_CPU_CORELOCK_H_ */
