/**
 * \usergroup{SceShaccCg}
 * \externalusage{psp2/shacccg.h,SceShaccCg_stub,"path:/to/libshacccg.suprx"}
 */

#ifndef _PSP2_SHACCCG_H_
#define _PSP2_SHACCCG_H_

#include <psp2/types.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

typedef struct SceShaccCgCompileOptions SceShaccCgCompileOptions;
typedef struct SceShaccCgSourceFile SceShaccCgSourceFile;
typedef struct SceShaccCgSourceLocation SceShaccCgSourceLocation;
typedef void const *SceShaccCgParameter;

typedef SceShaccCgSourceFile* (*SceShaccCgCallbackOpenFile)(
	const char *fileName,
	const SceShaccCgSourceLocation *includedFrom,
	const SceShaccCgCompileOptions *compileOptions,
	const char **errorString);

typedef void (*SceShaccCgCallbackReleaseFile)(
	const SceShaccCgSourceFile *file,
	const SceShaccCgCompileOptions *compileOptions);

typedef const char* (*SceShaccCgCallbackLocateFile)(
	const char *fileName,
	const SceShaccCgSourceLocation *includedFrom,
	SceUInt32 searchPathCount,
	const char *const*searchPaths,
	const SceShaccCgCompileOptions *compileOptions,
	const char **errorString);

typedef const char* (*SceShaccCgCallbackAbsolutePath)(
	const char *fileName,
	const SceShaccCgSourceLocation *includedFrom,
	const SceShaccCgCompileOptions *compileOptions);

typedef void (*SceShaccCgCallbackReleaseFileName)(
	const char *fileName,
	const SceShaccCgCompileOptions *compileOptions);

typedef SceInt32 (*SceShaccCgCallbackFileDate)(
	const SceShaccCgSourceFile *file,
	const SceShaccCgSourceLocation *includedFrom,
	const SceShaccCgCompileOptions *compileOptions,
	int64_t *timeLastStatusChange,
	int64_t *timeLastModified);

typedef enum SceShaccCgDiagnosticLevel {
	SCE_SHACCCG_DIAGNOSTIC_LEVEL_INFO,
	SCE_SHACCCG_DIAGNOSTIC_LEVEL_WARNING,
	SCE_SHACCCG_DIAGNOSTIC_LEVEL_ERROR
} SceShaccCgDiagnosticLevel;

typedef enum SceShaccCgTargetProfile {
	SCE_SHACCCG_PROFILE_VP,
	SCE_SHACCCG_PROFILE_FP
} SceShaccCgTargetProfile;

typedef enum SceShaccCgCallbackDefaults {
	SCE_SHACCCG_SYSTEM_FILES,
	SCE_SHACCCG_TRIVIAL
} SceShaccCgCallbackDefaults;

typedef enum SceShaccCgLocale {
	SCE_SHACCCG_ENGLISH,
	SCE_SHACCCG_JAPANESE
} SceShaccCgLocale;

typedef struct SceShaccCgSourceFile {
	const char *fileName;
	const char *text;
	SceUInt32 size;
} SceShaccCgSourceFile;

typedef struct SceShaccCgSourceLocation {
	const SceShaccCgSourceFile *file;
	SceUInt32 lineNumber;
	SceUInt32 columnNumber;
} SceShaccCgSourceLocation;

typedef struct SceShaccCgCallbackList {
	SceShaccCgCallbackOpenFile openFile;
	SceShaccCgCallbackReleaseFile releaseFile;
	SceShaccCgCallbackLocateFile locateFile;
	SceShaccCgCallbackAbsolutePath absolutePath;
	SceShaccCgCallbackReleaseFileName releaseFileName;
	SceShaccCgCallbackFileDate fileDate;
} SceShaccCgCallbackList;

typedef struct SceShaccCgCompileOptions {
	const char *mainSourceFile;
	SceShaccCgTargetProfile targetProfile;
	const char *entryFunctionName;
	SceUInt32 searchPathCount;
	const char* const *searchPaths;
	SceUInt32 macroDefinitionCount;
	const char* const *macroDefinitions;
	SceUInt32 includeFileCount;
	const char* const *includeFiles;
	SceUInt32 suppressedWarningsCount;
	const SceUInt32 *suppressedWarnings;
	SceShaccCgLocale locale;
	SceInt32 useFx;
	SceInt32 noStdlib;
	SceInt32 optimizationLevel;
	SceInt32 useFastmath;
	SceInt32 useFastprecision;
	SceInt32 useFastint;
	int field_48;
	SceInt32 warningsAsErrors;
	SceInt32 performanceWarnings;
	SceInt32 warningLevel;
	SceInt32 pedantic;
	SceInt32 pedanticError;
	int field_60;
	int field_64;
} SceShaccCgCompileOptions;

typedef struct SceShaccCgDiagnosticMessage {
	SceShaccCgDiagnosticLevel level;
	SceUInt32 code;
	const SceShaccCgSourceLocation *location;
	const char *message;
} SceShaccCgDiagnosticMessage;

typedef struct SceShaccCgCompileOutput {
	const uint8_t *programData;
	SceUInt32 programSize;
	SceInt32 diagnosticCount;
	const SceShaccCgDiagnosticMessage *diagnostics;
} SceShaccCgCompileOutput;

int sceShaccCgInitializeCompileOptions(
	SceShaccCgCompileOptions *options);

SceShaccCgCompileOutput const *sceShaccCgCompileProgram(
	const SceShaccCgCompileOptions *options,
	const SceShaccCgCallbackList *callbacks,
	int unk);

int sceShaccCgSetDefaultAllocator(void *(*malloc_cb)(unsigned int), void (*free_cb)(void *));

void sceShaccCgInitializeCallbackList(
	SceShaccCgCallbackList *callbacks,
	SceShaccCgCallbackDefaults defaults);

void sceShaccCgDestroyCompileOutput(
	SceShaccCgCompileOutput const *output);

void sceShaccCgReleaseCompiler(void);

const char *sceShaccCgGetVersionString(void);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif /* _PSP2_SHACCCG_H_ */
