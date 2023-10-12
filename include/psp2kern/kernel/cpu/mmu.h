/**
 * \kernelgroup{SceCpu}
 * \usage{psp2kern/kernel/cpu/mmu.h}
 */


#ifndef _PSP2KERN_KERNEL_CPU_MMU_H_
#define _PSP2KERN_KERNEL_CPU_MMU_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


int ksceKernelMMUGetMemoryType(void *vaddr);

int ksceKernelMMUVAtoPA(void *va, SceUIntPtr *pa);
int ksceKernelMMUVAtoPAWithMode(int mode, void *va, SceUIntPtr *pa);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_CPU_MMU_H_ */
