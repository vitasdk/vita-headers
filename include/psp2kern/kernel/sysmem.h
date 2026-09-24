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
	void *vbase;                    //!< Optional virtual base address.
	void *paddr;                    //!< Optional physical base address.
	SceSize alignment;
	SceSize extraLow;
	SceSize extraHigh;
	SceUID baseMemBlock;            //!< Memblock this allocation is based on.
	SceUID pid;
	const SceKernelPAVector *paddr_list; //!< Input physical-address vector.
	SceSize roundupUnitSize;
	SceUInt8 domain;
	SceUInt8 reservedDomain[3];     //!< Unused padding on FW 3.60.
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
SceUID ksceKernelAllocMemBlock(const char *name, SceKernelMemBlockType type, SceSize size, const SceKernelAllocMemBlockKernelOpt *opt);

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
int ksceKernelLockRange(const void *addr, SceSize size);

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
int ksceKernelLockRangeProc(ScePID pid, const void *addr, SceSize size);

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
int ksceKernelLockRangeWithMode(SceKernelMemoryRefPerm perm, const void *addr, SceSize size);

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
int ksceKernelUnlockRange(const void *addr, SceSize size);

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
int ksceKernelUnlockRangeProc(ScePID pid, const void *addr, SceSize size);

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
int ksceKernelUnlockRangeWithMode(SceKernelMemoryRefPerm perm, const void *addr, SceSize size);


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

typedef enum SceKernelHeapMemoryMappingAction {
	SCE_KERNEL_HEAP_MEMORY_MAPPING_ACTION_NONE  = 0,
	SCE_KERNEL_HEAP_MEMORY_MAPPING_ACTION_MAP   = 1,
	SCE_KERNEL_HEAP_MEMORY_MAPPING_ACTION_UNMAP = 2
} SceKernelHeapMemoryMappingAction;

/**
 * Options and mapping results for heap allocation.
 *
 * Set \a alignment to request an allocation alignment. The allocator writes
 * \a mapping_action, \a mapped_base, and \a mapped_size to describe any backing
 * memory range it mapped or unmapped during the allocation.
 */
typedef struct SceKernelHeapMemoryOpt {
	SceSize size; //!< Must be set to `sizeof(SceKernelHeapMemoryOpt)`.
	SceUInt32 mapping_action; //!< One of ::SceKernelHeapMemoryMappingAction.
	SceSize alignment; //!< Requested allocation alignment, or zero for the heap default.
	void *mapped_base; //!< Base of the mapped or unmapped backing range.
	SceSize mapped_size; //!< Size of the mapped or unmapped backing range.
} SceKernelHeapMemoryOpt;
VITASDK_BUILD_ASSERT_EQ(0x14, SceKernelHeapMemoryOpt); // size is from FW 0.990-3.60

typedef struct SceKernelAllocMemBlockInfo {
	SceSize size; //!< Must be set to `sizeof(SceKernelAllocMemBlockInfo)`.
	void *mapped_base; //!< Mapped base address.
	SceSize mapped_size; //!< Mapped size.
	SceKernelMemoryType memory_type; //!< Memory type derived from the selected memblock type.
	SceUInt32 access; //!< Bitwise OR of ::SceKernelMemoryAccessType values.
} SceKernelAllocMemBlockInfo;
VITASDK_BUILD_ASSERT_EQ(0x14, SceKernelAllocMemBlockInfo); // size is from FW 3.60

/** Opaque class-specific data for a physical-memory-partition UID object. */
typedef struct SceUIDPhyMemPartObject SceUIDPhyMemPartObject;

typedef struct SceKernelMemBlockInfoCore {
	SceKernelMemBlockType type; //!< Memblock type.
	SceUID guid; //!< Global memblock UID, or zero when it is hidden at the requested visibility level.
	const char *name; //!< Read-only memblock name.
	void *mapped_base; //!< Virtual mapping base.
	SceSize mapped_size; //!< Requested mapping size.
	SceSize alloc_map_size; //!< Size of the mapping actually allocated.
	SceSize extra_low; //!< Low-end mapping padding.
	SceSize extra_high; //!< High-end mapping padding.
	SceUInt32 paging_type; //!< Internal paging type; observed values include 4 and 8.
	SceUID partition_guid; //!< Physical-memory partition UID, or -1 when unavailable.
	SceUIDPhyMemPartObject *phy_mem_part; //!< Physical-memory partition object.
} SceKernelMemBlockInfoCore;
VITASDK_BUILD_ASSERT_EQ(0x2C, SceKernelMemBlockInfoCore); // size is from FW 3.60

