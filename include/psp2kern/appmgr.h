/**
 * \kernelgroup{SceAppMgr}
 * \usage{psp2kern/appmgr.h,SceAppMgrForDriver_stub}
 */


#ifndef _PSP2_KERNEL_APPMGR_H_
#define _PSP2_KERNEL_APPMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       Kill a process.
 * @param[in]   pid The process to kill.
 * @return      Zero on success, else < 0.
 */
int ksceAppMgrKillProcess(SceUID pid);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_APPMGR_H_ */
