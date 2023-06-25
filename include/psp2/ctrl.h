/**
 * \usergroup{SceCtrl}
 * \usage{psp2/ctrl.h,SceCtrl_stub}
 */


#ifndef _PSP2_CTRL_H_
#define _PSP2_CTRL_H_

#include <vitasdk/build_utils.h>
#include <psp2common/ctrl.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the controller mode.
 *
 * @param[in] mode - One of ::SceCtrlPadInputMode.
 *
 * @return The previous mode, <0 on error.
 */
int sceCtrlSetSamplingMode(SceCtrlPadInputMode mode);

/**
 * Set the controller extend mode.
 *
 * @param[in] mode - One of ::SceCtrlPadInputMode.
 *
 * @return The previous mode, <0 on error.
 */
int sceCtrlSetSamplingModeExt(SceCtrlPadInputMode mode);

/**
 * Get the current controller mode.
 *
 * @param[out] pMode - Return value, see ::SceCtrlPadInputMode.
 *
 * @return The current mode, <0 on error.
 */
int sceCtrlGetSamplingMode(SceCtrlPadInputMode *pMode);

/**
 * Get the controller state information (polling, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (polling, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0 - 5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositive2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (polling, positive logic).
 *
 * This function will return button presses, even if they're intercepted by common dialog/IME.
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositiveExt(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (polling, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 * This function will return button presses, even if they're intercepted by common dialog/IME.
 *
 * @param[in] port - use 0 - 5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositiveExt2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (polling, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (polling, negative logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0-5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferNegative2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (blocking, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0-5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositive2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller extended state information (blocking, positive logic).
 *
 * This function will return button presses, even if they're intercepted by common dialog/IME.
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositiveExt(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller extended state information (blocking, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 * This function will return button presses, even if they're intercepted by common dialog/IME.
 *
 * @param[in] port - use 0-5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositiveExt2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Get the wireless controller state information (blocking, negative logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0-5.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count. Up to 64 buffers can be requested.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferNegative2(int port, SceCtrlData *pad_data, int count);

/**
 * Set rules for button rapid fire
 *
 * @param[in] port - use 0.
 * @param[in] idx - rule index between 0-15
 * @param[in] pRule - structure ::SceCtrlRapidFireRule.
 *
 * @return 0, <0 on error.
 */
int sceCtrlSetRapidFire(int port, int idx, const SceCtrlRapidFireRule* pRule);

/**
 * Clear rules for button rapid fire
 *
 * @param[in] port - use 0.
 * @param[in] idx - rule index between 0-15
 *
 * @return 0, <0 on error.
 */
int sceCtrlClearRapidFire(int port, int idx);

/**
 * Control the actuator (vibrate) on paired controllers.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[in] state - see ::SceCtrlActuator
 *
 * @return 0, <0 on error.
 */
int sceCtrlSetActuator(int port, const SceCtrlActuator* pState);

/**
 * Control the light bar on paired controllers.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[in] r - red intensity
 * @param[in] g - green intensity
 * @param[in] b - blue intensity
 *
 * @return 0, <0 on error.
 */
int sceCtrlSetLightBar(int port, SceUInt8 r, SceUInt8 g, SceUInt8 b);

/**
 * Get controller port information.
 *
 * @param[out] info - see ::SceCtrlPortInfo
 * @return 0, <0 on error
 */
int sceCtrlGetControllerPortInfo(SceCtrlPortInfo *info);

/**
 * Get controller battery information.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[out] batt - battery level, between 0-5, 0xEE charging, 0xEF charged
 *
 * @return 0, <0 on error.
 */
int sceCtrlGetBatteryInfo(int port, SceUInt8 *batt);

/**
 * Sets intercept
 *
 * If true, allows the current thread to intercept controls. The use case
 * might be, for example, a game plugin that wishes to capture input without
 * having the input sent to the game thread.
 * @param[in]  intercept  Boolean value
 *
 * @return 0, < 0 on error
 */
int sceCtrlSetButtonIntercept(int intercept);

/**
 * Gets intercept
 *
 * @param[out]  intercept  Boolean value
 *
 * @return 0, < 0 on error
 */
int sceCtrlGetButtonIntercept(int *intercept);

/**
 * Check if multi controller is supported
 *
 * @return 1 if yes, 0 if no
 */
int sceCtrlIsMultiControllerSupported(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_CTRL_H_ */
