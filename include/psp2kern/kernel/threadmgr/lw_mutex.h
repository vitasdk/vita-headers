/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/lw_mutex.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2_KERNEL_THREADMGR_LW_MUTEX_H_
#define _PSP2_KERNEL_THREADMGR_LW_MUTEX_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct  SceKernelLwMutexWork {
	SceInt64 data[4];
} SceKernelLwMutexWork;

typedef struct SceKernelLwMutexOptParam {
	SceSize size;
} SceKernelLwMutexOptParam;

int ksceKernelInitializeFastMutex(void *mutex, const char *name, int unk0, int unk1);
int ksceKernelLockFastMutex(void *mutex);
int ksceKernelUnlockFastMutex(void *mutex);
int ksceKernelDeleteFastMutex(void *mutex);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_LW_MUTEX_H_ */
