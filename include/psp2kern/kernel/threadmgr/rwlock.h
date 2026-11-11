/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/rwlock.h,SceThreadmgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_THREADMGR_RWLOCK_H_
#define _PSP2KERN_KERNEL_THREADMGR_RWLOCK_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new rwlock
 *
 * @par Example:
 * @code
 * int rwlock_id;
 * rwlock_id = ksceKernelCreateRWLock("MyRWLock", 0, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the rwlock
 * @param attr - RWLock attribute flags (normally set to 0)
 * @param option - RWLock options (normally set to NULL)
 * @return RWLock id on success, < 0 on error
 */
SceUID ksceKernelCreateRWLock(const char *name, SceUInt32 attr, const SceKernelRWLockOptParam *opt_param);

/**
 * Destroy a rwlock
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int ksceKernelDeleteRWLock(SceUID rwlock_id);

/**
 * Lock a rwlock with read access
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @param timeout - Timeout in microseconds, use NULL to disable it
 * @return 0 on success, < 0 on error
 */
int ksceKernelLockReadRWLock(SceUID rwlock_id, unsigned int *timeout);

/**
 * Lock a rwlock with write access
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @param timeout - Timeout in microseconds, use NULL to disable it
 * @return 0 on success, < 0 on error
 */
int ksceKernelLockWriteRWLock(SceUID rwlock_id, unsigned int *timeout);

/**
 * Lock a rwlock with read access and handle callbacks
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @param timeout - Timeout in microseconds, use NULL to disable it
 * @return 0 on success, < 0 on error
 */
int ksceKernelLockReadRWLockCB(SceUID rwlock_id, unsigned int *timeout);

/**
 * Lock a rwlock with write access and handle callbacks
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @param timeout - Timeout in microseconds, use NULL to disable it
 * @return 0 on success, < 0 on error
 */
int ksceKernelLockWriteRWLockCB(SceUID rwlock_id, unsigned int *timeout);

/**
 * Try to lock a rwlock with read access (non-blocking)
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int ksceKernelTryLockReadRWLock(SceUID rwlock_id);

/**
 * Try to lock a rwlock with write access (non-blocking)
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int ksceKernelTryLockWriteRWLock(SceUID rwlock_id);

/**
 * Try to unlock a rwlock with read access (non-blocking)
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int ksceKernelUnlockReadRWLock(SceUID rwlock_id);

/**
 * Try to unlock a rwlock with write access (non-blocking)
 *
 * @param rwlock_id - The rwlock id returned from ::ksceKernelCreateRWLock
 * @return 0 on success, < 0 on error
 */
int ksceKernelUnlockWriteRWLock(SceUID rwlock_id);

/**
 * Retrieve information about a rwlock.
 *
 * @param rwlock_id - UID of the rwlock to retrieve info for.
 * @param info - Pointer to a ::SceKernelRWLockInfo struct to receive the info.
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelGetRWLockInfo(SceUID rwlock_id, SceKernelRWLockInfo *info);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_RWLOCK_H_ */
