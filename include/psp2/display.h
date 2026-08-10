/**
 * \usergroup{SceDisplay}
 * \usage{psp2/display.h,SceDisplay_stub}
 */


#ifndef _PSP2_DISPLAY_H_
#define _PSP2_DISPLAY_H_

#include <vitasdk/build_utils.h>
#include <psp2common/display.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set/Update framebuffer parameters
 *
 * @param[in] pParam - Pointer to a ::SceDisplayFrameBuf structure.
 * @param[in] sync - One of ::SceDisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as pParam pointer, output is blacked out.
*/
int sceDisplaySetFrameBuf(const SceDisplayFrameBuf *pParam, SceDisplaySetBufSync sync);

/**
 * Get current framebuffer parameters
 *
 * @param[out] pParam - Pointer to a ::SceDisplayFrameBuf structure
 * which will receive framebuffer parameters.
 *
 * @param[in] sync - One of ::SceDisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
*/
int sceDisplayGetFrameBuf(SceDisplayFrameBuf *pParam, SceDisplaySetBufSync sync);

/**
 * Primary display index
 */
int sceDisplayGetPrimaryHead(void);

/**
 * Get current number of fps for the current screen mode.
 *
 * @param[out] pFps - Pointer to a float variable to store current number of fps.
 *
 * @return 0 on success, < 0 on error.
 * @note - This function returns a theoretical value, this might not be the exact frame rate.
*/
int sceDisplayGetRefreshRate(float *pFps);

/**
 * Get maximum framebuffer resolution
 *
 * @param[out] width - Maximum width
 * @param[out] height - Maximum height
 *
 * @return 0 on success, < 0 on error.
*/
int sceDisplayGetMaximumFrameBufResolution(int *width, int *height);

/**
 * Number of vertical blank pulses up to now
 */
int sceDisplayGetVcount(void);

/**
 * Number of vertical blank pulses up to now for a display
 *
 * @param[in] display - Display index
 */
int sceDisplayGetVcountInternal(int display);

/**
 * Wait for vertical blank start
 */
int sceDisplayWaitVblankStart(void);

/**
 * Wait for vertical blank start with callback
 */
int sceDisplayWaitVblankStartCB(void);

/**
 * Wait for vertical blank start after specified number of vertical periods
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitVblankStartMulti(unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitVblankStartMultiCB(unsigned int vcount);

/**
 * Wait for vertical blank start since last update of framebuffer
 */
int sceDisplayWaitSetFrameBuf(void);

/**
 * Wait for vertical blank start with callback since last update of framebuffer
 */
int sceDisplayWaitSetFrameBufCB(void);

/**
 * Wait for vertical blank start after specified number of vertical periods
 * since last update of framebuffer.
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitSetFrameBufMulti(unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods
 * since last update of framebuffer.
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitSetFrameBufMultiCB(unsigned int vcount);

/**
 * Register callback to be used at each vertical blank start
 *
 * @param[in] uid - Callback UID
 */
int sceDisplayRegisterVblankStartCallback(SceUID uid);

/**
 * Unregister callback used at each vertical blank start
 *
 * @param[in] uid - Callback UID
 */
int sceDisplayUnregisterVblankStartCallback(SceUID uid);

typedef struct SceDisplayGetFrameBufInternalOpt {
	SceInt32 iUpdateTimingMode; //!< One of ::SceDisplayUpdateTiming.
	SceSize frameBufSize; //!< Set to sizeof(SceDisplayFrameBuf) for the declared output type; maximum 0x1C with a larger compatible buffer.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceDisplayGetFrameBufInternalOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceDisplayGetFrameBufInternalOpt); // size is from FW 3.60

typedef struct SceDisplayGetFrameBufOpt {
	SceInt32 frameBufSize; //!< Set to sizeof(SceDisplayFrameBuf) for the declared output type; a ::SceSize value with a maximum of 0x1C.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceDisplayGetFrameBufOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceDisplayGetFrameBufOpt); // size is from FW 3.60

typedef struct SceDisplayGetResolutionInfoInternalOpt {
	SceSize infoSize; //!< Set to sizeof(SceDisplayResolutionInfo).
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceDisplayGetResolutionInfoInternalOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceDisplayGetResolutionInfoInternalOpt); // size is from FW 3.60

typedef struct SceDisplayFrameBufForCompat {
	SceSize size; //!< Must be set to 0x1C.
	void *base;
	unsigned int pitch; //!< Pitch in pixels.
	unsigned int pixelformat; //!< One of ::SceDisplayPixelFormat.
	unsigned int width;
	unsigned int height;
	SceUInt32 flags; //!< Bitwise OR of ::SceDisplayFrameBufForCompatFlag values.
} SceDisplayFrameBufForCompat;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceDisplayFrameBufForCompat); // size is from FW 3.60

typedef enum SceDisplayFrameBufForCompatFlag {
	SCE_DISPLAY_FRAMEBUF_FOR_COMPAT_FLAG_BILINEAR = 0x00100000
} SceDisplayFrameBufForCompatFlag;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayFrameBufForCompatFlag);

typedef struct SceDisplaySetFrameBufForCompatOpt {
	SceSize scaleY; //!< Vertical source-sampling step in unsigned 16.16 fixed-point format; 0x10000 selects 1:1 scaling.
	SceDisplayFrameBuf *pFrameBuf; //!< Optional; points to a ::SceDisplayFrameBufForCompat structure.
	SceDisplayCaptureFrameBuf *pCaptureFrameBuf; //!< Optional; NULL skips capture.
	SceSize frameBufSize; //!< Set to sizeof(SceDisplayFrameBufForCompat).
	SceSize captureFrameBufSize; //!< Number of bytes to copy from pCaptureFrameBuf; maximum 0x18.
	int reserved; //!< Unused on FW 3.60.
} SceDisplaySetFrameBufForCompatOpt;
VITASDK_BUILD_ASSERT_EQ(0x18, SceDisplaySetFrameBufForCompatOpt); // size is from FW 3.60

typedef struct SceDisplaySetFrameBufOpt {
	SceSize frameBufSize; //!< Set to sizeof(SceDisplayFrameBuf) for the declared input type; maximum 0x1C with a larger compatible buffer.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceDisplaySetFrameBufOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceDisplaySetFrameBufOpt); // size is from FW 3.60

typedef struct SceDisplaySetFrameBufInternalOpt {
	SceInt32 iUpdateTimingMode; //!< One of ::SceDisplayUpdateTiming.
	SceSize frameBufSize; //!< Set to sizeof(SceDisplayFrameBuf) for the declared input type; maximum 0x1C with a larger compatible buffer.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceDisplaySetFrameBufInternalOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceDisplaySetFrameBufInternalOpt); // size is from FW 3.60

/**
 * Get the current framebuffer.
 *
 * @param[out] pFrameBuf - Framebuffer information.
 * @param[in] sync - Value of type ::SceDisplaySetBufSync.
 * @param[in] pOpt - Pointer to a ::SceDisplayGetFrameBufOpt structure.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceDisplayGetFrameBuf(SceDisplayFrameBuf *pFrameBuf, SceDisplayFrameBufType sync, SceDisplayGetFrameBufOpt *pOpt);
int _sceDisplayGetFrameBufInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayFrameBuf *pFrameBuf, SceDisplayGetFrameBufInternalOpt *pOpt);
int _sceDisplayGetMaximumFrameBufResolution(SceUInt32 *width, SceUInt32 *height);
int _sceDisplayGetResolutionInfoInternal(SceDisplayHead head, SceDisplayResolutionInfo *pInfo, SceDisplayGetResolutionInfoInternalOpt *pOpt);

/**
 * @param[in] iUpdateTimingMode One of ::SceDisplayUpdateTiming.
 */
int _sceDisplaySetFrameBuf(const SceDisplayFrameBuf *pFrameBuf, SceInt32 iUpdateTimingMode, SceDisplaySetFrameBufOpt *pOpt);

/**
 * Set the compatibility framebuffer and its scaling parameters.
 *
 * @param[in] dstX - Destination X offset in pixels.
 * @param[in] dstY - Destination Y offset in pixels.
 * @param[in] scaleX - Horizontal source-sampling step in unsigned 16.16 fixed-point format.
 * @param[in] pOpt - Pointer to a ::SceDisplaySetFrameBufForCompatOpt structure.
 *
 * @return 0 on success, < 0 on error.
 * @note This export is available only to a PSP emulator process.
 */
int _sceDisplaySetFrameBufForCompat(int dstX, int dstY, int scaleX, SceDisplaySetFrameBufForCompatOpt *pOpt);

int _sceDisplaySetFrameBufInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx, const SceDisplayFrameBuf *pFrameBuf, SceDisplaySetFrameBufInternalOpt *pOpt);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_DISPLAY_H_ */
