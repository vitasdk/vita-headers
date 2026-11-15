/**
 * \usergroup{SceNpDrmPackage}
 * \usage{psp2/npdrmpackage.h,SceNpDrm_stub}
 *
 * On FW 3.60, every function in this library except
 * ::sceNpDrmPackageIsGameExist is restricted to system programs with auth ID
 * 0x2800000000000001, 0x280000000000002D, 0x280000000000002E, or
 * 0x2800000000000039.
 *
 * The started and finished notification functions copy at most 0x40 bytes
 * from the message buffer before returning. You may reuse or free the buffer
 * after the function returns.
 */


#ifndef _PSP2_NPDRMPACKAGE_H_
#define _PSP2_NPDRMPACKAGE_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/sblssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceNpDrmPackageCheckOpt {
	SceUInt32 reserved[8]; //!< Ignored on FW 3.60.
} SceNpDrmPackageCheckOpt;
VITASDK_BUILD_ASSERT_EQ(0x20, SceNpDrmPackageCheckOpt); // size is from FW 3.60

/**
 * Options for ::_sceNpDrmPackageDecrypt.
 *
 * The older type name ::_sceNpDrmPackageDecrypt_opt is kept for
 * backwards compatibility.
 */
typedef struct _sceNpDrmPackageDecrypt {
	SceOff offset; //!< Offset in the encrypted data.
	SceUInt32 identifier; //!< Context identifier passed to ::_sceNpDrmPackageCheck without the 0x100 flag.
} SceNpDrmPackageDecryptOpt, _sceNpDrmPackageDecrypt_opt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceNpDrmPackageDecryptOpt); // size is from FW 3.60

typedef struct SceNpDrmPackageStartedOpt {
	SceSize message_size; //!< Size of the message buffer.
	SceSize message_copy_size; //!< Number of bytes to copy from the message buffer; must not exceed 0x40.
	SceUInt32 reserved[2]; //!< Ignored on FW 3.60.
} SceNpDrmPackageStartedOpt;
VITASDK_BUILD_ASSERT_EQ(0x10, SceNpDrmPackageStartedOpt); // size is from FW 3.60

typedef struct SceNpDrmPackageFinishedOpt {
	SceSize message_copy_size; //!< Number of bytes to copy from the message buffer; must not exceed 0x40.
	SceUInt32 reserved; //!< Ignored on FW 3.60.
} SceNpDrmPackageFinishedOpt;
VITASDK_BUILD_ASSERT_EQ(0x8, SceNpDrmPackageFinishedOpt); // size is from FW 3.60

/**
 * Read the header of the PKG and initialize the context
 *
 * The caller must be one of the system programs accepted by FW 3.60.
 *
 * @param[in] buffer - Buffer containing the PKG header
 * @param[in] size - Buffer size. A normal check requires at least 0x8000 bytes.
 * @param[in] opt - A 32-bit user pointer to a ::SceNpDrmPackageCheckOpt
 *                  structure, or 0. The parameter remains an integer for
 *                  backwards compatibility. The structure contents are ignored
 *                  on FW 3.60. Any nonzero pointer requests that the context
 *                  be destroyed.
 * @param[in] identifier - Value whose low byte selects one of six contexts. Bit
 *                         0x100 creates or uses the context. Bit 0x200 also
 *                         requests that the context be destroyed and requires
 *                         a nonzero \a opt.
 *
 * @return 0 on success, < 0 on error
 */
int _sceNpDrmPackageCheck(const void *buffer, SceSize size, int opt, unsigned int identifier);

/**
 * Decrypt a PKG
 *
 * The caller must be one of the system programs accepted by FW 3.60.
 *
 * @param[in,out] buffer - PKG data to decrypt in place
 * @param[in] size - Size of the buffer
 * @param[in] opt - Required input-only offset and context identifier. Still
 *                  declared as non-const for backwards compatibility.
 *
 * @return 0 on success, < 0 on error
 */
int _sceNpDrmPackageDecrypt(void * __restrict__ buffer, SceSize size, SceNpDrmPackageDecryptOpt * __restrict__ opt);

/**
 * Update a package hash-transform context
 *
 * The caller must be one of the system programs accepted by FW 3.60.
 *
 * @param[in] buffer - Input data
 * @param[in] size - Size of the input data; must be nonzero
 * @param[in,out] context - Required hash context. All 0x28 bytes are copied in
 *                          before the update and copied back afterwards.
 * @param[in] identifier - Package identifier and flags. Bit 0x10000 copies the
 *                         0x20-byte DMAC5 hash output into \a context->state. Bit
 *                         0x40000000 selects DMAC5 command 3 instead of command
 *                         0x13.
 *
 * @return 0 on success, < 0 on error
 */
int _sceNpDrmPackageTransform(const void *buffer, SceSize size, SceSblDmac5HashTransformContext *context, SceUInt32 identifier);

/**
 * Notify that package installation has started
 *
 * @param[in] identifier - Package operation identifier. The FW 3.60 installer
 *                         sets bit 0x80000000 for a started notification.
 * @param[in] forwarded_value - Passed unchanged to the system callback;
 *                              its purpose is unknown. Observed FW 3.60
 *                              callers pass 0.
 * @param[in] message - Optional status data
 * @param[in] opt - Required message-size options
 *
 * @return >= 0 on success, < 0 on error
 */
int _sceNpDrmPackageInstallStarted(int identifier, int forwarded_value, const void *message, const SceNpDrmPackageStartedOpt *opt);

