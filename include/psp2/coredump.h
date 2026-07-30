/**
 * \usergroup{SceCoredump}
 * \usage{psp2/coredump.h,SceCoredump_stub}
 */

#ifndef _PSP2_COREDUMP_H_
#define _PSP2_COREDUMP_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Coredump handler invoked on a dedicated thread.
 *
 * @param[in] handler_arg Argument registered with
 * ::sceCoredumpRegisterCoredumpHandler.
 */
typedef int (*SceCoredumpHandler)(void *handler_arg);

/**
 * Registers a callback that can append application-specific data to a coredump.
 *
 * @param[in] handler Pointer to a ::SceCoredumpHandler function.
 * @param[in] stack_size Stack size of the thread used to invoke the handler.
 * Must be at least 0x1000 bytes on FW 3.60.
 * @param[in] handler_arg Argument passed to the handler. When non-NULL, it must
 * point to at least 16 readable bytes on FW 3.60.
 *
 * @return 0 on success, < 0 on error.
 */
int sceCoredumpRegisterCoredumpHandler(void *handler, SceSize stack_size, void *handler_arg);

/**
 * Unregisters the current process's coredump handler.
 *
 * @return 0 on success, < 0 on error.
 */
int sceCoredumpUnregisterCoredumpHandler(void);

/**
 * Appends data to the current coredump's user-data section.
 *
 * This function is intended to be called from a ::SceCoredumpHandler. The
 * destination is limited to 0x4000 bytes on FW 3.60.
 *
 * @param[in] data Data to append.
 * @param[in] size Number of bytes requested.
 *
 * @return The number of bytes appended, which can be less than \p size when
 * the destination is full, or < 0 on error. The return value has
 * ::SceSSize semantics despite the published \c int type.
 */
int sceCoredumpWriteUserData(const void *data, SceSize size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_COREDUMP_H_ */
