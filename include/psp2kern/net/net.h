/**
 * \kernelgroup{SceNet}
 * \usage{psp2kern/net/net.h,-lSceNetPsForDriver_stub}
 */

/**
 * \file
 * \brief Header file related to net
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _PSP2_KERNEL_NET_NET_H_
#define _PSP2_KERNEL_NET_NET_H_

#ifdef __cplusplus
extern "C" {
#endif

/** Net Error Codes */
enum {
	SCE_NET_ERROR_EPERM					= 0x80410101,
	SCE_NET_ERROR_ENOENT					= 0x80410102,
	SCE_NET_ERROR_ESRCH					= 0x80410103,
	SCE_NET_ERROR_EINTR					= 0x80410104,
	SCE_NET_ERROR_EIO						= 0x80410105,
	SCE_NET_ERROR_ENXIO					= 0x80410106,
	SCE_NET_ERROR_E2BIG					= 0x80410107,
	SCE_NET_ERROR_ENOEXEC					= 0x80410108,
	SCE_NET_ERROR_EBADF					= 0x80410109,
	SCE_NET_ERROR_ECHILD					= 0x8041010A,
	SCE_NET_ERROR_EDEADLK					= 0x8041010B,
	SCE_NET_ERROR_ENOMEM					= 0x8041010C,
	SCE_NET_ERROR_EACCES					= 0x8041010D,
	SCE_NET_ERROR_EFAULT					= 0x8041010E,
	SCE_NET_ERROR_ENOTBLK					= 0x8041010F,
	SCE_NET_ERROR_EBUSY					= 0x80410110,
	SCE_NET_ERROR_EEXIST					= 0x80410111,
	SCE_NET_ERROR_EXDEV					= 0x80410112,
	SCE_NET_ERROR_ENODEV					= 0x80410113,
	SCE_NET_ERROR_ENOTDIR					= 0x80410114,
	SCE_NET_ERROR_EISDIR					= 0x80410115,
	SCE_NET_ERROR_EINVAL					= 0x80410116,
	SCE_NET_ERROR_ENFILE					= 0x80410117,
	SCE_NET_ERROR_EMFILE					= 0x80410118,
	SCE_NET_ERROR_ENOTTY					= 0x80410119,
	SCE_NET_ERROR_ETXTBSY					= 0x8041011A,
	SCE_NET_ERROR_EFBIG					= 0x8041011B,
	SCE_NET_ERROR_ENOSPC					= 0x8041011C,
	SCE_NET_ERROR_ESPIPE					= 0x8041011D,
	SCE_NET_ERROR_EROFS					= 0x8041011E,
	SCE_NET_ERROR_EMLINK					= 0x8041011F,
	SCE_NET_ERROR_EPIPE					= 0x80410120,
	SCE_NET_ERROR_EDOM						= 0x80410121,
	SCE_NET_ERROR_ERANGE					= 0x80410122,
	SCE_NET_ERROR_EAGAIN					= 0x80410123,
	SCE_NET_ERROR_EWOULDBLOCK				= 0x80410123,
	SCE_NET_ERROR_EINPROGRESS				= 0x80410124,
	SCE_NET_ERROR_EALREADY					= 0x80410125,
	SCE_NET_ERROR_ENOTSOCK					= 0x80410126,
	SCE_NET_ERROR_EDESTADDRREQ				= 0x80410127,
	SCE_NET_ERROR_EMSGSIZE					= 0x80410128,
	SCE_NET_ERROR_EPROTOTYPE				= 0x80410129,
	SCE_NET_ERROR_ENOPROTOOPT				= 0x8041012A,
	SCE_NET_ERROR_EPROTONOSUPPORT			= 0x8041012B,
	SCE_NET_ERROR_ESOCKTNOSUPPOR			= 0x8041012C,
	SCE_NET_ERROR_EOPNOTSUPP				= 0x8041012D,
	SCE_NET_ERROR_EPFNOSUPPORT				= 0x8041012E,
	SCE_NET_ERROR_EAFNOSUPPORT				= 0x8041012F,
	SCE_NET_ERROR_EADDRINUSE				= 0x80410130,
	SCE_NET_ERROR_EADDRNOTAVAIL			= 0x80410131,
	SCE_NET_ERROR_ENETDOWN					= 0x80410132,
	SCE_NET_ERROR_ENETUNREACH				= 0x80410133,
	SCE_NET_ERROR_ENETRESET				= 0x80410134,
	SCE_NET_ERROR_ECONNABORTED				= 0x80410135,
	SCE_NET_ERROR_ECONNRESET				= 0x80410136,
	SCE_NET_ERROR_ENOBUFS					= 0x80410137,
	SCE_NET_ERROR_EISCONN					= 0x80410138,
	SCE_NET_ERROR_ENOTCONN					= 0x80410139,
	SCE_NET_ERROR_ESHUTDOWN				= 0x8041013A,
	SCE_NET_ERROR_ETOOMANYREFS				= 0x8041013B,
	SCE_NET_ERROR_ETIMEDOUT				= 0x8041013C,
	SCE_NET_ERROR_ECONNREFUSED				= 0x8041013D,
	SCE_NET_ERROR_ELOOP					= 0x8041013E,
	SCE_NET_ERROR_ENAMETOOLONG				= 0x8041013F,
	SCE_NET_ERROR_EHOSTDOWN				= 0x80410140,
	SCE_NET_ERROR_EHOSTUNREACH				= 0x80410141,
	SCE_NET_ERROR_ENOTEMPTY				= 0x80410142,
	SCE_NET_ERROR_EPROCLIM					= 0x80410143,
	SCE_NET_ERROR_EUSERS					= 0x80410144,
	SCE_NET_ERROR_EDQUOT					= 0x80410145,
	SCE_NET_ERROR_ESTALE					= 0x80410146,
	SCE_NET_ERROR_EREMOTE					= 0x80410147,
	SCE_NET_ERROR_EBADRPC					= 0x80410148,
	SCE_NET_ERROR_ERPCMISMATCH				= 0x80410149,
	SCE_NET_ERROR_EPROGUNAVAIL				= 0x8041014A,
	SCE_NET_ERROR_EPROGMISMATCH			= 0x8041014B,
	SCE_NET_ERROR_EPROCUNAVAIL				= 0x8041014C,
	SCE_NET_ERROR_ENOLCK					= 0x8041014D,
	SCE_NET_ERROR_ENOSYS					= 0x8041014E,
	SCE_NET_ERROR_EFTYPE					= 0x8041014F,
	SCE_NET_ERROR_EAUTH					= 0x80410150,
	SCE_NET_ERROR_ENEEDAUTH				= 0x80410151,
	SCE_NET_ERROR_EIDRM					= 0x80410152,
	SCE_NET_ERROR_ENOMS					= 0x80410153,
	SCE_NET_ERROR_EOVERFLOW				= 0x80410154,
	SCE_NET_ERROR_EILSEQ					= 0x80410155,
	SCE_NET_ERROR_ENOTSUP					= 0x80410156,
	SCE_NET_ERROR_ECANCELED				= 0x80410157,
	SCE_NET_ERROR_EBADMSG					= 0x80410158,
	SCE_NET_ERROR_ENODATA					= 0x80410159,
	SCE_NET_ERROR_ENOSR					= 0x8041015A,
	SCE_NET_ERROR_ENOSTR					= 0x8041015B,
	SCE_NET_ERROR_ETIME					= 0x8041015C,
	SCE_NET_ERROR_EADHOC					= 0x804101A0,
	SCE_NET_ERROR_EDISABLEDIF				= 0x804101A1,
	SCE_NET_ERROR_ERESUME					= 0x804101A2,
	SCE_NET_ERROR_ENOTINIT					= 0x804101C8,
	SCE_NET_ERROR_ENOLIBMEM				= 0x804101C9,
	SCE_NET_ERROR_ERESERVED202				= 0x804101CA,
	SCE_NET_ERROR_ECALLBACK				= 0x804101CB,
	SCE_NET_ERROR_EINTERNAL				= 0x804101CC,
	SCE_NET_ERROR_ERETURN					= 0x804101CD,
	SCE_NET_ERROR_RESOLVER_EINTERNAL		= 0x804101DC,
	SCE_NET_ERROR_RESOLVER_EBUSY			= 0x804101DD,
	SCE_NET_ERROR_RESOLVER_ENOSPACE		= 0x804101DE,
	SCE_NET_ERROR_RESOLVER_EPACKET			= 0x804101DF,
	SCE_NET_ERROR_RESOLVER_ERESERVED22 	= 0x804101E0,
	SCE_NET_ERROR_RESOLVER_ENODNS			= 0x804101E1,
	SCE_NET_ERROR_RESOLVER_ETIMEDOUT		= 0x804101E2,
	SCE_NET_ERROR_RESOLVER_ENOSUPPORT		= 0x804101E3,
	SCE_NET_ERROR_RESOLVER_EFORMAT			= 0x804101E4,
	SCE_NET_ERROR_RESOLVER_ESERVERFAILURE	= 0x804101E5,
	SCE_NET_ERROR_RESOLVER_ENOHOST			= 0x804101E6,
	SCE_NET_ERROR_RESOLVER_ENOTIMPLEMENTED	= 0x804101E7,
	SCE_NET_ERROR_RESOLVER_ESERVERREFUSED	= 0x804101E8,
	SCE_NET_ERROR_RESOLVER_ENORECORD		= 0x804101E9,
	SCE_NET_ERROR_RESOLVER_EALIGNMENT		= 0x804101EA
};

