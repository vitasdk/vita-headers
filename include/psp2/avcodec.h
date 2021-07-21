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

SceInt32 _sceM4vdecCreateDecoder(SceUInt32 codecType, SceM4vdecCtrl *pCtrl, const SceM4vdecQueryDecoderInfo *pDecoderInfo);
SceInt32 _sceM4vdecCreateDecoderInternal(SceUInt32 codecType, SceM4vdecCtrl *pCtrl, const SceM4vdecQueryDecoderInfo *pDecoderInfo);
SceInt32 _sceM4vdecCsc(SceM4vdecPicture *pDst, const SceM4vdecPicture *pSrc);
SceInt32 _sceM4vdecDecode(const SceM4vdecCtrl *pCtrl, const SceM4vdecAu *pAu, SceM4vdecArrayPicture *pArrayPicture);
SceInt32 _sceM4vdecDecodeAvailableSize(SceM4vdecCtrl *pCtrl);
SceInt32 _sceM4vdecDecodeFlush(const SceM4vdecCtrl *pCtrl);
SceInt32 _sceM4vdecDecodeStop(const SceM4vdecCtrl *pCtrl, SceM4vdecArrayPicture *pArrayPicture);
SceInt32 _sceM4vdecDecodeStopWithWorkPicture(const SceM4vdecCtrl *pCtrl, SceM4vdecArrayPicture *pArrayPicture, SceM4vdecArrayPicture *pWorkArrayPicture);
SceInt32 _sceM4vdecDecodeWithWorkPicture(const SceM4vdecCtrl *pCtrl, const SceM4vdecAu *pAu, SceM4vdecArrayPicture *pArrayPicture, SceM4vdecArrayPicture *pWorkArrayPicture);
SceInt32 _sceM4vdecDeleteDecoder(SceM4vdecCtrl *pCtrl);
SceInt32 _sceM4vdecQueryDecoderMemSize(SceUInt32 codecType, const SceM4vdecQueryDecoderInfo *pDecoderInfo, SceM4vdecDecoderInfo *pMemInfo);
SceInt32 _sceM4vdecQueryDecoderMemSizeInternal(SceUInt32 codecType, const SceM4vdecQueryDecoderInfo *pDecoderInfo, SceM4vdecDecoderInfo *pMemInfo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_AVCODEC_H_ */
