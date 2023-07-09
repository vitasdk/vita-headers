/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/cond.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_COND_H_
#define _PSP2_KERNEL_THREADMGR_COND_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/** Additional options used when creating condition variables. */
typedef struct SceKernelCondOptParam {
	/** Size of the ::SceKernelCondOptParam structure. */
	SceSize 	size;
} SceKernelCondOptParam;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelCondOptParam);

/** Current state of a condition variable.
 * @see sceKernelGetCondInfo.
 */
typedef struct SceKernelCondInfo {
	/** Size of the ::SceKernelCondInfo structure. */
	SceSize         size;
	/** The UID of the condition variable. */
	SceUID          condId;
	/** NUL-terminated name of the condition variable. */
	char            name[32];
	/** Attributes. */
	SceUInt         attr;
	/** Mutex associated with the condition variable. */
	SceUID          mutexId;
	/** The number of threads waiting on the condition variable. */
	int             numWaitThreads;
} SceKernelCondInfo;
VITASDK_BUILD_ASSERT_EQ(0x34, SceKernelCondInfo);

/**
 * Creates a new condition variable
 *
 * @par Example:
 * @code
 * SceUID condId;
 * condId = sceKernelCreateCond("MyCond", 0, mutexId, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the condition variable
 * @param attr - Condition variable attribute flags (normally set to 0)
 * @param mutexId - Mutex to be related to the condition variable
 * @param option - Condition variable options (normally set to 0)
 * @return A condition variable id
 */
SceUID sceKernelCreateCond(const char *name, SceUInt attr, SceUID mutexId, const SceKernelCondOptParam *option);

/**
 * Destroy a condition variable
 *
 * @param condition variableid - The condition variable id returned from ::sceKernelCreateCond
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceKernelDeleteCond(SceUID condId);

/**
 * Open a condition variable
 *
 * @param name - The name of the condition variable to open
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceKernelOpenCond(const char *name);

/**
 * Close a condition variable
 *
 * @param condition variableid - The condition variable id returned from ::sceKernelCreateCond
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int sceKernelCloseCond(SceUID condId);

/**
 * Waits for a signal of a condition variable
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @param timeout - Timeout in microseconds (assumed)
 * @return < 0 On error.
 */
int sceKernelWaitCond(SceUID condId, unsigned int *timeout);

/**
 * Waits for a signal of a condition variable (with callbacks)
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @param timeout - Timeout in microseconds (assumed)
 * @return < 0 On error.
 */
int sceKernelWaitCondCB(SceUID condId, unsigned int *timeout);

/**
 * Signals a condition variable
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @return < 0 On error.
 */
int sceKernelSignalCond(SceUID condId);

/**
 * Signals a condition variable to all threads waiting for it
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @return < 0 On error.
 */
int sceKernelSignalCondAll(SceUID condId);

/**
 * Signals a condition variable to a specific thread waiting for it
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @param threadId - The thread id returned from ::sceKernelCreateThread
 * @return < 0 On error.
 */
int sceKernelSignalCondTo(SceUID condId, SceUID threadId);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_COND_H_ */
