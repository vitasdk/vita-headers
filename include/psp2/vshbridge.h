/**
 * \usergroup{SceVshBridge}
 * \usage{psp2/vshbridge.h,SceVshBridge_stub}
 */

#ifndef _PSP2_VSHBRIDGE_H_
#define _PSP2_VSHBRIDGE_H_

#include <vitasdk/build_utils.h>
#include <psp2common/appmgr.h>
#include <psp2common/kernel/msif.h>
#include <psp2/types.h>
#include <psp2common/sblssmgr.h>
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/kernel/modulemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceVshMountId {
    SCE_VSH_MOUNT_SD0  = 0x00100,
    SCE_VSH_MOUNT_OS0  = 0x00200,
    SCE_VSH_MOUNT_VS0  = 0x00300,
    SCE_VSH_MOUNT_VD0  = 0x00400,
    SCE_VSH_MOUNT_TM0  = 0x00500,
    SCE_VSH_MOUNT_UR0  = 0x00600,
    SCE_VSH_MOUNT_UD0  = 0x00700,
    SCE_VSH_MOUNT_UX0  = 0x00800,
    SCE_VSH_MOUNT_GRO0 = 0x00900,
    SCE_VSH_MOUNT_GRW0 = 0x00A00,
    SCE_VSH_MOUNT_SA0  = 0x00B00,
    SCE_VSH_MOUNT_PD0  = 0x00C00,
    SCE_VSH_MOUNT_IMC0 = 0x00D00,
    SCE_VSH_MOUNT_XMC0 = 0x00E00,
    SCE_VSH_MOUNT_UMA0 = 0x00F00,
    SCE_VSH_MOUNT_LMA0 = 0x10000,
    SCE_VSH_MOUNT_LMB0 = 0x20000,
    SCE_VSH_MOUNT_MFA0 = 0x50000,
    SCE_VSH_MOUNT_MFB0 = 0x60000,
} SceVshMountId;

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

/**
 * Get the console identifier.
 *
 * @param[out] console_id - Receives 16 bytes with the layout of ::SceConsoleId.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, < 0 on error.
 */
int _vshSblAimgrGetConsoleId(char console_id[0x10]);

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
 * @brief Mount a partition.
 *
 * @param[in] id - Mount ID (one of ::SceVshMountId).
 * @param[in] path - Mount path (optional, can be NULL).
 * @param[in] permission - `1` for read-only, `2` for read-write.
 * @param[in] buf - Work buffer. Allocate `0x100` and (important!) fill with `0`.
 *
 * @return `>= 0` on success, `< 0` on error.
 */
int _vshIoMount(SceVshMountId id, const char *path, int permission, void *buf);

/**
 * @brief Unmount a partition.
 *
 * @warning Unmounting system partitions can cause system instability, even if
 *          you remount them back. For example, FIOS overlays used by the Shell
 *          won't get recreated and would effectively render the Shell unusable
 *
 * @param[in] id - Mount ID (one of ::SceVshMountId).
 * @param[in] force - `1` to force unmount, `0` otherwise.
 * @param[in] unk2 - Unknown, set to `0`.
 * @param[in] unk3 - Unknown, set to `0`.
 *
 * @return `>= 0` on success, `< 0` on error.
 */
int vshIoUmount(SceVshMountId id, int force, int unk2, int unk3);

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
 * @param[in]  eboot_signature_magic  - The pointer of a pointer of magic number within __sce_ebootpbp, "NPUMDSIG" or "PSISOSIG"
 *
 * @return 0 on success, < 0 on error.
*/
int _vshNpDrmEbootSigVerify(const char *eboot_pbp_path, const char *eboot_signature, char** eboot_signature_header);

/**
 * Verify an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" from firmware <2.00
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_signature        - The pointer of data of __sce_ebootpbp signature. size is 0x100
 * @param[in]  eboot_signature_magic  - The pointer of a pointer of magic number within __sce_ebootpbp, "NPUMDSIG" or "PSISOSIG"
 *
 * @return 0 on success, < 0 on error.
*/
int _vshNpDrmPspEbootVerify(const char *eboot_pbp_path, const char *eboot_signature, char** eboot_signature_header);

/** FW 3.60 copies the entire option block but ignores its contents. */
typedef struct SceVshNpDrmEbootSigOpt {
	SceUInt32 reserved[2];
} SceVshNpDrmEbootSigOpt;
VITASDK_BUILD_ASSERT_EQ(8, SceVshNpDrmEbootSigOpt);

