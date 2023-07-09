/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/callback.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_CALLBACK_H_
#define _PSP2_KERNEL_THREADMGR_CALLBACK_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Callback function prototype */
typedef int (* SceKernelCallbackFunction)(int notifyId, int notifyCount, int notifyArg, void *userData);

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
VITASDK_BUILD_ASSERT_EQ(0x3C, SceKernelCallbackInfo);

/**
 * Create callback
 *
 * @par Example:
 * @code
 * int cbid;
 * cbid = sceKernelCreateCallback("Exit Callback", 0, exit_cb, NULL);
 * @endcode
 *
 * @param name      - A textual name for the callback
 * @param attr      - ?
 * @param func      - A pointer to a function that will be called as the callback
 * @param userData  - User defined data to be passed to the callback.
 *
 * @return >= 0 A callback id which can be used in subsequent functions, < 0 an error.
 */
int sceKernelCreateCallback(const char *name, unsigned int attr, SceKernelCallbackFunction func, void *userData);

/**
  * Gets the status of a specified callback.
  *
  * @param cb - The UID of the callback to retrieve info for.
  * @param status - Pointer to a status structure. The size parameter should be
  * initialised before calling.
  *
  * @return < 0 on error.
  */
int sceKernelGetCallbackInfo(SceUID cb, SceKernelCallbackInfo *infop);

/**
 * Delete a callback
 *
 * @param cb - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelDeleteCallback(SceUID cb);

/**
 * Notify a callback
 *
 * @param cb - The UID of the specified callback
 * @param arg2 - Passed as arg2 into the callback function
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelNotifyCallback(SceUID cb, int arg2);

/**
 * Cancel a callback ?
 *
 * @param cb - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelCancelCallback(SceUID cb);

/**
 * Get the callback count
 *
 * @param cb - The UID of the specified callback
 *
 * @return The callback count, < 0 on error
 */
int sceKernelGetCallbackCount(SceUID cb);

/**
 * Check callback ?
 *
 * @return Something or another
 */
int sceKernelCheckCallback(void);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_CALLBACK_H_ */
