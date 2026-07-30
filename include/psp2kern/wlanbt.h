/**
 * \kernelgroup{SceWlanBt}
 * \usage{psp2kern/wlanbt.h,SceWlanBtForDriver_stub}
 */

#ifndef _PSP2KERN_WLANBT_H_
#define _PSP2KERN_WLANBT_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceWlanBtSetConfiguration(SceUInt32 config);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_WLANBT_H_ */
