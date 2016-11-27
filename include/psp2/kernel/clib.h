/**
 * \usergroup{SceCLib}
 * \usage{psp2/kernel/clib.h,-lSceKernel_stub}
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
void *sceClibStrncmp(const char *, const char *, SceSize);
int sceClibStrncasecmp(const char *, const char *, SceSize);
char *sceClibStrncpy(char *, const char *, SceSize);
char *sceClibStrncat(char *, const char *, SceSize);
SceSize sceClibStrnlen(const char *, SceSize);
char *sceClibStrrchr(const char *, int);

int sceClibPrintf(const char *, ...);
int sceClibSnprintf(char *, SceSize, const char *, ...);
int sceClibVsnprintf(char *, SceSize, const char *, va_list);

void *sceClibMemset(void *, int, SceSize);
void *sceClibMemcpy(void *, const void *, SceSize);
void *sceClibMemmove(void *, const void *, SceSize);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CLIB_H_ */

