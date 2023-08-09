/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/cond.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_COND_H_
#define _PSP2KERN_KERNEL_THREADMGR_COND_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Creates a new condition variable
 *
 * @par Example:
 * @code
 * SceUID condId;
 * condId = ksceKernelCreateCond("MyCond", 0, mutexId, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the condition variable
 * @param attr - Condition variable attribute flags (normally set to 0)
 * @param mutexId - Mutex to be related to the condition variable
 * @param option - Condition variable options (normally set to 0)
 * @return A condition variable id
 */
SceUID ksceKernelCreateCond(const char *name, SceUInt attr, SceUID mutexId, const SceKernelCondOptParam *option);

/**
 * Destroy a condition variable
 *
 * @param condition variableid - The condition variable id returned from ::ksceKernelCreateCond
 * @return Returns the value 0 if it's successful, otherwise -1
 */
int ksceKernelDeleteCond(SceUID condId);

/**
 * Waits for a signal of a condition variable
 *
 * @param condId - The condition variable id returned from ::ksceKernelCreateCond
 * @param timeout - Timeout in microseconds (assumed)
 * @return < 0 On error.
 */
int ksceKernelWaitCond(SceUID condId, unsigned int *timeout);

/**
 * Signals a condition variable
 *
 * @param condId - The condition variable id returned from ::ksceKernelCreateCond
 * @return < 0 On error.
 */
int ksceKernelSignalCond(SceUID condId);

/**
 * Signals a condition variable to all threads waiting for it
 *
 * @param condId - The condition variable id returned from ::ksceKernelCreateCond
 * @return < 0 On error.
 */
int ksceKernelSignalCondAll(SceUID condId);

/**
 * Signals a condition variable to a specific thread waiting for it
 *
 * @param condId - The condition variable id returned from ::ksceKernelCreateCond
 * @param threadId - The thread id returned from ::ksceKernelCreateThread
 * @return < 0 On error.
 */
int ksceKernelSignalCondTo(SceUID condId, SceUID threadId);



#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_COND_H_ */
