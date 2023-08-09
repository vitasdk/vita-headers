/**
 * \usergroup{SceNet}
 * \usage{psp2/net/net.h,SceNet_stub,SCE_SYSMODULE_NET}
 */


#ifndef _PSP2_NET_NET_H_
#define _PSP2_NET_NET_H_

#include <vitasdk/build_utils.h>
#include <psp2common/net.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Resolver specific error codes */
typedef enum SceNetResolverErrorCode {
	SCE_NET_RESOLVER_EINTERNAL	= 220,
	SCE_NET_RESOLVER_EBUSY,
	SCE_NET_RESOLVER_ENOSPACE,
	SCE_NET_RESOLVER_EPACKET,
	SCE_NET_RESOLVER_ERESERVED224,
	SCE_NET_RESOLVER_ENODNS,
	SCE_NET_RESOLVER_ETIMEDOUT,
	SCE_NET_RESOLVER_ENOSUPPORT,
	SCE_NET_RESOLVER_EFORMAT,
	SCE_NET_RESOLVER_ESERVERFAILURE,
	SCE_NET_RESOLVER_ENOHOST,
	SCE_NET_RESOLVER_ENOTIMPLEMENTED,
	SCE_NET_RESOLVER_ESERVERREFUSED,
	SCE_NET_RESOLVER_ENORECORD,
	SCE_NET_RESOLVER_EALIGNMENT
} SceNetResolverErrorCode;

/** Flags to specify as argument to ::sceNetDumpRead() */
typedef enum SceNetDumpType {
	SCE_NET_DUMP_PEEK                    = 0x00000010,
	SCE_NET_DUMP_DONTWAIT                = 0x00000020,
	SCE_NET_DUMP_OVERFLOW                = 0x00000040,
	SCE_NET_DUMP_ABORT_FLAG_PRESERVATION = 0x00000001
} SceNetDumpType;

/** Events for ::SceNetEpollEvent */
typedef enum SceNetEpollEventType {
	SCE_NET_EPOLLIN       = 0x00000001,
	SCE_NET_EPOLLOUT      = 0x00000002,
	SCE_NET_EPOLLERR      = 0x00000008,
	SCE_NET_EPOLLHUP      = 0x00000010,
	SCE_NET_EPOLLDESCID   = 0x00010000
} SceNetEpollEventType;

/** Flags to specify as argument to ::sceNetEpollControl() */
typedef enum SceNetEpollControlFlag {
	SCE_NET_EPOLL_CTL_ADD = 1,
	SCE_NET_EPOLL_CTL_MOD,
	SCE_NET_EPOLL_CTL_DEL
} SceNetEpollControlFlag;

/** Flags to specify as argument to ::sceNetEmulationGet() / ::sceNetEmulationSet() */
typedef enum SceNetEmulationFlag {
	SCE_NET_EMULATION_FLAG_ETH0	= 1,
	SCE_NET_EMULATION_FLAG_WLAN0
} SceNetEmulationFlag;

/** Flags to specify as argument to ::sceNetResolverStartNtoa() / ::sceNetResolverStartAton() */
typedef enum SceNetResolverFlag {
	SCE_NET_RESOLVER_ASYNC                          = 0x00000001,
	SCE_NET_RESOLVER_START_NTOA_DISABLE_IPADDRESS   = 0x00010000
} SceNetResolverFlag;

/** Flags to specify as argument to ::sceNetResolverAbort() */
typedef enum SceNetResolverAbortFlag {
	SCE_NET_RESOLVER_ABORT_FLAG_NTOA_PRESERVATION = 0x00000001,
	SCE_NET_RESOLVER_ABORT_FLAG_ATON_PRESERVATION = 0x00000002
} SceNetResolverAbortFlag;

/** Flags to specify as argument to ::sceNetSocketAbort() */
typedef enum SceNetSocketAbortFlag {
	SCE_NET_SOCKET_ABORT_FLAG_RCV_PRESERVATION	= 0x00000001,
	SCE_NET_SOCKET_ABORT_FLAG_SND_PRESERVATION	= 0x00000002
} SceNetSocketAbortFlag;

