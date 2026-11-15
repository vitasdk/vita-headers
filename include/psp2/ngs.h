/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgsUser_stub}
 */

#ifndef _PSP2_NGS_H_
#define _PSP2_NGS_H_

#include <psp2/ngs_internal.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_NGS_MAX_SYSTEM_CHANNELS 2

/**
 * Opaque immutable voice definition.
 *
 * On FW 3.60, this pointer holds an encoded value, not an address. Do not
 * dereference it; store it in ::SceNgsRackDescription::voice_definition.
 */
typedef struct SceNgsVoiceDefinition SceNgsVoiceDefinition;

/** Buffer owned by the caller and used by NGS in place. */
typedef struct SceNgsBufferInfo {
	void *data;   //!< Buffer base address.
	SceSize size; //!< Buffer size in bytes.
} SceNgsBufferInfo;
VITASDK_BUILD_ASSERT_EQ(0x8, SceNgsBufferInfo); // size is from FW 3.60

/** System sizing and processing configuration. */
typedef struct SceNgsSystemInitParams {
	SceInt32 max_racks;    //!< Maximum number of racks; must be from 1 through 64.
	SceInt32 max_voices;   //!< Maximum number of voices; must be from 1 through 256.
	SceInt32 granularity; //!< Number of samples processed per update; a multiple of 64 from 64 through 512.
	SceInt32 sample_rate;  //!< System sample rate; must be 48000 on FW 3.60.
	SceInt32 reserved;    //!< Must be at least zero; otherwise ignored on FW 3.60.
} SceNgsSystemInitParams;
VITASDK_BUILD_ASSERT_EQ(0x14, SceNgsSystemInitParams); // size is from FW 3.60

/** Description used to size and create a rack. */
typedef struct SceNgsRackDescription {
	const SceNgsVoiceDefinition *voice_definition; //!< Immutable definition returned by a sceNgsVoiceDefGet* function.
	SceInt32 voice_count;                          //!< Number of voices to allocate; must be greater than zero.
	SceInt32 channels_per_voice;                    //!< Audio channels per voice; must be 1 or 2.
	SceInt32 max_patches_per_input;                  //!< Patch slots for each dynamic input. Input/mixer racks require a nonzero value.
	SceInt32 patches_per_output;                    //!< Patch slots allocated for each voice output.
	void *user_data;                               //!< Value delivered to the callback passed to ::sceNgsRackRelease.
} SceNgsRackDescription;
VITASDK_BUILD_ASSERT_EQ(0x18, SceNgsRackDescription); // size is from FW 3.60

/** Endpoints used to create one voice-to-voice patch. */
typedef struct SceNgsPatchSetupInfo {
	SceNgsHVoice source_voice;       //!< Source voice.
	SceInt32 source_output_index;     //!< Source voice output index.
	SceInt32 source_output_sub_index;  //!< Source output patch slot, or -1 to use the first free slot.
	SceNgsHVoice destination_voice;  //!< Destination voice; it must belong to the same system as the source.
	SceInt32 destination_input_index; //!< Destination voice input index.
} SceNgsPatchSetupInfo;
VITASDK_BUILD_ASSERT_EQ(0x14, SceNgsPatchSetupInfo); // size is from FW 3.60

/** Voice preset header. Offsets are relative to the start of this structure. */
typedef struct SceNgsVoicePreset {
	SceInt32 name_offset;        //!< Offset of the preset name. Ignored when applying the preset on FW 3.60.
	SceUInt32 name_length;       //!< Preset-name length. Ignored when applying the preset on FW 3.60.
	SceInt32 preset_data_offset;  //!< Offset of the variable-length module parameter records, or zero.
	SceUInt32 preset_data_size;   //!< Size of the module parameter records in bytes.
	SceInt32 bypass_flags_offset; //!< Offset of an array of module indices to bypass, or zero.
	SceUInt32 bypass_flags_count; //!< Number of module indices in the bypass array.
} SceNgsVoicePreset;
VITASDK_BUILD_ASSERT_EQ(0x18, SceNgsVoicePreset); // size is from FW 3.60

/**
 * Information delivered to an NGS callback.
 *
 * A voice-finished callback receives the voice, rack, and user-data fields. A
 * rack-release callback receives the rack and user-data fields. A module
 * callback additionally receives the module ID, two module-defined reason
 * values, and an optional module-defined pointer. Parameter-range callbacks
 * receive the voice, rack, and module ID; the remaining fields are zero on
 * FW 3.60.
 */
