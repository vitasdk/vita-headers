/**
 * \usergroup{SceJpegArm}
 * \internalusage{psp2/jpegarm.h,SceJpegArm_stub,SCE_SYSMODULE_INTERNAL_JPEG_ARM}
 */

#ifndef _PSP2_JPEGARM_H_
#define _PSP2_JPEGARM_H_

#include <psp2/types.h>
#include <psp2/jpeg.h>

/**
 * Error Codes
 */
typedef enum SceJpegArmErrorCode {
    SCE_JPEG_ARM_OK = 0
} SceJpegArmErrorCode;

int sceJpegArmDecodeMJpeg(const SceUInt8* pJpeg,
                          SceSize isize,
                          SceInt decodeMode,
                          void* pRGBA,
                          SceSize osize,
                          void* pCoefBuffer,
                          SceSize coefBufferSize);

int sceJpegArmDecodeMJpegYCbCr(const SceUInt8* pJpeg,
                               SceSize isize,
                               SceInt decodeMode,
                               SceUInt8* pYCbCr,
                               SceSize osize,
                               void* pCoefBuffer,
                               SceSize coefBufferSize);

int sceJpegArmGetOutputInfo(const SceUInt8* pJpeg,
                            SceSize isize,
                            SceInt decodeMode,
                            SceInt outputFormat,
                            SceJpegOutputInfo* pOutputInfo);

#endif /* _PSP2_JPEGARM_H_ */
