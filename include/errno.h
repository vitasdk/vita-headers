/*
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _ERRNO_H_
#define _ERRNO_H_

#define EPERM 1
#define ENOENT	2
#define ESRCH	3
#define EINTR	4
#define EIO	5
#define ENXIO	6
#define E2BIG	7
#define ENOEXEC	8
#define EBADF	9
#define ECHILD	10
#define EAGAIN	11
#define EWOULDBLOCK 11
#define ENOMEM	12
#define EACCES	13
#define EFAULT	14
#define ENOTBLK	15
#define EBUSY	16
#define EEXIST	17
#define EXDEV	18
#define ENODEV	19
#define ENOTDIR	20
#define EISDIR	21
#define EINVAL	22
#define ENFILE	23
#define EMFILE	24
#define ENOTTY	25
#define ETXTBSY	26
#define EFBIG	27
#define ENOSPC	28
#define ESPIPE	29
#define EROFS	30
#define EMLINK	31
#define EPIPE	32
#define EDOM	33
#define ERANGE	34
#define ENOMSG	35
#define EIDRM	36
#define ECHRNG	37
#define EL2NSYNC	38
#define EL3HLT	39
#define EL3RST	40
#define ELNRNG	41
#define EUNATCH	42
#define ENOCSI	43
#define EL2HLT	44
#define EDEADLK	45
#define ENOLCK	46
#define EFORMAT	47
#define EUNSUP	48

#define EBADE	50
#define EBADR	51
#define EXFULL	52
#define ENOANO	53
#define EBADRQC	54
#define EBADSLT	55
#define EDEADLOCK	56
#define EBFONT	57

#define ENOSTR	60
#define ENODATA	61
#define ETIME	62
#define ENOSR	63
#define ENONET	64
#define ENOPKG	65
#define EREMOTE	66
#define ENOLINK	67
#define EADV	68
#define ESRMNT	69
#define ECOMM	70
#define EPROTO	71

#define EMULTIHOP	74
#define ELBIN	75
#define EDOTDOT	76
#define EBADMSG	77
#define EFTYPE	79
#define ENOTUNIQ	80
#define EBADFD	81
#define EREMCHG	82
#define ELIBACC	83
#define ELIBBAD	84
#define ELIBSCN	85
#define ELIBMAX	86
#define ELIBEXEC	87
#define ENOSYS	88
#define ENMFILE	89
#define ENOTEMPTY	90
#define ENAMETOOLONG	91
#define ELOOP	92

#define EOPNOTSUPP	95
#define EPFNOSUPPORT	96

#define ECONNRESET	104
#define ENOBUFS	105
#define EAFNOSUPPORT	106
#define EPROTOTYPE	107
#define ENOTSOCK	108
#define ENOPROTOOPT	109
#define ESHUTDOWN	110
#define ECONNREFUSED	111
#define EADDRINUSE	112
#define ECONNABORTED	113
#define ENETUNREACH	114
#define ENETDOWN	115
#define ETIMEDOUT	116
#define EHOSTDOWN	117
#define EHOSTUNREACH	118
#define EINPROGRESS	119
#define EALREADY	120
#define EDESTADDRREQ	121
#define EMSGSIZE	122
#define EPROTONOSUPPORT	123
#define ESOCKTNOSUPPORT	124
#define EADDRNOTAVAIL	125
#define ENETRESET	126
#define EISCONN	127
#define ENOTCONN	128
#define ETOOMANYREFS	129
#define EPROCLIM	130
#define EUSERS	131
#define EDQUOT	132
#define ESTALE	133
#define ENOTSUP	134
#define ENOMEDIUM	135
#define ENOSHARE	136
#define ECASECLASH	137
#define EILSEQ	138
#define EOVERFLOW	139
#define ECANCELED	140
#define ENOTRECOVERABLE	141
#define EOWNERDEAD	142

int *_sceLibcErrnoLoc(void);

#define errno (*_sceLibcErrnoLoc())

#endif
