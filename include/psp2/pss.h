/**
 * \file
 * \brief Header file which defines functions of SceLibMonoBridge
 *
 * Copyright (C) 2015 PSP2SDK Project
 * Copyright (C) 2016 vitasdk
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_PSS_H_
#define _PSP2_PSS_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void *pss_code_mem_alloc(SceSize *);
void pss_code_mem_flush_icache(const void *, SceSize);
void pss_code_mem_lock(void);
void pss_code_mem_unlock(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PSS_H_ */
