/**
 * \kernelgroup{SceDeci4pUserp}
 * \usage{psp2/deci4p/user.h.h,SceDeci4pUserp_stub}
 */


#ifndef _PSP2_DECI4P_USER_H_
#define _PSP2_DECI4P_USER_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

SceUID sceKernelDeci4pOpen(const char* protoname, SceUInt32 protonum, SceSize bufsize);
SceInt32 sceKernelDeci4pClose(SceUID socketid);
SceInt32 sceKernelDeci4pDisableWatchpoint(void);
SceInt32 sceKernelDeci4pEnableWatchpoint(void);
SceInt32 sceKernelDeci4pIsProcessAttached(void);
SceInt32 sceKernelDeci4pRead(SceUID socketid, void *buffer, SceSize size, SceUInt32 reserved);
SceInt32 sceKernelDeci4pRegisterCallback(SceUID socketid, SceUID cbid);
SceInt32 sceKernelDeci4pWrite(SceUID socketid, const void *buffer, SceSize size, SceUInt32 reserved);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_DECI4P_USER_H_ */
