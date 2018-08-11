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

/**
 * Get the maximum brightness.
 *
 * @param[out] maxBrightness - Maximum brightness.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetDisplayMaxBrightness(int *maxBrightness);

/**
 * Set the screen brightness.
 *
 * @param brightness - Brightness that the screen will be set to (range 21-65536, 0 turns off the screen).
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigSetDisplayBrightness(int brightness);

/**
 * Get the shutter volume.
 *
 * @param[out] volume - shutter volume.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetShutterVol(int *volume);

/**
 * Get the system volume.
 *
 * @param[out] volume - System volume.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetSystemVol(int *volume);

/**
 * Set the system volume.
 *
 * @param volume - volume that the device will be set to (range 0-30).
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigSetSystemVol(int volume);

/**
 * Turns on mute.
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAVConfigMuteOn(void);


#ifdef __cplusplus
}
#endif

#endif

