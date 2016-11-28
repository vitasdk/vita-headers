/**
 * \usergroup{ScePromoterUtil}
 * \usage{psp2/promoterutil.h,-lScePromoterUtil_Stub}
 */

/**
 * \file
 * \brief Header file which defines promoter utility related variables and functions
 *
 * Copyright (C) 2016 VITASDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_PROMOTERUTIL_H_
#define _PSP2_PROMOTERUTIL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Parameters for scePromoterUtilityUpdateLiveArea() */
typedef struct ScePromoterUtilityLAUpdate {
	char titleid[12]; //!< Target app.
	char path[128]; //!< Directory of extracted LA update data.
} ScePromoterUtilityLAUpdate;

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
 * @return 0 on success.
 */
int scePromoterUtilityDeletePkg(void *unk);

/**
 * Update the LiveArea ressources of an app
 *
 * @param[in] *args - see ::ScePromoterUtilityLAUpdate
 *
 * @return 0 on success.
 */
int scePromoterUtilityUpdateLiveArea(ScePromoterUtilityLAUpdate *args);

/**
 * Install a package from a directory, and add an icon on the LiveArea.
 * \note It is an asynchronous function.
 *
 * @param[in] *path - the path of the directory where the extracted content of the package is
 * @param unk - unknown, pass 0
 *
 * @return 0 on success.
 */
int scePromoterUtilityPromotePkg(const char *path, int unk);

/**
 * Install a package from a directory and generate a rif.
 * \note It is an asynchronous function.
 *
 * @param[in] *path - the path of the directory where the extracted content of the package is
 * @param unk - unknown, pass 0
 *
 * @return 0 on success.
 */
int scePromoterUtilityPromotePkgWithRif(const char *path, int unk);

/**
 * Returns the state of an operation.
 *
 * @param[out] *state - the current status, 0 when finished
 *
 * @return <0 if failed.
 */
int scePromoterUtilityGetState(int *state);

/**
 * Returns the result of a finished operation
 *
 * @param[out] *res - the result, 0 on success
 *
 * @return <0 if failed.
 */
int scePromoterUtilityGetResult(int *res);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PROMOTERUTIL_H_ */
