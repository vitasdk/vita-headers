/*
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _SETJMP_H_
#define _SETJMP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _JBLEN 24
#define _JBTYPE long long

typedef _JBTYPE jmp_buf[_JBLEN];

void longjmp(jmp_buf __j, int __res) __attribute__((noreturn));
int setjmp(jmp_buf __j);

#ifdef __cplusplus
}
#endif

#endif
