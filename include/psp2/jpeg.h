/**
 * \usergroup{SceJpeg}
 * \usage{psp2/jpeg.h,SceJpeg_stub}
 */

#ifndef _PSP2_JPEG_H_
#define _PSP2_JPEG_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceJpegMJpegInitParam {
    SceSize size;
    SceInt32 decoderCount;
    SceInt32 options;
} SceJpegMJpegInitParam;

typedef struct SceJpegPitch {
    SceUInt32 x;
    SceUInt32 y;
} SceJpegPitch;

typedef struct SceJpegOutputInfo {
    SceInt32 colorSpace;
    SceUInt16 width;
    SceUInt16 height;
    SceUInt32 outputSize;
    SceUInt32 unk_0xc;
    SceUInt32 unk_0x10;
    SceJpegPitch pitch[4];
} SceJpegOutputInfo;

int sceJpegInitMJpeg(SceInt32 decoderCount);

int sceJpegInitMJpegWithParam(const SceJpegMJpegInitParam* params);

int sceJpegFinishMJpeg();

int sceJpegGetOutputInfo(const SceUInt8* jpegData,
                        SceSize jpegSize,
                        SceInt32 format,
                        SceInt32 mode,
                        SceJpegOutputInfo *output);

int sceJpegDecodeMJpegYCbCr(const SceUInt8 *jpegData,
                            SceSize jpegSize,
                            SceInt32 mode,
                            SceUInt8 *output,
                            SceSize outputSize,
                            void *buffer,
                            SceSize bufferSize);

int sceJpegMJpegCsc(SceUInt8* rgba,
                    const SceUInt8* yuv,
                    SceSize yuvSize,
                    SceInt32 imageWidth,
                    SceInt32 format,
                    SceInt32 sampling);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_JPEG_H_ */
