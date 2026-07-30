/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr.h,SceKernelThreadMgr_stub}
 */

#ifndef _PSP2_KERNEL_THREADMGR_H_
#define _PSP2_KERNEL_THREADMGR_H_

#include <vitasdk/build_utils.h>
#include <psp2/kernel/threadmgr/callback.h>
#include <psp2/kernel/threadmgr/cond.h>
#include <psp2/kernel/threadmgr/eventflag.h>
#include <psp2/kernel/threadmgr/lw_cond.h>
#include <psp2/kernel/threadmgr/lw_mutex.h>
#include <psp2/kernel/threadmgr/msgpipe.h>
#include <psp2/kernel/threadmgr/mutex.h>
#include <psp2/kernel/threadmgr/rwlock.h>
#include <psp2/kernel/threadmgr/semaphore.h>
#include <psp2/kernel/threadmgr/signal.h>
#include <psp2/kernel/threadmgr/thread.h>
#include <psp2/kernel/threadmgr/vfp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelGetThreadInfoOpt {
	uint32_t size; //!< Number of bytes to copy to and from pInfo.
	uint32_t unused; //!< Ignored.
} SceKernelGetThreadInfoOpt;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelGetThreadInfoOpt); // size is from FW 3.60

typedef struct _sceKernelGetMutexInfo_opt {
	SceSize infoSize; //!< Number of bytes to copy to and from pInfo.
	SceUInt32 unused; //!< Ignored.
} _sceKernelGetMutexInfo_opt;
VITASDK_BUILD_ASSERT_EQ(8, _sceKernelGetMutexInfo_opt); // size is from FW 3.60

typedef struct sceKernelCreateLwMutex_opt {
	int initCount; //!< Initial lock count.
	const SceKernelLwMutexOptParam *pOptParam; //!< Optional lightweight mutex parameters.
	uint32_t unused0; //!< Ignored.
	uint32_t unused1; //!< Ignored.
} sceKernelCreateLwMutex_opt;
VITASDK_BUILD_ASSERT_EQ(0x10, sceKernelCreateLwMutex_opt); // size is from FW 3.60

typedef struct sceKernelRegisterThreadEventHandlerOpt {
	SceKernelThreadEventHandler *handler; //!< Contains a callback value of type ::SceKernelThreadEventHandler.
	void *common; //!< Value passed to the handler.
	int unused0; //!< Ignored.
	int unused1; //!< Ignored.
} sceKernelRegisterThreadEventHandlerOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, sceKernelRegisterThreadEventHandlerOpt); // size is from FW 3.60

typedef struct sceKernelCreateThreadForUser_opt {
	SceSize size; //!< Size of this structure.
	SceSize stackSize; //!< Thread stack size.
	SceUInt32 attr; //!< Thread attributes.
	SceInt32 cpuAffinityMask; //!< Thread CPU affinity mask.
	const SceKernelThreadOptParam *pOptParam; //!< Optional thread parameters.
	SceUIntVAddr callerAddress; //!< Wrapper call-site address used to identify the caller module.
} sceKernelCreateThreadForUser_opt;
VITASDK_BUILD_ASSERT_EQ(0x18, sceKernelCreateThreadForUser_opt); // size is from FW 3.60

/**
 * Creates a lightweight mutex through the raw user export.
 *
 * @param[in,out] pWork Lightweight mutex work area.
 * @param[in] pName Mutex name.
 * @param[in] attr Mutex attributes.
 * @param[in] pOpt Required wrapper option block.
 *
 * @return 0 on success, or < 0 on error.
 */
int __sceKernelCreateLwMutex(SceKernelLwMutexWork *pWork, const char *pName, unsigned int attr, sceKernelCreateLwMutex_opt *pOpt);

/**
 * Retrieves size-prefixed mutex information through the raw user export.
 *
 * @param[in] mutexid Mutex identifier.
 * @param[in,out] pInfo Mutex information buffer.
 * @param[in] pOpt Required option block selecting the number of bytes copied.
 *
 * @return 0 on success, or < 0 on error.
 */
int _sceKernelGetMutexInfo(SceUID mutexid, SceKernelMutexInfo *pInfo, const _sceKernelGetMutexInfo_opt *pOpt);

/**
 * Retrieves size-prefixed thread information through the raw user export.
 *
 * @param[in] thid Thread identifier.
 * @param[in,out] pInfo Thread information buffer.
 * @param[in] pOpt Required option block selecting the number of bytes copied.
 *
 * @return 0 on success, or < 0 on error.
 */
int _sceKernelGetThreadInfo(SceUID thid, SceKernelThreadInfo *pInfo, SceKernelGetThreadInfoOpt *pOpt);

/**
 * Registers a thread event handler through the raw user export.
 *
 * @param[in] name Handler name.
 * @param[in] threadId Target thread identifier.
 * @param[in] mask Event mask.
 * @param[in] pOpt Required option block containing the callback and common argument.
 *
 * @return Handler identifier on success, or < 0 on error.
 */
int _sceKernelRegisterThreadEventHandler(char *name, SceUID threadId, SceUInt32 mask, sceKernelRegisterThreadEventHandlerOpt *pOpt);

/**
 * Creates a user thread through the raw four-argument export.
 *
 * @param[in] pName Thread name.
 * @param[in] entry Thread entry point.
 * @param[in] initPriority Initial thread priority.
 * @param[in] pOpt Required wrapper option block.
 *
 * @return Thread identifier on success, or < 0 on error.
 */
SceUID sceKernelCreateThreadForUser(const char *pName, SceKernelThreadEntry entry, SceInt32 initPriority, const sceKernelCreateThreadForUser_opt *pOpt);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_H_ */
