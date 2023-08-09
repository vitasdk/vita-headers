/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/event_flags.h,SceThreadmgrForDriver_stub}
 */

#ifndef _PSP2KERN_KERNEL_THREADMGR_EVENT_FLAGS_H_
#define _PSP2KERN_KERNEL_THREADMGR_EVENT_FLAGS_H_

#include <vitasdk/build_utils.h>
#include <psp2kern/types.h>
#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Get event flags info
 *
 * @param[in]  evfid - The event flags guid.
 * @param[out] info  - The info output buffer pointer.
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelGetEventFlagInfo(SceUID evfid, SceKernelEventFlagInfo *info);

/**
  * Create an event flag.
  *
  * @param name - The name of the event flag.
  * @param attr - Attributes from ::SceEventFlagAttributes
  * @param bits - Initial bit pattern.
  * @param opt  - Options, set to NULL
  * @return < 0 on error. >= 0 event flag id.
  *
  * @par Example:
  * @code
  * int evid;
  * evfid = ksceKernelCreateEventFlag("wait_event_flags", 0, 0, NULL);
  * @endcode
  */
SceUID ksceKernelCreateEventFlag(const char *name, int attr, int bits, SceKernelEventFlagOptParam *opt);

/**
  * Set an event flag bit pattern.
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  * @param bits - The bit pattern to set.
  *
  * @return < 0 On error
  */
int ksceKernelSetEventFlag(SceUID evfid, unsigned int bits);

/**
 * Clear a event flag bit pattern
 *
 * @param evid - The event id returned by ::ksceKernelCreateEventFlag
 * @param bits - The bits to clean
 *
 * @return < 0 on Error
 */
int ksceKernelClearEventFlag(SceUID evfid, unsigned int bits);

/**
  * Poll an event flag for a given bit pattern.
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @return < 0 On error
  */
int ksceKernelPollEventFlag(SceUID evfid, unsigned int bits, unsigned int wait, unsigned int *outBits);

/**
  * Wait for an event flag for a given bit pattern.
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @param timeout  - Timeout in microseconds
  * @return < 0 On error
  */
int ksceKernelWaitEventFlag(SceUID evfid, unsigned int bits, unsigned int wait, unsigned int *outBits, SceUInt *timeout);

/**
  * Wait for an event flag for a given bit pattern with callback.
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @param timeout  - Timeout in microseconds
  * @return < 0 On error
  */
int ksceKernelWaitEventFlagCB(SceUID evfid, unsigned int bits, unsigned int wait, unsigned int *outBits, SceUInt *timeout);

/**
  * Delete an event flag
  *
  * @param evid - The event id returned by ::ksceKernelCreateEventFlag.
  *
  * @return < 0 On error
  */
int ksceKernelDeleteEventFlag(SceUID evfid);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_KERNEL_THREADMGR_EVENT_FLAGS_H_ */
