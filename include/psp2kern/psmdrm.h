/**
 * \kernelgroup{ScePsmDrm}
 * \usage{psp2kern/psmdrm.h,ScePsmDrmForDriver_stub}
 */

#ifndef _PSP2KERN_PSMDRM_H_
#define _PSP2KERN_PSMDRM_H_

#include <psp2kern/types.h>
#include <psp2common/npdrm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get PSM activation information.
 *
 * @param[out] act_type - Optional activation type output
 * @param[out] version_flag - Optional activation version flag output
 * @param[out] account_id - Optional activated account ID output
 * @param[out] act_start_time - Optional activation start time output
 * @param[out] act_exp_time - Optional activation expiration time output
 *
 * @return 0 on success, < 0 on error.
 */
int kscePsmDrmGetActInfo(SceUInt32 *act_type, SceUInt32 *version_flag, SceUInt64 *account_id, SceRtcTick *act_start_time, SceRtcTick *act_exp_time);

/**
 * Get PSM RIF information.
 *
 * @param[in] license - Required PSM RIF data (0x400 bytes)
 * @param[out] content_id - Optional content ID buffer (0x30 bytes)
 * @param[out] account_id - Optional license account ID output
 * @param[out] lic_start_time - Optional license start time output
 * @param[out] lic_exp_time - Optional license expiration time output
 *
 * @return 0 on success, < 0 on error.
 */
int kscePsmDrmGetRifInfo(const ScePsmDrmLicense *license, char *content_id, SceUInt64 *account_id, SceRtcTick *lic_start_time, SceRtcTick *lic_exp_time);

/**
 * Get a PSM RIF key set and license information.
 *
 * @param[in] license - Required PSM RIF data (0x400 bytes)
 * @param[out] keydata - Required ::ScePsmDrmKeySet output
 * @param[out] version_flag - Optional activation version flag output
 * @param[out] lic_start_time - Optional license start time output
 * @param[out] lic_exp_time - Optional license expiration time output
 *
 * The returned start time is the later of the activation and license start
 * times. The returned expiration time is the earlier of their expiration
 * times.
 *
 * @return 0 on success, < 0 on error.
 */
int kscePsmDrmGetRifKey(const ScePsmDrmLicense *license, ScePsmDrmKeySet *keydata, SceUInt32 *version_flag, SceRtcTick *lic_start_time, SceRtcTick *lic_exp_time);

/**
 * Reload and validate tm0:/psmdrm/act.dat and refresh the cached activation
 * data.
 *
 * @return 0 on success, < 0 on error.
 */
int kscePsmDrmReadActData(void);

/**
 * Remove tm0:/psmdrm/act.dat and clear the cached PSM activation data.
 *
 * @param[out] account_id - Optional account ID from the removed activation data
 *
 * @return 0 on success, < 0 on error.
 */
int kscePsmDrmRemoveActData(SceUInt64 *account_id);

/**
 * Validate and install PSM activation data.
 *
 * @param[in] psm_act_data - PSM-ACT activation data (0x400 bytes)
 * @param[in] aes_dec_key - Optional 0x10-byte AES key used to decrypt the
 *                          activation data before validation
 *
 * @return 0 on success, < 0 on error.
 */
int kscePsmDrmWriteActData(const void *psm_act_data, const void *aes_dec_key);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_PSMDRM_H_ */
