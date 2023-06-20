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
 * @param[out]  act_exp_time    - The pointer of activation data expire time output
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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_NPDRM_H_ */
