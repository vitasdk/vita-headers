/**
 * \file
 * \brief Header file related to module management
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_KERNEL_MODULEMGR_H_
#define _PSP2_KERNEL_MODULEMGR_H_

#include <psp2/types.h>

typedef struct
{
	SceUInt size;	//< this structure size (0x18)
	SceUInt perms;	//< probably rwx in low bits
	void *vaddr;	//< address in memory
	SceUInt memsz;	//< size in memory
	SceUInt flags;	//< meanig unknown
	SceUInt res;	//< unused?
} Psp2SegmentInfo;

typedef struct
{
	SceUInt size;	//< 0x1B8 for Vita 1.x
	SceUInt handle;	//< kernel module handle?
	SceUInt flags;	//< some bits. could be priority or whatnot
	char module_name[28];
	SceUInt unk28;
	void *module_start;
	SceUInt unk30;
	void *module_stop;
	void *exidxTop;
	void *exidxBtm;
	SceUInt unk40;
	SceUInt unk44;
	void *tlsInit;
	SceSize tlsInitSize;
	SceSize tlsAreaSize;
	char path[256];
	Psp2SegmentInfo segments[4];
	SceUInt type;	//< 6 = user-mode PRX?
} Psp2LoadedModuleInfo;

int sceKernelGetModuleList(int, SceUID *, unsigned int *);
int sceKernelGetModuleInfo(SceUID, Psp2LoadedModuleInfo *);
SceUID sceKernelLoadModule(const char *path, int flags, int *res);
int sceKernelUnloadModule(SceUID);

#endif