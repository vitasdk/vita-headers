/**
 * \kernelgroup{SceSblACMgr}
 * \usage{psp2kern/sblacmgr.h,SceSblACMgrForDriver_stub}
 */

#ifndef _PSP2_KERNEL_SBLACMGR_H_
#define _PSP2_KERNEL_SBLACMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get process type state
 *
 * @return If root mode process, 1. else 0.
 */
int ksceSblACMgrIsSystem(SceUID pid);

#define ksceSblACMgrIsRootProgram(pid) ksceSblACMgrIsSystem(pid)

/**
 * @brief Get process type state
 *
 * @return If system mode process, 1. else 0.
 */
int ksceSblACMgrIsShell(SceUID pid);

#define ksceSblACMgrIsSystemProgram(pid) ksceSblACMgrIsShell(pid)

/**
 * @brief Get process type state
 *
 * @return If game mode process, 1. else 0.
 */
int ksceSblACMgrIsGameProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @return If non game mode process, 1. else 0.
 */
int ksceSblACMgrIsNonGameProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @return If pspemu process, 1. else 0.
 */
int ksceSblACMgrIsPspEmu(SceUID pid);

/**
 * @brief Get process type state
 *
 * @return If SceShell process(authid:0x2800000000000001), 1. else 0.
 */
int ksceSblACMgrIsSceShell(SceUID pid);

/**
 * @brief Get process type state
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

#endif /* _PSP2_KERNEL_SBLACMGR_H_ */
