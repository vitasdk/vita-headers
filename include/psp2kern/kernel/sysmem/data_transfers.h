/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/data_transfers.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_DATA_TRANSFERS_H_
#define _PSP2KERN_KERNEL_SYSMEM_DATA_TRANSFERS_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * TTBR1: Translation Table Base Register 1.
 *        The 0x40000000-0xFFFFFFFF virtual region is mapped by TTBR1.
 *        This range is all userland memory.
 *        At kernel context, kernel TTBR1 is set, but it is not mapped to anything.
 *
 * DACR:  Domain access control register.
 *        Simply put, memory access permission.
 *        See: https://developer.arm.com/documentation/ddi0406/c/System-Level-Architecture/System-Control-Registers-in-a-VMSA-implementation/VMSA-System-control-registers-descriptions--in-register-order/DACR--Domain-Access-Control-Register--VMSA?lang=en
 */

/**
 * Memcpy from user memory
 *
 * @param[in] dst - The userland or kernel memory pointer.
 * @param[in] src - The userland memory pointer.
 * @param[in] len - The memcpy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note Cannot use this function in kernel context. Use ksceKernelProcMemcpyFromUser.
 *       DACR          - 0x55555555
 *       Setting TTBR1 - No (use current TTBR1)
 */
int ksceKernelMemcpyFromUser(void *dst, const void *src, SceSize len);

/**
 * Memcpy from user memory with process
 *
 * @param[in] pid - The target process id.
 * @param[in] dst - The userland or kernel memory pointer.
 * @param[in] src - The userland memory pointer.
 * @param[in] len - The memcpy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - Invoke ksceKernelMemcpyFromUser with disable interrupts.
 *         Setting TTBR1 - Yes
 */
int ksceKernelProcMemcpyFromUser(SceUID pid, void *dst, const void *src, SceSize len);

/**
 * Memcpy to user memory
 *
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland or kernel memory pointer.
 * @param[in] len - The memcpy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note Cannot use this function in kernel context. Use ksceKernelProcMemcpyToUser.
 *       DACR          - 0x55555555
 *       Setting TTBR1 - No (use current TTBR1)
 */
int ksceKernelMemcpyToUser(void *dst, const void *src, SceSize len);

/**
 * Memcpy from user memory with process
 *
 * @param[in] pid - The target process id.
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland or kernel memory pointer.
 * @param[in] len - The memcpy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - Invoke ksceKernelMemcpyToUser with disable interrupts.
 *         Setting TTBR1 - Yes
 */
int ksceKernelProcMemcpyToUser(SceUID pid, void *dst, const void *src, SceSize len);

/**
 * Memcpy to user RO memory
 *
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland or kernel memory pointer.
 * @param[in] len - The memcpy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note Cannot use this function in kernel context.
 *       DACR          - 0x15450FC3
 *       Setting TTBR1 - No (use current TTBR1)
 */
int ksceKernelMemcpyToUserRo(void *dst, const void *src, SceSize len);

/**
 * Memcpy to user RO memory with DcacheAndL2WritebackRange
 *
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland or kernel memory pointer.
 * @param[in] len - The memcpy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note Cannot use this function in kernel context. Use ksceKernelProcMemcpyToUserRx.
 *       DACR          - 0x15450FC3
 *       Setting TTBR1 - No (use current TTBR1)
 */
int ksceKernelMemcpyToUserRx(void *dst, const void *src, SceSize len);

/**
 * Memcpy to user RX memory with process
 *
 * @param[in] pid - The target process id.
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland or kernel memory pointer.
 * @param[in] len - The memcpy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - Invoke ksceKernelMemcpyToUserRx with disable interrupts.
 *         Setting TTBR1 - Yes
 */
int ksceKernelProcMemcpyToUserRx(SceUID pid, void *dst, const void *src, SceSize len);

/**
 * Strncpy from user memory
 *
 * @param[in] dst - The userland or kernel memory pointer.
 * @param[in] src - The userland memory pointer.
 * @param[in] len - The copy length.
 *
 * @return The copied length on success, < 0 on error.
 *
 * @note Cannot use this function in kernel context. Use ksceKernelProcStrncpyFromUser.
 *       DACR          - 0x55555555
 *       Setting TTBR1 - No (use current TTBR1)
 */
SceSSize ksceKernelStrncpyFromUser(char *dst, const char *src, SceSize len);

/**
 * Strncpy from user memory with process
 *
 * @param[in] pid - The target process id.
 * @param[in] dst - The userland or kernel memory pointer.
 * @param[in] src - The userland memory pointer.
 * @param[in] len - The copy length.
 *
 * @return The copied length on success, < 0 on error.
 *
 * @note - Invoke ksceKernelStrncpyFromUserInternal with disable interrupts.
 *         DACR          - Current process DACR
 *         Setting TTBR1 - Yes
 */