typedef struct SceNgsCallbackInfo {
	SceNgsHVoice voice_handle;  //!< Voice associated with the event, or zero for a rack-release event.
	SceNgsHRack rack_handle;    //!< Rack associated with the event.
	SceNgsModuleID module_id;   //!< Module type associated with a module or parameter event.
	SceUInt32 callback_reason;  //!< First module-defined reason value.
	SceUInt32 callback_reason2; //!< Second module-defined reason value.
	void *callback_ptr;         //!< Optional module-defined pointer; valid for the duration of the callback.
	void *user_data;            //!< User value registered with the callback or rack description.
} SceNgsCallbackInfo;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceNgsCallbackInfo); // size is from FW 3.60

/** Header shared by every module-specific parameter structure. */
typedef struct SceNgsParamsDescriptor {
	SceNgsParamsID id;
	SceSize size; //!< Size beginning at \a id, including this field and the module-specific data.
} SceNgsParamsDescriptor;
VITASDK_BUILD_ASSERT_EQ(0x8, SceNgsParamsDescriptor); // size is from FW 3.60

/** Error codes returned by the FW 3.60 NGS implementation. */
typedef enum SceNgsErrorCode {
	SCE_NGS_OK                           = 0x00000000,
	SCE_NGS_ERROR                        = 0x804A0001,
	SCE_NGS_ERROR_INVALID_PARAM          = 0x804A0002,
	SCE_NGS_ERROR_INVALID_ALIGNMENT      = 0x804A0003,
	SCE_NGS_ERROR_NOT_IMPL               = 0x804A0004,
	SCE_NGS_ERROR_DEPENDENCY             = 0x804A0005,
	SCE_NGS_ERROR_OUT_OF_ASSETS          = 0x804A0006,
	SCE_NGS_ERROR_MODULE_NOT_AVAIL       = 0x804A0007,
	SCE_NGS_ERROR_RESOURCE_LOCKED        = 0x804A0008,
	SCE_NGS_ERROR_PARAM_OUT_OF_RANGE     = 0x804A0009,
	SCE_NGS_ERROR_INVALID_VOICE_TYPE     = 0x804A000A,
	SCE_NGS_ERROR_SYSTEM_MISMATCH        = 0x804A000B,
	SCE_NGS_ERROR_INVALID_HANDLE         = 0x804A000C,
	SCE_NGS_ERROR_SIZE_MISMATCH          = 0x804A000D,
	SCE_NGS_ERROR_PATCH_NOT_AVAIL        = 0x804A000E,
	SCE_NGS_ERROR_PARAM_TYPE_MISMATCH    = 0x804A000F,
	SCE_NGS_ERROR_INVALID_STATE          = 0x804A0010,
	SCE_NGS_ERROR_INTERNAL_ALLOC         = 0x804A0011,
	SCE_NGS_ERROR_INTERNAL_PROCESSING    = 0x804A0012,
	SCE_NGS_ERROR_INVALID_BUFFER         = 0x804A0013
} SceNgsErrorCode;

/** Flags accepted by ::sceNgsSystemSetFlags. */
typedef enum SceNgsSystemFlag {
	SCE_NGS_SYSTEM_FLAG_CHECK_PARAMS = 0x00000001 //!< Validate parameter ranges when parameter blocks are unlocked or applied.
} SceNgsSystemFlag;

/** Reset operations selected by ::sceNgsVoiceInit. */
typedef enum SceNgsVoiceInitFlag {
	SCE_NGS_VOICE_INIT_BASE      = 0x00000000,
	SCE_NGS_VOICE_INIT_ROUTING   = 0x00000001, //!< Remove every input and output patch connected to the voice.
	SCE_NGS_VOICE_INIT_PRESET    = 0x00000002, //!< Apply the supplied preset, or the voice definition's default preset when it is NULL.
	SCE_NGS_VOICE_INIT_CALLBACKS = 0x00000004, //!< Clear the module and voice-finished callbacks.
	SCE_NGS_VOICE_INIT_ALL       = 0x00000007
} SceNgsVoiceInitFlag;

