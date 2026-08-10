/**
 * \usergroup{SceSblPmMgr}
 * \usage{psp2/sblpmmgr.h,SceSblPmMgr_stub}
 */

#ifndef _PSP2_SBLPMMGR_H_
#define _PSP2_SBLPMMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSblPmMgrAuthEtoI(void);

/**
 * Get the cached current-mode value.
 *
 * @param[out] result - Receives one byte through the existing wider pointer type.
 */
int sceSblPmMgrGetCurrentMode(int *result);

/**
 * Get the KBL product-mode value.
 *
 * @param[out] result - Receives one byte through the existing wider pointer type.
 */
int sceSblPmMgrGetProductModeForUser(int *result);

/**
 * Read the product-mode byte from NVS.
 *
 * @param[out] product_mode - Receives one byte.
 */
int sceSblPmMgrGetProductModeFromNVS(SceUInt8 *product_mode);

int sceSblPmMgrSetProductModeOffForUser(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLPMMGR_H_ */
