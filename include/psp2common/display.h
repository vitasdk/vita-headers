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

#define SCE_DISPLAY_UPDATETIMING_NEXTHSYNC 0
#define SCE_DISPLAY_UPDATETIMING_NEXTVSYNC 1

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


typedef enum SceDisplayFrameBufType {
	SCE_DISPLAY_FRAMEBUF_GAME_APP = 0,
	SCE_DISPLAY_FRAMEBUF_LIVEAREA = 1
} SceDisplayFrameBufType;
VITASDK_BUILD_ASSERT_EQ(1, SceDisplayFrameBufType);

typedef enum SceDisplayHead {
	SCE_DISPLAY_HEAD_MAIN_LCD_OLED = 0,
	SCE_DISPLAY_HEAD_HDMI          = 1,
	SCE_DISPLAY_HEAD_SUB_LCD       = 2
} SceDisplayHead;
VITASDK_BUILD_ASSERT_EQ(1, SceDisplayHead);

typedef enum SceDisplayScreenModeFlag {
	SCE_DISPLAY_SCREENMODE_FLAG_60_HTZ = 0x0000,
	SCE_DISPLAY_SCREENMODE_FLAG_24_HTZ = 0x0020,
	SCE_DISPLAY_SCREENMODE_FLAG_50_HTZ = 0x0080,
	SCE_DISPLAY_SCREENMODE_FLAG_480P   = 0x0300,
	SCE_DISPLAY_SCREENMODE_FLAG_576P   = 0x0400,
	SCE_DISPLAY_SCREENMODE_FLAG_1080I  = 0x0500,
	SCE_DISPLAY_SCREENMODE_FLAG_720P   = 0x0600,
	SCE_DISPLAY_SCREENMODE_FLAG_1080P  = 0x0700
} SceDisplayScreenModeFlag;
VITASDK_BUILD_ASSERT_EQ(2, SceDisplayScreenModeFlag);

typedef SceUInt32 SceDisplayScreenMode;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayScreenMode);

typedef enum SceDisplayScanMode {
	SCE_DISPLAY_SCANMODE_PROGRESSIVE = 0,
	SCE_DISPLAY_SCANMODE_INTERLACED = 1
} SceDisplayScanMode;
VITASDK_BUILD_ASSERT_EQ(1, SceDisplayScanMode);

typedef struct SceDisplayCaptureFrameBuf {
	SceSize size;
	void *base;
	unsigned int pitch;
	SceDisplayPixelFormat pixelformat;
	unsigned int width;
	unsigned int height;
} SceDisplayCaptureFrameBuf;
VITASDK_BUILD_ASSERT_EQ(0x18, SceDisplayCaptureFrameBuf); // size is from FW 3.60

typedef struct SceDisplayResolutionInfo {
	SceSize size;
	SceDisplayScreenMode screenMode;
	SceUInt32 width;
	SceUInt32 height;
	SceDisplayPixelFormat pixelformat;
	SceDisplayScanMode scanMode;
	float fps;
} SceDisplayResolutionInfo;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceDisplayResolutionInfo); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_DISPLAY_H_ */
