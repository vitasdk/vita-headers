/**
 * \kernelgroup{SceAudioIn}
 * \usage{psp2kern/audioin.h,SceAudioInForDriver_stub}
 */

#ifndef _PSP2KERN_AUDIOIN_H_
#define _PSP2KERN_AUDIOIN_H_

#include <psp2kern/types.h>
#include <psp2common/audioin.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback called after an audio-input port is opened or released.
 *
 * @param[in] process_id - Owner PID for an opened port, or former owner PID for
 *                        a released port.
 */
typedef void (*SceAudioInPortCallback)(ScePID process_id);

/**
 * Open an audio-input port for the calling process.
 *
 * @param[in] port_type - Capture profile. See ::sceAudioInOpenPort.
 * @param[in] grain - Number of mono samples returned by each input call.
 * @param[in] freq - Sample frequency in Hz.
 * @param[in] param - Must be ::SCE_AUDIO_IN_PARAM_FORMAT_S16_MONO on FW 3.60.
 *
 * @return A port handle on success, or a negative error code. Most validation
 *         failures use ::SceAudioInErrorCode.
 */
int ksceAudioInOpenPort(SceAudioInPortType port_type, int grain, int freq, SceAudioInParam param);

/**
 * Release an audio-input port owned by the calling process.
 *
 * @param[in] port - Port handle returned by ::ksceAudioInOpenPort.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceAudioInReleasePort(int port);

/**
 * Capture the configured number of mono signed 16-bit PCM samples.
 *
 * @param[in] port - Port handle returned by ::ksceAudioInOpenPort.
 * @param[out] dest_ptr - Kernel buffer for the captured samples. Its size must
 *                       be at least <code>grain * sizeof(SceInt16)</code> bytes.
 *
 * @return 0 on success, or a negative error code.
 */
int ksceAudioInInput(int port, void *dest_ptr);

/**
 * Check whether any process owns an audio-input port.
 *
 * @return SCE_TRUE when at least one port is open, otherwise SCE_FALSE.
 */
SceBool ksceAudioInIsAnyPortOpen(void);

/**
 * Check whether a process owns an audio-input port.
 *
 * @param[in] process_id - Valid nonzero process ID. Passing 0 also matches an
 *                        unused FW 3.60 port slot.
 *
 * @return SCE_TRUE when the process owns a port, otherwise SCE_FALSE.
 */
SceBool ksceAudioInIsProcessPortOwner(ScePID process_id);

/**
 * Select the process whose audio-input port is adopted.
 *
 * On FW 3.60 \a unused1 and \a unused2 are ignored. A nonzero
 * \a transition_delay temporarily suppresses the selected process's input. The
 * input worker subtracts 16 from this value per processing cycle. If the value
 * reaches exactly zero while route-change reports remain, the worker holds it
 * at 16 until both reports have been returned by input calls. Values that are
 * not positive multiples of 16 can cross below zero and end suppression
 * without that hold.
 * AppMgr always passes zero on FW 3.60.
 *
 * @param[in] process_id - Process to adopt.
 * @param[in] unused1 - Ignored on FW 3.60.
 * @param[in] unused2 - Ignored on FW 3.60.
 * @param[in] transition_delay - Input-suppression countdown, or 0.
 *
 * @return 0.
 */
int ksceAudioInSetAdoptForPid(ScePID process_id, int unused1, int unused2, int transition_delay);

/**
 * Register or clear the port-open callback.
 *
 * The callback runs synchronously after a port opens successfully and receives
 * its owner PID. AudioIn releases its internal mutex before invoking it and
 * returns the new handle after the callback completes.
 *
 * @param[in] callback - Callback, or NULL to clear it.
 *
 * @return 0.
 */
int ksceAudioInSetPortOpenCallback(SceAudioInPortCallback callback);

/**
 * Register or clear the port-release callback.
 *
 * The callback runs synchronously when a port is released, including during
 * process exit or kill cleanup, and receives its former owner PID. It runs
 * while AudioIn holds its internal mutex. The callback must not call an AudioIn
 * operation that locks the same mutex, such as opening, releasing, or reading
 * a port.
 *
 * @param[in] callback - Callback, or NULL to clear it.
 *
 * @return 0.
 */
int ksceAudioInSetPortReleaseCallback(SceAudioInPortCallback callback);

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
int ksceAudioInSelectInput(SceAudioInInputMode input_mode);

/**
 * Submit Bluetooth microphone PCM to AudioIn.
 *
 * AVConfig uses this function after receiving Bluetooth audio. The samples are
 * used only while Bluetooth input is active. FW 3.60 stores them in a
 * 360-sample ring buffer and advances the expected producer position
 * by 120 samples per submission. It inserts silence when the producer is more
 * than 120 samples behind and trims input when the producer is more than 120
 * samples ahead. The worker upsamples the submitted stream by two using
 * midpoint interpolation.
 *
 * @param[in] samples - Kernel-resident mono signed 16-bit PCM samples. This may
 *                      be NULL only when \a sample_count is zero.
 * @param[in] sample_count - Number of 16-bit samples, not bytes.
 *
 * @return The input-worker notification result on success, -1 when the
 *         Bluetooth input is not active, or a negative mutex error.
 */
int ksceAudioInSubmitBluetoothPcm(const SceInt16 *samples, SceSize sample_count);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_AUDIOIN_H_ */
