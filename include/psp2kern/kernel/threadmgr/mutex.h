/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/mutex.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_MUTEX_H_
#define _PSP2KERN_KERNEL_THREADMGR_MUTEX_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


#define SCE_KERNEL_MUTEX_ATTR_RECURSIVE 2

/** Additional options used when creating mutexes. */
typedef struct SceKernelMutexOptParam {
	/** Size of the ::SceKernelMutexOptParam structure. */
	SceSize   size;
	int             ceilingPriority;
} SceKernelMutexOptParam;

/** Current state of a mutex.
 * @see ksceKernelGetMutexInfo.
 */
typedef struct SceKernelMutexInfo {
	/** Size of the ::SceKernelMutexInfo structure. */
	SceSize         size;
	/** The UID of the mutex. */
	SceUID          mutexId;
	/** NUL-terminated name of the mutex. */
	char            name[32];
	/** Attributes. */
	SceUInt         attr;
	/** The initial count the mutex was created with. */
	int             initCount;
	/** The current count. */
	int             currentCount;
	/** The UID of the current owner of the mutex. */
	SceUID          currentOwnerId;
	/** The number of threads waiting on the mutex. */
	int             numWaitThreads;
} SceKernelMutexInfo;

/**
 * Creates a new mutex
 *
 * @par Example:
 * @code
 * int mutexid;
 * mutexid = ksceKernelCreateMutex("MyMutex", 0, 1, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the mutex
 * @param attr - Mutex attribute flags (normally set to 0)
 * @param initCount - Mutex initial value
 * @param option - Mutex options (normally set to 0)
 * @return A mutex id
 */
SceUID ksceKernelCreateMutex(const char *name, SceUInt attr, int initCount, SceKernelMutexOptParam *option);

/**
 * Destroy a mutex
 *
 * @param mutexid - The mutex id returned from ::ksceKernelCreateMutex
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int ksceKernelDeleteMutex(SceUID mutexid);

/**
 * Lock a mutex
 *
 * @param mutexid - The mutex id returned from ::ksceKernelCreateMutex
 * @param lockCount - The value to increment to the lock count of the mutex
 * @param timeout - Timeout in microseconds (assumed)
 * @return < 0 On error.
 */
int ksceKernelLockMutex(SceUID mutexid, int lockCount, unsigned int *timeout);

/**
 * Try to lock a mutex (non-blocking)
 *
 * @param mutexid - The mutex id returned from ::ksceKernelCreateMutex
 * @param lockCount - The value to increment to the lock count of the mutex
 * @return < 0 On error.
 */
int ksceKernelTryLockMutex(SceUID mutexid, int lockCount);

/**
 * Try to unlock a mutex (non-blocking)
 *
 * @param mutexid - The mutex id returned from ::ksceKernelCreateMutex
 * @param unlockCount - The value to decrement to the lock count of the mutex
 * @return < 0 On error.
 */
int ksceKernelUnlockMutex(SceUID mutexid, int unlockCount);

/**
 * Cancels a mutex
 *
 * @param mutexid - The mutex id returned from ::ksceKernelCreateMutex
 * @param newCount - The new lock count of the mutex
 * @param numWaitThreads - Number of threads waiting for the mutex
 * @return < 0 On error.
 */
int ksceKernelCancelMutex(SceUID mutexid, int newCount, int *numWaitThreads);

/**
 * Retrieve information about a mutex.
 *
 * @param mutexid - UID of the mutex to retrieve info for.
 * @param info - Pointer to a ::SceKernelMutexInfo struct to receive the info.
 *
 * @return < 0 on error.
 */
int ksceKernelGetMutexInfo(SceUID mutexid, SceKernelMutexInfo *info);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_MUTEX_H_ */
