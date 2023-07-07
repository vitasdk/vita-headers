/**
 * \kernelgroup{SceDisplay}
 * \usage{psp2common/display.h}
 */


#ifndef _PSP2COMMON_DISPLAY_H_
#define _PSP2COMMON_DISPLAY_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum SceDisplayErrorCode : SceInt32 {
	SCE_DISPLAY_ERROR_OK                    = 0,
	SCE_DISPLAY_ERROR_INVALID_HEAD          = (SceInt32)0x80290000,
	SCE_DISPLAY_ERROR_INVALID_VALUE         = (SceInt32)0x80290001,
	SCE_DISPLAY_ERROR_INVALID_ADDR          = (SceInt32)0x80290002,
	SCE_DISPLAY_ERROR_INVALID_PIXELFORMAT   = (SceInt32)0x80290003,
	SCE_DISPLAY_ERROR_INVALID_PITCH         = (SceInt32)0x80290004,
	SCE_DISPLAY_ERROR_INVALID_RESOLUTION    = (SceInt32)0x80290005,
	SCE_DISPLAY_ERROR_INVALID_UPDATETIMING  = (SceInt32)0x80290006,
	SCE_DISPLAY_ERROR_NO_FRAME_BUFFER       = (SceInt32)0x80290007,
	SCE_DISPLAY_ERROR_NO_PIXEL_DATA         = (SceInt32)0x80290008,
	SCE_DISPLAY_ERROR_NO_OUTPUT_SIGNAL      = (SceInt32)0x80290009
} SceDisplayErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayErrorCode);

typedef enum SceDisplayPixelFormat : SceUInt32 {
	SCE_DISPLAY_PIXELFORMAT_A8B8G8R8    = 0x00000000U,
	SCE_DISPLAY_PIXELFORMAT_A2B10G10R10 = 0x60800000U
} SceDisplayPixelFormat;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayPixelFormat);

typedef enum SceDisplaySetBufSync : SceUInt32 {
	/** Buffer change effective immediately */
	SCE_DISPLAY_SETBUF_IMMEDIATE = 0,
	/** Buffer change effective next frame */
	SCE_DISPLAY_SETBUF_NEXTFRAME = 1
} SceDisplaySetBufSync;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplaySetBufSync);

/**
 * Structure used with ::ksceDisplaySetFrameBuf to set/update framebuffer.
 * Original screen resolution is 960x544, but the following resolutions
 * can also be supplied as width and height :
 * 480x272, 640x368, 720x408
 *
 * @note - This structure is returned by ::ksceDisplayGetFrameBuf
*/
typedef struct SceDisplayFrameBuf {
	SceSize size;               //!< sizeof(SceDisplayFrameBuf)
	void *base;                 //!< Pointer to framebuffer
	unsigned int pitch;         //!< pitch pixels
	unsigned int pixelformat;   //!< pixel format (one of ::SceDisplayPixelFormat)
	unsigned int width;         //!< framebuffer width
	unsigned int height;        //!< framebuffer height
} SceDisplayFrameBuf;
VITASDK_BUILD_ASSERT_EQ(0x18, SceDisplayFrameBuf);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_DISPLAY_H_ */