typedef struct SceKernelMemBlockInfoEx {
	SceSize size; //!< Must be set to `sizeof(SceKernelMemBlockInfoEx)`.
	SceKernelMemBlockInfoCore core_info;
	SceSize physical_range_count; //!< Total number of physical ranges.
	SceSize physical_range_count_written; //!< Number of entries written to the arrays below, at most 16.
	void *physical_addresses[16]; //!< Physical base of each reported range.
	SceSize physical_sizes[16]; //!< Size of each reported range.
} SceKernelMemBlockInfoEx;
VITASDK_BUILD_ASSERT_EQ(0xB8, SceKernelMemBlockInfoEx); // size is from FW 3.60

/** Opaque class-specific data returned by the GUID and PUID object APIs. */
typedef struct SceKernelObject SceKernelObject;

/**
 * Creates a global UID object, optionally relative to \p reference_guid.
 *
 * \p object receives the newly created class-specific object data. The
 * memory is owned by the UID object and must not be freed by the caller.
 */
SceUID ksceGUIDCreate(SceClass *object_class, const char *name, SceUID reference_guid, SceKernelObject **object);

/** Gets the class of a global UID object. */
int ksceGUIDGetClass(SceUID guid, SceClass **object_class);

/**
 * Gets the read-only name owned by a live global UID.
 *
 * Sysmem owns the name. Renaming or destroying the UID can invalidate the
 * pointer. On FW 3.60, a GUID with a valid format that no longer refers to a
 * live UID does not reliably produce a lookup error. The caller must ensure
 * that the UID remains alive.
 */
int ksceGUIDGetName(SceUID guid, const char **name);

/**
 * Gets the class-specific object data for a global UID without taking a
 * reference. The caller must ensure that the UID remains alive.
 */
int ksceGUIDGetObject(SceUID guid, SceKernelObject **object);

/** Creates a kernel-owned global UID object with the default attributes. */
SceUID ksceGUIDKernelCreate(SceClass *object_class, const char *name, SceKernelObject **object);

/**
 * Returns the read-only name of a live global UID.
 *
 * FW 3.60 does not reliably report lookup failure for a GUID that no longer
 * refers to a live UID. The caller must ensure that the UID remains alive.
 */
const char *ksceGUIDName(SceUID guid);

/** Opens a named global UID object. */
SceUID ksceGUIDOpenByName(const char *name);

/**
 * Takes a reference to a global UID at visibility level 0 through 7.
 *
 * \p object may be NULL. When it is non-NULL, it receives the class-specific
 * object data. Each successful call must be matched by one later call to
 * ::ksceGUIDReleaseObject with \p guid.
 */
int ksceGUIDReferObjectWithLevel(SceUID guid, SceUInt32 visibility_level, SceKernelObject **object);

/**
 * Takes a reference to a global UID object when its class derives from \p object_class.
 *
 * \p object may be NULL. When it is non-NULL, it receives the class-specific
 * object data. Each successful call must be matched by one later call to
 * ::ksceGUIDReleaseObject with \p guid.
 */
int ksceGUIDReferObjectWithSubclass(SceUID guid, SceClass *object_class, SceKernelObject **object);

/** Replaces the name of a global UID object. */
int ksceGUIDSetName(SceUID guid, const char *name);

/** Allocates from the heap identified by \p heap_id. */
void *ksceKernelAllocHeapMemoryWithOpt(SceUID heap_id, SceSize size, SceKernelHeapMemoryOpt *opt);

/**
 * Allocates a memory block and returns its mapping information.
 *
 * On FW 3.60, a non-NULL \p info must point to a ::SceKernelAllocMemBlockInfo
 * structure with its \c size field set to 0x14. The function writes exactly
 * those 0x14 bytes. A non-NULL \p info with any other size is ignored.
 *
 * @param[in] name Memory-block name.
 * @param[in] type Memory-block type.
 * @param[in] vsize Allocation size.
 * @param[in] opt Optional allocation options. FW 3.60 accepts option sizes
 * 0x30 and 0x58.
 * @param[out] info Optional mapping information.
 *
 * @return The memory-block UID on success, < 0 on error.
 */
