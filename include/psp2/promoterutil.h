/**
 * \usergroup{ScePromoterUtil}
 * \usage{psp2/promoterutil.h,ScePromoterUtil_stub}
 */


#ifndef _PSP2_PROMOTERUTIL_H_
#define _PSP2_PROMOTERUTIL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Avalible types for ::ScePromoterUtilityImportParams **/
typedef enum ScePromoterUtilityPackageType {
	SCE_PKG_TYPE_VITA               = 0x0001,          //!< PSVita Apps
	SCE_PKG_TYPE_PSM                = 0x0003,          //!< PlayStation Mobile
} ScePromoterUtilityPackageType;

/** Parameters for scePromoterUtilityUpdateLiveArea() */
typedef struct ScePromoterUtilityLAUpdate {
	char titleid[12];  //!< Target app.
	char path[128];    //!< Directory of extracted LA update data.
} ScePromoterUtilityLAUpdate;

/** Parameters for scePromoterUtilityPromoteImport() */
typedef struct ScePromoterUtilityImportParams {
	char path[0x80]; //!< Install path usually (ux0:/temp/game)
	char titleid[0xC]; //!< Game titleid
	ScePromoterUtilityPackageType type; //!< Package type
	uint32_t attribute; //!< Additional Attributes (Appears to be 0x1 on PSM content but 0x00 on Vita contents)
	char reserved[0x1C];
} ScePromoterUtilityImportParams;

/**
 * Init the promoter utility.
 * \note Needs to be called before using the other functions.
 *
 * @return 0 on success.
 */
int scePromoterUtilityInit(void);

/**
 * Deinit the promoter utility.
 *
 * @return 0 on success.
 */
int scePromoterUtilityExit(void);

/**
 * Delete a package from the LiveArea.
 *
 * @param[in] *titleid
 *
 * @return 0 on success.
 */
int scePromoterUtilityDeletePkg(const char *titleid);

/**
 * Update the LiveArea resources of an app
 *
 * @param[in] *args - see ::ScePromoterUtilityLAUpdate
 *
 * @return 0 on success.
 */
int scePromoterUtilityUpdateLiveArea(ScePromoterUtilityLAUpdate *args);

/**
 * Install Content Manager import contents and create bubbles without checking license files.
 *
 * @param[in] *params - see ::ScePromoterUtilImportParams
 *
 * @return 0 on success.
 */
int scePromoterUtilityPromoteImport(ScePromoterUtilityImportParams *params);

/**
 * Install a package from a directory, and add an icon on the LiveArea.
 *
 * @param[in] *path - the path of the directory where the extracted content of the package is
 * @param sync - pass 0 for asynchronous, 1 for synchronous
 *
 * @return 0 on success.
 */
int scePromoterUtilityPromotePkg(const char *path, int sync);

/**
 * Install a package from a directory and generate a rif.
 *
 * @param[in] *path - the path of the directory where the extracted content of the package is
 * @param sync - pass 0 for asynchronous, 1 for synchronous
 *
 * @return 0 on success.
 */
int scePromoterUtilityPromotePkgWithRif(const char *path, int sync);

/**
 * Returns the state of an operation.
 *
 * @param[out] *state - the current status, 0 when finished
 *
 * @return < 0 if failed.
 */
int scePromoterUtilityGetState(int *state);

/**
 * Returns the result of a finished operation
 *
 * @param[out] *res - the result, 0 on success
 *
 * @return < 0 if failed.
 */
int scePromoterUtilityGetResult(int *res);

/**
 * Check if titleid exists
 *
 * @param[out] *res - the result, unknown meaning
 *
 * @return 0 if exists, < 0 otherwise.
 */
int scePromoterUtilityCheckExist(const char *titleid, int *res);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PROMOTERUTIL_H_ */
