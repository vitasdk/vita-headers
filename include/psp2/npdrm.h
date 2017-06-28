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

/**
 * Get rif name
 *
 * @param[out] rif_name - RIF name buffer (48 bytes)
 *
 * @param[in] unk - Unknown, use 0
 *
 * @param[in] aid - Account ID
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetRifName(char *rif_name, int unk, uint64_t aid);

/**
 * Get fixed rif name
 *
 * @param[out] rif_name - RIF name buffer (48 bytes)
 *
 * @param[in] unk - Unknown, use 0
 *
 * @param[in] aid - Account ID
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetFixedRifName(char *rif_name, int unk, uint64_t aid);

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

