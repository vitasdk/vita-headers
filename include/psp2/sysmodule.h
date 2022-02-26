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

/** Errorcodes for SceSysmodule */
typedef enum SceSysmoduleErrorCode {
	SCE_SYSMODULE_LOADED                = 0,          //!< Module is already loaded
	SCE_SYSMODULE_ERROR_INVALID_VALUE   = 0x805A1000, //!< Invalid value
	SCE_SYSMODULE_ERROR_UNLOADED        = 0x805A1001, //!< Module is not loaded
	SCE_SYSMODULE_ERROR_FATAL           = 0x805A10FF  //!< Fatal error
} SceSysmoduleErrorCode;

/** Available modules ID for ::sceSysmoduleLoadModule */
typedef enum SceSysmoduleModuleId {
	SCE_SYSMODULE_INVALID               = 0x0000, //!< Invalid module
	SCE_SYSMODULE_NET                   = 0x0001, //!< Net module
	SCE_SYSMODULE_HTTP                  = 0x0002, //!< HTTP module
	SCE_SYSMODULE_SSL                   = 0x0003, //!< SSL module
	SCE_SYSMODULE_HTTPS                 = 0x0004, //!< HTTPS module
	SCE_SYSMODULE_PERF                  = 0x0005, //!< Perf module
	SCE_SYSMODULE_FIBER                 = 0x0006, //!< Fiber module
	SCE_SYSMODULE_ULT                   = 0x0007, //!< Ult module
	SCE_SYSMODULE_DBG                   = 0x0008, //!< DBG module
	SCE_SYSMODULE_RAZOR_CAPTURE         = 0x0009, //!< Razor Capture module
	SCE_SYSMODULE_RAZOR_HUD             = 0x000A, //!< Razor HUD module
	SCE_SYSMODULE_NGS                   = 0x000B, //!< NGS module
	SCE_SYSMODULE_SULPHA                = 0x000C, //!< Sulpha module
	SCE_SYSMODULE_SAS                   = 0x000D, //!< Sas module
	SCE_SYSMODULE_PGF                   = 0x000E, //!< Pgf module
	SCE_SYSMODULE_APPUTIL               = 0x000F, //!< AppUtil module
	SCE_SYSMODULE_FIOS2                 = 0x0010, //!< Fios2 module
	SCE_SYSMODULE_IME                   = 0x0011, //!< Ime module
	SCE_SYSMODULE_NP_BASIC              = 0x0012, //!< NpBasic module
	SCE_SYSMODULE_SYSTEM_GESTURE        = 0x0013, //!< System Gesture module
	SCE_SYSMODULE_LOCATION              = 0x0014, //!< Location module
	SCE_SYSMODULE_NP                    = 0x0015, //!< Np module
	SCE_SYSMODULE_PHOTO_EXPORT          = 0x0016, //!< Photo Export module
	SCE_SYSMODULE_XML                   = 0x0017, //!< XML module
	SCE_SYSMODULE_NP_COMMERCE2          = 0x0018, //!< NPCommerce2 module
	SCE_SYSMODULE_NP_UTILITY            = 0x0019, //!< NpUtility module
	SCE_SYSMODULE_VOICE                 = 0x001A, //!< Voice module
	SCE_SYSMODULE_VOICEQOS              = 0x001B, //!< VoiceQos module
	SCE_SYSMODULE_NP_MATCHING2          = 0x001C, //!< NpMatching2 module
	SCE_SYSMODULE_SCREEN_SHOT           = 0x001D, //!< ScreenShot module
	SCE_SYSMODULE_NP_SCORE_RANKING      = 0x001E, //!< NpScoreRanking module
	SCE_SYSMODULE_SQLITE                = 0x001F, //!< Sqlite module
	SCE_SYSMODULE_TRIGGER_UTIL          = 0x0020, //!< TriggerUtil module
	SCE_SYSMODULE_RUDP                  = 0x0021, //!< Rudp module
	SCE_SYSMODULE_CODECENGINE_PERF      = 0x0022, //!< CodecEngine Perf module
	SCE_SYSMODULE_LIVEAREA              = 0x0023, //!< Livearea module
	SCE_SYSMODULE_NP_ACTIVITY           = 0x0024, //!< NpActivity module
	SCE_SYSMODULE_NP_TROPHY             = 0x0025, //!< NpTrophy module
	SCE_SYSMODULE_NP_MESSAGE            = 0x0026, //!< NpMessage module
	SCE_SYSMODULE_SHUTTER_SOUND         = 0x0027, //!< Shutter Sound module
	SCE_SYSMODULE_CLIPBOARD             = 0x0028, //!< Clipboard module
	SCE_SYSMODULE_NP_PARTY              = 0x0029, //!< NpParty module
	SCE_SYSMODULE_NET_ADHOC_MATCHING    = 0x002A, //!< NetAdhoc Matching module
	SCE_SYSMODULE_NEAR_UTIL             = 0x002B, //!< NearUtil module
	SCE_SYSMODULE_NP_TUS                = 0x002C, //!< NpTus module
	SCE_SYSMODULE_MP4                   = 0x002D, //!< MP4 module
	SCE_SYSMODULE_AACENC                = 0x002E, //!< AacEnc module
	SCE_SYSMODULE_HANDWRITING           = 0x002F, //!< Handwriting module
	SCE_SYSMODULE_ATRAC                 = 0x0030, //!< Atrac module
	SCE_SYSMODULE_NP_SNS_FACEBOOK       = 0x0031, //!< NpSns Facebook module
	SCE_SYSMODULE_VIDEO_EXPORT          = 0x0032, //!< Video Export module
	SCE_SYSMODULE_NOTIFICATION_UTIL     = 0x0033, //!< NotificationUtil module
	SCE_SYSMODULE_BG_APP_UTIL           = 0x0034, //!< BgAppUtil module
	SCE_SYSMODULE_INCOMING_DIALOG       = 0x0035, //!< Incoming Dialog module
	SCE_SYSMODULE_IPMI                  = 0x0036, //!< IPMI module
	SCE_SYSMODULE_AUDIOCODEC            = 0x0037, //!< AudioCodec module
	SCE_SYSMODULE_FACE                  = 0x0038, //!< Face module
	SCE_SYSMODULE_SMART                 = 0x0039, //!< Smart module
	SCE_SYSMODULE_MARLIN                = 0x003A, //!< Marlin module
	SCE_SYSMODULE_MARLIN_DOWNLOADER     = 0x003B, //!< Marlin Downloader module
	SCE_SYSMODULE_MARLIN_APP_LIB        = 0x003C, //!< Marlin AppLib module
	SCE_SYSMODULE_TELEPHONY_UTIL        = 0x003D, //!< TelephonyUtil module
	SCE_SYSMODULE_SHACCCG               = 0x003E, //!< ShaccCg module
	SCE_SYSMODULE_MONO_BRIDGE           = 0x003F, //!< Mono bridge module
	SCE_SYSMODULE_MONO                  = 0x0040, //!< Mono module
	SCE_SYSMODULE_PSM                   = 0x0041, //!< Psm module
	SCE_SYSMODULE_PSM_DEVAGENT          = 0x0042, //!< Psm devagent module
	SCE_SYSMODULE_PSPNET_ADHOC          = 0x0043, //!< PSPNet Adhoc module
	SCE_SYSMODULE_DTCP_IP               = 0x0044, //!< DTCP/IP module
	SCE_SYSMODULE_VIDEO_SEARCH_EMPR     = 0x0045, //!< VideoSearch module
	SCE_SYSMODULE_NP_SIGNALING          = 0x0046, //!< NpSignaling module
	SCE_SYSMODULE_BEISOBMF              = 0x0047, //!< BEISOBMF module
	SCE_SYSMODULE_BEMP2SYS              = 0x0048, //!< BEMP2SYS module
	SCE_SYSMODULE_MUSIC_EXPORT          = 0x0049, //!< Music Export module
	SCE_SYSMODULE_NEAR_DIALOG_UTIL      = 0x004A, //!< NearDialogUtil module
	SCE_SYSMODULE_LOCATION_EXTENSION    = 0x004B, //!< LocationExt module
	SCE_SYSMODULE_AVPLAYER              = 0x004C, //!< AVPlayer module
	SCE_SYSMODULE_GAME_UPDATE           = 0x004D, //!< Game Update module
	SCE_SYSMODULE_MAIL_API              = 0x004E, //!< Mail Api module
	SCE_SYSMODULE_TELEPORT_CLIENT       = 0x004F, //!< Teleport Client module
	SCE_SYSMODULE_TELEPORT_SERVER       = 0x0050, //!< Teleport Server module
	SCE_SYSMODULE_MP4_RECORDER          = 0x0051, //!< MP4 Recorder module
	SCE_SYSMODULE_APPUTIL_EXT           = 0x0052, //!< AppUtilExt module
	SCE_SYSMODULE_NP_WEBAPI             = 0x0053, //!< NpWebApi module
	SCE_SYSMODULE_AVCDEC                = 0x0054, //!< AVCDec module
	SCE_SYSMODULE_JSON                  = 0x0055  //!< JSON module
} SceSysmoduleModuleId;

