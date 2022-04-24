/**
 * \usergroup{SceNpDrm}
 * \usage{psp2kern/npdrm.h,SceNpDrmForDriver_stub}
 */

#ifndef _PSP2KERN_NPDRM_H_
#define _PSP2KERN_NPDRM_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceNpDrmLicense { // size is 0x200
  SceInt16 version;       // -1, 1
  SceInt16 version_flags; // 0, 1
  SceInt16 license_type;  // 1
  SceInt16 license_flags; // 0x400:non-check ecdsa
  SceUInt64 account_id;
  char content_id[0x30];
  char key_table[0x10];
  char key1[0x10];
  SceInt64 start_time;
  SceInt64 expiration_time;
  char ecdsa_signature[0x28];
  SceInt64 flags;
  char key2[0x10];
  char unk_0xB0[0x10];
  char open_psid[0x10];
  char unk_0xD0[0x10];
  char cmd56_handshake_part[0x14];
  int debug_upgradable;
  int unk_0xF8;
  int sku_flag;
  char rsa_signature[0x100];
} SceNpDrmLicense;

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_NPDRM_H_ */
