/**
 * \usergroup{SceUsbstorVStorDriver}
 * \usage{psp2/usbstorvstor.h,-lSceUsbstorVStorDriver_stub}
 */


#ifndef _PSP2_USBSTORVSTOR_H_
#define _PSP2_USBSTORVSTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

enum {
	SCE_USBSTOR_VSTOR_TYPE_FAT		= 0,
	SCE_USBSTOR_VSTOR_TYPE_CDROM	= 5,
};

/**
 * Set image file path
 *
 * @param[in] path - Image file path
 *
 * @return 0 on success, < 0 on error.
*/
int sceUsbstorVStorSetImgFilePath(const char *path);

/**
 * Set USB descriptor device information
 *
 * @param[in] name - Name
 * @param[in] version - Version
 *
 * @return 0 on success, < 0 on error.
*/
int sceUsbstorVStorSetDeviceInfo(const char *name, const char *version);

/**
 * Start USB virtual storage
 *
 * @param[in] type - One of ::UsbStorVstorType
 *
 * @return 0 on success, < 0 on error.
*/
int sceUsbstorVStorStart(int type);

/**
 * Stop USB virtual storage
 *
 * @return 0 on success, < 0 on error.
*/
int sceUsbstorVStorStop(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_USBSTORVSTOR_H_ */
