/**
 * \kernelgroup{SceNpDrm}
 * \usage{psp2kern/npdrm.h,SceNpDrmForDriver_stub}
 */

#ifndef _PSP2KERN_NPDRM_H_
#define _PSP2KERN_NPDRM_H_

#include <psp2kern/types.h>
#include <psp2kern/psmdrm.h>
#include <psp2common/npdrm.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Get license file name
 *
 * @param[out] name - The pointer of license file name output buffer. size is 0x30.
 * @param[in]  aid  - The license account id
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmGetRifName(char *name, SceUInt64 aid);

/**
 * Get license file name with fixed
 *
 * @param[out] name - The pointer of license file name output buffer. size is 0x30.
 * @param[in]  aid  - The license account id
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmGetFixedRifName(char *name, SceUInt64 aid);

/**
 * Get current activation data
 *
 * @param[out] act_data       - The pointer of output activation data see:SceNpDrmActivationData. if ecdsa or rsa verify fail, will be all 0.
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmReadActData(SceNpDrmActivationData *act_data);

/**
 * Check you have npdrm activation data, and get information from it
 *
 * @param[out]  act_type        - The pointer of activation type output.
 * @param[out]  version_flag    - The pointer of version flag output.
 * @param[out]  account_id      - The pointer of activated account id output.
 * @param[out]  act_start_time  - The pointer of activation data start time output.
 * @param[out]  act_end_time    - Activation data expiration time output.
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmCheckActData(int *act_type, int *version_flag, SceUInt64 *account_id, SceUInt64 *act_start_time, SceUInt64 *act_end_time);

/**
 * Get license key info
 *
 * @param[in]  license        - The pointer of license data. see:SceNpDrmLicense
 * @param[out] klicense       - The pointer of klicense output buffer. size is 0x10.
 * @param[out] flags          - The pointer of flags output.
 * @param[out] sku_flags      - The pointer of sku flags output.
 * @param[out] lic_start_time - The pointer of license start time output.
 * @param[out] lic_exp_time   - The pointer of license exp time output.
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmGetRifVitaKey(const SceNpDrmLicense *license, void *klicense, int *flags, int *sku_flags, SceUInt64 *lic_start_time, SceUInt64 *lic_exp_time);

/**
 * Get license key info for a PSP game
 *
 * @param[in]  license        - The pointer of license data. see:SceNpDrmLicense
 * @param[out] klicense       - The pointer of klicense output buffer. size is 0x10.
 * @param[out] flags          - The pointer of flags output.
 * @param[out] lic_start_time - The pointer of license start time output.
 * @param[out] lic_exp_time   - The pointer of license exp time output.
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmGetRifPspKey(const SceNpDrmLicense *license, void *klicense, int *flags, SceUInt64 *lic_start_time, SceUInt64 *lic_exp_time);

/**
 * Get license info
 *
 * @param[in]  license         - Required ::SceNpDrmLicense structure.
 * @param[in]  license_size    - Set to 0x200. FW 3.60 still reads the complete
 *                               RIF when a smaller value is supplied.
 * @param[in]  check_sign      - Set to 1 to check the RIF signature.
 * @param[out] content_id      - Optional 0x30-byte content ID output buffer.
 * @param[out] account_id      - Optional license account ID output.
 * @param[out] license_version - Optional license version output; receives a
 *                               ::SceUInt32 value.
 * @param[out] drm_type        - Optional DRM type output; receives a
 *                               ::SceUInt32 value.
 * @param[out] flags           - Optional derived license flags output.
 * @param[out] sku_flags       - Optional SKU flags output.
 * @param[out] lic_start_time  - Optional license start time output; receives a
 *                               ::SceRtcTick value.
 * @param[out] lic_exp_time    - Optional license expiration time output;
 *                               receives a ::SceRtcTick value.
 * @param[out] rif_data_0x98   - Optional raw 8-byte RIF field output.
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmGetRifInfo(const SceNpDrmLicense *license, SceSize license_size, int check_sign, char *content_id, SceUInt64 *account_id, int *license_version, int *drm_type, int *flags, int *sku_flags, SceInt64 *lic_start_time, SceInt64 *lic_exp_time, SceUInt64 *rif_data_0x98);

/**
 * Verify a eboot.pbp signature "__sce_ebootpbp"
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_signature        - The pointer of data of __sce_ebootpbp signature. size is 0x200
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmEbootSigVerify(const char *eboot_pbp_path, const void *eboot_signature);

/**
 * Verify an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" from firmware <2.00
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_signature        - The pointer of data of __sce_ebootpbp signature. size is 0x100
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmPspEbootVerify(const char *eboot_pbp_path, const void *eboot_signature);

/**
 * Generate an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" for a PSP game - this is unused in firmware >2.00
 * 
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x100
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int ksceNpDrmPspEbootSigGen(const char *eboot_pbp_path, const void *eboot_sha256, void *eboot_signature);

/**
 * Convert an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" to a 0x200 byte one used in firmwares >2.00
 * 
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  old_eboot_signature    - The pointer of old eboot signature data. size is 0x100
 * @param[out] new_eboot_signature    - The pointer of new eboot signature data. size is 0x200
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int ksceNpDrmEbootSigConvert(const char *eboot_pbp_path, const void* old_eboot_signature, void* new_eboot_signature); 

/**
 * Generate eboot.pbp signature "__sce_ebootpbp" for a PSP game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x200
 * @param[in]  sw_version             - The minimum firmware version the signature can be used on. cannot be lower than current firmware
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int ksceNpDrmEbootSigGenPsp(const char *eboot_pbp_path, const void *eboot_sha256, void *eboot_signature, int sw_version);

/**
 * Generate eboot.pbp signature "__sce_ebootpbp" for a single-disc PS1 game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x200
 * @param[in]  sw_version             - The minimum firmware version the signature can be used on. cannot be lower than current firmware
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int ksceNpDrmEbootSigGenPs1(const char *eboot_pbp_path, const void *eboot_sha256, void *eboot_signature, int sw_version);

/**
 * Generate eboot.pbp signature "__sce_discinfo" for a multi-disc PS1 game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  sce_discinfo           - The pointer of contents of vs0:/app/NPXS10028/__sce_discinfo
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x100
 * @param[in]  sw_version             - The minimum firmware version the signature can be used on. cannot be lower than current firmware
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int ksceNpDrmEbootSigGenMultiDisc(const char *eboot_pbp_path, const void *sce_discinfo, void *eboot_signature, int sw_version);

/**
 * Get a legacy PSP document key
 *
 * @param[in] rif - RIF data. This is only read when required by the document header.
 * @param[in] doc_edat - Required document EDAT data with a PSPEDAT header; at least 0x90 bytes
 * @param[in] doc_edat_size - Size of the document EDAT data
 * @param[out] legacy_doc_key - Required legacy document key output buffer (0x10 bytes)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmGetLegacyDocKey(const void *rif, const void *doc_edat, SceSize doc_edat_size, void *legacy_doc_key);

/**
 * Get a RIF name for installation
 *
 * @param[out] rif_name - Required RIF name buffer (0x30 bytes)
 * @param[in] license - Required ::SceNpDrmLicense structure
 * @param[in] is_fixed - Set to 0 to derive the name from the RIF content ID,
 *                       or 1 to request the fixed account-based name
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmGetRifNameForInstall(char *rif_name, const SceNpDrmLicense *license, SceBool is_fixed);

/** @return ::SCE_TRUE when loose account binding is enabled, otherwise ::SCE_FALSE. */
SceBool ksceNpDrmIsLooseAccountBind(void);

