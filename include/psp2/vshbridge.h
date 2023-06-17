/**
 * \usergroup{SceVshBridge}
 * \usage{psp2/vshbridge.h,SceVshBridge_stub}
 */

#ifndef _PSP2_VSHBRIDGE_H_
#define _PSP2_VSHBRIDGE_H_

#include <psp2common/kernel/msif.h>
#include <psp2/types.h>
#include <psp2/kernel/modulemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets real system firmware information.
 *
 * @param[out] data - firmware information.
 */
int _vshSblGetSystemSwVersion(SceKernelFwInfo *data);

/**
 * @brief Get service/manufacturing information (factory/minimum firmware).
 *
 * @param[out] info - The info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int _vshSblAimgrGetSMI(SceUInt32 *info);

int _vshSblAimgrGetConsoleId(char CID[32]);

/**
 * @brief Check if a module is loaded.
 *
 * @param[in] module_name - The module's name
 * @param[in] buffer - Set a buffer with a size of 8 bytes
 *
 * @return the SceUID of the module on success, < 0 on error.
 */
SceUID _vshKernelSearchModuleByName(const char *module_name, const void *buffer);

/**
 * @param[in] id - mount id
 * @param[in] path - mount path
 * @param[in] permission - 1/RO 2/RW
 * @param[in] buf - work buffer
 *
 * @return 0 >= on success, < 0 on error.
 */
int _vshIoMount(int id, const char *path, int permission, void *buf);


/**
 * @param[in] id - mount id
 * @param[in] force - Set to 1 to force umount
 * @param[in] unk2 - Unknown, set 0
 * @param[in] unk3 - Unknown, set 0
 *
 * @return 0 >= on success, < 0 on error.
 */
int vshIoUmount(int id, int force, int unk2, int unk3);

int vshIdStorageIsDirty(void);
int vshIdStorageIsFormatted(void);
int vshIdStorageIsReadOnly(void);

/**
 * @param[in]  leafnum - The read target leaf number
 * @param[out] buf     - The leaf data buffer pointer, size is 512 byte
 *
 * @return 0 on success, < 0 on error.
 */
int vshIdStorageReadLeaf(SceSize leafnum, void *buf);

/**
 * @param[in] leafnum - The write target leaf number
 * @param[in] buf     - The leaf data buffer pointer, size is 512 byte
 *
 * @return 0 on success, < 0 on error.
 *
 * note - Writing to leaf requires manufacturing mode.
 */
int vshIdStorageWriteLeaf(SceSize leafnum, const void *buf);

/**
 * Verify a eboot.pbp signature "__sce_ebootpbp"
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_signature        - The pointer of data of __sce_ebootpbp signature. size is 0x200
 *
 * @return 0 on success, < 0 on error.
*/
int _vshNpDrmEbootSigVerify(const char *eboot_pbp_path, const char *eboot_signature);

/**
 * Verify an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" from firmware <2.00
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_signature        - The pointer of data of __sce_ebootpbp signature. size is 0x100
 *
 * @return 0 on success, < 0 on error.
*/
int _vshNpDrmPspEbootVerify(const char *eboot_pbp_path, const char *eboot_signature);

/**
 * Generate an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" for a PSP game - this is unused in firmware >2.00
 * 
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x100
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int _vshNpDrmPspEbootSigGen(const char *eboot_pbp_path, const void *eboot_sha256, void *eboot_signature);

/**
 * Convert an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" to a 0x200 byte one used in firmwares >2.00
 * 
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  old_eboot_signature    - The pointer of old eboot signature data. size is 0x100
 * @param[out] new_eboot_signature    - The pointer of new eboot signature data. size is 0x200
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int _vshNpDrmEbootSigConvert(const char *eboot_pbp_path, const void* old_eboot_signature, void* new_eboot_signature); 


/**
 * Generate eboot.pbp signature "__sce_ebootpbp" for a PSP game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x200
 * @param[in]  sw_version             - The pointer of the minimum firmware version the signature can be used on. cannot be lower than current firmware
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int _vshNpDrmEbootSigGenPsp(const char *eboot_pbp_path, const void* eboot_sha256, void *eboot_signature, int *sw_version);


/**
 * Generate eboot.pbp signature "__sce_ebootpbp" for a single-disc PS1 game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x200
 * @param[in]  sw_version             - The pointer of the minimum firmware version the signature can be used on. cannot be lower than current firmware
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int _vshNpDrmEbootSigGenPs1(const char *eboot_pbp_path, const void *eboot_sha256, void *eboot_signature, int *sw_version);

/**
 * Generate eboot.pbp signature "__sce_ebootpbp" for a multi-disc PS1 game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  sce_discinfo           - The pointer of contents of vs0:/app/NPXS10028/__sce_discinfo
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x200
 * @param[in]  sw_version             - The pointer of the minimum firmware version the signature can be used on. cannot be lower than current firmware
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int _vshNpDrmEbootSigGenMultiDisc(const char *eboot_pbp_path, const void *sce_discinfo, void *eboot_signature, int *sw_version);

int vshSblAimgrIsCEX(void);
int vshSblAimgrIsDEX(void);
int vshSblAimgrIsVITA(void);
int vshSblAimgrIsGenuineVITA(void);
int vshSblAimgrIsDolce(void);
int vshSblAimgrIsGenuineDolce(void);
int vshSblAimgrIsTest(void);
int vshSblAimgrIsTool(void);
int vshSblSsIsDevelopmentMode(void);

int vshSysconHasWWAN(void);

int vshSysconIsDownLoaderMode(void);
int vshSysconIsIduMode(void);
int vshSysconIsMCEmuCapable(void);
int vshSysconIsShowMode(void);

int vshSysconIduModeSet(void);
int vshSysconIduModeClear(void);

int vshSysconShowModeSet(void);
int vshSysconShowModeClear(void);

int vshMemoryCardGetCardInsertState(void);
int vshRemovableMemoryGetCardInsertState(void);

int vshMsifGetMsInfo(SceMsInfo *info);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_VSHBRIDGE_H_ */
