/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs_internal.h,SceNgs_stub}
 */


#ifndef _PSP2_NGS_INTERNAL_H_
#define _PSP2_NGS_INTERNAL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SceUInt32 SceNgsHRack;
typedef SceUInt32 SceNgsHPatch;
typedef SceUInt32 SceNgsHSynSystem;
typedef SceUInt32 SceNgsHVoice;
typedef SceUInt32 SulphaNgsModuleQueryType;
typedef SceUInt32 SceNgsModuleID;
typedef void * SceNgsSulphaUpdateCallback;

typedef struct SceNgsCallbackInfo SceNgsCallbackInfo;

typedef void (* SceNgsCallbackFunc)(const SceNgsCallbackInfo* callback_info);

typedef SceNgsCallbackFunc SceNgsRackReleaseCallbackFunc;
typedef SceNgsCallbackFunc SceNgsModuleCallbackFunc;
typedef SceNgsCallbackFunc SceNgsParamsErrorCallbackFunc;

// missing structs
typedef struct SceNgsVoicePreset SceNgsVoicePreset;
typedef struct SceNgsSystemInitParams SceNgsSystemInitParams;
typedef struct SceNgsBufferInfo SceNgsBufferInfo;
typedef struct SceNgsSystemInitParams SceNgsSystemInitParams;
typedef struct SceNgsCallbackListInfo SceNgsCallbackListInfo;
typedef struct SulphaNgsModuleQuery SulphaNgsModuleQuery;
typedef struct SulphaNgsRegistration SulphaNgsRegistration;
typedef struct SceNgsRackDescription SceNgsRackDescription;
typedef struct SceNgsPatchSetupInfo SceNgsPatchSetupInfo;
typedef struct SceNgsParamsDescriptor SceNgsParamsDescriptor;
typedef struct SceNgsCallbackInfo SceNgsCallbackInfo;
typedef struct SceNgsVoiceDefinition SceNgsVoiceDefinition;