/** Flags to specify as argument to ::sceNetShutdown */
typedef enum SceNetShutdownFlag {
	SCE_NET_SHUT_RD,
	SCE_NET_SHUT_WR,
	SCE_NET_SHUT_RDWR
} SceNetShutdownFlag;

/* Defines */
#define SCE_NET_EPOLL_ABORT_FLAG_PRESERVATION   0x00000001

#define SCE_NET_RESOLVER_PORT             53
#define SCE_NET_RESOLVER_HOSTNAME_LEN_MAX 255

/* callback */

typedef void *(*SceNetResolverFunctionAllocate)(
	unsigned int size,
	int rid,
	const char *name,
	void *user);
typedef void (*SceNetResolverFunctionFree)(
	void *ptr,
	int rid,
	const char *name,
	void *user);

/* struct */

typedef struct SceNetInitParam {
	void *memory;
	int size;
	int flags;
} SceNetInitParam;
VITASDK_BUILD_ASSERT_EQ(0xC, SceNetInitParam);

typedef struct SceNetEmulationData {
	unsigned short int drop_rate;
	unsigned short int drop_duration;
	unsigned short int pass_duration;
	unsigned short int delay_time;
	unsigned short int delay_jitter;
	unsigned short int order_rate;
	unsigned short int order_delay_time;
	unsigned short int duplication_rate;
	unsigned int bps_limit;
	unsigned short int lower_size_limit;
	unsigned short int upper_size_limit;
	unsigned int system_policy_pattern;
	unsigned int game_policy_pattern;
	unsigned short int policy_flags[64];
	unsigned char reserved[64];
} SceNetEmulationData;
VITASDK_BUILD_ASSERT_EQ(0xE0, SceNetEmulationData);

typedef struct SceNetEmulationParam {
	unsigned short int version;
	unsigned short int option_number;
	unsigned short int current_version;
	unsigned short int result;
	unsigned int flags;
	unsigned int reserved1;
	SceNetEmulationData send;
	SceNetEmulationData recv;
	unsigned int seed;
	unsigned char reserved[44];
} SceNetEmulationParam;
VITASDK_BUILD_ASSERT_EQ(0x200, SceNetEmulationParam);

typedef struct SceNetEpollDataExt {
	int id;
	unsigned int u32;
} SceNetEpollDataExt;
VITASDK_BUILD_ASSERT_EQ(8, SceNetEpollDataExt);

typedef union SceNetEpollData {
	void *ptr;
	int fd;
	unsigned int u32;
	unsigned long long int u64;
	SceNetEpollDataExt ext;
} SceNetEpollData;
VITASDK_BUILD_ASSERT_EQ(8, SceNetEpollData);

typedef struct SceNetEpollSystemData {
	unsigned int system[4];
} SceNetEpollSystemData;
VITASDK_BUILD_ASSERT_EQ(0x10, SceNetEpollSystemData);

typedef struct SceNetEpollEvent {
	unsigned int events;
	unsigned int reserved;
	SceNetEpollSystemData system;
	SceNetEpollData data;
} SceNetEpollEvent;
VITASDK_BUILD_ASSERT_EQ(0x20, SceNetEpollEvent);

typedef struct SceNetResolverParam {
	SceNetResolverFunctionAllocate allocate;
	SceNetResolverFunctionFree free;
	void *user;
} SceNetResolverParam;
VITASDK_BUILD_ASSERT_EQ(0xC, SceNetResolverParam);

/* prototypes */

int sceNetInit(SceNetInitParam *param);
int sceNetTerm(void);

int sceNetShowIfconfig(void *p, int b);
int sceNetShowRoute(void);
int sceNetShowNetstat(void);

int sceNetEmulationSet(SceNetEmulationParam *param, int flags);
int sceNetEmulationGet(SceNetEmulationParam *param, int flags);

