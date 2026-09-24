/**
 * \kernelgroup{SceAudio}
 * \usage{psp2kern/audioout.h,SceAudioForDriver_stub}
 */

#ifndef _PSP2KERN_AUDIOOUT_H_
#define _PSP2KERN_AUDIOOUT_H_

#include <psp2kern/types.h>
#include <psp2common/audioout.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Mixed-output paths configured and read by the monitor APIs. */
typedef enum SceAudioOutMonitorPath {
	SCE_AUDIO_OUT_MONITOR_PATH_PRIMARY   = 0, //!< SrcMix1 main output; used for program-audio capture.
	SCE_AUDIO_OUT_MONITOR_PATH_SECONDARY = 1  //!< SrcMix0 secondary output.
} SceAudioOutMonitorPath;

/** Output modes selected for a mixed-output monitor path. */
typedef enum SceAudioOutMonitorPathMode {
	SCE_AUDIO_OUT_MONITOR_PATH_MODE_LOCAL_I2S = 0, //!< Route to the selected local I2S output.
	SCE_AUDIO_OUT_MONITOR_PATH_MODE_HDMI      = 1, //!< Route to the HDMI audio output.
	SCE_AUDIO_OUT_MONITOR_PATH_MODE_READBACK  = 2  //!< Route mixed PCM to RAM through ::ksceAudioOutMonitorRead.
} SceAudioOutMonitorPathMode;

/** Channel modes accepted by ::ksceAudioOutMonitorSetChannelMode. */
typedef enum SceAudioOutMonitorChannelMode {
	SCE_AUDIO_OUT_MONITOR_CHANNEL_MODE_MONO   = 1,
	SCE_AUDIO_OUT_MONITOR_CHANNEL_MODE_STEREO = 2
} SceAudioOutMonitorChannelMode;

/** SrcMix2 input-0 sources selected by ::ksceAudioSrcMix2SetInput0SourceMode. */
typedef enum SceAudioOutSrcMix2Input0SourceMode {
	SCE_AUDIO_OUT_SRCMIX2_INPUT0_SOURCE_I2S   = 0, //!< Read the selected I2S transmit FIFO.
	SCE_AUDIO_OUT_SRCMIX2_INPUT0_SOURCE_DUMMY = 1, //!< Read the FW 3.60 dummy page.
	SCE_AUDIO_OUT_SRCMIX2_INPUT0_SOURCE_PCM   = 2  //!< Read PCM submitted by ::ksceAudioSrcMix2SubmitInput0Pcm.
} SceAudioOutSrcMix2Input0SourceMode;

/**
 * Callback invoked after a voice or compressed-voice output port is opened or
 * released. MAIN and BGM ports do not invoke these callbacks on FW 3.60.
 *
 * @param[in] process_id - Owner PID for an opened port, or former owner PID for
 *                        a released port.
 */
typedef void (*SceAudioOutPortCallback)(ScePID process_id);

