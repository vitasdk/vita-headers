/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/debugger.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2_KERNEL_THREADMGR_DEBUGGER_H_
#define _PSP2_KERNEL_THREADMGR_DEBUGGER_H_

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

typedef struct SceKernelFaultingProcessInfo {
	SceUID pid;
	SceUID faultingThreadId; //!< Kernel UID of the faulting thread
} SceKernelFaultingProcessInfo;

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
 * @brief      Call from an abort handler to get info on faulting process
 *
 * @param      info  Output info
 *
 * @return     Zero on success
 */
int ksceKernelGetFaultingProcess(SceKernelFaultingProcessInfo *info);

/**
 * @brief       Change the thread suspension status to another value.
 *
 * More research needs to be done to find out exactly what each status actually means. Some examples of useful scenarios:
 * When handling an exception changing the status to 0x1002 (on a newly suspended thread) will stop the kernel rethrowing the same exception.
 * When resuming a suspended thread changing the status to 2 will allow it to resume.
 *
 * @param[in]   thid    The thread to change.
 * @param[in]   status  The new status for suspension.
 * @return      Zero on success, else < 0 on error.
 */
int ksceKernelChangeThreadSuspendStatus(SceUID thid, int status);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_DEBUGGER_H_ */
