/**
 * \kernelgroup{SceDeci4pDbgp}
 * \usage{psp2kern/deci4p.h,SceDeci4pDbgpForDriver_stub}
 */

#ifndef _PSP2KERN_DECI4P_H_
#define _PSP2KERN_DECI4P_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SceInt32 (SceDbgpBreakpointHandler)(ScePID pid, SceUID thid, ScePVoid bkpt_addr, SceUIntPtr sp, SceUInt32 cpsr, SceUInt32 arm_opcode, SceUInt16 thumb_opcode, SceBool is_thumb);

SceDbgpBreakpointHandler *ksceDbgpGetDTraceBreakpointHandler(void);
SceDbgpBreakpointHandler *ksceDbgpGetDTraceUsdtHandler(void);
void ksceDbgpSetDTraceBreakpointHandler(SceDbgpBreakpointHandler *handler);
void ksceDbgpSetDTraceUsdtHandler(SceDbgpBreakpointHandler *handler);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_DECI4P_H_ */
