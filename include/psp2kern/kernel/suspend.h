/**
 * \kernelgroup{SceSuspend}
 * \usage{psp2kern/kernel/suspend.h,SceKernelSuspendForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_SUSPEND_H_
#define _PSP2KERN_KERNEL_SUSPEND_H_

#include <psp2common/kernel/processmgr.h>
#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * System suspend/resume event handler.
 *
 * @param[in] resume - Zero while suspending, or one while resuming.
 * @param[in] event_id - Event identifier.
 * @param[in] event_param - Event data supplied to ::ksceKernelSysEventDispatch.
 * @param[in] args - Private argument supplied when registering the handler.
 *
 * @return 0 on success, < 0 on error.
 */
typedef int (*SceSysEventHandler)(int resume, int event_id, void *event_param, void *args);


/**
 * Cancel specified idle timers to prevent entering in power save processing.
 *
 * @param[in] type - One of ::SceKernelPowerTickType
 *
 * @return 0
*/
int ksceKernelPowerTick(SceKernelPowerTickType type);

/**
 * Register system event handler
 *
 * @param[in] name - Name of handler
 * @param[in] handler - The handler
 * @param[in] args - Handler arguments
 *
 * @return 0 on success, < 0 on error.
*/
int ksceKernelRegisterSysEventHandler(const char *name, SceSysEventHandler handler, void *args);

/**
 * Call registered handlers for a suspend or resume event.
 *
 * If a handler fails and \p failed_handler_id is non-NULL, stop calling handlers
 * and write the failing handler's UID to *failed_handler_id. If \p failed_handler_id
 * is NULL, continue calling handlers after failures and return the last
 * handler's result.
 *
 * @param[in] resume - Zero while suspending, or one while resuming.
 * @param[in] event_id - Event identifier.
 * @param[in] event_param - Event data passed to each handler that is called.
 * @param[out] failed_handler_id - Optional output for the first failing handler UID.
 *
 * @return The result from the last handler called, or 0 when no handler is registered.
 */
int ksceKernelSysEventDispatch(SceBool resume, SceUInt32 event_id, void *event_param, SceUID *failed_handler_id);

/**
 * Unregister a system event handler.
 *
 * @param[in] handler_id - UID returned by ::ksceKernelRegisterSysEventHandler.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceKernelUnregisterSysEventHandler(SceUID handler_id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_SUSPEND_H_ */
