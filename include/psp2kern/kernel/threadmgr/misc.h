/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/misc.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_MISC_H_
#define _PSP2KERN_KERNEL_THREADMGR_MISC_H_

#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the type of a Threadmgr uid
 *
 * @param uid - The uid to get the type from
 *
 * @return The type, < 0 on error
 */
SceKernelIdListType ksceKernelGetThreadmgrUIDClass(SceUID uid);

/**
 * Get the system time
 *
 * @return The system time
 */
SceUInt32 ksceKernelGetSystemTimeLow(void);

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
 * @brief Set Permission
 *
 * @param[in] value - The new permission
 *
 * @return previous permission value
 */
int ksceKernelSetPermission(int value);

/**
 * @brief      Gets the current process PID
 *
 * @return     Current PID
 */
SceUID ksceKernelGetProcessId(void);

/**
 * @brief Get Process id from Thread Local Storage
 *
 * @return current process id
 */
SceUID ksceKernelGetProcessIdFromTLS(void);

/**
 * @brief Set Process id to Thread Local Storage
 *
 * @param[in] value - The new process id
 *
 * @return previous process id
 */
SceUID ksceKernelSetProcessIdToTLS(SceUID pid);

/**
 * @brief      Runs a function with larger stack size
 *
 * @param[in]  stack_size  The stack size
 * @param[in]  to_call     To call
 * @param      args        The arguments
 *
 * @return     Zero on success
 */
int ksceKernelRunWithStack(SceSize stack_size, int (* to_call)(void *), void *args);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_MISC_H_ */