/**
 * Generate an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" for a PSP game - this is unused in firmware >2.00
 * 
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  eboot_sha256           - The pointer of SHA256 hash of first (data.psar offset + 0x1C0000) bytes into the EBOOT.PBP file
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x100
 * @param[in]  opt                    - Required 8-byte option block; ignored after being copied on FW 3.60.
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int _vshNpDrmPspEbootSigGen(const char *eboot_pbp_path, const void *eboot_sha256, void *eboot_signature, const SceVshNpDrmEbootSigOpt *opt);

/**
 * Convert an older 0x100 byte eboot.pbp signature "__sce_ebootpbp" to a 0x200 byte one used in firmwares >2.00
 * 
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  old_eboot_signature    - The pointer of old eboot signature data. size is 0x100
 * @param[out] new_eboot_signature    - The pointer of new eboot signature data. size is 0x200
 * @param[in]  opt                    - Required 8-byte option block; ignored after being copied on FW 3.60.
 *
 * @return eboot_signature size on success, < 0 on error.
*/
int _vshNpDrmEbootSigConvert(const char *eboot_pbp_path, const void *old_eboot_signature, void *new_eboot_signature, const SceVshNpDrmEbootSigOpt *opt);


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
 * Generate eboot.pbp signature "__sce_discinfo" for a multi-disc PS1 game
 *
 * @param[in]  eboot_pbp_path         - The pointer of the file path of the EBOOT.PBP file
 * @param[in]  sce_discinfo           - The pointer of contents of vs0:/app/NPXS10028/__sce_discinfo
 * @param[out] eboot_signature        - The pointer of the output eboot signature data. size is 0x100
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

int vshMemoryCardGetCardInsertState(int device_index);
int vshRemovableMemoryGetCardInsertState(void);

int vshMsifGetMsInfo(SceMsInfo *info);

