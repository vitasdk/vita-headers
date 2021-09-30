/**
 * \usergroup{ScePss}
 * \usage{psp2/pss.h,SceLibMonoBridge_stub}
 */


#ifndef _PSP2_PSS_H_
#define _PSP2_PSS_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PSS_OK 0
#define PSS_ERROR_THREAD_SUSPENDED -2147319763

/* IO Defines */
#define PSS_ERROR_ERRNO_EEXIST -2147418095
#define PSS_ERROR_ERRNO_ENOENT -2147418110
#define PSS_ERROR_ERRNO_EACCES -2147418099

#define PSS_STM_RWU (00600)
#define PSS_STM_FDIR (0x1 << 12)
#define PSS_STM_FREG (0x2 << 12)

#define PSS_FREAD (0x0001)
#define PSS_FWRITE (0x0002)
#define PSS_FCREAT (0x0200)
#define PSS_TRUNC (0x0400)

#define PSS_CST_SIZE 0x0004
#define PSS_CST_CT 0x0008
#define PSS_CST_AT 0x0010
#define PSS_CST_MT 0x0020

/* Net defines */
#define PSS_NET_IPPROTO_IP            0
#define PSS_NET_IPPROTO_ICMP          1
#define PSS_NET_IPPROTO_IGMP          2
#define PSS_NET_IPPROTO_TCP           6
#define PSS_NET_IPPROTO_UDP           17
#define PSS_NET_SOL_SOCKET            0xffff

#define PSS_NET_IP_HDRINCL            2
#define PSS_NET_IP_TOS                3
#define PSS_NET_IP_TTL                4
#define PSS_NET_IP_MULTICAST_IF       9
#define PSS_NET_IP_MULTICAST_TTL      10
#define PSS_NET_IP_MULTICAST_LOOP     11
#define PSS_NET_IP_ADD_MEMBERSHIP     12
#define PSS_NET_IP_DROP_MEMBERSHIP    13
#define PSS_NET_IP_TTLCHK             23
#define PSS_NET_IP_MAXTTL             24

#define PSS_NET_TCP_NODELAY           1
#define PSS_NET_TCP_MAXSEG            2
#define PSS_NET_TCP_MSS_TO_ADVERTISE  3

#define PSS_NET_SO_REUSEADDR          0x00000004
#define PSS_NET_SO_KEEPALIVE          0x00000008
#define PSS_NET_SO_BROADCAST          0x00000020
#define PSS_NET_SO_LINGER             0x00000080
#define PSS_NET_SO_OOBINLINE          0x00000100
#define PSS_NET_SO_REUSEPORT          0x00000200
#define PSS_NET_SO_ONESBCAST          0x00000800
#define PSS_NET_SO_USECRYPTO          0x00001000
#define PSS_NET_SO_USESIGNATURE       0x00002000
#define PSS_NET_SO_SNDBUF             0x1001
#define PSS_NET_SO_RCVBUF             0x1002
#define PSS_NET_SO_SNDLOWAT           0x1003
#define PSS_NET_SO_RCVLOWAT           0x1004
#define PSS_NET_SO_SNDTIMEO           0x1005
#define PSS_NET_SO_RCVTIMEO           0x1006
#define PSS_NET_SO_ERROR              0x1007
#define PSS_NET_SO_TYPE               0x1008
#define PSS_NET_SO_NBIO               0x1100
#define PSS_NET_SO_TPPOLICY           0x1101
#define PSS_NET_SO_NAME               0x1102
#define PSS_NET_SO_ERROR_EX           0x1104

#define PSS_NET_SOCK_STREAM           1
#define PSS_NET_SOCK_DGRAM            2
#define PSS_NET_SOCK_RAW              3
#define PSS_NET_SOCK_DGRAM_P2P        6
#define PSS_NET_SOCK_STREAM_P2P       10

#define PSS_NET_ADHOC_PORT            3658

#define PSS_NET_AF_INET               2

