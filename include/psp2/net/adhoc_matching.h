/**
 * \usergroup{SceNetAdhocMatching}
 * \usage{psp2/net/adhoc_matching.h,SceNetAdhocMatching_stub}
 */

#ifndef _PSP2_NET_ADHOC_MATCHING_H_
#define _PSP2_NET_ADHOC_MATCHING_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2/net/net.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceNetAdhocMatchingErrorCode {
    SCE_NET_ADHOC_MATCHING_ERROR_INVALID_MODE        = 0x80413101,
    SCE_NET_ADHOC_MATCHING_ERROR_INVALID_PORT        = 0x80413102,
    SCE_NET_ADHOC_MATCHING_ERROR_INVALID_MAXNUM      = 0x80413103,
    SCE_NET_ADHOC_MATCHING_ERROR_RXBUF_TOO_SHORT     = 0x80413104,
    SCE_NET_ADHOC_MATCHING_ERROR_INVALID_OPTLEN      = 0x80413105,
    SCE_NET_ADHOC_MATCHING_ERROR_INVALID_ARG         = 0x80413106,
    SCE_NET_ADHOC_MATCHING_ERROR_INVALID_ID          = 0x80413107,
    SCE_NET_ADHOC_MATCHING_ERROR_ID_NOT_AVAIL        = 0x80413108,
    SCE_NET_ADHOC_MATCHING_ERROR_NO_SPACE            = 0x80413109,
    SCE_NET_ADHOC_MATCHING_ERROR_IS_RUNNING          = 0x8041310a,
    SCE_NET_ADHOC_MATCHING_ERROR_NOT_RUNNING         = 0x8041310b,
    SCE_NET_ADHOC_MATCHING_ERROR_UNKNOWN_TARGET      = 0x8041310c,
    SCE_NET_ADHOC_MATCHING_ERROR_TARGET_NOT_READY    = 0x8041310d,
    SCE_NET_ADHOC_MATCHING_ERROR_EXCEED_MAXNUM       = 0x8041310e,
    SCE_NET_ADHOC_MATCHING_ERROR_REQUEST_IN_PROGRESS = 0x8041310f,
    SCE_NET_ADHOC_MATCHING_ERROR_ALREADY_ESTABLISHED = 0x80413110,
    SCE_NET_ADHOC_MATCHING_ERROR_BUSY                = 0x80413111,
    SCE_NET_ADHOC_MATCHING_ERROR_ALREADY_INITIALIZED = 0x80413112,
    SCE_NET_ADHOC_MATCHING_ERROR_NOT_INITIALIZED     = 0x80413113,
    SCE_NET_ADHOC_MATCHING_ERROR_PORT_IN_USE         = 0x80413114,
    SCE_NET_ADHOC_MATCHING_ERROR_STACKSIZE_TOO_SHORT = 0x80413115,
    SCE_NET_ADHOC_MATCHING_ERROR_INVALID_DATALEN     = 0x80413116,
    SCE_NET_ADHOC_MATCHING_ERROR_NOT_ESTABLISHED     = 0x80413117,
    SCE_NET_ADHOC_MATCHING_ERROR_DATA_BUSY           = 0x80413118,
    SCE_NET_ADHOC_MATCHING_ERROR_INVALID_ALIGNMENT   = 0x80413119
} SceNetAdhocMatchingErrorCode;

typedef enum SceNetAdhocMatchingMode{
    SCE_NET_ADHOC_MATCHING_MODE_PARENT = 1,
    SCE_NET_ADHOC_MATCHING_MODE_CHILD,
    SCE_NET_ADHOC_MATCHING_MODE_P2P,
} SceNetAdhocMatchingMode;

typedef void (*SceNetAdhocMatchingCallback)(
    int id,
    int type,
    SceNetInAddr* addr,
    SceSize optLen,
    void* opt);
    
struct SceNetAdhocMatchingMember {
    SceNetInAddr addr;
};

int sceNetAdhocMatchingInit(unsigned int poolsize, void *poolptr);
int sceNetAdhocMatchingTerm(void);

int sceNetAdhocMatchingStart(int id, int threadPriority, int threadStackSize, int threadCpuAffinityMask, int helloOptLen, void *helloOpt);
int sceNetAdhocMatchingCreate(SceNetAdhocMatchingMode mode, int maxNum, SceUShort16 port, int rxBufLen, unsigned int helloInterval, unsigned int keepAliveInterval, int initCount, unsigned int rexmtInterval, SceNetAdhocMatchingCallback handlerCallback);
int sceNetAdhocMatchingStop(int id);
int sceNetAdhocMatchingDelete(int id);

int sceNetAdhocMatchingAbortSendData(int id, SceNetInAddr *addr);
int sceNetAdhocMatchingCancelTargetWithOpt(int id, SceNetInAddr *target, int optLen, char *opt);
int sceNetAdhocMatchingCancelTarget(int id, SceNetInAddr *target);

int sceNetAdhocMatchingSetHelloOpt(int id, int optLen, void *opt);
int sceNetAdhocMatchingGetHelloOpt(int id, unsigned int *optLen, void *opt);

int sceNetAdhocMatchingGetMembers(int id, unsigned int *membersCount, struct SceNetAdhocMatchingMember *members);
int sceNetAdhocMatchingSelectTarget(int id, SceNetInAddr *target, int optLen, void *opt);
int sceNetAdhocMatchingSendData(int id, SceNetInAddr *addr, int dataLen, void *data);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NET_ADHOC_MATCHING_H_ */
