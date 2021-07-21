/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub}
 */


#ifndef _PSP2_NGS_H_
#define _PSP2_NGS_H_

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

typedef void (* SceNgsCallbackFunc)(const SceNgsCallbackInfo* pCallbackInfo);

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

SceInt32 sceNgsModuleCheckParamsInRangeInternal(SceNgsHVoice VoiceHandle, const SceNgsModuleID moduleId, const SceNgsParamsDescriptor* pParams, const SceUInt32 uSize);
SceInt32 sceNgsModuleGetNumPresetsInternal(SceNgsHSynSystem SystemHandle, const SceNgsModuleID ModuleID, SceUInt32* puNumPresets);
SceInt32 sceNgsModuleGetPresetInternal(SceNgsHSynSystem SystemHandle, const SceNgsModuleID ModuleID, const SceUInt32 uPresetIndex, SceNgsBufferInfo* pBufferInfo);
SceInt32 sceNgsPatchCreateRoutingInternal(const SceNgsPatchSetupInfo* pPatchInfo, SceNgsHPatch* pPatchHandle);
SceInt32 sceNgsPatchRemoveRoutingInternal(SceNgsHPatch PatchHandle);
SceInt32 sceNgsRackGetRequiredMemorySizeInternal(SceNgsHSynSystem SystemHandle, const SceNgsRackDescription* pRackDesc, SceUInt32* puUserSize);
SceInt32 sceNgsRackGetVoiceHandleInternal(SceNgsHRack RackHandle, const SceUInt32 uIndex, SceNgsHVoice* pVoiceHandle);
SceInt32 sceNgsRackInitInternal(SceNgsHSynSystem SystemHandle, SceNgsBufferInfo *pRackBuffer, const SceNgsRackDescription* pRackDesc, SceNgsHRack* pRackHandle);
SceInt32 sceNgsRackReleaseInternal(SceNgsHRack RackHandle, const SceNgsRackReleaseCallbackFunc Callback);
SceInt32 sceNgsRackSetParamErrorCallbackInternal(SceNgsHRack RackHandle, const SceNgsParamsErrorCallbackFunc Callback);
SceInt32 sceNgsSulphaGetInfoInternal(const SulphaNgsRegistration* objReg, SceNgsBufferInfo* pInfo);
SceInt32 sceNgsSulphaGetModuleListInternal(SceUInt32* pModuleIds, SceUInt32 inArrayCount, SceUInt32* pCount);
SceInt32 sceNgsSulphaGetSynthUpdateCallbackInternal(SceNgsHSynSystem SystemHandle, SceNgsSulphaUpdateCallback* pUpdateCallback, SceNgsBufferInfo* ppInfo);
SceInt32 sceNgsSulphaQueryModuleInternal(SulphaNgsModuleQueryType type, SulphaNgsModuleQuery* pDebug);
SceInt32 sceNgsSulphaSetSynthUpdateCallbackInternal(SceNgsHSynSystem SystemHandle, SceNgsSulphaUpdateCallback UpdateCallback, SceNgsBufferInfo* pInfo);
SceInt32 sceNgsSystemGetCallbackListInternal(SceNgsHSynSystem SystemHandle, SceNgsCallbackListInfo** ppArray, SceUInt32* puArraySize);
SceInt32 sceNgsSystemGetRequiredMemorySizeInternal(const SceNgsSystemInitParams* pSynthParams, SceUInt32* pnSize);
SceInt32 sceNgsSystemInitInternal(SceNgsBufferInfo* pBufferInfo, const SceUInt32 uCompiledSdkVersion, const SceNgsSystemInitParams* pSynthParams, SceNgsHSynSystem* pSystemHandle);
SceInt32 sceNgsSystemLockInternal(SceNgsHSynSystem SystemHandle);
SceInt32 sceNgsSystemPullDataInternal(SceNgsHSynSystem SystemHandle, const SceUInt32 uDirtyFlagsA, const SceUInt32 uDirtyFlagsB);
SceInt32 sceNgsSystemPushDataInternal(SceNgsHSynSystem SystemHandle);
SceInt32 sceNgsSystemReleaseInternal(SceNgsHSynSystem SystemHandle);
SceInt32 sceNgsSystemSetFlagsInternal(SceNgsHSynSystem hSystemHandle, const SceUInt32 uSystemFlags);
SceInt32 sceNgsSystemSetParamErrorCallbackInternal(SceNgsHSynSystem SystemHandle, const SceNgsParamsErrorCallbackFunc CallbackId);
SceInt32 sceNgsSystemUnlockInternal(SceNgsHSynSystem SystemHandle);
SceInt32 sceNgsSystemUpdateInternal(SceNgsHSynSystem SystemHandle);
SceInt32 sceNgsVoiceBypassModuleInternal(SceNgsHVoice VoiceHandle, const SceUInt32 uModule, const SceUInt32 uBypassFlag);
SceInt32 sceNgsVoiceClearDirtyFlagInternal(SceNgsHVoice VoiceHandle, const SceUInt32 uParamBitFlag);
SceInt32 sceNgsVoiceDefinitionGetPresetInternal(const SceNgsVoiceDefinition* pVoiceDefn, const SceUInt32 uIndex, const SceNgsVoicePreset** ppPreset);
SceInt32 sceNgsVoiceGetModuleBypassInternal(SceNgsHVoice VoiceHandle, const SceUInt32 uModule, SceUInt32* puBypassFlag);
SceInt32 sceNgsVoiceGetOutputPatchInternal(SceNgsHVoice VoiceHandle, const SceInt32 nOutputIndex, const SceInt32 nSubIndex, SceNgsHPatch* pPatchHandle);
SceInt32 sceNgsVoiceGetParamsOutOfRangeBufferedInternal(SceNgsHVoice VoiceHandle, const SceUInt32 uModule, char* messageBuffer);
SceInt32 sceNgsVoiceInitInternal(SceNgsHVoice VoiceHandle, const SceNgsVoicePreset* pPreset, const SceUInt32 uInitFlags);
SceInt32 sceNgsVoiceKeyOffInternal(SceNgsHVoice VoiceHandle);
SceInt32 sceNgsVoiceKillInternal(SceNgsHVoice VoiceHandle);
SceInt32 sceNgsVoicePauseInternal(SceNgsHVoice VoiceHandle);
SceInt32 sceNgsVoicePlayInternal(SceNgsHVoice VoiceHandle);
SceInt32 sceNgsVoiceResumeInternal(SceNgsHVoice VoiceHandle);
SceInt32 sceNgsVoiceSetAllBypassesInternal(SceNgsHVoice VoiceHandle, const SceUInt32 uBypassBitFlag);
SceInt32 sceNgsVoiceSetFinishedCallbackInternal(SceNgsHVoice VoiceHandle, const SceNgsCallbackFunc Callback, void* pUserData);
SceInt32 sceNgsVoiceSetModuleCallbackInternal(SceNgsHVoice VoiceHandle, const SceUInt32 uModule, const SceNgsModuleCallbackFunc Callback, void* pCallbackUsrData);
SceInt32 sceNgsVoiceSetPresetInternal(SceNgsHVoice VoiceHandle, const SceNgsVoicePreset* pVoicePresetInput);
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

#endif /* _PSP2_NGS_H_ */
