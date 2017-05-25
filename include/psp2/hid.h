/**
 * \usergroup{SceHid}
 * \usage{psp2/hid.h,-lSceHid_stub}
 */


#ifndef _PSP2_HID_H_
#define _PSP2_HID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <psp2/types.h>

typedef struct SceHidKeyboardReport {
    SceUInt8 unk0[2];
	SceUInt8 modifier;
	SceUInt8 key1;
	SceUInt8 key2;
	SceUInt8 key3;
	SceUInt8 key4;
	SceUInt8 key5;
	SceUInt8 key6;
	SceUInt8 unk1[15];
	
} SceHidKeyboardReport;

enum {
	SCE_HID_KEYBOARD_MAX_REPORT	= 16
};

/**
 * Enumerate hid keyboards.
 *
 * @param[out]	handle	Hid handle.
 * @param[int]	port?	Use 1.
 */
int sceHidKeyboardEnumerate(int* handle, int port);


/**
 * Get hid keyboard reports.
 *
 * @param[in]	handle		Hid handle.
 * @param[in]	reports		Buffer to receive reports.
 * @param[in]	nReports	Number of reports to receive.
 */
int sceHidKeyboardRead(SceUInt32 handle, SceHidKeyboardReport *reports[], int nReports);

#ifdef __cplusplus
}
#endif

#endif

