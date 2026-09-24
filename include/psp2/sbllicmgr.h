/**
 * \usergroup{SceSblLicMgr}
 * \usage{psp2/sbllicmgr.h,SceSblLicMgr_stub}
 */

#ifndef _PSP2_SBLLICMGR_H_
#define _PSP2_SBLLICMGR_H_

#include <psp2/types.h>
#include <psp2common/sblpostssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Activate a development or testing kit from an AFV file.
 *
 * This operation is restricted to system programs. FW 3.60 copies at most
 * 255 path bytes and accepts paths under `host0:`, `ux0:/data/activate/`, and
 * `ur0:/temp/activation`. A successful installation does not recalculate the
 * cached license state.
 *
 * @param[in] afv_path - NUL-terminated activation-file path.
 *
 * @return SCE_OK on success, or a negative error code.
 */
int sceSblLicMgrActivateDevkit(const char *afv_path);

/**
 * Activate from the first `.afv` file in `ux0:/data/activate/`.
 *
 * This operation is restricted to system programs. A successful installation
 * does not recalculate the cached license state.
 *
 * @return SCE_OK on success, or a negative error code.
 */
int sceSblLicMgrActivateFromFs(void);

/**
 * Clear activation data in NVS and in `tm0:activate/`.
 *
 * FW 3.60 overwrites the stored data with 0xFF bytes rather than removing the
 * two activation files. It does not recalculate the cached license
 * state. This operation is restricted to system programs.
 *
 * @return SCE_OK on success, or a negative error code.
 */
int sceSblLicMgrClearActivationData(void);

/**
 * Get the console activation key.
 *
 * This operation is restricted to system programs.
 *
 * @param[out] key - Receives the OpenPSID and its four-lane byte-sum hash.
 *
 * @return SCE_OK on success, or a negative error code.
 */
int sceSblLicMgrGetActivationKey(SceSblActivationKey *key);

/**
 * Get the cached expiration time or the remaining activation time.
 *
 * This operation is restricted to system programs. When \a read_from_nvs is
 * zero, FW 3.60 writes the cached absolute expiration time to \a expire_date.
 * When it is nonzero, FW 3.60 reads and verifies NVS and writes the number of
 * seconds remaining to \a expire_date.
 *
 * @param[out] expire_date - Receives the expiration result described above.
 * @param[in] read_from_nvs - Nonzero to refresh from NVS; zero uses the cache.
 *
 * @return SCE_OK on success, or a negative error code.
 */
int sceSblLicMgrGetExpireDate(int *expire_date, SceBool read_from_nvs);

/**
 * Get the activation issue number.
 *
 * This operation is restricted to system programs.
 *
 * @param[out] issue_number - Receives the issue number.
 * @param[in] read_from_nvs - Nonzero to refresh from NVS; zero uses the cache.
 *
 * @return SCE_OK on success, or a negative error code.
 */
int sceSblLicMgrGetIssueNo(int *issue_number, SceBool read_from_nvs);

/**
 * Get the cached activation state.
 *
 * @return A ::SceSblLicenseStatus value, or a negative permission error.
 */
int sceSblLicMgrGetLicenseStatus(void);

/**
 * Get the kit's remaining activation time in seconds.
 *
 * On success, a zero value in \a time_limit means the kit has expired. This
 * operation is restricted to system programs. When any QAF flag is set, FW
 * 3.60 writes the bitwise complement of the current secure Unix time to
 * \a time_limit as an effectively unrestricted value instead of the normal
 * expiration interval.
 *
 * @param[out] time_limit - Receives the remaining number of seconds.
 *
 * @return SCE_OK on success, 0x800F1326 when not activated, 0x800F1329 when
 *         the RTC backup battery has failed, 0x80251002 when the current time
 *         cannot be established, or another negative error code.
 */
int sceSblLicMgrGetUsageTimeLimit(SceUInt32 *time_limit);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLLICMGR_H_ */
