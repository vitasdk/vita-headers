/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/debugger.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_DEBUGGER_H_
#define _PSP2KERN_KERNEL_THREADMGR_DEBUGGER_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/** Structure representing all ARM registers */
typedef struct SceArmCpuRegisters
{
    uint32_t    r0;
    uint32_t    r1;
    uint32_t    r2;
    uint32_t    r3;
    uint32_t    r4;
    uint32_t    r5;
    uint32_t    r6;
    uint32_t    r7;
    uint32_t    r8;
    uint32_t    r9;
    uint32_t    r10;
    uint32_t    r11;
    uint32_t    r12;
    uint32_t    sp;
    uint32_t    lr;
    uint32_t    pc;
    uint32_t    cpsr;
    uint32_t    fpscr;
} SceArmCpuRegisters;

/* Typedef for compatibility */
typedef SceArmCpuRegisters ArmCpuRegisters;

/** Structure containing a threads register states. */
typedef struct SceThreadCpuRegisters
{
    union {
        struct { // These are wrong. Please use "entry[2]"
            /** Set of registers used for user mode. */
            SceArmCpuRegisters user;

            /** Set of registers used for kernel mode. */
            SceArmCpuRegisters kernel;
        };
        SceArmCpuRegisters entry[2];
    };
} SceThreadCpuRegisters;

/* Typedef for compatibility */
typedef SceThreadCpuRegisters ThreadCpuRegisters;

typedef struct SceKernelThreadContextInfo {
	ScePID process_id;  //<! Process ID the thread scheduled on this CPU belongs to
	SceUID thread_id;   //<! Thread ID of the thread scheduled on this CPU
} SceKernelThreadContextInfo;


/**
 * @brief       Retrieve a list of all threads belonging to a process.
 * @param[in]   pid         The process to query.
 * @param[out]  ids         The list of thread ids. Can be NULL if output is not required.
 * @param[in]   n           The max number of thread ids to copy out.
 * @param[out]  copy_count  The number of thread ids copied.
 * @return      The number of threads within the process, else < 0 on error.
 */
int ksceKernelGetThreadIdList(SceUID pid, SceUID *ids, int n, int *copy_count);

/**
 * @brief       Query the state of the registers for a suspended thread.
 *
 * The registers returned are the user/kernel set for the requested thread.
 * It's not certain that user/kernel is correct representation, instead it could be current/exception.
 * The thread provided must be suspended for this function to succeed.
 *
 * @param[in]   thid        The thread to query.
 * @param[out]  registers   The set of registers belonging to the thread.
 * @return      Zero on success, else < 0 on error.
 */
int ksceKernelGetThreadCpuRegisters(SceUID thid, SceThreadCpuRegisters *registers);

/**
 * @brief      Obtain the context information for the thread scheduled on this CPU.
 *
 * This function can be called from an exception handler to obtain information about
 * the thread that was interrupted.
 *
 * @param[out]  pInfo   Context information of the thread
 *
 * @return      Zero on success, < 0 on error
 */
int ksceKernelGetThreadContextInfo(SceKernelThreadContextInfo *pInfo);


/**
 * @brief       Change the thread suspension status to another value.
 *
 * More research needs to be done to find out exactly what each status actually means. Some examples of useful scenarios:
 * When handling an exception changing the status to 0x1002 (on a newly suspended thread) will stop the kernel rethrowing the same exception.
 * When resuming a suspended thread changing the status to 2 will allow it to resume.
 * 
 * @note The valid mask for \p status is 0xF7F03.
 *
 * @param[in]   thid    The thread to change.
 * @param[in]   status  The new status for suspension.
 * @return      Zero on success, else < 0 on error.
 */
int ksceKernelChangeThreadSuspendStatus(SceUID thid, int status);

/**
 * @brief Get thread PUID from GUID.
 *
 * @param[in] thid - The thread global uid.
 *
 * @return thread_puid on success, else < 0 on error.
 */
SceUID ksceKernelGetUserThreadId(SceUID thid);

/**
 * @brief Get thread suspend status.
 *
 * @param[in] thid - The thread global uid.
 *
 * @return    Suspend status on success, else <0 on error.
 */
int ksceKernelIsThreadDebugSuspended(SceUID thid);

/**
 * @brief Debug suspend a thread.
 *
 * @note The valid mask for \p status is 0xF7F03.
 * 
 * @param[in] thid    The thread global uid.
 * @param[in] status  The suspend status.
 *  
 * @return    Zero on success, else <0 on error.
 */
int ksceKernelDebugSuspendThread(SceUID thid, int status);

/**
 * @brief Debug resume a thread.
 *
 * @note The valid mask for \p status is 0xF7F03.
 *
 * @param[in] thid    The thread global uid.
 * @param[in] status  The suspend status to resume from.
 *  
 * @return    Zero on success, else <0 on error.
 */
int ksceKernelDebugResumeThread(SceUID thid, int status);


/* For backwards compatibility */
typedef struct __attribute__((deprecated("This structure has been replaced by SceKernelThreadContextInfo"))) SceKernelFaultingProcessInfo {
    SceUID pid;
    SceUID faultingThreadId;
} SceKernelFaultingProcessInfo;

#define ksceKernelGetFaultingProcessInfo(info) ksceKernelGetThreadContextInfo((SceKernelThreadContextInfo*)info)

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_DEBUGGER_H_ */
