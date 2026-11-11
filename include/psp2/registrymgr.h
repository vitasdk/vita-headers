/**
 * \usergroup{SceRegistryMgr}
 * \usage{psp2/registrymgr.h,SceRegistryMgr_stub}
 */

#ifndef _PSP2_REGISTRYMGR_H_
#define _PSP2_REGISTRYMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * System-parameter IDs accepted by the SceRegMgrForGame exports on FW 3.60.
 *
 * Each ID maps to the registry category and key shown in its comment. The
 * setter functions accept only entries explicitly marked writable; using a
 * known read-only ID returns 0x800D0015.
 */
typedef enum SceRegMgrSystemParam {
	SCE_REGMGR_SYSTEM_PARAM_ID_BUTTON_ASSIGN                    = 0x00229142, //!< /CONFIG/SYSTEM/button_assign.
	SCE_REGMGR_SYSTEM_PARAM_ID_LANGUAGE                         = 0x00037502, //!< /CONFIG/SYSTEM/language.
	SCE_REGMGR_SYSTEM_PARAM_ID_DATE_FORMAT                      = 0x00088776, //!< /CONFIG/DATE/date_format.
	SCE_REGMGR_SYSTEM_PARAM_ID_TIME_FORMAT                      = 0x00668503, //!< /CONFIG/DATE/time_format.
	SCE_REGMGR_SYSTEM_PARAM_ID_TIME_ZONE                        = 0x00100591, //!< /CONFIG/DATE/time_zone.
	SCE_REGMGR_SYSTEM_PARAM_ID_SUMMER_TIME                      = 0x00760538, //!< /CONFIG/DATE/summer_time.
	SCE_REGMGR_SYSTEM_PARAM_ID_PARENTAL_PASSCODE                = 0x00186122, //!< /CONFIG/SECURITY/PARENTAL/passcode.
	SCE_REGMGR_SYSTEM_PARAM_ID_USERNAME                         = 0x00598438, //!< /CONFIG/SYSTEM/username.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP_ACCOUNT_ID                    = 0x00450F32, //!< /CONFIG/NP/account_id.
	SCE_REGMGR_SYSTEM_PARAM_ID_TRENDMICRO_SERVICE               = 0x0081649F, //!< /CONFIG/BROWSER/ADDIN/TRENDMICRO/tm_service; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TRENDMICRO_EC_TTL                = 0x00068303, //!< /CONFIG/BROWSER/ADDIN/TRENDMICRO/tm_ec_ttl; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TRENDMICRO_EC_TTL_UPDATE_TIME    = 0x001B2292, //!< /CONFIG/BROWSER/ADDIN/TRENDMICRO/tm_ec_ttl_update_time; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TRENDMICRO_SERVICE_SUB_STATUS    = 0x00872621, //!< /CONFIG/BROWSER/ADDIN/TRENDMICRO/tm_service_sub_status; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP_DEBUG_INGAME_COMMERCE2        = 0x00156489, //!< /CONFIG/NP/debug_ingame_commerce2.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP_ENV                           = 0x00033818, //!< /CONFIG/NP/env.
	SCE_REGMGR_SYSTEM_PARAM_ID_DEVENV_GPI_SWITCH                = 0x003CB6A4, //!< /DEVENV/TOOL/gpi_switch.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP_DEBUG                         = 0x000B73CD, //!< /CONFIG/NP/debug.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP_NAV_ONLY                      = 0x000A0495, //!< /CONFIG/NP/nav_only.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP_AD_CLOCK_DIFF                 = 0x000B6ECD, //!< /CONFIG/NP/np_ad_clock_diff.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP_GEO_FILTERING                 = 0x000D18E5, //!< /CONFIG/NP/np_geo_filtering.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_TEST_PATCH                   = 0x00313905, //!< /CONFIG/NP2/test_patch.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_TPPS_PROXY_SERVER            = 0x00646A8E, //!< /CONFIG/NP2/tpps_proxy_server.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_TPPS_PROXY_PORT              = 0x0022B191, //!< /CONFIG/NP2/tpps_proxy_port.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_TPPS_PROXY_USER_NAME         = 0x008EB468, //!< /CONFIG/NP2/tpps_proxy_user_name.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_TPPS_PROXY_PASSWORD          = 0x00168B9B, //!< /CONFIG/NP2/tpps_proxy_password.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_TPPS_PROXY_FLAG              = 0x006FF829, //!< /CONFIG/NP2/tpps_proxy_flag.
	SCE_REGMGR_SYSTEM_PARAM_ID_BROWSER_WEB_SECURITY_STATUS      = 0x00612B3E, //!< /CONFIG/BROWSER/web_security_status; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_TROPHY_SETUP_DIALOG_DEBUG    = 0x003317A1, //!< /CONFIG/NP2/trophy_setup_dialog_debug.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP_COUNTRY                       = 0x008F94F9, //!< /CONFIG/NP/country.
	SCE_REGMGR_SYSTEM_PARAM_ID_NET_PSPNET_ADHOC_SSID_PREFIX     = 0x00134C03, //!< /CONFIG/NET/pspnet_adhoc_ssid_prefix.
	SCE_REGMGR_SYSTEM_PARAM_ID_KEY_PAD                          = 0x00683DCD, //!< /CONFIG/SYSTEM/key_pad.
	SCE_REGMGR_SYSTEM_PARAM_ID_MUSIC_IMPOSE_AUDIO_BALANCE       = 0x008E3939, //!< /CONFIG/MUSIC/MUSIC_APP/impose_audio_balance.
	SCE_REGMGR_SYSTEM_PARAM_ID_GAME_SHOW_DEBUG_INFO             = 0x00146E23, //!< /CONFIG/GAME/show_debug_info.
	SCE_REGMGR_SYSTEM_PARAM_ID_GAME_FAKE_SDSLOT_BROKEN          = 0x00424500, //!< /CONFIG/GAME/fake_sdslot_broken.
	SCE_REGMGR_SYSTEM_PARAM_ID_SPECIFIC_IDU_MODE                = 0x0051F6AE, //!< /CONFIG/SPECIFIC/idu_mode.
	SCE_REGMGR_SYSTEM_PARAM_ID_GAME_FAKE_FREE_SPACE             = 0x00154A2C, //!< /CONFIG/GAME/fake_free_space.
	SCE_REGMGR_SYSTEM_PARAM_ID_GAME_FAKE_FREE_SPACE_QUOTA       = 0x0025CE9A, //!< /CONFIG/GAME/fake_free_space_quota.
	SCE_REGMGR_SYSTEM_PARAM_ID_TWITTER_ACCESS_TOKEN             = 0x005F6737, //!< /CONFIG/NP2/TWITTER/access_token; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TWITTER_ACCESS_TOKEN_SECRET      = 0x0091F34F, //!< /CONFIG/NP2/TWITTER/access_token_secret; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_PSM_REVOCATION_CHECK_REQ         = 0x0093C981, //!< /CONFIG/PSM/revocation_check_req.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_FAKE_PLUS                    = 0x007C9764, //!< /CONFIG/NP2/fake_plus.
	SCE_REGMGR_SYSTEM_PARAM_ID_SHELL_VOICE_PRIORITY             = 0x00971FA1, //!< /CONFIG/SHELL/voice_priority.
	SCE_REGMGR_SYSTEM_PARAM_ID_NET_SSL_CERT_IGNORABLE           = 0x00563BFE, //!< /CONFIG/NET/ssl_cert_ignorable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TELEPORT_WOL_TARGET_MAC_ADDRESS  = 0x008D89EB, //!< /CONFIG/NP2/TELEPORT/wol_target_mac_address; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TELEPORT_TARGET_NAME             = 0x004E7A16, //!< /CONFIG/NP2/TELEPORT/target_name; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TELEPORT_INITIAL_TARGET          = 0x00987180, //!< /CONFIG/NP2/TELEPORT/initial_target; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TELEPORT_PASSCODE_CLIENT         = 0x000504E4, //!< /CONFIG/NP2/TELEPORT/passcode_client; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_TELEPORT_ENABLE_MEDIA_TRANSFER   = 0x0036F14E, //!< /CONFIG/NP2/TELEPORT/enable_media_transfer.
	SCE_REGMGR_SYSTEM_PARAM_ID_DISPLAY_HDMI_OUT_SCALING_RATIO   = 0x002FDFB4, //!< /CONFIG/DISPLAY/hdmi_out_scaling_ratio.
	SCE_REGMGR_SYSTEM_PARAM_ID_PS4LINK_COUNTER                  = 0x004F7E60, //!< /CONFIG/PS4LINK/counter; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_PS4LINK_KEYS                     = 0x0094E320, //!< /CONFIG/PS4LINK/keys; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_GAME_FAKE_NO_MEMORY_CARD         = 0x009623D0, //!< /CONFIG/GAME/fake_no_memory_card.
	SCE_REGMGR_SYSTEM_PARAM_ID_GAME_FAKE_CONTENTS_MAX           = 0x007D12C4, //!< /CONFIG/GAME/fake_contents_max.
	SCE_REGMGR_SYSTEM_PARAM_ID_PARENTAL_STORE_START_CONTROL     = 0x0089C9CF, //!< /CONFIG/SECURITY/PARENTAL/store_start_control.
	SCE_REGMGR_SYSTEM_PARAM_ID_DATE_IS_SUMMER_TIME              = 0x007F9315, //!< /CONFIG/DATE/is_summer_time.
	SCE_REGMGR_SYSTEM_PARAM_ID_PSNOW_APP_CACHED_URL             = 0x00988B81, //!< /CONFIG/PSNOW/app_cached_url.
	SCE_REGMGR_SYSTEM_PARAM_ID_BROWSER_DEBUG_NET_DBG_CONFIG     = 0x008C3860, //!< /CONFIG/BROWSER/DEBUG/net_dbg_config; writable.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_FAKE_RATELIMIT               = 0x00505BCE, //!< /CONFIG/NP2/fake_ratelimit.
	SCE_REGMGR_SYSTEM_PARAM_ID_NP2_IGNORE_TITLEID               = 0x00528C0D, //!< /CONFIG/NP2/ignore_titleid.
	SCE_REGMGR_SYSTEM_PARAM_ID_ACCESSIBILITY_LARGE_TEXT         = 0x00023FC2, //!< /CONFIG/ACCESSIBILITY/large_text.
	SCE_REGMGR_SYSTEM_PARAM_ID_ACCESSIBILITY_BOLD_TEXT          = 0x00611DC9, //!< /CONFIG/ACCESSIBILITY/bold_text.
	SCE_REGMGR_SYSTEM_PARAM_ID_ACCESSIBILITY_CONTRAST           = 0x008A2AD7, //!< /CONFIG/ACCESSIBILITY/contrast.
	SCE_REGMGR_SYSTEM_PARAM_ID_PARENTAL_CONTENT_START_CONTROL   = 0x00711659  //!< /CONFIG/SECURITY/PARENTAL/content_start_control.
} SceRegMgrSystemParam;

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeyBin(const char *category, const char *name, void *buf, int size);

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a int buffer to hold the value
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeyInt(const char* category, const char* name, int* buf);

