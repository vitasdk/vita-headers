/**
 * \kernelgroup{SceThreadMgr}
 * \usage{psp2kern/kernel/threadmgr/msg_pipe.h,SceThreadmgrForDriver_stub}
 */


#ifndef _PSP2_KERNEL_THREADMGR_MSG_PIPE_H_
#define _PSP2_KERNEL_THREADMGR_MSG_PIPE_H_

#include <psp2kern/types.h>

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
SceUID ksceKernelCreateMsgPipe(const char *name, int type, int attr, SceSize bufSize, void *opt);

/**
 * Delete a message pipe
 *
 * @param uid - The UID of the pipe
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelDeleteMsgPipe(SceUID uid);

typedef struct
{
    const void *message;
    SceSize size;
} MsgPipeSendData;

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
int ksceKernelSendMsgPipeVector(SceUID uid, const MsgPipeSendData *v, unsigned int n, int unk1, void *unk2, unsigned int *timeout);

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
int ksceKernelTrySendMsgPipeVector(SceUID uid, const MsgPipeSendData *v, SceSize size, int unk1, void *unk2);

typedef struct
{
    void *message;
    SceSize size;
} MsgPipeRecvData;

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
int ksceKernelReceiveMsgPipeVector(SceUID uid, const MsgPipeRecvData *v, unsigned int n, int unk1, void *unk2, unsigned int *timeout);

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
int ksceKernelTryReceiveMsgPipeVector(SceUID uid, const MsgPipeRecvData *v, SceSize size, int unk1, void *unk2);

/**
 * Cancel a message pipe
 *
 * @param uid - UID of the pipe to cancel
 * @param psend - Receive number of sending threads, NULL is valid
 * @param precv - Receive number of receiving threads, NULL is valid
 *
 * @return 0 on success, < 0 on error
 */
int ksceKernelCancelMsgPipe(SceUID uid, int *psend, int *precv);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_MSG_PIPE_H_ */
