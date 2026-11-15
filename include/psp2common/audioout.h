/**
 * \usergroup{SceAudio}
 * \usage{psp2common/audioout.h}
 */

#ifndef _PSP2COMMON_AUDIOOUT_H_
#define _PSP2COMMON_AUDIOOUT_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAudioOutErrorCode {
	SCE_AUDIO_OUT_ERROR_NOT_OPENED          = 0x80260001,
	SCE_AUDIO_OUT_ERROR_BUSY                = 0x80260002,
	SCE_AUDIO_OUT_ERROR_INVALID_PORT        = 0x80260003,
	SCE_AUDIO_OUT_ERROR_INVALID_POINTER     = 0x80260004,
	SCE_AUDIO_OUT_ERROR_PORT_FULL           = 0x80260005,
	SCE_AUDIO_OUT_ERROR_INVALID_SIZE        = 0x80260006,
	SCE_AUDIO_OUT_ERROR_INVALID_FORMAT      = 0x80260007,
	SCE_AUDIO_OUT_ERROR_INVALID_SAMPLE_FREQ = 0x80260008,
	SCE_AUDIO_OUT_ERROR_INVALID_VOLUME      = 0x80260009,
	SCE_AUDIO_OUT_ERROR_INVALID_PORT_TYPE   = 0x8026000A,
	SCE_AUDIO_OUT_ERROR_INVALID_FX_TYPE     = 0x8026000B,
	SCE_AUDIO_OUT_ERROR_INVALID_CONF_TYPE   = 0x8026000C,
	SCE_AUDIO_OUT_ERROR_OUT_OF_MEMORY       = 0x8026000D
} SceAudioOutErrorCode;

/**
 * Legacy signed 16-bit PCM format names.
 *
 * Prefer ::SceAudioOutMode for new declarations.
 */
typedef enum SceAudioOutParam {
	SCE_AUDIO_OUT_PARAM_FORMAT_S16_MONO   = 0,
	SCE_AUDIO_OUT_PARAM_FORMAT_S16_STEREO = 1
} SceAudioOutParam;

typedef enum SceAudioOutPortType {
	SCE_AUDIO_OUT_PORT_TYPE_MAIN             = 0, //!< Main output; use ::SCE_AUDIO_OUT_SAMPLE_RATE_48000.
	SCE_AUDIO_OUT_PORT_TYPE_BGM              = 1, //!< Background-music output.
	SCE_AUDIO_OUT_PORT_TYPE_VOICE            = 2, //!< Voice-chat output.
	SCE_AUDIO_OUT_PORT_TYPE_VOICE_COMPRESSED = 3  //!< Compressed voice; non-game processes only on FW 3.60.
} SceAudioOutPortType;

typedef enum SceAudioOutMode {
	SCE_AUDIO_OUT_MODE_MONO   = 0,
	SCE_AUDIO_OUT_MODE_STEREO = 1
} SceAudioOutMode;

/**
 * BGM seven-band graphic-equalizer presets.
 *
 * The gains below apply to the 63 Hz, 160 Hz, 400 Hz, 1 kHz, 2.5 kHz, 6.3 kHz,
 * and 16 kHz bands, in that order.
 */
typedef enum SceAudioOutEffectType {
	SCE_AUDIO_OUT_EFFECT_TYPE_OFF    = 0, //!< Bypasses the equalizer; the stored preset uses 0 dB for every band.
	SCE_AUDIO_OUT_EFFECT_TYPE_HEAVY  = 1, //!< +3, +3, 0, -3, +3, +3, 0 dB.
	SCE_AUDIO_OUT_EFFECT_TYPE_POPS   = 2, //!< -3, 0, +3, +3, 0, 0, -3 dB.
	SCE_AUDIO_OUT_EFFECT_TYPE_JAZZ   = 3, //!< 0, +6, 0, 0, -3, 0, +3 dB.
	SCE_AUDIO_OUT_EFFECT_TYPE_UNIQUE = 4  //!< +6, 0, 0, +3, 0, -3, +6 dB.
} SceAudioOutEffectType;

