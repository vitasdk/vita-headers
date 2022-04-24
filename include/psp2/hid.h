/**
 * \usergroup{SceHid}
 * \usage{psp2/hid.h,SceHid_stub}
 */


#ifndef _PSP2_HID_H_
#define _PSP2_HID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <psp2/types.h>

typedef struct SceHidKeyboardReport {
	SceUInt8 reserved;
	SceUInt8 modifiers[2]; //modifiers[0] Standard modifiers Ctrl Shift Alt, modifiers[1] Caps Lock, ..?
	SceUInt8 keycodes[6];
	SceUInt8 unk1[15];
} SceHidKeyboardReport;

typedef struct SceHidMouseReport {
	SceUInt8 buttons;
	SceUInt8 reserved;
	SceInt16 rel_x;
	SceInt16 rel_y;
	SceInt8 unk[10];
} SceHidMouseReport;

#define SCE_HID_MAX_REPORT 16
#define SCE_HID_MAX_DEVICE_COUNT 8

/**
 * Enumerate hid keyboards.
 *
 * @param[out]	handle	Buffer to receive keyboard hid handles.
 * @param[int]	count   Number of keyboards to enumerate
 */
int sceHidKeyboardEnumerate(int* handle, int count);


/**
 * Get hid keyboard reports.
 *
 * @param[in]	handle		Hid handle.
 * @param[in]	reports		Buffer to receive reports.
 * @param[in]	nReports	Number of reports to receive.
 */
int sceHidKeyboardRead(SceUInt32 handle, SceHidKeyboardReport *reports[], int nReports);

/**
 * Enumerate hid mice.
 *
 * @param[out]	handle	Buffer to receive mouse hid handles.
 * @param[int]	count   Number of mice to enumerate
 */
int sceHidMouseEnumerate(int* handle, int count);


/**
 * Get hid mouse reports.
 *
 * @param[in]	handle		Hid handle.
 * @param[in]	reports		Buffer to receive reports.
 * @param[in]	nReports	Number of reports to receive.
 */
int sceHidMouseRead(SceUInt32 handle, SceHidMouseReport *reports[], int nReports);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_HID_H_ */

