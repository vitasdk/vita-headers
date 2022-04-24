/**
 * \usergroup{ScePspnetAdhoc}
 * \usage{psp2/pspnet_adhoc.h,ScePspnetAdhoc_stub}
 */


#ifndef _PSP2_PSPNET_ADHOC_H_
#define _PSP2_PSPNET_ADHOC_H_

#include <psp2/types.h>
#include <psp2/pspnet_adhocctl.h>
#include <psp2/net/net.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ScePspnetAdhocErrorCode {
	SCE_ERROR_NET_ADHOC_INVALID_SOCKET_ID      = 0x80410701,
	SCE_ERROR_NET_ADHOC_INVALID_ADDR           = 0x80410702,
	SCE_ERROR_NET_ADHOC_INVALID_PORT           = 0x80410703,
	SCE_ERROR_NET_ADHOC_INVALID_BUFLEN         = 0x80410704,
	SCE_ERROR_NET_ADHOC_INVALID_DATALEN        = 0x80410705,
	SCE_ERROR_NET_ADHOC_NOT_ENOUGH_SPACE       = 0x80410706,
	SCE_ERROR_NET_ADHOC_SOCKET_DELETED         = 0x80410707,
	SCE_ERROR_NET_ADHOC_SOCKET_ALERTED         = 0x80410708,
	SCE_ERROR_NET_ADHOC_WOULD_BLOCK            = 0x80410709,
	SCE_ERROR_NET_ADHOC_PORT_IN_USE            = 0x8041070A,
	SCE_ERROR_NET_ADHOC_NOT_CONNECTED          = 0x8041070B,
	SCE_ERROR_NET_ADHOC_DISCONNECTED           = 0x8041070C,
	SCE_ERROR_NET_ADHOC_NOT_OPENED             = 0x8041070D,
	SCE_ERROR_NET_ADHOC_NOT_LISTENED           = 0x8041070E,
	SCE_ERROR_NET_ADHOC_SOCKET_ID_NOT_AVAIL    = 0x8041070F,
	SCE_ERROR_NET_ADHOC_PORT_NOT_AVAIL         = 0x80410710,
	SCE_ERROR_NET_ADHOC_INVALID_ARG            = 0x80410711,
	SCE_ERROR_NET_ADHOC_NOT_INITIALIZED        = 0x80410712,
	SCE_ERROR_NET_ADHOC_ALREADY_INITIALIZED    = 0x80410713,
	SCE_ERROR_NET_ADHOC_BUSY                   = 0x80410714,
	SCE_ERROR_NET_ADHOC_TIMEOUT                = 0x80410715,
	SCE_ERROR_NET_ADHOC_NO_ENTRY               = 0x80410716,
	SCE_ERROR_NET_ADHOC_EXCEPTION_EVENT        = 0x80410717,
	SCE_ERROR_NET_ADHOC_CONNECTION_REFUSED     = 0x80410718,
	SCE_ERROR_NET_ADHOC_THREAD_ABORTED         = 0x80410719,
	SCE_ERROR_NET_ADHOC_ALREADY_CREATED        = 0x8041071A,
	SCE_ERROR_NET_ADHOC_NOT_IN_GAMEMODE        = 0x8041071B,
	SCE_ERROR_NET_ADHOC_NOT_CREATED            = 0x8041071C,
	SCE_ERROR_NET_ADHOC_INVALID_ALIGNMENT      = 0x8041071D
} ScePspnetAdhocErrorCode;

struct SceNetAdhocPollSd {
	int id;
	int events;
	int revents;
};

typedef enum ScePspnetAdhocEvent {
	SCE_NET_ADHOC_EV_SEND        = 0x0001,
	SCE_NET_ADHOC_EV_RECV        = 0x0002,
	SCE_NET_ADHOC_EV_CONNECT     = 0x0004,
	SCE_NET_ADHOC_EV_ACCEPT      = 0x0008,
	SCE_NET_ADHOC_EV_FLUSH       = 0x0010,
	SCE_NET_ADHOC_EV_INVALID     = 0x0100,
	SCE_NET_ADHOC_EV_DELETE      = 0x0200,
	SCE_NET_ADHOC_EV_ALERT       = 0x0400,
	SCE_NET_ADHOC_EV_DISCONNECT  = 0x0800
} ScePspnetAdhocEvent;

struct SceNetAdhocPdpStat {
	struct SceNetAdhocPdpStat *next;
	int id;
	struct SceNetEtherAddr laddr;
	SceUShort16 lport;
	unsigned int rcv_sb_cc;
};

