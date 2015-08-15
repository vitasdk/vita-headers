/**
 * @file gxt.h
 * @brief Header file which defines GXT variables and functions
 *
 * The GXT library facilitates the runtime manipulation of GXT files
 * produced using the offline texture tools.
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_GXT_H_
#define _PSP2_GXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <psp2/gxm.h>

/** GXT error codes */
enum SceGxtErrorCode {
	SCE_OK = 0,
	SCE_GXT_ERROR_INVALID_ALIGNMENT,
	SCE_GXT_ERROR_INVALID_VALUE,
	SCE_GXT_ERROR_INVALID_POINTER
};

/** Header for a GXT file */
typedef struct SceGxtHeader {
	uint32_t tag;		//!< GXT Identifier
	uint32_t version;	//!< Version number
	uint32_t numTextures;	//!< Number of textures
	uint32_t dataOffset;	//!< Offset to the texture data
	uint32_t dataSize;	//!< Total size of the texture data
	uint32_t numP4Palettes;	//!< Number of 16 entry palettes
	uint32_t numP8Palettes;	//!< Number of 256 entry palettes
	uint32_t pad;		//!< Padding
} SceGxtHeader;

/** This structure contains information about each texture in the GXT file */
typedef struct SceGxtTextureInfo {
	uint32_t dataOffset;		//!< Offset to the texture data
	uint32_t dataSize;		//!< Size of the texture data
	uint32_t paletteIndex;		//!< Index of the palette
	uint32_t flags;			//!< Flags
	uint32_t controlWords[4];	//!< Texture control words
} SceGxtTextureInfo;

/**
 * Checks if a pointer is a valid GXT file.
 *
 * @param	gxt	pointer to the GXT data
 *
 * @retval	SCE_OK
 * @retval	SCE_GXT_ERROR_INVALID_VALUE Magic or version invalid
 */
SceGxtErrorCode sceGxtCheckData(const void *gxt);

/**
 * Gets the start address of the texture data.
 *
 * @param	gxt	pointer to the GXT data
 * @return A pointer to the start of the texture data
 */
const void *sceGxtGetDataAddress(const void *gxt);

/**
 * Gets the size of the texture data.
 *
 * @param	gxt	pointer to the GXT data
 * @return The size of the texture data in bytes
 */
uint32_t sceGxtGetDataSize(const void *gxt);

/**
 * Gets the header size of a GXT file.
 *
 * @param	gxt	pointer to the GXT data
 * @return The size of the header in bytes
 */
uint32_t sceGxtGetHeaderSize(const void *gxt);

/**
 * Gets the texture count in a GXT file.
 *
 * @param	gxt	pointer to the GXT data
 * @return The number of textures.
 */
uint32_t sceGxtGetTextureCount(const void *gxt);

/**
 * Sets the palette of a given texture.
 *
 * @param	texture		pointer to the texture
 * @param	gxt 		pointer to the GXT data
 * @param	textureData 	pointer to the start of texture data
 * @param	paletteIndex 	palette index
 *
 * @retval	SCE_OK
 * @retval	SCE_GXT_ERROR_INVALID_ALIGNMENT
 * @retval	SCE_GXT_ERROR_INVALID_VALUE
 * @retval	SCE_GXT_ERROR_INVALID_POINTER
 */
SceGxtErrorCode sceGxtSetPalette(SceGxmTexture *texture,
				const void *gxt,
				const void *textureData,
				uint32_t paletteIndex);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_GXT_H_ */
