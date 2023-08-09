/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/lw_mutex.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_LW_MUTEX_H_
#define _PSP2KERN_KERNEL_THREADMGR_LW_MUTEX_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceKernelLwMutexInfo {
	SceSize size;
	SceUID mtxid;
	char name[0x20];
	int attr;
	SceKernelLwMutexWork *work;
	int init_count;
	int current_count;
	SceUID current_owner_id;
	SceUInt32 num_wait_threads;
} SceKernelLwMutexInfo;
VITASDK_BUILD_ASSERT_EQ(0x40, SceKernelLwMutexInfo);

int ksceKernelGetLwMutexInfo(SceUID lwmtxid, SceKernelLwMutexInfo *info);

int ksceKernelInitializeFastMutex(void *mutex, const char *name, int unk0, int unk1);
int ksceKernelLockFastMutex(void *mutex);
int ksceKernelUnlockFastMutex(void *mutex);
int ksceKernelDeleteFastMutex(void *mutex);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_LW_MUTEX_H_ */
