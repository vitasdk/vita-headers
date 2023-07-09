/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/eventflag.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_EVENTFLAG_H_
#define _PSP2_KERNEL_THREADMGR_EVENTFLAG_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2/kernel/threadmgr.h> // temp

#ifdef __cplusplus
extern "C" {
#endif


typedef enum SceEventFlagAttributes {
	SCE_DEPRECATED(SCE_EVENT_THREAD_FIFO) = SCE_KERNEL_ATTR_THREAD_FIFO, //!< Use SCE_KERNEL_ATTR_THREAD_FIFO
	SCE_DEPRECATED(SCE_EVENT_THREAD_PRIO) = SCE_KERNEL_ATTR_THREAD_PRIO, //!< Use SCE_KERNEL_ATTR_THREAD_PRIO
	SCE_EVENT_WAITSINGLE   = 0,          //!< Sync object can only be waited upon by one thread.
	SCE_EVENT_WAITMULTIPLE = 0x00001000, //!< Sync object can be waited upon by multiple threads.
	SCE_DEPRECATED(SCE_EVENT_OPENABLE) = SCE_KERNEL_ATTR_OPENABLE //!< Use SCE_KERNEL_ATTR_OPENABLE
} SceEventFlagAttributes;

/** Structure to hold the event flag information */
typedef struct SceKernelEventFlagInfo {
	SceSize size;
	SceUID  evfId;          // Needs confirmation
	char    name[32];
	SceUInt attr;
	SceUInt initPattern;
	SceUInt currentPattern;
	int     numWaitThreads;
} SceKernelEventFlagInfo;
VITASDK_BUILD_ASSERT_EQ(0x38, SceKernelEventFlagInfo);

typedef struct SceKernelEventFlagOptParam {
	SceSize         size;
} SceKernelEventFlagOptParam;
VITASDK_BUILD_ASSERT_EQ(4, SceKernelEventFlagOptParam);

/** Event flag wait types */
typedef enum SceEventFlagWaitTypes {
	/** Wait for all bits in the pattern to be set */
	SCE_EVENT_WAITAND       = 0,
	/** Wait for one or more bits in the pattern to be set */
	SCE_EVENT_WAITOR        = 1,
	/** Clear all the bits when it matches */
	SCE_EVENT_WAITCLEAR     = 2,
	/** Clear the wait pattern when it matches */
	SCE_EVENT_WAITCLEAR_PAT = 4
} SceEventFlagWaitTypes;

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
  * evid = sceKernelCreateEventFlag("wait_event", 0, 0, NULL);
  * @endcode
  */
SceUID sceKernelCreateEventFlag(const char *name, int attr, int bits, SceKernelEventFlagOptParam *opt);

/**
  * Set an event flag bit pattern.
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  * @param bits - The bit pattern to set.
  *
  * @return < 0 On error
  */
int sceKernelSetEventFlag(SceUID evid, unsigned int bits);

/**
 * Clear a event flag bit pattern
 *
 * @param evid - The event id returned by ::sceKernelCreateEventFlag
 * @param bits - The bits to clean
 *
 * @return < 0 on Error
 */
int sceKernelClearEventFlag(SceUID evid, unsigned int bits);

/**
  * Poll an event flag for a given bit pattern.
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @return < 0 On error
  */
int sceKernelPollEventFlag(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits);

/**
  * Wait for an event flag for a given bit pattern.
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @param timeout  - Timeout in microseconds
  * @return < 0 On error
  */
int sceKernelWaitEventFlag(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits, SceUInt *timeout);

/**
  * Wait for an event flag for a given bit pattern with callback.
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param outBits - The bit pattern that was matched.
  * @param timeout  - Timeout in microseconds
  * @return < 0 On error
  */
int sceKernelWaitEventFlagCB(int evid, unsigned int bits, unsigned int wait, unsigned int *outBits, SceUInt *timeout);

/**
  * Delete an event flag
  *
  * @param evid - The event id returned by ::sceKernelCreateEventFlag.
  *
  * @return < 0 On error
  */
int sceKernelDeleteEventFlag(int evid);

/**
  * Get the status of an event flag.
  *
  * @param event - The UID of the event.
  * @param status - A pointer to a ::SceKernelEventFlagInfo structure.
  *
  * @return < 0 on error.
  */
int sceKernelGetEventFlagInfo(SceUID event, SceKernelEventFlagInfo *info);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_EVENTFLAG_H_ */
