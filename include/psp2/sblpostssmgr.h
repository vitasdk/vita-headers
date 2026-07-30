/**
 * \usergroup{SceSblPostSsMgr}
 * \usage{psp2/sblpostssmgr.h,SceSblLicMgr_stub SceSblPmMgr_stub SceSblRtcMgr_stub SceSblUtMgr_stub}
 */

#ifndef _PSP2_SBLPOSTSSMGR_H_
#define _PSP2_SBLPOSTSSMGR_H_

#include <psp2/types.h>
#include <psp2common/sblpostssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSblLicMgrActivateDevkit(char *afv_path);
int sceSblLicMgrActivateFromFs(void);
int sceSblLicMgrClearActivationData(void);
int sceSblLicMgrGetActivationKey(SceSblActivationKey *key);
int sceSblLicMgrGetExpireDate(int *expire_date, int request_data_flag);
int sceSblLicMgrGetIssueNo(int *issue_number, int request_data_flag);
int sceSblLicMgrGetLicenseStatus(void);
int sceSblLicMgrGetUsageTimeLimit(SceUInt32 *time_limit);
int sceSblPmMgrAuthEtoI(void);

/**
 * Get the cached current-mode value.
 *
 * @param[out] result - Receives one byte through the existing wider pointer type.
 */
int sceSblPmMgrGetCurrentMode(int *result);

/**
 * Get the KBL product-mode value.
 *
 * @param[out] result - Receives one byte through the existing wider pointer type.
 */
int sceSblPmMgrGetProductModeForUser(int *result);

/**
 * Read the product-mode byte from NVS.
 *
 * @param[out] product_mode - Receives one byte.
 */
int sceSblPmMgrGetProductModeFromNVS(SceUInt8 *product_mode);

int sceSblPmMgrSetProductModeOffForUser(void);

/**
 * Set the CP activation key from the activation data managed by the service.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpActivationKey(void);

/**
 * Set the 32-bit CP physical RTC value and corresponding key.
 *
 * @param[in] rtc - New physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpRtcPhysicalAndKey(int rtc);

/**
 * Get the CP serial identifier.
 *
 * @param[out] serial_id - Receives exactly 0x80 bytes.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrGetCpSerialId(void *serial_id);

/**
 * Set the 32-bit CP physical RTC value.
 *
 * @param[in] rtc - New physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpRtcPhysicalForUser(int rtc);

/**
 * Get the 32-bit CP physical RTC value.
 *
 * @param[out] rtc - Receives the physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrGetCpRtcPhysicalForUser(int *rtc);

/**
 * Set the 32-bit CP logical RTC value.
 *
 * @param[in] rtc - New logical RTC value.
 *
 * @note FW 3.60 validates the value but does not set the RTC; it returns
 * 0x800F1025 for a valid value.
 */
int sceSblRtcMgrSetCpRtcLogical(int rtc);

/**
 * Get the 32-bit CP logical RTC value.
 *
 * @param[out] rtc - Receives the logical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrGetCpRtcLogical(int *rtc);

/**
 * Get the remaining validity time for the initialized Utoken.
 *
 * @param[out] remaining_seconds - Receives -1 when no validity deadline is
 * configured, 0 when the deadline has passed, or the number of seconds until
 * the deadline otherwise.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblUtMgrGetCurrentSecureTick(int *remaining_seconds);

/**
 * Copy the Utoken name.
 *
 * @param[out] name - Destination buffer.
 * @param[in] size - Destination size. At most 0x18 bytes are copied.
 */
int sceSblUtMgrIsTrilithiumFlagEnabled(char *name, SceSize size);

/**
 * Read and decrypt the persisted Utoken.
 *
 * @param[out] buf - Pointer to a ::SceUtoken buffer.
 * @param[in] size - Must be at least 0x800; exactly 0x800 bytes are written.
 */
int sceSblUtMgrReadUtoken(char *buf, SceSize size);

int sceSblUtMgrResetUtokenFile(void);

/**
 * Verify and persist an encrypted Utoken.
 *
 * @param[in] buf - Pointer to a ::SceUtoken buffer.
 * @param[in] size - Must be at least 0x800; exactly 0x800 bytes are consumed.
 */
int sceSblUtMgrUpdateUtoken(char *buf, SceSize size);

#define sceSblUtMgrGetUtName sceSblUtMgrIsTrilithiumFlagEnabled

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLPOSTSSMGR_H_ */