/**
 * Get a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a char buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeyStr(const char* category, const char* name, char* buf, const int size);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeyBin(const char *category, const char *name, void *buf, int size);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to an int buffer to hold the value
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeyInt(const char* category, const char* name, int buf);

/**
 * Set a key's information by category and name
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param name - Name of the key
 * @param buf - Pointer to a char buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeyStr(const char* category, const char* name, char* buf, const int size);

/**
 * Get all keys' initial information by category (from os0:kd/registry.db0)
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf[out] - Pointer to a char buffer to hold the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetInitVals(const char* category, char* buf, const int elements_number);

/**
 * Get all keys' information by category
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf[out] - Pointer to a char buffer to hold the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrGetKeys(const char* category, char* buf, const int elements_number);

/**
 * Set all keys' information by category
 *
 * @param category - The path to the directory to be opened (e.g. /CONFIG/SYSTEM)
 * @param buf[out] - Pointer to a char buffer that holds the values
 * @param elements_number - The number of elements of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSetKeys(const char* category, char* buf, const int elements_number);

/**
 * Get a system param key's information by id
 *
 * @param id - A ::SceRegMgrSystemParam ID.
 * @param buf[out] - Pointer to an int to hold the value
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSystemParamGetInt(const int id, int* buf);

/**
 * Get a system param key's information by id
 *
 * @param id - A ::SceRegMgrSystemParam ID.
 * @param buf[out] - Pointer to a char buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegMgrSystemParamGetStr(const int id, char* buf, const int size);


/**
 * Get the registry version
 *
 * @return The packed registry version value on FW 3.60.
 */
