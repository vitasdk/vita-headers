/**
 * \usergroup{SceNpDrm}
 * \usage{psp2/npdrm.h,SceNpDrm_stub}
 */

#ifndef _PSP2_NPDRM_H_
#define _PSP2_NPDRM_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2/psmdrm.h>
#include <psp2common/npdrm.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  
/**
 * Get rif name
 *
 * @param[out] rif_name - Required RIF name buffer (48 bytes)
 *
 * @param[in] aid - Account ID
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetRifName(char *rif_name, uint64_t aid);

/**
 * Get fixed rif name
 *
 * @param[out] rif_name - Required RIF name buffer (48 bytes)
 *
 * @param[in] aid - Account ID
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetFixedRifName(char *rif_name, uint64_t aid);

/**
 * Check you have npdrm activation data, and get information from it
 *
 * @param[out]  act_type        - Optional activation type output.
 *
 * @param[out]  version_flag    - Optional activation version flag output.
 *
 * @param[out]  account_id      - Optional activated account ID output.
 *
 * @param[in]   opt             - Required pointer to a ::SceNpDrmCheckActDataOpt
 *                                structure, passed as a ::SceUInt64 pointer
 *                                for backwards compatibility. Both pointer
 *                                types have the same ABI.
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmCheckActData(int *act_type, int *version_flag, SceUInt64 *account_id, SceUInt64 opt[2]);

/**
 * Get rif name for install
 *
 * @param[out] rif_name - Required RIF name buffer (48 bytes)
 *
 * @param[in] rif_data - Required RIF data (512 bytes)
 *
 * @param[in] is_fixed - Set to 0 to derive the name from the RIF content ID,
 *                      or 1 to request the fixed account-based name
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetRifNameForInstall(char *rif_name, const SceNpDrmLicense *rif_data, int is_fixed);

typedef struct SceNpDrmCheckActDataOpt {
	SceRtcTick *act_start_time; //!< Optional activation start time output.
	SceRtcTick *act_exp_time; //!< Optional activation expiration time output.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceNpDrmCheckActDataOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceNpDrmCheckActDataOpt); // size is from FW 3.60

typedef struct SceNpDrmCheckDrmResetOpt {
	SceUInt64 account_id; //!< Account ID to compare with the current activation data.
	SceBool *reset; //!< Optional output set to ::SCE_TRUE if this call reset act.dat.
	SceSize input_copy_size; //!< Number of input bytes to copy; set to \a input_size and do not exceed 0x40.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceNpDrmCheckDrmResetOpt;
VITASDK_BUILD_ASSERT_EQ(0x18, SceNpDrmCheckDrmResetOpt); // size is from FW 3.60

/**
 * Optional outputs for ::_sceNpDrmGetRifInfo.
 *
 * On FW 3.60, \a flags receives a derived bit field: bit 0 is set when the
 * DRM type contains 0x2000 or the SKU flags equal 1, bit 1 mirrors the RIF
 * provisional flag, bit 16 denotes OpenPsId binding, and bit 17 denotes
 * game-card binding.
 */
typedef struct SceNpDrmGetRifInfoOpt {
	char *content_id; //!< Optional 0x30-byte content ID output buffer.
	SceUInt64 *account_id; //!< Optional license account ID output.
	SceUInt32 *license_version; //!< Optional license version output.
	SceUInt32 *drm_type; //!< Optional DRM type output.
	SceUInt32 *flags; //!< Optional derived license flags output.
	SceUInt32 *sku_flags; //!< Optional SKU flags output.
	SceRtcTick *lic_start_time; //!< Optional license start time output.
	SceRtcTick *lic_exp_time; //!< Optional license expiration time output.
	SceUInt64 *rif_data_0x98; //!< Optional raw 8-byte RIF field output.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceNpDrmGetRifInfoOpt;
VITASDK_BUILD_ASSERT_EQ(0x28, SceNpDrmGetRifInfoOpt); // size is from FW 3.60

/**
 * Check whether activation data must be reset
 *
 * @param[in] input - Required input data. If its first byte is zero, FW 3.60 returns
 *                    success without checking or resetting act.dat.
 * @param[in] input_size - Size of the input data; must be in the range [2, 0x40]
 * @param[in] opt - Required structure containing the account ID, optional
 *                   reset-result pointer, and input copy size. Set
 *                   \a input_copy_size to \a input_size.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceNpDrmCheckDrmReset(const void *input, SceSize input_size, const SceNpDrmCheckDrmResetOpt *opt);

/**
 * Get RIF information
 *
 * @param[in] license - Required RIF data (0x200 bytes)
 * @param[in] license_size - Size of the RIF data
 * @param[in] check_sign - Set to ::SCE_TRUE to check the RIF signature
 * @param[in] opt - Required option structure containing optional output pointers
 *
 * @return 0 on success, < 0 on error.
 */
int _sceNpDrmGetRifInfo(const SceNpDrmLicense *license, SceSize license_size, SceBool check_sign, const SceNpDrmGetRifInfoOpt *opt);

/**
 * Set the provisional flag in a RIF.
 *
 * The 0x200-byte RIF is modified in place. Its existing signature is validated
 * with the provisional bit normalized.
 *
 * @param[in,out] license - RIF to update
 *
 * @return 0 on success, < 0 on error.
 */
int _sceNpDrmPresetRifProvisionalFlag(SceNpDrmLicense *license);

/**
 * Remove tm0:/npdrm/act.dat and clear the cached activation data.
 *
 * @param[out] account_id - Optional account ID from the removed act.dat
 *
 * @return 0 on success, < 0 on error.
 */
int _sceNpDrmRemoveActData(SceUInt64 *account_id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NPDRM_H_ */
