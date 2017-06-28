/**
 * \usergroup{SceSysmodule}
 * \usage{psp2/sysmodule.h,SceSysmodule_stub}
 */


#ifndef _PSP2_SYSMODULE_H_
#define _PSP2_SYSMODULE_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceSysmoduleErrorCode {
	SCE_SYSMODULE_LOADED                = 0,
	SCE_SYSMODULE_ERROR_INVALID_VALUE   = 0x805A1000,
	SCE_SYSMODULE_ERROR_UNLOADED        = 0x805A1001,
	SCE_SYSMODULE_ERROR_FATAL           = 0x805A10FF,
} SceSysmoduleErrorCode;

/* module IDs */
typedef enum SceSysmoduleModuleId {
	SCE_SYSMODULE_INVALID               = 0x0000,
	SCE_SYSMODULE_NET                   = 0x0001,
	SCE_SYSMODULE_HTTP                  = 0x0002,
	SCE_SYSMODULE_SSL                   = 0x0003,
	SCE_SYSMODULE_HTTPS                 = 0x0004,
	SCE_SYSMODULE_PERF                  = 0x0005,
	SCE_SYSMODULE_FIBER                 = 0x0006,
	SCE_SYSMODULE_ULT                   = 0x0007,
	SCE_SYSMODULE_DBG                   = 0x0008,
	SCE_SYSMODULE_RAZOR_CAPTURE         = 0x0009,
	SCE_SYSMODULE_RAZOR_HUD             = 0x000a,
	SCE_SYSMODULE_NGS                   = 0x000b,
	SCE_SYSMODULE_SULPHA                = 0x000c,
	SCE_SYSMODULE_SAS                   = 0x000d,
	SCE_SYSMODULE_PGF                   = 0x000e,
	SCE_SYSMODULE_APPUTIL               = 0x000f,
	SCE_SYSMODULE_FIOS2                 = 0x0010,
	SCE_SYSMODULE_IME                   = 0x0011,
	SCE_SYSMODULE_NP_BASIC              = 0x0012,
	SCE_SYSMODULE_SYSTEM_GESTURE        = 0x0013,
	SCE_SYSMODULE_LOCATION              = 0x0014,
	SCE_SYSMODULE_NP                    = 0x0015,
	SCE_SYSMODULE_PHOTO_EXPORT          = 0x0016,
	SCE_SYSMODULE_XML                   = 0x0017,
	SCE_SYSMODULE_NP_COMMERCE2          = 0x0018,
	SCE_SYSMODULE_NP_UTILITY            = 0x0019,
	SCE_SYSMODULE_VOICE                 = 0x001a,
	SCE_SYSMODULE_VOICEQOS              = 0x001b,
	SCE_SYSMODULE_NP_MATCHING2          = 0x001c,
	SCE_SYSMODULE_SCREEN_SHOT           = 0x001d,
	SCE_SYSMODULE_NP_SCORE_RANKING      = 0x001e,
	SCE_SYSMODULE_SQLITE                = 0x001f,
	SCE_SYSMODULE_RUDP                  = 0x0021,
	SCE_SYSMODULE_CODECENGINE_PERF      = 0x0022,
	SCE_SYSMODULE_LIVEAREA              = 0x0023,
	SCE_SYSMODULE_NP_ACTIVITY           = 0x0024,
	SCE_SYSMODULE_NP_TROPHY             = 0x0025,
	SCE_SYSMODULE_NP_MESSAGE            = 0x0026,
	SCE_SYSMODULE_SHUTTER_SOUND         = 0x0027,
	SCE_SYSMODULE_CLIPBOARD             = 0x0028,
	SCE_SYSMODULE_NP_PARTY              = 0x0029,
	SCE_SYSMODULE_NET_ADHOC_MATCHING    = 0x002a,
	SCE_SYSMODULE_NEAR_UTIL             = 0x002b,
	SCE_SYSMODULE_NP_TUS                = 0x002c,
	SCE_SYSMODULE_MP4                   = 0x002d,
	SCE_SYSMODULE_HANDWRITING           = 0x002f,
	SCE_SYSMODULE_ATRAC                 = 0x0030,
	SCE_SYSMODULE_NP_SNS_FACEBOOK       = 0x0031,
	SCE_SYSMODULE_FACE                  = 0x0038,
	SCE_SYSMODULE_SMART                 = 0x0039,
	SCE_SYSMODULE_PSPNET_ADHOC          = 0x0043,
	SCE_SYSMODULE_NP_SIGNALING          = 0x0046,
	SCE_SYSMODULE_MUSIC_EXPORT          = 0x0049,
	SCE_SYSMODULE_NEAR_DIALOG_UTIL      = 0x004a,
	SCE_SYSMODULE_LOCATION_EXTENSION    = 0x004b,
	SCE_SYSMODULE_AVPLAYER              = 0x004c
} SceSysmoduleModuleId;

/* internal module IDs */
typedef enum SceSysmoduleInternalModuleId {
	SCE_SYSMODULE_PAF                   = 0x80000008,
	SCE_SYSMODULE_VIDEO_EXPORT          = 0x80000020,
	SCE_SYSMODULE_PROMOTER_UTIL         = 0x80000024
} SceSysmoduleInternalModuleId;

int sceSysmoduleLoadModule(SceSysmoduleModuleId id);
int sceSysmoduleUnloadModule(SceSysmoduleModuleId id);
int sceSysmoduleIsLoaded(SceSysmoduleModuleId id);
int sceSysmoduleLoadModuleInternal(SceSysmoduleInternalModuleId id);
int sceSysmoduleUnloadModuleInternal(SceSysmoduleInternalModuleId id);
int sceSysmoduleIsLoadedInternal(SceSysmoduleInternalModuleId id);
int sceSysmoduleLoadModuleInternalWithArg(SceSysmoduleInternalModuleId id, SceSize args, void *argp, void *unk);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SYSMODULE_H_ */

