/**
 * \kernelgroup{SceSysmem}
 * \usage{psp2kern/kernel/sysmem.h,SceSysmemForDriver_stub}
 */


#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int SceKernelMemBlockType;

enum {
  SCE_KERNEL_MEMBLOCK_TYPE_USER_RW  = 0x0c20d060,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE  = 0x0c208060,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_RW = 0x0c80d060,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_NC_RW  = 0x0d808060,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW  = 0x09408060,
  SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RX = 0x1020D005,
  SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW = 0x1020D006,
  SCE_KERNEL_MEMBLOCK_TYPE_SHARED_RX = 0x390D050,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_RX = 0xC20D050,
  SCE_KERNEL_MEMBLOCK_TYPE_RW_UNK0 = 0x6020D006
};

// specific to 3.60
typedef struct SceKernelAllocMemBlockKernelOpt {
  SceSize size;
  SceUInt32 field_4;
  SceUInt32 attr;
  SceUInt32 field_C;
  SceUInt32 paddr;
  SceSize alignment;
  SceUInt32 field_18;
  SceUInt32 field_1C;
  SceUInt32 mirror_blkid;
  SceUID pid;
  SceUInt32 field_28;
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

enum {
  SCE_KERNEL_MODEL_VITA = 0x10000,
  SCE_KERNEL_MODEL_VITATV = 0x20000
};

#define SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_ALIGNMENT    0x00000004U

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
SceUID ksceKernelAllocMemBlock(const char *name, SceKernelMemBlockType type, int size, SceKernelAllocMemBlockKernelOpt *optp);

/***
 * Frees new memory block
 *
 * @param[in] uid - SceUID of the memory block to free
 *
 * @return 0 on success, < 0 on error.
*/
int ksceKernelFreeMemBlock(SceUID uid);

/***
 * Gets the base address of a memory block
 *
 * @param[in] uid - SceUID of the memory block to free
 * @param[out] basep - Base address of the memory block identified by SceUID
 *
 * @return 0 on success, < 0 on error.
*/
int ksceKernelGetMemBlockBase(SceUID uid, void **basep);

/***
 * Find the SceUID of a memory block
 *
 * @param[in] addr - Base address of the memory block
 * @param[in] size - Size to search for (usally set to 0)
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID ksceKernelFindMemBlockByAddr(const void *addr, SceSize size);

/**
 * Changes the block type
 *
 * @param[in] uid - SceUID of the memory block to change
 * @param[in] type - Type of the memory to change to
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelRemapBlock(SceUID uid, SceKernelMemBlockType type);

SceUID ksceKernelCreateHeap(const char *name, SceSize size, SceKernelHeapCreateOpt *opt);
int ksceKernelDeleteHeap(SceUID uid);
void *ksceKernelAllocHeapMemory(SceUID uid, SceSize size);
void ksceKernelFreeHeapMemory(SceUID uid, void *ptr);

int ksceKernelMemcpyUserToKernelForPid(SceUID pid, void *dst, uintptr_t src, size_t len);
int ksceKernelMemcpyUserToKernel(void *dst, uintptr_t src, size_t len);
int ksceKernelMemcpyKernelToUser(uintptr_t dst, const void *src, size_t len);
int ksceKernelRxMemcpyKernelToUserForPid(SceUID pid, uintptr_t dst, const void *src, size_t len);

int ksceKernelStrncpyUserToKernel(void *dst, uintptr_t src, size_t len);
int ksceKernelStrncpyKernelToUser(uintptr_t dst, const void *src, size_t len);
int ksceKernelStrncpyUserForPid(SceUID pid, void *dst, uintptr_t src, size_t len);

typedef struct {
  char data[0x2C];
} SceClass;

typedef struct {
  uint32_t sce_reserved[2];
} SceObjectBase;

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
typedef int (*SceClassCallback)(void *item);
int ksceKernelCreateClass(SceClass *cls, const char *name, void *uidclass, size_t itemsize, SceClassCallback create, SceClassCallback destroy);
int ksceKernelDeleteUserUid(SceUID pid, SceUID user_uid);
int ksceKernelDeleteUid(SceUID uid);

int ksceKernelSwitchVmaForPid(SceUID pid);

void *ksceKernelGetSysrootBuffer(void);
int ksceKernelGetPidContext(SceUID pid, int **ctx);

int ksceKernelGetProcessTitleId(SceUID pid, char *titleid, size_t len);

int ksceKernelMapBlockUserVisible(SceUID uid);

int ksceKernelGetPaddr(void *addr, uintptr_t *paddr);

int ksceSysrootIsManufacturingMode(void);

int ksceDebugPrintf(const char *fmt, ...);

int ksceDebugPrintf2(int unk0, int unk1, const char *fmt, ...);

int ksceDebugSetHandlers(int (*func)(void *args, char c), void *args);

int ksceDebugRegisterPutcharHandler(int (*func)(void *args, char c), void *args);

void *ksceDebugGetPutcharHandler(void);

int ksceDebugPutchar(int character);

#ifdef __cplusplus
}
#endif

#endif

