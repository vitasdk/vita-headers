/**
 * \usergroup{SceLibSsp}
 * \usage{psp2/kernel/ssp.h,SceLibKernel_stub}
 */

#ifndef _PSP2_KERNEL_SSP_H_
#define _PSP2_KERNEL_SSP_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Raises the stack-protector failure trap and does not return. */
__attribute__((__noreturn__))
void sceLibSspStackChkFail(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SSP_H_ */
