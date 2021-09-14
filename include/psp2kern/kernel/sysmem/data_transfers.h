/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/data_transfers.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2_KERNEL_SYSMEM_DATA_TRANSFERS_H_
#define _PSP2_KERNEL_SYSMEM_DATA_TRANSFERS_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Memory copy from user
 *
 * @param[in] dst - The pointer of kern memory output buffer
 * @param[in] src - The pointer of user memory
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemcpyUserToKernel(void *dst, uintptr_t src, SceSize len);

/**
 * Memory copy from user with process
 *
 * @param[in] pid - The target process id
 * @param[in] dst - The pointer of kern memory
 * @param[in] src - The pointer of user memory
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemcpyUserToKernelForPid(SceUID pid, void *dst, uintptr_t src, SceSize len);

/**
 * Memory copy to user
 *
 * @param[in] dst - The pointer of user memory
 * @param[in] src - The pointer of kern memory
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemcpyKernelToUser(uintptr_t dst, const void *src, SceSize len);

/**
 * Memory copy to user Read only memory
 *
 * @param[in] dst - The pointer of user memory
 * @param[in] src - The pointer of kern memory
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemcpyToUserRo(uintptr_t dst, const void *src, SceSize len);

/**
 * Memory copy to user Read execute memory
 *
 * @param[in] dst - The pointer of user memory
 * @param[in] src - The pointer of kern memory
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemcpyToUserRx(uintptr_t dst, const void *src, SceSize len);

/**
 * Memory copy to user with process
 *
 * @param[in] pid - The target process id
 * @param[in] dst - The pointer of user memory
 * @param[in] src - The pointer of kern memory
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelRxMemcpyKernelToUserForPid(SceUID pid, uintptr_t dst, const void *src, SceSize len);

/**
 * Strncpy from user
 *
 * @param[in] dst - The pointer of user space strings
 * @param[in] src - The pointer of kern strings output
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStrncpyUserToKernel(void *dst, uintptr_t src, SceSize len);

/**
 * Strncpy to user
 *
 * @param[in] dst - The pointer of kern space strings
 * @param[in] src - The pointer of user strings output
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelStrncpyKernelToUser(uintptr_t dst, const void *src, SceSize len);
int ksceKernelStrncpyUserForPid(SceUID pid, void *dst, uintptr_t src, SceSize len);

#ifdef __cplusplus
}
#endif

#endif
