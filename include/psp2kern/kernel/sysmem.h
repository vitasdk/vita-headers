/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_SYSMEM_H_
#define _PSP2KERN_KERNEL_SYSMEM_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2kern/kernel/sysmem/address_space.h>
#include <psp2kern/kernel/sysmem/uid_class.h>
#include <psp2kern/kernel/sysmem/uid_guid.h>
#include <psp2kern/kernel/sysmem/uid_puid.h>
#include <psp2kern/kernel/sysmem/uid_entryheap.h>
#include <psp2kern/kernel/sysmem/fixedheap.h>
#include <psp2kern/kernel/sysmem/nameheap.h>
#include <psp2kern/kernel/sysmem/heap.h>
#include <psp2kern/kernel/sysmem/data_transfers.h>
#include <psp2kern/kernel/sysmem/memtype.h>
#include <psp2common/kernel/sysmem.h>

#ifdef __cplusplus
extern "C" {
#endif

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
	SceSize size;                   //!< Size of this structure.
	SceUInt32 reserved;             //!< Ignored on FW 3.60.
	SceUInt32 attr;                 //!< Bitwise OR of ::SceKernelAllocMemBlockAttr values.
	SceUInt32 vbase;                //!< A virtual base address represented as \c void*.
	SceUInt32 paddr;                //!< better name: pbase; a physical base address represented as \c void*.
	SceSize alignment;
	SceUInt32 extraLow;             //!< A ::SceSize value.
	SceUInt32 extraHigh;            //!< A ::SceSize value.
	SceUInt32 baseMemBlock;         //!< Value of type ::SceUID for the memblock this allocation is based on.
	SceUID pid;
	SceKernelPaddrList *paddr_list; //!< better name: pPAV; a pointer to a ::SceKernelPAVector structure.
	SceUInt32 roundupUnitSize;      //!< Value of type ::SceSize.
	SceUInt32 domain;               //!< Its low byte is a value of type ::SceUInt8.
	SceUInt32 allowedOpenFlags;     //!< Flags permitted when another process opens the block.
	SceUInt32 requiredCapabilityMask[8]; //!< Required 256-bit process capability mask.
} SceKernelAllocMemBlockKernelOpt;
VITASDK_BUILD_ASSERT_EQ(0x58, SceKernelAllocMemBlockKernelOpt); // size is from FW 3.60

typedef SceKernelAllocMemBlockKernelOpt SceKernelAllocMemBlockOptKernel;

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
 * Find the SceUID of a memory block in a process
 *
 * @param[in] pid - PID of the process
 * @param[in] addr - Base address of the memory block
 * @param[in] size - Size to search for (usally set to 0)
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID ksceKernelFindProcMemBlockByAddr(SceUID pid, const void *addr, SceSize size);

/**
 * Get the AllocMapSize of a MemBlock
 *
 * @param[in]           memid - The target uid of the memblock
 * @param[out] alloc_map_size - The output for AllocMapSize
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceKernelGetMemBlockAllocMapSize(SceUID memid, SceSize *alloc_map_size);

/**
 * Map a memblock
 *
 * @param[in] uid - GUID of the memblock to map.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceKernelMapMemBlock(SceUID uid);

/**
 * Map a memblock.
 *
 * @param[in] uid  - GUID of the memblock to map.
 * @param[in] flag - Set to 1 to prevent DCache invalidation before mapping.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceKernelMapMemBlockWithFlag(SceUID uid, int flag);

/**
 * Changes the block type
 *
 * @param[in] uid - SceUID of the memory block to change
 * @param[in] type - Type of the memory to change to
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelRemapMemBlock(SceUID uid, SceKernelMemBlockType type);

/**
 * Unmap a memblock.
 *
 * @param[in] uid  - GUID of the memblock to unmap.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int ksceKernelUnmapMemBlock(SceUID uid);

/**
 * The mapping user address space to kernel
 *
 * @param[in]  name          - The mapping name.
 * @param[in]  permission    - The access permission. 1 for Read, 2 or 3 for read/write.
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

/**
 * The mapping user address space to kernel with process
 *
 * @param[in]  pid           - The target process id.
 * @param[in]  name          - The mapping name.
 * @param[in]  permission    - The access permission. 1 for Read, 2 or 3 for read/write.
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

/**
 * The mapping user address space to kernel with flags
 *
 * @param[in]  name          - The mapping name.
 * @param[in]  permission    - The access permission. 1 for Read, 2 or 3 for read/write.
 * @param[in]  flags         - 0x11 to map into TmpFsGame instead of Tmp
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
SceUID ksceKernelUserMapWithFlags(const char *name, int permission, int flags, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, unsigned int *kernel_offset);

/**
 * Frees a memblock mapped with ksceKernelUserMap
 *
 * This decreases the internal reference count.
 *
 * @param[in]  uid   The uid of the memblock
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelUserUnmap(SceUID uid);

/**
 * Locks a memory range
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
int ksceKernelLockRange(void *addr, SceSize size);

/**
 * Locks a memory range for a process (pid)
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
int ksceKernelLockRangeProc(SceUID pid, void *addr, SceSize size);

/**
 * Locks a memory range, checking for a given permission
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
int ksceKernelLockRangeWithMode(SceKernelMemoryRefPerm perm, void *addr, SceSize size);

/**
 * Unlocks a memory range
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
int ksceKernelUnlockRange(void *addr, SceSize size);

/**
 * Unlocks a memory range for a process (pid)
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
int ksceKernelUnlockRangeProc(SceUID pid, void *addr, SceSize size);

/**
 * Unlocks a memory range checking for a given permission
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
int ksceKernelUnlockRangeWithMode(SceKernelMemoryRefPerm perm, void *addr, SceSize size);


SceUID ksceKernelAllocPartitionMemBlock(SceUID part, const char *name, SceKernelMemBlockType type, SceSize size, const SceKernelAllocMemBlockOptKernel *pOpt);
int ksceKernelFreeSimpleMemBlock(void *a1);


/* Macros for backwards compatibility */
#define ksceKernelFindMemBlockByAddrForPid(pid, addr, size) ksceKernelFindProcMemBlockByAddr(pid, addr, size)