/** Specific kernel and libnet error codes */
enum {
	SCE_NET_EPERM				= 1,
	SCE_NET_ENOENT				= 2,
	SCE_NET_ESRCH				= 3,
	SCE_NET_EINTR				= 4,
	SCE_NET_EIO				= 5,
	SCE_NET_ENXIO				= 6,
	SCE_NET_E2BIG				= 7,
	SCE_NET_ENOEXEC			= 8,
	SCE_NET_EBADF				= 9,
	SCE_NET_ECHILD				= 10,
	SCE_NET_EDEADLK			= 11,
	SCE_NET_ENOMEM				= 12,
	SCE_NET_EACCES				= 13,
	SCE_NET_EFAULT				= 14,
	SCE_NET_ENOTBLK			= 15,
	SCE_NET_EBUSY				= 16,
	SCE_NET_EEXIST				= 17,
	SCE_NET_EXDEV				= 18,
	SCE_NET_ENODEV				= 19,
	SCE_NET_ENOTDIR			= 20,
	SCE_NET_EISDIR				= 21,
	SCE_NET_EINVAL				= 22,
	SCE_NET_ENFILE				= 23,
	SCE_NET_EMFILE				= 24,
	SCE_NET_ENOTTY				= 25,
	SCE_NET_ETXTBSY			= 26,
	SCE_NET_EFBIG				= 27,
	SCE_NET_ENOSPC				= 28,
	SCE_NET_ESPIPE				= 29,
	SCE_NET_EROFS				= 30,
	SCE_NET_EMLINK				= 31,
	SCE_NET_EPIPE				= 32,
	SCE_NET_EDOM				= 33,
	SCE_NET_ERANGE				= 34,
	SCE_NET_EAGAIN				= 35,
	SCE_NET_EWOULDBLOCK		= 35,
	SCE_NET_EINPROGRESS		= 36,
	SCE_NET_EALREADY			= 37,
	SCE_NET_ENOTSOCK			= 38,
	SCE_NET_EDESTADDRREQ		= 39,
	SCE_NET_EMSGSIZE			= 40,
	SCE_NET_EPROTOTYPE			= 41,
	SCE_NET_ENOPROTOOPT		= 42,
	SCE_NET_EPROTONOSUPPORT	= 43,
	SCE_NET_ESOCKTNOSUPPORT	= 44,
	SCE_NET_EOPNOTSUPP			= 45,
	SCE_NET_EPFNOSUPPORT		= 46,
	SCE_NET_EAFNOSUPPORT		= 47,
	SCE_NET_EADDRINUSE 		= 48,
	SCE_NET_EADDRNOTAVAIL		= 49,
	SCE_NET_ENETDOWN			= 50,
	SCE_NET_ENETUNREACH		= 51,
	SCE_NET_ENETRESET			= 52,
	SCE_NET_ECONNABORTED		= 53,
	SCE_NET_ECONNRESET			= 54,
	SCE_NET_ENOBUFS			= 55,
	SCE_NET_EISCONN			= 56,
	SCE_NET_ENOTCONN			= 57,
	SCE_NET_ESHUTDOWN			= 58,
	SCE_NET_ETOOMANYREFS		= 59,
	SCE_NET_ETIMEDOUT			= 60,
	SCE_NET_ECONNREFUSED		= 61,
	SCE_NET_ELOOP				= 62,
	SCE_NET_ENAMETOOLONG		= 63,
	SCE_NET_EHOSTDOWN			= 64,
	SCE_NET_EHOSTUNREACH		= 65,
	SCE_NET_ENOTEMPTY			= 66,
	SCE_NET_EPROCLIM			= 67,
	SCE_NET_EUSERS				= 68,
	SCE_NET_EDQUOT				= 69,
	SCE_NET_ESTALE				= 70,
	SCE_NET_EREMOTE			= 71,
	SCE_NET_EBADRPC			= 72,
	SCE_NET_ERPCMISMATCH		= 73,
	SCE_NET_EPROGUNAVAIL		= 74,
	SCE_NET_EPROGMISMATCH		= 75,
	SCE_NET_EPROCUNAVAIL		= 76,
	SCE_NET_ENOLCK				= 77,
	SCE_NET_ENOSYS				= 78,
	SCE_NET_EFTYPE				= 79,
	SCE_NET_EAUTH				= 80,
	SCE_NET_ENEEDAUTH			= 81,
	SCE_NET_EIDRM				= 82,
	SCE_NET_ENOMSG				= 83,
	SCE_NET_EOVERFLOW			= 84,
	SCE_NET_EILSEQ				= 85,
	SCE_NET_ENOTSUP			= 86,
	SCE_NET_ECANCELED			= 87,
	SCE_NET_EBADMSG			= 88,
	SCE_NET_ENODATA			= 89,
	SCE_NET_ENOSR				= 90,
	SCE_NET_ENOSTR				= 91,
	SCE_NET_ETIME				= 92,
	SCE_NET_EADHOC				= 160,
	SCE_NET_EDISABLEDIF		= 161,
	SCE_NET_ERESUME			= 162
};