#define PSS_NET_EPERM           1
#define PSS_NET_ENOENT          2
#define PSS_NET_ESRCH           3
#define PSS_NET_EINTR           4
#define PSS_NET_EIO             5
#define PSS_NET_ENXIO           6
#define PSS_NET_E2BIG           7
#define PSS_NET_ENOEXEC         8
#define PSS_NET_EBADF           9
#define PSS_NET_ECHILD          10
#define PSS_NET_EDEADLK         11
#define PSS_NET_ENOMEM          12
#define PSS_NET_EACCES          13
#define PSS_NET_EFAULT          14
#define PSS_NET_ENOTBLK         15
#define PSS_NET_EBUSY           16
#define PSS_NET_EEXIST          17
#define PSS_NET_EXDEV           18
#define PSS_NET_ENODEV          19
#define PSS_NET_ENOTDIR         20
#define PSS_NET_EISDIR          21
#define PSS_NET_EINVAL          22
#define PSS_NET_ENFILE          23
#define PSS_NET_EMFILE          24
#define PSS_NET_ENOTTY          25
#define PSS_NET_ETXTBSY         26
#define PSS_NET_EFBIG           27
#define PSS_NET_ENOSPC          28
#define PSS_NET_ESPIPE          29
#define PSS_NET_EROFS           30
#define PSS_NET_EMLINK          31
#define PSS_NET_EPIPE           32
#define PSS_NET_EDOM            33
#define PSS_NET_ERANGE          34
#define PSS_NET_EAGAIN          35
#define PSS_NET_EWOULDBLOCK     PSS_NET_EAGAIN
#define PSS_NET_EINPROGRESS     36
#define PSS_NET_EALREADY        37
#define PSS_NET_ENOTSOCK        38
#define PSS_NET_EDESTADDRREQ    39
#define PSS_NET_EMSGSIZE        40
#define PSS_NET_EPROTOTYPE      41
#define PSS_NET_ENOPROTOOPT     42
#define PSS_NET_EPROTONOSUPPORT 43
#define PSS_NET_ESOCKTNOSUPPORT 44
#define PSS_NET_EOPNOTSUPP      45
#define PSS_NET_EPFNOSUPPORT    46
#define PSS_NET_EAFNOSUPPORT    47
#define PSS_NET_EADDRINUSE      48
#define PSS_NET_EADDRNOTAVAIL   49
#define PSS_NET_ENETDOWN        50
#define PSS_NET_ENETUNREACH     51
#define PSS_NET_ENETRESET       52
#define PSS_NET_ECONNABORTED    53
#define PSS_NET_ECONNRESET      54
#define PSS_NET_ENOBUFS         55
#define PSS_NET_EISCONN         56
#define PSS_NET_ENOTCONN        57
#define PSS_NET_ESHUTDOWN       58
#define PSS_NET_ETOOMANYREFS    59
#define PSS_NET_ETIMEDOUT       60
#define PSS_NET_ECONNREFUSED    61
#define PSS_NET_ELOOP           62
#define PSS_NET_ENAMETOOLONG    63
#define PSS_NET_EHOSTDOWN       64
#define PSS_NET_EHOSTUNREACH    65
#define PSS_NET_ENOTEMPTY       66
#define PSS_NET_EPROCLIM        67
#define PSS_NET_EUSERS          68
#define PSS_NET_EDQUOT          69
#define PSS_NET_ESTALE          70
#define PSS_NET_EREMOTE         71
#define PSS_NET_EBADRPC         72
#define PSS_NET_ERPCMISMATCH    73
#define PSS_NET_EPROGUNAVAIL    74
#define PSS_NET_EPROGMISMATCH   75
#define PSS_NET_EPROCUNAVAIL    76
#define PSS_NET_ENOLCK          77
#define PSS_NET_ENOSYS          78
#define PSS_NET_EFTYPE          79
#define PSS_NET_EAUTH           80
#define PSS_NET_ENEEDAUTH       81
#define PSS_NET_EIDRM           82
#define PSS_NET_ENOMSG          83
#define PSS_NET_EOVERFLOW       84
#define PSS_NET_EILSEQ          85
#define PSS_NET_ENOTSUP         86
#define PSS_NET_ECANCELED       87
#define PSS_NET_EBADMSG         88
#define PSS_NET_ENODATA         89
#define PSS_NET_ENOSR           90
#define PSS_NET_ENOSTR          91
#define PSS_NET_ETIME           92
#define PSS_NET_EADHOC          160
#define PSS_NET_EDISABLEDIF     161
#define PSS_NET_ERESUME         162
#define PSS_NET_EIPADDRCHANGED  163
#define PSS_NET_EINACTIVEDISABLED  PSS_NET_EIPADDRCHANGED

