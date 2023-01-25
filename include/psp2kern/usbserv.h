/**
 * \kernelgroup{SceUsbServ}
 * \usage{psp2kernel/usbserv.h,SceUsbServForDriver_stub}
 */

#ifndef _PSP2KERN_USBSERV_H_
#define _PSP2KERN_USBSERV_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceUsbservErrorCode {
	SCE_USBSERV_ERROR_UNAVAILABLE   = 0x80248002,
	SCE_USBSERV_ERROR_INVALID_PARAM = 0x80248003,
	SCE_USBSERV_ERROR_NOT_SUPPORTED = 0x80248004,

	SCE_USBSERV_ERROR_FATAL         = 0x802480FF
} SceUsbservErrorCode;

/**
 * Enable PSTV ethernet
 *
 * @return 0 on success, < 0 on error
 *
 * @note NID 0x30AE5F66
 */
int ksceUsbServEtherEnable(void);

/**
 * Disable PSTV ethernet
 *
 * @return 0 on success, < 0 on error
 *
 * @note NID 0xD787B191
 */
int ksceUsbServEtherDisable(void);

/**
 * Enable accessory port
 *
 * @return 0 on success, < 0 on error
 *
 * @note NID 0xAA6D4409
 */
int ksceUsbServAccessoryActivate(void);

/**
 * Disable accessory port
 *
 * @return 0 on success, < 0 on error
 *
 * @note NID 0x853CB8E4
 */
int ksceUsbServAccessoryDeactivate(void);

/**
 * Set USB port mode
 *
 * @return 0 on success, < 0 on error
 *
 * @param usbPort usb port number (0,1,2)
 * @param clientMode 0 = host mode, 1 = client mode
 *
 * @note NID 0x7AD36284
 */
int ksceUsbServMacSelect(SceUInt usbPort, SceBool clientMode);

/**
 * Get USB port mode
 *
 * @return usb port mode (1 = client, 0 = host)
 *
 * @param usbPort usb port number (0,1,2)
 *
 * @note NID 0xF0553A69
 */
SceBool ksceUsbServMacGet(SceUInt usbPort);

/**
 * Prevent PSTV ethernet hibernation
 *
 * @return 0 on success, < 0 on error
 *
 * @note NID 0x6D738018, guessed name
 */
int ksceUsbServDisableEtherSuspend(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_USBSERV_H_ */
