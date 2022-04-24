/**
 * \kernelgroup{SceSblACMgr}
 * \usage{psp2kern/sblacmgr.h,SceSblACMgrForDriver_stub}
 */

#ifndef _PSP2KERN_SBLACMGR_H_
#define _PSP2KERN_SBLACMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If root mode process, 1. else 0.
 */
int ksceSblACMgrIsRootProgram(SceUID pid);

#define ksceSblACMgrIsSystem(pid) ksceSblACMgrIsRootProgram(pid)

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If system mode process, 1. else 0.
 */
int ksceSblACMgrIsSystemProgram(SceUID pid);

#define ksceSblACMgrIsShell(pid) ksceSblACMgrIsSystemProgram(pid)

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If game mode process, 1. else 0.
 */
int ksceSblACMgrIsGameProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If non game mode process, 1. else 0.
 */
int ksceSblACMgrIsNonGameProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If pspemu process, 1. else 0.
 */
int ksceSblACMgrIsPspEmu(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If SceShell process(authid:0x2800000000000001), 1. else 0.
 */
int ksceSblACMgrIsSceShell(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If fake self process, 1. else 0.
 */
int ksceSblACMgrIsFself(SceUID pid);

/**
 * @brief Get process authority id
 *
 * @param[in]  pid    - The target process id
 * @param[out] authid - The authid output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblACMgrGetProcessProgramAuthId(SceUID pid, SceUInt64 *authid);

/**
 * @brief Get development mode state
 *
 * @return If development mode, 1. else 0.
 */
int ksceSblACMgrIsDevelopmentMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_SBLACMGR_H_ */
