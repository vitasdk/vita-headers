/**
 * \usergroup{SceBgAppUtil}
 * \usage{psp2/bgapputil.h,SceBgAppUtil_stub,SCE_SYSMODULE_BG_APP_UTIL}
 */


#ifndef _PSP2_BGAPPUTIL_H_
#define _PSP2_BGAPPUTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Error Codes
 */
typedef enum SceBgAppUtilErrorCode {
	SCE_BGAPP_UTIL_ERROR_INVALID_ARG = 0x80106502
} SceBgAppUtilErrorCode;

/**
 * Start BG application (eboot2.bin)
 *
 * @param[in] mode - must be 1
 *
 * @return 0 on success, <0 otherwise.
 */
int sceBgAppUtilStartBgApp(int mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_BGAPPUTIL_H_ */
