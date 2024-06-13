/**
 * \usergroup{SceNpDrm}
 * \usage{psp2/npdrm.h,SceNpDrm_stub}
 */

#ifndef _PSP2_NPDRM_H_
#define _PSP2_NPDRM_H_

#include <psp2/types.h>
#include <psp2common/npdrm.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  
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
 * Check you have npdrm activation data, and get information from it
 *
 * @param[out]  act_type        - The pointer of activation type output.
 *
 * @param[out]  version_flag    - The pointer of version flag output.
 *
 * @param[out]  account_id      - The pointer of activated account id output.
 *
 * @param[out]  act_exp_time    - The pointer of activation expire time output, [0] is start_date, [1] is end_date
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmCheckActData(int *act_type, int *version_flag, SceUInt64 *account_id, SceUInt64 act_exp_time[2]);

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
int _sceNpDrmGetRifNameForInstall(char *rif_name, const SceNpDrmLicense *rif_data, int unk);

/**
 * Get PSM rif key
 *
 * @param[in] license_buf - RIF buffer (1024 bytes)
 *
 * @param[out] keydata - Decrypted keyset
 *
 * @param[out] flags - License flags
 * 
 * @param[out] exp_time - Expire times output
 * 
 * @return 0 on success, < 0 on error
*/
int scePsmDrmGetRifKey(const ScePsmDrmLicense *license_buf, ScePsmDrmKeySet *keydata, int* flags, ScePsmDrmExpireTime* exp_time);

 
#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NPDRM_H_ */
