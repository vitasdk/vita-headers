/**
 * \usergroup{ScePsmDrm}
 * \usage{psp2/psmdrm.h,SceNpDrm_stub}
 */

#ifndef _PSP2_PSMDRM_H_
#define _PSP2_PSMDRM_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/npdrm.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScePsmDrmGetActInfoOpt {
	SceRtcTick *act_start_time; //!< Optional activation start time output.
	SceRtcTick *act_exp_time; //!< Optional activation expiration time output.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} ScePsmDrmGetActInfoOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, ScePsmDrmGetActInfoOpt); // size is from FW 3.60

typedef struct ScePsmDrmGetRifInfoOpt {
	SceRtcTick *lic_start_time; //!< Optional license start time output.
	SceRtcTick *lic_exp_time; //!< Optional license expiration time output.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} ScePsmDrmGetRifInfoOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, ScePsmDrmGetRifInfoOpt); // size is from FW 3.60

/**
 * Get a PSM RIF key set.
 *
 * This function is restricted to a PSM runtime process on FW 3.60.
 *
 * @param[in] license_buf - Required RIF buffer (0x400 bytes)
 * @param[out] keydata - Required decrypted key set output
 * @param[out] version_flag - Optional activation version flag output; receives
 *                            a ::SceUInt32 value.
 * @param[in] exp_time - Required structure containing optional license start
 *                       and expiration time output pointers. The structure
 *                       itself is not modified, but remains non-const for
 *                       backwards compatibility.
 *
 * The returned start time is the later of the activation and license start
 * times. The returned expiration time is the earlier of their expiration
 * times.
 *
 * @return 0 on success, < 0 on error.
 */
int scePsmDrmGetRifKey(const ScePsmDrmLicense *license_buf, ScePsmDrmKeySet *keydata, int *version_flag, ScePsmDrmExpireTime *exp_time);

/**
 * Get PSM activation information.
 *
 * @param[out] act_type - Optional activation type output
 * @param[out] version_flag - Optional activation version flag output
 * @param[out] account_id - Optional activated account ID output
 * @param[in] opt - Required structure containing optional activation start
 *                   and expiration time output pointers
 *
 * @return 0 on success, < 0 on error.
 */
int scePsmDrmGetActInfo(SceUInt32 *act_type, SceUInt32 *version_flag, SceUInt64 *account_id, const ScePsmDrmGetActInfoOpt *opt);

/**
 * Get PSM RIF information.
 *
 * @param[in] license - Required PSM RIF data (0x400 bytes)
 * @param[out] content_id - Optional content ID buffer (0x30 bytes)
 * @param[out] account_id - Optional license account ID output
 * @param[in] opt - Required structure containing optional license start and
 *                   expiration time output pointers
 *
 * @return 0 on success, < 0 on error.
 */
int scePsmDrmGetRifInfo(const ScePsmDrmLicense *license, char *content_id, SceUInt64 *account_id, const ScePsmDrmGetRifInfoOpt *opt);

/**
 * Get the fixed PSM RIF name.
 *
 * @param[out] rif_name - Required RIF name buffer (0x30 bytes)
 *
 * @return 0 on success, < 0 on error.
 */
int scePsmDrmGetRifName(char *rif_name);

/**
 * Get the installation name for a PSM RIF.
 *
 * @param[out] rif_name - Required RIF name buffer (0x30 bytes)
 * @param[in] license - Required PSM RIF data (0x400 bytes)
 *
 * @return 0 on success, < 0 on error.
 */
int scePsmDrmGetRifNameForInstall(char *rif_name, const ScePsmDrmLicense *license);

/**
 * Remove tm0:/psmdrm/act.dat and clear the cached PSM activation data.
 *
 * @param[out] account_id - Optional account ID from the removed act.dat
 *
 * @return 0 on success, < 0 on error.
 */
int scePsmDrmRemoveActData(SceUInt64 *account_id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PSMDRM_H_ */
