/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2_KERNEL_THREADMGR_H_
#define _PSP2_KERNEL_THREADMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_KERNEL_MUTEX_ATTR_RECURSIVE 2

/** 64-bit system clock type. */
typedef SceUInt64 SceKernelSysClock;

/* Threads. */

typedef int (*SceKernelThreadEntry)(SceSize args, void *argp);

/** Additional options used when creating threads. */
typedef struct SceKernelThreadOptParam {
	/** Size of the ::SceKernelThreadOptParam structure. */
	SceSize   size;
	/** Attributes */
	SceUInt32       attr;
} SceKernelThreadOptParam;

/** Structure to hold the status information for a thread
  * @see ksceKernelGetThreadInfo
  */
typedef struct SceKernelThreadInfo {
	/** Size of the structure */
	SceSize         size;
	/** The UID of the process where the thread belongs */
	SceUID          processId; //Needs confirmation
	/** Nul terminated name of the thread */
	char            name[32];
	/** Thread attributes */
	SceUInt         attr;
	/** Thread status */
	int             status;
	/** Thread entry point */
	SceKernelThreadEntry entry;
	/** Thread stack pointer */
	void            *stack;
	/** Thread stack size */
	int             stackSize;
	/** Initial priority */
	int             initPriority;
	/** Current priority */
	int             currentPriority;
	/** Initial CPU affinity mask */
	int             initCpuAffinityMask;
	/** Current CPU affinity mask */
	int             currentCpuAffinityMask;
	/** Current CPU ID */
	int             currentCpuId;
	/** Last executed CPU ID */
	int             lastExecutedCpuId;
	/** Wait type */
	int             waitType;
	/** Wait id */
	SceUID          waitId;
	/** Exit status of the thread */
	int             exitStatus;
	/** Number of clock cycles run */
	SceKernelSysClock runClocks;
	/** Interrupt preemption count */
	SceUInt     intrPreemptCount;
	/** Thread preemption count */
	SceUInt     threadPreemptCount;
	/** Thread release count */
	SceUInt     threadReleaseCount;
	/** Function notify callback UID */
	SceUID      fNotifyCallback;
	/** Reserved */
	int         reserved;
} SceKernelThreadInfo;

/** Statistics about a running thread.
 * @see ksceKernelGetThreadRunStatus.
 */
typedef struct SceKernelThreadRunStatus {
	SceSize        size;
	struct {
		SceUID processId;
		SceUID threadId;
		int    priority;
	} cpuInfo[4];
} SceKernelThreadRunStatus;

/* Sure there must be more than this, but haven't seen them */
typedef enum SceThreadStatus {
	SCE_THREAD_RUNNING = 1,
	SCE_THREAD_READY   = 2,
	SCE_THREAD_WAITING = 4,
	SCE_THREAD_SUSPEND = 8,
	SCE_THREAD_STOPPED = 16,
	SCE_THREAD_KILLED  = 32, /* Thread manager has killed the thread (stack overflow) */
} SceThreadStatus;

typedef struct SceKernelFaultingProcessInfo {
    SceUID pid;
    uint32_t unk;
} SceKernelFaultingProcessInfo;

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
                             int stackSize, SceUInt attr, int cpuAffinityMask,
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
 * @param thid - The thread ID. Seem to take current thread
 * if set to 0.
 *
 * @return The free size.
 */
int ksceKernelGetThreadStackFreeSize(SceUID thid);


/* Semaphores. */

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
 * Creates a new semaphore
 *
 * @par Example:
 * @code
 * int semaid;
 * semaid = ksceKernelCreateSema("MySema", 0, 1, 1, 0);
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
 * ksceKernelWaitSema(semaid, 1, 0);
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


/* Mutexes. */

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
 * mutexid = ksceKernelCreateMutex("MyMutex", 0, 1, 1, 0);
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

typedef struct  SceKernelLwMutexWork {
	SceInt64 data[4];
} SceKernelLwMutexWork;

typedef struct SceKernelLwMutexOptParam {
	SceSize size;
} SceKernelLwMutexOptParam;

int ksceKernelInitializeFastMutex(void *mutex, const char *name, int unk0, int unk1);
int ksceKernelLockFastMutex(void *mutex);
int ksceKernelUnlockFastMutex(void *mutex);
int ksceKernelDeleteFastMutex(void *mutex);

/* Event flags. */

/** Structure to hold the event flag information */
typedef struct SceKernelEventFlagInfo {
	SceSize   size;
	SceUID          evfId; // Needs confirmation
	char    name[32];
	SceUInt   attr;
	SceUInt   initPattern;
	SceUInt   currentPattern;
	int     numWaitThreads;
} SceKernelEventFlagInfo;

typedef struct SceKernelEventFlagOptParam {
	SceSize         size;
} SceKernelEventFlagOptParam;

typedef struct SceKernelEventFlagOptParam SceKernelEventFlagOptParam;

/** Event flag creation attributes */
typedef enum SceEventFlagAttributes {
	/** Allow the event flag to be waited upon by multiple threads */
	SCE_EVENT_WAITMULTIPLE = 0x1000
} SceEventFlagAttributes;

