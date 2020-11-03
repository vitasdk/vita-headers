/**
 * \kernelgroup{SceSysclib}
 * \usage{psp2kern/kernel/sysclib.h,SceSysclibForDriver_stub}
 */

#ifndef _PSP2_KERNEL_SYSCLIB_H_
#define _PSP2_KERNEL_SYSCLIB_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void __stack_chk_fail(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SYSCLIB_H_ */