#define ksceKernelMapBlockUserVisible(uid) ksceKernelMapMemBlock(uid)
#define ksceKernelRemapBlock(uid, type) ksceKernelRemapMemBlock(uid, type)

#define ksceKernelMapUserBlock(name, permission, flags, user_buf, size, kernel_page, kernel_size, kernel_offset) ksceKernelUserMapWithFlags(name, permission, flags, user_buf, size, kernel_page, kernel_size, kernel_offset)
#define ksceKernelMapUserBlockDefaultType(name, permission, user_buf, size, kernel_page, kernel_size, kernel_offset) ksceKernelUserMap(name, permission, user_buf, size, kernel_page, kernel_size, kernel_offset)
#define ksceKernelMapUserBlockDefaultTypeForPid(pid, name, permission, user_buf, size, kernel_page, kernel_size, kernel_offset) ksceKernelProcUserMap(pid, name, permission, user_buf, size, kernel_page, kernel_size, kernel_offset)
#define ksceKernelMemBlockRelease(uid) ksceKernelUserUnmap(uid)

#define ksceKernelMemRangeRetain(addr, size) ksceKernelLockRange(addr, size)
#define ksceKernelMemRangeRetainForPid(pid, addr, size) ksceKernelLockRangeProc(pid, addr, size)
#define ksceKernelMemRangeRetainWithPerm(perm, addr, size) ksceKernelLockRangeWithMode(perm, addr, size)

#define ksceKernelMemRangeRelease(addr, size) ksceKernelUnlockRange(addr, size)
#define ksceKernelMemRangeReleaseForPid(pid, addr, size) ksceKernelUnlockRangeProc(pid, addr, size)
#define ksceKernelMemRangeReleaseWithPerm(perm, addr, size) ksceKernelUnlockRangeWithMode(perm, addr, size)

typedef struct SceKernelHeapMemoryOpt {
	SceSize size;
	uint32_t mappingAction; //!< 0 if no mapping occurred, 1 for mapping, or 2 for unmapping.
	SceSize alignment;
	uint32_t mappedBase; //!< Base address of the mapped or unmapped block.
	uint32_t mappedSize; //!< Size of the mapped or unmapped block.
} SceKernelHeapMemoryOpt;
VITASDK_BUILD_ASSERT_EQ(0x14, SceKernelHeapMemoryOpt); // size is from FW 0.990-3.60

typedef struct SceKernelAllocMemBlockInfo {
	SceSize size; //!< Size of this structure.
	void *mappedBase; //!< Mapped base address.
	SceSize mappedSize; //!< Mapped size.
	SceKernelMemoryType memoryType; //!< Memory type.
	SceUInt32 access; //!< Access rights.
} SceKernelAllocMemBlockInfo;
VITASDK_BUILD_ASSERT_EQ(0x14, SceKernelAllocMemBlockInfo); // size is from FW 3.60

typedef struct SceUIDPhyMemPartObject SceUIDPhyMemPartObject;

