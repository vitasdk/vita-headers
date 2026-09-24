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

/**
 * Raises breakpoint 0x81 and does not return.
 *
 * This is the ::SceLibSsp alias of ::__stack_chk_fail. Both names use the same
 * entry point on FW 3.60.
 */
__attribute__((__noreturn__))
void sceLibSspStackChkFail(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SSP_H_ */
