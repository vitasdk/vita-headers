/**
 * \kernelgroup{SceDisplay}
 * \usage{psp2kern/display.h,SceDisplayForDriver_stub}
 */


#ifndef _PSP2KERN_DISPLAY_H_
#define _PSP2KERN_DISPLAY_H_

#include <vitasdk/build_utils.h>
#include <psp2common/display.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Extended framebuffer information
*/
typedef struct SceDisplayFrameBufInfo {
	SceSize size;                //!< sizeof(SceDisplayFrameBufInfo)
	SceUID pid;                  //!< PID of the process owning this framebuffer
	unsigned int vblankcount;    //!< Amount of VBlanks this framebuffer has been displayed
	uintptr_t paddr;             //!< Physical address
	SceDisplayFrameBuf framebuf; //!< First 0x18 bytes of the framebuffer descriptor
	unsigned int resolution;     //!< Extended framebuffer flags; same value as ::SceDisplayFrameBufExt::flags
} SceDisplayFrameBufInfo;
VITASDK_BUILD_ASSERT_EQ(0x2C, SceDisplayFrameBufInfo);

/**
 * Set/Update framebuffer parameters
 *
 * @param[in] pParam - Pointer to a ::SceDisplayFrameBuf structure.
 * @param[in] sync - One of ::SceDisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as pParam pointer, output is blacked out.
*/
int ksceDisplaySetFrameBuf(const SceDisplayFrameBuf *pParam, int sync);

/**
 * Set/Update framebuffer parameters for display
 *
 * @param[in] head - Use 0 for OLED/LCD and 1 for HDMI
 * @param[in] index - Can be 0 or 1
 * @param[in] pParam - Pointer to a ::SceDisplayFrameBuf structure.
 * @param[in] sync - One of ::SceDisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as pParam pointer, output is blacked out.
*/
int ksceDisplaySetFrameBufInternal(int head, int index, const SceDisplayFrameBuf *pParam, int sync);

/**
 * Get current framebuffer parameters
 *
 * @param[out] pParam - Pointer to a ::SceDisplayFrameBuf structure
 * which will receive framebuffer parameters.
 * @warning FW 3.60 writes 0x1C bytes even when the size member is 0x18.
 *          Allocate a ::SceDisplayFrameBufExt object and cast its address to
 *          ::SceDisplayFrameBuf * when calling this backwards-compatible prototype.
 *
 * @param[in] sync - One of ::SceDisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
*/
int ksceDisplayGetFrameBuf(SceDisplayFrameBuf *pParam, int sync);

/**
 * Get the configured framebuffer information of a head and its framebuffer index for a PID
 *
 * @param[in] pid - PID of the process to get the framebuffer information from.
 *                  It can either be a vallid PID, -1 to use the current configured
 *                  framebuffer for the head and index, or 0 to use the PID of the caller.
 * @param[in] head - Use 0 for OLED/LCD and 1 for HDMI
 * @param[in] index - Can be 0 or 1
 * @param[out] info - Pointer to a ::SceDisplayFrameBufInfo structure
 * which will receive the framebuffer information.
 *
 * @return 0 on success, < 0 on error.
*/
int ksceDisplayGetProcFrameBufInternal(SceUID pid, int head, int index, SceDisplayFrameBufInfo *info);

/**
 * Get maximum framebuffer resolution
 *
 * @param[out] width - Maximum width
 * @param[out] height - Maximum height
 *
 * @return 0 on success, < 0 on error.
*/
int ksceDisplayGetMaximumFrameBufResolution(int *width, int *height);

/**
 * Primary display index
 */
int ksceDisplayGetPrimaryHead(void);

/**
 * Number of vertical blank pulses up to now for a display
 *
 * @param[in] display - Display index
 */
int ksceDisplayGetVcountInternal(int display);

/**
 * Wait for vertical blank start
 */
int ksceDisplayWaitVblankStart(void);

