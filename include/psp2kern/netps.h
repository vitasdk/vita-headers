/**
 * \kernelgroup{SceNet}
 * \usage{psp2kern/netps.h,SceNetPsForDriver_stub}
 */


#ifndef _PSP2KERN_NET_NET_H_
#define _PSP2KERN_NET_NET_H_

#include <vitasdk/build_utils.h>
#include <psp2common/net.h>

#ifdef __cplusplus
extern "C" {
#endif

/* prototypes */

int ksceNetSocket(const char *name, int domain, int type, int protocol);
int ksceNetAccept(int s, SceNetSockaddr *addr, unsigned int *addrlen);
int ksceNetBind(int s, const SceNetSockaddr *addr, unsigned int addrlen);
int ksceNetConnect(int s, const SceNetSockaddr *name, unsigned int namelen);
int ksceNetListen(int s, int backlog);
int ksceNetRecvfrom(int s, void *buf, unsigned int len, int flags, SceNetSockaddr *from, unsigned int *fromlen);
int ksceNetSendto(int s, const void *msg, unsigned int len, int flags, const SceNetSockaddr *to, unsigned int tolen);
int ksceNetSetsockopt(int s, int level, int optname, const void *optval, unsigned int optlen);
int ksceNetClose(int s);

#define ksceNetRecv(s, buf, len, flags) ksceNetRecvfrom(s, buf, len, flags, NULL, 0)
#define ksceNetSend(s, msg, len, flags) ksceNetSendto(s, msg, len, flags, NULL, 0)
#define ksceNetSocketClose ksceNetClose

/* fixme ? */
#define ksceNetHtons __builtin_bswap16
#define ksceNetHtonl __builtin_bswap32

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_NET_NET_H_ */
