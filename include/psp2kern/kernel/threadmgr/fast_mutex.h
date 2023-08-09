/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/fast_mutex.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_FAST_MUTEX_H_
#define _PSP2KERN_KERNEL_THREADMGR_FAST_MUTEX_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelFastMutex {
	SceUInt8 data[0x40];
} SceKernelFastMutex;
VITASDK_BUILD_ASSERT_EQ(0x40, SceKernelFastMutex);


int ksceKernelInitializeFastMutex(SceKernelFastMutex *fast_mutex, const char *name, int attr, void *opt);
int ksceKernelFinalizeFastMutex(SceKernelFastMutex *fast_mutex);

int ksceKernelLockFastMutex(SceKernelFastMutex *fast_mutex);
int ksceKernelTryLockFastMutex(SceKernelFastMutex *fast_mutex);
int ksceKernelUnlockFastMutex(SceKernelFastMutex *fast_mutex);

int ksceKernelGetFastMutexInfo(SceKernelFastMutex *fast_mutex, void *info);


/* backward compatibility */

#define ksceKernelDeleteFastMutex(__fast_mutex__) ksceKernelFinalizeFastMutex((__fast_mutex__))


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_FAST_MUTEX_H_ */
