/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs_internal.h,SceNgs_stub SceNgsUser_stub}
 */


#ifndef _PSP2_NGS_INTERNAL_H_
#define _PSP2_NGS_INTERNAL_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SceUInt32 SceNgsHRack;             
VITASDK_BUILD_ASSERT_EQ(4, SceNgsHRack);
typedef SceUInt32 SceNgsHPatch;            
VITASDK_BUILD_ASSERT_EQ(4, SceNgsHPatch);
typedef SceUInt32 SceNgsHSynSystem;        
VITASDK_BUILD_ASSERT_EQ(4, SceNgsHSynSystem);
typedef SceUInt32 SceNgsHVoice;            
VITASDK_BUILD_ASSERT_EQ(4, SceNgsHVoice);
typedef SceUInt32 SulphaNgsModuleQueryType;
VITASDK_BUILD_ASSERT_EQ(4, SulphaNgsModuleQueryType);
typedef SceUInt32 SceNgsModuleID;          
VITASDK_BUILD_ASSERT_EQ(4, SceNgsModuleID);
typedef void * SceNgsSulphaUpdateCallback; 
VITASDK_BUILD_ASSERT_EQ(4, SceNgsSulphaUpdateCallback);

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

typedef struct SceNgsAT9SkipBufferInfo SceNgsAT9SkipBufferInfo;

typedef struct SceNgsModuleParamHeader SceNgsModuleParamHeader;

typedef SceUInt32 SceNgsParamsID;

typedef struct SceNgsPatchRouteInfo SceNgsPatchRouteInfo;

typedef struct SceNgsVoiceInfo SceNgsVoiceInfo;

typedef struct SceNgsVolumeMatrix SceNgsVolumeMatrix;

typedef struct SceSulphaNgsConfig SceSulphaNgsConfig;

