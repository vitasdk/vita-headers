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

typedef struct SceKernelAddrPair { // do not use
	uint32_t addr;             //!< Address
	uint32_t length;           //!< Length
} SceKernelAddrPair;

typedef struct SceKernelVARange { // size is 0x8
	uint32_t addr;
	SceSize size;
} SceKernelVARange;

typedef struct SceKernelPARange { // size is 0x8
	uint32_t addr;
	SceSize size;
} SceKernelPARange;

typedef struct SceKernelPAVector { // size is 0x14
	SceSize size;              //!< Size of this structure
	union {
		struct {
			uint32_t ranges_size;    //!< Ex: 8
			uint32_t data_in_vector; //!< Must be <= 8
			uint32_t count;
			SceKernelPARange *ranges;
		};
		struct { // do not use.
			uint32_t list_size;             //!< Size in elements of the list array
			uint32_t ret_length;            //!< Total physical size of the memory pairs
			uint32_t ret_count;             //!< Number of elements of list filled by ksceKernelGetPaddrList
			SceKernelAddrPair *list;        //!< Array of physical addresses and their lengths pairs
		};
	};
} SceKernelPAVector;

typedef SceKernelPAVector SceKernelPaddrList; // do not use.

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_TYPES_H_ */
