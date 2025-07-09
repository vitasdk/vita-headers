/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2common/kernel/threadmgr.h}
 */

#ifndef _PSP2COMMON_KERNEL_THREADMGR_H_
#define _PSP2COMMON_KERNEL_THREADMGR_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

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

typedef enum SceKernelThreadEventType {
	SCE_KERNEL_THREAD_EVENT_TYPE_START = 0x00000004,
	SCE_KERNEL_THREAD_EVENT_TYPE_EXIT  = 0x00000008
} SceKernelThreadEventType;

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

typedef int (* SceKernelThreadEntry)(SceSize args, void *argp);

typedef int (* SceKernelThreadEventHandler)(SceInt32 type, SceUID threadId, SceInt32 arg, void *pCommon);

/** Additional options used when creating threads. */
typedef struct SceKernelThreadOptParam {
	/** Size of the ::SceKernelThreadOptParam structure. */
	SceSize     size;
	/** Attributes */
	SceUInt32   attr;
	SceUInt32 kStackMemType;
	SceUInt32 uStackMemType;
	SceUInt32 uTLSMemType;
	SceUInt32 uStackMemid;
	SceUInt32 data_0x18;
} SceKernelThreadOptParam;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceKernelThreadOptParam);

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

/** Inherit calling thread affinity mask. */
#define SCE_KERNEL_THREAD_CPU_AFFINITY_MASK_DEFAULT (0)



/** Callback function prototype */
typedef int (* SceKernelCallbackFunction)(int notifyId, int notifyCount, int notifyArg, void *userData);

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
VITASDK_BUILD_ASSERT_EQ(0x3C, SceKernelCallbackInfo);




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



typedef enum SceKernelWaitableAttribute {
	SCE_KERNEL_ATTR_THREAD_FIFO  = 0x00000000, //!< Waiting threads First input First output
	SCE_KERNEL_ATTR_THREAD_PRIO  = 0x00002000, //!< Waiting threads queued on priority basis
	SCE_KERNEL_ATTR_OPENABLE     = 0x00000080  //!< Sync object can be accessed by sceKernelOpenXxx
} SceKernelWaitableAttribute;

/** Event flag creation attributes */
typedef enum SceEventFlagAttributes {
	SCE_DEPRECATED(SCE_EVENT_THREAD_FIFO) = SCE_KERNEL_ATTR_THREAD_FIFO, //!< Use SCE_KERNEL_ATTR_THREAD_FIFO
	SCE_DEPRECATED(SCE_EVENT_THREAD_PRIO) = SCE_KERNEL_ATTR_THREAD_PRIO, //!< Use SCE_KERNEL_ATTR_THREAD_PRIO
	SCE_EVENT_WAITSINGLE   = 0,          //!< Sync object can only be waited upon by one thread.
	SCE_EVENT_WAITMULTIPLE = 0x00001000, //!< Sync object can be waited upon by multiple threads.
	SCE_DEPRECATED(SCE_EVENT_OPENABLE) = SCE_KERNEL_ATTR_OPENABLE //!< Use SCE_KERNEL_ATTR_OPENABLE
} SceEventFlagAttributes;

typedef struct SceKernelEventFlagOptParam {
	SceSize         size;
} SceKernelEventFlagOptParam;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelEventFlagOptParam);

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
VITASDK_BUILD_ASSERT_EQ(0x38, SceKernelEventFlagInfo);

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



typedef struct	SceKernelLwCondWork {
	SceInt32 data[4];
} SceKernelLwCondWork;
VITASDK_BUILD_ASSERT_EQ(0x10, SceKernelLwCondWork);

typedef struct SceKernelLwCondOptParam {
	SceSize	size;
} SceKernelLwCondOptParam;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelLwCondOptParam);



typedef struct	SceKernelLwMutexWork {
	SceInt64 data[4];
} SceKernelLwMutexWork;
VITASDK_BUILD_ASSERT_EQ(0x20, SceKernelLwMutexWork);

typedef struct SceKernelLwMutexOptParam {
	SceSize	size;
} SceKernelLwMutexOptParam;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelLwMutexOptParam);




typedef enum SceKernelMutexAttribute {
	SCE_KERNEL_MUTEX_ATTR_RECURSIVE   = 0x02,
	SCE_KERNEL_MUTEX_ATTR_CEILING     = 0x04
} SceKernelMutexAttribute;

/** Additional options used when creating mutexes. */
typedef struct SceKernelMutexOptParam {
	/** Size of the ::SceKernelMutexOptParam structure. */
	SceSize     size;
	int         ceilingPriority;
} SceKernelMutexOptParam;
VITASDK_BUILD_ASSERT_EQ(8, SceKernelMutexOptParam);

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
VITASDK_BUILD_ASSERT_EQ(0x3C, SceKernelMutexInfo);



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

/*
 * Value linked to fpcsr
 */
#define SCE_KERNEL_VFP_EXCP_IOC (0x00000001)
#define SCE_KERNEL_VFP_EXCP_DZC (0x00000002)
#define SCE_KERNEL_VFP_EXCP_OFC (0x00000004)
#define SCE_KERNEL_VFP_EXCP_UFC (0x00000008)
#define SCE_KERNEL_VFP_EXCP_IXC (0x00000010)
#define SCE_KERNEL_VFP_EXCP_IDC (0x00000080)
#define SCE_KERNEL_VFP_EXCP_QC  (0x08000000)
#define SCE_KERNEL_VFP_EXCP_ALL (SCE_KERNEL_VFP_EXCP_IOC | SCE_KERNEL_VFP_EXCP_DZC | SCE_KERNEL_VFP_EXCP_OFC | SCE_KERNEL_VFP_EXCP_UFC | SCE_KERNEL_VFP_EXCP_IXC | SCE_KERNEL_VFP_EXCP_IDC | SCE_KERNEL_VFP_EXCP_QC)


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_KERNEL_THREADMGR_H_ */

