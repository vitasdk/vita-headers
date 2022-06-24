/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_H_
#define _PSP2KERN_KERNEL_SYSMEM_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/sysmem/uid_class.h>
#include <psp2kern/kernel/sysmem/uid_guid.h>
#include <psp2kern/kernel/sysmem/uid_puid.h>
#include <psp2kern/kernel/sysmem/heap.h>
#include <psp2kern/kernel/sysmem/data_transfers.h>
#include <psp2kern/kernel/sysmem/mmu.h>
#include <psp2kern/kernel/sysmem/memtype.h>
#include <psp2kern/kernel/debug.h>
#include <psp2kern/kernel/sysroot.h>
#include <psp2common/kernel/sysmem.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceKernelAllocMemBlockAttr {
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PADDR          = 0x00000002U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_ALIGNMENT      = 0x00000004U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_MIRROR_BLOCKID = 0x00000040U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PID            = 0x00000080U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PADDR_LIST     = 0x00001000U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_PHYCONT            = 0x00200000U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_ALLOW_PARTIAL_OP   = 0x04000000U
} SceKernelAllocMemBlockAttr;

typedef enum SceKernelMemoryRefPerm {
	SCE_KERNEL_MEMORY_REF_PERM_ANY		= 0,
	SCE_KERNEL_MEMORY_REF_PERM_USER_R	= 0x01,
	SCE_KERNEL_MEMORY_REF_PERM_USER_W	= 0x02,
	SCE_KERNEL_MEMORY_REF_PERM_USER_X	= 0x04,
	SCE_KERNEL_MEMORY_REF_PERM_KERN_R	= 0x10,
	SCE_KERNEL_MEMORY_REF_PERM_KERN_W	= 0x20,
	SCE_KERNEL_MEMORY_REF_PERM_KERN_X	= 0x40,
} SceKernelMemoryRefPerm;

// specific to 3.60
typedef struct SceKernelAllocMemBlockKernelOpt {
	SceSize size;                   //!< sizeof(SceKernelAllocMemBlockKernelOpt)
	SceUInt32 field_4;
	SceUInt32 attr;                 //!< OR of SceKernelAllocMemBlockAttr
	SceUInt32 field_C;
	SceUInt32 paddr;
	SceSize alignment;
	SceUInt32 extraLow;
	SceUInt32 extraHigh;
	SceUInt32 mirror_blockid;
	SceUID pid;
	SceKernelPaddrList *paddr_list;
	SceUInt32 field_2C;
	SceUInt32 field_30;
	SceUInt32 field_34;
	SceUInt32 field_38;
	SceUInt32 field_3C;
	SceUInt32 field_40;
	SceUInt32 field_44;
	SceUInt32 field_48;
	SceUInt32 field_4C;
	SceUInt32 field_50;
	SceUInt32 field_54;
} SceKernelAllocMemBlockKernelOpt;

typedef enum SceKernelModel {
	SCE_KERNEL_MODEL_VITA   = 0x10000,
	SCE_KERNEL_MODEL_VITATV = 0x20000
} SceKernelModel;

/**
 * Allocates a new memory block
 *
 * @param[in] name - Name for the memory block
 * @param[in] type - Type of the memory to allocate. Use `SCE_KERNEL_MEMBLOCK_TYPE_USER_*` or `SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_*`.
 * @param[in] size - Size of the memory to allocate
 * @param[in] opt  - Memory block options?
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID ksceKernelAllocMemBlock(const char *name, SceKernelMemBlockType type, SceSize size, SceKernelAllocMemBlockKernelOpt *opt);

/**
 * Frees new memory block
 *
 * @param[in] uid - SceUID of the memory block to free
 *
 * @return 0 on success, < 0 on error.
*/
int ksceKernelFreeMemBlock(SceUID uid);

/**
 * Gets the base address of a memory block
 *
 * @param[in]  uid  - SceUID of the memory block
 * @param[out] base - Base address of the memory block identified by uid
 *
 * @return 0 on success, < 0 on error.
*/
int ksceKernelGetMemBlockBase(SceUID uid, void **base);

/**
 * Gets the memory block type of a memory block
 *
 * @param[in] uid - SceUID of the memory block
 * @param[out] type - Type of the memory block identified by uid
 *
 * @return 0 on success, < 0 on error.
*/
int ksceKernelGetMemBlockType(SceUID uid, unsigned int *type);

