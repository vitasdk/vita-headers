/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/signal.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_SIGNAL_H_
#define _PSP2_KERNEL_THREADMGR_SIGNAL_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Sleep current thread and wait for a signal. After it receives a signal, the thread wakes up.
 *
 * This is like a semphore with limit 1.
 * If signal was sent before and not consumed before, the function will immediately return.
 * @param unk0 unknown parameter. 0 can be used.
 * @param delay the delay before wating for a signal
 * @param timeout the timeout if it's null, it waits indefinitely.
 * @return 0 on success
 */
int sceKernelWaitSignal(SceUInt32 unk0, SceUInt32 delay, SceUInt32 *timeout);

/**
 * @brief Send a signal to the thread specified by thid. Note that it can send a signal to the current thread as well.
 *
 * @param thid - the id of the thread to send a signal to
 * @return 0 on success
 * @return SCE_KERNEL_ERROR_ALREADY_SENT if the last signal was not consumed by sceKernelWaitSignal
 */
int sceKernelSendSignal(SceUID thid);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_SIGNAL_H_ */
