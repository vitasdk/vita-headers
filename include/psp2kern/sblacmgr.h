/**
 * \kernelgroup{SceSblACMgr}
 * \usage{psp2kern/sblacmgr.h,?}
 */

/**
 * \file
 * \brief Header file related to SceSblACMgr for kernel
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_KERNEL_SBLACMGR_H_
#define _PSP2_KERNEL_SBLACMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSblACMgrIsShell(SceUID pid);
int sceSblACMgrIsGameProgram(SceUID pid);
int sceSblACMgrIsNonGameProgram(SceUID pid);
int sceSblACMgrIsDevelopmentMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SBLACMGR_H_ */

