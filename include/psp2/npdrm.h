/**
 * \usergroup{SceNpDrm}
 * \usage{psp2/npdrm.h,SceNpDrm_stub}
 */

#ifndef _PSP2_NPDRM_H_
#define _PSP2_NPDRM_H_

#include <vitasdk/build_utils.h>
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
 * @param[in]   opt             - Points to the layout described by
 *                                ::SceNpDrmCheckActDataOpt. The ABI-equivalent
 *                                ::SceUInt64 pointer type is retained for
 *                                backwards compatibility.
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmCheckActData(int *act_type, int *version_flag, SceUInt64 *account_id, SceUInt64 opt[2]);

/**
 * Get rif name for install
 *
 * @param[out] rif_name - RIF name buffer (48 bytes)
 *
 * @param[in] rif_data - Data of RIF file (512 bytes)
 *
 * @param[in] is_fixed - Set to 0 to derive the name from the RIF content ID,
 *                      or 1 to request the fixed account-based name
 *
 * @return 0 on success, < 0 on error.
*/
int _sceNpDrmGetRifNameForInstall(char *rif_name, const SceNpDrmLicense *rif_data, int is_fixed);

/**
 * Get PSM rif key
 *
 * @param[in] license_buf - RIF buffer (1024 bytes)
 *
 * @param[out] keydata - Decrypted keyset
 *
 * @param[out] version_flag - Activation version flag
 * 
 * @param[in] exp_time - Structure containing license start and expiration time
 *                       output pointers
 * 
 * @return 0 on success, < 0 on error
*/
int scePsmDrmGetRifKey(const ScePsmDrmLicense *license_buf, ScePsmDrmKeySet *keydata, int *version_flag, ScePsmDrmExpireTime *exp_time);

 
typedef struct SceNpDrmCheckActDataOpt {
	SceUInt64 *act_start_time; //!< Activation start time output.
	SceUInt64 *act_exp_time; //!< Activation expiration time output.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceNpDrmCheckActDataOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceNpDrmCheckActDataOpt); // size is from FW 3.60

typedef SceNpDrmCheckActDataOpt ScePsmDrmGetActInfoOpt;

typedef struct SceNpDrmCheckDrmResetOpt {
	SceUInt64 account_id;
	SceBool *pReset; //!< Set to ::SCE_TRUE if act.dat was reset during the function call.
	SceSize in_size; //!< Number of input bytes to copy; must not exceed 0x40.
	SceUInt64 reserved; //!< Ignored on FW 3.60.
} SceNpDrmCheckDrmResetOpt;
VITASDK_BUILD_ASSERT_EQ(0x18, SceNpDrmCheckDrmResetOpt); // size is from FW 3.60

typedef struct ScePsmDrmGetRifInfoOpt {
	SceUInt64 *lic_start_time; //!< License start time output.
	SceUInt64 *lic_exp_time; //!< License expiration time output.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} ScePsmDrmGetRifInfoOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, ScePsmDrmGetRifInfoOpt); // size is from FW 3.60

typedef struct _sceNpDrmGetRifInfo_opt {
	void *content_id; //!< A pointer to a 0x30-byte content ID buffer.
	void *account_id; //!< A pointer to a ::SceUInt64.
	void *version_number; //!< A pointer to a ::SceUInt32.
	void *license_flags; //!< A pointer to a ::SceUInt32.
	void *lic_type0; //!< A pointer to a ::SceUInt32.
	void *lic_type1; //!< A pointer to a ::SceUInt32.
	void *lic_start_time; //!< A pointer to a ::SceUInt64.
	void *lic_exp_time; //!< A pointer to a ::SceUInt64.
	void *rif_data_0x98; //!< A pointer to an 8-byte output buffer.
	void *reserved; //!< Ignored on FW 3.60.
} _sceNpDrmGetRifInfo_opt;
VITASDK_BUILD_ASSERT_EQ(0x28, _sceNpDrmGetRifInfo_opt); // size is from FW 3.60

/**
 * Check whether activation data must be reset
 *
 * @param[in] input - Input data. If its first byte is zero, FW 3.60 returns
 *                    success without checking or resetting act.dat.
 * @param[in] input_size - Size of the input data; must be in the range [2, 0x40]
 * @param[in] pOpt - Account ID, reset-result pointer, and input copy size
 *
 * @return 0 on success, < 0 on error.
 */
int _sceNpDrmCheckDrmReset(const void *input, SceSize input_size, SceNpDrmCheckDrmResetOpt *pOpt);

/**
 * Get RIF information
 *
 * @param[in] license - RIF data
 * @param[in] license_size - Size of the RIF data
 * @param[in] check_sign - Set to 1 to check the RIF signature
 * @param[in] pOpt - Output pointers
 *
 * @return 0 on success, < 0 on error.
 */
int _sceNpDrmGetRifInfo(void *license, SceSize license_size, SceUInt32 check_sign, _sceNpDrmGetRifInfo_opt *pOpt);

int _sceNpDrmPresetRifProvisionalFlag(void *license);
int _sceNpDrmRemoveActData(SceUInt64 *pAccountId);

/**
 * Get PSM activation information
 *
 * @param[out] act_type - Activation type
 * @param[out] version_flag - Activation version flag
 * @param[out] account_id - Activated account ID
 * @param[in] pOpt - Activation start and expiration time output pointers
 *
 * @return 0 on success, < 0 on error.
 */
int scePsmDrmGetActInfo(SceUInt32 *act_type, SceUInt32 *version_flag, SceUInt64 *account_id, ScePsmDrmGetActInfoOpt *pOpt);

/**
 * Get PSM RIF information
 *
 * @param[in] license - PSM RIF data
 * @param[out] content_id - Content ID buffer (0x30 bytes)
 * @param[out] account_id - A pointer to a ::SceUInt64
 * @param[in] pOpt - License start and expiration time output pointers
 *
 * @return 0 on success, < 0 on error.
 */
int scePsmDrmGetRifInfo(void *license, char *content_id, void *account_id, ScePsmDrmGetRifInfoOpt *pOpt);
int scePsmDrmGetRifName(char *rif_name);
int scePsmDrmGetRifNameForInstall(char *rif_name, const void *license);
int scePsmDrmRemoveActData(SceUInt64 *pAccountId);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NPDRM_H_ */
