/**
 * \file
 * \brief Header file which defines memory related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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

typedef struct SceKernelMemPoolCreateOpt {
  SceSize size;
  SceUInt32 uselock;
  SceUInt32 field_8;
  SceUInt32 field_C;
  SceUInt32 field_10;
  SceUInt32 field_14;
  SceUInt32 field_18;
} SceKernelMemPoolCreateOpt;

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
 * Allocates a new memoy block
 *
 * @param[in] name - Name for the memory block
 * @param[in] type - Type of the memory to allocate
 * @param[in] size - Size of the memory to allocate
 * @param[in] optp - Memory block options?
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID sceKernelAllocMemBlockForKernel(const char *name, SceKernelMemBlockType type, int size, SceKernelAllocMemBlockKernelOpt *optp);

/***
 * Frees new memoy block
 *
 * @param[in] uid - SceUID of the memory block to free
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelFreeMemBlockForKernel(SceUID uid);

/***
 * Gets the base address of a memoy block
 *
 * @param[in] uid - SceUID of the memory block to free
 * @param[out] basep - Base address of the memory block identified by SceUID
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetMemBlockBaseForKernel(SceUID uid, void **basep);

SceUID sceKernelMemPoolCreate(const char *name, SceSize size, SceKernelMemPoolCreateOpt *opt);
int sceKernelMemPoolDestroy(SceUID pool);
void *sceKernelMemPoolAlloc(SceUID pool, SceSize size);
void sceKernelMemPoolFree(SceUID pool, void *ptr);

int sceKernelMemcpyUserToKernelForPid(SceUID pid, void *dst, uintptr_t src, size_t len);
int sceKernelMemcpyUserToKernel(void *dst, uintptr_t src, size_t len);
int sceKernelMemcpyKernelToUser(uintptr_t dst, const void *src, size_t len);
int sceKernelRxMemcpyKernelToUserForPid(SceUID pid, uintptr_t dst, const void *src, size_t len);

int sceKernelStrncpyUserToKernel(void *dst, uintptr_t src, size_t len);
int sceKernelStrncpyKernelToUser(uintptr_t dst, const void *src, size_t len);
int sceKernelStrncpyUserForPid(SceUID pid, void *dst, uintptr_t src, size_t len);

typedef struct {
  char data[0x2C];
} SceClass;

typedef struct {
  uint32_t sce_reserved[2];
} SceObjectBase;

SceUID sceKernelKernelUidForUserUid(SceUID pid, SceUID user_uid);
SceUID sceKernelCreateUserUid(SceUID pid, SceUID kern_uid);
SceUID sceKernelCreateUidObj(SceClass *cls, const char *name, SceCreateUidObjOpt *opt, SceObjectBase **obj);
int sceKernelGetObjForUid(SceUID uid, SceClass *cls, SceObjectBase **obj);
SceClass *sceKernelGetUidClass(void);
typedef int (*SceClassCallback)(void *item);
int sceKernelCreateClass(SceClass *cls, const char *name, void *uidclass, size_t itemsize, SceClassCallback create, SceClassCallback destroy);
int sceKernelDeleteUserUid(SceUID pid, SceUID user_uid);
int sceKernelDeleteUid(SceUID uid);

int sceKernelSwitchVmaForPid(SceUID pid);

void *sceKernelGetSysrootBuffer(void);
int sceKernelGetPidContext(SceUID pid, int **ctx);

int sceKernelGetProcessTitleIdForKernel(SceUID pid, char *titleid, size_t len);

int sceKernelMapBlockUserVisible(SceUID uid);

#ifdef __cplusplus
}
#endif

#endif
