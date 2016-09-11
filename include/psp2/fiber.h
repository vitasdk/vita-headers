/**
 * \file
 * \brief Header file which defines SceFiber variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 * Copyright (C) 2016 vitasdk
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_FIBER_H
#define _PSP2_FIBER_H

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Error Codes

enum {
 SCE_FIBER_ERROR_NULL = 0x80590001,
 SCE_FIBER_ERROR_ALIGNMENT = 0x80590002,
 SCE_FIBER_ERROR_RANGE = 0x80590003,
 SCE_FIBER_ERROR_INVALID = 0x80590004,
 SCE_FIBER_ERROR_PERMISSION = 0x80590005,
 SCE_FIBER_ERROR_STATE = 0x80590006,
 SCE_FIBER_ERROR_BUSY = 0x80590007,
 SCE_FIBER_ERROR_AGAIN = 0x80590008,
 SCE_FIBER_ERROR_FATAL = 0x80590009
};

typedef struct SceFiber {
	char reserved[128];
} SceFiber __attribute__((aligned(8)));

typedef struct SceFiberOptParam {
	char reserved[128];
} SceFiberOptParam __attribute__((aligned(8)));

typedef void (SceFiberEntry)(SceUInt32 argOnInitialize, SceUInt32 argOnRun);

typedef struct SceFiberInfo
{
	SceFiberEntry* entry;
	SceUInt32 argOnInitialize;
	void* addrContext;
	SceSize sizeContext;
	char name[32];
	unsigned padding[80];
} SceFiberInfo __attribute__((aligned(8)));

SceInt32 _sceFiberInitializeImpl(SceFiber* fiber, char* name, SceFiberEntry* entry, SceUInt32 argOnInitialize, void* addrContext, SceSize sizeContext, SceFiberOptParam* params);

SceInt32 _sceFiberOptParamInitialize(SceFiberOptParam* optParam);

SceInt32 sceFiberFinalize(SceFiber* fiber);

SceInt32 sceFiberRun(SceFiber* fiber, SceUInt32 argOnRunTo, SceUInt32* argOnRun);

SceInt32 sceFiberSwitch(SceFiber* fiber, SceUInt32 argOnRunTo, SceUInt32* argOnRun);

SceInt32 sceFiberGetSelf(SceFiber* fiber);

SceInt32 sceFiberReturnToThread(SceUInt32 argOnReturn, SceUInt32* argOnRun);

SceInt32 sceFiberGetInfo(SceFiber* fiber, SceFiberInfo* fiberInfo);


#ifdef __cplusplus
}
#endif
#endif
