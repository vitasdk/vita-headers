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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_DISPLAY_H_ */

