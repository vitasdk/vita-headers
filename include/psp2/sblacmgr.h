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

/**
 * Check whether the calling process is a game program.
 *
 * This SceLibKernel wrapper calls ::_sceSblACMgrIsGameProgram.
 *
 * @param[out] result - Must be non-NULL. Receives 1 for a game program,
 *                      or 0 otherwise.
 *
 * @return SCE_OK on success, 0x800F0916 if \a result is NULL, or
 *         an error copying the result to user memory.
 */
SceInt32 sceSblACMgrIsGameProgram(SceBool *result);

/**
 * Check whether the calling process is a game program.
 *
 * @param[out] result - Must point to a four-byte value. Receives 1 if the
 *                      calling process is a game program, otherwise 0.
 *
 * @return SCE_OK on success, 0x800F0916 if \a result is NULL, or
 *         an error copying the result to user memory.
 */
int _sceSblACMgrIsGameProgram(int *result);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLACMGR_H_ */
