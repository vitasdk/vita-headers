/**
 * \kernelgroup{SceUsbSerial}
 * \usage{psp2kern/usbserial.h,-lSceUsbSerialForDriver_stub}
 */

/**
 * \file
 * \brief Header file Which defines USB Serial related functions
 *
 * Copyright (C) 2016 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _PSP2_KERNEL_USBSERIAL_H_
#define _PSP2_KERNEL_USBSERIAL_H_

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
 * @param len int len of serial buffer data 
 * @param unk1 Unknown
 * @param unk2 Unknown
 * @note max send length is 0x10000
 */
unsigned int ksceUsbSerialSend(const void *buffer, unsigned int len, int unk1, int unk2);	

/**
 * Receive Data
 *
 * @param[out] *buffer buffer for incoming data
 * @param max_len max data length to receive
 * @param unk1 Unknown
 * @param unk2 Unknown
 * @note max recv length is 0x10000
 */
unsigned int ksceUsbSerialRecv(void *buffer, unsigned int max_len, int unk1, int unk2);

#ifdef __cplusplus
}
#endif
#endif
