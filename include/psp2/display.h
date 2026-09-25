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
	SceDisplaySetBufSync update_timing_mode; //!< Framebuffer state to query.
	SceSize frame_buf_size; //!< Framebuffer structure size, or 0 when frame_buf is NULL.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceDisplayGetFrameBufInternalOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceDisplayGetFrameBufInternalOpt); // size is from FW 3.60

typedef struct SceDisplayGetFrameBufOpt {
	SceSize frame_buf_size; //!< Framebuffer structure size, or 0 when frame_buf is NULL.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceDisplayGetFrameBufOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceDisplayGetFrameBufOpt); // size is from FW 3.60

typedef struct SceDisplayGetResolutionInfoInternalOpt {
	SceSize info_size; //!< Set to sizeof(SceDisplayResolutionInfo).
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceDisplayGetResolutionInfoInternalOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceDisplayGetResolutionInfoInternalOpt); // size is from FW 3.60

typedef struct SceDisplayFrameBufForCompat {
	SceSize size; //!< Must be set to 0x1C.
	void *base; //!< Framebuffer base address; must be aligned to 0x100 bytes.
	unsigned int pitch; //!< Pitch in pixels; must be a multiple of 64 and at least width.
	unsigned int pixelformat; //!< FW 3.60 accepts 0x00000000 and 0x50000000.
	unsigned int width; //!< Visible width in pixels.
	unsigned int height; //!< Visible height in pixels.
	SceUInt32 flags; //!< Bitwise OR of ::SceDisplayFrameBufForCompatFlag values; only bit 20 is interpreted on FW 3.60.
} SceDisplayFrameBufForCompat;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceDisplayFrameBufForCompat); // size is from FW 3.60

typedef enum SceDisplayFrameBufForCompatFlag {
	SCE_DISPLAY_FRAMEBUF_FOR_COMPAT_FLAG_BILINEAR = 0x00100000
} SceDisplayFrameBufForCompatFlag;
VITASDK_BUILD_ASSERT_EQ(4, SceDisplayFrameBufForCompatFlag);