/** Bitfield reported by ::SceNgsVoiceInfo::voice_state. */
typedef enum SceNgsVoiceState {
	SCE_NGS_VOICE_STATE_AVAILABLE = 0x00000000,
	SCE_NGS_VOICE_STATE_ACTIVE    = 0x00000001,
	SCE_NGS_VOICE_STATE_FINALIZE  = 0x00000004,
	SCE_NGS_VOICE_STATE_UNLOADING = 0x00000008,
	SCE_NGS_VOICE_STATE_PENDING   = 0x00000010,
	SCE_NGS_VOICE_STATE_PAUSED    = 0x00000020,
	SCE_NGS_VOICE_STATE_KEY_OFF   = 0x00000040
} SceNgsVoiceState;

/** Values accepted and returned by the module-bypass functions. */
typedef enum SceNgsModuleBypassFlag {
	SCE_NGS_MODULE_FLAG_NOT_BYPASSED = 0,
	SCE_NGS_MODULE_FLAG_BYPASSED     = 2
} SceNgsModuleBypassFlag;

/** Byte range and samples to skip at each end when decoding an ATRAC9 sample interval. */
typedef struct SceNgsAT9SkipBufferInfo {
	SceInt32 start_byte_offset; //!< Byte offset of the first required ATRAC9 packet.
	SceInt32 num_bytes;        //!< Number of bytes to make available to the decoder.
	SceInt16 start_skip;       //!< Samples to discard at the start of the first decoded packet.
	SceInt16 end_skip;         //!< Samples to discard at the end of the last decoded packet.
	SceInt32 is_super_packet;   //!< 1 for the four-frame packet layout, otherwise 0.
} SceNgsAT9SkipBufferInfo;
VITASDK_BUILD_ASSERT_EQ(0x10, SceNgsAT9SkipBufferInfo); // size is from FW 3.60

/** Header of one record accepted by ::sceNgsVoiceSetParamsBlock. */
typedef struct SceNgsModuleParamHeader {
	SceInt32 module_index;  //!< Zero-based index in the voice definition.
	SceInt32 channel_index; //!< Channel to update, or -1 to update every channel represented by the following parameter descriptor.
} SceNgsModuleParamHeader;
VITASDK_BUILD_ASSERT_EQ(0x8, SceNgsModuleParamHeader); // size is from FW 3.60

/** Gain matrix indexed as `matrix[outputChannel][inputChannel]`. */
typedef struct SceNgsVolumeMatrix {
	SceFloat32 matrix[SCE_NGS_MAX_SYSTEM_CHANNELS][SCE_NGS_MAX_SYSTEM_CHANNELS];
} SceNgsVolumeMatrix;
VITASDK_BUILD_ASSERT_EQ(0x10, SceNgsVolumeMatrix); // size is from FW 3.60

/** Current route and gain information returned by ::sceNgsPatchGetInfo. */
typedef struct SceNgsPatchRouteInfo {
	SceInt32 output_channels;         //!< Source-rack channel count.
	SceInt32 input_channels;          //!< Destination-rack channel count.
	SceNgsVolumeMatrix volume_matrix; //!< Current output-to-input gain matrix.
} SceNgsPatchRouteInfo;
VITASDK_BUILD_ASSERT_EQ(0x18, SceNgsPatchRouteInfo); // size is from FW 3.60

/** Current voice and voice-definition information. */
typedef struct SceNgsVoiceInfo {
	SceUInt32 voice_state;          //!< Bitwise OR of ::SceNgsVoiceState values.
	SceUInt32 num_modules;          //!< Number of modules in the voice definition.
	SceUInt32 num_inputs;           //!< Number of dynamic input modules in the voice definition.
	SceUInt32 num_outputs;          //!< Number of outputs exposed by the voice definition.
	SceUInt32 num_patches_per_output; //!< Patch slots allocated for each output.
	SceUInt32 update_passed;        //!< Number of processing updates completed for this voice since its most recent initialization or play.
} SceNgsVoiceInfo;
VITASDK_BUILD_ASSERT_EQ(0x18, SceNgsVoiceInfo); // size is from FW 3.60

/** Sulpha NGS trace-agent capacities. */
typedef struct SceSulphaNgsConfig {
	SceUInt32 max_named_samples;    //!< Maximum sample-memory ranges that can be named; the FW 3.60 default is 1024.
	SceUInt32 api_trace_buffer_size; //!< NGS API-call trace buffer size in bytes; only complete 16-byte records are used. The FW 3.60 default is 4096.
} SceSulphaNgsConfig;
VITASDK_BUILD_ASSERT_EQ(0x8, SceSulphaNgsConfig); // size is from FW 3.60