#define PSS_NET_ENOTINIT                           200
#define PSS_NET_ENOLIBMEM                          201
#define PSS_NET_ETLS                               202
#define PSS_NET_ECALLBACK                          203
#define PSS_NET_EINTERNAL                          204
#define PSS_NET_ERETURN                            205

#define PSS_NET_RESOLVER_EINTERNAL                 220
#define PSS_NET_RESOLVER_EBUSY                     221
#define PSS_NET_RESOLVER_ENOSPACE                  222
#define PSS_NET_RESOLVER_EPACKET                   223
#define PSS_NET_RESOLVER_ERESERVED224              224
#define PSS_NET_RESOLVER_ENODNS                    225
#define PSS_NET_RESOLVER_ETIMEDOUT                 226
#define PSS_NET_RESOLVER_ENOSUPPORT                227
#define PSS_NET_RESOLVER_EFORMAT                   228
#define PSS_NET_RESOLVER_ESERVERFAILURE            229
#define PSS_NET_RESOLVER_ENOHOST                   230
#define PSS_NET_RESOLVER_ENOTIMPLEMENTED           231
#define PSS_NET_RESOLVER_ESERVERREFUSED            232
#define PSS_NET_RESOLVER_ENORECORD                 233

#define PSS_NET_SHUT_RD             0
#define PSS_NET_SHUT_WR             1
#define PSS_NET_SHUT_RDWR           2

#define PSS_NET_CTL_INFO_CNF_NAME          1
#define PSS_NET_CTL_INFO_DEVICE            2
#define PSS_NET_CTL_INFO_ETHER_ADDR        3
#define PSS_NET_CTL_INFO_MTU               4
#define PSS_NET_CTL_INFO_LINK              5
#define PSS_NET_CTL_INFO_BSSID             6
#define PSS_NET_CTL_INFO_SSID              7
#define PSS_NET_CTL_INFO_WIFI_SECURITY     8
#define PSS_NET_CTL_INFO_RSSI_DBM          9
#define PSS_NET_CTL_INFO_RSSI_PERCENTAGE   10
#define PSS_NET_CTL_INFO_CHANNEL           11
#define PSS_NET_CTL_INFO_IP_CONFIG         12
#define PSS_NET_CTL_INFO_DHCP_HOSTNAME     13
#define PSS_NET_CTL_INFO_PPPOE_AUTH_NAME   14
#define PSS_NET_CTL_INFO_IP_ADDRESS        15
#define PSS_NET_CTL_INFO_NETMASK           16
#define PSS_NET_CTL_INFO_DEFAULT_ROUTE     17
#define PSS_NET_CTL_INFO_PRIMARY_DNS       18
#define PSS_NET_CTL_INFO_SECONDARY_DNS     19
#define PSS_NET_CTL_INFO_HTTP_PROXY_CONFIG 20
#define PSS_NET_CTL_INFO_HTTP_PROXY_SERVER 21
#define PSS_NET_CTL_INFO_HTTP_PROXY_PORT   22
#define PSS_NET_CTL_INFO_RESERVED1         23
#define PSS_NET_CTL_INFO_RESERVED2         24

#define PSS_NET_EPOLLIN         0x00000001
#define PSS_NET_EPOLLOUT        0x00000002
#define PSS_NET_EPOLLERR        0x00000008
#define PSS_NET_EPOLLHUP        0x00000010
#define PSS_NET_EPOLLDESCID     0x00010000

#define PSS_NET_EPOLL_CTL_ADD   1
#define PSS_NET_EPOLL_CTL_MOD   2
#define PSS_NET_EPOLL_CTL_DEL   3

typedef struct PssIRegisters {
	unsigned int size;
	uint32_t cpsr;
	uint32_t reg[16];
	uint32_t tpidrurw;
	uint32_t teehbr;
	uint32_t stackBottom;
	uint32_t stackTop;
} PSSIntegerRegisters;

