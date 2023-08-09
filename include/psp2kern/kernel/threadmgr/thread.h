/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/thread.h,SceThreadmgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_THREADMGR_THREAD_H_
#define _PSP2KERN_KERNEL_THREADMGR_THREAD_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief Create a thread
 *
 * @par Example:
 * @code
 * SceUID thid;
 * thid = ksceKernelCreateThread("my_thread", threadFunc, 0x10000100, 0x10000, 0, 0, NULL);
 * @endcode
 *
 * @param name - An arbitrary thread name.
 * @param entry - The thread function to run when started.
 * @param initPriority - The initial priority of the thread. Less if higher priority.
 * @param stackSize - The size of the initial stack.
 * @param attr - The thread attributes, zero or more of ::SceThreadAttributes.
 * @param cpuAffinityMask - The CPU affinity mask
 * @param option - Additional options specified by ::SceKernelThreadOptParam.

 * @return UID of the created thread, or an error code.
 */
SceUID ksceKernelCreateThread(const char *name, SceKernelThreadEntry entry, int initPriority,
                             SceSize stackSize, SceUInt attr, int cpuAffinityMask,
                             const SceKernelThreadOptParam *option);

/**
 * Delate a thread
 *
 * @param thid - UID of the thread to be deleted.
 *
 * @return < 0 on error.
 */
int ksceKernelDeleteThread(SceUID thid);

/**
 * Start a created thread
 *
 * @param thid - Thread id from ::ksceKernelCreateThread
 * @param arglen - Length of the data pointed to by argp, in bytes
 * @param argp - Pointer to the arguments.
 */
int ksceKernelStartThread(SceUID thid, SceSize arglen, void *argp);

/**
 * Exit a thread
 *
 * @param status - Exit status.
 */
int ksceKernelExitThread(int status);

/**
  * Exit a thread and delete itself.
  *
  * @param status - Exit status
  */
int ksceKernelExitDeleteThread(int status);

/**
  * Wait until a thread has ended.
  *
  * @param thid - Id of the thread to wait for.
  * @param stat - Exit status.
  * @param timeout - Timeout in microseconds (assumed).
  *
  * @return < 0 on error.
  */
int ksceKernelWaitThreadEnd(SceUID thid, int *stat, SceUInt *timeout);

/**
  * Wait until a thread has ended and handle callbacks if necessary.
  *
  * @param thid - Id of the thread to wait for.
  * @param stat - Exit status.
  * @param timeout - Timeout in microseconds (assumed).
  *
  * @return < 0 on error.
  */
int ksceKernelWaitThreadEndCB(SceUID thid, int *stat, SceUInt *timeout);

/**
  * Delay the current thread by a specified number of microseconds
  *
  * @param delay - Delay in microseconds.
  *
  * @par Example:
  * @code
  * ksceKernelDelayThread(1000000); // Delay for a second
  * @endcode
  */
int ksceKernelDelayThread(SceUInt delay);

/**
  * Delay the current thread by a specified number of microseconds and handle any callbacks.
  *
  * @param delay - Delay in microseconds.
  *
  * @par Example:
  * @code
  * ksceKernelDelayThread(1000000); // Delay for a second
  * @endcode
  */
int ksceKernelDelayThreadCB(SceUInt delay);

/**
  * Change the threads current priority.
  *
  * @param thid - The ID of the thread (from ::ksceKernelCreateThread or ::ksceKernelGetThreadId)
  * @param priority - The new priority (the lower the number the higher the priority)
  *
  * @par Example:
  * @code
  * int thid = ksceKernelGetThreadId();
  * // Change priority of current thread to 16
  * ksceKernelChangeThreadPriority(thid, 16);
  * @endcode
  *
  * @return 0 if successful, otherwise the error code.
  */
int ksceKernelChangeThreadPriority(SceUID thid, int priority);

/**
  * Get the current thread Id
  *
  * @return The thread id of the calling thread.
  */
int ksceKernelGetThreadId(void);

/**
 * Get the current priority of the thread you are in.
 *
 * @return The current thread priority
 */
int ksceKernelGetThreadCurrentPriority(void);

/**
 * Get the free stack size for a thread.
 *
 * @param thid - The thread ID
 *
 * @return The free size.
 */
int ksceKernelGetThreadStackFreeSize(SceUID thid);

/**
 * Get the thread info by thread id.
 *
 * @param thid - The thread id for get info.
 * @param info - The info output.
 *
 * @return < 0 on error.
 */
int ksceKernelGetThreadInfo(SceUID thid, SceKernelThreadInfo *info);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_THREAD_H_ */