/**
 * Wait for vertical blank start for display
 *
 * @param[in] display - Display index
 */
int ksceDisplayWaitVblankStartInternal(int display);

/**
 * Wait for vertical blank start with callback
 */
int ksceDisplayWaitVblankStartCB(void);

/**
 * Wait for vertical blank start with callback for display
 *
 * @param[in] display - Display index
 */
int ksceDisplayWaitVblankStartCBInternal(int display);

/**
 * Wait for vertical blank start after specified number of vertical periods
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int ksceDisplayWaitVblankStartMulti(unsigned int vcount);

/**
 * Wait for vertical blank start after specified number of vertical periods for display
 *
 * @param[in] display - Display index
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int ksceDisplayWaitVblankStartMultiInternal(int display, unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int ksceDisplayWaitVblankStartMultiCB(unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods for display
 *
 * @param[in] display - Display index
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int ksceDisplayWaitVblankStartMultiCBInternal(int display, unsigned int vcount);

/**
 * Wait for vertical blank start since last update of framebuffer
 */
int ksceDisplayWaitSetFrameBuf(void);

/**
 * Wait for vertical blank start with callback since last update of framebuffer
 */
int ksceDisplayWaitSetFrameBufCB(void);

/**
 * Wait for vertical blank start after specified number of vertical periods
 * since last update of framebuffer.
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int ksceDisplayWaitSetFrameBufMulti(unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods
 * since last update of framebuffer.
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int ksceDisplayWaitSetFrameBufMultiCB(unsigned int vcount);

/**
 * Register callback to be used at each vertical blank start
 *
 * @param[in] uid - Callback UID
 */
int ksceDisplayRegisterVblankStartCallback(SceUID uid);

/**
 * Register callback to be used at each vertical blank start for a display
 *
 * @param[in] display - Display index
 * @param[in] uid - Callback UID
 */
int ksceDisplayRegisterVblankStartCallbackInternal(int display, SceUID uid);

/**
 * Unregister callback used at each vertical blank start
 *
 * @param[in] uid - Callback UID
 */
int ksceDisplayUnregisterVblankStartCallback(SceUID uid);

/**
 * Unregister callback used at each vertical blank start for a display
 *
 * @param[in] display - Display index
 * @param[in] uid - Callback UID
 */
int ksceDisplayUnregisterVblankStartCallbackInternal(int display, SceUID uid);

/**
 * Register callback to be used when the framebuffer changes
 *
 * @param[in] uid - Callback UID
 */
int ksceDisplayRegisterFrameBufCallback(SceUID uid);

/**
 * Register callback to be used when the framebuffer changes for a display
 *
 * @param[in] display - Display index
 * @param[in] uid - Callback UID
 */
int ksceDisplayRegisterFrameBufCallbackInternal(int display, SceUID uid);

/**
 * Enable/disable color inversion for a display.
 *
 * @param[in] display - Display index
 * @param[in] enable - Enable/disable color inversion
 */
int ksceDisplaySetInvertColors(int display, int enable);

/**
 * Set display plane owner
 *
 * @param[in] head - Use 0 for OLED/LCD and 1 for HDMI
 * @param[in] index - Can be 0 or 1
 * @param[in] pid - PID of the new owner
 *
 * @return 0 on success, < 0 on error.
*/
int ksceDisplaySetOwner(int head, int index, SceUID pid);

typedef struct SceDisplayViewportConf {
	SceSize size; //!< Must be set to 0x14.
	unsigned int x; //!< Horizontal viewport offset in pixels.
	unsigned int y; //!< Vertical viewport offset in pixels.
	unsigned int width; //!< Viewport width in pixels.
	unsigned int height; //!< Viewport height in pixels.
} SceDisplayViewportConf;
VITASDK_BUILD_ASSERT_EQ(0x14, SceDisplayViewportConf); // size is from FW 3.60