typedef struct SceDisplaySetFrameBufForCompatOpt {
	SceUInt32 scale_y; //!< Vertical source-sampling step in unsigned 16.16 fixed-point format; 0x10000 selects 1:1 scaling.
	const SceDisplayFrameBufForCompat *frame_buf; //!< Optional compatibility framebuffer; NULL disables scanout.
	const SceDisplayCaptureFrameBuf *capture_frame_buf; //!< Optional capture destination; ignored when frame_buf is NULL.
	SceSize frame_buf_size; //!< Set to sizeof(SceDisplayFrameBufForCompat), or 0 when frame_buf is NULL.
	SceSize capture_frame_buf_size; //!< Set to sizeof(SceDisplayCaptureFrameBuf), or 0 when capture_frame_buf is NULL.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceDisplaySetFrameBufForCompatOpt;
VITASDK_BUILD_ASSERT_EQ(0x18, SceDisplaySetFrameBufForCompatOpt); // size is from FW 3.60

typedef struct SceDisplaySetFrameBufOpt {
	SceSize frame_buf_size; //!< Framebuffer structure size, or 0 when frame_buf is NULL.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceDisplaySetFrameBufOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceDisplaySetFrameBufOpt); // size is from FW 3.60

typedef struct SceDisplaySetFrameBufInternalOpt {
	SceDisplaySetBufSync update_timing_mode; //!< Framebuffer update timing.
	SceSize frame_buf_size; //!< Framebuffer structure size, or 0 when frame_buf is NULL.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceDisplaySetFrameBufInternalOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceDisplaySetFrameBufInternalOpt); // size is from FW 3.60

/**
 * Get the current framebuffer.
 *
 * FW 3.60 accepts framebuffer structures of 0x18 and 0x1C bytes. The declared
 * ::SceDisplayFrameBuf receives the first 0x18 bytes. Both valid sync values
 * return the same current state on this firmware.
 *
 * @param[in,out] frame_buf - A 0x18-byte ::SceDisplayFrameBuf, or a 0x1C-byte
 *                            ::SceDisplayFrameBufExt cast to this pointer type.
 * @param[in] sync - One of ::SceDisplaySetBufSync.
 * @param[in] opt - Required option structure.
 *
 * @return 0 on success, or a negative error code.
 */
int _sceDisplayGetFrameBuf(SceDisplayFrameBuf *frame_buf, SceDisplaySetBufSync sync, const SceDisplayGetFrameBufOpt *opt);

/**
 * Get one framebuffer slot for a display head.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in,out] frame_buf - A 0x18-byte ::SceDisplayFrameBuf, or a 0x1C-byte
 *                            ::SceDisplayFrameBufExt cast to this pointer type.
 * @param[in] opt - Required option structure containing the framebuffer
 *                   structure size and update timing.
 *
 * @return 0 on success, or a negative error code.
 */
int _sceDisplayGetFrameBufInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayFrameBuf *frame_buf, const SceDisplayGetFrameBufInternalOpt *opt);

/**
 * Get the maximum framebuffer dimensions.
 *
 * @param[out] width - Receives the maximum width; may be NULL.
 * @param[out] height - Receives the maximum height; may be NULL.
 *
 * @return 0 on success, or a negative error code.
 */
int _sceDisplayGetMaximumFrameBufResolution(SceUInt32 *width, SceUInt32 *height);

/**
 * Get resolution, output-format, scan-mode, and refresh-rate information.
 *
 * @param[in] head - Display head.
 * @param[in,out] info - Receives the resolution information. Set its size
 *                        member to sizeof(SceDisplayResolutionInfo).
 * @param[in] opt - Required option structure.
 *
 * @return 0 on success, or a negative error code.
 */
int _sceDisplayGetResolutionInfoInternal(SceDisplayHead head, SceDisplayResolutionInfo *info, const SceDisplayGetResolutionInfoInternalOpt *opt);

/**
 * Set the calling process's framebuffer.
 *
 * @param[in] frame_buf - A 0x18-byte ::SceDisplayFrameBuf, a 0x1C-byte
 *                        ::SceDisplayFrameBufExt cast to this pointer type, or
 *                        NULL to disable scanout.
 * @param[in] sync - Framebuffer update timing.
 * @param[in] opt - Required option structure.
 *
 * @return 0 on success, or a negative error code.
 */
int _sceDisplaySetFrameBuf(const SceDisplayFrameBuf *frame_buf, SceDisplaySetBufSync sync, const SceDisplaySetFrameBufOpt *opt);

/**
 * Set the compatibility framebuffer and its scaling parameters.
 *
 * @param[in] dst_x - Destination X offset in pixels.
 * @param[in] dst_y - Destination Y offset in pixels.
 * @param[in] scale_x - Horizontal source-sampling step in unsigned 16.16 fixed-point format.
 * @param[in] opt - Required option structure. A capture destination must use
 *                   pixel format 0 and an address aligned to 0x100 bytes.
 *
 * @return 0 on success, or a negative error code.
 * @note This export is available only to a PSP emulator process.
 */
int _sceDisplaySetFrameBufForCompat(int dst_x, int dst_y, SceUInt32 scale_x, const SceDisplaySetFrameBufForCompatOpt *opt);

/**
 * Set one framebuffer slot for a display head.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in] frame_buf - A 0x18-byte ::SceDisplayFrameBuf, a 0x1C-byte
 *                        ::SceDisplayFrameBufExt cast to this pointer type, or
 *                        NULL to disable scanout.
 * @param[in] opt - Required option structure containing the framebuffer
 *                   structure size and update timing.
 *
 * @return 0 on success, or a negative error code.
 */
int _sceDisplaySetFrameBufInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx, const SceDisplayFrameBuf *frame_buf, const SceDisplaySetFrameBufInternalOpt *opt);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_DISPLAY_H_ */
