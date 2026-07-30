/**
 * \usergroup{SceNpDrmPackage}
 * \usage{psp2/npdrmpackage.h,SceNpDrm_stub}
 */


#ifndef _PSP2_NPDRMPACKAGE_H_
#define _PSP2_NPDRMPACKAGE_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/sblssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _sceNpDrmPackageCheck_opt {
	SceUInt32 reserved[8]; //!< Ignored on FW 3.60.
} _sceNpDrmPackageCheck_opt;
VITASDK_BUILD_ASSERT_EQ(0x20, _sceNpDrmPackageCheck_opt); // size is from FW 3.60

/** Options for ::_sceNpDrmPackageDecrypt */
typedef struct _sceNpDrmPackageDecrypt {
	SceOff offset; //!< Offset in the encrypted data.
	unsigned int identifier; //!< Identifier passed to ::_sceNpDrmPackageCheck without the 0x100 flag.
} _sceNpDrmPackageDecrypt_opt;
VITASDK_BUILD_ASSERT_EQ(0x10, _sceNpDrmPackageDecrypt_opt); // size is from FW 3.60

typedef struct _sceNpDrmPackageStarted_opt {
	SceSize message_size; //!< Size of the message buffer.
	SceSize message_copy_size; //!< Number of bytes to copy from the message buffer; must not exceed 0x40.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} _sceNpDrmPackageStarted_opt;
VITASDK_BUILD_ASSERT_EQ(0x10, _sceNpDrmPackageStarted_opt); // size is from FW 3.60

typedef struct _sceNpDrmPackageFinished_opt {
	SceSize message_copy_size; //!< Number of bytes to copy from the message buffer; must not exceed 0x40.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} _sceNpDrmPackageFinished_opt;
VITASDK_BUILD_ASSERT_EQ(0x8, _sceNpDrmPackageFinished_opt); // size is from FW 3.60

/**
 * Read the header of the PKG and initialize the context
 *
 * @param buffer - The buffer containing the header of PKG.
 * @param size - The size of buffer. The minimum confirmed value is 0x8000.
 * @param opt - A 32-bit user pointer to a ::_sceNpDrmPackageCheck_opt structure,
 *              or 0. The structure contents are ignored on FW 3.60. Any nonzero
 *              pointer requests package-context teardown.
 * @param identifier - A value whose low byte is in the range [0, 6). The 0x100
 *                     flag creates or uses the package context. The 0x200 flag
 *                     also requests teardown and requires a nonzero opt.
 *
 * @return 0 on success, != 0 on error
 */
int _sceNpDrmPackageCheck(const void *buffer, SceSize size, int opt, unsigned int identifier);

/**
 * Decrypt a PKG
 *
 * @param buffer - The buffer containing the content of the PKG.
 * @param size - The size of the buffer. The minimum confirmed value is 0x20.
 * @param opt - The options.
 *
 * @return 0 on success, != 0 on error
 */
int _sceNpDrmPackageDecrypt(void * __restrict__ buffer, SceSize size, _sceNpDrmPackageDecrypt_opt * __restrict__ opt);

/**
 * Update a package hash-transform context
 *
 * @param buffer - A 32-bit user pointer to the input data
 * @param size - Size of the input data
 * @param opt - A pointer to a ::SceSblDmac5HashTransformContext structure
 * @param identifier - Package identifier and flags. The 0x10000 flag copies the
 *                     0x20-byte DMAC5 hash output into opt's state. The
 *                     0x40000000 flag selects DMAC5 command 3 instead of command
 *                     0x13.
 *
 * @return 0 on success, != 0 on error
 */
int _sceNpDrmPackageTransform(int buffer, int size, void *opt, int identifier);

/**
 * Notify that package installation has started
 *
 * @param identifier - Package operation identifier
 * @param forwarded_value - Forwarded unchanged to the system callback; 0 in
 *                          observed FW 3.60 callers
 * @param message - A 32-bit user pointer to the status message
 * @param opt - A pointer to a ::_sceNpDrmPackageStarted_opt structure
 */
int _sceNpDrmPackageInstallStarted(int identifier, int forwarded_value, int message, void *opt);

/**
 * Notify that package installation has finished
 *
 * @param result_code - Operation result
 * @param message - A 32-bit user pointer to the status message
 * @param message_size - Size of the status message
 * @param opt - A pointer to a ::_sceNpDrmPackageFinished_opt structure
 */
int _sceNpDrmPackageInstallFinished(int result_code, int message, int message_size, void *opt);

/**
 * Notify that package uninstallation has started
 *
 * @param identifier - Package operation identifier
 * @param forwarded_value - Forwarded unchanged to the system callback; 0 in
 *                          observed FW 3.60 callers
 * @param message - A 32-bit user pointer to the status message
 * @param opt - A pointer to a ::_sceNpDrmPackageStarted_opt structure
 */
int _sceNpDrmPackageUninstallStarted(int identifier, int forwarded_value, int message, void *opt);

/**
 * Notify that package uninstallation has finished
 *
 * @param result_code - Operation result
 * @param message - A 32-bit user pointer to the status message
 * @param message_size - Size of the status message
 * @param opt - A pointer to a ::_sceNpDrmPackageFinished_opt structure
 */
int _sceNpDrmPackageUninstallFinished(int result_code, int message, int message_size, void *opt);

/**
 * Notify that save-data formatting has started
 *
 * @param identifier - Save-data operation identifier
 * @param forwarded_value - Forwarded unchanged to the system callback; 0 in
 *                          observed FW 3.60 callers
 * @param message - A 32-bit user pointer to the status message
 * @param opt - A pointer to a ::_sceNpDrmPackageStarted_opt structure
 */
int _sceNpDrmSaveDataFormatStarted(int identifier, int forwarded_value, int message, void *opt);

/**
 * Notify that save-data formatting has finished
 *
 * @param result_code - Operation result
 * @param message - A 32-bit user pointer to the status message
 * @param message_size - Size of the status message
 * @param opt - A pointer to a ::_sceNpDrmPackageFinished_opt structure
 */
int _sceNpDrmSaveDataFormatFinished(int result_code, int message, int message_size, void *opt);

/**
 * Notify that save-data installation has started
 *
 * @param identifier - Save-data operation identifier
 * @param forwarded_value - Forwarded unchanged to the system callback; 0 in
 *                          observed FW 3.60 callers
 * @param message - A 32-bit user pointer to the status message
 * @param opt - A pointer to a ::_sceNpDrmPackageStarted_opt structure
 */
int _sceNpDrmSaveDataInstallStarted(int identifier, int forwarded_value, int message, void *opt);

/**
 * Notify that save-data installation has finished
 *
 * @param result_code - Operation result
 * @param message - A 32-bit user pointer to the status message
 * @param message_size - Size of the status message
 * @param opt - A pointer to a ::_sceNpDrmPackageFinished_opt structure
 */
int _sceNpDrmSaveDataInstallFinished(int result_code, int message, int message_size, void *opt);

/**
 * Report package installation progress
 *
 * @param identifier - Package operation identifier
 * @param progress - Progress percentage. The observed FW 3.60 caller accepts
 *                   values in the range [0, 100].
 */
int sceNpDrmPackageInstallOngoing(int identifier, int progress);

/** @return Nonzero when package game content exists, 0 otherwise */
int sceNpDrmPackageIsGameExist(void);

/**
 * Report package uninstallation progress
 *
 * @param identifier - Package operation identifier
 * @param progress - Progress percentage. The observed FW 3.60 caller accepts
 *                   values in the range [0, 100].
 */
int sceNpDrmPackageUninstallOngoing(int identifier, int progress);

/**
 * Report save-data formatting progress
 *
 * @param identifier - Save-data operation identifier
 * @param progress - Progress percentage. The observed FW 3.60 caller accepts
 *                   values in the range [0, 100].
 */
int sceNpDrmSaveDataFormatOngoing(int identifier, int progress);

/**
 * Report save-data installation progress
 *
 * @param identifier - Save-data operation identifier
 * @param progress - Progress percentage. The observed FW 3.60 caller accepts
 *                   values in the range [0, 100].
 */
int sceNpDrmSaveDataInstallOngoing(int identifier, int progress);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NPDRMPACKAGE_H_ */
