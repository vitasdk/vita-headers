/**
 * \kernelgroup{ScePmMgr}
 * \usage{psp2kern/kernel/pm_mgr.h,ScePmMgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_PM_MGR_H_
#define _PSP2KERN_KERNEL_PM_MGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef char SceProductMode;

int kscePmMgrGetProductMode(SceProductMode *result);

int kscePmMgrIsExternalBootMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_PM_MGR_H_ */
