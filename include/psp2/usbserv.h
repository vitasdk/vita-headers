/**
 * \usergroup{SceUsbServ}
 * \usage{psp2/usbserv.h,SceUsbServ_stub}
 */

#ifndef _PSP2_USBSERV_H_
#define _PSP2_USBSERV_H_

#include <psp2common/usbserv.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enable accessory port
 *
 * @return 0 on success, < 0 on error
 *
 */
int sceUsbServAccessoryActivate(void);

/**
 * Disable accessory port
 *
 * @return 0 on success, < 0 on error
 *
 */
int sceUsbServAccessoryDeactivate(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_USBSERV_H_ */
