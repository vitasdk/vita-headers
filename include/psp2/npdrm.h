/**
 * \usergroup{SceNpDrm}
 * \usage{psp2/npdrm.h,SceNpDrm_stub}
 */

#ifndef _PSP2_NPDRM_H_
#define _PSP2_NPDRM_H_

#include <psp2/types.h>
#include <stdint.h>

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
 * Get rif name
 *
 * @param[out] rif_name - RIF name buffer (48 bytes)
 *
 * @param[in] aid - Account ID
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetRifName(char *rif_name, uint64_t aid);

/**
 * Get fixed rif name
 *
 * @param[out] rif_name - RIF name buffer (48 bytes)
 *
 * @param[in] aid - Account ID
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetFixedRifName(char *rif_name, uint64_t aid);

/**
 * Get rif name for install
 *
 * @param[out] rif_name - RIF name buffer (48 bytes)
 *
 * @param[in] rif_data - Data of RIF file (512 bytes)
 *
 * @param[in] unk - Unknown, use 0
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetRifNameForInstall(char *rif_name, const void *rif_data, int unk);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NPDRM_H_ */