SceInt32 sceNgsAT9GetSectionDetails(const SceInt32 nStartSampleOffset, const SceInt32 nNumSamples, const SceInt32 nConfigData, SceNgsAT9SkipBufferInfo *pAt9InfoBuffer);
SceInt32 sceNgsModuleGetNumPresets(SceNgsHSynSystem hSystemHandle, const SceNgsModuleID uModuleID, SceUInt32 *puNumPresets);
SceInt32 sceNgsModuleGetPreset(SceNgsHSynSystem hSystemHandle, const SceNgsModuleID uModuleID, const SceUInt32 uPresetIndex, SceNgsBufferInfo *pParamsBuffer);
SceInt32 sceNgsPatchCreateRouting(const SceNgsPatchSetupInfo *pPatchInfo, SceNgsHPatch *pPatchHandle);
SceInt32 sceNgsPatchGetInfo(SceNgsHPatch hPatchHandle, SceNgsPatchRouteInfo *pRouteInfo, SceNgsPatchSetupInfo *pSetup);
SceInt32 sceNgsPatchRemoveRouting(SceNgsHPatch hPatchHandle);
SceInt32 sceNgsRackGetRequiredMemorySize(SceNgsHSynSystem hSystemHandle, const SceNgsRackDescription *pRackDesc, SceUInt32 *pnSize);
SceInt32 sceNgsRackGetVoiceHandle(SceNgsHRack hRackHandle, const SceUInt32 uIndex, SceNgsHVoice *pVoiceHandle);
SceInt32 sceNgsRackInit(SceNgsHSynSystem hSystemHandle, SceNgsBufferInfo *pRackBuffer, const SceNgsRackDescription *pRackDesc, SceNgsHRack *pRackHandle);
SceInt32 sceNgsRackRelease(SceNgsHRack hRackHandle, const SceNgsRackReleaseCallbackFunc callbackFuncPtr);
SceInt32 sceNgsRackSetParamErrorCallback(SceNgsHRack hRackHandle, const SceNgsParamsErrorCallbackFunc callbackFuncPtr);
SceInt32 sceNgsSystemGetRequiredMemorySize(const SceNgsSystemInitParams *pSynthParams, SceUInt32 *pnSize);
SceInt32 sceNgsSystemInit(void *pSynthSysMemory, const SceUInt32 uMemSize, const SceNgsSystemInitParams *pSynthParams, SceNgsHSynSystem *pSystemHandle);
SceInt32 sceNgsSystemLock(SceNgsHSynSystem hSystemHandle);
SceInt32 sceNgsSystemRelease(SceNgsHSynSystem hSystemHandle);
SceInt32 sceNgsSystemSetFlags(SceNgsHSynSystem hSystemHandle, const SceUInt32 uSystemFlags);
SceInt32 sceNgsSystemSetParamErrorCallback(SceNgsHSynSystem hSystemHandle, const SceNgsParamsErrorCallbackFunc callbackFuncPtr);
SceInt32 sceNgsSystemUnlock(SceNgsHSynSystem hSystemHandle);
SceInt32 sceNgsSystemUpdate(SceNgsHSynSystem hSystemHandle);
SceInt32 sceNgsVoiceBypassModule(SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, const SceUInt32 uBypassFlag);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetAtrac9Voice(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetCompressorBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetCompressorSideChainBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetDelayBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetDistortionBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetEnvelopeBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetEqBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetMasterBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetMixerBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetPauserBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetPitchShiftBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetReverbBuss(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetSasEmuVoice(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetScreamAtrac9Voice(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetScreamVoice(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetSimpleAtrac9Voice(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetSimpleVoice(void);
const struct SceNgsVoiceDefinition *sceNgsVoiceDefGetTemplate1(void);
SceInt32 sceNgsVoiceGetInfo(SceNgsHVoice hVoiceHandle, SceNgsVoiceInfo *pInfo);
SceInt32 sceNgsVoiceGetModuleBypass(SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, SceUInt32 *puBypassFlag);
SceInt32 sceNgsVoiceGetModuleType(SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, SceNgsModuleID *pModuleType);
SceInt32 sceNgsVoiceGetOutputPatch(SceNgsHVoice hVoiceHandle, const SceInt32 nOutputIndex, const SceInt32 nSubIndex, SceNgsHPatch *pPatchHandle);
SceInt32 sceNgsVoiceGetParamsOutOfRange(SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, char *pszMessageBuffer);
SceInt32 sceNgsVoiceGetStateData(SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, void *pMem, const SceUInt32 uMemSize);
SceInt32 sceNgsVoiceInit(SceNgsHVoice hVoiceHandle, const SceNgsVoicePreset *pPreset, const SceUInt32 uInitFlags);
SceInt32 sceNgsVoiceKeyOff(SceNgsHVoice hVoiceHandle);
SceInt32 sceNgsVoiceKill(SceNgsHVoice hVoiceHandle);
SceInt32 sceNgsVoiceLockParams(SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, const SceNgsParamsID uParamsInterfaceId, SceNgsBufferInfo *pParamsBuffer);
SceInt32 sceNgsVoicePatchSetVolume(SceNgsHPatch hPatchHandle, const SceInt32 nOutputChannel, const SceInt32 nInputChannel, const SceFloat32 fVol);
SceInt32 sceNgsVoicePatchSetVolumes(SceNgsHPatch hPatchHandle, const SceInt32 nOutputChannel, const SceFloat32 *pVolumes, const SceInt32 nVols);
SceInt32 sceNgsVoicePatchSetVolumesMatrix(SceNgsHPatch hPatchHandle, const SceNgsVolumeMatrix *pMatrix);
SceInt32 sceNgsVoicePause(SceNgsHVoice hVoiceHandle);
SceInt32 sceNgsVoicePlay(SceNgsHVoice hVoiceHandle);
SceInt32 sceNgsVoiceResume(SceNgsHVoice hVoiceHandle);
SceInt32 sceNgsVoiceSetFinishedCallback(SceNgsHVoice hVoiceHandle, const SceNgsCallbackFunc callbackFuncPtr, void *pUserData);
SceInt32 sceNgsVoiceSetModuleCallback(SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, const SceNgsModuleCallbackFunc callbackFuncPtr, void *pUserData);
SceInt32 sceNgsVoiceSetParamsBlock(SceNgsHVoice hVoiceHandle, const SceNgsModuleParamHeader *pParamData, const SceUInt32 uSize, SceInt32 *pnErrorCount);
SceInt32 sceNgsVoiceSetPreset(SceNgsHVoice hVoiceHandle, const SceNgsVoicePreset *pVoicePreset);
SceInt32 sceNgsVoiceUnlockParams(SceNgsHVoice hVoiceHandle, const SceUInt32 uModule);
int sceSulphaNgsGetDefaultConfig(SceSulphaNgsConfig *config);
int sceSulphaNgsGetNeededMemory(const SceSulphaNgsConfig *config, SceUInt32 *sizeInBytes);
int sceSulphaNgsInit(const SceSulphaNgsConfig *config, void *buffer, SceUInt32 sizeInBytes);
int sceSulphaNgsSetRackName(SceNgsHRack rackHandle, const char *name);
int sceSulphaNgsSetSampleName(const void *location, SceUInt32 length, const char *name);
int sceSulphaNgsSetSynthName(SceNgsHSynSystem synthHandle, const char *name);
int sceSulphaNgsSetVoiceName(SceNgsHVoice voiceHandle, const char *name);
int sceSulphaNgsShutdown(void);
int sceSulphaNgsTrace(const char *message);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NGS_INTERNAL_H_ */
