/**
 * \addtogroup Kernel Kernel
 * Modules, Processes, Threads, Memory blocks
 * \{
 */

/**
 * \addtogroup SceCLib C Standard Library
 * String comparison and string printf
 */
/** \} */

/**
 * \defgroup SceCLibUser User
 *  \ingroup SceCLib
 * Exports for User
 *
 * ------------------------
 * ### Using this library in your project ###
 * Include the header file in your project:
 * \code
 * #include <psp2/kernel/clib.h>
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
 * \brief Header file which defines sceClib functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_KERNEL_CLIB_H_
#define _PSP2_KERNEL_CLIB_H_

#include <psp2/types.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceClibStrcmp(const char *, const char *);

int sceClibSnprintf(char *, SceSize, const char *, ...);
int sceClibVsnprintf(char *, SceSize, const char *, va_list);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CLIB_H_ */

/** \} */