/**
 * Select the mixed-output monitor sample rate.
 *
 * Selecting ::SCE_AUDIO_OUT_SAMPLE_RATE_8000 enables the FW 3.60 FIR
 * downsample path.
 *
 * @param[in] sample_rate - ::SCE_AUDIO_OUT_SAMPLE_RATE_8000 or
 *                         ::SCE_AUDIO_OUT_SAMPLE_RATE_48000.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioOutMonitorSetSampleRate(int sample_rate);

/**
 * Set the global SrcMix1 master gain.
 *
 * SceAVConfig uses this control for PS TV master volume. It sets the same gain
 * for the left and right channels.
 *
 * @param[in] gain - Q15 gain from 0 through ::SCE_AUDIO_OUT_MAX_VOL.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioOutSetMasterGain(SceUInt32 gain);

/**
 * Set automatic level control for the current process's BGM port.
 *
 * Mode 1 enables the FW 3.60 dynamic normalizer; mode 0 bypasses it.
 *
 * @param[in] mode - Automatic-level-control mode.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioOutSetAlcMode(SceAudioOutAlcMode mode);

/**
 * Configure one SrcMix block's input and output sample rates.
 *
 * A positive input rate may be any ::SceAudioOutSampleRate value. For each rate
 * argument, a negative value leaves the setting unchanged and zero disables
 * that input or output. FW 3.60 accepts positive output rates 8000, 12000,
 * 16000, 22050, 24000, 32000, 44100, and 48000 Hz. The command encoder
 * recognizes 11050, but a later rate check rejects it; neither 11050 nor 11025
 * is a usable output rate.
 * FW 3.60 does not validate @p src_mix_index; callers must use 0 through 2.
 *
 * @param[in] src_mix_index - SrcMix block index from 0 through 2.
 * @param[in] input0_rate - Input-0 ::SceAudioOutSampleRate value, zero to
 *                         disable the input, or a negative value to leave it
 *                         unchanged.
 * @param[in] input1_rate - Input-1 ::SceAudioOutSampleRate value, zero to
 *                         disable the input, or a negative value to leave it
 *                         unchanged.
 * @param[in] output_rate - Output rate listed above, zero to disable output, or
 *                         a negative value to leave it unchanged.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioSrcMixSetSampleRates(SceUInt32 src_mix_index, int input0_rate, int input1_rate, int output_rate);

/**
 * Change a process's adoption state for one output profile.
 *
 * @param[in] process_id - Process whose output state is changed.
 * @param[in] type - MAIN, BGM, or voice port selector.
 * @param[in] adopt - ::SCE_TRUE to adopt the port, or ::SCE_FALSE to release it.
 * @param[in] ramp_length - Gain-transition duration in milliseconds, clamped to
 *                         1..4096 on FW 3.60.
 * @param[in] wait_for_completion - When releasing adoption, wait for the
 *                                transition to finish if nonzero.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioOutSetAdoptForPid(ScePID process_id, SceAudioOutPortType type, SceBool adopt, int ramp_length, SceBool wait_for_completion);

/**
 * Capture the I2S0 transmit FIFO into RAM.
 *
 * The result is interleaved stereo signed 16-bit PCM. Calls with a non-NULL
 * destination form a two-entry pipeline and may return while the destination
 * is still being filled. You may reuse the destination buffer after the next
 * call with a non-NULL destination returns. A call with a NULL destination
 * waits for all queued captures to complete, after which you may reuse their
 * buffers.
 *
 * @param[out] dest - 128-byte-aligned destination, or NULL.
 * @param[in] frame_count - At least 64 frames and a multiple of 32. FW 3.60
 *                         validates this argument even when @p dest is NULL.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioI2s0CaptureTx(SceInt16 *dest, SceSize frame_count);

/**
 * Apply a private gain ramp to selected output profiles of a process.
 * A zero mask does nothing, and FW 3.60 ignores mask bits not defined by
 * ::SceAudioOutPortMask.
 *
 * @param[in] process_id - Process whose output state is changed.
 * @param[in] port_mask - Bitwise OR of ::SceAudioOutPortMask values.
 * @param[in] volume - Target gain from 0 through 256.
 * @param[in] ramp_length - Gain-transition duration in milliseconds, clamped to
 *                         1..4096 on FW 3.60.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioOutSetPortVolumeForPid(ScePID process_id, int port_mask, SceUInt32 volume, int ramp_length);

/**
 * Submit PCM from RAM to SrcMix2 input 0.
 *
 * ::SCE_AUDIO_OUT_SRCMIX2_INPUT0_SOURCE_PCM must be selected first. The input
 * is interleaved stereo signed 16-bit PCM.
 *
 * @param[in] src - Source PCM buffer. The caller must keep it readable until
 *                  the queued DMA transfer has finished reading it; this
 *                  function does not provide a completion callback.
 * @param[in] frame_count - More than 4 frames and a multiple of 4.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioSrcMix2SubmitInput0Pcm(const SceInt16 *src, SceSize frame_count);

/**
 * Queue capture of SrcMix2's main output into RAM.
 *
 * Calls with a non-NULL destination form a two-entry pipeline and may return
 * while the destination is still being filled. You may reuse the destination
 * buffer after the next call with a non-NULL destination returns. Passing NULL
 * waits until all already queued captures complete.
 *
 * @param[out] dest - 16-byte-aligned destination for interleaved stereo signed
 *                    16-bit PCM, or NULL to wait for queued captures to finish.
 * @param[in] frame_count - More than 4 frames and a multiple of 4; ignored when
 *                         @p dest is NULL.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioSrcMix2CaptureOutput(SceInt16 *dest, SceSize frame_count);

/**
 * Select the hardware I2S source used by SrcMix2 input 0.
 *
 * @param[in] i2s_index - I2S index from 0 through 2.
 *
 * @return 0 on success, or -1 for an invalid index.
 */