typedef struct PssFRegisters {
	unsigned int size;
	uint32_t fpscr;
	struct {
		uint32_t word[4];
	} reg[16];
} PSSFloatRegisters;

typedef struct pss_ucontext {
	PSSIntegerRegisters iregs;
	PSSFloatRegisters fregs;
} pss_ucontext;

typedef struct _PssCryptoContext {
	int handle;
	int valid;
	int size;
	int type;
} PssCryptoContext;

typedef struct _PssTimeval {
	long tv_sec;
	long tv_usec;
} PssTimeval;

typedef struct _PssTimespec {
	int tv_sec;
	int tv_nsec;
} PssTimespec;

typedef struct _PssTimezone {
	int tz_minuteswest;
	int tz_dsttime;
} PssTimezone;

typedef struct _PssDateTime {
    unsigned short year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned int   microsecond;
} PssDateTime;


typedef struct _PssIoStat {
	int st_mode;
	unsigned int st_attr;
	int64_t st_size;
	PssDateTime st_ctime;
	PssDateTime st_atime;
	PssDateTime st_mtime;
	unsigned int st_private[6];
} PssIoStat;

typedef struct _PssNetHostent {
    char  *h_name;
    char **h_aliases;
    int    h_addrtype;
    int    h_length;
    char **h_addr_list;
} PssNetHostent;

typedef struct _PssNetLinger {
    int l_onoff;
    int l_linger;
} PssNetLinger;

typedef struct _PssNetSockaddr {
    unsigned char sa_len;
    unsigned char sa_family;
    signed char sa_data[14];
} PssNetSockaddr;

typedef struct _PssNetIovec {
    void *iov_base;
    int iov_len;
} PssNetIovec;

typedef struct _PssNetMsghdr {
    void *msg_name;
    uint32_t msg_namelen;
    PssNetIovec *msg_iov;
    int msg_iovlen;
    void *msg_control;
    uint32_t msg_controllen;
    int msg_flags;
} PssNetMsghdr;

typedef struct _PssNetInAddr {
    uint32_t s_addr;
} PssNetInAddr;

typedef struct _PssNetIpMreq {
    PssNetInAddr imr_multiaddr;
    PssNetInAddr imr_interface;
} PssNetIpMreq;


typedef struct _PssNetSockaddrIn {
    unsigned char sin_len;
    unsigned char sin_family;
    unsigned short sin_port;
    PssNetInAddr sin_addr;
    unsigned short sin_vport;
    unsigned char sin_zero[6];
} PssNetSockaddrIn;

typedef struct PssNetEpollDataExt {
        int id;
        uint32_t u32;
} PssNetEpollDataExt;

typedef union PssNetEpollData {
        void *ptr;
        int fd;
        uint32_t u32;
        uint64_t u64;
        PssNetEpollDataExt ext;
} PssNetEpollData;

typedef struct PssNetEpollSystemData {
        uint32_t system[4];
} PssNetEpollSystemData;

typedef struct PssNetEpollEvent {
        uint32_t events;
        uint32_t reserved;
        PssNetEpollSystemData system;
        PssNetEpollData data;
} PssNetEpollEvent;


/* Misc */
int pss_getpid ();
int pss_nanosleep (const PssTimespec *req, PssTimespec *rem);

/* Threading */
typedef void (*pss_exception_callback)(pthread_t tid, pss_ucontext *ctx);
int32_t pss_suspend_thread (int tid, uint32_t *timeout);
int32_t pss_resume_thread (int tid);
int32_t pss_set_thread_context (int tid, PSSIntegerRegisters *iregs, PSSFloatRegisters *fregs);
int32_t pss_get_thread_context (int tid, PSSIntegerRegisters *iregs, PSSFloatRegisters *fregs);
void pss_disable_ftz ();
int pss_supports_fast_tls ();
void pss_threads_initialize (pss_exception_callback cb);
void *pss_get_stack_bottom ();

/* Time */
uint32_t pss_get_ticks_32 (void);
int64_t pss_get_ticks_64 (void);
int64_t pss_get_ticks_since_111 (void);
int pss_gettimeofday (PssTimeval *tv, PssTimezone *tz);
int32_t pss_delay_thread (uint32_t usec);
int pss_get_win32_filetime (const PssDateTime *time, uint64_t *win32time);
int pss_set_win32_filetime (PssDateTime *time, uint64_t win32time);