/** libnet specific error codes */
enum {
	SCE_NET_ENOTINIT	= 200,
	SCE_NET_ENOLIBMEM,
	SCE_NET_ETLS,
	SCE_NET_ECALLBACK,
	SCE_NET_EINTERNAL,
	SCE_NET_ERETURN
};

/** Resolver specific error codes */
enum {
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
};

/** Flags to specify as argument to ::ksceNetDumpRead() */
enum {
	SCE_NET_DUMP_PEEK						= 0x00000010,
	SCE_NET_DUMP_DONTWAIT					= 0x00000020,
	SCE_NET_DUMP_OVERFLOW					= 0x00000040,
	SCE_NET_DUMP_ABORT_FLAG_PRESERVATION	= 0x00000001
};

/** Events for ::SceNetEpollEvent */
enum {
	SCE_NET_EPOLLIN		= 0x00000001,
	SCE_NET_EPOLLOUT		= 0x00000002,
	SCE_NET_EPOLLERR		= 0x00000008,
	SCE_NET_EPOLLHUP		= 0x00000010,
	SCE_NET_EPOLLDESCID	= 0x00010000
};

/** Flags to specify as argument to ::ksceNetEpollControl() */
enum {
	SCE_NET_EPOLL_CTL_ADD = 1,
	SCE_NET_EPOLL_CTL_MOD,
	SCE_NET_EPOLL_CTL_DEL
};

