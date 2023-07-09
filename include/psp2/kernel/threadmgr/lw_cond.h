/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/lw_cond.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_LW_COND_H_
#define _PSP2_KERNEL_THREADMGR_LW_COND_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2/kernel/threadmgr/lw_mutex.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct	SceKernelLwCondWork {
	SceInt32 data[4];
} SceKernelLwCondWork;
VITASDK_BUILD_ASSERT_EQ(0x10, SceKernelLwCondWork);

typedef struct SceKernelLwCondOptParam {
	SceSize	size;
} SceKernelLwCondOptParam;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelLwCondOptParam);

int sceKernelCreateLwCond(SceKernelLwCondWork *pWork, const char *pName, unsigned int attr, SceKernelLwMutexWork *pLwMutex, const SceKernelLwCondOptParam *pOptParam);
int sceKernelDeleteLwCond(SceKernelLwCondWork *pWork);
int sceKernelSignalLwCond(SceKernelLwCondWork *pWork);
int sceKernelSignalLwCondAll(SceKernelLwCondWork *pWork);
int sceKernelSignalLwCondTo(SceKernelLwCondWork *pWork, SceUID threadId);
int sceKernelWaitLwCond(SceKernelLwCondWork *pWork,  unsigned int *pTimeout);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_LW_COND_H_ */