int ksceAudioSrcMix2SetInputI2sIndex(SceUInt32 i2s_index);

/**
 * Queue one mixed-output PCM readback.
 *
 * SceAVConfig uses the primary path as the post-mix program-audio source for
 * Bluetooth transmission. At 48000 Hz in stereo, a frame occupies four bytes.
 * When either 8000 Hz or mono conversion is selected, FW 3.60 requires exactly
 * 120 frames. Only one destination can be pending per path.
 *
 * @param[in] path - Mixed-output path.
 * @param[out] dest - Destination for signed 16-bit PCM. The caller must keep
 *                    the buffer writable until the queued readback completes.
 * @param[in] frame_count - More than 4 frames and a multiple of 4; exactly 120
 *                         when conversion is enabled.
 *
 * @return 0 when queued, -2 when the path is not in readback mode, or another
 *         negative error.
 */
int ksceAudioOutMonitorRead(SceAudioOutMonitorPath path, SceInt16 *dest, SceSize frame_count);

/**
 * Select the source used by SrcMix2 input 0.
 *
 * FW 3.60 does not validate this value. Values other than 0 and 2 use the
 * dummy-page source, but only value 2 permits
 * ::ksceAudioSrcMix2SubmitInput0Pcm.
 *
 * @param[in] source_mode - Input source.
 *
 * @return 0.
 */
int ksceAudioSrcMix2SetInput0SourceMode(SceAudioOutSrcMix2Input0SourceMode source_mode);

/**
 * Select the current process's BGM seven-band graphic-equalizer preset.
 *
 * @param[in] effect_type - Equalizer preset.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioOutSetEffectType(SceAudioOutEffectType effect_type);

/**
 * Select and enable an I2S output.
 *
 * @param[in] i2s_index - I2S index from 3 through 7.
 *
 * @return 0 on success, or -1 for an invalid index.
 */
int ksceAudioOutSetI2sOutputIndex(int i2s_index);

/**
 * Select the output mode of a mixed-output monitor path.
 *
 * On FW 3.60 this function accepts path value 2, but that value indexes beyond
 * the two intended monitor contexts and is rejected by
 * ::ksceAudioOutMonitorRead. Do not use it. This function does not
 * validate @p mode; values outside ::SceAudioOutMonitorPathMode are stored but
 * do not select a usable output path.
 *
 * @param[in] path - Primary or secondary mixed-output path.
 * @param[in] mode - Output mode for the path.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioOutMonitorSetPathMode(SceAudioOutMonitorPath path, SceAudioOutMonitorPathMode mode);

/**
 * Get a process's private output-profile gain.
 *
 * @param[in] process_id - Process whose output state is queried.
 * @param[in] type - MAIN, BGM, or voice port selector.
 *
 * @return The private target gain, normally from 0 through 256, on success; or
 *         a negative error.
 */
int ksceAudioOutGetPortVolumeForPid(ScePID process_id, SceAudioOutPortType type);

/**
 * Select whether newly opened BGM and voice-profile ports are adopted
 * automatically.
 *
 * @param[in] mode - Adoption mode. Any nonzero value behaves as manual mode on
 *                   FW 3.60.
 *
 * @return 0.
 */
int ksceAudioOutSetAdoptMode(SceAudioOutAdoptMode mode);

/**
 * Register or clear the output-port release callback.
 *
 * @param[in] callback - Callback invoked with the former owner PID after a
 *                       voice or compressed-voice port is released, or NULL to
 *                       clear it.
 *
 * @return 0.
 */
int ksceAudioOutSetPortReleaseCallback(SceAudioOutPortCallback callback);

/**
 * Register or clear the output-port open callback.
 *
 * @param[in] callback - Callback invoked with the owner PID after a voice or
 *                       compressed-voice port opens, or NULL to clear it.
 *
 * @return 0.
 */
int ksceAudioOutSetPortOpenCallback(SceAudioOutPortCallback callback);

/**
 * Select the mixed-output monitor channel mode.
 *
 * On FW 3.60 this also configures the monitor clock generator for a 48000 Hz
 * source.
 *
 * @param[in] mode - Mono or stereo monitor mode.
 *
 * @return 0 on success, or a negative error.
 */
int ksceAudioOutMonitorSetChannelMode(SceAudioOutMonitorChannelMode mode);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_AUDIOOUT_H_ */
