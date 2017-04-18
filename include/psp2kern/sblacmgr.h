/**
 * \kernelgroup{SceSblACMgr}
 * \usage{psp2kern/sblacmgr.h,SceSblACMgrForDriver_stub}
 */


#ifndef _PSP2_KERNEL_SBLACMGR_H_
#define _PSP2_KERNEL_SBLACMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceSblACMgrIsShell(SceUID pid);
int ksceSblACMgrIsGameProgram(SceUID pid);
int ksceSblACMgrIsNonGameProgram(SceUID pid);
int ksceSblACMgrIsDevelopmentMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SBLACMGR_H_ */