/* PRng */
void *pss_get_prng_provider ();
void pss_free_prng_provider (void *provider);
void pss_prng_fill (void *provider, unsigned char *buffer, size_t bytes);

/* Memory */
int pss_getpagesize ();

void pss_code_mem_initialize ();
void pss_code_mem_flush_icache (uint8_t *code, int size);
void *pss_code_mem_alloc (unsigned int *length);
void pss_code_mem_lock ();
void pss_code_mem_unlock ();
int pss_code_mem_free (void *code);
void pss_code_mem_terminate ();

void *pss_alloc_mem (size_t length, size_t alignment);
int pss_free_mem (void *addr, size_t length);

int pss_alloc_raw (void **base, size_t length);
void pss_free_raw (int id);

/* USB Transport */
void pss_usb_transport_connect (const char *address);
void pss_usb_transport_close1 (void);
void pss_usb_transport_close2 (void);
int pss_usb_transport_send (void *data, int len);
int pss_usb_transport_recv (void *data, int len);

/* Crypto */
int pss_crypto_open (PssCryptoContext *context, const char *path);
char *pss_crypto_read (PssCryptoContext *context);
int pss_crypto_fread (PssCryptoContext *context, char *buffer, int bytes);
void pss_crypto_close (PssCryptoContext *context);

/* Semaphores */
int pss_create_semaphore (int32_t initial);
void pss_delete_semaphore (int32_t semaphore);
int pss_signal_semaphore (int32_t semaphore, int32_t count);
int pss_wait_semaphore (int32_t semaphore, int32_t count, uint32_t *timeout);

/* IO */
int pss_io_mkdir (const char *dirname, int mode);
int pss_io_rmdir (const char *dirname);
int pss_io_getstat (const char *filename, PssIoStat *stat);
int pss_io_rename (const char *src, const char *dst);
int pss_io_open (const char *filename, int flag, int mode);
int pss_io_close (int fd);
int pss_io_remove (const char *filename);
int pss_io_dopen (const char *dirname);
int pss_io_dclose (int fd);
int pss_io_read (int fd, void *buf, unsigned int nbyte);
int pss_io_write (int fd, void *buf, unsigned int nbyte);
int pss_io_lseek (int fd, int offset, int whence);
int pss_io_chstat (const char *name, const PssIoStat *buf, unsigned int cbit);

/* Network */

void pss_net_init ();
int pss_net_shutdown (int s, int how);
int *pss_get_errnoloc ();
#define pss_net_errno (*pss_get_errnoloc ())
int pss_net_socket_close (int sock);
int pss_net_accept (int s, PssNetSockaddr *addr, uint32_t *len);
int pss_net_bind (int s, PssNetSockaddr *addr, uint32_t len);
int pss_net_connect (int s, const PssNetSockaddr *addr, uint32_t len);
int pss_net_getpeername (int s, PssNetSockaddr *addr, uint32_t *len);
int pss_net_getsockname (int s, PssNetSockaddr *addr, uint32_t *len);
int pss_net_getsockopt (int s, int level, int optname, void *optval, uint32_t *len);
int pss_net_setsockopt (int s, int level, int optname, const void *optval, uint32_t len);
int pss_net_gethostname (char *name, size_t len);
int pss_net_resolver_start_aton (int rid, const PssNetInAddr *addr, char *hostname, int len, int timeout, int retry, int flags);
int pss_net_resolver_start_ntoa (int rid, const char *hostname, PssNetInAddr *addr, int timeout, int retry, int flags);
int pss_net_resolver_create (const char *name, void *param, int flags);
int pss_net_listen (int sock, int backlog);
int pss_net_recv (int s, void *buf, uint32_t len, int flags);
int pss_net_recvfrom (int s, void *buf, uint32_t len, int flags, PssNetSockaddr *addr, uint32_t *fromlen);
int pss_net_send (int s, const void *msg, uint32_t len, int flags);
int pss_net_sendto (int s, const void *msg, uint32_t len, int flags, const PssNetSockaddr *to, uint32_t tolen);
int pss_net_socket (const char *name, int domain, int type, int protocol);
int pss_net_socket_available (int s, int* amount);
unsigned short pss_net_ntohs (unsigned short net16);
uint32_t pss_net_ntohl (uint32_t net32);
unsigned short pss_net_htons (unsigned short net16);
uint32_t pss_net_htonl (uint32_t net32);
PssNetInAddr* pss_net_get_local_ips (int family, int* nips);

