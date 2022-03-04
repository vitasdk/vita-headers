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
	SCE_GXT_ERROR_INVALID_VALUE     = 0x805D0000,
	SCE_GXT_ERROR_INVALID_POINTER   = 0x805D0001,
	SCE_GXT_ERROR_INVALID_ALIGNMENT = 0x805D0002
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
	uint32_t flags;             //!< Texture flags
	uint32_t type;              //!< Texture type
	uint32_t format;            //!< Texture format
	uint16_t width;             //!< Texture width
	uint16_t height;            //!< Texture height
	uint8_t mipCount;           //!< Number of mipmaps
	uint8_t pad[3];             //!< Padding
} SceGxtTextureInfo;

/**
 * Gets the start address of the texture data.
 *
 * @param	gxt	pointer to the GXT data
 * @return A pointer to the start of the texture data
 */
const void *sceGxtGetDataAddress(const void *gxt);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_GXT_H_ */