/** state for ::SceNetSockInfo structure */
enum {
	SCE_NET_SOCKINFO_STATE_UNKNOWN,
	SCE_NET_SOCKINFO_STATE_CLOSED,
	SCE_NET_SOCKINFO_STATE_OPENED,
	SCE_NET_SOCKINFO_STATE_LISTEN,
	SCE_NET_SOCKINFO_STATE_SYN_SENT,
	SCE_NET_SOCKINFO_STATE_SYN_RECEIVED,
	SCE_NET_SOCKINFO_STATE_ESTABLISHED,
	SCE_NET_SOCKINFO_STATE_FIN_WAIT_1,
	SCE_NET_SOCKINFO_STATE_FIN_WAIT_2,
	SCE_NET_SOCKINFO_STATE_CLOSE_WAIT,
	SCE_NET_SOCKINFO_STATE_CLOSING,
	SCE_NET_SOCKINFO_STATE_LAST_ACK,
	SCE_NET_SOCKINFO_STATE_TIME_WAIT
};

/** flags for ::SceNetSockInfo structure */
enum {
	SCE_NET_SOCKINFO_F_SELF			= 0x00000001,
	SCE_NET_SOCKINFO_F_KERNEL			= 0x00000002,
	SCE_NET_SOCKINFO_F_OTHERS			= 0x00000004,
	SCE_NET_SOCKINFO_F_RECV_WAIT		= 0x00010000,
	SCE_NET_SOCKINFO_F_SEND_WAIT		= 0x00020000,
	SCE_NET_SOCKINFO_F_RECV_EWAIT		= 0x00040000,
	SCE_NET_SOCKINFO_F_SEND_EWAIT		= 0x00080000,
	SCE_NET_SOCKINFO_F_WAKEUP_SIGNAL	= 0x00100000,
	SCE_NET_SOCKINFO_F_ALL				= 0x001F0007
};

