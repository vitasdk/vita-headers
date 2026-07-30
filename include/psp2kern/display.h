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
	SceDisplayFrameBuf framebuf; //!< SceDisplayFrameBuf information
	unsigned int resolution;     //!< Resolution
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
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
} SceDisplayViewportConf;
VITASDK_BUILD_ASSERT_EQ(0x14, SceDisplayViewportConf); // size is from FW 3.60

SceInt32 ksceDisplayCaptureFrameBufDMAC(SceUID pid, SceDisplayCaptureFrameBuf *pCaptureFrameBuf);
SceInt32 ksceDisplayCaptureFrameBufDMACInternal(SceUID pid, SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayCaptureFrameBuf *pCaptureFrameBuf);
SceInt32 ksceDisplayCaptureFrameBufIFTU(SceUID pid, SceDisplayCaptureFrameBuf *pCaptureFrameBuf);
SceInt32 ksceDisplayCaptureFrameBufIFTUInternal(SceUID pid, SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayCaptureFrameBuf *pCaptureFrameBuf);
int ksceDisplayDisableHead(SceDisplayHead head);
int ksceDisplayEnableHead(SceDisplayHead head);
int ksceDisplayGetActualViewportConf(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayViewportConf *pViewportConf);
int ksceDisplayGetDeviceType(SceDisplayHead head, SceUInt32 *pDeviceType);
int ksceDisplayGetFrameBufInternal(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayFrameBuf *pFrameBuf, SceInt32 iUpdateTimingMode);
int ksceDisplayGetOutputMode(SceDisplayHead head, SceDisplayScreenMode *pScreenMode, SceDisplayPixelFormat *pPixelformat);
SceInt32 ksceDisplayGetRefreshRateInternal(SceDisplayHead head, float *pFps, SceDisplayScanMode *pScanMode);
int ksceDisplayGetResolutionInfoInternal(SceDisplayHead head, SceDisplayResolutionInfo *pInfo);
int ksceDisplaySetBrightness(SceDisplayHead head, SceUInt32 brightness);
int ksceDisplaySetColorSpaceMode(SceDisplayHead head, SceUInt32 mode);
int ksceDisplaySetMergeConf(SceDisplayHead head, int control, SceUInt32 alpha);
int ksceDisplaySetOutputMode(SceDisplayHead head, SceDisplayScreenMode screenMode, SceDisplayPixelFormat pixelformat);
int ksceDisplaySetScaleConf(float scale, SceDisplayHead head, SceDisplayFrameBufType fb_idx, int scaling);
int ksceDisplaySetViewportConf(SceDisplayHead head, SceDisplayFrameBufType fb_idx, SceDisplayViewportConf *pViewportConf);

/**
 * Wait for the next vertical blank start since the last update of the selected
 * framebuffer, processing callbacks while waiting.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceDisplayWaitSetFrameBufCBInternal(SceDisplayHead head, int fb_idx);

/**
 * Wait for the next vertical blank start since the last update of the selected
 * framebuffer.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceDisplayWaitSetFrameBufInternal(SceDisplayHead head, int fb_idx);

/**
 * Wait for vertical blank start after the specified number of vertical periods
 * since the last update of the selected framebuffer, processing callbacks while
 * waiting.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in] vcount - Number of vertical periods to wait, from 1 through 0xFFFF.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceDisplayWaitSetFrameBufMultiCBInternal(SceDisplayHead head, int fb_idx, SceUInt32 vcount);

/**
 * Wait for vertical blank start after the specified number of vertical periods
 * since the last update of the selected framebuffer.
 *
 * @param[in] head - Display head.
 * @param[in] fb_idx - One of ::SceDisplayFrameBufType.
 * @param[in] vcount - Number of vertical periods to wait, from 1 through 0xFFFF.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 ksceDisplayWaitSetFrameBufMultiInternal(SceDisplayHead head, int fb_idx, SceUInt32 vcount);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_DISPLAY_H_ */

