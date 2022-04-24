/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/mmu.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_MMU_H_
#define _PSP2KERN_KERNEL_SYSMEM_MMU_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the physical address of a given virtual address
 *
 * @param[in]  va - The virtual address
 * @param[out] pa - The physical address
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelVAtoPA(const void *va, uintptr_t *pa);

/**
 * Get the physical address list of a given virtual address range
 *
 * @param[in]  va_range  - The virtual address range
 * @param[out] pa_vector - The vector of physical addresses
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelVARangeToPAVector(const SceKernelVARange *va_range, SceKernelPAVector *pa_vector);

typedef struct SceKernelProcessContext {
	SceUInt32 TTBR1;
	SceUInt32 DACR;
	SceUInt32 CONTEXTIDR;
} SceKernelProcessContext;

int ksceKernelGetPidContext(SceUID pid, SceKernelProcessContext **ctx);

#define ksceKernelGetPaddr(va, pa) ksceKernelVAtoPA(va, pa)
#define ksceKernelGetPaddrList(input, list) ksceKernelVARangeToPAVector((const SceKernelVARange *)input, list)

// Not exist on 3.60
int ksceKernelSwitchVmaForPid(SceUID pid);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_MMU_H_ */
