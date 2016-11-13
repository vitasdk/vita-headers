/**
 * \addtogroup Kernel Kernel
 * Modules, Processes, Threads, Memory blocks
 * \{
 */

/**
 * \addtogroup SceOpenPsid OpenPsid Library
 * Get the Vita unique Open Psid
 */
/** \} */

/**
 * \defgroup SceOpenPsidUser User
 *  \ingroup SceOpenPsid
 * Exports for User
 *
 * ------------------------
 * ### Using this library in your project ###
 * Include the header file in your project:
 * \code
 * #include <psp2/kernel/openpsid.h>
 * \endcode
 *
 * Link the library in your makefile:
 * \code
 * -lSceKernel_stub
 * \endcode
 * ------------------------
 * \{
 */

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

/** \} */
