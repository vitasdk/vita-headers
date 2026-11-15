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
 * Coredump handler invoked on a dedicated user thread.
 *
 * The internal thread entry point calls this handler with the registered
 * \p handler_arg.
 *
 * @param[in] handler_arg Argument registered with
 * ::sceCoredumpRegisterCoredumpHandler.
 * @return The return value is ignored by the coredump path on FW 3.60.
 */
typedef int (*SceCoredumpHandler)(void *handler_arg);

/**
 * Registers a callback that can append application-specific data to a coredump.
 *
 * The callback runs on a dedicated user thread whose stack has the requested
 * size. FW 3.60 waits up to three seconds for the callback. The target process
 * is suspended while it runs, so the callback must not issue ordinary system
 * calls; it should use ::sceCoredumpWriteUserData to append data.
 *
 * @param[in] handler Pointer to a ::SceCoredumpHandler function.
 * @param[in] stack_size Stack size of the thread used to invoke the handler.
 * Must be at least 0x1000 bytes on FW 3.60.
 * @param[in] handler_arg Argument passed to the handler. When non-NULL,
 * FW 3.60 probes exactly 4 readable bytes at registration time. It must remain
 * valid until the handler is unregistered.
 *
 * @retval 0 Success.
 * @retval 0x800A0000 Invalid handler, stack size, or handler argument, or
 * failure to allocate the handler stack.
 * @retval 0x800A0002 A handler is already registered for this process.
 */
int sceCoredumpRegisterCoredumpHandler(SceCoredumpHandler handler, SceSize stack_size, void *handler_arg);

/**
 * Unregisters the current process's coredump handler.
 *
 * @retval 0 Success.
 * @retval 0x800A0001 No handler is registered for this process.
 */
int sceCoredumpUnregisterCoredumpHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_COREDUMP_H_ */
