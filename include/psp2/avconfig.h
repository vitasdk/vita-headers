/**
 * \usergroup{SceAVConfig}
 * \usage{psp2/avconfig.h,SceAVConfig_stub}
 */


#ifndef _PSP2_AVCONFIG_H_
#define _PSP2_AVCONFIG_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Color Space Mode values to specify to ::sceAVConfigSetDisplayColorSpaceMode */
typedef enum SceAVConfigColorSpaceMode {
	SCE_AVCONFIG_COLOR_SPACE_MODE_DEFAULT           = 0, //!< Default
	SCE_AVCONFIG_COLOR_SPACE_MODE_HIGH_CONTRAST     = 1  //!< High Contrast Mode
} SceAVConfigColorSpaceMode;

/**
 * Get the maximum brightness.
 *
 * @param[out] maxBrightness - Maximum brightness.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 sceAVConfigGetDisplayMaxBrightness(SceInt32 *maxBrightness);

/**
 * Set the screen brightness.
 *
 * @param brightness - Brightness that the screen will be set to (range 21-65536, 0 turns off the screen).
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 sceAVConfigSetDisplayBrightness(SceUInt32 brightness);

/**
 * Get the shutter volume.
 *
 * @return Shutter vol
 */
SceInt32 sceAVConfigGetShutterVol(void);

/**
 * Get the system volume.
 *
 * @param[out] step - System volume.
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 sceAVConfigGetSystemVol(SceUInt32 *step);

/**
 * Set the system volume.
 *
 * @param step - volume that the device will be set to (range 0-30).
 *
 * @return 0 on success, < 0 on error.
 */
SceInt32 sceAVConfigSetSystemVol(SceUInt32 step);

/**
 * Turns on mute.
 *
 * @return 0 on success, < 0 on error.
 *
 */
SceInt32 sceAVConfigMuteOn(void);

/**
 * Sets the color space mode on runtime.
 *
 * @param[in] colorSpaceMode - see ::SceAVConfigColorSpaceMode()
 *
 * @return 0 on success, < 0 on error.
 * @note - This does not change color_space_mode in the registry.
 */
SceInt32 sceAVConfigSetDisplayColorSpaceMode(SceUInt32 colorSpaceMode);

SceInt32 sceAVConfigChangeReg(SceUInt32 reg_key, SceUInt32 value);
SceInt32 sceAVConfigClearAutoSuspend2(void);
SceInt32 sceAVConfigDisplayOn(void);
SceInt32 sceAVConfigGetAcStatus(SceUInt32 *status);
SceInt32 sceAVConfigGetBtVol(SceUInt32 *isChanged, SceUInt32 *step);
SceInt32 sceAVConfigGetConnectedAudioDevice(SceUInt32 *connectState);
SceInt32 sceAVConfigGetVolCtrlEnable(SceUInt32 *enable, SceUInt32 *isMute, SceUInt32 *isAvls);
SceInt32 sceAVConfigHdmiCecCmdOneTouchPlay(SceUInt32 mode);
SceInt32 sceAVConfigHdmiCecDisable(void);
SceInt32 sceAVConfigHdmiCecEnable(void);
SceInt32 sceAVConfigHdmiClearCecInfo(void);
SceInt32 sceAVConfigHdmiGetCecInfo(SceAVConfigCecInfo *info);
SceInt32 sceAVConfigHdmiGetMonitorInfo(SceAVConfigMonitorInfo *info);
SceInt32 sceAVConfigHdmiGetOutScalingRatio(SceAVConfigRatioOpt *opt);
SceInt32 sceAVConfigHdmiSetOutScalingRatio(const SceAVConfigRatioOpt *opt);
SceInt32 sceAVConfigHdmiSetResolution(SceInt32 resolution, SceInt32 forcedFlag);
SceInt32 sceAVConfigHdmiSetRgbRangeMode(SceInt32 rgbRangeMode);
SceInt32 sceAVConfigOledOn(void);
SceInt32 sceAVConfigRegisterCallback(SceUID cuid, SceUInt32 type);
SceInt32 sceAVConfigSendVolKey(SceUInt32 volKey);
SceInt32 sceAVConfigSetAutoDisplayDimming(SceUInt32 dimmingInterval);
SceInt32 sceAVConfigSetAutoSuspend(SceUInt32 suspendInterval);
SceInt32 sceAVConfigSetAutoSuspend2(SceUInt32 suspendInterval);
SceInt32 sceAVConfigUnRegisterCallback(void);
SceInt32 sceAVConfigWriteRegSystemVol(SceUInt32 step);

#ifdef __cplusplus
}
#endif

#endif

