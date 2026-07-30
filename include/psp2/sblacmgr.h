/**
 * \usergroup{SceSblACMgr}
 * \usage{psp2/sblacmgr.h,SceSblACMgr_stub}
 */


#ifndef _PSP2_SBLACMGR_H_
#define _PSP2_SBLACMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

SceInt32 sceSblACMgrIsGameProgram(SceBool *result);

/**
 * Check whether the calling process is a game program.
 *
 * @param[out] pResult - Required pointer to a four-byte value that receives 1
 *                      if the calling process is a game program, otherwise 0.
 *
 * @return 0 on success, < 0 on error.
 */
int _sceSblACMgrIsGameProgram(int *pResult);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLACMGR_H_ */