/** Non-negative device types returned by ::ksceDisplayGetDeviceType. */
typedef enum SceDisplayDeviceType {
	SCE_DISPLAY_DEVICE_TYPE_NONE = 0,
	SCE_DISPLAY_DEVICE_TYPE_OLED = 1,
	SCE_DISPLAY_DEVICE_TYPE_LCD  = 2,
	SCE_DISPLAY_DEVICE_TYPE_HDMI = 3
} SceDisplayDeviceType;
VITASDK_BUILD_ASSERT_EQ(1, SceDisplayDeviceType);

/** Device-dependent values accepted by ::ksceDisplaySetColorSpaceMode. */
typedef enum SceDisplayColorSpaceMode {
	SCE_DISPLAY_COLOR_SPACE_MODE_0 = 0, //!< Selects panel-driver mode 0 on OLED and LCD.
	SCE_DISPLAY_COLOR_SPACE_MODE_1 = 1, //!< Selects panel-driver mode 1 on OLED and mode 0 on LCD.
	SCE_DISPLAY_COLOR_SPACE_MODE_2 = 2  //!< Selects panel-driver mode 1 on LCD; rejected by OLED.
} SceDisplayColorSpaceMode;
VITASDK_BUILD_ASSERT_EQ(1, SceDisplayColorSpaceMode);

/**
 * Capture the current process's primary GAME_APP framebuffer through DMAC.
 *
 * The destination address must be aligned to 0x100 bytes. Pitch must be a
 * multiple of 64 pixels and at least the requested width. On success, FW 3.60
 * replaces the structure's width, height, and pixel format with the actual
 * copied source values.
 *
 * @param[in] pid - Source process ID, or 0 for the calling process.
 * @param[in,out] capture_frame_buf - Capture destination and resulting format.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 ksceDisplayCaptureFrameBufDMAC(SceUID pid, SceDisplayCaptureFrameBuf *capture_frame_buf);

/**
 * Capture a selected process framebuffer through DMAC.
 *
 * @param[in] pid - Source process ID, or 0 for the calling process.
 * @param[in] head - Main or HDMI display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in,out] capture_frame_buf - Capture destination and resulting format.
 *                                   The same rules apply as for
 *                                   ::ksceDisplayCaptureFrameBufDMAC.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 ksceDisplayCaptureFrameBufDMACInternal(SceUID pid, SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayCaptureFrameBuf *capture_frame_buf);

/**
 * Convert and capture the current process's primary GAME_APP framebuffer
 * through IFTU.
 *
 * The destination address must be aligned to 0x100 bytes. FW 3.60 accepts pixel
 * format values 0x00000000, 0x00008000, 0x00100000, 0x00108000, 0x60800000,
 * 0x60808000, 0x60900000, and 0x60908000. The destination buffer must contain
 * at least pitch * height * 4 bytes.
 *
 * @param[in] pid - Source process ID, or 0 for the calling process.
 * @param[in] capture_frame_buf - Capture destination description.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 ksceDisplayCaptureFrameBufIFTU(SceUID pid, const SceDisplayCaptureFrameBuf *capture_frame_buf);

/**
 * Convert and capture a selected process framebuffer through IFTU.
 *
 * @param[in] pid - Source process ID, or 0 for the calling process.
 * @param[in] head - Main or HDMI display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in] capture_frame_buf - Capture destination description. The same
 *                               rules apply as for
 *                               ::ksceDisplayCaptureFrameBufIFTU.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 ksceDisplayCaptureFrameBufIFTUInternal(SceUID pid, SceDisplayHead head, SceDisplayFrameBufType fb_idx, const SceDisplayCaptureFrameBuf *capture_frame_buf);

/**
 * Disable a display head.
 *
 * @param[in] head - Main or HDMI display head.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplayDisableHead(SceDisplayHead head);

/**
 * Enable a display head.
 *
 * @param[in] head - Main or HDMI display head.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplayEnableHead(SceDisplayHead head);

/**
 * Get the effective viewport for a framebuffer slot.
 *
 * The output must be non-NULL with its size member set to 0x14. FW 3.60
 * returns zero for x, y, width, and height when the slot has no owner or
 * active framebuffer.
 *
 * @param[in] head - Main or HDMI display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in,out] viewport_conf - Receives the viewport; set its size member first.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplayGetActualViewportConf(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayViewportConf *viewport_conf);

/**
 * Get the hardware type for a display head.
 *
 * On FW 3.60, OLED returns 1 and writes 0x103, LCD returns 2 and writes 0x101,
 * HDMI returns 3 and writes 0x101, and an absent device returns 0 and writes 0.
 * The output pointer is optional.
 *
 * @param[in] head - Display head.
 * @param[out] device_info - Optional device-information output.
 *
 * @return One of ::SceDisplayDeviceType, or a negative error code.
 */
