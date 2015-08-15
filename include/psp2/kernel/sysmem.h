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

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int SceKernelMemBlockType;

enum {
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RW	= 0x0c20d060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE	= 0x0c208060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_RW	= 0x0c80d060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_NC_RW	= 0x0d808060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW	= 0x09408060
};

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
SceUID sceKernelAllocMemBlock(const char *name, SceKernelMemBlockType type, int size, void *optp);

SceUID sceKernelAllocMemBlockForVM(const char *, SceSize);

/***
 * Frees new memoy block
 *
 * @param[in] uid - SceUID of the memory block to free
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelFreeMemBlock(SceUID uid);

/***
 * Gets the base address of a memoy block
 *
 * @param[in] uid - SceUID of the memory block to free
 * @param[out] basep - Base address of the memory block identified by SceUID
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetMemBlockBase(SceUID uid, void **basep);

SceUID sceKernelFindMemBlockByAddr(const void *, int);

void sceKernelSyncVMDomain(SceUID, void *, SceSize);
void sceKernelOpenVMDomain();
void sceKernelCloseVMDomain();

#ifdef __cplusplus
}
#endif

#endif
