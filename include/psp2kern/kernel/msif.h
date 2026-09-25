/**
 * \kernelgroup{SceMsif}
 * \usage{psp2kern/kernel/msif.h,SceMsifForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_MSIF_H_
#define _PSP2KERN_KERNEL_MSIF_H_

#include <psp2common/kernel/msif.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceMsifGetMsInfo(SceMsInfo *info);

#define SCE_MSIF_SECTOR_SIZE (0x200)

/** MSIF errors returned directly by the FW 3.60 sector APIs. */
typedef enum SceMsifErrorCode {
	SCE_MSIF_ERROR_INTERNAL          = 0x803D0000,
	SCE_MSIF_ERROR_INVALID_ARGUMENT  = 0x803D0001,
	SCE_MSIF_ERROR_UNALIGNED_BUFFER  = 0x803D0002,
	SCE_MSIF_ERROR_WRITE_PROTECTED   = 0x803D0003
} SceMsifErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, SceMsifErrorCode); // size is from FW 3.60

/**
 * Disable slow-card mode.
 *
 * Slow-card mode does not change the MSIF controller clock. It adds minimum
 * completion delays after successful sector reads and writes, including
 * periodic 350 or 400 ms pauses.
 *
 * @return Always 0.
 */
int ksceMsifDisableSlowCardMode(void);

/**
 * Enable slow-card mode.
 *
 * @return Always 0.
 * @see ::ksceMsifDisableSlowCardMode
 */
int ksceMsifEnableSlowCardMode(void);

/**
 * Check whether slow-card mode is enabled.
 *
 * @return ::SCE_TRUE when enabled, or ::SCE_FALSE when disabled.
 */
SceBool ksceMsifGetSlowCardModeState(void);

/**
 * Read sectors from the Memory Stick medium.
 *
 * @param[in] sector - First logical sector to read.
 * @param[out] buffer - Destination for \a sector_count *
 *                      ::SCE_MSIF_SECTOR_SIZE bytes. Must be aligned to 4
 *                      bytes.
 * @param[in] sector_count - Number of sectors to read. Must not be 0.
 *
 * @return 0 on success, a negative ::SceMsifErrorCode value, a mapped medium
 *         error, or a fast-mutex error.
 */
int ksceMsifReadSector(SceUInt32 sector, void *buffer, SceUInt32 sector_count);

/**
 * Write sectors to the Memory Stick medium.
 *
 * @param[in] sector - First logical sector to write.
 * @param[in] buffer - Source containing \a sector_count *
 *                     ::SCE_MSIF_SECTOR_SIZE bytes. Must be aligned to 4
 *                     bytes.
 * @param[in] sector_count - Number of sectors to write. Must not be 0.
 *
 * @return 0 on success, a negative ::SceMsifErrorCode value, a mapped medium
 *         error, or a fast-mutex error.
 */
int ksceMsifWriteSector(SceUInt32 sector, const void *buffer, SceUInt32 sector_count);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_MSIF_H_ */