/** Flags to specify as argument to ::ksceNetEmulationGet() / ::ksceNetEmulationSet() */
enum {
	SCE_NET_EMULATION_FLAG_ETH0	= 1,
	SCE_NET_EMULATION_FLAG_WLAN0
};

/** Flags to specify as argument to ::ksceNetResolverStartNtoa() / ::ksceNetResolverStartAton() */
enum {
	SCE_NET_RESOLVER_ASYNC							= 0x00000001,
	SCE_NET_RESOLVER_START_NTOA_DISABLE_IPADDRESS	= 0x00010000
};

/** Flags to specify as argument to ::ksceNetResolverAbort() */
enum {
	SCE_NET_RESOLVER_ABORT_FLAG_NTOA_PRESERVATION	= 0x00000001,
	SCE_NET_RESOLVER_ABORT_FLAG_ATON_PRESERVATION	= 0x00000002
};

/** Flags to specify as argument to ::ksceNetSocketAbort() */
enum {
	SCE_NET_SOCKET_ABORT_FLAG_RCV_PRESERVATION	= 0x00000001,
	SCE_NET_SOCKET_ABORT_FLAG_SND_PRESERVATION	= 0x00000002
};

/** Net Protocols */
enum {
	SCE_NET_IPPROTO_IP		= 0,
	SCE_NET_IPPROTO_ICMP	= 1,
	SCE_NET_IPPROTO_IGMP	= 2,
	SCE_NET_IPPROTO_TCP	= 6,
	SCE_NET_IPPROTO_UDP	= 17,
	SCE_NET_SOL_SOCKET		= 0xffff
};

