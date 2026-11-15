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

typedef struct _sceKernelGetThreadInfo_opt {
	SceSize info_size; //!< Number of bytes to copy to and from info.
	SceUInt32 unused; //!< Ignored; the public wrapper leaves this word uninitialized.
} _sceKernelGetThreadInfo_opt;
VITASDK_BUILD_ASSERT_EQ(8, _sceKernelGetThreadInfo_opt); // size is from FW 3.60

typedef struct _sceKernelGetMutexInfo_opt {
	SceSize info_size; //!< Number of bytes to copy to and from info.
	SceUInt32 unused; //!< Ignored; the public wrapper leaves this word uninitialized.
} _sceKernelGetMutexInfo_opt;
VITASDK_BUILD_ASSERT_EQ(8, _sceKernelGetMutexInfo_opt); // size is from FW 3.60

typedef struct sceKernelCreateLwMutex_opt {
	SceInt32 init_count; //!< Initial lock count.
	const SceKernelLwMutexOptParam *opt_param; //!< Optional lightweight mutex parameters.
	SceUInt32 unused[2]; //!< Ignored.
} sceKernelCreateLwMutex_opt;
VITASDK_BUILD_ASSERT_EQ(0x10, sceKernelCreateLwMutex_opt); // size is from FW 3.60

typedef struct sceKernelRegisterThreadEventHandlerOpt {
	SceKernelThreadEventHandler handler; //!< Event callback.
	void *common; //!< Value passed to the handler.
	SceUInt32 unused[2]; //!< Ignored.
} sceKernelRegisterThreadEventHandlerOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, sceKernelRegisterThreadEventHandlerOpt); // size is from FW 3.60

typedef struct sceKernelCreateThreadForUser_opt {
	SceSize size; //!< Ignored on FW 3.60; the public wrapper sets it to 0x18.
	SceSize stack_size; //!< Thread stack size.
	SceUInt32 attr; //!< Thread attributes.
	SceInt32 cpu_affinity_mask; //!< CPU affinity encoded in bits 16-19.
	const SceKernelThreadOptParam *opt_param; //!< Optional thread parameters.
	SceUIntVAddr caller_address; //!< Wrapper return address used to identify the caller module.
} sceKernelCreateThreadForUser_opt;
VITASDK_BUILD_ASSERT_EQ(0x18, sceKernelCreateThreadForUser_opt); // size is from FW 3.60

/**
 * Creates a lightweight mutex through the raw user export.
 *
 * The work area must be 8-byte aligned and remain valid until the lightweight
 * mutex is deleted.
 *
 * @param[in,out] work Lightweight mutex work area.
 * @param[in] name Required mutex name, limited to 31 bytes plus NUL.
 * @param[in] attr Mutex attributes.
 * @param[in] opt Required 0x10-byte wrapper option block. Only
 * ::sceKernelCreateLwMutex_opt::init_count and
 * ::sceKernelCreateLwMutex_opt::opt_param are used; the other fields are ignored.
 *
 * @return 0 on success, or < 0 on error.
 */
int __sceKernelCreateLwMutex(SceKernelLwMutexWork *work, const char *name, SceUInt32 attr, const sceKernelCreateLwMutex_opt *opt);

/**
 * Gets mutex information through the raw user export.
 *
 * @param[in] mutex_id Mutex identifier.
 * @param[in,out] info Mutex information buffer, beginning with its size.
 * @param[in] opt Required option block specifying the number of bytes to copy.
 *
 * @return 0 on success, or < 0 on error.
 */
int _sceKernelGetMutexInfo(SceUID mutex_id, SceKernelMutexInfo *info, const _sceKernelGetMutexInfo_opt *opt);

/**
 * Gets thread information through the raw user export.
 *
 * @param[in] thread_id Thread identifier.
 * @param[in,out] info Thread information buffer, beginning with its size.
 * @param[in] opt Required option block specifying the number of bytes to copy.
 *
 * @return 0 on success, or < 0 on error.
 */
int _sceKernelGetThreadInfo(SceUID thread_id, SceKernelThreadInfo *info, const _sceKernelGetThreadInfo_opt *opt);

/**
 * Registers a thread event handler through the raw user export.
 *
 * Call ::sceKernelUnregisterThreadEventHandler with the returned handler
 * identifier when the handler is no longer needed.
 *
 * @param[in] name Required handler name, limited to 31 bytes plus NUL.
 * @param[in] thread_id Target thread identifier.
 * @param[in] mask Bitwise OR of ::SceKernelThreadEventType values.
 * @param[in] opt Required option block containing the callback and common argument.
 *
 * @return Handler identifier on success, or < 0 on error.
 */
SceUID _sceKernelRegisterThreadEventHandler(const char *name, SceUID thread_id, SceUInt32 mask, const sceKernelRegisterThreadEventHandlerOpt *opt);

/**
 * Creates a user thread in the dormant state through the raw four-argument export.
 *
 * @param[in] name Required thread name, limited to 31 bytes plus NUL.
 * @param[in] entry Thread entry point.
 * @param[in] init_priority Initial thread priority.
 * @param[in] opt Required 0x18-byte wrapper option block. Initialize its first
 * field, ::sceKernelCreateThreadForUser_opt::size, to the size of the structure,
 * even though FW 3.60 ignores it.
 *
 * @return Thread identifier on success, or < 0 on error.
 */
SceUID sceKernelCreateThreadForUser(const char *name, SceKernelThreadEntry entry, SceInt32 init_priority, const sceKernelCreateThreadForUser_opt *opt);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_H_ */
