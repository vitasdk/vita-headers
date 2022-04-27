/**
 * \usergroup{SceFiber}
 * \usage{psp2/fiber.h,SceFiber_stub,SCE_SYSMODULE_FIBER}
 */


#ifndef _PSP2_FIBER_H
#define _PSP2_FIBER_H

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Error Codes

typedef enum SceFiberErrorCode {
	SCE_FIBER_ERROR_NULL       = 0x80590001,
	SCE_FIBER_ERROR_ALIGNMENT  = 0x80590002,
	SCE_FIBER_ERROR_RANGE      = 0x80590003,
	SCE_FIBER_ERROR_INVALID    = 0x80590004,
	SCE_FIBER_ERROR_PERMISSION = 0x80590005,
	SCE_FIBER_ERROR_STATE      = 0x80590006,
	SCE_FIBER_ERROR_BUSY       = 0x80590007,
	SCE_FIBER_ERROR_AGAIN      = 0x80590008,
	SCE_FIBER_ERROR_FATAL      = 0x80590009
} SceFiberErrorCode;

typedef struct SCE_ALIGN(8) SceFiber {
	char reserved[128];
} SceFiber;

typedef struct SCE_ALIGN(8) SceFiberOptParam {
	char reserved[128];
} SceFiberOptParam;

typedef void (SceFiberEntry)(SceUInt32 argOnInitialize, SceUInt32 argOnRun);

typedef struct SCE_ALIGN(8) SceFiberInfo {
	SceFiberEntry* entry;
	SceUInt32 argOnInitialize;
	void* addrContext;
	SceSize sizeContext;
	char name[32];
	unsigned padding[80];
} SceFiberInfo;

SceInt32 _sceFiberInitializeImpl(SceFiber* fiber, char* name, SceFiberEntry* entry, SceUInt32 argOnInitialize, void* addrContext, SceSize sizeContext, SceFiberOptParam* params);

SceInt32 sceFiberOptParamInitialize(SceFiberOptParam* optParam);

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

