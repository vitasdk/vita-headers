/**
 * \usergroup{SceAudio}
 * \usage{psp2/audioout.h,SceAudio_stub}
 */

#ifndef _PSP2_AUDIOOUT_H_
#define _PSP2_AUDIOOUT_H_

#include <psp2common/audioout.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Open an audio-output port.
 *
 * FW 3.60 supports one BGM port and one voice port per process, eight regular
 * MAIN ports, and the dedicated extended MAIN port opened by
 * ::sceAudioOutOpenExtPort. The MAIN profile requires
 * ::SCE_AUDIO_OUT_SAMPLE_RATE_48000. BGM and voice accept every
 * ::SceAudioOutSampleRate value except ::SCE_AUDIO_OUT_SAMPLE_RATE_44184;
 * PSPemu may additionally use that rate.
 *
 * @param[in] type - Output profile.
 * @param[in] len - Number of PCM frames. Must be a multiple of
 *                  ::SCE_AUDIO_MIN_LEN and no greater than
 *                  ::SCE_AUDIO_MAX_LEN.
 * @param[in] freq - One of the ::SceAudioOutSampleRate values accepted by the
 *                   selected output profile.
 * @param[in] mode - Mono or stereo signed 16-bit PCM.
 *
 * @return A port handle on success, or a negative ::SceAudioOutErrorCode value.
 */
int sceAudioOutOpenPort(SceAudioOutPortType type, int len, int freq, SceAudioOutMode mode);

/**
 * Open the calling process's dedicated extended MAIN port.
 *
 * The port uses handle 8 and ::SCE_AUDIO_OUT_SAMPLE_RATE_48000 on FW 3.60.
 *
 * @param[in] len - Number of PCM frames. Must be a multiple of
 *                  ::SCE_AUDIO_MIN_LEN and no greater than
 *                  ::SCE_AUDIO_MAX_LEN.
 * @param[in] mode - Mono or stereo signed 16-bit PCM.
 *
 * @return Port handle 8 on success, or a negative ::SceAudioOutErrorCode value.
 */
int sceAudioOutOpenExtPort(int len, SceAudioOutMode mode);

/**
 * Release an audio-output port.
 *
 * @param[in] port - Port handle returned by ::sceAudioOutOpenPort or
 *                   ::sceAudioOutOpenExtPort.
 *
 * @return 0 on success, or a negative ::SceAudioOutErrorCode value.
 */
int sceAudioOutReleasePort(int port);

/**
 * Output one configured PCM buffer.
 *
 * The call blocks until the supplied buffer has been accepted. Passing NULL
 * waits until the port's previously queued audio has finished playing.
 *
 * @param[in] port - Open port handle.
 * @param[in] buf - Interleaved signed 16-bit PCM, or NULL to wait for queued
 *                  audio to finish playing.
 *
 * @return 0 on success, or a negative ::SceAudioOutErrorCode value.
 */
int sceAudioOutOutput(int port, const void *buf);

/**
 * Set an output port's channel volume.
 *
 * @param[in] port - Open port handle.
 * @param[in] ch - Bitwise OR of ::SceAudioOutChannelFlag values.
 * @param[in] vol - Read-only array containing the left- and right-channel
 *                  Q15 volume values, in that order. FW 3.60 reads both values,
 *                  including for a mono port. Game processes may use values
 *                  from 0 through ::SCE_AUDIO_OUT_MAX_VOL; system and other
 *                  non-game processes may use values through 0xFFFF.
 *                  Channel-mask bits other than left and right are ignored.
 *
 * @return 0 on success, or a negative ::SceAudioOutErrorCode value.
 */
int sceAudioOutSetVolume(int port, int ch, const int *vol);

/**
 * Change an output port's configuration.
 *
 * A negative value for @p len, @p freq, or @p mode leaves that setting
 * unchanged.
 *
 * For a BGM port, the low byte of @p mode contains one of ::SceAudioOutMode,
 * while its high byte contains one of ::SceAudioOutEffectType.
 *
 * @param[in] port - Open port handle.
 * @param[in] len - New frame count, or a negative value to leave it unchanged.
 * @param[in] freq - New ::SceAudioOutSampleRate value accepted by the output
 *                   profile, or a negative value to leave it unchanged.
 * @param[in] mode - New channel mode and optional BGM effect preset, or a
 *                   negative value to leave them unchanged.
 *
 * @par Example:
 * Configure stereo output with the Heavy equalizer preset without changing
 * the frame count or sample rate:
 * @code
 * int mode = SCE_AUDIO_OUT_MODE_STEREO |
 *            (SCE_AUDIO_OUT_EFFECT_TYPE_HEAVY << 8);
 * sceAudioOutSetConfig(port, -1, -1, mode);
 * @endcode
 *
 * @return 0 on success, or a negative ::SceAudioOutErrorCode value.
 */
