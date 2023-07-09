/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/thread.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_THREAD_H_
#define _PSP2_KERNEL_THREADMGR_THREAD_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2/kernel/cpu.h>


#ifdef __cplusplus
extern "C" {
#endif


/** Inherit calling thread affinity mask. */
#define SCE_KERNEL_THREAD_CPU_AFFINITY_MASK_DEFAULT (0)


/* Threads. */

typedef int (* SceKernelThreadEntry)(SceSize args, void *argp);

/** Additional options used when creating threads. */
typedef struct SceKernelThreadOptParam {
	/** Size of the ::SceKernelThreadOptParam structure. */
	SceSize     size;
	/** Attributes */
	SceUInt32   attr;
} SceKernelThreadOptParam;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelThreadOptParam);

/** Structure to hold the status information for a thread
  * @see sceKernelGetThreadInfo
  */
typedef struct SceKernelThreadInfo {
	/** Size of the structure */
	SceSize              size;
	/** The UID of the process where the thread belongs */
	SceUID               processId;
	/** Nul terminated name of the thread */
	char                 name[32];
	/** Thread attributes */
	SceUInt32            attr;
	/** Thread status */
	SceUInt32            status;
	/** Thread entry point */
	SceKernelThreadEntry entry;
	/** Thread stack pointer */
	void                 *stack;
	/** Thread stack size */
	SceInt32             stackSize;
	/** Initial priority */
	SceInt32             initPriority;
	/** Current priority */
	SceInt32             currentPriority;
	/** Initial CPU affinity mask */
	SceInt32             initCpuAffinityMask;
	/** Current CPU affinity mask */
	SceInt32             currentCpuAffinityMask;
	/** Current CPU ID */
	SceInt32             currentCpuId;
	/** Last executed CPU ID */
	SceInt32             lastExecutedCpuId;
	/** Wait type */
	SceUInt32            waitType;
	/** Wait id */
	SceUID               waitId;
	/** Exit status of the thread */
	SceInt32             exitStatus;
	/** Number of clock cycles run */
	SceKernelSysClock    runClocks;
	/** Interrupt preemption count */
	SceUInt32            intrPreemptCount;
	/** Thread preemption count */
	SceUInt32            threadPreemptCount;
	/** Thread release count */
	SceUInt32            threadReleaseCount;
	/** Number of CPUs to which the thread is moved */
	SceInt32             changeCpuCount;
	/** Function notify callback UID */
	SceInt32             fNotifyCallback;
	/** Reserved */
	SceInt32             reserved;
} SceKernelThreadInfo;
VITASDK_BUILD_ASSERT_EQ(0x80, SceKernelThreadInfo);

/** Statistics about a running thread.
 * @see sceKernelGetThreadRunStatus.
 */
typedef struct SceKernelThreadRunStatus {
	SceSize        size;
	struct {
		SceUID processId;
		SceUID threadId;
		int    priority;
	} cpuInfo[4];
} SceKernelThreadRunStatus;
VITASDK_BUILD_ASSERT_EQ(0x34, SceKernelThreadRunStatus);

typedef enum SceThreadStatus {
	SCE_THREAD_RUNNING   = 1,
	SCE_THREAD_READY     = 2,
	SCE_THREAD_STANDBY   = 4,
	SCE_THREAD_WAITING   = 8,
	SCE_THREAD_SUSPEND   = 8, /* Compatibility */
	SCE_THREAD_DORMANT   = 16,
	SCE_THREAD_STOPPED   = 16, /* Compatibility */
	SCE_THREAD_DELETED   = 32, /* Thread manager has killed the thread (stack overflow) */
	SCE_THREAD_KILLED    = 32, /* Compatibility */
	SCE_THREAD_DEAD      = 64,
	SCE_THREAD_STAGNANT  = 128,
	SCE_THREAD_SUSPENDED = 256
} SceThreadStatus;


/**
 * Create a thread
 *
 * @par Example:
 * @code
 * SceUID thid;
 * thid = sceKernelCreateThread("my_thread", threadFunc, 0x10000100, 0x10000, 0, 0, NULL);
 * @endcode
 *
 * @param name - An arbitrary thread name.
 * @param entry - The thread function to run when started.
 * @param initPriority - The initial priority of the thread. Less if higher priority.
 * @param stackSize - The size of the initial stack.
 * @param attr - The thread attributes, zero or more of ::SceThreadAttributes.
 * @param cpuAffinityMask - The CPU affinity mask
 *                          A thread can run only on the cores specified in the CPU affinity mask.
 *                          The CPU affinity mask can be specified by the logical sum of the following macros:
 *                          - SCE_KERNEL_CPU_MASK_USER_0
 *                          - SCE_KERNEL_CPU_MASK_USER_1
 *                          - SCE_KERNEL_CPU_MASK_USER_2
 *                          - SCE_KERNEL_CPU_MASK_SYSTEM (system-reserved core)
 *                          The following macro are also available to represent all available in userland CPU cores:
 *                          - SCE_KERNEL_CPU_MASK_USER_ALL
 *                          The following macro are also available to inherit affinity mask of the calling process:
 *                          - SCE_KERNEL_THREAD_CPU_AFFINITY_MASK_DEFAULT
 * @param option - Additional options specified by ::SceKernelThreadOptParam.

 * @return UID of the created thread, or an error code.
 */
SceUID sceKernelCreateThread(const char *name, SceKernelThreadEntry entry, int initPriority,
                             SceSize stackSize, SceUInt attr, int cpuAffinityMask,
                             const SceKernelThreadOptParam *option);

/**
 * Delate a thread
 *
 * @param thid - UID of the thread to be deleted.
 *
 * @return < 0 on error.
 */
int sceKernelDeleteThread(SceUID thid);

/**
 * Start a created thread
 *
 * @param thid - Thread id from ::sceKernelCreateThread
 * @param arglen - Length of the data pointed to by argp, in bytes
 * @param argp - Pointer to the arguments.
 */
int sceKernelStartThread(SceUID thid, SceSize arglen, void *argp);

/**
 * Exit a thread
 *
 * @param status - Exit status.
 */
int sceKernelExitThread(int status);

/**
  * Exit a thread and delete itself.
  *
  * @param status - Exit status
  */
int sceKernelExitDeleteThread(int status);

/**
  * Wait until a thread has ended.
  *
  * @param thid - Id of the thread to wait for.
  * @param stat - Exit status.
  * @param timeout - Timeout in microseconds (assumed).
  *
  * @return < 0 on error.
  */
int sceKernelWaitThreadEnd(SceUID thid, int *stat, SceUInt *timeout);

/**
  * Wait until a thread has ended and handle callbacks if necessary.
  *
  * @param thid - Id of the thread to wait for.
  * @param stat - Exit status.
  * @param timeout - Timeout in microseconds (assumed).
  *
  * @return < 0 on error.
  */
int sceKernelWaitThreadEndCB(SceUID thid, int *stat, SceUInt *timeout);

/**
  * Delay the current thread by a specified number of microseconds
  *
  * @param delay - Delay in microseconds.
  *
  * @par Example:
  * @code
  * sceKernelDelayThread(1000000); // Delay for a second
  * @endcode
  */
int sceKernelDelayThread(SceUInt delay);

/**
  * Delay the current thread by a specified number of microseconds and handle any callbacks.
  *
  * @param delay - Delay in microseconds.
  *
  * @par Example:
  * @code
  * sceKernelDelayThread(1000000); // Delay for a second
  * @endcode
  */
int sceKernelDelayThreadCB(SceUInt delay);

/**
 * Modify the attributes of the current thread.
 *
 * @param clearAttr - The thread attributes to clear.  One of ::SceThreadAttributes.
 * @param setAttr - The thread attributes to set.  One of ::SceThreadAttributes.
 *
 * @return < 0 on error.
 */
int sceKernelChangeCurrentThreadAttr(SceUInt clearAttr, SceUInt setAttr);

/**
  * Change the threads current priority.
  *
  * @param thid - The ID of the thread (from ::sceKernelCreateThread or ::sceKernelGetThreadId)
  * @param priority - The new priority (the lower the number the higher the priority)
  *
  * @par Example:
  * @code
  * int thid = sceKernelGetThreadId();
  * // Change priority of current thread to 16
  * sceKernelChangeThreadPriority(thid, 16);
  * @endcode
  *
  * @return 0 if successful, otherwise the error code.
  */
int sceKernelChangeThreadPriority(SceUID thid, int priority);

/**
 * Get the current priority of the thread you are in.
 *
 * @return The current thread priority
 */
int sceKernelGetThreadCurrentPriority(void);

/**
 * Get the exit status of a thread.
 *
 * @param[in]  thid   - The UID of the thread to check.
 * @param[out] status - Status out pointer
 * @return The exit status
 */
int sceKernelGetThreadExitStatus(SceUID thid, int *status);

/**
 * Check the thread stack?
 *
 * @return Unknown.
 */
int sceKernelCheckThreadStack(void);

/**
 * Get the free stack size for a thread.
 *
 * @param thid - The thread ID
 *
 * @return The free size.
 */
