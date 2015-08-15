/**
 * \file
 * \brief Header file related to module information definitions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_MODULEINFO_H_
#define _PSP2_MODULEINFO_H_

#include <psp2/types.h>
#include <stddef.h>
#include <stdint.h>

//! Module Information
typedef struct {
	uint16_t attr;	//!< Attribute
	uint16_t ver;	//!< Version
	char name[27];	//!< Name
	uint8_t type;	//!< Type
	void *gp;	//!< Global Pointer
	uint32_t expTop;	//!< Offset of the top of export table
	uint32_t expBtm;	//!< Offset of the bottom of export table
	uint32_t impTop;	//!< Offset of the top of import table
	uint32_t impBtm;	//!< Offset of the bottom of import table
	uint32_t nid;	//!< NID
	uint32_t unk[3];	//!< Unknown
	uint32_t start;	//!< Offset of module_start function
	uint32_t stop;	//!< Offset of module_stop function
	uint32_t exidxTop;	//!< Offset of the top of exidx section
	uint32_t exidxBtm;	//!< Offset of the bottom of exidx section
	uint32_t extabTop;	//!< Offset of the top of extab section
	uint32_t extabBtm;	//!< Offset of the bottom of extab section
} _sceModuleInfo;

//! The type of structure stored in .sceModuleInfo.rodata section
typedef const _sceModuleInfo SceModuleInfo;

// It doesn't refer to import_btm because it is not defined yet.
/**
 * Define module information
 *
 * \param attribute Attribute
 * \param version Version
 * \param module_name Name
 */

/* Declare a module.  This must be specified in the source of a library or executable. */
#define _PSP2_MODULE_INFO_(attribute, version, module_name)	\
	__asm__ (".section .sceLib.stub, \"a\", %progbits;");	\
	SceModuleInfo module_info	\
		__attribute__((section(".sceModuleInfo.rodata"), used))	\
			= { attribute, version,	module_name };

#ifdef __cplusplus
#define PSP2_MODULE_INFO(attribute, version, module_name)	\
	extern "C" { _PSP2_MODULE_INFO_(attribute, version, module_name) }
#else
#define PSP2_MODULE_INFO _PSP2_MODULE_INFO_
#endif

#endif
