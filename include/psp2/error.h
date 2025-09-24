/**
 * \usergroup{SceError}
 * \usage{psp2/error.h,SceError_stub}
 */


#ifndef _PSP2_ERROR_H_
#define _PSP2_ERROR_H_

/**
 * Convert an internal error code to an external one
 *
 * @param[out] error_string - External error code
 * @param[in] error_code - Internal error code
 *
 * @return 0 on success, < 0 on error.
 */
int _sceErrorGetExternalString(char* error_string, int error_code);
 
#endif //_PSP2_ERROR_H_