int pss_net_epoll_create (const char *name, int flags);
int pss_net_epoll_ctl (int eid, int op, int id, PssNetEpollEvent *event);
int pss_net_epoll_wait (int eid, PssNetEpollEvent *events, int maxevents, int timeout);
int pss_net_epoll_destroy (int eid);
int pss_net_epoll_abort (int eid, int flags);

void *pss_load_system_certs (void **out_pemList);
void pss_free_system_certs (void *ctx);

#define PSS_NET_ID_SOCKET_MIN      0
#define PSS_NET_ID_SOCKET_MAX      1023

#define PSS_NET_NBITS        (sizeof(uint32_t) * 8)
#define PSS_NET_NBITS_SHIFT  5
#define PSS_NET_NBITS_MASK	 (PSS_NET_NBITS - 1)
#define PSS_NET_FD_SETSIZE   (PSS_NET_ID_SOCKET_MAX - PSS_NET_ID_SOCKET_MIN + 1)

#define PSS_NET_ID_SET(n, p, min_id, max_id) \
	if ((n) >= (min_id) && (n) <= (max_id)) { \
		((p)->bits[(uint32_t)((n) - (min_id)) >> PSS_NET_NBITS_SHIFT] \
		    |= (uint32_t)(1 << ((uint32_t)((n) - (min_id)) & \
		    PSS_NET_NBITS_MASK))); \
	}
#define PSS_NET_ID_CLR(n, p, min_id, max_id) \
	if ((n) >= (min_id) && (n) <= (max_id)) { \
		((p)->bits[(uint32_t)((n) - (min_id)) >> PSS_NET_NBITS_SHIFT] \
		    &= (uint32_t)~(1 << ((uint32_t)((n) - (min_id)) & \
		    PSS_NET_NBITS_MASK))); \
	}
#define PSS_NET_ID_ISSET(n, p, min_id, max_id) \
	((p)->bits[(uint32_t)((n) - (min_id)) >> PSS_NET_NBITS_SHIFT] \
	    & (uint32_t)(1 << ((uint32_t)((n) - (min_id)) & PSS_NET_NBITS_MASK)))

#define PSS_NET_ID_ZERO(p, id_size) do { \
	uint32_t *__bits = (p)->bits; \
	unsigned int __i; \
	for (__i = 0; __i < ((id_size) >> PSS_NET_NBITS_SHIFT); __i++) { \
		__bits[__i] = 0; \
	} \
} while (0)

typedef struct {
	uint32_t bits[PSS_NET_FD_SETSIZE >> PSS_NET_NBITS_SHIFT];
} PssNetFdSet;

#define FD_SET(n, p) \
	PSS_NET_ID_SET(n, p, \
	    (int)PSS_NET_ID_SOCKET_MIN, (int)PSS_NET_ID_SOCKET_MAX)
#define FD_CLR(n, p) \
	PSS_NET_ID_CLR(n, p, \
	    (int)PSS_NET_ID_SOCKET_MIN, (int)PSS_NET_ID_SOCKET_MAX)
#define FD_ISSET(n, p) \
	PSS_NET_ID_ISSET(n, p, \
	    (int)PSS_NET_ID_SOCKET_MIN, (int)PSS_NET_ID_SOCKET_MAX)
#define FD_ZERO(p) \
	PSS_NET_ID_ZERO(p, PSS_NET_FD_SETSIZE)
#define FD_SETSIZE PSS_NET_FD_SETSIZE

int pss_net_select (int nfds, PssNetFdSet *readFds, PssNetFdSet *writefds, PssNetFdSet *exceptfds, int ms_timeout);

int pss_return_to_lb( void );
  

#endif /* _PSP2_PSS_H_ */

