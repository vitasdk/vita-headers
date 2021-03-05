/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem.h,SceSysmemForDriver_stub}
 */

#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/debug.h>
#include <psp2kern/kernel/sysroot.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceKernelMemBlockType {
	SCE_KERNEL_MEMBLOCK_TYPE_SHARED_RX                = 0x0390D050,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW            = 0x09408060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE          = 0x0C208060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RX                  = 0x0C20D050,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RW                  = 0x0C20D060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_RW     = 0x0C80D060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_NC_RW  = 0x0D808060,
	SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RX                = 0x1020D005,
	SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW                = 0x1020D006,
	SCE_KERNEL_MEMBLOCK_TYPE_RW_UNK0                  = 0x6020D006
} SceKernelMemBlockType;

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

typedef struct SceKernelAddrPair {
	uint32_t addr;                  //!< Address
	uint32_t length;                //!< Length
} SceKernelAddrPair;

typedef struct SceKernelPaddrList {
	uint32_t size;                  //!< sizeof(SceKernelPaddrList)
	uint32_t list_size;             //!< Size in elements of the list array
	uint32_t ret_length;            //!< Total physical size of the memory pairs
	uint32_t ret_count;             //!< Number of elements of list filled by ksceKernelGetPaddrList
	SceKernelAddrPair *list;        //!< Array of physical addresses and their lengths pairs
} SceKernelPaddrList;

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

typedef struct SceKernelHeapCreateOpt {
	SceSize size;
	SceUInt32 uselock;
	SceUInt32 field_8;
	SceUInt32 field_C;
	SceUInt32 field_10;
	SceUInt32 field_14;
	SceUInt32 field_18;
} SceKernelHeapCreateOpt;

typedef struct SceCreateUidObjOpt {
	SceUInt32 flags;
	SceUInt32 field_4;
	SceUInt32 field_8;
	SceUInt32 pid;
	SceUInt32 field_10;
	SceUInt32 field_14;
	SceUInt32 field_18;
} SceCreateUidObjOpt;

typedef enum SceKernelModel {
	SCE_KERNEL_MODEL_VITA   = 0x10000,
	SCE_KERNEL_MODEL_VITATV = 0x20000
} SceKernelModel;

typedef int (* SceClassCallback)(void *item);

typedef struct SceClass {
	struct SceClass *next;
	struct SceClass *root;
	struct SceClass *prev;
	const char *name;
	struct SceClass *uidclass;
	unsigned int attributes;
	unsigned short itemsize;
	unsigned short unk1A;
	unsigned int unk1C;
	SceClassCallback create_cb;
	SceClassCallback destroy_cb;
	unsigned int magic; /* 0xABCE9DA5 */
} SceClass; /* size = 0x2C */

typedef struct SceObjectBase {
	uint32_t sce_reserved[2];
	uint32_t data[];
} SceObjectBase;

typedef struct SceKernelProcessContext {
	SceUInt32 TTBR1;
	SceUInt32 DACR;
	SceUInt32 CONTEXTIDR;
} SceKernelProcessContext;

typedef struct SceAllocOpt {
	SceSize size;   // 0x14
	SceSize data04; // maybe len align?
	SceSize align;
	int data0C;
	int data10; 
} SceAllocOpt;

/**
 * Allocates a new memory block
 *
 * @param[in] name - Name for the memory block
 * @param[in] type - Type of the memory to allocate
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

int ksceKernelMemcpyUserToKernelForPid(SceUID pid, void *dst, uintptr_t src, SceSize len);
int ksceKernelMemcpyUserToKernel(void *dst, uintptr_t src, SceSize len);
int ksceKernelMemcpyKernelToUser(uintptr_t dst, const void *src, SceSize len);
int ksceKernelRxMemcpyKernelToUserForPid(SceUID pid, uintptr_t dst, const void *src, SceSize len);

/**
 * Memory copy to user Read only memory
 *
 * @param[in] dst - The pointer of user memory
 * @param[in] src - The pointer of kern memory
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemcpyToUserRo(uintptr_t dst, const void *src, SceSize len);

/**
 * Memory copy to user Read execute memory
 *
 * @param[in] dst - The pointer of user memory
 * @param[in] src - The pointer of kern memory
 * @param[in] len - The copy length
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelMemcpyToUserRx(uintptr_t dst, const void *src, SceSize len);

int ksceKernelStrncpyUserToKernel(void *dst, uintptr_t src, SceSize len);
int ksceKernelStrncpyKernelToUser(uintptr_t dst, const void *src, SceSize len);
int ksceKernelStrncpyUserForPid(SceUID pid, void *dst, uintptr_t src, SceSize len);

SceUID ksceKernelKernelUidForUserUid(SceUID pid, SceUID user_uid);
SceUID ksceKernelCreateUserUid(SceUID pid, SceUID kern_uid);
SceUID ksceKernelCreateUidObj(SceClass *cls, const char *name, SceCreateUidObjOpt *opt, SceObjectBase **obj);

/**
 * Gets an object from a UID.
 *
 * This retains the object internally! You must call `ksceKernelUidRelease`
 * after you are done using it.
 *
 * @param[in]  uid   The uid
 * @param      cls   The class
 * @param      obj   The object
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetObjForUid(SceUID uid, SceClass *cls, SceObjectBase **obj);

/**
 * Retains an object referenced by the UID.
 *
 * This increases the internal reference count.
 *
 * @param[in]  uid   The uid
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelUidRetain(SceUID uid);

/**
 * Releases an object referenced by the UID.
 *
 * This decreases the internal reference count.
 *
 * @param[in]  uid   The uid
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelUidRelease(SceUID uid);

SceClass *ksceKernelGetUidClass(void);
SceClass *ksceKernelGetUidDLinkClass(void);
SceClass *ksceKernelGetUidHeapClass(void);
SceClass *ksceKernelGetUidMemBlockClass(void);

int ksceKernelCreateClass(SceClass *cls, const char *name, void *uidclass, SceSize itemsize, SceClassCallback create, SceClassCallback destroy);
int ksceKernelDeleteUserUid(SceUID pid, SceUID user_uid);
int ksceKernelDeleteUid(SceUID uid);
int ksceKernelFindClassByName(const char *name, SceClass **cls);

int ksceKernelSwitchVmaForPid(SceUID pid);

int ksceKernelGetPidContext(SceUID pid, SceKernelProcessContext **ctx);

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
 * Get the physical address of a given virtual address
 *
 * @param[in] addr - The virtual address
 * @param[out] paddr - The physical address
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetPaddr(const void *addr, uintptr_t *paddr);

/**
 * Get the physical address list of a given virtual address range
 *
 * @param[in] input - The virtual address range
 * @param[out] list - The list of physical addresses
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelGetPaddrList(const SceKernelAddrPair *input, SceKernelPaddrList *list);

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

#endif
