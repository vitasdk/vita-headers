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
	SceSize opt_len,
	void* opt);

struct SceNetAdhocMatchingMember {
	SceNetInAddr addr;
};

int sceNetAdhocMatchingInit(unsigned int pool_size, void *pool_ptr);
int sceNetAdhocMatchingTerm(void);

int sceNetAdhocMatchingStart(int id, int thread_priority, int thread_stack_size, int thread_cpu_affinity_mask, int hello_opt_len, void *hello_opt);
int sceNetAdhocMatchingCreate(SceNetAdhocMatchingMode mode, int max_members, SceUShort16 port, int rx_buffer_len, unsigned int hello_interval, unsigned int keep_alive_interval, int retry_count, unsigned int rexmt_interval, SceNetAdhocMatchingCallback handler_callback);
int sceNetAdhocMatchingStop(int id);
int sceNetAdhocMatchingDelete(int id);

int sceNetAdhocMatchingAbortSendData(int id, SceNetInAddr *addr);
int sceNetAdhocMatchingCancelTargetWithOpt(int id, SceNetInAddr *target, int opt_len, char *opt);
int sceNetAdhocMatchingCancelTarget(int id, SceNetInAddr *target);

int sceNetAdhocMatchingSetHelloOpt(int id, int opt_len, void *opt);
int sceNetAdhocMatchingGetHelloOpt(int id, unsigned int *opt_len, void *opt);

int sceNetAdhocMatchingGetMembers(int id, unsigned int *members_count, struct SceNetAdhocMatchingMember *members);
int sceNetAdhocMatchingSelectTarget(int id, SceNetInAddr *target, int opt_len, void *opt);
int sceNetAdhocMatchingSendData(int id, SceNetInAddr *addr, int data_len, void *data);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NET_ADHOC_MATCHING_H_ */