/**
 * Compute the encoded byte range and samples to skip at each end for an ATRAC9
 * sample range.
 *
 * The output is cleared before validation. FW 3.60 accepts ATRAC9 frame-duration
 * codes 1, 4, and 7 and requires the low byte of \a config_data to be 0xFE.
 * Bit 31 of \a start_sample_offset requests one frame of decoder preroll; the
 * remaining 31 bits contain the sample offset and are backed up by 64, 128, or
 * 256 samples according to the frame-duration code, clamped at zero.
 *
 * @param[in] start_sample_offset - First requested decoded sample.
 * @param[in] num_samples - Number of requested samples; must be at least zero.
 * @param[in] config_data - Packed ATRAC9 configuration word.
 * @param[out] at9_info_buffer - Receives the required byte range and sample skips.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsAT9GetSectionDetails(SceInt32 start_sample_offset, SceInt32 num_samples, SceInt32 config_data, SceNgsAT9SkipBufferInfo *at9_info_buffer);

/**
 * Return the number of built-in presets provided by a module type.
 *
 * @param[in] system_handle - Initialized system handle.
 * @param[in] module_id - Module type ID, not a module index in a voice.
 * @param[out] num_presets - Receives the preset count.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsModuleGetNumPresets(SceNgsHSynSystem system_handle, SceNgsModuleID module_id, SceUInt32 *num_presets);

/**
 * Copy one built-in module preset into a caller-owned buffer.
 *
 * Initialize both members of \a params_buffer before the call. Its data buffer
 * must be large enough for the selected preset; the function does not allocate
 * memory or change the buffer-size member.
 *
 * @param[in] system_handle - Initialized system handle.
 * @param[in] module_id - Module type ID, not a module index in a voice.
 * @param[in] preset_index - Zero-based preset index.
 * @param[in,out] params_buffer - Destination pointer and capacity in bytes.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsModuleGetPreset(SceNgsHSynSystem system_handle, SceNgsModuleID module_id, SceUInt32 preset_index, SceNgsBufferInfo *params_buffer);

/**
 * Create a route from one voice output to one voice input.
 *
 * Both voices must belong to the same system. A source sub-index of -1 selects
 * the first free patch slot. The route is initialized with zero gains. NGS
 * rejects a route that would create a dependency cycle it cannot process.
 *
 * @param[in] patch_info - Source and destination endpoints.
 * @param[out] patch_handle - Receives the new patch handle.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsPatchCreateRouting(const SceNgsPatchSetupInfo *patch_info, SceNgsHPatch *patch_handle);

/**
 * Get the current source/destination channel counts and gains of a patch.
 *
 * @param[in] patch_handle - Patch handle.
 * @param[out] route_info - Receives current channel counts and matrix information.
 * @param[out] setup - Optional destination for the original patch setup.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsPatchGetInfo(SceNgsHPatch patch_handle, SceNgsPatchRouteInfo *route_info, SceNgsPatchSetupInfo *setup);

/**
 * Remove a voice-to-voice patch and release its source output slot.
 *
 * @param[in] patch_handle - Patch handle to remove.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsPatchRemoveRouting(SceNgsHPatch patch_handle);

/**
 * Compute the rack-buffer size required for a description.
 *
 * @param[in] system_handle - System that will own the rack.
 * @param[in] rack_desc - Rack description.
 * @param[out] size - Receives the required number of bytes.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsRackGetRequiredMemorySize(SceNgsHSynSystem system_handle, const SceNgsRackDescription *rack_desc, SceSize *size);

/**
 * Return one voice allocated by a rack.
 *
 * @param[in] rack_handle - Initialized rack handle.
 * @param[in] index - Zero-based voice index, less than the rack's voice count.
 * @param[out] voice_handle - Receives the voice handle.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsRackGetVoiceHandle(SceNgsHRack rack_handle, SceUInt32 index, SceNgsHVoice *voice_handle);

/**
 * Create a rack and all of its voices in caller-owned memory.
 *
 * The buffer base must be 16-byte aligned and its capacity must be at least the
 * value returned by ::sceNgsRackGetRequiredMemorySize. NGS retains and modifies
 * this memory until the rack has been released. Initialization uses one
 * rack slot and ::SceNgsRackDescription::voice_count voice slots from the
 * system limits.
 *
 * @param[in] system_handle - Owning system handle.
 * @param[in] rack_buffer - Rack buffer pointer and capacity.
 * @param[in] rack_desc - Rack configuration and allocation limits.
 * @param[out] rack_handle - Receives the rack handle.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsRackInit(SceNgsHSynSystem system_handle, const SceNgsBufferInfo *rack_buffer, const SceNgsRackDescription *rack_desc, SceNgsHRack *rack_handle);

/**
 * Stop every voice, remove every connected patch, and release a rack.
 *
 * With a NULL callback, the rack is released before this function returns.
 * With a callback, a later ::sceNgsSystemUpdate completes the release, and the
 * callback receives the rack and ::SceNgsRackDescription::user_data.
 *
 * @param[in] rack_handle - Rack to release.
 * @param[in] callback_func_ptr - Optional asynchronous completion callback.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsRackRelease(SceNgsHRack rack_handle, SceNgsRackReleaseCallbackFunc callback_func_ptr);

/**
 * Set the parameter-range callback for one rack.
 *
 * This callback takes precedence over the system-wide callback and is invoked
 * by ::sceNgsSystemUpdate on the thread that calls it.
 *
 * @param[in] rack_handle - Rack handle.
 * @param[in] callback_func_ptr - Callback, or NULL to clear it.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsRackSetParamErrorCallback(SceNgsHRack rack_handle, SceNgsParamsErrorCallbackFunc callback_func_ptr);

/**
 * Compute the system-buffer size required by an initialization configuration.
 *
 * @param[in] synth_params - System limits and processing configuration.
 * @param[out] size - Receives the required number of bytes.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsSystemGetRequiredMemorySize(const SceNgsSystemInitParams *synth_params, SceSize *size);

/**
 * Initialize an NGS system in caller-owned memory.
 *
 * The memory base must be 16-byte aligned and the size must be at least the
 * result of ::sceNgsSystemGetRequiredMemorySize. FW 3.60 permits at most eight
 * simultaneous systems in one process and initializes each system with
 * ::SCE_NGS_SYSTEM_FLAG_CHECK_PARAMS enabled.
 *
 * @param[in,out] synth_sys_memory - Memory retained and modified by NGS until release.
 * @param[in] mem_size - Available bytes at \a synth_sys_memory.
 * @param[in] synth_params - System limits and processing configuration.
 * @param[out] system_handle - Receives the initialized system handle.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsSystemInit(void *synth_sys_memory, SceSize mem_size, const SceNgsSystemInitParams *synth_params, SceNgsHSynSystem *system_handle);

/**
 * Lock the system's internal update state.
 *
 * Pair each call with a call to ::sceNgsSystemUnlock.
 *
 * @param[in] system_handle - System to lock.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsSystemLock(SceNgsHSynSystem system_handle);

/**
 * Release a system after all of its racks have been released.
 *
 * @param[in] system_handle - System to release.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsSystemRelease(SceNgsHSynSystem system_handle);

/**
 * Replace the system flags used by subsequent parameter operations.
 *
 * @param[in] system_handle - System handle.
 * @param[in] system_flags - Bitwise OR of ::SceNgsSystemFlag values.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsSystemSetFlags(SceNgsHSynSystem system_handle, SceUInt32 system_flags);

/**
 * Set the fallback parameter-range callback for a system.
 *
 * @param[in] system_handle - System handle.
 * @param[in] callback_func_ptr - Callback, or NULL to clear it.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsSystemSetParamErrorCallback(SceNgsHSynSystem system_handle, SceNgsParamsErrorCallbackFunc callback_func_ptr);

/**
 * Unlock a system previously locked with ::sceNgsSystemLock.
 *
 * @param[in] system_handle - System to unlock.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsSystemUnlock(SceNgsHSynSystem system_handle);

/**
 * Process one audio grain and run every queued callback.
 *
 * Callback functions execute synchronously on the thread calling this function,
 * after the kernel-side processing update has completed.
 *
 * @param[in] system_handle - System to update.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsSystemUpdate(SceNgsHSynSystem system_handle);

/**
 * Set the bypass state of one module in a voice definition.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] module - Zero-based module index, not a ::SceNgsModuleID.
 * @param[in] bypass_flag - One of ::SceNgsModuleBypassFlag.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceBypassModule(SceNgsHVoice voice_handle, SceUInt32 module, SceUInt32 bypass_flag);
/** Return the complex ATRAC9 playback voice definition with four sends. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetAtrac9Voice(void);

/** Return an input-mix, compressor, and output bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetCompressorBuss(void);

/** Return a two-input side-chain compressor bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetCompressorSideChainBuss(void);

/** Return an input-mix, modulated-delay, and output bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetDelayBuss(void);

/** Return an input-mix, distortion, and output bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetDistortionBuss(void);

/** Return an input-mix, amplitude-envelope, and output bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetEnvelopeBuss(void);

/** Return an input-mix, four-band parametric-EQ, and output bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetEqBuss(void);

/** Return the master bus definition that exposes PCM output to the caller. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetMasterBuss(void);

/** Return a bus definition that mixes multiple input voices. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetMixerBuss(void);

/** Return an input-mix, click-free pauser, and output bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetPauserBuss(void);

/** Return an input-mix, pitch-shift, and output bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetPitchShiftBuss(void);

/** Return an input-mix, environmental-reverb, and output bus definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetReverbBuss(void);

/** Return the libSas-emulation voice definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetSasEmuVoice(void);

/** Return the Scream ATRAC9 playback voice definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetScreamAtrac9Voice(void);

/** Return the Scream waveform playback voice definition. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetScreamVoice(void);

/** Return the basic ATRAC9 playback voice definition with two sends. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetSimpleAtrac9Voice(void);

/** Return the basic PCM/VAG playback voice definition with two sends. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetSimpleVoice(void);

/** Return the complex waveform playback template with signal generation and four sends. */
const SceNgsVoiceDefinition *sceNgsVoiceDefGetTemplate1(void);