/**
 * Find the SceUID of a memory block
 *
 * @param[in] addr - Base address of the memory block
 * @param[in] size - Size to search for (usally set to 0)
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID ksceKernelFindMemBlockByAddr(const void *addr, SceSize size);

/**
 * Find the SceUID of a memory block for a PID
 *
 * @param[in] pid - PID of the process
 * @param[in] addr - Base address of the memory block
 * @param[in] size - Size to search for (usally set to 0)
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID ksceKernelFindMemBlockByAddrForPid(SceUID pid, const void *addr, SceSize size);

/**
 * Changes the block type
 *
 * @param[in] uid - SceUID of the memory block to change
 * @param[in] type - Type of the memory to change to
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelRemapBlock(SceUID uid, SceKernelMemBlockType type);

int ksceKernelMapBlockUserVisible(SceUID uid);

SceUID ksceKernelMapUserBlock(const char *name, int permission, int type,
			   const void *user_buf, SceSize size, void **kernel_page,
			   SceSize *kernel_size, unsigned int *kernel_offset);

/**
 * The mapping user address space to kernel
 *
 * @param[in]  name          - The mapping name.
 * @param[in]  permission    - The access permission. 1 for Read.
 * @param[in]  user_buf      - The target address of user space.
 * @param[in]  size          - The mapping size.
 * @param[out] kernel_page   - The mapped kernel address space.
 * @param[out] kernel_size   - The mapped size.
 * @param[out] kernel_offset - The output of address align value.
 *                             For example, if user_buf is 0x81000123, kernel_offset to 0x123.
 *
 * @return uid on success, < 0 on error.
 *
 * note - If no longer use the mapped address, need to release it with ksceKernelMemBlockRelease
 */
SceUID ksceKernelUserMap(const char *name, int permission, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);

#define ksceKernelMapUserBlockDefaultType(name, permission, user_buf, size, kernel_page, kernel_size, kernel_offset) ksceKernelUserMap(name, permission, user_buf, size, kernel_page, kernel_size, kernel_offset)

/**
 * The mapping user address space to kernel with process
 *
 * @param[in]  pid           - The target process id.
 * @param[in]  name          - The mapping name.
 * @param[in]  permission    - The access permission. 1 for Read.
 * @param[in]  user_buf      - The target address of user space.
 * @param[in]  size          - The mapping size.
 * @param[out] kernel_page   - The mapped kernel address space.
 * @param[out] kernel_size   - The mapped size.
 * @param[out] kernel_offset - The output of address align value.
 *                             For example, if user_buf is 0x81000123, kernel_offset to 0x123.
 *
 * @return uid on success, < 0 on error.
 *
 * note - If no longer use the mapped address, need to release it with ksceKernelMemBlockRelease
 */
SceUID ksceKernelProcUserMap(SceUID pid, const char *name, int permission, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);

#define ksceKernelMapUserBlockDefaultTypeForPid(pid, name, permission, user_buf, size, kernel_page, kernel_size, kernel_offset) ksceKernelProcUserMap(pid, name, permission, user_buf, size, kernel_page, kernel_size, kernel_offset)

/**
 * Releases a memblock referenced by the UID.
 *
 * This decreases the internal reference count.
 *
 * @param[in]  uid   The uid of the memblock
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemBlockRelease(SceUID uid);

/**
 * Retains a memory range
 *
 * This increases the internal reference count of the memblocks belonging to the range.
 *
 * Note: It uses ::SCE_KERNEL_MEMORY_REF_PERM_ANY as the reference permission.
 *
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemRangeRetain(void *addr, SceSize size);

/**
 * Retains a memory range for a process (pid)
 *
 * This increases the internal reference count of the memblocks belonging to the range.
 *
 * Note: It uses ::SCE_KERNEL_MEMORY_REF_PERM_ANY as the reference permission.
 *
 * @param[in]  pid    The pid of the process
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemRangeRetainForPid(SceUID pid, void *addr, SceSize size);

/**
 * Retains a memory range checking for a given permission
 *
 * This increases the internal reference count of the memblocks belonging to the range.
 * If the memory blocks belonging to the range don't have the required memory access permission,
 * it returns an error.
 *
 * @param[in]  perm   The required permission of the memory blocks belonging to the range
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemRangeRetainWithPerm(SceKernelMemoryRefPerm perm, void *addr, SceSize size);

/**
 * Releases a memory range
 *
 * This decreases the internal reference count of the memblocks belonging to the range.
 *
 * Note: It uses ::SCE_KERNEL_MEMORY_REF_PERM_ANY as the reference permission.
 *
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemRangeRelease(void *addr, SceSize size);

/**
 * Releases a memory range for a process (pid)
 *
 * This decreases the internal reference count of the memblocks belonging to the range.
 *
 * Note: It uses ::SCE_KERNEL_MEMORY_REF_PERM_ANY as the reference permission.
 *
 * @param[in]  pid    The pid of the process
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemRangeReleaseForPid(SceUID pid, void *addr, SceSize size);

/**
 * Releases a memory range checking for a given permission
 *
 * This decreases the internal reference count of the memblocks belonging to the range.
 * If the memory blocks belonging to the range don't have the required memory access permission,
 * it returns an error.
 *
 * @param[in]  perm   The required permission of the memory blocks belonging to the range
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemRangeReleaseWithPerm(SceKernelMemoryRefPerm perm, void *addr, SceSize size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_H_ */
