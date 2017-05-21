/**
 * \usergroup{SceGxt}
 * \usage{psp2/gxt.h,SceGxm_stub}
 */


#ifndef _PSP2_GXT_H_
#define _PSP2_GXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <psp2/gxm.h>

/** GXT error codes */
typedef enum SceGxtErrorCode {
	SCE_OK                          = 0,
	SCE_GXT_ERROR_INVALID_VALUE     = 0x805d0000,
	SCE_GXT_ERROR_INVALID_POINTER   = 0x805d0001,
	SCE_GXT_ERROR_INVALID_ALIGNMENT = 0x805d0002
} SceGxtErrorCode;

/** Header for a GXT file */
typedef struct SceGxtHeader {
	uint32_t tag;           //!< GXT Identifier
	uint32_t version;       //!< Version number
	uint32_t numTextures;   //!< Number of textures
	uint32_t dataOffset;    //!< Offset to the texture data
	uint32_t dataSize;      //!< Total size of the texture data
	uint32_t numP4Palettes; //!< Number of 16 entry palettes
	uint32_t numP8Palettes; //!< Number of 256 entry palettes
	uint32_t pad;           //!< Padding
} SceGxtHeader;

/** This structure contains information about each texture in the GXT file */
typedef struct SceGxtTextureInfo {
	uint32_t dataOffset;        //!< Offset to the texture data
	uint32_t dataSize;          //!< Size of the texture data
	uint32_t paletteIndex;      //!< Index of the palette
	uint32_t flags;             //!< Flags
	uint32_t controlWords[4];   //!< Texture control words
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