SceUID ksceKernelAllocMemBlockWithInfo(const char *name, SceKernelMemBlockType type, SceSize vsize, const SceKernelAllocMemBlockOptKernel *opt, SceKernelAllocMemBlockInfo *info);
void *ksceKernelAllocUncacheHeapMemory(SceSize size);
void *ksceKernelAllocUncacheHeapMemoryWithOption(SceSize size, SceKernelHeapMemoryOpt *opt);

/**
 * Counts the bytes at the start of a user-memory range in the calling process
 * that match a repeated 64-bit value.
 *
 * @param[in] ptr Input buffer. The function does not modify it.
 * @param[in] value Value to match.
 * @param[in] byte_size - Buffer size in bytes. It must be a multiple of 8.
 *
 * @return The number of matching bytes at the start of the range, or < 0 on error.
 */
int ksceKernelCountFillValue64FromUser(const SceUInt64 *ptr, SceUInt64 value, SceSize byte_size);

/**
 * Counts the bytes at the start of another process's user-memory range that
 * match a repeated 64-bit value.
 *
 * @param[in] pid Target process identifier.
 * @param[in] ptr Input buffer. The function does not modify it.
 * @param[in] value Value to match.
 * @param[in] byte_size - Buffer size in bytes. It must be a multiple of 8.
 *
 * @return The number of matching bytes at the start of the range, or < 0 on error.
 */
int ksceKernelCountFillValue64FromUserProc(ScePID pid, const SceUInt64 *ptr, SceUInt64 value, SceSize byte_size);

/**
 * Counts the bytes at the start of a user-memory range in the calling process
 * that match a repeated 32-bit value.
 *
 * @param[in] ptr Input buffer. The function does not modify it.
 * @param[in] value Value to match.
 * @param[in] byte_size - Buffer size in bytes. It must be a multiple of 4.
 *
 * @return The number of matching bytes at the start of the range, or < 0 on error.
 */
int ksceKernelCountFillValueFromUser(const SceUInt32 *ptr, SceUInt32 value, SceSize byte_size);

/**
 * Counts the bytes at the start of another process's user-memory range that
 * match a repeated 32-bit value.
 *
 * @param[in] pid Target process identifier.
 * @param[in] ptr Input buffer. The function does not modify it.
 * @param[in] value Value to match.
 * @param[in] byte_size - Buffer size in bytes. It must be a multiple of 4.
 *
 * @return The number of matching bytes at the start of the range, or < 0 on error.
 */
int ksceKernelCountFillValueFromUserProc(ScePID pid, const SceUInt32 *ptr, SceUInt32 value, SceSize byte_size);

/** Decrements a memblock's internal range/reference counter. */
int ksceKernelDecRefCountMemBlock(SceUID uid);

int ksceKernelFreeUncacheHeapMemory(void *ptr);
/**
 * Gets extended memblock information at visibility level 0 through 7.
 *
 * Set the \c size field of \p info to 0xB8 before calling. The function writes
 * the information to the same structure.
 */
int ksceKernelGetMemBlockInfo(SceUID uid, SceUInt32 visibility_level, SceKernelMemBlockInfoEx *info);

/** Gets the currently mapped base of a memblock. */
int ksceKernelGetMemBlockMappedBase(SceUID uid, void **base);

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
int ksceKernelGetMemBlockMemtypeByAddr(const void *addr);

/** Gets the single physical range backing a memblock. */
int ksceKernelGetMemBlockPARange(SceUID uid, SceKernelPARange *pa_range);

/** Gets the physical-range vector backing a memblock. */
int ksceKernelGetMemBlockPAVector(SceUID uid, SceKernelPAVector *pa_vector);

/** Gets the virtual base reserved for a memblock. */
int ksceKernelGetMemBlockVBase(SceUID uid, void **base);

/**
 * Classifies the physical region containing a virtual address.
 *
 * FW 3.60 returns 5 for physical addresses from 0x20000000 through
 * 0x2FFFFFFF, 1 from 0x40000000 through 0x7FFFFFFF, 3 from 0x80000000
 * through 0xBFFFFFFF, and 7 for all other physical ranges.
 *
 * @return The physical-region value described above, or < 0 when address
 * translation fails.
 */
int ksceKernelGetPhysicalMemoryType(const void *vaddr);