/** Available internal modules ID for ::sceSysmoduleLoadModuleInternal */
typedef enum SceSysmoduleInternalModuleId {
	SCE_SYSMODULE_INTERNAL_JPEG_ENC_ARM               = 0x80000001, //!< sceJpegEncArm module
	SCE_SYSMODULE_INTERNAL_AUDIOCODEC                 = 0x80000002, //!< AudioCodec module
	SCE_SYSMODULE_INTERNAL_JPEG_ARM                   = 0x80000003, //!< sceJpegArm module
	SCE_SYSMODULE_INTERNAL_G729                       = 0x80000004, //!< G729 module
	SCE_SYSMODULE_INTERNAL_BXCE                       = 0x80000005, //!< BXCE module
	SCE_SYSMODULE_INTERNAL_INI_FILE_PROCESSOR         = 0x80000006, //!< INI File Processor module
	SCE_SYSMODULE_INTERNAL_NP_ACTIVITY_NET            = 0x80000007, //!< NpActivityNet module
	SCE_SYSMODULE_INTERNAL_PAF                        = 0x80000008, //!< Paf module
	SCE_SYSMODULE_INTERNAL_SQLITE_VSH                 = 0x80000009, //!< sceSqliteVsh module
	SCE_SYSMODULE_INTERNAL_DBUTIL                     = 0x8000000A, //!< DBUtil module
	SCE_SYSMODULE_INTERNAL_ACTIVITY_DB                = 0x8000000B, //!< ActivityDB module
	SCE_SYSMODULE_INTERNAL_COMMON_GUI_DIALOG          = 0x8000000C, //!< Common Gui Dialog module
	SCE_SYSMODULE_INTERNAL_STORE_CHECKOUT             = 0x8000000D, //!< Store Checkout module
	SCE_SYSMODULE_INTERNAL_IME_DIALOG                 = 0x8000000E, //!< Ime Dialog module
	SCE_SYSMODULE_INTERNAL_PHOTO_IMPORT_DIALOG        = 0x8000000F, //!< Photo Import Dialog module
	SCE_SYSMODULE_INTERNAL_PHOTO_REVIEW_DIALOG        = 0x80000010, //!< Photo Review Dialog module
	SCE_SYSMODULE_INTERNAL_CHECKOUT_DIALOG            = 0x80000011, //!< Checkout Dialog module
	SCE_SYSMODULE_INTERNAL_COMMON_DIALOG_MAIN         = 0x80000012, //!< Common Dialog Main module
	SCE_SYSMODULE_INTERNAL_MSG_DIALOG                 = 0x80000013, //!< sceMsgDialog module
	SCE_SYSMODULE_INTERNAL_NET_CHECK_DIALOG           = 0x80000014, //!< NetCheck Dialog module
	SCE_SYSMODULE_INTERNAL_SAVEDATA_DIALOG            = 0x80000015, //!< SaveData Dialog module
	SCE_SYSMODULE_INTERNAL_NP_MESSAGE_DIALOG          = 0x80000016, //!< NpMessage Dialog module
	SCE_SYSMODULE_INTERNAL_TROPHY_SETUP_DIALOG        = 0x80000017, //!< Trophy Setup Dialog module
	SCE_SYSMODULE_INTERNAL_FRIEND_LIST_DIALOG         = 0x80000018, //!< FriendList Dialog module
	SCE_SYSMODULE_INTERNAL_NEAR_PROFILE               = 0x8000001A, //!< Near Profile module
	SCE_SYSMODULE_INTERNAL_NP_FRIEND_PRIVACY_LEVEL    = 0x8000001B, //!< NpFriend Privacy Level module
	SCE_SYSMODULE_INTERNAL_NP_COMMERCE2               = 0x8000001D, //!< NpCommerce2 module
	SCE_SYSMODULE_INTERNAL_NP_KDC                     = 0x8000001E, //!< NpKdc module
	SCE_SYSMODULE_INTERNAL_MUSIC_EXPORT               = 0x8000001F, //!< Music Export module
	SCE_SYSMODULE_INTERNAL_VIDEO_EXPORT               = 0x80000020, //!< Video Export module
	SCE_SYSMODULE_INTERNAL_NP_MESSAGE_DIALOG_IMPL     = 0x80000021, //!< NpMessageDlg module
	SCE_SYSMODULE_INTERNAL_NP_MESSAGE_CONTACTS        = 0x80000022, //!< NpMessageContacts module
	SCE_SYSMODULE_INTERNAL_DB_RECOVERY_UTILITY        = 0x80000023, //!< DBRecoveryUtil module
	SCE_SYSMODULE_INTERNAL_PROMOTER_UTIL              = 0x80000024, //!< scePromoterUtil module
	SCE_SYSMODULE_INTERNAL_PARTY_MEMBER_LIST          = 0x80000026, //!< Party Member List module
	SCE_SYSMODULE_INTERNAL_ULT                        = 0x80000025, //!< Ult module
	SCE_SYSMODULE_INTERNAL_DRM_PSM_KDC                = 0x80000027, //!< DRM PSM KDC module
	SCE_SYSMODULE_INTERNAL_LOCATION_INTERNAL          = 0x80000028, //!< sceLocation module
	SCE_SYSMODULE_INTERNAL_LOCATION_FACTORY           = 0x80000029  //!< Location Factory module
} SceSysmoduleInternalModuleId;

