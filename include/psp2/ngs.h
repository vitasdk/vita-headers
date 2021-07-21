/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub}
 */


#ifndef _PSP2_NGS_H_
#define _PSP2_NGS_H_

#ifdef __cplusplus
extern "C" {
#endif

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
SceInt32 sceNgsVoiceDefinitionGetPresetInternal(const struct SceNgsVoiceDefinition* pVoiceDefn, const SceUInt32 uIndex, const SceNgsVoicePreset** ppPreset);
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
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetAtrac9VoiceInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetCompressorBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetCompressorSideChainBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetDelayBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetDistortionBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetEnvelopeBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetEqBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetMasterBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetMixerBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetPauserBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetPitchshiftBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetReverbBussInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetSasEmuVoiceInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetScreamVoiceAT9Internal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetScreamVoiceInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetSimpleAtrac9VoiceInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetSimpleVoiceInternal(void);
const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetTemplate1Internal(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NGS_H_ */
