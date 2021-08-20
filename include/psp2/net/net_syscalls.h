/**
 * \kernelgroup{SceNet}
 * \usage{psp2/net/net_syscalls.h,SceNetPsForSyscalls_stub}
 */


#ifndef _PSP2_NET_NET_SYSCALLS_H_
#define _PSP2_NET_NET_SYSCALLS_H_

#include <psp2/net/net.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceNetSyscallParameter SceNetSyscallParameter; // missing struct

int sceNetSyscallAccept(int s, void *addr, void *addrlen);
int sceNetSyscallBind(int s, const void *addr, int addrlen);
int sceNetSyscallClose(int s);
int sceNetSyscallConnect(int s, const void *name, int namelen);
int sceNetSyscallControl(int if_index, int code, void *ptr, int len);
int sceNetSyscallDescriptorClose(int id);
int sceNetSyscallDescriptorCreate(const char *name, int flags);
int sceNetSyscallDescriptorCtl(int id, int op, int s, void *info);
int sceNetSyscallDumpAbort(int id, int flags);
int sceNetSyscallDumpClose(int id);
int sceNetSyscallDumpCreate(const char *name, int len, int flags);
int sceNetSyscallDumpRead(int id, void *buf, int len, void *pflags);
int sceNetSyscallEpollAbort(int eid, int flags);
int sceNetSyscallEpollClose(int eid);
int sceNetSyscallEpollCreate(const char *name, int flags);
int sceNetSyscallEpollCtl(int eid, int op, int id, void *event);
int sceNetSyscallEpollWait(SceNetSyscallParameter *param);

/**
 * @brief Get net if list
 *
 * @param[out] list - The output buffer list. size is (0x140 * n)
 * @param[in]  n    - The output size number.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetSyscallGetIfList(void *list, int n);

int sceNetSyscallGetSockinfo(int s, void *ptr, int n, int flags);
int sceNetSyscallGetpeername(int s, void *name, void *namelen);
int sceNetSyscallGetsockname(int s, void *name, void *namelen);
int sceNetSyscallGetsockopt(SceNetSyscallParameter *param);
int sceNetSyscallIcmConnect(int s, int flags);
int sceNetSyscallIoctl(int s, unsigned int com, void *data);
int sceNetSyscallListen(int s, int backlog);
int sceNetSyscallRecvfrom(SceNetSyscallParameter *param);
int sceNetSyscallRecvmsg(int s, void *msg, int flags);
int sceNetSyscallSendmsg(int s, const void *msg, int flags);
int sceNetSyscallSendto(SceNetSyscallParameter *param);
int sceNetSyscallSetsockopt(SceNetSyscallParameter *param);
int sceNetSyscallShutdown(int s, int how);
int sceNetSyscallSocket(const char *name, int domain, int type, int protocol);
int sceNetSyscallSocketAbort(int s, int flags);
int sceNetSyscallSysctl(SceNetSyscallParameter *param);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NET_NET_SYSCALLS_H_ */