/** Socket Options */
enum {
	/* IP */
	SCE_NET_IP_HDRINCL				= 2,
	SCE_NET_IP_TOS					= 3,
	SCE_NET_IP_TTL					= 4,
	SCE_NET_IP_MULTICAST_IF		= 9,
	SCE_NET_IP_MULTICAST_TTL		= 10,
	SCE_NET_IP_MULTICAST_LOOP		= 11,
	SCE_NET_IP_ADD_MEMBERSHIP		= 12,
	SCE_NET_IP_DROP_MEMBERSHIP		= 13,
	SCE_NET_IP_TTLCHK				= 23,
	SCE_NET_IP_MAXTTL				= 24,
	/* TCP */
	SCE_NET_TCP_NODELAY			= 1,
	SCE_NET_TCP_MAXSEG				= 2,
	SCE_NET_TCP_MSS_TO_ADVERTISE	= 3,
	/* SOCKET */
	SCE_NET_SO_REUSEADDR			= 0x00000004,
	SCE_NET_SO_KEEPALIVE			= 0x00000008,
	SCE_NET_SO_BROADCAST			= 0x00000020,
	SCE_NET_SO_LINGER				= 0x00000080,
	SCE_NET_SO_OOBINLINE			= 0x00000100,
	SCE_NET_SO_REUSEPORT			= 0x00000200,
	SCE_NET_SO_ONESBCAST			= 0x00000800,
	SCE_NET_SO_USECRYPTO			= 0x00001000,
	SCE_NET_SO_USESIGNATURE		= 0x00002000,
	SCE_NET_SO_SNDBUF				= 0x1001,
	SCE_NET_SO_RCVBUF				= 0x1002,
	SCE_NET_SO_SNDLOWAT			= 0x1003,
	SCE_NET_SO_RCVLOWAT			= 0x1004,
	SCE_NET_SO_SNDTIMEO			= 0x1005,
	SCE_NET_SO_RCVTIMEO			= 0x1006,
	SCE_NET_SO_ERROR				= 0x1007,
	SCE_NET_SO_TYPE				= 0x1008,
	SCE_NET_SO_NBIO				= 0x1100,
	SCE_NET_SO_TPPOLICY			= 0x1101,
	SCE_NET_SO_NAME				= 0x1102
};

/** Socket types */
enum {
	SCE_NET_SOCK_STREAM		= 1,
	SCE_NET_SOCK_DGRAM			= 2,
	SCE_NET_SOCK_RAW			= 3,
	SCE_NET_SOCK_DGRAM_P2P		= 6,
	SCE_NET_SOCK_STREAM_P2P	= 10
};

/** MSG Flags */
enum {
	SCE_NET_MSG_PEEK			= 0x00000002,
	SCE_NET_MSG_WAITALL		= 0x00000040,
	SCE_NET_MSG_DONTWAIT		= 0x00000080,
	SCE_NET_MSG_USECRYPTO		= 0x00000400,
	SCE_NET_MSG_USESIGNATURE	= 0x00000800
};

/** Flags to specify as argument to ::ksceNetShutdown() */
enum {
	SCE_NET_SHUT_RD,
	SCE_NET_SHUT_WR,
	SCE_NET_SHUT_RDWR
};

/** Types to specify to ::SceNetIcmpHeader structure */
enum {
	SCE_NET_ICMP_TYPE_ECHO_REPLY			= 0,
	SCE_NET_ICMP_TYPE_DEST_UNREACH			= 3,
	SCE_NET_ICMP_TYPE_SOURCE_QUENCH		= 4,
	SCE_NET_ICMP_TYPE_REDIRECT				= 5,
	SCE_NET_ICMP_TYPE_ECHO_REQUEST			= 8,
	SCE_NET_ICMP_TYPE_TIME_EXCEEDED		= 11,
	SCE_NET_ICMP_TYPE_PARAMETER_PROBLEM	= 12,
	SCE_NET_ICMP_TYPE_TIMESTAMP_REQUEST	= 13,
	SCE_NET_ICMP_TYPE_TIMESTAMP_REPLY		= 14,
	SCE_NET_ICMP_TYPE_INFORMATION_REQUEST	= 15,
	SCE_NET_ICMP_TYPE_INFORMATION_REPLY	= 16,
	SCE_NET_ICMP_TYPE_ADDRESS_MASK_REQUEST	= 17,
	SCE_NET_ICMP_TYPE_ADDRESS_MASK_REPLY	= 18
};