/**
 * Audio-output sample rates.
 *
 * Each AudioOut function accepts only the rates documented for that function.
 */
typedef enum SceAudioOutSampleRate {
	SCE_AUDIO_OUT_SAMPLE_RATE_8000  = 8000,
	SCE_AUDIO_OUT_SAMPLE_RATE_11025 = 11025,
	SCE_AUDIO_OUT_SAMPLE_RATE_12000 = 12000,
	SCE_AUDIO_OUT_SAMPLE_RATE_16000 = 16000,
	SCE_AUDIO_OUT_SAMPLE_RATE_22050 = 22050,
	SCE_AUDIO_OUT_SAMPLE_RATE_24000 = 24000,
	SCE_AUDIO_OUT_SAMPLE_RATE_32000 = 32000,
	SCE_AUDIO_OUT_SAMPLE_RATE_44100 = 44100,
	SCE_AUDIO_OUT_SAMPLE_RATE_44184 = 44184, //!< Accepted by SrcMix inputs and PSPemu output ports on FW 3.60.
	SCE_AUDIO_OUT_SAMPLE_RATE_48000 = 48000
} SceAudioOutSampleRate;

#define SCE_AUDIO_MIN_LEN 64    //!< Minimum frame-count granularity.
#define SCE_AUDIO_MAX_LEN 65472 //!< Maximum frame count.

#define SCE_AUDIO_OUT_MAX_VOL 32768                 //!< Maximum Q15 output-port volume for game processes on FW 3.60.
#define SCE_AUDIO_VOLUME_0DB  SCE_AUDIO_OUT_MAX_VOL //!< Q15 unity-gain output-port volume.

/** Channel-flag bits accepted by ::sceAudioOutSetVolume. */
typedef enum SceAudioOutChannelFlag {
	SCE_AUDIO_VOLUME_FLAG_L_CH = 1, //!< Left channel.
	SCE_AUDIO_VOLUME_FLAG_R_CH = 2  //!< Right channel.
} SceAudioOutChannelFlag;

/** Configuration selectors accepted by ::sceAudioOutGetConfig. */
typedef enum SceAudioOutConfigType {
	SCE_AUDIO_OUT_CONFIG_TYPE_LEN  = 0,
	SCE_AUDIO_OUT_CONFIG_TYPE_FREQ = 1,
	SCE_AUDIO_OUT_CONFIG_TYPE_MODE = 2
} SceAudioOutConfigType;

/** Automatic-level-control modes for ::sceAudioOutSetAlcMode. */
typedef enum SceAudioOutAlcMode {
	SCE_AUDIO_ALC_OFF      = 0, //!< Disable the BGM dynamic normalizer.
	SCE_AUDIO_ALC_MODE1    = 1, //!< Enable the BGM dynamic normalizer.
	SCE_AUDIO_ALC_MODE_MAX = 2 //!< Number of ALC modes; not a valid mode.
} SceAudioOutAlcMode;

/** Port-selection bits used by the private port-volume APIs. */
typedef enum SceAudioOutPortMask {
	SCE_AUDIO_OUT_PORT_MASK_MAIN  = 2,
	SCE_AUDIO_OUT_PORT_MASK_BGM   = 4,
	SCE_AUDIO_OUT_PORT_MASK_VOICE = 8
} SceAudioOutPortMask;

/** New-port adoption behavior selected by ::sceAudioOutSetAdoptMode. */
typedef enum SceAudioOutAdoptMode {
	SCE_AUDIO_OUT_ADOPT_MODE_AUTOMATIC = 0, //!< Automatically adopt newly opened BGM and voice-profile ports.
	SCE_AUDIO_OUT_ADOPT_MODE_MANUAL    = 1  //!< Do not automatically adopt newly opened BGM and voice-profile ports.
} SceAudioOutAdoptMode;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_AUDIOOUT_H_ */
