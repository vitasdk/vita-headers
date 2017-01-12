/**
 * \usergroup{SceMtpIfDriver}
 * \usage{psp2/mtpif.h,-lSceMtpIfDriver_stub}
 */

/**
 * \file
 * \brief Header file which defines MTP interface driver functions
 *
 * Copyright (C) 2017 vitasdk developers
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_MTPIF_H_
#define _PSP2_MTPIF_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Start MTP driver
 *
 * @param[in] flags - Set to 1
 *
 * @return 0 on success, < 0 on error.
*/
int sceMtpIfStartDriver(int flags);

/**
 * Stop MTP driver
 *
 * @param[in] flags - Set to 1
 *
 * @return 0 on success, < 0 on error.
*/
int sceMtpIfStopDriver(int flags);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_MTPIF_H_ */