/**
 * Get one voice's current key state, module counts, and routing information.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[out] info - Receives the voice snapshot.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceGetInfo(SceNgsHVoice voice_handle, SceNgsVoiceInfo *info);

/**
 * Get the bypass state of one module.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] module - Zero-based module index.
 * @param[out] bypass_flag - Receives one of ::SceNgsModuleBypassFlag.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceGetModuleBypass(SceNgsHVoice voice_handle, SceUInt32 module, SceUInt32 *bypass_flag);

/**
 * Map a zero-based module index to its module type ID.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] module - Zero-based module index.
 * @param[out] module_type - Receives the ::SceNgsModuleID.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceGetModuleType(SceNgsHVoice voice_handle, SceUInt32 module, SceNgsModuleID *module_type);

/**
 * Return the patch occupying one voice output slot.
 *
 * @param[in] voice_handle - Source voice handle.
 * @param[in] output_index - Zero-based output index.
 * @param[in] sub_index - Zero-based patch slot within that output.
 * @param[out] patch_handle - Receives the patch handle, or zero when the slot is empty.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceGetOutputPatch(SceNgsHVoice voice_handle, SceInt32 output_index, SceInt32 sub_index, SceNgsHPatch *patch_handle);

/**
 * Format the most recent parameter-range result for one module.
 *
 * The destination must provide at least 128 bytes. The resulting string is
 * either a module mismatch/range diagnostic or `No value was out of range\n`.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] module - Zero-based module index.
 * @param[out] message_buffer - Writable 128-byte string buffer.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceGetParamsOutOfRange(SceNgsHVoice voice_handle, SceUInt32 module, char *message_buffer);

/**
 * Copy one module's runtime state snapshot.
 *
 * The requested size must exactly match that module's state-data size; otherwise
 * ::SCE_NGS_ERROR_SIZE_MISMATCH is returned.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] module - Zero-based module index.
 * @param[out] memory - Destination buffer.
 * @param[in] mem_size - Exact module state-data size in bytes.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceGetStateData(SceNgsHVoice voice_handle, SceUInt32 module, void *memory, SceSize mem_size);

/**
 * Reinitialize a stopped voice and optionally reset patches, preset, or callbacks.
 *
 * The voice must not be playing or keyed off. Bits outside
 * ::SceNgsVoiceInitFlag are ignored on FW 3.60.
 *
 * @param[in] voice_handle - Voice to initialize.
 * @param[in] preset - Optional preset selected by ::SCE_NGS_VOICE_INIT_PRESET.
 * @param[in] init_flags - Bitwise OR of ::SceNgsVoiceInitFlag values.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceInit(SceNgsHVoice voice_handle, const SceNgsVoicePreset *preset, SceUInt32 init_flags);

/**
 * Request release/envelope processing for a playing voice.
 *
 * This changes the key state from playing to keyed off; processing continues
 * until the voice finishes or is killed.
 *
 * @param[in] voice_handle - Playing voice to key off.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceKeyOff(SceNgsHVoice voice_handle);

/**
 * Immediately stop a playing or keyed-off voice and return it to the stopped state.
 *
 * @param[in] voice_handle - Voice to stop.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceKill(SceNgsHVoice voice_handle);

/**
 * Lock and expose one module's live parameter block.
 *
 * Only one lock for a module may be active at a time. The returned pointer
 * refers directly to the rack buffer and remains valid until the rack is
 * released, but changes are committed by ::sceNgsVoiceUnlockParams.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] module - Zero-based module index.
 * @param[in] params_interface_id - Expected parameter-interface ID; FW 3.60 compares its low 16 bits.
 * @param[out] params_buffer - Receives the live parameter pointer and size.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceLockParams(SceNgsHVoice voice_handle, SceUInt32 module, SceNgsParamsID params_interface_id, SceNgsBufferInfo *params_buffer);

/**
 * Set one gain in a patch's `[output][input]` matrix.
 *
 * @param[in] patch_handle - Patch handle.
 * @param[in] output_channel - Output channel, less than the source channel count.
 * @param[in] input_channel - Destination input channel; must be 0 or 1.
 * @param[in] volume - Linear gain stored without clamping on FW 3.60.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoicePatchSetVolume(SceNgsHPatch patch_handle, SceInt32 output_channel, SceInt32 input_channel, SceFloat32 volume);

/**
 * Set the one or two input-channel gains for a patch output.
 *
 * @param[in] patch_handle - Patch handle.
 * @param[in] output_channel - Output row to replace.
 * @param[in] volumes - Array containing \a volume_count gains.
 * @param[in] volume_count - Number of gains; valid callers use 1 or 2.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoicePatchSetVolumes(SceNgsHPatch patch_handle, SceInt32 output_channel, const SceFloat32 *volumes, SceInt32 volume_count);

/**
 * Replace a patch's complete 2x2 output-to-input gain matrix.
 *
 * A mono source uses only the first row; a stereo source uses all four
 * values.
 *
 * @param[in] patch_handle - Patch handle.
 * @param[in] matrix - Replacement gain matrix.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoicePatchSetVolumesMatrix(SceNgsHPatch patch_handle, const SceNgsVolumeMatrix *matrix);

/**
 * Pause voice processing without changing whether the voice is playing or keyed off.
 *
 * @param[in] voice_handle - Voice to pause.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoicePause(SceNgsHVoice voice_handle);

/**
 * Start a stopped voice.
 *
 * A voice must be initialized before it can be played.
 *
 * @param[in] voice_handle - Voice to start.
 *
 * @return 0 on success, or ::SCE_NGS_ERROR_INVALID_STATE if it is not stopped.
 */
