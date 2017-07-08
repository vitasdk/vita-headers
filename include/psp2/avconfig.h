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

/***
 * Get the maximum brightness.
 *
 * @param[out] maxBrightness - Maximum brightness.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetDisplayMaxBrightness(int *maxBrightness);

/***
 * Set the screen brightness.
 *
 * @param brightness - Brightness that the screen will be set to (range 21-65536, 0 turns off the screen).
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigSetDisplayBrightness(int brightness);


#ifdef __cplusplus
}
#endif

#endif

