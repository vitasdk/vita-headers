/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/mutex.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_MUTEX_H_
#define _PSP2_KERNEL_THREADMGR_MUTEX_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Creates a new mutex
 *
 * @par Example:
 * @code
 * int mutexid;
 * mutexid = sceKernelCreateMutex("MyMutex", 0, 1, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the mutex
 * @param attr - Mutex attribute flags (normally set to 0)
 * @param initCount - Mutex initial value
 * @param option - Mutex options (normally set to 0)
 * @return A mutex id
 */
SceUID sceKernelCreateMutex(const char *name, SceUInt attr, int initCount, SceKernelMutexOptParam *option);

/**
 * Destroy a mutex
 *
 * @param mutexid - The mutex id returned from ::sceKernelCreateMutex
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceKernelDeleteMutex(SceUID mutexid);

/**
 * Open a mutex
 *
 * @param name - The name of the mutex to open
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceKernelOpenMutex(const char *name);

/**
 * Close a mutex
 *
 * @param mutexid - The mutex id returned from ::sceKernelCreateMutex
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceKernelCloseMutex(SceUID mutexid);

/**
 * Lock a mutex
 *
 * @param mutexid - The mutex id returned from ::sceKernelCreateMutex
 * @param lockCount - The value to increment to the lock count of the mutex
 * @param timeout - Timeout in microseconds (assumed)
 * @return < 0 On error.
 */
int sceKernelLockMutex(SceUID mutexid, int lockCount, unsigned int *timeout);

/**
 * Lock a mutex and handle callbacks if necessary.
 *
 * @param mutexid - The mutex id returned from ::sceKernelCreateMutex
 * @param lockCount - The value to increment to the lock count of the mutex
 * @param timeout - Timeout in microseconds (assumed)
 * @return < 0 On error.
 */
int sceKernelLockMutexCB(SceUID mutexid, int lockCount, unsigned int *timeout);

/**
 * Try to lock a mutex (non-blocking)
 *
 * @param mutexid - The mutex id returned from ::sceKernelCreateMutex
 * @param lockCount - The value to increment to the lock count of the mutex
 * @return < 0 On error.
 */
int sceKernelTryLockMutex(SceUID mutexid, int lockCount);

/**
 * Try to unlock a mutex (non-blocking)
 *
 * @param mutexid - The mutex id returned from ::sceKernelCreateMutex
 * @param unlockCount - The value to decrement to the lock count of the mutex
 * @return < 0 On error.
 */
int sceKernelUnlockMutex(SceUID mutexid, int unlockCount);

/**
 * Cancels a mutex
 *
 * @param mutexid - The mutex id returned from ::sceKernelCreateMutex
 * @param newCount - The new lock count of the mutex
 * @param numWaitThreads - Number of threads waiting for the mutex
 * @return < 0 On error.
 */
int sceKernelCancelMutex(SceUID mutexid, int newCount, int *numWaitThreads);

/**
 * Retrieve information about a mutex.
 *
 * @param mutexid - UID of the mutex to retrieve info for.
 * @param info - Pointer to a ::SceKernelMutexInfo struct to receive the info.
 *
 * @return < 0 on error.
 */
int sceKernelGetMutexInfo(SceUID mutexid, SceKernelMutexInfo *info);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_MUTEX_H_ */