SceInt32 sceNgsVoicePlay(SceNgsHVoice voice_handle);

/**
 * Resume a paused voice without changing its play/key-off state.
 *
 * @param[in] voice_handle - Voice to resume.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceResume(SceNgsHVoice voice_handle);

/**
 * Set the callback queued when a voice reaches its finished state.
 *
 * The callback runs from ::sceNgsSystemUpdate and receives \a user_data through
 * ::SceNgsCallbackInfo::user_data.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] callback_func_ptr - Callback, or NULL to clear it.
 * @param[in] user_data - Opaque value returned to the callback.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceSetFinishedCallback(SceNgsHVoice voice_handle, SceNgsCallbackFunc callback_func_ptr, void *user_data);

/**
 * Set the callback for events from the module at a given index.
 *
 * The callback runs from ::sceNgsSystemUpdate. Its reason and data fields are
 * defined by the selected module type.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] module - Zero-based module index.
 * @param[in] callback_func_ptr - Callback, or NULL to clear it.
 * @param[in] user_data - Opaque value returned to the callback.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceSetModuleCallback(SceNgsHVoice voice_handle, SceUInt32 module, SceNgsModuleCallbackFunc callback_func_ptr, void *user_data);

/**
 * Apply a packed sequence of module parameter records.
 *
 * Valid records are applied even when another record fails. If non-NULL,
 * \a error_count receives the number of rejected records.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] param_data - First packed record header. Each header is followed
 *                         by a ::SceNgsParamsDescriptor and its module-specific
 *                         data.
 * @param[in] size - Total byte size of the record sequence.
 * @param[out] error_count - Optional rejected-record count.
 *
 * @return 0 when every record is valid, or the error encountered while parsing or applying a record.
 */
