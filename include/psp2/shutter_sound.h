/**
 * \usergroup{SceShutterSound}
 * \usage{psp2/shutter_sound.h,SceShutterSound_stub,SCE_SYSMODULE_SHUTTER_SOUND}
 */


#ifndef _PSP2_SHUTTER_SOUND_H_
#define _PSP2_SHUTTER_SOUND_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceShutterSoundErrorCode {
	SCE_SHUTTER_SOUND_ERROR_INVALID_ARGUMENT = 0x80105201, //!< Invalid argument
	SCE_SHUTTER_SOUND_ERROR_INTERNAL         = 0x80105202, //!< Internal error
	SCE_SHUTTER_SOUND_ERROR_FATAL            = 0x80105203  //!< Fatal error
} SceShutterSoundErrorCode;

typedef enum SceShutterSoundType {
	SCE_SHUTTER_SOUND_TYPE_SAVE_IMAGE       = 0,
	SCE_SHUTTER_SOUND_TYPE_SAVE_VIDEO_START = 1,
	SCE_SHUTTER_SOUND_TYPE_SAVE_VIDEO_END   = 2
} SceShutterSoundType;

/**
 * Plays a shutter sound
 *
 * @param[in] type - The sound type to play (One of ::SceShutterSoundType)
 *
 * @return 0 on success, < 0 on error.
*/
int sceShutterSoundPlay(uint32_t type);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SHUTTER_SOUND_H_ */

