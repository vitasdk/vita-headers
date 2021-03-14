/**
 * \kernelgroup{SceNet}
 * \usage{psp2/net/net_syscalls.h,SceNetPsForSyscalls_stub}
 */


#ifndef _PSP2_NET_NET_SYSCALLS_H_
#define _PSP2_NET_NET_SYSCALLS_H_

#include <psp2/net/net.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get net if list
 *
 * @param[out] dst  - The output buffer list. size is (0x140 * size)
 * @param[in]  size - The output size number.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetSyscallGetIfList(void *dst, SceUInt32 size);

int sceNetSyscallConnect(int s, const SceNetSockaddr *name, unsigned int namelen);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NET_NET_SYSCALLS_H_ */