/**
 * Set whether package game content exists
 *
 * FW 3.60 stores the value unchanged. Observed AppMgr callers use 0 or 1.
 *
 * @param[in] game_exists - Value indicating whether package game content exists
 *
 * @return 0.
 */
int ksceNpDrmPackageSetGameExist(SceBool game_exists);

/**
 * Set or clear a RIF's provisional flag.
 *
 * The existing signature is validated with the provisional bit normalized.
 *
 * @param[in,out] license - RIF to update
 * @param[in] enable - ::SCE_TRUE to set the provisional flag, or ::SCE_FALSE
 *                     to clear it
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmPresetRifProvisionalFlag(SceNpDrmLicense *license, SceBool enable);

/**
 * Remove tm0:/npdrm/act.dat and clear the cached activation data.
 *
 * @param[out] account_id - Optional account ID from the removed activation data
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmRemoveActData(SceUInt64 *account_id);

/**
 * Update the cached NP account ID.
 *
 * A zero value reloads the account ID from the registry.
 *
 * @param[in] account_id - Account ID to cache, or 0 to reload it from the
 *                         registry
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmUpdateAccountId(SceUInt64 account_id);

/**
 * Reload and validate tm0:/npdrm/act.dat and refresh the cached activation
 * keys.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmUpdateActData(void);

/**
 * Refresh the cached NPDRM debug and loose-account-binding settings.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmUpdateDebugSettings(void);

/**
 * Verify a RIF signature.
 *
 * @param[in] license - Required RIF data (0x200 bytes)
 * @param[in] license_size - Set to 0x200. FW 3.60 still reads the complete RIF
 *                           when a smaller value is supplied.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmVerifyRif(const SceNpDrmLicense *license, SceSize license_size);

/**
 * Fully validate a RIF and update it in place.
 *
 * On FW 3.60, the function may decrypt and move the RIF key and clear the
 * trailing RIF fields on success.
 *
 * @param[in,out] license - Required RIF data (0x200 bytes)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmVerifyRifFull(SceNpDrmLicense *license);

/**
 * Validate and install NPDRM activation data.
 *
 * @param[in] npdrm_act_data - Activation data (0x1040 bytes)
 * @param[in] aes_dec_key - Optional 0x10-byte AES key used to decrypt the
 *                          activation data before validation
 *
 * @return 0 on success, < 0 on error.
 */
int ksceNpDrmWriteActData(const void *npdrm_act_data, const void *aes_dec_key);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_NPDRM_H_ */
