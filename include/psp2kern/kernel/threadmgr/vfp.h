/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/vfp.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_VFP_H_
#define _PSP2KERN_KERNEL_THREADMGR_VFP_H_

#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Change the current thread vfp exception mask
 *
 * @param[in] clear - The value to clear flag. ORed `SCE_KERNEL_VFP_EXCP_*`
 * @param[in]   set - The value to set flag. ORed `SCE_KERNEL_VFP_EXCP_*`
 *
 * @return SCE_OK on success, < 0 on error
 */
int ksceKernelChangeThreadVfpException(SceUInt32 clear, SceUInt32 set);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_VFP_H_ */
