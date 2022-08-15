/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr.h,SceKernelThreadMgr_stub}
 */


#ifndef _PSP2_KERNEL_THREADMGR_H_
#define _PSP2_KERNEL_THREADMGR_H_

#include <psp2/types.h>
#include <psp2/kernel/cpu.h>


#ifdef __cplusplus
extern "C" {
#endif


/** Inherit calling thread affinity mask. */
#define SCE_KERNEL_THREAD_CPU_AFFINITY_MASK_DEFAULT (0)


/* Threads. */

typedef int (*SceKernelThreadEntry)(SceSize args, void *argp);

/** Additional options used when creating threads. */
typedef struct SceKernelThreadOptParam {
	/** Size of the ::SceKernelThreadOptParam structure. */
	SceSize     size;
	/** Attributes */
	SceUInt32   attr;
} SceKernelThreadOptParam;

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

typedef enum SceKernelWaitableAttribute {
	SCE_KERNEL_ATTR_THREAD_FIFO  = 0x00000000, //!< Waiting threads First input First output
	SCE_KERNEL_ATTR_THREAD_PRIO  = 0x00002000, //!< Waiting threads queued on priority basis
	SCE_KERNEL_ATTR_OPENABLE     = 0x00000080  //!< Sync object can be accessed by sceKernelOpenXxx
} SceKernelWaitableAttribute;

typedef enum SceEventFlagAttributes {
	SCE_DEPRECATED(SCE_EVENT_THREAD_FIFO) = SCE_KERNEL_ATTR_THREAD_FIFO, //!< Use SCE_KERNEL_ATTR_THREAD_FIFO
	SCE_DEPRECATED(SCE_EVENT_THREAD_PRIO) = SCE_KERNEL_ATTR_THREAD_PRIO, //!< Use SCE_KERNEL_ATTR_THREAD_PRIO
	SCE_EVENT_WAITSINGLE   = 0,          //!< Sync object can only be waited upon by one thread.
	SCE_EVENT_WAITMULTIPLE = 0x00001000, //!< Sync object can be waited upon by multiple threads.
	SCE_DEPRECATED(SCE_EVENT_OPENABLE) = SCE_KERNEL_ATTR_OPENABLE //!< Use SCE_KERNEL_ATTR_OPENABLE
} SceEventFlagAttributes;

typedef enum SceKernelMutexAttribute {
	SCE_KERNEL_MUTEX_ATTR_RECURSIVE   = 0x02,
	SCE_KERNEL_MUTEX_ATTR_CEILING     = 0x04
} SceKernelMutexAttribute;

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


/* Semaphores. */

/** Additional options used when creating semaphores. */
typedef struct SceKernelSemaOptParam {
	/** Size of the ::SceKernelSemaOptParam structure. */
	SceSize 	size;
} SceKernelSemaOptParam;

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


/* Mutexes. */

/** Additional options used when creating mutexes. */
typedef struct SceKernelMutexOptParam {
	/** Size of the ::SceKernelMutexOptParam structure. */
	SceSize     size;
	int         ceilingPriority;
} SceKernelMutexOptParam;

/** Current state of a mutex.
 * @see sceKernelGetMutexInfo.
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


/* Event flags. */

/** Structure to hold the event flag information */
typedef struct SceKernelEventFlagInfo {
	SceSize size;
	SceUID  evfId;          // Needs confirmation
	char    name[32];
	SceUInt attr;
	SceUInt initPattern;
	SceUInt currentPattern;
	int     numWaitThreads;
} SceKernelEventFlagInfo;

typedef struct SceKernelEventFlagOptParam {
	SceSize         size;
} SceKernelEventFlagOptParam;

typedef struct SceKernelEventFlagOptParam SceKernelEventFlagOptParam;

/** Event flag wait types */
typedef enum SceEventFlagWaitTypes {
	/** Wait for all bits in the pattern to be set */
	SCE_EVENT_WAITAND       = 0,
	/** Wait for one or more bits in the pattern to be set */
	SCE_EVENT_WAITOR        = 1,
	/** Clear all the bits when it matches */
	SCE_EVENT_WAITCLEAR     = 2,
	/** Clear the wait pattern when it matches */
	SCE_EVENT_WAITCLEAR_PAT = 4
} SceEventFlagWaitTypes;

/**
  * Create an event flag.
  *
  * @param name - The name of the event flag.
  * @param attr - Attributes from ::SceEventFlagAttributes
  * @param bits - Initial bit pattern.
  * @param opt  - Options, set to NULL
  * @return < 0 on error. >= 0 event flag id.
  *
  * @par Example:
  * @code
  * int evid;
  * evid = sceKernelCreateEventFlag("wait_event", 0, 0, NULL);
  * @endcode
  */
SceUID sceKernelCreateEventFlag(const char *name, int attr, int bits, SceKernelEventFlagOptParam *opt);

/**
  * Set an event flag bit pattern.
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  * @param bits - The bit pattern to set.
  *
  * @return < 0 On error
  */
int sceKernelSetEventFlag(SceUID evid, unsigned int bits);

/**
 * Clear a event flag bit pattern
 *
 * @param evid - The event id returned by ::sceKernelCreateEventFlag
 * @param bits - The bits to clean
 *
 * @return < 0 on Error
 */
int sceKernelClearEventFlag(SceUID evid, unsigned int bits);

/**
  * Poll an event flag for a given bit pattern.
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @return < 0 On error
  */
int sceKernelPollEventFlag(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits);

/**
  * Wait for an event flag for a given bit pattern.
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @param timeout  - Timeout in microseconds
  * @return < 0 On error
  */
int sceKernelWaitEventFlag(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits, SceUInt *timeout);

/**
  * Wait for an event flag for a given bit pattern with callback.
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @param timeout  - Timeout in microseconds
  * @return < 0 On error
  */
int sceKernelWaitEventFlagCB(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits, SceUInt *timeout);

/**
  * Delete an event flag
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  *
  * @return < 0 On error
  */
int sceKernelDeleteEventFlag(int evid);

/**
  * Get the status of an event flag.
  *
  * @param event - The UID of the event.
  * @param status - A pointer to a ::SceKernelEventFlagInfo structure.
  *
  * @return < 0 on error.
  */
int sceKernelGetEventFlagInfo(SceUID event, SceKernelEventFlagInfo *info);

/* Condition variables */

/** Additional options used when creating condition variables. */
typedef struct SceKernelCondOptParam {
	/** Size of the ::SceKernelCondOptParam structure. */
	SceSize 	size;
} SceKernelCondOptParam;

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

/* Callbacks. */

/** Callback function prototype */
typedef int (*SceKernelCallbackFunction)(int notifyId, int notifyCount, int notifyArg, void *userData);

/** Structure to hold the status information for a callback */
typedef struct SceKernelCallbackInfo {
	/** Size of the structure (i.e. sizeof(SceKernelCallbackInfo)) */
	SceSize size;
	/** The UID of the callback. */
	SceUID  callbackId; // Needs confirmation
	/** The name given to the callback */
	char    name[32];
	/** The thread id associated with the callback */
	SceUID  threadId;
	/** Pointer to the callback function */
	SceKernelCallbackFunction callback;
	/** User supplied argument for the callback */
	void    *common;
	/** Unknown */
	int     notifyCount;
	/** Unknown */
	int     notifyArg;
} SceKernelCallbackInfo;

/**
 * Create callback
 *
 * @par Example:
 * @code
 * int cbid;
 * cbid = sceKernelCreateCallback("Exit Callback", 0, exit_cb, NULL);
 * @endcode
 *
 * @param name      - A textual name for the callback
 * @param attr      - ?
 * @param func      - A pointer to a function that will be called as the callback
 * @param userData  - User defined data to be passed to the callback.
 *
 * @return >= 0 A callback id which can be used in subsequent functions, < 0 an error.
 */
int sceKernelCreateCallback(const char *name, unsigned int attr, SceKernelCallbackFunction func, void *userData);

/**
  * Gets the status of a specified callback.
  *
  * @param cb - The UID of the callback to retrieve info for.
  * @param status - Pointer to a status structure. The size parameter should be
  * initialised before calling.
  *
  * @return < 0 on error.
  */
int sceKernelGetCallbackInfo(SceUID cb, SceKernelCallbackInfo *infop);

/**
 * Delete a callback
 *
 * @param cb - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelDeleteCallback(SceUID cb);

/**
 * Notify a callback
 *
 * @param cb - The UID of the specified callback
 * @param arg2 - Passed as arg2 into the callback function
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelNotifyCallback(SceUID cb, int arg2);

/**
 * Cancel a callback ?
 *
 * @param cb - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelCancelCallback(SceUID cb);

/**
 * Get the callback count
 *
 * @param cb - The UID of the specified callback
 *
 * @return The callback count, < 0 on error
 */
int sceKernelGetCallbackCount(SceUID cb);

/**
 * Check callback ?
 *
 * @return Something or another
 */
int sceKernelCheckCallback(void);


/* Message pipes */

/**
 * Create a message pipe
 *
 * @param name - Name of the pipe
 * @param type - The type of memory attribute to use internally (set to 0x40)
 * @param attr - Set to 12
 * @param bufSize - The size of the internal buffer in multiples of 0x1000 (4KB)
 * @param opt  - Message pipe options (set to NULL)
 *
 * @return The UID of the created pipe, < 0 on error
 */
SceUID sceKernelCreateMsgPipe(const char *name, int type, int attr, unsigned int bufSize, void *opt);

/**
 * Delete a message pipe
 *
 * @param uid - The UID of the pipe
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelDeleteMsgPipe(SceUID uid);

/**
 * Send a message to a pipe
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - async vs sync? use 0 for sync
 * @param unk2 - Unknown - use NULL
 * @param timeout - Timeout for send in us. use NULL to wait indefinitely
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelSendMsgPipe(SceUID uid, void *message, unsigned int size, int unk1, void *unk2, unsigned int *timeout);

/**
 * Send a message to a pipe (with callback)
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - async vs sync? use 0 for sync
 * @param unk2 - Unknown - use NULL
 * @param timeout - Timeout for send in us. use NULL to wait indefinitely
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelSendMsgPipeCB(SceUID uid, void *message, unsigned int size, int unk1, void *unk2, unsigned int *timeout);

/**
 * Try to send a message to a pipe
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - use 0
 * @param unk2 - Unknown - use NULL
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelTrySendMsgPipe(SceUID uid, void *message, SceSize size, int unk1, void *unk2);

/**
 * Receive a message from a pipe
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - async vs sync? use 0 for sync
 * @param unk2 - Unknown - use NULL
 * @param timeout - Timeout for receive in us. use NULL to wait indefinitely
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelReceiveMsgPipe(SceUID uid, void *message, SceSize size, int unk1, void *unk2, unsigned int *timeout);

/**
 * Receive a message from a pipe (with callback)
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - async vs sync? use 0 for sync
 * @param unk2 - Unknown - use NULL
 * @param timeout - Timeout for receive in us. use NULL to wait indefinitely
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelReceiveMsgPipeCB(SceUID uid, void *message, SceSize size, int unk1, void *unk2, unsigned int *timeout);

/**
 * Receive a message from a pipe
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - use 0
 * @param unk2 - Unknown - use NULL
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelTryReceiveMsgPipe(SceUID uid, void *message, SceSize size, int unk1, void *unk2);

/**
 * Cancel a message pipe
 *
 * @param uid - UID of the pipe to cancel
 * @param psend - Receive number of sending threads, NULL is valid
 * @param precv - Receive number of receiving threads, NULL is valid
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelCancelMsgPipe(SceUID uid, int *psend, int *precv);

/** Message Pipe status info */
typedef struct SceKernelMppInfo {
	SceSize size;
	SceUID  mppId; // Needs confirmation
	char    name[32];
	SceUInt attr;
	int     bufSize;
	int     freeSize;
	int     numSendWaitThreads;
	int     numReceiveWaitThreads;
} SceKernelMppInfo;

/**
 * Get the status of a Message Pipe
 *
 * @param uid - The uid of the Message Pipe
 * @param info - Pointer to a ::SceKernelMppInfo structure
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelGetMsgPipeInfo(SceUID uid, SceKernelMppInfo *info);


/* Misc. */

typedef struct SceKernelSystemInfo {
	SceSize   size;
	SceUInt32 activeCpuMask;

	struct {
		SceKernelSysClock idleClock;
		SceUInt32         comesOutOfIdleCount;
		SceUInt32         threadSwitchCount;
	} cpuInfo[4];
} SceKernelSystemInfo;

/**
 * Get the system information
 *
 * @param info - Pointer to a ::SceKernelSystemInfo structure
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelGetSystemInfo(SceKernelSystemInfo *info);

/* Misc. */

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


typedef struct	SceKernelLwMutexWork {
	SceInt64 data[4];
} SceKernelLwMutexWork;

typedef struct SceKernelLwMutexOptParam {
	SceSize	size;
} SceKernelLwMutexOptParam;

int sceKernelCreateLwMutex(SceKernelLwMutexWork *pWork,const char *pName, unsigned int attr, int initCount, const SceKernelLwMutexOptParam *pOptParam);
int sceKernelDeleteLwMutex(SceKernelLwMutexWork *pWork);
int sceKernelLockLwMutex(SceKernelLwMutexWork *pWork, int lockCount, unsigned int *pTimeout);
int sceKernelTryLockLwMutex(SceKernelLwMutexWork *pWork, int lockCount);
int sceKernelUnlockLwMutex(SceKernelLwMutexWork *pWork, int unlockCount);

typedef struct	SceKernelLwCondWork {
	SceInt32 data[4];
} SceKernelLwCondWork;

typedef struct SceKernelLwCondOptParam {
	SceSize	size;
} SceKernelLwCondOptParam;

int sceKernelCreateLwCond(SceKernelLwCondWork *pWork, const char *pName, unsigned int attr, SceKernelLwMutexWork *pLwMutex, const SceKernelLwCondOptParam *pOptParam);
int sceKernelDeleteLwCond(SceKernelLwCondWork *pWork);
int sceKernelSignalLwCond(SceKernelLwCondWork *pWork);
int sceKernelSignalLwCondAll(SceKernelLwCondWork *pWork);
int sceKernelSignalLwCondTo(SceKernelLwCondWork *pWork, SceUID threadId);
int sceKernelWaitLwCond(SceKernelLwCondWork *pWork,  unsigned int *pTimeout);

/**
 * @brief Sleep current thread and wait for a signal. After it receives a signal, the thread wakes up.
 *
 * This is like a semphore with limit 1.
 * If signal was sent before and not consumed before, the function will immediately return.
 * @param unk0 unknown parameter. 0 can be used.
 * @param delay the delay before wating for a signal
 * @param timeout the timeout if it's null, it waits indefinitely.
 * @return 0 on success
 */
int sceKernelWaitSignal(SceUInt32 unk0, SceUInt32 delay, SceUInt32 *timeout);

/**
 * @brief Send a signal to the thread specified by thid. Note that it can send a signal to the current thread as well.
 *
 * @param thid - the id of the thread to send a signal to
 * @return 0 on success
 * @return SCE_KERNEL_ERROR_ALREADY_SENT if the last signal was not consumed by sceKernelWaitSignal
 */
int sceKernelSendSignal(SceUID thid);

/**
 * Get the system time (wide version)
 *
 * @return The system time
 */
SceInt64 sceKernelGetSystemTimeWide(void);

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

/* RWLock */

/** Additional options used when creating rwlock. */
typedef struct SceKernelRWLockOptParam {
	/** Size of the ::SceKernelRWLockOptParam structure */
	SceSize     size;
} SceKernelRWLockOptParam;

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

#endif /* _PSP2_KERNEL_THREADMGR_H_ */

