/**
 * \kernelgroup{SceCtrl}
 * \usage{psp2kern/ctrl.h,SceCtrlForDriver_stub}
 */


#ifndef _PSP2KERN_CTRL_H_
#define _PSP2KERN_CTRL_H_

#include <vitasdk/build_utils.h>
#include <psp2common/ctrl.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Structure to pass as argument to ::ksceCtrlRegisterVirtualControllerDriver */
typedef struct SceCtrlVirtualControllerDriver {
	int (*readButtons)(int port, SceCtrlData *pad_data, int count);
	int (*setActuator)(int port, const SceCtrlActuator* pState);
	int (*getBatteryInfo)(int port, SceUInt8 *batt);
	int (*disconnect)(int port);
	int (*setTurnOffInterval)(int port);
	int (*getActiveControllerPort)(void);
	int (*changePortAssign)(int port1, int port2);
	int (*unk0)(void);
	int (*getControllerPortInfo)(SceCtrlPortInfo *info);
	int (*setLightBar)(int port, SceUInt8 r, SceUInt8 g, SceUInt8 b);
	int (*resetLightBar)(int port);
	int (*unk1)(int port);
	int (*singleControllerMode)(int port);
} SceCtrlVirtualControllerDriver;
VITASDK_BUILD_ASSERT_EQ(0x34, SceCtrlVirtualControllerDriver);

/**
 * Set the controller mode.
 *
 * @param[in] mode - One of ::SceCtrlPadInputMode.
 *
 * @return The previous mode, <0 on error.
 */
int ksceCtrlSetSamplingMode(int mode);

/**
 * Get the current controller mode.
 *
 * @param[out] pMode - Return value, see ::SceCtrlPadInputMode.
 *
 * @return The current mode, <0 on error.
 */
int ksceCtrlGetSamplingMode(int *pMode);

/**
 * Get the controller state information (polling, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int ksceCtrlPeekBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (polling, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int ksceCtrlPeekBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, positive logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int ksceCtrlReadBufferPositive(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller state information (blocking, negative logic).
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int ksceCtrlReadBufferNegative(int port, SceCtrlData *pad_data, int count);

/**
 * Set rules for button rapid fire
 *
 * @param[in] port - use 0.
 * @param[in] idx - rule index between 0-15
 * @param[in] pRule - structure ::SceCtrlRapidFireRule.
 *
 * @return 0, <0 on error.
 */
int ksceCtrlSetRapidFire(int port, int idx, const SceCtrlRapidFireRule* pRule);

/**
 * Clear rules for button rapid fire
 *
 * @param[in] port - use 0.
 * @param[in] idx - rule index between 0-15
 *
 * @return 0, <0 on error.
 */
int ksceCtrlClearRapidFire(int port, int idx);

/**
 * Get controller port information.
 *
 * @param[out] info - see ::SceCtrlPortInfo
 * @return 0, <0 on error
 */
int ksceCtrlGetControllerPortInfo(SceCtrlPortInfo *info);

/**
 * Sets intercept
 *
 * If true, allows the current thread to intercept controls. The use case
 * might be, for example, a game plugin that wishes to capture input without
 * having the input sent to the game thread.
 * @param[in]  intercept  Boolean value
 *
 * @return     0, < 0 on error
 */
int ksceCtrlSetButtonIntercept(int intercept);

/**
 * Gets intercept
 *
 * @param[out]  intercept  Boolean value
 *
 * @return     0, < 0 on error
 */
int ksceCtrlGetButtonIntercept(int *intercept);

/**
 * Emulate buttons for the digital pad.
 * @param port Use 0
 * @param slot The slot used to set the custom values. Between 0 - 3. If multiple slots are used,
 *             their settings are combined.
 * @param userButtons Emulated user buttons of ::SceCtrlButtons. You cannot emulate kernel
 *                    buttons and the emulated buttons will only be applied for applications
 *                    running in user mode.
 * @param kernelButtons Emulated buttons of ::SceCtrlButtons (you can emulate both user and
 *                      kernel buttons). The emulated buttons will only be applied for applications
 *                      running in kernel mode.
 * @param uiMake Specifies the duration of the emulation. Measured in sampling counts.
 *
 * @return 0 on success.
 */
int ksceCtrlSetButtonEmulation(unsigned int port, unsigned char slot,
			       unsigned int userButtons, unsigned int kernelButtons,
			       unsigned int uiMake);

/**
 * Emulate values for the analog pad's X- and Y-axis.
 *
 * @param port Use 0
 * @param slot The slot used to set the custom values. Between 0 - 3. If multiple slots are used,
 *             their settings are combined.
 * @param user_lX New emulated value for the left joystick's X-axis (userspace). Between 0 - 0xFF.
 * @param user_lY New emulate value for the left joystick's Y-axis (userspace). Between 0 - 0xFF.
 * @param user_rX New emulated value for the right joystick's X-axis (userspace). Between 0 - 0xFF.
 * @param user_rY New emulate value for the right joystick's Y-axis (userspace). Between 0 - 0xFF.
 * @param kernel_lX New emulated value for the left joystick's X-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_lY New emulate value for the left joystick's Y-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_rX New emulated value for the right joystick's X-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_rY New emulate value for the right joystick's Y-axis (kernelspace). Between 0 - 0xFF.
 * @param uiMake Specifies the duration of the emulation. Measured in sampling counts.
 *
 * @return 0 on success.
 */
int ksceCtrlSetAnalogEmulation(unsigned int port, unsigned char slot,
			      unsigned char user_lX, unsigned char user_lY,
			      unsigned char user_rX, unsigned char user_rY,
			      unsigned char kernel_lX, unsigned char kernel_lY,
			      unsigned char kernel_rX, unsigned char kernel_rY,
			      unsigned int uiMake);

/**
 * Register virtual controller driver.
 *
 * This function always overwrites global settings and not exist unregister method.
 *
 * @param[in] driver - See ::SceCtrlVirtualControllerDriver
 *
 * @return 0 on success. <0 on error
 */
int ksceCtrlRegisterVirtualControllerDriver(SceCtrlVirtualControllerDriver *driver);

/**
 * Update ctrl mask for non shell process
 *
 * @param[in] clear_mask - The SceCtrlButtons type value
 * @param[in] set_mask   - The SceCtrlButtons type value
 *
 * @return always 0.
 *
 * note - Some values cannot be clear/set.
 */
int ksceCtrlUpdateMaskForNonShell(int clear_mask, int set_mask);

/**
 * Update ctrl mask for all process
 *
 * @param[in] clear_mask - The SceCtrlButtons type value
 * @param[in] set_mask   - The SceCtrlButtons type value
 *
 * @return always 0.
 *
 * note - Some values cannot be clear/set.
 */
int ksceCtrlUpdateMaskForAll(int clear_mask, int set_mask);

/**
 * Get ctrl mask for non shell process
 *
 * @param[out] mask - The pointer of SceCtrlButtons type value output
 *
 * @return 0 on success. < 0 on error.
 */
int ksceCtrlGetMaskForNonShell(uint32_t *mask);

/**
 * Get ctrl mask for all process
 *
 * @param[out] mask - The pointer of SceCtrlButtons type value output
 *
 * @return 0 on success. < 0 on error.
 */
int ksceCtrlGetMaskForAll(uint32_t *mask);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_CTRL_H_ */
