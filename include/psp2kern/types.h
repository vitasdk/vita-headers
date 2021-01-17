/**
 * \kernelgroup{SceTypes}
 * \usage{psp2kern/types.h}
 */

#ifndef _PSP2_KERNEL_TYPES_H_
#define _PSP2_KERNEL_TYPES_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelPARange { // size is 0x8
	uint32_t paddr;
	uint32_t length;
} SceKernelPARange;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_TYPES_H_ */
