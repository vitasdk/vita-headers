
#ifndef _PSP2_USBSER_H_
#define _PSP2_USBSER_H_

#include <psp2/types.h>


#ifdef __cplusplus
extern "C" {
#endif



	
int SceUsbSerialStartForDriver(void);
int SceUsbSerialSetupForDriver(int unk);	
int SceUsbSerialStatysForDriver(void);
int SceUsbSerialCloseForDriver(void);
unsigned int SceUsbSerialget_lenForDriver(void);
unsigned int SceUsbSerialSebdForDriver(const void *buffer, unsigned int len, int unk1, int unk2);	
unsigned int SceUsbSerialrecvForDriver(void *buffer, unsigned int max_len, int unk1, int unk2);

	
int SceUsbSerialStart(void);
int SceUsbSerialSetup(int unk);	
int SceUsbSerialClose(void);
int SceUsbSerialStatus(void);
unsigned int SceUsbSerialget_len(void);
unsigned int SceUsbSerialSend(const void *buffer, unsigned int len, int unk1, int unk2);	
unsigned int SceUsbSerialrecv(void *buffer, unsigned int max_len, int unk1, int unk2);
#endif
