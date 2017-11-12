/**
 * \usergroup{SceVshBridge}
 * \usage{psp2/vshbridge.h,SceVshBridge_stub}
 */

#ifndef _PSP2_VSHBRIDGE_H_
#define _PSP2_VSHBRIDGE_H_

#include <psp2/types.h>
#include <psp2/kernel/modulemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

int _vshSblGetSystemSwVersion(SceKernelFwInfo * data);
 
int _vshSblAimgrGetConsoleId(char CID[32]);
 
int vshIdStorageIsDirty(void);
int vshIdStorageIsFormatted(void);
int vshIdStorageIsReadOnly(void);
 
int vshSblAimgrIsCEX(void);
int vshSblAimgrIsDEX(void);
int vshSblAimgrIsGenuineVITA(void);
int vshSblAimgrIsGenuineDolce(void);
int vshSblAimgrIsTest(void);
int vshSblAimgrIsTool(void);
int vshSblSsIsDevelopmentMode(void);
int sceKernelIsPSVitaTV(void);
 
int vshSysconHasWWAN(void);
 
int vshSysconIsDownLoaderMode(void);
int vshSysconIsIduMode(void);
int vshSysconIsMCEmuCapable(void);
int vshSysconIsShowMode(void);
 
int vshMemoryCardGetCardInsertState(void);
int vshRemovableMemoryGetCardInsertState(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_VSHBRIDGE_H_ */