typedef struct SceSysmoduleOpt {
	int flags;
	int *result;
	int unused[2];
} SceSysmoduleOpt;

/**
 * Load a module.
 *
 * @param[in] id - Module ID to load.
 *
 * @return 0 on success, <0 on error.
 */
int sceSysmoduleLoadModule(SceSysmoduleModuleId id);

/**
 * Unload a module.
 *
 * @param[in] id - Module ID to unload.
 *
 * @return 0 on success, <0 on error.
 */
int sceSysmoduleUnloadModule(SceSysmoduleModuleId id);

/**
 * Check if a module is loaded.
 *
 * @param[in] id - Module ID to check.
 *
 * @return 0 if loaded, <0 otherwise.
 */
int sceSysmoduleIsLoaded(SceSysmoduleModuleId id);

/**
 * Load an internal module.
 *
 * @param[in] id - Module ID to load.
 *
 * @return 0 on success, <0 on error.
 */
int sceSysmoduleLoadModuleInternal(SceSysmoduleInternalModuleId id);

/**
 * Unload an internal module.
 *
 * @param[in] id - Module ID to unload.
 *
 * @return 0 on success, <0 on error.
 */
int sceSysmoduleUnloadModuleInternal(SceSysmoduleInternalModuleId id);

/**
 * Check if an internal module is loaded.
 *
 * @param[in] id - Module ID to check.
 *
 * @return 0 if loaded, <0 otherwise.
 */
int sceSysmoduleIsLoadedInternal(SceSysmoduleInternalModuleId id);

/**
 * Load an internal module with custom arguments.
 *
 * @param[in] id     - Module ID to check.
 * @param[in] args   - Size of passed arguments.
 * @param[in] argp   - Pointer to arguments to pass.
 * @param[in] option - Module load option.
 *
 * @return 0 on success, <0 otherwise.
 */
int sceSysmoduleLoadModuleInternalWithArg(SceSysmoduleInternalModuleId id, SceSize args, void *argp, const SceSysmoduleOpt *option);

/**
 * Unload an internal module with custom arguments.
 *
 * @param[in] id     - Module ID to check.
 * @param[in] args   - Size of passed arguments.
 * @param[in] argp   - Pointer to arguments to pass.
 * @param[in] option - Module load option.
 *
 * @return 0 on success, <0 otherwise.
 */
int sceSysmoduleUnloadModuleInternalWithArg(SceSysmoduleInternalModuleId id, SceSize args, void *argp, const SceSysmoduleOpt *option);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SYSMODULE_H_ */

