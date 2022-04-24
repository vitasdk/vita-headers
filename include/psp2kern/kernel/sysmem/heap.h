/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem/heap.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_HEAP_H_
#define _PSP2KERN_KERNEL_SYSMEM_HEAP_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceKernelHeapAttr {
	SCE_KERNEL_HEAP_ATTR_HAS_AUTO_EXTEND = 0x00000001,
	SCE_KERNEL_HEAP_ATTR_HAS_MEMORY_TYPE = 0x00000400
} SceKernelHeapAttr;

typedef struct SceKernelHeapCreateOpt {
	SceSize size;
	union { //<! Union for compatibility
		SceUInt32 attr;
		SceUInt32 uselock; //<! Do not use uselock as it will be deprecated.
	};
	SceUInt32 field_8;
	SceUInt32 field_C;
	SceUInt32 memtype;
	SceUInt32 field_14;
	SceUInt32 field_18;
} SceKernelHeapCreateOpt;

typedef struct SceAllocOpt {
	SceSize size;   // 0x14
	SceSize data04; // maybe len align?
	SceSize align;
	int data0C;
	int data10;
} SceAllocOpt;

/**
 * Create heap area
 *
 * @param[in] name - The heap name
 * @param[in] size - The heap size
 * @param[in] opt  - The pointer of SceKernelHeapCreateOpt option data
 *
 * @return heapid on success, < 0 on error.
 */
SceUID ksceKernelCreateHeap(const char *name, SceSize size, SceKernelHeapCreateOpt *opt);

/**
 * Delete heap area
 *
 * @param[in] uid - The heapid
 *
 * @return always 0.
 *
 * note - Trigger an infinite loop if something fails internally.
 *        For example, passing an invalid heapid.
 */
int ksceKernelDeleteHeap(SceUID uid);

/**
 * Allocation the specified length of memory from heap
 *
 * @param[in] uid  - The heapid
 * @param[in] size - The alloc size
 *
 * @return The pointer of allocated memory on success, NULL on error.
 */
void *ksceKernelAllocHeapMemory(SceUID uid, SceSize size);

/**
 * Allocation the specified length of memory from heap with option
 *
 * @param[in] uid  - The heapid
 * @param[in] size - The alloc size
 * @param[in] opt  - The pointer of option
 *
 * @return The pointer of allocated memory on success, NULL on error.
 */
void *ksceKernelAllocHeapMemoryWithOption(SceUID heapid, SceSize len, SceAllocOpt *opt);

/**
 * Free allocated memory
 *
 * @param[in] uid - The heapid
 * @param[in] ptr - The pointer of allocated memory
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelFreeHeapMemory(SceUID uid, void *ptr);

/**
 * Alloc kernel memory
 *
 * @param[in] size - The alloction memory size
 *
 * @return memory pointer on success, NULL on error.
 */
void *ksceKernelAlloc(unsigned int size);

/**
 * Free kernel memory
 *
 * @param[in] ptr - The free memory pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelFree(void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_HEAP_H_ */
