/**
 * \usergroup{SceThreadMgr}
 * \usage{psp2/kernel/threadmgr/msgpipe.h}
 */

#ifndef _PSP2_KERNEL_THREADMGR_MSGPIPE_H_
#define _PSP2_KERNEL_THREADMGR_MSGPIPE_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Create a message pipe
 *
 * @param name - Name of the pipe
 * @param type - The type of memory attribute to use internally (set to 0x40)
 * @param attr - Set to 12
 * @param bufSize - The size of the internal buffer in multiples of 0x1000 (4KB)
 * @param opt  - Message pipe options (set to NULL)
 *
 * @return The UID of the created pipe, < 0 on error
 */
SceUID sceKernelCreateMsgPipe(const char *name, int type, int attr, unsigned int bufSize, void *opt);

/**
 * Delete a message pipe
 *
 * @param uid - The UID of the pipe
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelDeleteMsgPipe(SceUID uid);

/**
 * Send a message to a pipe
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - async vs sync? use 0 for sync
 * @param unk2 - Unknown - use NULL
 * @param timeout - Timeout for send in us. use NULL to wait indefinitely
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelSendMsgPipe(SceUID uid, void *message, unsigned int size, int unk1, void *unk2, unsigned int *timeout);

/**
 * Send a message to a pipe (with callback)
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - async vs sync? use 0 for sync
 * @param unk2 - Unknown - use NULL
 * @param timeout - Timeout for send in us. use NULL to wait indefinitely
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelSendMsgPipeCB(SceUID uid, void *message, unsigned int size, int unk1, void *unk2, unsigned int *timeout);

/**
 * Try to send a message to a pipe
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - use 0
 * @param unk2 - Unknown - use NULL
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelTrySendMsgPipe(SceUID uid, void *message, SceSize size, int unk1, void *unk2);

/**
 * Receive a message from a pipe
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - async vs sync? use 0 for sync
 * @param unk2 - Unknown - use NULL
 * @param timeout - Timeout for receive in us. use NULL to wait indefinitely
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelReceiveMsgPipe(SceUID uid, void *message, SceSize size, int unk1, void *unk2, unsigned int *timeout);

/**
 * Receive a message from a pipe (with callback)
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - async vs sync? use 0 for sync
 * @param unk2 - Unknown - use NULL
 * @param timeout - Timeout for receive in us. use NULL to wait indefinitely
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelReceiveMsgPipeCB(SceUID uid, void *message, SceSize size, int unk1, void *unk2, unsigned int *timeout);

/**
 * Receive a message from a pipe
 *
 * @param uid - The UID of the pipe
 * @param message - Pointer to the message
 * @param size - Size of the message
 * @param unk1 - Unknown - use 0
 * @param unk2 - Unknown - use NULL
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelTryReceiveMsgPipe(SceUID uid, void *message, SceSize size, int unk1, void *unk2);

/**
 * Cancel a message pipe
 *
 * @param uid - UID of the pipe to cancel
 * @param psend - Receive number of sending threads, NULL is valid
 * @param precv - Receive number of receiving threads, NULL is valid
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelCancelMsgPipe(SceUID uid, int *psend, int *precv);

/** Message Pipe status info */
typedef struct SceKernelMppInfo {
	SceSize size;
	SceUID  mppId; // Needs confirmation
	char    name[32];
	SceUInt attr;
	int     bufSize;
	int     freeSize;
	int     numSendWaitThreads;
	int     numReceiveWaitThreads;
} SceKernelMppInfo;
VITASDK_BUILD_ASSERT_EQ(0x3C, SceKernelMppInfo);

/**
 * Get the status of a Message Pipe
 *
 * @param uid - The uid of the Message Pipe
 * @param info - Pointer to a ::SceKernelMppInfo structure
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelGetMsgPipeInfo(SceUID uid, SceKernelMppInfo *info);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_MSGPIPE_H_ */
