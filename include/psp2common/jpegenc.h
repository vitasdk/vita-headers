/**
 * \usergroup{SceJpegEnc}
 * \usage{psp2common/jpegenc.h}
 */

#ifndef _PSP2COMMON_JPEGENC_H_
#define _PSP2COMMON_JPEGENC_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef void *SceJpegEncoderContext;
VITASDK_BUILD_ASSERT_EQ(4, SceJpegEncoderContext);

typedef enum SceJpegEncErrorCode {
	SCE_JPEGENC_ERROR_IMAGE_SIZE                = 0x80650200,
	SCE_JPEGENC_ERROR_INSUFFICIENT_BUFFER       = 0x80650201,
	SCE_JPEGENC_ERROR_INVALID_COMPRATIO         = 0x80650202,
	SCE_JPEGENC_ERROR_INVALID_PIXELFORMAT       = 0x80650203,
	SCE_JPEGENC_ERROR_INVALID_HEADER_MODE       = 0x80650204,
	SCE_JPEGENC_ERROR_INVALID_POINTER           = 0x80650205,
	SCE_JPEGENC_ERROR_NOT_PHY_CONTINUOUS_MEMORY = 0x80650206
} SceJpegEncErrorCode;

typedef enum SceJpegEncoderPixelFormat {
	SCE_JPEGENC_PIXELFORMAT_ARGB8888 = 0,       //!< ARGB8888 format
	SCE_JPEGENC_PIXELFORMAT_YCBCR420 = 8,       //!< YCbCr420 format
	SCE_JPEGENC_PIXELFORMAT_YCBCR422 = 9,       //!< YCbCr422 format
	SCE_JPEGENC_PIXELFORMAT_CSC_ARGB_YCBCR = 16 //!< ARGB to YCbCr color conversion flag
} SceJpegEncoderPixelFormat;

typedef enum SceJpegEncoderHeaderMode {
	SCE_JPEGENC_HEADER_MODE_JPEG = 0,   //!< JPEG header mode
	SCE_JPEGENC_HEADER_MODE_MJPEG = 1   //!< MJPEG header mode
} SceJpegEncoderHeaderMode;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2COMMON_JPEGENC_H_ */
