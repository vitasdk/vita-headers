/**
 * \usergroup{SceUsbSerial}
 * \usage{psp2/usbserial.h,SceUsbSerial_stub}
 */


#ifndef _PSP2_USBSERIAL_H_
#define _PSP2_USBSERIAL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Activate USB serial device
 *
 * @return 0 on success, < 0 on error
 *
 * @note The user is responsible for making sure no other UDC driver is active. This activates UDC as a "PS Vita" Type D device.
 *
 * @note Wrapper for kernel function sceUsbSerialStartForDriver()
 */
int sceUsbSerialStart(void);

/**
 * Setup USB serial device
 *
 * @return 0 on success, < 0 on error
 *
 * @param unk Unknown
 *
 * @note Wrapper for kernel function sceUsbSerialSetupForDriver()
 */
int sceUsbSerialSetup(int unk);

/**
 * Close USB serial device
 *
 * @note Wrapper for kernel function sceUsbSerialCloseForDriver()
 */
int sceUsbSerialClose(void);

/**
 * Close USB serial device
 *
 * @return Returns 1 when serial port is open
 *
 * @note Wrapper for kernel function sceUsbSerialStatusForDriver()
 */
int sceUsbSerialStatus(void);

/**
 * Get receive buffer length
 *
 * @return Returns length of USB rx buffer
 *
 * @note Wrapper for kernel function sceUsbSerialGetLenForDriver()
 */
unsigned int sceUsbSerialGetRecvBufferSize(void);

/**
 * Send data
 * @param[in] *buffer data to send over usb
 * @param len int len of serial buffer data
 * @param unk1 Unknown
 * @param unk2 Unknown
 * @note max send length is 0x10000
 * @note Wrapper for kernel function sceUsbSerialSendForDriver()
 */
unsigned int sceUsbSerialSend(const void *buffer, unsigned int len, int unk1, int unk2);

/**
 * Receive Data
 *
 * @param[out] *buffer buffer for incoming data
 * @param max_len max data length to receive
 * @param unk1 Unknown
 * @param unk2 Unknown
 * @note max recv length is 0x10000
 * @note Wrapper for kernel function sceUsbSerialRecvForDriver()
 */
unsigned int sceUsbSerialRecv(void *buffer, unsigned int max_len, int unk1, int unk2);

#ifdef __cplusplus
}
#endif
#endif /* _PSP2_USBSERIAL_H_ */
