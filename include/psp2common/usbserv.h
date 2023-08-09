/**
 * \kernelgroup{SceUsbServ}
 * \usage{psp2common/usbserv.h}
 */

#ifndef _PSP2COMMON_USBSERV_H_
#define _PSP2COMMON_USBSERV_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceUsbservErrorCode {
	SCE_USBSERV_ERROR_UNAVAILABLE    = 0x80248002,
	SCE_USBSERV_ERROR_INVALID_PARAM  = 0x80248003,
	SCE_USBSERV_ERROR_NOT_SUPPORTED  = 0x80248004,
	SCE_USBSERV_ERROR_FATAL          = 0x802480FF
} SceUsbservErrorCode;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_USBSERV_H_ */
