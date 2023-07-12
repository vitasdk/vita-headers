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


typedef enum SceDisplayErrorCode {
	SCE_DISPLAY_ERROR_OK                    = 0,
	SCE_DISPLAY_ERROR_INVALID_HEAD          = 0x80290000,
	SCE_DISPLAY_ERROR_INVALID_VALUE         = 0x80290001,
	SCE_DISPLAY_ERROR_INVALID_ADDR          = 0x80290002,
	SCE_DISPLAY_ERROR_INVALID_PIXELFORMAT   = 0x80290003,
	SCE_DISPLAY_ERROR_INVALID_PITCH         = 0x80290004,
	SCE_DISPLAY_ERROR_INVALID_RESOLUTION    = 0x80290005,
	SCE_DISPLAY_ERROR_INVALID_UPDATETIMING  = 0x80290006,
	SCE_DISPLAY_ERROR_NO_FRAME_BUFFER       = 0x80290007,
	SCE_DISPLAY_ERROR_NO_PIXEL_DATA         = 0x80290008,
	SCE_DISPLAY_ERROR_NO_OUTPUT_SIGNAL      = 0x80290009
} SceDisplayErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayErrorCode);

typedef enum SceDisplayPixelFormat {
	SCE_DISPLAY_PIXELFORMAT_A8B8G8R8    = 0x00000000U,
	SCE_DISPLAY_PIXELFORMAT_A2B10G10R10 = 0x60800000U
} SceDisplayPixelFormat;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayPixelFormat);

typedef enum SceDisplaySetBufSync {
	/** Buffer change effective immediately */
	SCE_DISPLAY_SETBUF_IMMEDIATE = 0,
	/** Buffer change effective next frame */
	SCE_DISPLAY_SETBUF_NEXTFRAME = 1,
	__SCE_DISPLAY_SETBUF = 0xFFFFFFFF
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

