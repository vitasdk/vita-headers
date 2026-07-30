/**
 * \usergroup{SceSysmem}
 * \usage{psp2/kernel/sysmem.h,SceSysmem_stub}
 */


#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/kernel/sysmem.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceKernelAllocMemBlockOpt {
	SceSize size;
	SceUInt32 attr;
	SceSize alignment;
	SceUInt32 uidBaseBlock;
	const char *strBaseBlockName;
	int flags;                     //! Unknown flags 0x10 or 0x30 for ::sceKernelOpenMemBlock
	int reserved[10];
} SceKernelAllocMemBlockOpt;
VITASDK_BUILD_ASSERT_EQ(0x40, SceKernelAllocMemBlockOpt);

typedef struct SceKernelFreeMemorySizeInfo {
	int size;         //!< sizeof(SceKernelFreeMemorySizeInfo)
	int size_user;    //!< Free memory size for *_USER_RW memory
	int size_cdram;   //!< Free memory size for USER_CDRAM_RW memory
	int size_phycont; //!< Free memory size for USER_MAIN_PHYCONT_*_RW memory
} SceKernelFreeMemorySizeInfo;
VITASDK_BUILD_ASSERT_EQ(0x10, SceKernelFreeMemorySizeInfo);

typedef enum SceKernelMemoryAccessType {
	SCE_KERNEL_MEMORY_ACCESS_X = 0x01, //!< Execute privileges
	SCE_KERNEL_MEMORY_ACCESS_W = 0x02, //!< Write privileges
	SCE_KERNEL_MEMORY_ACCESS_R = 0x04  //!< Read privileges
} SceKernelMemoryAccessType;

/**
 * Allocates a new memory block
 *
 * @param[in] name - Name for the memory block
 * @param[in] type - Type of the memory to allocate. Use `SCE_KERNEL_MEMBLOCK_TYPE_USER_*`.
 * @param[in] size - Size of the memory to allocate in bytes
 * @param[in] opt  - Memory block options?
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID sceKernelAllocMemBlock(const char *name, SceKernelMemBlockType type, SceSize size, SceKernelAllocMemBlockOpt *opt);

/**
 * Frees new memory block
 *
 * @param[in] uid - SceUID of the memory block to free
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelFreeMemBlock(SceUID uid);

/**
 * Gets the base address of a memory block
 *
 * @param[in]  uid  - SceUID of the memory block to free
 * @param[out] base - Base address of the memory block identified by SceUID
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetMemBlockBase(SceUID uid, void **base);

/**
 * Gets the associated memory block to a given memory location.
 *
 * @param[in] base - Address of the memory location to search
 * @param[in] size - Size of the memory location in bytes
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID sceKernelFindMemBlockByAddr(const void *addr, SceSize size);

/**
 * Gets memory block information given a base address.
 *
 * @param[in]  base - Base address of the memory location
 * @param[out] info - Information about the related memory block
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetMemBlockInfoByAddr(void *base, SceKernelMemBlockInfo *info);

/**
 * Gets memory block information given a memory location.
 *
 * @param[in]  base - Address of the memory location
 * @param[in]  size - Size of the memory location in bytes
 * @param[out] info - Information about the related memory block
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetMemBlockInfoByRange(void *base, SceSize size, SceKernelMemBlockInfo *info);

/**
 * Allocates a new memory block for Virtual Machine domain.
 *
 * @param[in] name - Name for the memory block
 * @param[in] size - Size of the memory to allocate in bytes
 *
 * @return SceUID of the memory block on success, < 0 on error.
 * @note - size can't be higher than 16 * 1024 * 1024.
*/
SceUID sceKernelAllocMemBlockForVM(const char *name, SceSize size);

/**
 * Flushes Virtual Machine caches for the given memory location.
 *
 * @param[in]  uid  - SceUID of the memory block to flush.
 * @param[in]  base - Address of the memory location to flush
 * @param[in]  size - Size of the memory to flush in bytes
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
int sceKernelSyncVMDomain(SceUID uid, void *data, SceSize size);

/**
 * Makes all Virtual Machine domain memblocks executeable.
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelOpenVMDomain(void);

/**
 * Makes all Virtual Machine domain memblocks non executeable.
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelCloseVMDomain(void);

int sceKernelOpenMemBlock(const char *name, int flags);
int sceKernelCloseMemBlock(SceUID uid);

/**
 * Get the model number of the device
 *
 * @return A value from SCE_KERNEL_MODEL
*/
int sceKernelGetModelForCDialog(void);

/**
 * Get the model number of the device
 *
 * @return A value from SCE_KERNEL_MODEL
*/
int sceKernelGetModel(void);

/**
 * Get free memory size in bytes
 *
 * @param[out] info - Returned free memory size for different kind of memory block types
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetFreeMemorySize(SceKernelFreeMemorySizeInfo *info);

/**
 * Returns wether the running device is a PSTV or not.
 *
 * @return 1 if the device is a PSTV, 0 otherwise.
*/
int sceKernelIsPSVitaTV(void);

typedef struct SceKernelSubbudgetInfo {
	int size; //!< Size of this structure. Must be set to 0xC.
	SceUInt32 totalSize; //!< Total size of the subbudget in bytes.
	SceUInt32 freeSize; //!< Free size of the subbudget in bytes.
} SceKernelSubbudgetInfo;
VITASDK_BUILD_ASSERT_EQ(0xC, SceKernelSubbudgetInfo); // size is from FW 3.60

#define SCE_KERNEL_SUBBUDGET_ID_MAIN (0)
#define SCE_KERNEL_SUBBUDGET_ID_CDLG (1)

int sceKernelAllocUnmapMemBlock(char *name, SceSize size);

/**
 * Tests a hardware-model capability exposed to user mode.
 *
 * FW 3.60 accepts capability indices 7 and 10.
 *
 * @param[in] capabilityIndex Capability bit index.
 *
 * @return 1 if the capability is present, 0 if it is absent,
 * ::SCE_KERNEL_ERROR_INVALID_ARGUMENT if the index is unsupported.
 */
int sceKernelCheckModelCapability(int capabilityIndex);
int sceKernelFreeMemBlockForVM(SceUID uid);

/**
 * Gets the total and free size of a memory subbudget.
 *
 * @param[in] subbudget ::SCE_KERNEL_SUBBUDGET_ID_MAIN or
 * ::SCE_KERNEL_SUBBUDGET_ID_CDLG.
 * @param[in,out] pInfo Pointer to a ::SceKernelSubbudgetInfo structure.
 *
 * @return 0 on success, < 0 on error.
 *
 * @note FW 3.60 requires DIP switch 159 to be enabled.
 */
int sceKernelGetSubbudgetInfo(SceInt subbudget, SceKernelSubbudgetInfo *pInfo);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SYSMEM_H_ */