int sceKernelGetThreadStackFreeSize(SceUID thid);

/**
  * Get the status information for the specified thread.
  *
  * @param thid - Id of the thread to get status
  * @param info - Pointer to the info structure to receive the data.
  * Note: The structures size field should be set to
  * sizeof(SceKernelThreadInfo) before calling this function.
  *
  * @par Example:
  * @code
  * SceKernelThreadInfo status;
  * status.size = sizeof(SceKernelThreadInfo);
  * if(sceKernelGetThreadInfo(thid, &status) == 0)
  * { Do something... }
  * @endcode
  * @return 0 if successful, otherwise the error code.
  */
int sceKernelGetThreadInfo(SceUID thid, SceKernelThreadInfo *info);

/**
 * Retrive the runtime status of a thread.
 *
 * @param thid - UID of the thread to retrieve status.
 * @param status - Pointer to a ::SceKernelThreadRunStatus struct to receive the runtime status.
 *
 * @return 0 if successful, otherwise the error code.
 */
int sceKernelGetThreadRunStatus(SceUID thid, SceKernelThreadRunStatus *status);

/**
 * Retrive the cpu affinity mask of a thread.
 *
 * @param thid - UID of the thread to retrieve affinity mask for.
 *
 * @return current affinity mask if >= 0, otherwise the error code.
 */
int sceKernelGetThreadCpuAffinityMask(SceUID thid);

/**
 * Set the cpu affinity mask of a thread.
 *
 * @param thid - UID of the thread to retrieve affinity mask for.
 * @param mask - New cpu affinity mask.
 *
 * @return 0 if successful, otherwise the error code.
 */
int sceKernelChangeThreadCpuAffinityMask(SceUID thid, int mask);

/**
  * Get the current thread Id
  *
  * @return The thread id of the calling thread.
  */
int sceKernelGetThreadId(void);

/**
 * Get the process ID of in the running thread.
 *
 * @return process ID of in the running thread
 */
SceUID sceKernelGetProcessId(void);

typedef struct SceKernelSystemInfo {
	SceSize   size;
	SceUInt32 activeCpuMask;

	struct {
		SceKernelSysClock idleClock;
		SceUInt32         comesOutOfIdleCount;
		SceUInt32         threadSwitchCount;
	} cpuInfo[4];
} SceKernelSystemInfo;
VITASDK_BUILD_ASSERT_EQ(0x48, SceKernelSystemInfo);

/**
 * Get the system information
 *
 * @param info - Pointer to a ::SceKernelSystemInfo structure
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelGetSystemInfo(SceKernelSystemInfo *info);

/** Threadmgr types */
typedef enum SceKernelIdListType {
	SCE_KERNEL_TMID_Thread             = 1,
	SCE_KERNEL_TMID_Semaphore          = 2,
	SCE_KERNEL_TMID_EventFlag          = 3,
	SCE_KERNEL_TMID_Mbox               = 4,
	SCE_KERNEL_TMID_Vpl                = 5,
	SCE_KERNEL_TMID_Fpl                = 6,
	SCE_KERNEL_TMID_Mpipe              = 7,
	SCE_KERNEL_TMID_Callback           = 8,
	SCE_KERNEL_TMID_ThreadEventHandler = 9,
	SCE_KERNEL_TMID_Alarm              = 10,
	SCE_KERNEL_TMID_VTimer             = 11,
	SCE_KERNEL_TMID_SleepThread        = 64,
	SCE_KERNEL_TMID_DelayThread        = 65,
	SCE_KERNEL_TMID_SuspendThread      = 66,
	SCE_KERNEL_TMID_DormantThread      = 67
} SceKernelIdListType;

/**
 * Get the type of a Threadmgr uid
 *
 * @param uid - The uid to get the type from
 *
 * @return The type, < 0 on error
 */
SceKernelIdListType sceKernelGetThreadmgrUIDClass(SceUID uid);

/**
 * @brief sceKernelGetThreadTLSAddr gets an address to a 4 bytes area of TLS memory for the specified thread
 * @param thid - The UID of the thread to access TLS
 * @param key - the TLS keyslot index
 * @return pointer to TLS memory
 */
void *sceKernelGetThreadTLSAddr(SceUID thid, int key);

/**
 * @brief sceKernelGetTLSAddr get pointer to TLS key area for current thread
 * @param key - the TLS keyslot index
 * @return pointer to TLS key value
 */
void *sceKernelGetTLSAddr(int key);

/**
 * Get the system time (wide version)
 *
 * @return The system time
 */
SceInt64 sceKernelGetSystemTimeWide(void);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_THREAD_H_ */
