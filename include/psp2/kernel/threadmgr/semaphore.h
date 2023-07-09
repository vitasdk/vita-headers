/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/semaphore.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_SEMAPHORE_H_
#define _PSP2_KERNEL_THREADMGR_SEMAPHORE_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/** Additional options used when creating semaphores. */
typedef struct SceKernelSemaOptParam {
	/** Size of the ::SceKernelSemaOptParam structure. */
	SceSize 	size;
} SceKernelSemaOptParam;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelSemaOptParam);

/** Current state of a semaphore.
 * @see sceKernelGetSemaInfo.
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
VITASDK_BUILD_ASSERT_EQ(0x3C, SceKernelSemaInfo);

/**
 * Creates a new semaphore
 *
 * @par Example:
 * @code
 * int semaid;
 * semaid = sceKernelCreateSema("MySema", 0, 1, 1, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the sema
 * @param attr - Sema attribute flags (normally set to 0)
 * @param initVal - Sema initial value
 * @param maxVal - Sema maximum value
 * @param option - Sema options (normally set to 0)
 * @return A semaphore id
 */
SceUID sceKernelCreateSema(const char *name, SceUInt attr, int initVal, int maxVal, SceKernelSemaOptParam *option);

/**
 * Destroy a semaphore
 *
 * @param semaid - The semaid returned from a previous create call.
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceKernelDeleteSema(SceUID semaid);

/**
 * Send a signal to a semaphore
 *
 * @par Example:
 * @code
 * // Signal the sema
 * sceKernelSignalSema(semaid, 1);
 * @endcode
 *
 * @param semaid - The sema id returned from ::sceKernelCreateSema
 * @param signal - The amount to signal the sema (i.e. if 2 then increment the sema by 2)
 *
 * @return < 0 On error.
 */
int sceKernelSignalSema(SceUID semaid, int signal);

/**
 * Lock a semaphore
 *
 * @par Example:
 * @code
 * sceKernelWaitSema(semaid, 1, 0);
 * @endcode
 *
 * @param semaid - The sema id returned from ::sceKernelCreateSema
 * @param signal - The value to wait for (i.e. if 1 then wait till reaches a signal state of 1)
 * @param timeout - Timeout in microseconds (assumed).
 *
 * @return < 0 on error.
 */
int sceKernelWaitSema(SceUID semaid, int signal, SceUInt *timeout);

/**
 * Lock a semaphore and handle callbacks if necessary.
 *
 * @par Example:
 * @code
 * sceKernelWaitSemaCB(semaid, 1, 0);
 * @endcode
 *
 * @param semaid - The sema id returned from ::sceKernelCreateSema
 * @param signal - The value to wait for (i.e. if 1 then wait till reaches a signal state of 1)
 * @param timeout - Timeout in microseconds (assumed).
 *
 * @return < 0 on error.
 */
int sceKernelWaitSemaCB(SceUID semaid, int signal, SceUInt *timeout);

/**
 * Poll a semaphore.
 *
 * @param semaid - UID of the semaphore to poll.
 * @param signal - The value to test for.
 *
 * @return < 0 on error.
 */
int sceKernelPollSema(SceUID semaid, int signal);

/**
 * Cancels a semaphore
 *
 * @param semaid - The sema id returned from ::sceKernelCreateSema
 * @param setCount - The new lock count of the semaphore
 * @param numWaitThreads - Number of threads waiting for the semaphore
 * @return < 0 On error.
 */
int sceKernelCancelSema(SceUID semaid, int setCount, int *numWaitThreads);

/**
 * Retrieve information about a semaphore.
 *
 * @param semaid - UID of the semaphore to retrieve info for.
 * @param info - Pointer to a ::SceKernelSemaInfo struct to receive the info.
 *
 * @return < 0 on error.
 */
int sceKernelGetSemaInfo(SceUID semaid, SceKernelSemaInfo *info);

SceUID sceKernelOpenSema(const char *name);

int sceKernelCloseSema(SceUID semaid);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_SEMAPHORE_H_ */
