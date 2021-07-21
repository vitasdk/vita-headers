/**
 * \usergroup{SceAvcodec}
 * \usage{psp2/avcodec.h,SceAvcodec_stub}
 */


#ifndef _PSP2_AVCODEC_H_
#define _PSP2_AVCODEC_H_

#ifdef __cplusplus
extern "C" {
#endif

SceInt32 _sceVideoencInitLibrary(SceUInt32 codecType, const SceVideodecQueryInitInfo *pInitDecInfo, const SceVideoencQueryInitInfo *pInitEncInfo);
SceInt32 _sceVideoencInitLibraryInternal(SceUInt32 codecType, const SceVideodecQueryInitInfoInternal *pInitDecInfo, const SceVideoencQueryInitInfoInternal *pInitEncInfo);
SceInt32 _sceVideoencInitLibraryWithMemInternal(SceUInt32 codecType, SceVideoencCtrl *pCtrl, const SceVideodecQueryInitInfoInternal *pInitInfo, const SceVideoencQueryInitInfoInternal *pInitEncInfo);
SceInt32 _sceVideoencInitLibraryWithUnmapMem(SceUInt32 codecType, SceVideoencCtrl *pCtrl, const SceVideodecQueryInitInfo *pInitDecInfo, const SceVideoencQueryInitInfo *pInitEncInfo);
SceInt32 _sceVideoencInitLibraryWithUnmapMemInternal(SceUInt32 codecType, SceVideoencCtrl *pCtrl, const SceVideodecQueryInitInfoInternal *pInitDecInfo, const SceVideoencQueryInitInfoInternal *pInitEncInfo);
SceInt32 _sceVideoencQueryMemSize(SceUInt32 codecType, const SceVideodecQueryInitInfo *pInitDecInfo, const SceVideoencQueryInitInfo *pInitEncInfo, SceVideoencMemInfo *pMemInfo);
SceInt32 _sceVideoencQueryMemSizeInternal(SceUInt32 codecType, const SceVideodecQueryInitInfoInternal *pInitDecInfo, const SceVideoencQueryInitInfoInternal *pInitEncInfo, SceVideoencMemInfo *pMemInfo);
SceInt32 _sceVideoencTermLibrary(SceUInt32 codecType);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_AVCODEC_H_ */