typedef struct SceVshAppMgrCheckPfsMountedOpt {
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceVshAppMgrCheckPfsMountedOpt;
VITASDK_BUILD_ASSERT_EQ(8, SceVshAppMgrCheckPfsMountedOpt); // size is from FW 3.60

typedef struct SceVshAppMgrBgdlQueueStatusEntry {
	SceUInt32 download_status; //!< Set from SceShell's 4-bit state: 7 maps to 2, 8 to 1,
	                          //!< 9 to 3, 0xC to 4, and every other value to 0.
	SceBool unknown_boolean; //!< Set for SceShell state 9, or when an unidentified source word is zero,
	                        //!< flags 0x300 are clear, and flag 0x40000 is set. AppMgr
	                        //!< preserves but does not test this field; its purpose is unknown.
	char identifier[0x30]; //!< NUL-terminated BGDL identifier; AppMgr treats bytes 7 through 15 as a title ID.
} SceVshAppMgrBgdlQueueStatusEntry;
VITASDK_BUILD_ASSERT_EQ(0x38, SceVshAppMgrBgdlQueueStatusEntry); // size is from FW 3.60

typedef struct SceVshAppMgrBgdlQueueStatus {
	SceVshAppMgrBgdlQueueStatusEntry entries[32];
} SceVshAppMgrBgdlQueueStatus;
VITASDK_BUILD_ASSERT_EQ(0x700, SceVshAppMgrBgdlQueueStatus); // size is from FW 3.60

typedef struct SceVshSblAuthMgrVerifySpsfoOpt {
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceVshSblAuthMgrVerifySpsfoOpt;
VITASDK_BUILD_ASSERT_EQ(8, SceVshSblAuthMgrVerifySpsfoOpt); // size is from FW 3.60

typedef struct SceVshNpDrmGetLegacyDocKeyOpt {
	SceUInt8 *document_key; //!< Destination for the 16-byte document key.
	SceSize document_data_size; //!< Number of bytes to copy from the document data, at most 0x200.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceVshNpDrmGetLegacyDocKeyOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceVshNpDrmGetLegacyDocKeyOpt); // size is from FW 3.60

typedef struct SceVshSblSsCreatePassPhraseOpt {
	SceSize pass_phrase_size; //!< Number of pass-phrase bytes to copy, at most 0x200.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceVshSblSsCreatePassPhraseOpt;
VITASDK_BUILD_ASSERT_EQ(8, SceVshSblSsCreatePassPhraseOpt); // size is from FW 3.60

/**
 * Get add-on-content installation data.
 *
 * @param[in] title_id - Pointer to a 0x10-byte buffer containing a NUL-terminated, nine-character title ID.
 * @param[in] addcont_id - Pointer to a 0x14-byte buffer containing a NUL-terminated, 16-character add-on-content ID.
 * @param[out] result - Output ::SceAppMgrAcInstResult structure containing the
 *                      add-on-content keystone and localized game title.
 *
 * @note The title ID must contain four uppercase letters followed by five
 *       decimal digits. The add-on-content ID must contain exactly 16
 *       uppercase alphanumeric characters. The calling process must be
 *       authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshAppMgrAcInstGetAcdirParam(const char title_id[0x10], const char addcont_id[0x14], SceAppMgrAcInstResult *result);

/**
 * Update the background-download queue status table.
 *
 * @param[in] queue_status - Pointer to a ::SceVshAppMgrBgdlQueueStatus structure.
 *
 * All 0x700 bytes are copied before this function returns. The caller still
 * owns the structure.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshAppMgrBgdlSetQueueStatus(const SceVshAppMgrBgdlQueueStatus *queue_status);

/**
 * Check whether a PFS path is mounted.
 *
 * @param[in] path - NUL-terminated `ux0:` path shorter than 0x124 bytes.
 * @param[in] opt - Required 8-byte structure whose contents are ignored on FW 3.60.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 when the path is a mounted PFS directory, or a negative error code.
 */
int _vshAppMgrCheckPfsMounted(const char *path, const SceVshAppMgrCheckPfsMountedOpt *opt);

/**
 * Create and sign a cloud-data header.
 *
 * @param[in] setup_key - 0x18-byte setup-key buffer. Its first 0x10 bytes contain the ASCII account ID.
 * @param[in] data_size - Size of the cloud-data payload, at most 0x40000000 bytes.
 * @param[in] digest - 0x20-byte payload digest.
 * @param[out] header - 0x170-byte "PSVB" header containing the timestamp,
 *                     data size, account ID, digest, and RSA signature.
 *
 * The last eight setup-key bytes are copied by the bridge but ignored by
 * AppMgr on FW 3.60. An all-zero ASCII account ID is rejected. The output
 * header is cleared when creation fails.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshAppMgrCloudDataCreateHeader(const SceUInt8 setup_key[0x18], SceSize data_size, const SceUInt8 digest[0x20], SceUInt8 header[0x170]);

/**
 * Change selected attributes of a path.
 *
 * @param[in] file - NUL-terminated path of at most 0x3FF characters.
 * @param[in] stat - Input ::SceIoStat structure.
 * @param[in] bits - Bitmask selecting which attributes to change.
 * @param[in] opt - Required 8-byte structure whose contents are ignored on FW 3.60.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshIoChstat(const char *file, const SceIoStat *stat, unsigned int bits, const sceIoChstatOpt *opt);

/**
 * Read the next directory entry.
 *
 * @param[in] fd - Directory descriptor.
 * @param[in,out] dir - ::SceIoDirent structure copied from the caller to the kernel and back.
 *
 * The descriptor is a PUID in the calling process. It is converted to its
 * kernel GUID before reading the directory.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 1 when an entry is read, 0 at end of directory, or a negative error code.
 */
int _vshIoDread(SceUID fd, SceIoDirent *dir);

/**
 * Get path metadata.
 *
 * @param[in] file - NUL-terminated path of at most 0x3FF characters.
 * @param[out] stat - Output ::SceIoStat structure.
 * @param[in] opt - Required 8-byte structure whose contents are ignored on FW 3.60.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshIoGetstat(const char *file, SceIoStat *stat, const sceIoGetstatOpt *opt);

/**
 * Get the compiled SDK version of a process.
 *
 * @param[in] pid - Process ID.
 * @param[out] sdk_version - Receives the compiled SDK version as a ::SceUInt32.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshKernelGetCompiledSdkVersionByPid(ScePID pid, SceUInt32 *sdk_version);

/**
 * Derive the 16-byte key for a legacy document.
 *
 * @param[in] rif_data - Optional 0x200-byte RIF data buffer. Some PSPEDAT
 *                      document modes require it.
 * @param[in] document_data - PSPEDAT document data, at least 0x90 bytes.
 * @param[in] document_data_size - Size of document_data in bytes; must match opt->document_data_size.
 * @param[in] opt - Required structure specifying the document-data copy size and key output buffer.
 *
 * The bridge can copy at most 0x200 bytes of document data. The caller owns
 * every buffer. Exactly 16 key bytes are written before this function returns.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshNpDrmGetLegacyDocKey(const SceUInt8 rif_data[0x200], const void *document_data, SceSize document_data_size, const SceVshNpDrmGetLegacyDocKeyOpt *opt);

/**
 * Get the primary platform security code.
 *
 * @param[out] pscode - Output ::ScePsCode structure.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshSblAimgrGetPscode(ScePsCode *pscode);

/**
 * Get the secondary platform security code.
 *
 * @param[out] pscode - Output ::ScePsCode structure.
 *
 * This variant gets the value from the secure module instead of the cached
 * primary value and is available only while product mode is enabled.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshSblAimgrGetPscode2(ScePsCode *pscode);

/**
 * Get the 0x20-byte visible ID when the system is in product mode.
 *
 * @param[out] visible_id - Output ::SceVisibleId structure.
 *
 * @note Product mode must be enabled and the calling process must be authorized
 *       as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshSblAimgrGetVisibleId(SceVisibleId *visible_id);

/**
 * Verify a signed PARAM.SFO file and copy its embedded payload.
 *
 * @param[in] path - NUL-terminated path to the signed PARAM.SFO file, at most
 *                   0xFF characters.
 * @param[out] verified_data - Output payload buffer.
 * @param[in] verified_data_capacity - Capacity of verified_data in bytes.
 * @param[in] opt - Required 8-byte structure whose contents are ignored on FW 3.60.
 *
 * The verified embedded payload must not be empty and must fit completely in
 * verified_data. The function does not copy part of a payload.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshSblAuthMgrVerifySpsfo(const char *path, void *verified_data, SceSize verified_data_capacity, const SceVshSblAuthMgrVerifySpsfoOpt *opt);

/**
 * Create a 0x200-byte account pass phrase.
 *
 * @param[in] args - Pass-phrase input parameters.
 * @param[out] pass_phrase - Output pass-phrase buffer.
 * @param[in] opt - Required structure specifying how many pass-phrase bytes to copy.
 *
 * SceSblSsMgr always creates 0x200 bytes internally. The bridge copies the
 * first opt->pass_phrase_size bytes to pass_phrase; this size must not exceed
 * 0x200. The caller owns all buffers.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshSblSsCreatePassPhrase(const SceSblSsCreatePassPhraseParam *args, void *pass_phrase, const SceVshSblSsCreatePassPhraseOpt *opt);

/**
 * Get the manufacturing-status value.
 *
 * @param[out] manufacturing_status - Receives the manufacturing status as a ::SceUInt32.
 *
 * FW 3.60 returns the four-byte response to Syscon command 0x15. No observed
 * caller interprets its individual bits, so their purposes are unknown.
 *
 * @note Product mode must be enabled and the calling process must be authorized
 *       as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int _vshSysconGetManufacturesStatus(SceUInt32 *manufacturing_status);

/**
 * Create a mount event.
 *
 * @param[in] mount_id - One of ::SceVshMountId.
 * @param[in] event_bits - Bitwise OR of ::SceIoMountEvent values. FW 3.60
 *                        discards bits outside 0x333; at least one accepted bit
 *                        must remain.
 *
 * The returned UID is a PUID belonging to the calling process.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return Event UID on success, or a negative error code.
 */
SceUID vshIoCreateMountEvent(SceVshMountId mount_id, SceUInt32 event_bits);

/**
 * Notify the kernel that SceShell is ready.
 *
 * @param[in] event_id - Event ID. FW 3.60 accepts only 0, meaning that SceShell
 *                      is ready.
 *
 * The notification is sent to SceSysroot only on the first successful call;
 * later calls with zero still return success.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 0 on success, or a negative error code.
 */
int vshKernelSendSysEvent(SceUInt32 event_id);

/**
 * Check whether the communication-test flag is set.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 1 when set, 0 when clear, or a negative authorization error.
 */
int vshSblUtMgrHasComTestFlag(void);

/**
 * Check whether the NP-test flag is set.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 1 when set, 0 when clear, or a negative authorization error.
 */
int vshSblUtMgrHasNpTestFlag(void);

/**
 * Check whether the store flag is set.
 *
 * @note The calling process must be authorized as a system program.
 *
 * @return 1 when set, 0 when clear, or a negative authorization error.
 */
int vshSblUtMgrHasStoreFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_VSHBRIDGE_H_ */
