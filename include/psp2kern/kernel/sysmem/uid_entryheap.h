/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/uid_entryheap.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_UID_ENTRYHEAP_H_
#define _PSP2KERN_KERNEL_SYSMEM_UID_ENTRYHEAP_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


SceInt32 ksceKernelUIDEntryHeapGetInfo(SceUID entryHeapId, void *pInfo);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_UID_ENTRYHEAP_H_ */
