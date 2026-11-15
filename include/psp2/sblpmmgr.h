/**
 * \usergroup{SceSblPmMgr}
 * \usage{psp2/sblpmmgr.h,SceSblPmMgr_stub}
 */

#ifndef _PSP2_SBLPMMGR_H_
#define _PSP2_SBLPMMGR_H_

#include <psp2/types.h>
#include <psp2common/sblpostssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the EtoI jig-authentication exchange through `pm_sm_sd.self`.
 *
 * This operation is restricted to system programs.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblPmMgrAuthEtoI(void);

/**
 * Get the cached current-mode value.
 *
 * This operation is restricted to system programs.
 *
 * @param[out] result - Only one byte is written through this int pointer.
 *                      The byte is a ::SceSblProductMode value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblPmMgrGetCurrentMode(int *result);

/**
 * Get the KBL product-mode value.
 *
 * This operation is restricted to system programs.
 *
 * @param[out] result - Only one byte is written through this int pointer.
 *                      The byte is a ::SceSblProductMode value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblPmMgrGetProductModeForUser(int *result);

/**
 * Read the product-mode byte from NVS.
 *
 * This operation is restricted to system programs.
 *
 * @param[out] product_mode - Receives the raw NVS byte. The FW 3.60 product-mode
 *                            operations write ::SceSblProductMode values.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblPmMgrGetProductModeFromNVS(SceUInt8 *product_mode);

/**
 * Leave manufacturing mode and disable SD mode.
 *
 * This operation is restricted to system programs.
 * ::sceSblPmMgrGetCurrentMode continues to report the value cached at boot
 * until the system restarts.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblPmMgrSetProductModeOffForUser(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLPMMGR_H_ */
