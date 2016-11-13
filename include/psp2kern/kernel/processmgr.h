/**
 * \addtogroup Kernel Kernel
 * Modules, Processes, Threads, Memory blocks
 * \{
 */

/**
 * \addtogroup SceProcessmgr Process Manager Library
 * Get time, ID of the current Process and exit it
 */
/** \} */

/**
 * \defgroup SceProcessmgrKernel Kernel
 *  \ingroup SceProcessmgr
 * Exports for Kernel
 *
 * ------------------------
 * ### Using this library in your project ###
 * Include the header file in your project:
 * \code
 * #include <psp2kern/kernel/processmgr.h>
 * \endcode
 *
 * Link the library in your makefile:
 * \code
 * ?
 * \endcode
 * ------------------------
 * \{
 */

/**
 * \file
 * \brief Header file which defines processes related variables and functions for kernel
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void *sceKernelGetProcessKernelBuf(SceUID pid);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */

/** \} */