SceInt32 sceNgsModuleCheckParamsInRangeInternal(SceNgsHVoice handle, const SceNgsModuleID module_id, const SceNgsParamsDescriptor* descriptor, const SceUInt32 size);
SceInt32 sceNgsModuleGetNumPresetsInternal(SceNgsHSynSystem handle, const SceNgsModuleID module_id, SceUInt32* num_presets);
SceInt32 sceNgsModuleGetPresetInternal(SceNgsHSynSystem handle, const SceNgsModuleID module_id, const SceUInt32 preset_index, SceNgsBufferInfo* info);
SceInt32 sceNgsPatchCreateRoutingInternal(const SceNgsPatchSetupInfo* info, SceNgsHPatch* handle);
SceInt32 sceNgsPatchRemoveRoutingInternal(SceNgsHPatch handle);
SceInt32 sceNgsRackGetRequiredMemorySizeInternal(SceNgsHSynSystem handle, const SceNgsRackDescription* rack_description, SceUInt32* user_size);
SceInt32 sceNgsRackGetVoiceHandleInternal(SceNgsHRack rack_handle, const SceUInt32 index, SceNgsHVoice* voice_handle);
SceInt32 sceNgsRackInitInternal(SceNgsHSynSystem system_handle, SceNgsBufferInfo *rack_buffer, const SceNgsRackDescription* rack_description, SceNgsHRack* rack_handle);
SceInt32 sceNgsRackReleaseInternal(SceNgsHRack handle, const SceNgsRackReleaseCallbackFunc callback);
SceInt32 sceNgsRackSetParamErrorCallbackInternal(SceNgsHRack rack_handle, const SceNgsParamsErrorCallbackFunc callback);
SceInt32 sceNgsSulphaGetInfoInternal(const SulphaNgsRegistration* obj_reg, SceNgsBufferInfo* info);
SceInt32 sceNgsSulphaGetModuleListInternal(SceUInt32* module_ids, SceUInt32 in_array_count, SceUInt32* count);
SceInt32 sceNgsSulphaGetSynthUpdateCallbackInternal(SceNgsHSynSystem handle, SceNgsSulphaUpdateCallback* update_callback, SceNgsBufferInfo* info);
SceInt32 sceNgsSulphaQueryModuleInternal(SulphaNgsModuleQueryType type, SulphaNgsModuleQuery* debug);
SceInt32 sceNgsSulphaSetSynthUpdateCallbackInternal(SceNgsHSynSystem handle, SceNgsSulphaUpdateCallback update_callback, SceNgsBufferInfo* info);
SceInt32 sceNgsSystemGetCallbackListInternal(SceNgsHSynSystem handle, SceNgsCallbackListInfo** array, SceUInt32* array_size);
SceInt32 sceNgsSystemGetRequiredMemorySizeInternal(const SceNgsSystemInitParams* params, SceUInt32* size);
SceInt32 sceNgsSystemInitInternal(SceNgsBufferInfo* buffer_info, const SceUInt32 compiled_sdk_version, const SceNgsSystemInitParams* params, SceNgsHSynSystem* handle);
SceInt32 sceNgsSystemLockInternal(SceNgsHSynSystem handle);
SceInt32 sceNgsSystemPullDataInternal(SceNgsHSynSystem handle, const SceUInt32 dirty_flags_a, const SceUInt32 dirty_flags_b);
SceInt32 sceNgsSystemPushDataInternal(SceNgsHSynSystem handle);
SceInt32 sceNgsSystemReleaseInternal(SceNgsHSynSystem handle);
SceInt32 sceNgsSystemSetFlagsInternal(SceNgsHSynSystem handle, const SceUInt32 system_flags);
SceInt32 sceNgsSystemSetParamErrorCallbackInternal(SceNgsHSynSystem handle, const SceNgsParamsErrorCallbackFunc callback_id);
SceInt32 sceNgsSystemUnlockInternal(SceNgsHSynSystem handle);
SceInt32 sceNgsSystemUpdateInternal(SceNgsHSynSystem handle);
SceInt32 sceNgsVoiceBypassModuleInternal(SceNgsHVoice handle, const SceUInt32 module, const SceUInt32 flag);
SceInt32 sceNgsVoiceClearDirtyFlagInternal(SceNgsHVoice handle, const SceUInt32 param_bit_flag);
SceInt32 sceNgsVoiceDefinitionGetPresetInternal(const SceNgsVoiceDefinition* definition, const SceUInt32 index, const SceNgsVoicePreset** presets);
SceInt32 sceNgsVoiceGetModuleBypassInternal(SceNgsHVoice handle, const SceUInt32 module, SceUInt32* flag);
SceInt32 sceNgsVoiceGetOutputPatchInternal(SceNgsHVoice handle, const SceInt32 nOutputIndex, const SceInt32 nSubIndex, SceNgsHPatch* pPatchHandle);
SceInt32 sceNgsVoiceGetParamsOutOfRangeBufferedInternal(SceNgsHVoice handle, const SceUInt32 module, char* message_buffer);
SceInt32 sceNgsVoiceInitInternal(SceNgsHVoice handle, const SceNgsVoicePreset* preset, const SceUInt32 flags);
SceInt32 sceNgsVoiceKeyOffInternal(SceNgsHVoice handle);
SceInt32 sceNgsVoiceKillInternal(SceNgsHVoice handle);
SceInt32 sceNgsVoicePauseInternal(SceNgsHVoice handle);
SceInt32 sceNgsVoicePlayInternal(SceNgsHVoice handle);
SceInt32 sceNgsVoiceResumeInternal(SceNgsHVoice handle);
SceInt32 sceNgsVoiceSetAllBypassesInternal(SceNgsHVoice handle, const SceUInt32 bitflag);
SceInt32 sceNgsVoiceSetFinishedCallbackInternal(SceNgsHVoice handle, const SceNgsCallbackFunc callback, void* userdata);
SceInt32 sceNgsVoiceSetModuleCallbackInternal(SceNgsHVoice handle, const SceUInt32 module, const SceNgsModuleCallbackFunc callback, void* callback_userdata);
SceInt32 sceNgsVoiceSetPresetInternal(SceNgsHVoice handle, const SceNgsVoicePreset* preset);

const SceNgsVoiceDefinition* sceNgsVoiceDefGetAtrac9VoiceInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetCompressorBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetCompressorSideChainBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetDelayBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetDistortionBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetEnvelopeBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetEqBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetMasterBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetMixerBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetPauserBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetPitchshiftBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetReverbBussInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetSasEmuVoiceInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetScreamVoiceAT9Internal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetScreamVoiceInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetSimpleAtrac9VoiceInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetSimpleVoiceInternal(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetTemplate1Internal(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NGS_INTERNAL_H_ */