typedef struct SceKernelMemBlockInfoCore {
	SceKernelMemBlockType type;
	SceUID guid;
	const char *name;
	void *mappedBase;
	SceSize mappedSize;
	SceSize allocMapSize;
	int extraLow;
	int extraHigh;
	int pagingType; //!< 4 for a virtual page list, or 8 for a partial mapping.
	SceUID partitionGuid;
	SceUIDPhyMemPartObject *pPhyMemPart;
} SceKernelMemBlockInfoCore;
VITASDK_BUILD_ASSERT_EQ(0x2C, SceKernelMemBlockInfoCore); // size is from FW 3.60

typedef struct SceKernelMemBlockInfoEx {
	SceSize size; //!< Size of this structure
	SceKernelMemBlockInfoCore coreInfo;
	SceSize nPhyAddrs;
	SceSize nPhySizes;
	void *phyAddrs[0x10];
	SceSize phySizes[0x10];
} SceKernelMemBlockInfoEx;
VITASDK_BUILD_ASSERT_EQ(0xB8, SceKernelMemBlockInfoEx); // size is from FW 3.60

typedef struct SceKernelObject {
	void *pObject;
	SceClass *pClass;
	uintptr_t classData[]; //!< Class-specific object data.
} SceKernelObject;

SceUID ksceGUIDCreate(SceClass *pClass, const char *name, SceUID guid, SceKernelObject **ppEntry);
int ksceGUIDGetClass(SceUID guid, SceClass **ppClass);
int ksceGUIDGetName(SceUID guid, char **pName);
int ksceGUIDGetObject(SceUID uid, SceKernelObject **ppEntry);
SceUID ksceGUIDKernelCreate(SceClass *pClass, const char *name, SceKernelObject **ppEntry);
char *ksceGUIDName(SceUID guid);
SceUID ksceGUIDOpenByName(const char *name);
int ksceGUIDReferObjectWithLevel(SceUID uid, SceUInt32 level, SceKernelObject **pEntry);
int ksceGUIDReferObjectWithSubclass(SceUID guid, SceClass *pClass, SceKernelObject **ppEntry);
SceInt32 ksceGUIDSetName(SceUID guid, const char *name);
void *ksceKernelAllocHeapMemoryWithOpt(SceUID uid, SceSize size, SceKernelHeapMemoryOpt *pOpt);

/**
 * Allocates a memory block and returns its mapping information.
 *
 * On FW 3.60, \p pInfo points to a ::SceKernelAllocMemBlockInfo layout, its
 * \c size field must be set to 0x14, and exactly those 0x14 bytes are written.
 * A non-NULL \p pInfo with any other size is ignored.
 *
 * @param[in] name Memory-block name.
 * @param[in] type Memory-block type.
 * @param[in] vsize Allocation size.
 * @param[in] pOpt Optional allocation options. FW 3.60 accepts option sizes
 * 0x30 and 0x58.
 * @param[out] pInfo Optional mapping information.
 *
 * @return The memory-block UID on success, < 0 on error.
 */
SceUID ksceKernelAllocMemBlockWithInfo(const char *name, SceKernelMemBlockType type, SceSize vsize, const SceKernelAllocMemBlockOptKernel *pOpt, SceKernelMemBlockInfo *pInfo);
void *ksceKernelAllocUncacheHeapMemory(SceSize size);
void *ksceKernelAllocUncacheHeapMemoryWithOption(SceSize size, SceKernelHeapMemoryOpt *pOpt);

/**
 * Counts the leading bytes filled with a repeated 64-bit value in a
 * current-process user range.
 *
 * @param[in] ptr Input buffer. The function does not modify it.
 * @param[in] unused ABI padding before the 64-bit \p value.
 * @param[in] value Value to match.
 * @param[in] byte_size Buffer size in bytes. It must be a multiple of 8.
 *
 * @return The matching prefix length in bytes, or < 0 on error.
 */
int ksceKernelCountFillValue64FromUser(unsigned long long *ptr, int unused, unsigned long long value, int byte_size);

/**
 * Counts the leading bytes filled with a repeated 64-bit value in another
 * process's user range.
 *
 * @param[in] pid Target process identifier.
 * @param[in] ptr Input buffer. The function does not modify it.
 * @param[in] value Value to match.
 * @param[in] byte_size Buffer size in bytes. It must be a multiple of 8.
 *
 * @return The matching prefix length in bytes, or < 0 on error.
 */
int ksceKernelCountFillValue64FromUserProc(SceUID pid, unsigned long long *ptr, unsigned long long value, int byte_size);

/**
 * Counts the leading bytes filled with a repeated 32-bit value in a
 * current-process user range.
 *
 * @param[in] ptr Input buffer. The function does not modify it.
 * @param[in] value Value to match.
 * @param[in] byte_size Buffer size in bytes. It must be a multiple of 4.
 *
 * @return The matching prefix length in bytes, or < 0 on error.
 */
