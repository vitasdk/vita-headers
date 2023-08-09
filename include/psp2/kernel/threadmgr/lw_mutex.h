/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/lw_mutex.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_LW_MUTEX_H_
#define _PSP2_KERNEL_THREADMGR_LW_MUTEX_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif


int sceKernelCreateLwMutex(SceKernelLwMutexWork *pWork,const char *pName, unsigned int attr, int initCount, const SceKernelLwMutexOptParam *pOptParam);
int sceKernelDeleteLwMutex(SceKernelLwMutexWork *pWork);
int sceKernelLockLwMutex(SceKernelLwMutexWork *pWork, int lockCount, unsigned int *pTimeout);
int sceKernelTryLockLwMutex(SceKernelLwMutexWork *pWork, int lockCount);
int sceKernelUnlockLwMutex(SceKernelLwMutexWork *pWork, int unlockCount);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_LW_MUTEX_H_ */