typedef enum ScePspnetAdhocPtpState {
	SCE_NET_ADHOC_PTP_STATE_CLOSED       = 0,
	SCE_NET_ADHOC_PTP_STATE_LISTEN       = 1,
	SCE_NET_ADHOC_PTP_STATE_SYN_SENT     = 2,
	SCE_NET_ADHOC_PTP_STATE_SYN_RCVD     = 3,
	SCE_NET_ADHOC_PTP_STATE_ESTABLISHED  = 4
} ScePspnetAdhocPtpState;

struct SceNetAdhocPtpStat {
	struct SceNetAdhocPtpStat *next;
	int id;
	struct SceNetEtherAddr laddr;
	struct SceNetEtherAddr paddr;
	SceUShort16 lport;
	SceUShort16 pport;
	unsigned int snd_sb_cc;
	unsigned int rcv_sb_cc;
	int state;
};

typedef enum ScePspnetAdhocFlags {
	SCE_NET_ADHOC_F_NONBLOCK      = 0x0001,
	SCE_NET_ADHOC_F_ALERTSEND     = 0x0010,
	SCE_NET_ADHOC_F_ALERTRECV     = 0x0020,
	SCE_NET_ADHOC_F_ALERTPOLL     = 0x0040,
	SCE_NET_ADHOC_F_ALERTCONNECT  = 0x0080,
	SCE_NET_ADHOC_F_ALERTACCEPT   = 0x0100,
	SCE_NET_ADHOC_F_ALERTFLUSH    = 0x0200
} ScePspnetAdhocFlags;

#define SCE_NET_ADHOC_F_ALERTALL \
       (SCE_NET_ADHOC_F_ALERTSEND \
       |SCE_NET_ADHOC_F_ALERTRECV \
       |SCE_NET_ADHOC_F_ALERTPOLL \
       |SCE_NET_ADHOC_F_ALERTCONNECT \
       |SCE_NET_ADHOC_F_ALERTACCEPT \
       |SCE_NET_ADHOC_F_ALERTFLUSH \
       )

#define SCE_NET_ADHOC_PDP_MFS  1444
#define SCE_NET_ADHOC_PDP_MTU  65523
#define SCE_NET_ADHOC_PTP_MSS  1444

int sceNetAdhocInit(void);
int sceNetAdhocTerm(void);

int sceNetAdhocPollSocket(struct SceNetAdhocPollSd *sds, int nsds, unsigned int timeout, int flag);
int sceNetAdhocSetSocketAlert(int id, int flag);
int sceNetAdhocGetSocketAlert(int id, int *flag);

int sceNetAdhocPdpCreate(const struct SceNetEtherAddr *saddr, SceUShort16 sport, unsigned int bufsize, int flag);
int sceNetAdhocPdpSend(int id, const struct SceNetEtherAddr *daddr, SceUShort16 dport, const void *data, int len, unsigned int timeout, int flag);
int sceNetAdhocPdpRecv(int id, struct SceNetEtherAddr *saddr, SceUShort16 *sport, void *buf, int *len, unsigned   int timeout, int flag);
int sceNetAdhocPdpDelete(int id, int flag);
int sceNetAdhocGetPdpStat(int *buflen, void *buf);

int sceNetAdhocPtpOpen(const struct SceNetEtherAddr *saddr, SceUShort16 sport, const struct SceNetEtherAddr *daddr, SceUShort16 dport, unsigned int bufsize, unsigned int rexmt_int, int rexmt_cnt, int flag);
int sceNetAdhocPtpConnect(int id, unsigned int timeout, int flag);
int sceNetAdhocPtpListen(const struct SceNetEtherAddr *saddr, SceUShort16 sport, unsigned int bufsize, unsigned int rexmt_int, int rexmt_cnt, int backlog, int flag);
int sceNetAdhocPtpAccept(int id, struct SceNetEtherAddr *addr, SceUShort16 *port, unsigned int timeout, int flag);
int sceNetAdhocPtpSend(int id, const void *data, int *len, unsigned int timeout, int flag);
int sceNetAdhocPtpRecv(int id, void *buf, int *len, unsigned int timeout, int flag);
int sceNetAdhocPtpFlush(int id, unsigned int timeout, int flag);
int sceNetAdhocPtpClose(int id, int flag) ;
int sceNetAdhocGetPtpStat(int *buflen, void *buf);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PSPNET_ADHOC_H_ */

