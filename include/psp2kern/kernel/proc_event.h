/**
 * \kernelgroup{SceProcEvent}
 * \usage{psp2kern/kernel/proc_event.h,SceProcEventForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_PROC_EVENT_H_
#define _PSP2KERN_KERNEL_PROC_EVENT_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceProcEventInvokeParam1 {
	SceSize size;                                     // SceProcEventInvokeParam1 struct size : 0x10
	int unk_0x04;
	int unk_0x08;
	int unk_0x0C;
} SceProcEventInvokeParam1;

typedef struct SceProcEventInvokeParam2 {
	SceSize size;                                     // SceProcEventInvokeParam2 struct size : 0x14
	SceUID pid;
	int unk_0x08;
	int unk_0x0C;
	int unk_0x10;
} SceProcEventInvokeParam2;

typedef struct SceProcEventHandler {
	SceSize size;                                                                               // SceProcEventHandler struct size : 0x1C
	int (* create)(SceUID pid, SceProcEventInvokeParam2 *a2, int a3);
	int (* exit)(SceUID pid, SceProcEventInvokeParam1 *a2, int a3);                             // current process exit
	int (* kill)(SceUID pid, SceProcEventInvokeParam1 *a2, int a3);                             // by SceShell
	int (* stop)(SceUID pid, int event_type, SceProcEventInvokeParam1 *a3, int a4);
	int (* start)(SceUID pid, int event_type, SceProcEventInvokeParam1 *a3, int a4);
	int (* switch_process)(int event_id, int event_type, SceProcEventInvokeParam2 *a3, int a4); // switch display frame?
} SceProcEventHandler;

/**
 * Register process event handler
 *
 * @param[in] name    - Name of handler
 * @param[in] handler - The pointer of handler
 * @param[in] a3      - unknown, set to 0
 *
 * @return uid on success, < 0 on error.
 */
SceUID ksceKernelRegisterProcEventHandler(const char *name, const SceProcEventHandler *handler, int a3);

/**
 * Unregister process event handler
 *
 * @param[in] uid - ProcEvent uid
 *
 * @return uid on success, < 0 on error.
 */
int ksceKernelUnregisterProcEventHandler(SceUID uid);

/**
 * Invoke process event handler
 *
 * @param[in] pid        - The ProccessId
 * @param[in] event_id   - event_id, [1, 2, 3, 4, 5, 0x10, 0x11]
 * @param[in] event_type - Various event types
 * @param[in] param      - The pointer of invoke parameter
 * @param[in] a5         - Unknown
 * @param[in] a6         - Unknown
 *
 * @return uid on success, < 0 on error.
 */
int ksceKernelInvokeProcEventHandler(SceUID pid, int event_id, int event_type, void *param, void *a5, int a6);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_PROC_EVENT_H_ */
