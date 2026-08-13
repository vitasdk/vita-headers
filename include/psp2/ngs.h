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
const SceNgsVoiceDefinition *sceNgsVoiceDefGetAtrac9Voice(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetCompressorBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetCompressorSideChainBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetDelayBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetDistortionBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetEnvelopeBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetEqBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetMasterBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetMixerBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetPauserBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetPitchShiftBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetReverbBuss(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetSasEmuVoice(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetScreamAtrac9Voice(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetScreamVoice(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetSimpleAtrac9Voice(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetSimpleVoice(void);
const SceNgsVoiceDefinition *sceNgsVoiceDefGetTemplate1(void);
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

#endif /* _PSP2_NGS_H_ */
