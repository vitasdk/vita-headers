/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/callback.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_CALLBACK_H_
#define _PSP2KERN_KERNEL_THREADMGR_CALLBACK_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/** Callback function prototype */
typedef int (*SceKernelCallbackFunction)(int notifyId, int notifyCount, int notifyArg, void *common);

/** Structure to hold the status information for a callback */
typedef struct SceKernelCallbackInfo {
	/** Size of the structure (i.e. sizeof(SceKernelCallbackInfo)) */
	SceSize size;
	/** The UID of the callback. */
	SceUID  callbackId; // Needs confirmation
	/** The name given to the callback */
	char    name[32];
	/** The thread id associated with the callback */
	SceUID  threadId;
	/** Pointer to the callback function */
	SceKernelCallbackFunction callback;
	/** User supplied argument for the callback */
	void    *common;
	/** Unknown */
	int     notifyCount;
	/** Unknown */
	int     notifyArg;
} SceKernelCallbackInfo;

/**
 * Create callback
 *
 * @par Example:
 * @code
 * int cbid;
 * cbid = ksceKernelCreateCallback("Exit Callback", 0, exit_cb, NULL);
 * @endcode
 *
 * @param name - A textual name for the callback
 * @param func - A pointer to a function that will be called as the callback
 * @param arg  - Argument for the callback ?
 *
 * @return >= 0 A callback id which can be used in subsequent functions, < 0 an error.
 */
int ksceKernelCreateCallback(const char *name, unsigned int attr, SceKernelCallbackFunction func, void *arg);

/**
 * Delete a callback
 *
 * @param cb - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelDeleteCallback(SceUID cb);

/**
 * Notify a callback
 *
 * @param cb - The UID of the specified callback
 * @param arg2 - Passed as arg2 into the callback function
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelNotifyCallback(SceUID cb, int arg2);

/**
 * Cancel a callback ?
 *
 * @param cb - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelCancelCallback(SceUID cb);

/**
 * Get the callback count
 *
 * @param cb - The UID of the specified callback
 *
 * @return The callback count, < 0 on error
 */
int ksceKernelGetCallbackCount(SceUID cb);

/**
 * Check callback ?
 *
 * @return Something or another
 */
int ksceKernelCheckCallback(void);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_CALLBACK_H_ */
