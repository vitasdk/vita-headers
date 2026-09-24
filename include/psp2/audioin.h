/**
 * \usergroup{SceAudioIn}
 * \usage{psp2/audioin.h,SceAudioIn_stub}
 */


#ifndef _PSP2_AUDIOIN_H_
#define _PSP2_AUDIOIN_H_

#include <psp2common/audioin.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Open an audio-input port.
 *
 * FW 3.60 supports at most four ports globally and one port per process.
 * ::SCE_AUDIO_IN_PORT_TYPE_VOICE accepts 256 or 512 samples at 16000 Hz.
 * ::SCE_AUDIO_IN_PORT_TYPE_RAW accepts 256 samples at 16000 Hz or 768 samples
 * at 48000 Hz. ::SCE_AUDIO_IN_PORT_TYPE_CAMERA accepts 256 or 512 samples at
 * 16000 Hz.
 *
 * On FW 3.60, successful handles range from 0x80 through 0xFF. In addition
 * to the named profiles above, any other nonnegative port type below 0x400
 * whose low four bits are zero is accepted, as are 0x12 and 0x1F. The purpose
 * of these additional values is unknown, and they have no confirmed
 * first-party uses.
 *
 * @param[in] port_type - Capture profile.
 * @param[in] grain - Number of mono samples returned by each input call.
 * @param[in] freq - Sample frequency in Hz.
 * @param[in] param - Must be ::SCE_AUDIO_IN_PARAM_FORMAT_S16_MONO on FW 3.60.
 *
 * @return A port handle on success, or a negative error code. Most validation
 *         failures use ::SceAudioInErrorCode.
 */
int sceAudioInOpenPort(SceAudioInPortType portType, int grain, int freq, SceAudioInParam param);

/**
 * Open an audio-input port using the diagnostic entry point.
 *
 * This performs the same work as ::sceAudioInOpenPort. On FW 3.60 it also
 * accepts ::SCE_AUDIO_IN_PORT_TYPE_DIAG without validating \a grain or \a freq;
 * both values are still stored in the resulting port configuration.
 *
 * @param[in] port_type - Capture profile.
 * @param[in] grain - Number of mono samples returned by each input call.
 * @param[in] freq - Sample frequency in Hz.
 * @param[in] param - Must be ::SCE_AUDIO_IN_PARAM_FORMAT_S16_MONO on FW 3.60.
 *
 * @return A port handle on success, or a negative error code. Most validation
 *         failures use ::SceAudioInErrorCode.
 */
int sceAudioInOpenPortForDiag(SceAudioInPortType port_type, int grain, int freq, SceAudioInParam param);

/**
 * Release an audio-input port owned by the calling process.
 *
 * @param[in] port - Port handle returned by ::sceAudioInOpenPort or
 *                   ::sceAudioInOpenPortForDiag.
 *
 * @return 0 on success, or a negative error code.
 */
int sceAudioInReleasePort(int port);

/**
 * Capture the configured number of mono signed 16-bit PCM samples.
 *
 * This function blocks until the configured number of samples is available.
 *
 * @param[in] port - Port handle returned by ::sceAudioInOpenPort or
 *                   ::sceAudioInOpenPortForDiag.
 * @param[out] dest_ptr - Buffer for the captured samples. Its size must be at
 *                       least <code>grain * sizeof(SceInt16)</code> bytes.
 *
 * @return 0 on success, or a negative error code.
 */
int sceAudioInInput(int port, void *destPtr);

/**
 * Capture the configured number of samples and report an input-route change.
 *
 * For a port with device-state reporting enabled, such as the camera profile,
 * FW 3.60 writes 1 for the first two successful captures after the input route
 * changes and writes 0 afterward. This value does not indicate whether the
 * input device is still connected. For other profiles FW 3.60 does not write
 * \a input_device_state.
 *
 * @param[in] port - Port handle returned by ::sceAudioInOpenPort.
 * @param[out] dest_ptr - Buffer for the captured samples. Its size must be at
 *                       least <code>grain * sizeof(SceInt16)</code> bytes.
 * @param[out] input_device_state - Receives the temporary route-change state when
 *                                reporting is enabled for the port. Otherwise
 *                                FW 3.60 does not access this pointer.
 *
 * @return 0 on success, or a negative error code.
 */