/**
 * Notify that package installation has finished
 *
 * @param[in] result_code - Operation result
 * @param[in] message - Optional status data
 * @param[in] message_size - Size of the status data
 * @param[in] opt - Required message-copy options
 *
 * @return >= 0 on success, < 0 on error
 */
int _sceNpDrmPackageInstallFinished(int result_code, const void *message, SceSize message_size, const SceNpDrmPackageFinishedOpt *opt);

/**
 * Notify that package uninstallation has started
 *
 * @param[in] identifier - Package operation identifier. The FW 3.60 installer
 *                         sets bit 0x80000000 for a started notification.
 * @param[in] forwarded_value - Passed unchanged to the system callback;
 *                              its purpose is unknown. Observed FW 3.60
 *                              callers pass 0.
 * @param[in] message - Optional status data
 * @param[in] opt - Required message-size options
 *
 * @return >= 0 on success, < 0 on error
 */
int _sceNpDrmPackageUninstallStarted(int identifier, int forwarded_value, const void *message, const SceNpDrmPackageStartedOpt *opt);

/**
 * Notify that package uninstallation has finished
 *
 * @param[in] result_code - Operation result
 * @param[in] message - Optional status data
 * @param[in] message_size - Size of the status data
 * @param[in] opt - Required message-copy options
 *
 * @return >= 0 on success, < 0 on error
 */
int _sceNpDrmPackageUninstallFinished(int result_code, const void *message, SceSize message_size, const SceNpDrmPackageFinishedOpt *opt);

/**
 * Notify that save-data formatting has started
 *
 * @param[in] identifier - Save-data operation identifier. The FW 3.60 installer
 *                         sets bit 0x80000000 for a started notification.
 * @param[in] forwarded_value - Passed unchanged to the system callback;
 *                              its purpose is unknown. Observed FW 3.60
 *                              callers pass 0.
 * @param[in] message - Optional status data
 * @param[in] opt - Required message-size options
 *
 * @return >= 0 on success, < 0 on error
 */
int _sceNpDrmSaveDataFormatStarted(int identifier, int forwarded_value, const void *message, const SceNpDrmPackageStartedOpt *opt);

/**
 * Notify that save-data formatting has finished
 *
 * @param[in] result_code - Operation result
 * @param[in] message - Optional status data
 * @param[in] message_size - Size of the status data
 * @param[in] opt - Required message-copy options
 *
 * @return >= 0 on success, < 0 on error
 */
int _sceNpDrmSaveDataFormatFinished(int result_code, const void *message, SceSize message_size, const SceNpDrmPackageFinishedOpt *opt);

/**
 * Notify that save-data installation has started
 *
 * @param[in] identifier - Save-data operation identifier. The FW 3.60 installer
 *                         sets bit 0x80000000 for a started notification.
 * @param[in] forwarded_value - Passed unchanged to the system callback;
 *                              its purpose is unknown. Observed FW 3.60
 *                              callers pass 0.
 * @param[in] message - Optional status data
 * @param[in] opt - Required message-size options
 *
 * @return >= 0 on success, < 0 on error
 */
int _sceNpDrmSaveDataInstallStarted(int identifier, int forwarded_value, const void *message, const SceNpDrmPackageStartedOpt *opt);

/**
 * Notify that save-data installation has finished
 *
 * @param[in] result_code - Operation result
 * @param[in] message - Optional status data
 * @param[in] message_size - Size of the status data
 * @param[in] opt - Required message-copy options
 *
 * @return >= 0 on success, < 0 on error
 */
int _sceNpDrmSaveDataInstallFinished(int result_code, const void *message, SceSize message_size, const SceNpDrmPackageFinishedOpt *opt);

/**
 * Report package installation progress
 *
 * @param[in] identifier - Package operation identifier
 * @param[in] progress - Progress percentage. FW 3.60 does not validate
 *                       this value; the FW 3.60 installer uses values from 0
 *                       through 100.
 *
 * @return >= 0 on success, < 0 on error
 */
int sceNpDrmPackageInstallOngoing(int identifier, SceUInt32 progress);

/** @return Nonzero when package game content exists, 0 otherwise */
SceBool sceNpDrmPackageIsGameExist(void);

/**
 * Report package uninstallation progress
 *
 * @param[in] identifier - Package operation identifier
 * @param[in] progress - Progress percentage. FW 3.60 does not validate
 *                       this value; the FW 3.60 installer uses values from 0
 *                       through 100.
 *
 * @return >= 0 on success, < 0 on error
 */
int sceNpDrmPackageUninstallOngoing(int identifier, SceUInt32 progress);

/**
 * Report save-data formatting progress
 *
 * @param[in] identifier - Save-data operation identifier
 * @param[in] progress - Progress percentage. FW 3.60 does not validate
 *                       this value; the FW 3.60 installer uses values from 0
 *                       through 100.
 *
 * @return >= 0 on success, < 0 on error
 */
int sceNpDrmSaveDataFormatOngoing(int identifier, SceUInt32 progress);

/**
 * Report save-data installation progress
 *
 * @param[in] identifier - Save-data operation identifier
 * @param[in] progress - Progress percentage. FW 3.60 does not validate
 *                       this value; the FW 3.60 installer uses values from 0
 *                       through 100.
 *
 * @return >= 0 on success, < 0 on error
 */
int sceNpDrmSaveDataInstallOngoing(int identifier, SceUInt32 progress);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NPDRMPACKAGE_H_ */
