/**
 * \usergroup{SceAvcodec}
 * \usage{psp2/avcodec.h,SceAvcodec_stub}
 */


#ifndef _PSP2_AVCODEC_H_
#define _PSP2_AVCODEC_H_

#ifdef __cplusplus
extern "C" {
#endif

// missing structs
typedef struct SceAvcencCtrl SceAvcencCtrl;
typedef struct SceAvcencEncoderParameter SceAvcencEncoderParameter;
typedef struct SceAvcencEncoderInfo SceAvcencEncoderInfo;
typedef struct SceAvcencQueryEncoderInfoInternal SceAvcencQueryEncoderInfoInternal;
typedef struct SceAvcencQueryEncoderInfoBasic SceAvcencQueryEncoderInfoBasic;
typedef struct SceAvcencQueryEncoderInfo SceAvcencQueryEncoderInfo;
typedef struct SceAvcencNal SceAvcencNal;
typedef struct SceAvcencArrayAu SceAvcencArrayAu;
typedef struct SceAvcencPicture SceAvcencPicture;
typedef struct SceM4vdecDecoderInfo SceM4vdecDecoderInfo;
typedef struct SceM4vdecQueryDecoderInfo SceM4vdecQueryDecoderInfo;
typedef struct SceM4vdecCtrl SceM4vdecCtrl;
typedef struct SceM4vdecArrayPicture SceM4vdecArrayPicture;
typedef struct SceM4vdecAu SceM4vdecAu;
typedef struct SceM4vdecPicture SceM4vdecPicture;
typedef struct SceVideoencMemInfo SceVideoencMemInfo;
typedef struct SceVideoencQueryInitInfoInternal SceVideoencQueryInitInfoInternal;
typedef struct SceVideoencQueryInitInfo SceVideoencQueryInitInfo;
typedef struct SceVideodecQueryInitInfoInternal SceVideodecQueryInitInfoInternal;
typedef union SceVideodecQueryInitInfo SceVideodecQueryInitInfo; // TODO fix with videoenc.h
typedef struct SceVideoencCtrl SceVideoencCtrl;

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

SceInt32 _sceAvcencCreateEncoder(SceUInt32 codecType, SceAvcencCtrl *pCtrl, const SceAvcencQueryEncoderInfo *pEncoderInfo);
SceInt32 _sceAvcencCreateEncoderBasic(SceUInt32 codecType, SceAvcencCtrl *pCtrl, const SceAvcencQueryEncoderInfoBasic *pEncoderInfoBasic);
SceInt32 _sceAvcencCreateEncoderInternal(SceUInt32 codecType, SceAvcencCtrl *pCtrl, const SceAvcencQueryEncoderInfoInternal *pEncoderInfo);
SceInt32 _sceAvcencCsc(SceAvcencPicture *pDst, const SceAvcencPicture *pSrc);
SceInt32 _sceAvcencDeleteEncoder(SceAvcencCtrl *pCtrl);
SceInt32 _sceAvcencEncode(SceAvcencCtrl *pCtrl, const SceAvcencPicture *pPicture, SceAvcencArrayAu *pArrayAu);
SceInt32 _sceAvcencEncodeFlush(const SceAvcencCtrl *pCtrl);
SceInt32 _sceAvcencEncodeStop(SceAvcencCtrl *pCtrl, SceAvcencArrayAu *pArrayAu);
SceInt32 _sceAvcencGetNalUnit(const SceAvcencCtrl *pCtrl, SceUInt32 nalNum, SceAvcencNal *pNalUnit);
SceInt32 _sceAvcencQueryEncoderMemSize(SceUInt32 codecType, const SceAvcencQueryEncoderInfo *pEncoderInfo, SceAvcencEncoderInfo *pMemInfo);
SceInt32 _sceAvcencQueryEncoderMemSizeBasic(SceUInt32 codecType, const SceAvcencQueryEncoderInfoBasic *pEncoderInfoBasic, SceAvcencEncoderInfo *pMemInfo);
SceInt32 _sceAvcencQueryEncoderMemSizeInternal(SceUInt32 codecType, const SceAvcencQueryEncoderInfoInternal *pEncoderInfo, SceAvcencEncoderInfo *pMemInfo);
SceInt32 _sceAvcencSetAvailablePreset(SceUInt32 codecType, SceUChar8 presetMode);
SceInt32 _sceAvcencSetEncoderParameter(const SceAvcencCtrl *pCtrl, const SceAvcencEncoderParameter *pParam);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_AVCODEC_H_ */
