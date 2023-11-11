/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/nameheap.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_NAMEHEAP_H_
#define _PSP2KERN_KERNEL_SYSMEM_NAMEHEAP_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


int ksceKernelNameHeapGetInfo(void *pInfo);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_NAMEHEAP_H_ */