int sceAudioInInputWithInputDeviceState(int port, void *dest_ptr, int *input_device_state);

/**
 * Check whether the calling process owns the adopted audio-input port.
 *
 * FW 3.60 accepts only ::SCE_AUDIO_IN_PORT_TYPE_VOICE and
 * ::SCE_AUDIO_IN_PORT_TYPE_RAW. The selected type is validated but does not
 * otherwise affect the result.
 *
 * @param[in] port_type - Port type to validate.
 *
 * @return 1 when the calling process owns a port and is the adopted input
 *         process, 0 otherwise, or a negative ::SceAudioInErrorCode value.
 */
int sceAudioInGetAdopt(SceAudioInPortType portType);

/**
 * Query audio-input state.
 *
 * On Vita TV, FW 3.60 also reports the microphone as muted while the Bluetooth
 * input is inactive.
 *
 * @param[in] select - ::SCE_AUDIO_IN_GETSTATUS_MUTE on FW 3.60.
 *
 * @return 1 when the system microphone is muted, 0 when it is not muted, or a
 *         negative error code for an unsupported selector. FW 3.60 returns
 *         ::SCE_AUDIO_IN_ERROR_INVALID_PORT_PARAM to processes built for an
 *         SDK older than 1.80, and ::SCE_AUDIO_IN_ERROR_INVALID_PARAMETER to
 *         processes built for SDK 1.80 or later.
 */
int sceAudioInGetStatus(int select);

/**
 * Get the current input route.
 *
 * @return The current route, normally one of ::SceAudioInInputMode.
 */
int sceAudioInGetInput(void);

/**
 * Select the input route.
 *
 * The request is applied asynchronously by the input worker. FW 3.60 does not
 * reject values outside ::SceAudioInInputMode: the worker records the requested
 * value as the current route but does not explicitly select an input source
 * for it.
 *
 * @param[in] input_mode - Input route.
 *
 * @return 0 when the route is already selected, otherwise the result of the
 *         FW 3.60 input-worker notification.
 */
int sceAudioInSelectInput(SceAudioInInputMode input_mode);

/**
 * Set the system microphone mute state.
 *
 * FW 3.60 ignores values other than ::SCE_AUDIO_IN_MUTE and
 * ::SCE_AUDIO_IN_UNMUTE.
 *
 * @param[in] command - Mute command.
 *
 * @return The updated internal AudioIn flags for a recognized command. An
 *         unrecognized command is returned unchanged.
 */
int sceAudioInSetMute(SceAudioInMuteCommand command);

/**
 * Set the microphone-gain value stored for a port.
 *
 * FW 3.60 initializes this field to 0x1060 and stores the low 16 bits of
 * \a gain. SceAudioin does not otherwise read it, so its units and purpose are
 * unknown.
 *
 * @param[in] port - Port handle owned by the calling process.
 * @param[in] gain - Value to store.
 *
 * @return 0 on success, or a negative error code. An invalid handle or one not
 *         owned by the calling process returns
 *         ::SCE_AUDIO_IN_ERROR_INVALID_PORT_TYPE on FW 3.60.
 */
int sceAudioInSetMicGain(int port, int gain);

/**
 * Get the microphone-gain value stored for a port.
 *
 * @param[in] port - Port handle owned by the calling process.
 *
 * @return The sign-extended 16-bit value on success, or a negative
 *         error code. An invalid handle or one not owned by the calling
 *         process returns ::SCE_AUDIO_IN_ERROR_INVALID_PORT_TYPE on FW 3.60.
 */
int sceAudioInGetMicGain(int port);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_AUDIOIN_H_ */