int sceNetResolverCreate(const char *name, SceNetResolverParam *param, int flags);
int sceNetResolverStartNtoa(int rid, const char *hostname, SceNetInAddr *addr, int timeout, int retry, int flags);
int sceNetResolverStartAton(int rid, const SceNetInAddr *addr, char *hostname, int len, int timeout, int retry, int flags);
int sceNetResolverGetError(int rid, int *result);
int sceNetResolverDestroy(int rid);
int sceNetResolverAbort(int rid, int flags);

int sceNetDumpCreate(const char *name, int len, int flags);
int sceNetDumpRead(int id, void *buf, int len, int *pflags);
int sceNetDumpDestroy(int id);
int sceNetDumpAbort(int id, int flags);
int sceNetEpollCreate(const char *name, int flags);
int sceNetEpollControl(int eid, int op, int id,SceNetEpollEvent *event);
int sceNetEpollWait(int eid, SceNetEpollEvent *events, int maxevents, int timeout);
int sceNetEpollWaitCB(int eid, SceNetEpollEvent *events, int maxevents, int timeout);
int sceNetEpollDestroy(int eid);
int sceNetEpollAbort(int eid, int flags);

int sceNetEtherStrton(const char *str, SceNetEtherAddr *n);
int sceNetEtherNtostr(const SceNetEtherAddr *n, char *str, unsigned int len);
int sceNetGetMacAddress(SceNetEtherAddr *addr, int flags);

int sceNetSocket(const char *name, int domain, int type, int protocol);
int sceNetAccept(int s, SceNetSockaddr *addr, unsigned int *addrlen);
int sceNetBind(int s, const SceNetSockaddr *addr, unsigned int addrlen);
int sceNetConnect(int s, const SceNetSockaddr *name, unsigned int namelen);
int sceNetGetpeername(int s, SceNetSockaddr *name, unsigned int *namelen);
int sceNetGetsockname(int s, SceNetSockaddr *name, unsigned int *namelen);
int sceNetGetsockopt(int s, int level, int optname, void *optval, unsigned int *optlen);
int sceNetListen(int s, int backlog);
int sceNetRecv(int s, void *buf, unsigned int len, int flags);
int sceNetRecvfrom(int s, void *buf, unsigned int len, int flags, SceNetSockaddr *from, unsigned int *fromlen);
int sceNetRecvmsg(int s, SceNetMsghdr *msg, int flags);
int sceNetSend(int s, const void *msg, unsigned int len, int flags);
int sceNetSendto(int s, const void *msg, unsigned int len, int flags, const SceNetSockaddr *to, unsigned int tolen);
int sceNetSendmsg(int s, const SceNetMsghdr *msg, int flags);
int sceNetSetsockopt(int s, int level, int optname, const void *optval, unsigned int optlen);
int sceNetShutdown(int s, int how);
int sceNetSocketClose(int s);
int sceNetSocketAbort(int s, int flags);
int sceNetGetSockInfo(int s, SceNetSockInfo *info, int n, int flags);
int sceNetGetSockIdInfo(SceNetFdSet *fds, int sockinfoflags, int flags);
int sceNetGetStatisticsInfo(SceNetStatisticsInfo *info, int flags);

int sceNetSetDnsInfo(SceNetDnsInfo *info, int flags);
int sceNetClearDnsCache(int flags);

const char *sceNetInetNtop(int af,const void *src,char *dst,unsigned int size);
int sceNetInetPton(int af, const char *src, void *dst);

//TODO : create BSD aliases ?

long long unsigned int sceNetHtonll(unsigned long long int host64);
unsigned int sceNetHtonl(unsigned int host32);
unsigned short int sceNetHtons(unsigned short int host16);
unsigned long long int sceNetNtohll(unsigned long long int net64);
unsigned int sceNetNtohl(unsigned int net32);
unsigned short int sceNetNtohs(unsigned short int net16);

/**
 * Get pointer to last network errno.
 *
 * @return pointer to int.
 */
int *sceNetErrnoLoc(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NET_NET_H_ */

