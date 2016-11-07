/**
 * \file
 * \brief Header file which defines NpDrmPackage related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_NPDRMPACKAGE_H_
#define _PSP2_NPDRMPACKAGE_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Options for _sceNpDrmPackageDecrypt */
typedef struct {
	/** The offset in the encrypted data */
	SceOff offset;

	/**
	 * The identifier specified for _sceNpDrmPackageCheck but NOT ORed
     * with (1 << 8)
	 */
	unsigned int identifier;
} _sceNpDrmPackageDecrypt_opt;

/**
 * Read the header of the PKG and initialize the context
 *
 * @param buffer - The buffer containing the header of PKG.
 * @param size - The size of buffer. The minimum confirmed value is 0x8000.
 * @param zero - Unknown. Supposed to be set to 0.
 * @param identifier - arbitrary value [0, 6) ORed with (1 << 8) or 0.
 *                     If it is set to 0, the function just checks the header
 *                     and doesn't create the context.
 */
int _sceNpDrmPackageCheck(const void *buffer, SceSize size, int zero, unsigned int identifier);

/**
 * Decrypt a PKG
 *
 * @param buffer - The buffer containing the content of the PKG.
 * @param size - The size of the buffer. The minimum confirmed value is 0x20.
 * @param opt - The options.
 */
int _sceNpDrmPackageDecrypt(void * restrict buffer, SceSize size, _sceNpDrmPackageDecrypt_opt * restrict opt);
	
#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NPDRMPACKAGE_H_ */
