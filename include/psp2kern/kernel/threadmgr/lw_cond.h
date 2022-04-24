/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/lw_cond.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_LW_COND_H_
#define _PSP2KERN_KERNEL_THREADMGR_LW_COND_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/threadmgr/lw_mutex.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  SceKernelLwCondWork {
	SceInt64 data[4];
} SceKernelLwCondWork;

typedef struct SceKernelLwCondOptParam {
	SceSize size;
} SceKernelLwCondOptParam;

typedef struct SceKernelLwCondInfo {
	SceSize size;
	SceUID  lwcond_id;
	char    name[0x20];
	int     attr;
	SceKernelLwCondWork *work;
	SceKernelLwMutexWork *lwmutex;
	int     num_wait_threads;
} SceKernelLwCondInfo;

int ksceKernelGetLwCondInfo(SceUID lwcond_id, SceKernelLwCondInfo *info);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_LW_COND_H_ */