int sceAudioOutSetConfig(int port, int len, int freq, int mode);

/**
 * Get one property of an output port.
 *
 * @param[in] port - Open port handle.
 * @param[in] type - Property to query.
 *
 * @return The selected frame count, sample rate, or channel mode on success;
 *         otherwise a negative ::SceAudioOutErrorCode value.
 */
int sceAudioOutGetConfig(int port, SceAudioOutConfigType type);

/**
 * Set automatic level control for the calling process's BGM port.
 *
 * Mode 1 enables the FW 3.60 dynamic normalizer; mode 0 bypasses it.
 *
 * @param[in] mode - Automatic-level-control mode.
 *
 * @return 0 on success, or a negative error.
 */
int sceAudioOutSetAlcMode(SceAudioOutAlcMode mode);

/**
 * Set the compressed-audio profile of an open BGM or voice port.
 *
 * @param[in] port - Open BGM or voice port handle.
 * @param[in] enable - ::SCE_TRUE to select the compressed external-codec
 *                     profile, or ::SCE_FALSE for the normal profile.
 *
 * @return 0 on success, or a negative error.
 */
int sceAudioOutSetCompress(int port, SceBool enable);

/**
 * Select the BGM seven-band graphic-equalizer preset for the calling process.
 *
 * @param[in] effect_type - Equalizer preset.
 *
 * @return 0 on success, or a negative error.
 */
int sceAudioOutSetEffectType(SceAudioOutEffectType effect_type);

/**
 * Select whether newly opened BGM and voice-profile ports are adopted
 * automatically.
 *
 * @param[in] mode - Adoption mode. Any nonzero value behaves as manual mode on
 *                   FW 3.60.
 *
 * @return 0.
 */
int sceAudioOutSetAdoptMode(SceAudioOutAdoptMode mode);

/**
 * Change the calling process's adoption state for one output profile.
 *
 * @param[in] type - MAIN, BGM, or voice port selector.
 * @param[in] adopt - ::SCE_TRUE to adopt the port, or ::SCE_FALSE to release it.
 * @param[in] ramp_length - Gain-transition duration in milliseconds, clamped to
 *                         1..4096 on FW 3.60.
 * @param[in] wait_for_completion - When releasing adoption, wait for the
 *                                transition to finish if nonzero.
 *
 * @return 0 on success, or a negative error.
 */
int sceAudioOutSetAdopt_forUser(SceAudioOutPortType type, SceBool adopt, int ramp_length, SceBool wait_for_completion);

/**
 * Apply a private gain ramp to selected output profiles of the calling process.
 *
 * This 0..256 gain is separate from the Q15 per-channel volume configured by
 * ::sceAudioOutSetVolume. A zero mask does nothing, and FW 3.60 ignores mask
 * bits not defined by ::SceAudioOutPortMask.
 *
 * @param[in] port_mask - Bitwise OR of ::SceAudioOutPortMask values.
 * @param[in] volume - Target gain from 0 through 256.
 * @param[in] ramp_length - Gain-transition duration in milliseconds, clamped to
 *                         1..4096 on FW 3.60.
 *
 * @return 0 on success, or a negative error.
 */
int sceAudioOutSetPortVolume_forUser(int port_mask, SceUInt32 volume, int ramp_length);

/**
 * Get a private output-profile gain for the calling process.
 *
 * @param[in] type - MAIN, BGM, or voice port selector.
 *
 * @return The private target gain, normally from 0 through 256, on success; or
 *         a negative error.
 */
int sceAudioOutGetPortVolume_forUser(SceAudioOutPortType type);

/**
 * Get the number of frames remaining on an output port.
 *
 * @param[in] port - Open port handle.
 *
 * @return The queued frame count on success, or a negative
 *         ::SceAudioOutErrorCode value.
 */
int sceAudioOutGetRestSample(int port);

/**
 * Check whether the calling process currently adopts an output profile.
 *
 * FW 3.60 also accepts ::SCE_AUDIO_OUT_PORT_TYPE_VOICE_COMPRESSED for a
 * non-game process and queries the same adoption state as the voice profile.
 * For the MAIN selector, this function returns 1 when the process's MAIN
 * adoption flag is set or when the process has no selected MAIN port.
 *
 * @param[in] type - Output profile selector.
 *
 * @return 1 when adopted, 0 otherwise, or a negative error.
 */
int sceAudioOutGetAdopt(SceAudioOutPortType type);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_AUDIOOUT_H_ */