/** Event flag wait types */
typedef enum SceEventFlagWaitTypes {
	/** Wait for all bits in the pattern to be set */
	SCE_EVENT_WAITAND = 0,
	/** Wait for one or more bits in the pattern to be set */
	SCE_EVENT_WAITOR  = 1,
	/** Clear all the bits when it matches */
	SCE_EVENT_WAITCLEAR = 2,
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
  * evid = ksceKernelCreateEventFlag("wait_event", 0, 0, 0);
  * @endcode
  */
SceUID ksceKernelCreateEventFlag(const char *name, int attr, int bits, SceKernelEventFlagOptParam *opt);

/**
  * Set an event flag bit pattern.
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  * @param bits - The bit pattern to set.
  *
  * @return < 0 On error
  */
int ksceKernelSetEventFlag(SceUID evid, unsigned int bits);

/**
 * Clear a event flag bit pattern
 *
 * @param evid - The event id returned by ::ksceKernelCreateEventFlag
 * @param bits - The bits to clean
 *
 * @return < 0 on Error
 */
int ksceKernelClearEventFlag(SceUID evid, unsigned int bits);

/**
  * Poll an event flag for a given bit pattern.
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @return < 0 On error
  */
int ksceKernelPollEventFlag(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits);

/**
  * Wait for an event flag for a given bit pattern.
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @param timeout  - Timeout in microseconds
  * @return < 0 On error
  */
int ksceKernelWaitEventFlag(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits, SceUInt *timeout);

/**
  * Wait for an event flag for a given bit pattern with callback.
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @param timeout  - Timeout in microseconds
  * @return < 0 On error
  */
int ksceKernelWaitEventFlagCB(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits, SceUInt *timeout);

/**
  * Delete an event flag
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  *
  * @return < 0 On error
  */
int ksceKernelDeleteEventFlag(int evid);

/* Condition variables */

typedef struct  SceKernelLwCondWork {
	SceInt64 data[4];
} SceKernelLwCondWork;

typedef struct SceKernelLwCondOptParam {
	SceSize size;
} SceKernelLwCondOptParam;

/* Callbacks. */

/** Callback function prototype */
typedef int (*SceKernelCallbackFunction)(int notifyId, int notifyCount, int notifyArg, void *common);

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
 * cbid = ksceKernelCreateCallback("Exit Callback", exit_cb, NULL);
 * @endcode
 *
 * @param name - A textual name for the callback
 * @param func - A pointer to a function that will be called as the callback
 * @param arg  - Argument for the callback ?
 *
 * @return >= 0 A callback id which can be used in subsequent functions, < 0 an error.
 */
int ksceKernelCreateCallback(const char *name, unsigned int attr, SceKernelCallbackFunction func, void *arg);

/**
 * Delete a callback
 *
 * @param cb - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelDeleteCallback(SceUID cb);

/**
 * Notify a callback
 *
 * @param cb - The UID of the specified callback
 * @param arg2 - Passed as arg2 into the callback function
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelNotifyCallback(SceUID cb, int arg2);

/**
 * Cancel a callback ?
 *
 * @param cb - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelCancelCallback(SceUID cb);

/**
 * Get the callback count
 *
 * @param cb - The UID of the specified callback
 *
 * @return The callback count, < 0 on error
 */
int ksceKernelGetCallbackCount(SceUID cb);

/**
 * Check callback ?
 *
 * @return Something or another
 */
int ksceKernelCheckCallback(void);


/* Misc. */

/** Threadmgr types */
typedef enum SceKernelIdListType {
	SCE_KERNEL_TMID_Thread = 1,
	SCE_KERNEL_TMID_Semaphore = 2,
	SCE_KERNEL_TMID_EventFlag = 3,
	SCE_KERNEL_TMID_Mbox = 4,
	SCE_KERNEL_TMID_Vpl = 5,
	SCE_KERNEL_TMID_Fpl = 6,
	SCE_KERNEL_TMID_Mpipe = 7,
	SCE_KERNEL_TMID_Callback = 8,
	SCE_KERNEL_TMID_ThreadEventHandler = 9,
	SCE_KERNEL_TMID_Alarm = 10,
	SCE_KERNEL_TMID_VTimer = 11,
	SCE_KERNEL_TMID_SleepThread = 64,
	SCE_KERNEL_TMID_DelayThread = 65,
	SCE_KERNEL_TMID_SuspendThread = 66,
	SCE_KERNEL_TMID_DormantThread = 67,
} SceKernelIdListType;

/**
 * Get the type of a Threadmgr uid
 *
 * @param uid - The uid to get the type from
 *
 * @return The type, < 0 on error
 */
SceKernelIdListType ksceKernelGetThreadmgrUIDClass(SceUID uid);

/**
 * Get the system time (wide version)
 *
 * @return The system time
 */
SceInt64 ksceKernelGetSystemTimeWide(void);

/**
 * @brief ksceKernelGetThreadTLSAddr gets an address to a 4 bytes area of TLS memory for the specified thread
 * @param thid - The UID of the thread to access TLS
 * @param key - the TLS keyslot index
 * @return pointer to TLS memory
 */
void *ksceKernelGetThreadTLSAddr(SceUID thid, int key);

/**
 * @brief ksceKernelGetTLSAddr get pointer to TLS key area for current thread
 * @param key - the TLS keyslot index
 * @return pointer to TLS key value
 */
void *ksceKernelGetTLSAddr(int key);

/**
 * @brief      Gets the current process PID
 *
 * @return     Current PID
 */
SceUID ksceKernelGetProcessId(void);

/**
 * @brief      Runs a function with larger stack size
 *
 * @param[in]  stack_size  The stack size
 * @param[in]  to_call     To call
 * @param      args        The arguments
 *
 * @return     Zero on success
 */
int ksceKernelRunWithStack(int stack_size, int (*to_call)(void *), void *args);

/**
 * @brief      Call from an abort handler to get info on faulting process
 *
 * @param      info  Output info
 *
 * @return     Zero on success
 */
int ksceKernelGetFaultingProcess(SceKernelFaultingProcessInfo *info);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_H_ */