SceSSize ksceKernelProcStrncpyFromUser(SceUID pid, char *dst, const char *src, SceSize len);

/**
 * Strncpy to user memory
 *
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland or kernel memory pointer.
 * @param[in] len - The copy length.
 *
 * @return The copied length on success, < 0 on error.
 *
 * @note Cannot use this function in kernel context. Use ksceKernelProcStrncpyToUser.
 *       DACR          - 0x55555555
 *       Setting TTBR1 - No (use current TTBR1)
 */
SceSSize ksceKernelStrncpyToUser(char *dst, const char *src, SceSize len);

/**
 * Strncpy to user memory with process
 *
 * @param[in] pid - The target process id.
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland or kernel memory pointer.
 * @param[in] len - The copy length.
 *
 * @return The copied length on success, < 0 on error.
 *
 * @note - Invoke ksceKernelStrncpyToUserInternal with disable interrupts.
 *         DACR          - Current process DACR
 *         Setting TTBR1 - Yes
 */
SceSSize ksceKernelProcStrncpyToUser(SceUID pid, char *dst, const char *src, SceSize len);

/**
 * Strnlen user memory
 *
 * @param[in] s - The userland memory pointer.
 * @param[in] n - The max length.
 *
 * @return The strings length
 *
 * @note Cannot use this function in kernel context. Use ksceKernelProcStrnlenUser.
 *       DACR          - 0x55555555
 *       Setting TTBR1 - No (use current TTBR1)
 */
SceSize ksceKernelStrnlenUser(const char *s, SceSize n);

/**
 * Strnlen user memory with process
 *
 * @param[in] pid - The target process id.
 * @param[in] s   - The userland memory pointer.
 * @param[in] n   - The max length.
 *
 * @return The strings length on success, < 0 on error.
 *
 * @note - Invoke ksceKernelStrnlenUserInternal with disable interrupts.
 *         DACR          - Current process DACR
 *         Setting TTBR1 - Yes
 */
SceSSize ksceKernelProcStrnlenUser(SceUID pid, const char *s, SceSize n);

/**
 * Memcpy user memory to user memory
 *
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland memory pointer.
 * @param[in] len - The copy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note Cannot use this function in kernel context. Use ksceKernelProcUserMemcpy.
 *       DACR          - 0x55555555
 *       Setting TTBR1 - No (use current TTBR1)
 */
int ksceKernelUserMemcpy(void *dst, const void *src, SceSize len);

/**
 * Memcpy user memory to user memory with process
 *
 * @param[in] pid - The target process id.
 * @param[in] dst - The userland memory pointer.
 * @param[in] src - The userland memory pointer.
 * @param[in] len - The copy length.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - Invoke ksceKernelUserMemcpyInternal with disable interrupts.
 *         DACR          - Current process DACR
 *         Setting TTBR1 - Yes
 */
int ksceKernelProcUserMemcpy(SceUID pid, void *dst, const void *src, SceSize len);


/* Macros for backwards compatibility */
#define ksceKernelMemcpyUserToKernel(__dst__, __src__, __len__)                  ksceKernelMemcpyFromUser((__dst__), (__src__), (__len__))
#define ksceKernelMemcpyUserToKernelForPid(__pid__, __dst__, __src__, __len__)   ksceKernelProcMemcpyFromUser((__pid__), (__dst__), (__src__), (__len__))
#define ksceKernelMemcpyKernelToUser(__dst__, __src__, __len__)                  ksceKernelMemcpyToUser((__dst__), (__src__), (__len__))
#define ksceKernelMemcpyToUserRo(__dst__, __src__, __len__)                      ksceKernelMemcpyToUserRo((__dst__), (__src__), (__len__))
#define ksceKernelMemcpyToUserRx(__dst__, __src__, __len__)                      ksceKernelMemcpyToUserRx((__dst__), (__src__), (__len__))
#define ksceKernelRxMemcpyKernelToUserForPid(__pid__, __dst__, __src__, __len__) ksceKernelProcMemcpyToUserRx((__pid__), (__dst__), (__src__), (__len__))

#define ksceKernelStrncpyUserToKernel(__dst__, __src__, __len__)        ksceKernelStrncpyFromUser((__dst__), (__src__), (__len__))
#define ksceKernelStrncpyUserForPid(__pid__, __dst__, __src__, __len__) ksceKernelProcStrncpyFromUser((__pid__), (__dst__), (__src__), (__len__))
#define ksceKernelStrncpyKernelToUser(__dst__, __src__, __len__)        ksceKernelStrncpyToUser((__dst__), (__src__), (__len__))


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_DATA_TRANSFERS_H_ */