int sceRegMgrGetRegVersion(void);


/**
 * Gets a system parameter as binary data.
 *
 * FW 3.60 looks up @p id in its fixed ::SceRegMgrSystemParam table and
 * copies exactly `min(buf_size, 0x800)` bytes to @p buf on success. The buffer
 * is not used after this function returns. An unknown ID or a NULL buffer
 * returns 0x800D0004.
 *
 * @param[in]  id      - System-parameter ID.
 * @param[out] buf     - Destination buffer.
 * @param[in]  buf_size - Requested byte count.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 sceRegMgrSystemParamGetBin(SceRegMgrSystemParam id, void *buf, SceSize buf_size);

/**
 * Sets a writable system parameter from binary data.
 *
 * FW 3.60 requires a non-NULL buffer and @p buf_size no greater than 0x7C0.
 * It copies exactly @p buf_size bytes to kernel memory before returning and
 * does not use the buffer afterwards. The selected registry key must have
 * binary type.
 * Unknown IDs return 0x800D0004 and known read-only IDs return 0x800D0015.
 *
 * @param[in] id      - Writable system-parameter ID.
 * @param[in] buf     - Source bytes.
 * @param[in] buf_size - Number of bytes to copy and store.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 sceRegMgrSystemParamSetBin(SceRegMgrSystemParam id, const void *buf, SceSize buf_size);

/**
 * Sets a writable 32-bit integer system parameter.
 *
 * Unknown IDs return 0x800D0004 and known read-only IDs return 0x800D0015.
 *
 * @param[in] id    - Writable system-parameter ID whose registry key is an integer.
 * @param[in] value - Value to store.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 sceRegMgrSystemParamSetInt(SceRegMgrSystemParam id, SceInt32 value);

/**
 * Sets a writable string system parameter.
 *
 * FW 3.60 requires a non-NULL buffer and @p buf_size no greater than 0x7C0.
 * It copies exactly @p buf_size bytes without adding or checking for a NUL
 * terminator. Include the terminator when the selected key requires it.
 * The buffer is not used after this function returns. Unknown IDs return
 * 0x800D0004 and known read-only IDs return 0x800D0015.
 *
 * @param[in] id      - Writable system-parameter ID whose registry key is a string.
 * @param[in] buf     - Characters to copy.
 * @param[in] buf_size - Number of bytes to copy and store.
 *
 * @return 0 on success, or a negative error code.
 */
SceInt32 sceRegMgrSystemParamSetStr(SceRegMgrSystemParam id, const char *buf, SceSize buf_size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_REGISTRYMGR_H_ */
