/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/workqueues.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2KERN_KERNEL_THREADMGR_WORKQUEUES_H_
#define _PSP2KERN_KERNEL_THREADMGR_WORKQUEUES_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef int (* SceKernelWorkQueueWorkFunction)(void *args);

/**
 * @brief      Enqueue work to a workqueue
 *
 * @param[in]  uid  UID of the workqueue (0x10023 for the SceKernelGlobalWorkQueue)
 * @param[in]  name Name of the work to enqueue
 * @param[in]  work Work function to enqueue
 * @param[in]  args Argument to pass to the work function
 *
 * @return     Zero on success
 */
int ksceKernelEnqueueWorkQueue(SceUID uid, const char *name, SceKernelWorkQueueWorkFunction work, void *args);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_WORKQUEUES_H_ */
