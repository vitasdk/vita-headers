/**
 * \file
 * \brief Header file which defines output audio related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_AUDIOOUT_H_
#define _PSP2_AUDIOOUT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_AUDIO_OUT_PARAM_FORMAT_S16_MONO		0
#define SCE_AUDIO_OUT_PARAM_FORMAT_S16_STEREO	1

enum {
	SCE_AUDIO_OUT_ERROR_NOT_OPENED		= 0x80260001,
	SCE_AUDIO_OUT_ERROR_BUSY		= 0x80260002,
	SCE_AUDIO_OUT_ERROR_INVALID_PORT	= 0x80260003,
	SCE_AUDIO_OUT_ERROR_INVALID_POINTER	= 0x80260004,
	SCE_AUDIO_OUT_ERROR_PORT_FULL		= 0x80260005,
	SCE_AUDIO_OUT_ERROR_INVALID_SIZE	= 0x80260006,
	SCE_AUDIO_OUT_ERROR_INVALID_FORMAT	= 0x80260007,
	SCE_AUDIO_OUT_ERROR_INVALID_SAMPLE_FREQ	= 0x80260008,
	SCE_AUDIO_OUT_ERROR_INVALID_VOLUME	= 0x80260009,
	SCE_AUDIO_OUT_ERROR_INVALID_PORT_TYPE	= 0x8026000A,
	SCE_AUDIO_OUT_ERROR_INVALID_FX_TYPE	= 0x8026000B,
	SCE_AUDIO_OUT_ERROR_INVALID_CONF_TYPE	= 0x8026000C,
	SCE_AUDIO_OUT_ERROR_OUT_OF_MEMORY	= 0x8026000D
};

enum {
	//! Used for main audio output, freq must be set to 48000 Hz
	SCE_AUDIO_OUT_PORT_TYPE_MAIN	= 0,

	//! Used for Background Music port
	SCE_AUDIO_OUT_PORT_TYPE_BGM	= 1,

	//! Used for voice chat port
	SCE_AUDIO_OUT_PORT_TYPE_VOICE	= 2
};

enum {
	SCE_AUDIO_OUT_MODE_MONO	= 0,
	SCE_AUDIO_OUT_MODE_STEREO	= 1
};

#define SCE_AUDIO_MIN_LEN 64		//!< Minimum granularity
#define SCE_AUDIO_MAX_LEN 65472	//!< Maximum granularity

/**
 * Initialize audio port
 *
 * @param[in] type - One of ::AudioOutPortType
 * @param[in] len - Number of samples, between ::SCE_AUDIO_MIN_LEN and ::SCE_AUDIO_MAX_LEN (multiple of 64)
 * @param[in] freq - Samping frequency (in Hz), one of the followings :
 * 8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000
 * @param[in] mode - One of ::AudioOutMode
 *
 * @return port number, < 0 on error.
 * @note - The volume is initially set to its max value (::SCE_AUDIO_OUT_MAX_VOL)
*/
int sceAudioOutOpenPort(int type, int len, int freq, int mode);

/**
 * Release an audio port
 *
 * @param[in] type - Port number returned by ::sceAudioOutOpenPort
 *
 * @return 0 on success, < 0 on error.
*/
int sceAudioOutReleasePort(int port);

/**
 * Output audio (blocking function)
 *
 * @param[in] port - Port number returned by ::sceAudioOutOpenPort
 * @param[in] *buf : Pointer to audio data buffer
 *
 * @return 0 on success, < 0 on error.
 * @note - if NULL is specified for *buf, the function will not return until the last
 * output audio data has been output.
 */
int sceAudioOutOutput(int port, const void *buf);

#define SCE_AUDIO_OUT_MAX_VOL 32768 					//!< Maximum output port volume
#define SCE_AUDIO_VOLUME_0DB  SCE_AUDIO_OUT_MAX_VOL	//!< Maximum output port volume

/** Flags to use as 'ch' argument for ::sceAudioOutSetVolume */
enum {
	SCE_AUDIO_VOLUME_FLAG_L_CH	= 0x1, //!< Left Channel
	SCE_AUDIO_VOLUME_FLAG_R_CH	= 0x2  //!< Right Channel
};

/**
 * Set volume of specified output audio port
 *
 * @param[in] port - Port number returned by ::sceAudioOutOpenPort
 * @param[in] ch - Channel numbers as flags (see ::AudioOutChannelFlag)
 * @param[in] *vol - Array to int specifying volume for each channel (Left channel first for stereo)
 *
 * @return 0 on success, < 0 on error.
 */
int sceAudioOutSetVolume(int port, int ch, int *vol);

/**
 * Change configuration of specified output port
 *
 * @param[in] port - Port number returned by ::sceAudioOutOpenPort
 * @param[in] len - see ::sceAudioOutOpenPort()
 * @param[in] freq - see ::sceAudioOutOpenPort()
 * @param[in] mode - see ::sceAudioOutOpenPort()
 *
 * @return 0 on success, < 0 on error.
 * @note - If (-1) is specified for any argument (excepted for port), current configuration is used instead.
 */
int sceAudioOutSetConfig(int port, int len, int freq, int mode);

/** Config type values to specify to ::sceAudioOutGetConfig */
enum {
	SCE_AUDIO_OUT_CONFIG_TYPE_LEN	= 0,
	SCE_AUDIO_OUT_CONFIG_TYPE_FREQ	= 1,
	SCE_AUDIO_OUT_CONFIG_TYPE_MODE	= 2
};

/**
 * Get a parameter value of specified output port
 *
 * @param[in] port - Port number returned by ::sceAudioOutOpenPort
 * @param[in] type - One of ::AudioOutConfigType
 *
 * @return 0 on success, < 0 on error.
 */
int sceAudioOutGetConfig(int port, int type);

/** Argument 'mode' to specify to ::sceAudioOutSetAlcMode */
enum {
	SCE_AUDIO_ALC_OFF	= 0,
	SCE_AUDIO_ALC_MODE1	= 1,
	SCE_AUDIO_ALC_MODE_MAX	= 2
};

/**
 * Set 'Automatic Level Control' mode on the BGM port
 * ALC is also known as 'Dynamic Normalizer'
 *
 * @param[in] mode - One of
 *
 * @return 0 on success, < 0 on error.
 */
int sceAudioOutSetAlcMode(int mode);

/**
 * Get the number of remaining samples to be output on the specified port
 *
 * @param[in] port - Port number returned by ::sceAudioOutOpenPort
 *
 * @return Number of samples on success, < 0 on error.
 */
int sceAudioOutGetRestSample(int port);

/**
 * Get status of port type
 * Return different value on whether the port type is used for sound generation or not.
 *
 * @param[in] type - One of ::AudioOutPortType
 *
 * @return (1) if port is in use, (0) otherwise. < 0 on error.
 */
int sceAudioOutGetAdopt(int type);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_AUDIOOUT_H_ */
