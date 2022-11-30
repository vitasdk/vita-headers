/**
 * \usergroup{SceUsbServ}
 * \usage{psp2/usbserv.h,SceUsbServ_stub}
 */

#ifndef _PSP2_USBSERV_H_
#define _PSP2_USBSERV_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceUsbservErrorCode {
    SCE_USBSERV_ERROR_UNAVAILABLE    = 0x80248002,
    SCE_USBSERV_ERROR_INVALID_PARAM  = 0x80248003,
    SCE_USBSERV_ERROR_NOT_SUPPORTED = 0x80248004,

    SCE_USBSERV_ERROR_FATAL          = 0x802480FF
} SceUsbservErrorCode;

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