SceInt32 sceNgsVoiceSetParamsBlock(SceNgsHVoice voice_handle, const SceNgsModuleParamHeader *param_data, SceSize size, SceInt32 *error_count);

/**
 * Restore module defaults, then apply an optional voice preset.
 *
 * A NULL preset restores the definition's module defaults and clears the preset
 * bypass list. The voice does not have to be stopped, but locked parameter
 * interfaces cause ::SCE_NGS_ERROR_RESOURCE_LOCKED.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] voice_preset - Preset to apply, or NULL for module defaults.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceSetPreset(SceNgsHVoice voice_handle, const SceNgsVoicePreset *voice_preset);

/**
 * Commit and unlock a module parameter block returned by ::sceNgsVoiceLockParams.
 *
 * When ::SCE_NGS_SYSTEM_FLAG_CHECK_PARAMS is set, invalid values are rejected
 * and the module is not marked as changed for processing.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] module - Zero-based module index previously locked.
 *
 * @return 0 on success, or a negative ::SceNgsErrorCode value.
 */
SceInt32 sceNgsVoiceUnlockParams(SceNgsHVoice voice_handle, SceUInt32 module);
/**
 * Fill a Sulpha NGS configuration with the FW 3.60 defaults.
 *
 * @param[out] config - Receives limits of 1024 named sample-memory ranges and a
 *                      4096-byte API-call trace buffer.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsGetDefaultConfig(SceSulphaNgsConfig *config);

/**
 * Compute all memory needed by the Sulpha NGS agent and its fixed NGS pools.
 *
 * @param[in] config - Sulpha NGS capacities.
 * @param[out] size_in_bytes - Receives the required byte count.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsGetNeededMemory(const SceSulphaNgsConfig *config, SceSize *size_in_bytes);

/**
 * Initialize Sulpha NGS tracing for the calling process.
 *
 * All threads in the process share this tracing agent.
 * The supplied memory must remain valid until ::sceSulphaNgsShutdown. Use
 * ::sceSulphaNgsGetNeededMemory rather than relying on the implementation's
 * check, which accepts a smaller minimum size.
 *
 * @param[in] config - Sulpha NGS capacities.
 * @param[in,out] buffer - Caller-owned tracing memory.
 * @param[in] size_in_bytes - Available bytes in \a buffer.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsInit(const SceSulphaNgsConfig *config, void *buffer, SceSize size_in_bytes);

/**
 * Assign a diagnostic Sulpha name to an initialized rack.
 *
 * @param[in] rack_handle - Rack handle.
 * @param[in] name - Diagnostic name forwarded to Sulpha.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsSetRackName(SceNgsHRack rack_handle, const char *name);

/**
 * Associate a diagnostic name with a sample-memory range.
 *
 * @param[in] location - Non-NULL sample-data address.
 * @param[in] length - Nonzero sample-data size in bytes.
 * @param[in] name - Diagnostic name forwarded to Sulpha.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsSetSampleName(const void *location, SceSize length, const char *name);

/**
 * Assign a diagnostic Sulpha name to an initialized NGS system.
 *
 * @param[in] synth_handle - System handle.
 * @param[in] name - Diagnostic name forwarded to Sulpha.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsSetSynthName(SceNgsHSynSystem synth_handle, const char *name);

/**
 * Assign a diagnostic Sulpha name to an initialized voice.
 *
 * @param[in] voice_handle - Voice handle.
 * @param[in] name - Diagnostic name forwarded to Sulpha.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsSetVoiceName(SceNgsHVoice voice_handle, const char *name);

/**
 * Unregister the Sulpha NGS agent shared by all threads in the process and
 * release its registrations.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsShutdown(void);

/**
 * Emit \a message as a Sulpha trace event in the `Ngs` category.
 *
 * @param[in] message - Literal message; it is passed through a `%s` format.
 *
 * @return 0 on success, or a negative Sulpha error code.
 */
SceInt32 sceSulphaNgsTrace(const char *message);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NGS_H_ */
