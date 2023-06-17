/**
 * \usergroup{SceNpDrm}
 * \usage{psp2kern/npdrm.h,SceNpDrmForDriver_stub}
 */

#ifndef _PSP2KERN_NPDRM_H_
#define _PSP2KERN_NPDRM_H_

#include <psp2kern/types.h>
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
int ksceNpDrmGetRifVitaKey(const void *license, void *klicense, int *flags, int *sku_flags, SceUInt64 *lic_start_time, SceUInt64 *lic_exp_time);

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
int ksceNpDrmGetRifPspKey(const void *license, void *klicense, int *flags, SceUInt64 *lic_start_time, SceUInt64 *lic_exp_time);

/**
 * Get license info
 *
 * @param[in]  license         - The pointer of license data. see:SceNpDrmLicense
 * @param[in]  license_size    - The license data size. 0x200 etc
 * @param[in]  check_sign      - The license signature check flag. if pass 1, do check.
 * @param[out] content_id      - The pointer of license content_id output buffer. size is 0x30.
 * @param[out] account_id      - The pointer of license account_id output.
 * @param[out] license_version - The pointer of license version output.
 * @param[out] license_flags   - The pointer of license flags output.
 * @param[out] flags           - The pointer of flags output.
 * @param[out] sku_flags       - The pointer of sku flags output.
 * @param[out] lic_start_time  - The pointer of license start time output.
 * @param[out] lic_exp_time    - The pointer of license exp time output.
 * @param[out] flags2          - The pointer of flags2 output.
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmGetRifInfo(const void *license, SceSize license_size, int check_sign, char *content_id, SceUInt64 *account_id, int *license_version, int *license_flags, int *flags, int *sku_flags, SceInt64 *lic_start_time, SceInt64 *lic_exp_time, SceUInt64 *flags2);

/**
 * Generate eboot.pbp signature "__sce_ebootpbp" for a PSP game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x200
 * @param[in]  sw_version             - The minimum firmware version the signature can be used on. cannot be lower than current firmware
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmEbootSigGenPsp(const char *eboot_pbp_path, const void *eboot_sha256, void *eboot_signature, int sw_version);

/**
 * Generate eboot.pbp signature "__sce_ebootpbp" for a PS1 game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x200
 * @param[in]  sw_version             - The minimum firmware version the signature can be used on. cannot be lower than current firmware
 *
 * @return 0 on success, < 0 on error.
*/
int ksceNpDrmEbootSigGenPs1(const char *eboot_pbp_path, const void *eboot_sha256, void *eboot_signature, int sw_version);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_NPDRM_H_ */
