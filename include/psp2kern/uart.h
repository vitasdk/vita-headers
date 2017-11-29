/**
 * \kernelgroup{SceUart}
 * \usage{psp2kern/uart.h,SceUartForKernel_stub}
 */

#ifndef _PSP2_KERN_UART_H_
#define _PSP2_KERN_UART_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ksceUartInit(int port);
int ksceUartReadAvailable(int port);
int ksceUartRead(int port);
int ksceUartWrite(int port, char data);
int kscePervasiveUartSetBaudrate(int port, unsigned int baudrate);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERN_UART_H_ */

