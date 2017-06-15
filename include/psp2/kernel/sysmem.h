/**
 * \usergroup{SceSysmem}
 * \usage{psp2/kernel/sysmem.h,SceSysmem_stub}
 */


#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceKernelMemBlockType {
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE          = 0x0c208060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RW                  = 0x0c20d060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_RW     = 0x0c80d060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_NC_RW  = 0x0d808060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW            = 0x09408060
} SceKernelMemBlockType;

typedef struct SceKernelAllocMemBlockOpt {
	SceSize size;
	SceUInt32 attr;
	SceSize alignment;
	SceUInt32 uidBaseBlock;
	const char *strBaseBlockName;
	int flags;                     //! Unknown flags 0x10 or 0x30 for ::sceKernelOpenMemBlock
	int reserved[10];
} SceKernelAllocMemBlockOpt;

typedef enum SceKernelModel {
	SCE_KERNEL_MODEL_VITA   = 0x10000,
	SCE_KERNEL_MODEL_VITATV = 0x20000
} SceKernelModel;

typedef struct SceKernelMemBlockInfo {
	SceSize size;
	void *mappedBase;
	SceSize mappedSize;
	int memoryType;
	SceUInt32 access;
	SceKernelMemBlockType type;
} SceKernelMemBlockInfo;

typedef enum SceKernelMemoryAccessType {
	SCE_KERNEL_MEMORY_ACCESS_X = 0x01,
	SCE_KERNEL_MEMORY_ACCESS_W = 0x02,
	SCE_KERNEL_MEMORY_ACCESS_R = 0x04
} SceKernelMemoryAccessType;

typedef enum SceKernelMemoryType {
	SCE_KERNEL_MEMORY_TYPE_NORMAL_NC = 0x80,
	SCE_KERNEL_MEMORY_TYPE_NORMAL    = 0xD0
} SceKernelMemoryType;

/***
 * Allocates a new memory block
 *
 * @param[in] name - Name for the memory block
 * @param[in] type - Type of the memory to allocate
 * @param[in] size - Size of the memory to allocate
 * @param[in] optp - Memory block options?
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID sceKernelAllocMemBlock(const char *name, SceKernelMemBlockType type, int size, SceKernelAllocMemBlockOpt *optp);

/***
 * Frees new memory block
 *
 * @param[in] uid - SceUID of the memory block to free
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelFreeMemBlock(SceUID uid);

/***
 * Gets the base address of a memory block
 *
 * @param[in] uid - SceUID of the memory block to free
 * @param[out] basep - Base address of the memory block identified by SceUID
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetMemBlockBase(SceUID uid, void **basep);

SceUID sceKernelFindMemBlockByAddr(const void *addr, SceSize size);

int sceKernelGetMemBlockInfoByAddr(void *base, SceKernelMemBlockInfo *info);
int sceKernelGetMemBlockInfoByRange(void *base, SceSize size, SceKernelMemBlockInfo *info);

SceUID sceKernelAllocMemBlockForVM(const char *name, SceSize size);
int sceKernelSyncVMDomain(SceUID uid, void *data, SceSize size);
int sceKernelOpenVMDomain(void);
int sceKernelCloseVMDomain(void);

int sceKernelOpenMemBlock(const char *name, int flags);
int sceKernelCloseMemBlock(SceUID uid);

/***
 * Get the model number of the device
 *
 * @return A value from SCE_KERNEL_MODEL
*/
int sceKernelGetModelForCDialog();

/***
 * Get the model number of the device
 *
 * @return A value from SCE_KERNEL_MODEL
*/
int sceKernelGetModel();

#ifdef __cplusplus
}
#endif

#endif

