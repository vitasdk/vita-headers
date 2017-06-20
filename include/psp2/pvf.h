/**
 * \usergroup{ScePvf}
 * \usage{psp2/pvf.h,ScePvf_stub}
 */


#ifndef _PSP2_PVF_H_
#define _PSP2_PVF_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus

extern "C" {
#endif

#define SCE_PVF_MAX_OPEN	18

typedef enum ScePvfErrorCode {
	SCE_PVF_ERROR_NOMEMORY         = 0x80460001,
	SCE_PVF_ERROR_LIBID            = 0x80460002,
	SCE_PVF_ERROR_ARG              = 0x80460003,
	SCE_PVF_ERROR_NOFILE           = 0x80460004,
	SCE_PVF_ERROR_FILEOPEN         = 0x80460005,
	SCE_PVF_ERROR_FILECLOSE        = 0x80460006,
	SCE_PVF_ERROR_FILEREAD         = 0x80460007,
	SCE_PVF_ERROR_FILESEEK         = 0x80460008,
	SCE_PVF_ERROR_TOOMANYOPENED    = 0x80460009,
	SCE_PVF_ERROR_ILLEGALVERSION   = 0x8046000A,
	SCE_PVF_ERROR_DATAINCONSISTENT = 0x8046000B,
	SCE_PVF_ERROR_EXPIRED          = 0x8046000C,
	SCE_PVF_ERROR_NOSUPPORT        = 0x8046000E,
	SCE_PVF_ERROR_NOGLYPH          = 0x8046000F,
	SCE_PVF_ERROR_UNKNOWN          = 0x8046FFFF
} ScePvfErrorCode;

typedef enum ScePvfFamilyCode {
	SCE_PVF_DEFAULT_FAMILY_CODE = 0,
	SCE_PVF_FAMILY_SANSERIF     = 1,
	SCE_PVF_FAMILY_SERIF        = 2,
	SCE_PVF_FAMILY_ROUNDED      = 3
} ScePvfFamilyCode;

typedef enum ScePvfStyleCode {
	SCE_PVF_DEFAULT_STYLE_CODE    = 0,
	SCE_PVF_STYLE_REGULAR         = 1,
	SCE_PVF_STYLE_OBLIQUE         = 2,
	SCE_PVF_STYLE_NARROW          = 3,
	SCE_PVF_STYLE_NARROW_OBLIQUE  = 4,
	SCE_PVF_STYLE_BOLD            = 5,
	SCE_PVF_STYLE_BOLD_OBLIQUE    = 6,
	SCE_PVF_STYLE_BLACK           = 7,
	SCE_PVF_STYLE_BLACK_OBLIQUE   = 8,
	SCE_PVF_STYLE_L               = 101,
	SCE_PVF_STYLE_M               = 102,
	SCE_PVF_STYLE_DB              = 103,
	SCE_PVF_STYLE_B               = 104,
	SCE_PVF_STYLE_EB              = 105,
	SCE_PVF_STYLE_UB              = 106
} ScePvfStyleCode;

typedef enum ScePvfImageByfferPixelFormatType {
	SCE_PVF_USERIMAGE_DIRECT4_L = 0,
	SCE_PVF_USERIMAGE_DIRECT8   = 2
} ScePvfImageByfferPixelFormatType;

typedef enum ScePvfLanguageCode {
	SCE_PVF_DEFAULT_LANGUAGE_CODE = 0,
	SCE_PVF_LANGUAGE_J            = 1,
	SCE_PVF_LANGUAGE_LATIN        = 2,
	SCE_PVF_LANGUAGE_K            = 3,
	SCE_PVF_LANGUAGE_C            = 4,
	SCE_PVF_LANGUAGE_CJK          = 5
} ScePvfLanguageCode;

typedef enum ScePvfRegionCode {
	SCE_PVF_GENERIC_REGION_CODE = 0,
	SCE_PVF_REGION_001          = 1,
	SCE_PVF_REGION_002          = 2,
	SCE_PVF_REGION_003          = 3,
	SCE_PVF_REGION_004          = 4,
	SCE_PVF_REGION_005          = 5,
	SCE_PVF_REGION_006          = 6,
	SCE_PVF_REGION_007          = 7
} ScePvfRegionCode;

typedef enum ScePvfFontVendorCountryCode {
	SCE_PVF_GENERIC_COUNTRY_CODE  = 0,
	SCE_PVF_COUNTRY_JAPAN         = 1,
	SCE_PVF_COUNTRY_USA           = 2,
	SCE_PVF_COUNTRY_KOREA         = 3
} ScePvfFontVendorCountryCode;

typedef enum ScePvfBoolValue {
	SCE_PVF_FALSE       = 0,
	SCE_PVF_TRUE        = 1
} ScePvfBoolValue;

typedef enum ScePvfSubstyle {
	SCE_PVF_SUBSTYLE_VERTICALLAYOUT = 0x0001,
	SCE_PVF_SUBSTYLE_PSEUDO_BOLD    = 0x0002,
	SCE_PVF_SUBSTYLE_PSEUDO_SLANT   = 0x0004
} ScePvfSubstyle;

#define SCE_PVF_FONTNAME_LENGTH     64
#define SCE_PVF_STYLENAME_LENGTH    64
#define SCE_PVF_FONTFILENAME_LENGTH 64

typedef enum ScePvfDataAccessMode {
	SCE_PVF_FILEBASEDSTREAM     = 0,
	SCE_PVF_MEMORYBASEDSTREAM   = 1
} ScePvfDataAccessMode;

#define SCE_PVF_MIN_EMBOLDEN_RATE   -20.0f
#define SCE_PVF_MAX_EMBOLDEN_RATE   40.0f
#define SCE_PVF_MIN_SKEW_VALUE      -30.0f
#define SCE_PVF_MAX_SKEW_VALUE      30.0f

typedef unsigned int  ScePvfU32;
typedef signed	 int  ScePvfS32;
typedef unsigned short ScePvfU16;
typedef unsigned char  ScePvfU8;
typedef float	   ScePvfFloat32;
typedef ScePvfU32  ScePvfBool;
typedef void *ScePvfLibId;
typedef void *ScePvfFontId;
typedef void *ScePvfPointer;
typedef void *ScePvfHandle;
typedef ScePvfS32 ScePvfError;
typedef ScePvfS32 ScePvfInt;
typedef ScePvfU16 ScePvfCharCode;
typedef ScePvfS32 ScePvfFontIndex;

typedef struct ScePvfIrect {
	ScePvfU16 width;
	ScePvfU16 height;
} ScePvfIrect;

typedef struct ScePvfRect {
	ScePvfU32 width;
	ScePvfU32 height;
} ScePvfRect;

typedef ScePvfS32 (*ScePvfFontCacheLockFunc)(ScePvfPointer cacheInstance);

typedef ScePvfS32 (*ScePvfFontChcheUnlockFunc)(ScePvfPointer cacheInstance);

typedef ScePvfPointer (*ScePvfFontChcheFindFunc)(ScePvfPointer chcheInstance,
	ScePvfU32 hashValue, ScePvfPointer key, ScePvfBool *result);

typedef ScePvfS32 (*ScePvfFontChcheWriteKeyValueToCacheFunc)(ScePvfPointer cacheInstance,
	ScePvfPointer chcheSlot, ScePvfPointer key);

typedef ScePvfS32 (*ScePvfFontChcheWriteToCacheFunc)(ScePvfPointer cacheInstance,
	ScePvfPointer cacheSlot, ScePvfPointer data0, ScePvfInt size);

typedef ScePvfS32 (*ScePvfFontChcheReadFromCacheFunc)(ScePvfPointer cacheInstance,
	ScePvfPointer cacheSlot, ScePvfPointer data0);

typedef struct ScePvfCacheSystemInterface {
	ScePvfPointer *cacheInstance;
	ScePvfFontCacheLockFunc lockFunc;
	ScePvfFontChcheUnlockFunc unlockFunc;
	ScePvfFontChcheFindFunc	findFunc;
	ScePvfFontChcheWriteKeyValueToCacheFunc writeKeyValueToCacheFunc;
	ScePvfFontChcheWriteToCacheFunc write0ToCacheFunc;
	ScePvfFontChcheWriteToCacheFunc write1ToCacheFunc;
	ScePvfFontChcheReadFromCacheFunc read0FromCacheFunc;
	ScePvfFontChcheReadFromCacheFunc read1FromCacheFunc;
} ScePvfCacheSystemInterface;

typedef ScePvfPointer (*ScePvfAllocFunc)(ScePvfPointer userData, ScePvfU32 size);

typedef ScePvfPointer (*ScePvfReallocFunc)(ScePvfPointer userData, ScePvfPointer old_ptr,
	ScePvfU32 size);

typedef void (*ScePvfFreeFunc)(ScePvfPointer userData, ScePvfPointer ptr);

typedef struct ScePvfInitRec {
	ScePvfPointer userData;
	ScePvfU32 maxNumFonts;
	ScePvfCacheSystemInterface *cache;
	ScePvfPointer reserved;
	ScePvfAllocFunc allocFunc;
	ScePvfReallocFunc reallocFunc;
	ScePvfFreeFunc freeFunc;
} ScePvfInitRec;

typedef struct ScePvfFontStyleInfo {
	ScePvfFloat32 weight;
	ScePvfU16 familyCode;
	ScePvfU16 style;
	ScePvfU16 subStyle; //<! One of ::ScePvfSubstyle
	ScePvfU16 languageCode;
	ScePvfU16 regionCode;
	ScePvfU16 countryCode;
	ScePvfU8 fontName [SCE_PVF_FONTNAME_LENGTH];
	ScePvfU8 styleName [SCE_PVF_STYLENAME_LENGTH];
	ScePvfU8 fileName [SCE_PVF_FONTFILENAME_LENGTH];
	ScePvfU32 extraAttributes;
	ScePvfU32 expireDate;
} ScePvfFontStyleInfo;

typedef struct ScePvfUserImageBufferRec {
	ScePvfU32 pixelFormat;
	ScePvfS32 xPos64;
	ScePvfS32 yPos64;
	ScePvfIrect rect;
	ScePvfU16 bytesPerLine;
	ScePvfU16 reserved;
	ScePvfU8 *buffer;
} ScePvfUserImageBufferRec;

typedef struct ScePvfIGlyphMetricsInfo {
	ScePvfU32 width64;
	ScePvfU32 height64;
	ScePvfS32 ascender64;
	ScePvfS32 descender64;
	ScePvfS32 horizontalBearingX64;
	ScePvfS32 horizontalBearingY64;
	ScePvfS32 verticalBearingX64;
	ScePvfS32 verticalBearingY64;
	ScePvfS32 horizontalAdvance64;
	ScePvfS32 verticalAdvance64;
} ScePvfIGlyphMetricsInfo;

typedef struct ScePvfCharInfo {
	ScePvfU32 bitmapWidth;
	ScePvfU32 bitmapHeight;
	ScePvfU32 bitmapPitch;
	ScePvfS32 bitmapLeft;
	ScePvfS32 bitmapTop;
	ScePvfIGlyphMetricsInfo glyphMetrics;
	ScePvfU8 reserved0 [2];
	ScePvfU16 reserved1;
} ScePvfCharInfo;

typedef struct ScePvfFGlyphMetricsInfo {
	ScePvfFloat32 width;
	ScePvfFloat32 height;
	ScePvfFloat32 ascender;
	ScePvfFloat32 descender;
	ScePvfFloat32 horizontalBearingX;
	ScePvfFloat32 horizontalBearingY;
	ScePvfFloat32 verticalBearingX;
	ScePvfFloat32 verticalBearingY;
	ScePvfFloat32 horizontalAdvance;
	ScePvfFloat32 verticalAdvance;
} ScePvfFGlyphMetricsInfo;

typedef struct ScePvfFontInfo {
	ScePvfIGlyphMetricsInfo maxIGlyphMetrics;
	ScePvfFGlyphMetricsInfo maxFGlyphMetrics;
	ScePvfU32 numChars;
	ScePvfFontStyleInfo fontStyleInfo;
	ScePvfU8 reserved [4];
} ScePvfFontInfo;

typedef struct ScePvfIKerningInfo {
	ScePvfS32 xOffset64;
	ScePvfS32 yOffset64;
} ScePvfIKerningInfo;

typedef struct ScePvfFKerningInfo {
	ScePvfFloat32 xOffset;
	ScePvfFloat32 yOffset;
} ScePvfFKerningInfo;

typedef struct ScePvfKerningInfo {
	ScePvfIKerningInfo iKerningInfo;
	ScePvfFKerningInfo fKerningInfo;
} ScePvfKerningInfo;

typedef struct ScePvfCacheKey {
	int keyValue0;
	int keyValue1;
	float keyValue2;
	float keyValue3;
	float keyValue4;
	float keyValue5;
	float keyValue6;
	float keyValue7;
	float keyValue8;
} ScePvfCacheKey;

ScePvfLibId scePvfNewLib(ScePvfInitRec *initParam, ScePvfError *errorCode);

ScePvfError scePvfDoneLib(ScePvfLibId libID);

ScePvfError scePvfSetEM(ScePvfLibId libID, ScePvfFloat32 emValue);

ScePvfError scePvfSetResolution(ScePvfLibId libID, ScePvfFloat32 hResolution,
	ScePvfFloat32 vResolution);

ScePvfInt scePvfGetNumFontList(ScePvfLibId libID, ScePvfError *errorCode);

ScePvfError scePvfGetFontList(ScePvfLibId libID, ScePvfFontStyleInfo *fontStyleInfo,
	ScePvfInt arraySize);

ScePvfFontIndex scePvfFindOptimumFont(ScePvfLibId libID, ScePvfFontStyleInfo *fontStyleInfo,
	ScePvfError *errorCode);

ScePvfFontIndex scePvfFindFont(ScePvfLibId libID, ScePvfFontStyleInfo *fontStyleInfo,
	ScePvfError *errorCode);

ScePvfError scePvfGetFontInfoByIndexNumber(ScePvfLibId libID, ScePvfFontStyleInfo *fontStyleInfo,
	ScePvfFontIndex fontIndex);

ScePvfFontId scePvfOpen(ScePvfLibId libID, ScePvfFontIndex fontIndex, ScePvfU32 mode,
	ScePvfError *errorCode);

ScePvfFontId scePvfOpenUserFile(ScePvfLibId libID, ScePvfPointer filename, ScePvfU32 mode,
	ScePvfError *errorCode);

ScePvfFontId scePvfOpenUserFileWithSubfontIndex(ScePvfLibId libID, ScePvfPointer filename,
	ScePvfU32 mode, ScePvfU32 subFontIndex, ScePvfError *errorCode);

ScePvfFontId scePvfOpenUserMemory(ScePvfLibId libID, ScePvfPointer addr, ScePvfU32 size,
	ScePvfError *errorCode);

ScePvfFontId scePvfOpenUserMemoryWithSubfontIndex(ScePvfLibId libID, ScePvfPointer addr,
	ScePvfU32 size, ScePvfU32 subFontIndex, ScePvfError *errorCode);

ScePvfFontId scePvfOpenDefaultJapaneseFontOnSharedMemory(ScePvfLibId libID, ScePvfError *errorCode);

ScePvfFontId scePvfOpenDefaultLatinFontOnSharedMemory(ScePvfLibId libID, ScePvfError *errorCode);

ScePvfError scePvfClose(ScePvfFontId fontID);

ScePvfError scePvfFlush(ScePvfFontId fontID);

ScePvfError scePvfSetCharSize(ScePvfFontId fontID, ScePvfFloat32 hSize, ScePvfFloat32 vSize);

ScePvfError scePvfSetEmboldenRate(ScePvfFontId fontID, ScePvfFloat32 emboldenRate);

ScePvfError scePvfSetSkewValue(ScePvfFontId fontID, ScePvfFloat32 angleX, ScePvfFloat32 angleY);

ScePvfBool scePvfIsElement(ScePvfFontId fontID, ScePvfCharCode charCode);

ScePvfError scePvfGetFontInfo(ScePvfFontId fontID, ScePvfFontInfo *fontInfo);

ScePvfError scePvfGetCharInfo(ScePvfFontId fontID, ScePvfCharCode charCode, ScePvfCharInfo *charInfo);

ScePvfError scePvfGetKerningInfo(ScePvfFontId fontID, ScePvfCharCode leftCharCode,
	ScePvfCharCode rightCharCode, ScePvfKerningInfo *pKerningInfo);

ScePvfError scePvfGetCharImageRect(ScePvfFontId fontID, ScePvfCharCode charCode, ScePvfIrect *rect);

ScePvfError scePvfGetCharGlyphImage(ScePvfFontId fontID, ScePvfCharCode charCode, ScePvfUserImageBufferRec *imageBuffer);

ScePvfError scePvfGetCharGlyphImage_Clip(ScePvfFontId fontID, ScePvfCharCode charCode,
	ScePvfUserImageBufferRec *imageBuffer, ScePvfS32 clipX, ScePvfS32 clipY, ScePvfU32 clipWidth, ScePvfU32 clipHeight);

#define scePvfGetCharGlyphImageClip scePvfGetCharGlyphImage_Clip

ScePvfFloat32 scePvfPixelToPointH(ScePvfLibId libID, ScePvfFloat32 pixel, ScePvfError *errorCode);

ScePvfFloat32 scePvfPixelToPointV(ScePvfLibId libID, ScePvfFloat32 pixel, ScePvfError *errorCode);

ScePvfFloat32 scePvfPointToPixelH(ScePvfLibId libID, ScePvfFloat32 point, ScePvfError *errorCode);

ScePvfFloat32 scePvfPointToPixelV(ScePvfLibId libID, ScePvfFloat32 point, ScePvfError *errorCode);

ScePvfError scePvfSetAltCharacterCode(ScePvfLibId libID, ScePvfCharCode charCode);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PVF_H_ */
