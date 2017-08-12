/**
 * \kernelgroup{SceSblAIMgr}
 * \usage{psp2kern/sblaimgr.h,SceSblAIMgrForDriver_stub}
 */


#ifndef _PSP2_KERNEL_SBLACMGR_H_
#define _PSP2_KERNEL_SBLACMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceSblAimgrGetSMI(void);
int ksceSblAimgrIsTest(void);
int ksceSblAimgrIsTool(void);
int ksceSblAimgrIsDEX(void);
int ksceSblAimgrIsCEX(void);
int ksceSblAimgrIsVITA(void);
int ksceSblAimgrIsDolce(void);
int ksceSblAimgrIsGenuineVITA(void);
int ksceSblAimgrIsGenuineDolce(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SBLAIMGR_H_ */