int ksceKernelCountFillValueFromUser(unsigned int *ptr, int value, int byte_size);

/**
 * Counts the leading bytes filled with a repeated 32-bit value in another
 * process's user range.
 *
 * @param[in] pid Target process identifier.
 * @param[in] ptr Input buffer. The function does not modify it.
 * @param[in] value Value to match.
 * @param[in] byte_size Buffer size in bytes. It must be a multiple of 4.
 *
 * @return The matching prefix length in bytes, or < 0 on error.
 */
int ksceKernelCountFillValueFromUserProc(SceUID pid, unsigned int *ptr, int value, int byte_size);
int ksceKernelDecRefCountMemBlock(SceUID uid);
int ksceKernelFreeUncacheHeapMemory(void *ptr);
int ksceKernelGetMemBlockInfo(SceUID uid, uint32_t level, SceKernelMemBlockInfoEx *pInfo);
int ksceKernelGetMemBlockMappedBase(SceUID uid, void **basep);

/**
 * Gets the internal memory type for an address.
 *
 * FW 3.60 can return internal 0x??00 values such as 0x8000 that are not named
 * by ::SceKernelMemoryType.
 *
 * @param[in] addr Address in the current address space.
 *
 * @return The internal memory type masked with 0xFF00, or < 0 on error.
 */
SceKernelMemoryType ksceKernelGetMemBlockMemtypeByAddr(const void *addr);
int ksceKernelGetMemBlockPARange(SceUID uid, SceKernelPARange *pRange);
int ksceKernelGetMemBlockPAVector(SceUID uid, SceKernelPAVector *pPAV);
int ksceKernelGetMemBlockVBase(SceUID uid, void **kernel_page);
int ksceKernelGetPhysicalMemoryType(void *vaddr);
int ksceKernelIncRefCountMemBlock(SceUID uid);
int ksceKernelIsAccessibleRange(SceUInt32 permission_type, const void *pVA, SceSize len);
int ksceKernelIsAccessibleRangeProc(SceUID pid, SceUInt32 permission_type, const void *pVA, SceSize len);

/**
 * Checks whether a range has exactly the requested software permissions.
 *
 * On FW 3.60, \p pid is ignored and \p pVA is only read.
 *
 * @param[in] pid Preserved process-identifier argument. FW 3.60 ignores it.
 * @param[in] permission_type Bitwise OR of ::SceKernelMemoryRefPerm values.
 * @param[in] pVA Start of the range.
 * @param[in] len Range size in bytes. It must be nonzero.
 *
 * @return 0 if every page has exactly the requested permissions, < 0 on
 * error.
 */
int ksceKernelIsEqualAccessibleRangeProcBySW(SceUID pid, int permission_type, void *pVA, SceSize len);
int ksceKernelMemBlockGetInfoEx(SceUID uid, SceKernelMemBlockInfoEx *pInfo);
int ksceKernelMemBlockType2Memtype(SceKernelMemBlockType type);
int ksceKernelMemBlockTypeGetPrivileges(SceKernelMemBlockType type);
int ksceKernelProcModeVAtoPA(SceUID pid, SceUInt32 mode, void *pVA, void **pPA);
int ksceKernelVARangeToPARangeByHW(SceKernelVARange *vRange, SceKernelPARange *pRange);
int ksceKernelVARangeToPARangeBySW(SceKernelVARange *vRange, SceKernelPARange *pRange);
int ksceKernelVARangeToPAVectorByHW(const SceKernelVARange *vRange, SceKernelPAVector *pPAV);
int ksceKernelVARangeToPAVectorBySW(const SceKernelVARange *vRange, SceKernelPAVector *pPAV);
int ksceKernelVAtoPABySW(void *pVA, void **pPA);
int kscePUIDGetClass(SceUID pid, SceUID puid, SceClass **ppClass);
int kscePUIDGetName(SceUID pid, SceUID puid, char **pName);
int kscePUIDGetObject(SceUID pid, SceUID uid, SceKernelObject **ppEntry);
SceUID kscePUIDOpenByGUIDWithFlags(SceUID pid, SceUID guid, SceUInt32 flags);
SceUID kscePUIDOpenByName(SceUID pid, const char *name);
SceUID kscePUIDOpenByNameWithClass(ScePID pid, const char *name, SceClass *pClass);
int kscePUIDSetName(SceUID pid, SceUID puid, const char *name);
SceUID kscePUIDtoGUIDWithClass(SceUID pid, SceUID puid, SceClass *pClass);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_H_ */