/** Codes to specify to ::SceNetIcmpHeader structure */
enum {
	SCE_NET_ICMP_CODE_DEST_UNREACH_NET_UNREACH				= 0,
	SCE_NET_ICMP_CODE_DEST_UNREACH_HOST_UNREACH			= 1,
	SCE_NET_ICMP_CODE_DEST_UNREACH_PROTO_UNREACH			= 2,
	SCE_NET_ICMP_CODE_DEST_UNREACH_PORT_UNREACH			= 3,
	SCE_NET_ICMP_CODE_DEST_UNREACH_FRAG_AND_DF				= 4,
	SCE_NET_ICMP_CODE_DEST_UNREACH_SRC_HOST_FAILED			= 5,
	SCE_NET_ICMP_CODE_DEST_UNREACH_DST_NET_UNKNOWN			= 6,
	SCE_NET_ICMP_CODE_DEST_UNREACH_DST_HOST_UNKNOWN		= 7,
	SCE_NET_ICMP_CODE_DEST_UNREACH_SRC_HOST_ISOLATED		= 8,
	SCE_NET_ICMP_CODE_DEST_UNREACH_NET_ADMIN_PROHIBITED	= 9,
	SCE_NET_ICMP_CODE_DEST_UNREACH_NET_HOST_PROHIBITED		= 10,
	SCE_NET_ICMP_CODE_DEST_UNREACH_NET_TOS					= 11,
	SCE_NET_ICMP_CODE_DEST_UNREACH_HOST_TOS				= 12,
	SCE_NET_ICMP_CODE_TIME_EXCEEDED_TTL_EXCEEDED			= 0,
	SCE_NET_ICMP_CODE_TIME_EXCEEDED_FRT_EXCEEDED			= 1
};

/* Defines */
#define SCE_NET_EPOLL_ABORT_FLAG_PRESERVATION   0x00000001

#define SCE_NET_IP_DEFAULT_MULTICAST_TTL   1
#define SCE_NET_IP_DEFAULT_MULTICAST_LOOP  1

#define SCE_NET_IPVERSION   4

#define SCE_NET_IP_RF       0x8000
#define SCE_NET_IP_DF       0x4000
#define SCE_NET_IP_MF       0x2000
#define SCE_NET_IP_OFFMASK  0x1fff

#define SCE_NET_INADDR_ANY           0x00000000
#define SCE_NET_INADDR_LOOPBACK      0x7f000001
#define SCE_NET_INADDR_BROADCAST     0xffffffff
#define SCE_NET_INADDR_UNSPEC_GROUP  0xe0000000
#define SCE_NET_INADDR_AUTOIP        0xa9fe0000

#define SCE_NET_IN_CLASSD_NET        0xf0000000
#define SCE_NET_IN_AUTOIP_NET        0xffff0000

#define SCE_NET_ADHOC_PORT            3658

#define SCE_NET_AF_INET               2

#define SCE_NET_DEBUG_NAME_LEN_MAX 31

#define SCE_NET_RESOLVER_PORT             53
#define SCE_NET_RESOLVER_HOSTNAME_LEN_MAX 255

#define SCE_NET_ID_SOCKET_MIN      0
#define SCE_NET_ID_SOCKET_MAX      1023

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

typedef struct SceNetFdSet {
	unsigned int bits[32];
} SceNetFdSet;

typedef struct SceNetInAddr {
	unsigned int s_addr;
} SceNetInAddr;

typedef struct SceNetSockaddrIn {
	unsigned char sin_len;
	unsigned char sin_family;
	unsigned short int sin_port;
	SceNetInAddr sin_addr;
	unsigned short int sin_vport;
	char sin_zero[6];
} SceNetSockaddrIn;

typedef struct SceNetIpMreq {
	SceNetInAddr imr_multiaddr;
	SceNetInAddr imr_interface;
} SceNetIpMreq;

typedef struct SceNetInitParam {
	void *memory;
	int size;
	int flags;
} SceNetInitParam;

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

typedef struct SceNetEtherAddr {
	unsigned char data[6];
} SceNetEtherAddr;

typedef struct SceNetDnsInfo {
	SceNetInAddr dns_addr[2];
} SceNetDnsInfo;

typedef struct SceNetEpollDataExt {
	int id;
	unsigned int u32;
} SceNetEpollDataExt;

typedef union SceNetEpollData {
	void *ptr;
	int fd;
	unsigned int u32;
	unsigned long long int u64;
	SceNetEpollDataExt ext;
} SceNetEpollData;

typedef struct SceNetEpollSystemData {
	unsigned int system[4];
} SceNetEpollSystemData;

typedef struct SceNetEpollEvent {
	unsigned int events;
	unsigned int reserved;
	SceNetEpollSystemData system;
	SceNetEpollData data;
} SceNetEpollEvent;

