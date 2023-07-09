/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr.h,SceKernelThreadMgr_stub}
 */

#ifndef _PSP2_KERNEL_THREADMGR_H_
#define _PSP2_KERNEL_THREADMGR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceKernelWaitableAttribute {
	SCE_KERNEL_ATTR_THREAD_FIFO  = 0x00000000, //!< Waiting threads First input First output
	SCE_KERNEL_ATTR_THREAD_PRIO  = 0x00002000, //!< Waiting threads queued on priority basis
	SCE_KERNEL_ATTR_OPENABLE     = 0x00000080  //!< Sync object can be accessed by sceKernelOpenXxx
} SceKernelWaitableAttribute;

#ifdef __cplusplus
}
#endif

#include <vitasdk/build_utils.h>
#include <psp2/kernel/threadmgr/callback.h>
#include <psp2/kernel/threadmgr/cond.h>
#include <psp2/kernel/threadmgr/eventflag.h>
#include <psp2/kernel/threadmgr/lw_cond.h>
#include <psp2/kernel/threadmgr/lw_mutex.h>
#include <psp2/kernel/threadmgr/msgpipe.h>
#include <psp2/kernel/threadmgr/mutex.h>
#include <psp2/kernel/threadmgr/rwlock.h>
#include <psp2/kernel/threadmgr/semaphore.h>
#include <psp2/kernel/threadmgr/signal.h>
#include <psp2/kernel/threadmgr/thread.h>

#endif /* _PSP2_KERNEL_THREADMGR_H_ */

