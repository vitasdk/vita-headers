/**
 * \kernelgroup{SceUsbSerial}
 * \usage{psp2kern/usbserial.h,SceUsbSerialForDriver_stub}
 */


#ifndef _PSP2KERN_USBSERIAL_H_
#define _PSP2KERN_USBSERIAL_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Activate USB serial device
 *
 * @return 0 on success, < 0 on error
 *
 * @note The user is responsible for making sure no other UDC driver is active. This activates UDC as a "PS Vita" Type D device.
 */
int ksceUsbSerialStart(void);

/**
 * Setup USB serial device
 *
 * @return 0 on success, < 0 on error
 *
 * @param unk Unknown
 */
int ksceUsbSerialSetup(int unk);

/**
 * Get USB device status
 *
 * @return Returns 1 when serial port is open
 */
int ksceUsbSerialStatus(void);

/**
 * Close USB serial device
 */
int ksceUsbSerialClose(void);

/**
 * Get receive buffer length
 *
 * @return Returns length of USB rx buffer
 */
unsigned int ksceUsbSerialGetRecvBufferSize(void);

/**
 * Send data
 *
 * @param[in] *buffer data to send over usb
 * @param[in] len int len of serial buffer data
 * @param unk1 Unknown
 * @param unk2 Unknown
 * @note max send length is 0x10000
 */
SceSize ksceUsbSerialSend(const void *buffer, SceSize len, int unk1, int unk2);

/**
 * Receive Data
 *
 * @param[out] *buffer buffer for incoming data
 * @param[in] max_len max data length to receive
 * @param unk1 Unknown
 * @param unk2 Unknown
 * @note max recv length is 0x10000
 */
SceSize ksceUsbSerialRecv(void *buffer, SceSize max_len, int unk1, int unk2);

#ifdef __cplusplus
}
#endif
#endif /* _PSP2KERN_USBSERIAL_H_ */
