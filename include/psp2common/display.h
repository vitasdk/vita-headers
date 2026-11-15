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
	unsigned int pixelformat;   //!< Combined pixel-format and RGB-range encoding
	unsigned int width;         //!< framebuffer width
	unsigned int height;        //!< framebuffer height
} SceDisplayFrameBuf;
VITASDK_BUILD_ASSERT_EQ(0x18, SceDisplayFrameBuf);

/** Flags stored in ::SceDisplayFrameBufExt::flags. */
typedef enum SceDisplayFrameBufFlag {
	SCE_DISPLAY_FRAMEBUF_FLAG_SHARED   = 0x00040000, //!< Identifies a shared framebuffer.
	SCE_DISPLAY_FRAMEBUF_FLAG_BILINEAR = 0x00100000  //!< Enable bilinear filtering.
} SceDisplayFrameBufFlag;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayFrameBufFlag);

/**
 * Extended framebuffer descriptor accepted by FW 3.60.
 *
 * ::SceDisplayFrameBuf remains 0x18 bytes for backwards compatibility. The
 * raw and internal framebuffer APIs also accept this 0x1C-byte structure.
 * To use it, set \a size to `sizeof(SceDisplayFrameBufExt)`.
 * FW 3.60 permits only bits in the mask 0x001F0000 in \a flags. The purposes of
 * bits 0x00020000 and 0x00080000 are unknown.
 * For a 0x18-byte structure, the driver sets
 * ::SCE_DISPLAY_FRAMEBUF_FLAG_BILINEAR internally.
 */
typedef struct SceDisplayFrameBufExt {
	SceSize size; //!< Must be set to sizeof(SceDisplayFrameBufExt).
	void *base; //!< Framebuffer base address.
	unsigned int pitch; //!< Pitch in pixels.
	unsigned int pixelformat; //!< Combined pixel-format and RGB-range encoding.
	unsigned int width; //!< Framebuffer width in pixels.
	unsigned int height; //!< Framebuffer height in pixels.
	SceUInt32 flags; //!< Bitwise OR of ::SceDisplayFrameBufFlag values and other firmware-defined bits.
} SceDisplayFrameBufExt;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceDisplayFrameBufExt); // size is from FW 3.60


typedef enum SceDisplayFrameBufType {
	SCE_DISPLAY_FRAMEBUF_GAME_APP = 0, //!< Game or application framebuffer.
	SCE_DISPLAY_FRAMEBUF_LIVEAREA = 1 //!< LiveArea, HOME, and system-overlay framebuffer.
} SceDisplayFrameBufType;
VITASDK_BUILD_ASSERT_EQ(1, SceDisplayFrameBufType);

typedef enum SceDisplayHead {
	SCE_DISPLAY_HEAD_MAIN_LCD_OLED = 0, //!< Built-in OLED or LCD panel.
	SCE_DISPLAY_HEAD_HDMI          = 1, //!< HDMI output.
	SCE_DISPLAY_HEAD_SUB_LCD       = 2  //!< Secondary LCD state reserved by the display driver.
} SceDisplayHead;
VITASDK_BUILD_ASSERT_EQ(1, SceDisplayHead);

/**
 * Complete screen-mode identifiers accepted by the FW 3.60 DSI driver.
 *
 * Use these IDs as listed; do not combine them as flags. For example,
 * 1080p at 24 Hz is 0x8730; ORing 0x0700 with 0x0020 produces 0x0720, which
 * FW 3.60 rejects.
 */
typedef enum SceDisplayScreenModeId {
	SCE_DISPLAY_SCREENMODE_INTERNAL_960X544               = 0x0000, //!< Progressive; 1050x594 total timing.
	SCE_DISPLAY_SCREENMODE_INTERNAL_960X544_1375X567       = 0x0020, //!< Progressive; 1375x567 total timing.
	SCE_DISPLAY_SCREENMODE_INTERNAL_960X540                = 0x0080, //!< Progressive; 1250x594 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_720X480_858X525        = 0x8300, //!< Progressive; 858x525 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_720X480_858X526        = 0x8370, //!< Progressive; 858x526 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_720X576_864X625        = 0x8480, //!< Progressive; 864x625 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_720X575_864X626        = 0x84F0, //!< Progressive; 864x626 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_1080I_60HZ             = 0x8500, //!< Interlaced; 2200x1125 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_1080I_50HZ             = 0x8580, //!< Interlaced; 2640x1125 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_720P_60HZ              = 0x8600, //!< Progressive; 1650x750 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_720P_50HZ              = 0x8680, //!< Progressive; 1980x750 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_1080P_60HZ             = 0x8710, //!< Progressive; 2200x1125 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_1080P_24HZ             = 0x8730, //!< Progressive; 2750x1125 total timing.
	SCE_DISPLAY_SCREENMODE_EXTERNAL_1080P_50HZ             = 0x8790, //!< Progressive; 2640x1125 total timing.
	SCE_DISPLAY_SCREENMODE_1280X720_1428X775               = 0x8900  //!< Progressive; 1428x775 total timing.
} SceDisplayScreenModeId;
VITASDK_BUILD_ASSERT_EQ(2, SceDisplayScreenModeId);

/** Storage type for one of ::SceDisplayScreenModeId. */
typedef SceUInt32 SceDisplayScreenMode;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayScreenMode);

typedef enum SceDisplayScanMode {
	SCE_DISPLAY_SCANMODE_PROGRESSIVE = 0, //!< Progressive scan.
	SCE_DISPLAY_SCANMODE_INTERLACED = 1 //!< Interlaced scan.
} SceDisplayScanMode;
VITASDK_BUILD_ASSERT_EQ(1, SceDisplayScanMode);

/**
 * Framebuffer capture destination.
 *
 * The DMAC capture functions use \a width and \a height as maximum dimensions,
 * ignore the input \a pixelformat, and replace all three fields with the copied
 * source values. The IFTU capture functions instead use all three fields as
 * destination parameters and leave the structure unchanged.
 */
typedef struct SceDisplayCaptureFrameBuf {
	SceSize size; //!< Must be set to sizeof(SceDisplayCaptureFrameBuf).
	void *base; //!< Capture destination; must be aligned to 0x100 bytes on FW 3.60.
	unsigned int pitch; //!< Destination pitch in pixels.
	unsigned int pixelformat; //!< Format value; see the capture function being used.
	unsigned int width; //!< Requested or resulting width in pixels.
	unsigned int height; //!< Requested or resulting height in pixels.
} SceDisplayCaptureFrameBuf;
VITASDK_BUILD_ASSERT_EQ(0x18, SceDisplayCaptureFrameBuf); // size is from FW 3.60

typedef struct SceDisplayResolutionInfo {
	SceSize size; //!< Must be set to sizeof(SceDisplayResolutionInfo).
	SceDisplayScreenMode screen_mode; //!< One of ::SceDisplayScreenModeId.
	SceUInt32 width; //!< Output width in pixels.
	SceUInt32 height; //!< Output height in pixels.
	SceUInt32 output_format; //!< Combined pixel-format and RGB-range encoding.
	SceUInt32 scan_mode; //!< One of ::SceDisplayScanMode; stored as a 32-bit value.
	float fps; //!< Driver refresh-rate value; approximately 59.940056 on FW 3.60.
} SceDisplayResolutionInfo;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceDisplayResolutionInfo); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_DISPLAY_H_ */
