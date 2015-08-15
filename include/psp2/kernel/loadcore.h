/**
 * \file
 * \brief Header file related to module load core
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_KERNEL_LOADCORE_
#define _PSP2_KERNEL_LOADCORE_

#include <stdint.h>

typedef struct {
	uint16_t size;
	uint16_t ver;
	uint16_t attr;
	uint16_t funcNum;
	uint32_t varNum;
	uint32_t unkNum;
	uint32_t nid;
	const char *name;
	const uint32_t *nids;
	const void **ents;
} SceLibraryEntryTable;

#endif