int ksceDisplayGetDeviceType(SceDisplayHead head, SceUInt32 *device_info);

/**
 * Get one current process framebuffer slot.
 *
 * FW 3.60 always writes 0x1C bytes. Although the size member may be 0x18 or
 * 0x1C, callers must provide storage for the complete extended framebuffer
 * structure.
 *
 * @param[in] head - Main or HDMI display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in,out] frame_buf - Receives the extended framebuffer information;
 *                            set its size member first.
 * @param[in] update_timing_mode - One of ::SceDisplaySetBufSync. FW 3.60
 *                                validates but otherwise ignores this value.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplayGetFrameBufInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayFrameBufExt *frame_buf, SceDisplaySetBufSync update_timing_mode);

/**
 * Get the configured screen-mode ID and output-format value for a head.
 *
 * @param[in] head - Display head.
 * @param[out] screen_mode - Optional complete screen-mode ID output.
 * @param[out] output_format - Optional pixel-format/RGB-range output.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplayGetOutputMode(SceDisplayHead head, SceDisplayScreenMode *screen_mode, SceUInt32 *output_format);

/**
 * Get a head's theoretical refresh rate and scan mode.
 *
 * Either output pointer may be NULL. The scan-mode output is a 32-bit value
 * containing one of ::SceDisplayScanMode. FW 3.60 reports approximately
 * 59.940056 through \a fps for every configured screen mode; this value is
 * not calculated from the selected DSI timing.
 *
 * @param[in] head - Display head.
 * @param[out] fps - Optional stored refresh-rate output.
 * @param[out] scan_mode - Optional 32-bit scan-mode output.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 ksceDisplayGetRefreshRateInternal(SceDisplayHead head, float *fps, SceUInt32 *scan_mode);

/**
 * Get complete resolution and output-mode information for a head.
 *
 * @param[in] head - Display head.
 * @param[in,out] info - Receives the information; set its size member to 0x1C.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplayGetResolutionInfoInternal(SceDisplayHead head, SceDisplayResolutionInfo *info);

/**
 * Set display brightness.
 *
 * For the main panel, values from 0 through 0x10000 are passed to the active
 * OLED or LCD driver. For HDMI, zero remains zero, one becomes 0x8000, and
 * values from two through 0x10000 become `0x8000 + (brightness >> 1)` before
 * being applied to the IFTU color-conversion matrices.
 *
 * @param[in] head - Main or HDMI display head.
 * @param[in] brightness - Brightness value from zero through 0x10000.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplaySetBrightness(SceDisplayHead head, SceUInt32 brightness);

/**
 * Set the main panel's device-dependent color-space mode.
 *
 * @param[in] head - Must be ::SCE_DISPLAY_HEAD_MAIN_LCD_OLED.
 * @param[in] mode - One of ::SceDisplayColorSpaceMode.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplaySetColorSpaceMode(SceDisplayHead head, SceUInt32 mode);

/**
 * Configure overlay-plane blending for a head.
 *
 * The control value is passed unchanged to IFTU. Value 0x80 disables
 * blending; every other value enables blending. FW 3.60 performs no other
 * validation of this value.
 *
 * @param[in] head - Main or HDMI display head.
 * @param[in] control - Raw IFTU merge-control value.
 * @param[in] alpha - Overlay alpha from 0 through 0x100.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplaySetMergeConf(SceDisplayHead head, int control, SceUInt32 alpha);

/**
 * Set a head's complete screen-mode ID and output-format value.
 *
 * The output-format value combines a pixel-format encoding with RGB-range bit
 * 0 where supported. For the main head, FW 3.60 accepts values 0x00000000,
 * 0x00100000, 0x60800000, and 0x60900000. For HDMI it additionally accepts
 * values 0x00000001, 0x00008000, 0x00100001, 0x00108000, 0x60800001,
 * 0x60808000, 0x60900001, and 0x60908000.
 *
 * @param[in] head - Main or HDMI display head.
 * @param[in] screen_mode - One of ::SceDisplayScreenModeId. Use these IDs as
 *                         listed; do not combine them as flags.
 * @param[in] output_format - Combined pixel-format and RGB-range encoding.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplaySetOutputMode(SceDisplayHead head, SceDisplayScreenMode screen_mode, SceUInt32 output_format);

/**
 * Set scaling for a display head's framebuffer slot.
 *
 * On FW 3.60, \a scale must be 0 when bit 0 of \a scaling is clear. When bit
 * 0 is set, bits 6 and 7 must be clear and \a scale must be between 0.8 and
 * 1.2, inclusive. Observed callers also use \a scaling values 0x40 and 0x80
 * with a zero scale.
 *
 * @param[in] scale - Per-slot scale factor.
 * @param[in] head - Main or HDMI display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in] scaling - Scaling-control bits described above.
 *
 * @note Under the ARM hard-float ABI, \a scale is passed in S0 while the
 *       remaining arguments are passed in R0 through R2.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplaySetScaleConf(float scale, SceDisplayHead head, SceDisplayFrameBufType fb_idx, int scaling);

/**
 * Set viewport scaling for a framebuffer slot.
 *
 * NULL, or x = 0, y = 0, width = 960, and height = 544, selects the default
 * full viewport. A non-NULL structure must have its size member set to 0x14;
 * FW 3.60 rejects x values above 640 and y values above 364.
 *
 * @param[in] head - Main or HDMI display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in] viewport_conf - Viewport configuration, or NULL for the default.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceDisplaySetViewportConf(SceDisplayHead head, SceDisplayFrameBufType fb_idx, const SceDisplayViewportConf *viewport_conf);

/**
 * Wait for the next vertical blank start since the last update of the selected
 * framebuffer, processing callbacks while waiting.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - Framebuffer slot. FW 3.60 uses only the low bit.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceDisplayWaitSetFrameBufCBInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx);

/**
 * Wait for the next vertical blank start since the last update of the selected
 * framebuffer.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - Framebuffer slot. FW 3.60 uses only the low bit.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceDisplayWaitSetFrameBufInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx);

/**
 * Wait for vertical blank start after the specified number of vertical periods
 * since the last update of the selected framebuffer, processing callbacks while
 * waiting.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - Framebuffer slot. FW 3.60 uses only the low bit.
 * @param[in] vcount - Number of vertical periods to wait, from 1 through 0xFFFF.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceDisplayWaitSetFrameBufMultiCBInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceUInt32 vcount);

/**
 * Wait for vertical blank start after the specified number of vertical periods
 * since the last update of the selected framebuffer.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - Framebuffer slot. FW 3.60 uses only the low bit.
 * @param[in] vcount - Number of vertical periods to wait, from 1 through 0xFFFF.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceDisplayWaitSetFrameBufMultiInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceUInt32 vcount);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_DISPLAY_H_ */
