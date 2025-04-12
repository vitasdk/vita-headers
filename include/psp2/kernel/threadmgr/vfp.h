/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/vfp.h,SceKernelThreadMgr_stub}
 */


#ifndef _PSP2_KERNEL_THREADMGR_VFP_H_
#define _PSP2_KERNEL_THREADMGR_VFP_H_

#include <psp2/types.h>
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
int sceKernelChangeThreadVfpException(SceUInt32 clear, SceUInt32 set);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_VFP_H_ */