typedef struct SceNetResolverParam {
	SceNetResolverFunctionAllocate allocate;
	SceNetResolverFunctionFree free;
	void *user;
} SceNetResolverParam;

typedef struct SceNetLinger {
	int l_onoff;
	int l_linger;
} SceNetLinger;

typedef struct SceNetSockaddr {
	unsigned char sa_len;
	unsigned char sa_family;
	char sa_data[14];
} SceNetSockaddr;

typedef struct SceNetIovec {
	void *iov_base;
	unsigned int iov_len;
} SceNetIovec;

typedef struct SceNetMsghdr {
	void *msg_name;
	unsigned int msg_namelen;
	SceNetIovec *msg_iov;
	int msg_iovlen;
	void *msg_control;
	unsigned int msg_controllen;
	int msg_flags;
} SceNetMsghdr;

typedef struct SceNetSockInfo {
	char name[SCE_NET_DEBUG_NAME_LEN_MAX + 1];
	int pid;
	int s;
	char socket_type;
	char policy;
	short int reserved16;
	int recv_queue_length;
	int send_queue_length;
	SceNetInAddr local_adr;
	SceNetInAddr remote_adr;
	unsigned short int local_port;
	unsigned short int remote_port;
	unsigned short int local_vport;
	unsigned short int remote_vport;
	int state;
	int flags;
	int reserved[8];
} SceNetSockInfo;

typedef struct SceNetStatisticsInfo {

	int kernel_mem_free_size;
	int kernel_mem_free_min;
	int packet_count;
	int packet_qos_count;

	int libnet_mem_free_size;
	int libnet_mem_free_min;
} SceNetStatisticsInfo;

typedef struct SceNetIpHeaderIpVerHl {
	unsigned char hl;
	unsigned char ver;
} SceNetIpHeaderIpVerHl;

typedef union SceNetIpHeaderUnion {
	SceNetIpHeaderIpVerHl ip_ver_hl;
	unsigned char ver_hl;
} SceNetIpHeaderUnion;

typedef struct SceNetIpHeader {
	SceNetIpHeaderUnion un;
	unsigned char ip_tos;
	unsigned short ip_len;
	unsigned short ip_id;
	unsigned short ip_off;
	unsigned char ip_ttl;
	unsigned char ip_p;
	unsigned short ip_sum;
	SceNetInAddr ip_src;
	SceNetInAddr ip_dst;
} SceNetIpHeader;

typedef struct SceNetIcmpHeaderEcho {
	unsigned short id;
	unsigned short sequence;
} SceNetIcmpHeaderEcho;

typedef struct SceNetIcmpHeaderFrag {
	unsigned short unused;
	unsigned short mtu;
} SceNetIcmpHeaderFrag;

typedef union SceNetIcmpHeaderUnion {
	SceNetIcmpHeaderEcho echo;
	unsigned int gateway;
	SceNetIcmpHeaderFrag frag;
} SceNetIcmpHeaderUnion;

typedef struct SceNetIcmpHeader {
	unsigned char type;
	unsigned char code;
	unsigned short checksum;
	SceNetIcmpHeaderUnion un;
} SceNetIcmpHeader;

/* prototypes */

int ksceNetSocket(const char *name, int domain, int type, int protocol);
int ksceNetAccept(int s, SceNetSockaddr *addr, unsigned int *addrlen);
int ksceNetBind(int s, const SceNetSockaddr *addr, unsigned int addrlen);
int ksceNetListen(int s, int backlog);
int ksceNetRecv(int s, void *buf, unsigned int len, int flags);
int ksceNetRecvfrom(int s, void *buf, unsigned int len, int flags, SceNetSockaddr *from, unsigned int *fromlen);
int ksceNetSend(int s, const void *msg, unsigned int len, int flags);
int ksceNetSendto(int s, const void *msg, unsigned int len, int flags, const SceNetSockaddr *to, unsigned int tolen);
int ksceNetSetsockopt(int s, int level, int optname, const void *optval, unsigned int optlen);
int ksceNetSocketClose(int s);

/* fixme ? */
#define ksceNetHtons __builtin_bswap16
#define ksceNetHtonl __builtin_bswap32

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_NET_NET_H_ */