/** Increments a memblock's internal range/reference counter. */
int ksceKernelIncRefCountMemBlock(SceUID uid);
/** \p permission is a bitwise OR of ::SceKernelMemoryRefPerm values. */
int ksceKernelIsAccessibleRange(SceUInt32 permission, const void *va, SceSize len);
/** \p permission is a bitwise OR of ::SceKernelMemoryRefPerm values. */
int ksceKernelIsAccessibleRangeProc(ScePID pid, SceUInt32 permission, const void *va, SceSize len);

/**
 * Checks whether a range has exactly the requested software permissions.
 *
 * On FW 3.60, \p pid is ignored and \p va is only read.
 *
 * @param[in] pid Process identifier. Ignored on FW 3.60.
 * @param[in] permission - Bitwise OR of ::SceKernelMemoryRefPerm values.
 * @param[in] va Start of the range.
 * @param[in] len Range size in bytes. It must be nonzero.
 *
 * @return 0 if every page has exactly the requested permissions, < 0 on
 * error.
 */
int ksceKernelIsEqualAccessibleRangeProcBySW(ScePID pid, SceUInt32 permission, const void *va, SceSize len);

/**
 * Gets extended memblock information at visibility level 7.
 *
 * @param[in] uid - Memblock UID.
 * @param[in,out] info - Receives the information. Set its \c size field to 0xB8 before calling.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemBlockGetInfoEx(SceUID uid, SceKernelMemBlockInfoEx *info);

/**
 * Gets the internal memory-type class associated with a memblock type.
 *
 * @return The internal type masked with 0xFF00, or < 0 for an invalid type.
 */
int ksceKernelMemBlockType2Memtype(SceKernelMemBlockType type);

/**
 * Gets the memory permissions associated with a memblock type.
 *
 * @return A bitwise OR of ::SceKernelMemoryRefPerm values.
 */
int ksceKernelMemBlockTypeGetPrivileges(SceKernelMemBlockType type);

/**
 * Translates an address in another process after applying an MMU access mode.
 *
 * @param[in] pid - Target process.
 * @param[in] permission - Bitwise OR of ::SceKernelMemoryRefPerm values.
 * @param[in] va - Virtual address.
 * @param[out] pa - Physical address.
 */
int ksceKernelProcModeVAtoPA(ScePID pid, SceUInt32 permission, const void *va, void **pa);
int ksceKernelVARangeToPARangeByHW(const SceKernelVARange *v_range, SceKernelPARange *pa_range);
int ksceKernelVARangeToPARangeBySW(const SceKernelVARange *v_range, SceKernelPARange *pa_range);
int ksceKernelVARangeToPAVectorByHW(const SceKernelVARange *v_range, SceKernelPAVector *pa_vector);
int ksceKernelVARangeToPAVectorBySW(const SceKernelVARange *v_range, SceKernelPAVector *pa_vector);
int ksceKernelVAtoPABySW(const void *va, void **pa);

/** Gets the class of an object in a process-local UID namespace. */
int kscePUIDGetClass(ScePID pid, SceUID puid, SceClass **object_class);

/**
 * Gets the read-only name owned by a process-local UID entry.
 *
 * Sysmem owns the name. Renaming or destroying the entry can invalidate the
 * pointer.
 */
int kscePUIDGetName(ScePID pid, SceUID puid, const char **name);

/**
 * Gets the class-specific object data for a process-local UID without taking a
 * reference. The caller must ensure that the object remains alive.
 */
int kscePUIDGetObject(ScePID pid, SceUID puid, SceKernelObject **object);

/**
 * Opens a global UID in a process-local UID namespace.
 *
 * FW 3.60 accepts flag values from 0 through 3. Bit 0 marks the source GUID as
 * opened through a PUID entry; bit 1 sets an internal flag on the target PUID
 * entry heap.
 */
SceUID kscePUIDOpenByGUIDWithFlags(ScePID pid, SceUID guid, SceUInt32 flags);

/** Opens a named object in a process-local UID namespace. */
SceUID kscePUIDOpenByName(ScePID pid, const char *name);

/** Opens a named object of the required class in a process-local UID namespace. */
SceUID kscePUIDOpenByNameWithClass(ScePID pid, const char *name, SceClass *object_class);

/** Replaces the name of a process-local UID entry. */
int kscePUIDSetName(ScePID pid, SceUID puid, const char *name);

/** Resolves a process-local UID to its global UID, requiring \p object_class. */
SceUID kscePUIDtoGUIDWithClass(ScePID pid, SceUID puid, SceClass *object_class);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SYSMEM_H_ */
