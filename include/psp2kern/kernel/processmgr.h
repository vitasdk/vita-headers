/**
 * \kernelgroup{SceProcessmgr}
 * \usage{psp2kern/kernel/processmgr.h,SceProcessmgrForKernel_stub}
 */


#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void *ksceKernelGetProcessKernelBuf(SceUID pid);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */

