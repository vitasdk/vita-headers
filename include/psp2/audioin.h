/**
 * \usergroup{SceAudioIn}
 * \usage{psp2/audioin.h,SceAudioIn_stub}
 */


#ifndef _PSP2_AUDIOIN_H_
#define _PSP2_AUDIOIN_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAudioInErrorCode {
	//! Undefined error
	SCE_AUDIO_IN_ERROR_FATAL                = 0x80260100,
	//! Bad value of port number
	SCE_AUDIO_IN_ERROR_INVALID_PORT         = 0x80260101,
	//! Invalid sample length
	SCE_AUDIO_IN_ERROR_INVALID_SIZE         = 0x80260102,
	//! Invalid sample frequency
	SCE_AUDIO_IN_ERROR_INVALID_SAMPLE_FREQ  = 0x80260103,
	//! Invalid port type
	SCE_AUDIO_IN_ERROR_INVALID_PORT_TYPE    = 0x80260104,
	//! Invalid pointer value
	SCE_AUDIO_IN_ERROR_INVALID_POINTER      = 0x80260105,
	//! Invalid port param
	SCE_AUDIO_IN_ERROR_INVALID_PORT_PARAM   = 0x80260106,
	//! Cannot open no ports
	SCE_AUDIO_IN_ERROR_PORT_FULL            = 0x80260107,
	//! Not enough memory
	SCE_AUDIO_IN_ERROR_OUT_OF_MEMORY        = 0x80260108,
	//! Port is not opened
	SCE_AUDIO_IN_ERROR_NOT_OPENED           = 0x80260109,
	//! Tried to input while busy
	SCE_AUDIO_IN_ERROR_BUSY                 = 0x8026010A,
	//! Invalid parameter
	SCE_AUDIO_IN_ERROR_INVALID_PARAMETER    = 0x8026010B
} SceAudioInErrorCode;

typedef enum SceAudioInPortType {
	SCE_AUDIO_IN_PORT_TYPE_VOICE   = 0,
	SCE_AUDIO_IN_PORT_TYPE_RAW     = 2
} SceAudioInPortType;

typedef enum SceAudioInParam {
	SCE_AUDIO_IN_PARAM_FORMAT_S16_MONO  = 0,
	SCE_AUDIO_IN_GETSTATUS_MUTE         = 1
} SceAudioInParam;

//! Open port
int sceAudioInOpenPort(SceAudioInPortType portType, int grain, int freq, SceAudioInParam param);

//! Close port
int sceAudioInReleasePort(int port);

int sceAudioInInput(int port, void *destPtr);

/* get status */
int sceAudioInGetAdopt(SceAudioInPortType portType);
int sceAudioInGetStatus(int select);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_AUDIOIN_H_ */

