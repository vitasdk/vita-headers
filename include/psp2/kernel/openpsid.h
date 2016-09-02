/**
 * \file
 * \brief Header file which defines processes related variables and functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_KERNEL_OPENPSID_H_
#define _PSP2_KERNEL_OPENPSID_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelOpenPsId {
	char id[16];
} SceKernelOpenPsId;

int sceKernelGetOpenPsId(SceKernelOpenPsId *id);

#ifdef __cplusplus
}
#endif

#endif
