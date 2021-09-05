/**
 * \kernelgroup{SceGpuEs4}
 * \usage{psp2kern/gpu_es4.h,SceGpuEs4ForDriver}
 */

#ifndef _PSP2_KERNEL_GPU_ES4_
#define _PSP2_KERNEL_GPU_ES4_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int PVRSRVGetMiscInfoKM(void *info);

int ksceGpuGetRegisterDump(void *dst, SceSize size);

int ksceGpuMmuMapMemory(void *mmuContext, uint32_t vaddr, void *base, uint32_t size, uint32_t flags);
int ksceGpuMmuUnmapMemory(void *mmuContext, uint32_t vaddr, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_GPU_ES4_ */
