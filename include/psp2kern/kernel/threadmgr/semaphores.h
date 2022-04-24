/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/semaphores.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_SEMAPHORES_H_
#define _PSP2KERN_KERNEL_THREADMGR_SEMAPHORES_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/** Additional options used when creating semaphores. */
typedef struct SceKernelSemaOptParam {
	/** Size of the ::SceKernelSemaOptParam structure. */
	SceSize   size;
} SceKernelSemaOptParam;

/** Current state of a semaphore.
 * @see ksceKernelGetSemaInfo.
 */
typedef struct SceKernelSemaInfo {
	/** Size of the ::SceKernelSemaInfo structure. */
	SceSize         size;
	/** The UID of the semaphore */
	SceUID          semaId;
	/** NUL-terminated name of the semaphore. */
	char            name[32];
	/** Attributes. */
	SceUInt         attr;
	/** The initial count the semaphore was created with. */
	int             initCount;
	/** The current count. */
	int             currentCount;
	/** The maximum count. */
	int             maxCount;
	/** The number of threads waiting on the semaphore. */
	int             numWaitThreads;
} SceKernelSemaInfo;

/**
 * Get semaphore info
 *
 * @param[in]  semaid - The semaphore guid.
 * @param[out] info   - The info output buffer pointer.
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelGetSemaInfo(SceUID semaid, SceKernelSemaInfo *info);

/**
 * Creates a new semaphore
 *
 * @par Example:
 * @code
 * int semaid;
 * semaid = ksceKernelCreateSema("MySema", 0, 1, 1, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the sema
 * @param attr - Sema attribute flags (normally set to 0)
 * @param initVal - Sema initial value
 * @param maxVal - Sema maximum value
 * @param option - Sema options (normally set to 0)
 * @return A semaphore id
 */
SceUID ksceKernelCreateSema(const char *name, SceUInt attr, int initVal, int maxVal, SceKernelSemaOptParam *option);

/**
 * Destroy a semaphore
 *
 * @param semaid - The semaid returned from a previous create call.
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int ksceKernelDeleteSema(SceUID semaid);

/**
 * Send a signal to a semaphore
 *
 * @par Example:
 * @code
 * // Signal the sema
 * ksceKernelSignalSema(semaid, 1);
 * @endcode
 *
 * @param semaid - The sema id returned from ::ksceKernelCreateSema
 * @param signal - The amount to signal the sema (i.e. if 2 then increment the sema by 2)
 *
 * @return < 0 On error.
 */
int ksceKernelSignalSema(SceUID semaid, int signal);

/**
 * Lock a semaphore
 *
 * @par Example:
 * @code
 * ksceKernelWaitSema(semaid, 1, NULL);
 * @endcode
 *
 * @param semaid - The sema id returned from ::ksceKernelCreateSema
 * @param signal - The value to wait for (i.e. if 1 then wait till reaches a signal state of 1)
 * @param timeout - Timeout in microseconds (assumed).
 *
 * @return < 0 on error.
 */
int ksceKernelWaitSema(SceUID semaid, int signal, SceUInt *timeout);

/**
 * Poll a semaphore.
 *
 * @param semaid - UID of the semaphore to poll.
 * @param signal - The value to test for.
 *
 * @return < 0 on error.
 */
int ksceKernelPollSema(SceUID semaid, int signal);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_SEMAPHORES_H_ */
