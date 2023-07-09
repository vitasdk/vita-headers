/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/rwlock.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_RWLOCK_H_
#define _PSP2_KERNEL_THREADMGR_RWLOCK_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/** Additional options used when creating rwlock. */
typedef struct SceKernelRWLockOptParam {
	/** Size of the ::SceKernelRWLockOptParam structure */
	SceSize     size;
} SceKernelRWLockOptParam;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelRWLockOptParam);

/** Current state of a rwlock.
 * @see sceKernelGetRWLockInfo
 */
typedef struct SceKernelRWLockInfo {
	/** Size of the ::SceKernelRWLockInfo structure */
	SceSize         size;
	/** The UID of the rwlock */
	SceUID          rwLockId;
	/** NULL-terminated name of the rwlock */
	char            name[32];
	/** Attributes */
  SceUInt32       attr;
	/** The current lock count */
	SceInt32        lockCount;
	/** The UID of the current owner of the rwlock with write access, 0 when locked for reads */
	SceUID          writeOwnerId;
	/** The number of threads waiting on the rwlock for read access */
	SceUInt32       numReadWaitThreads;
	/** The number of threads waiting on the rwlock for write access */
	SceUInt32       numWriteWaitThreads;
} SceKernelRWLockInfo;
VITASDK_BUILD_ASSERT_EQ(0x3C, SceKernelRWLockInfo);

/**
 * Creates a new rwlock
 *
 * @par Example:
 * @code
 * int rwlock_id;
 * rwlock_id = sceKernelCreateRWLock("MyRWLock", 0, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the rwlock
 * @param attr - RWLock attribute flags (normally set to 0)
 * @param option - RWLock options (normally set to NULL)
 * @return RWLock id on success, < 0 on error
 */
SceUID sceKernelCreateRWLock(const char *name, SceUInt32 attr, const SceKernelRWLockOptParam *opt_param);

/**
 * Destroy a rwlock
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int sceKernelDeleteRWLock(SceUID rwlock_id);

/**
 * Open a rwlock
 *
 * @param name - The name of the rwlock to open
 * @return RWLock id on success, < 0 on error
 */
SceUID sceKernelOpenRWLock(const char *name);

/**
 * Close a rwlock
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int sceKernelCloseRWLock(SceUID rwlock_id);

/**
 * Lock a rwlock with read access
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @param timeout - Timeout in microseconds, use NULL to disable it
 * @return 0 on success, < 0 on error
 */
int sceKernelLockReadRWLock(SceUID rwlock_id, unsigned int *timeout);

/**
 * Lock a rwlock with write access
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @param timeout - Timeout in microseconds, use NULL to disable it
 * @return 0 on success, < 0 on error
 */
int sceKernelLockWriteRWLock(SceUID rwlock_id, unsigned int *timeout);

/**
 * Lock a rwlock with read access and handle callbacks
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @param timeout - Timeout in microseconds, use NULL to disable it
 * @return 0 on success, < 0 on error
 */
int sceKernelLockReadRWLockCB(SceUID rwlock_id, unsigned int *timeout);

/**
 * Lock a rwlock with write access and handle callbacks
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @param timeout - Timeout in microseconds, use NULL to disable it
 * @return 0 on success, < 0 on error
 */
int sceKernelLockWriteRWLockCB(SceUID rwlock_id, unsigned int *timeout);

/**
 * Try to lock a rwlock with read access (non-blocking)
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int sceKernelTryLockReadRWLock(SceUID rwlock_id);

/**
 * Try to lock a rwlock with write access (non-blocking)
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int sceKernelTryLockWriteRWLock(SceUID rwlock_id);

/**
 * Try to unlock a rwlock with read access (non-blocking)
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int sceKernelUnlockReadRWLock(SceUID rwlock_id);

/**
 * Try to unlock a rwlock with write access (non-blocking)
 *
 * @param rwlock_id - The rwlock id returned from ::sceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int sceKernelUnlockWriteRWLock(SceUID rwlock_id);

/**
 * Retrieve information about a rwlock.
 *
 * @param rwlock_id - UID of the rwlock to retrieve info for.
 * @param info - Pointer to a ::SceKernelRWLockInfo struct to receive the info.
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelGetRWLockInfo(SceUID rwlock_id, SceKernelRWLockInfo *info);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_RWLOCK_H_ */
