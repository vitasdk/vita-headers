/**
 * \kernelgroup{SceLcd}
 * \usage{psp2kern/lcd.h,SceLcdForDriver_stub}
 */

#ifndef _PSP2KERN_LCD_H_
#define _PSP2KERN_LCD_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** LCD driver error codes observed on FW 3.60. */
typedef enum SceLcdErrorCode {
	SCE_LCD_ERROR_INVALID_ARGUMENT      = 0x803F0C02,
	SCE_LCD_ERROR_INITIALIZATION_FAILED = 0x803F0C03,
	SCE_LCD_ERROR_NOT_READY             = 0x803F0C04,
	SCE_LCD_ERROR_INVALID_STATE         = 0x803F0C05
} SceLcdErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, SceLcdErrorCode); // size is from FW 3.60

/** LCD color-space modes. Their effects on the image are unknown. */
typedef enum SceLcdColorSpaceMode {
	SCE_LCD_COLOR_SPACE_MODE_0 = 0,
	SCE_LCD_COLOR_SPACE_MODE_1 = 1
} SceLcdColorSpaceMode;
VITASDK_BUILD_ASSERT_EQ(1, SceLcdColorSpaceMode); // size is from FW 3.60

/**
 * Queue the LCD display-off sequence.
 *
 * The sequence sends DCS display-off command 0x28, waits 128 ms, sends
 * sleep-in command 0x10, and waits 96 ms. The cached brightness and target
 * backlight level are set to 0. If the backlight controller is initialized,
 * an update is also queued for its worker. Errors from individual SPI commands
 * are not returned.
 *
 * @return 0 on success, ::SCE_LCD_ERROR_INVALID_STATE if another command
 *         sequence is pending, or an error from the backlight work queue.
 */
int ksceLcdDisplayOff(void);

/**
 * Queue the LCD display-on sequence.
 *
 * The common sequence waits 64 ms, sends DCS sleep-out command 0x11, waits
 * 208 ms, sends panel-specific setup and the cached color-space commands,
 * sends display-on command 0x29, and waits 16 ms. One panel-data path also
 * waits 64 ms immediately before the cached mode commands. It does not restore
 * the cached brightness. Errors from individual SPI commands are not returned.
 *
 * @return 0 on success, or ::SCE_LCD_ERROR_INVALID_STATE if another command
 *         sequence is pending.
 */
int ksceLcdDisplayOn(void);

/** Get the exact wide-brightness value most recently accepted by the driver. */
SceUInt32 ksceLcdGetBrightness(void);

/**
 * Get the Device Descriptor Block values cached during LCD initialization.
 *
 * Initialization reads five bytes with MIPI DSI command 0xA1. It accepts a
 * reply only when the fifth byte is 0xFF and the first 16-bit value is zero.
 * Either output pointer may be NULL.
 *
 * @param[out] supplier_id - Receives the first 16-bit DDB value when non-NULL.
 * @param[out] supplier_elective_data - Receives the second 16-bit DDB value when
 *                                     non-NULL. This value selects a panel
 *                                     display-on command sequence on FW 3.60.
 *
 * @return 0 on success, ::SCE_LCD_ERROR_NOT_READY while initialization is
 *         pending, or ::SCE_LCD_ERROR_INITIALIZATION_FAILED after a failed
 *         panel probe.
 */
int ksceLcdGetDDB(SceUInt16 *supplier_id, SceUInt16 *supplier_elective_data);

/** Get the cached LCD color-space mode. */
SceLcdColorSpaceMode ksceLcdGetDisplayColorSpaceMode(void);

/**
 * Set the wide LCD brightness (0 through 0x10000).
 *
 * Valid values range from 0 through 0x10000. Zero queues the display-off
 * sequence when the panel is on. A nonzero value queues the display-on
 * sequence when the panel is off. A value of 1 maps to backlight level 0x19.
 * Values from 2 through 0x10000 map to one of 17 table entries ranging from
 * 0x1F through 0xFF, while the exact requested value remains available through
 * ::ksceLcdGetBrightness.
 *
 * Once initialized, the backlight controller is updated through I2C register
 * 0x05. Changing from off to on also writes 1 to register 0x0E; changing from
 * on to off writes 0. Errors from individual SPI and I2C commands are not returned.
 *
 * @param[in] brightness - Wide brightness from 0 through 0x10000.
 *
 * @return 0 on success, ::SCE_LCD_ERROR_INVALID_ARGUMENT for a larger value,
 *         ::SCE_LCD_ERROR_INVALID_STATE if another panel command sequence is
 *         pending, or an error from the backlight work queue.
 */
int ksceLcdSetBrightness(SceUInt32 brightness);

/**
 * Set the LCD color-space mode.
 *
 * If the panel is off, the new mode is cached without sending a command. If it
 * is on, the driver sends vendor commands B0 04, C9 00/01, and B0 03. Their
 * effect on the image is unknown. Errors from individual SPI commands are not
 * returned.
 *
 * @param[in] mode - One of ::SceLcdColorSpaceMode.
 *
 * @return 0 on success, ::SCE_LCD_ERROR_INVALID_ARGUMENT for an unsupported
 *         mode, or ::SCE_LCD_ERROR_INVALID_STATE if another command sequence
 *         is pending.
 */
int ksceLcdSetDisplayColorSpaceMode(SceLcdColorSpaceMode mode);

/**
 * Wait until the asynchronous LCD initialization attempt has completed.
 *
 * This function busy-waits without a timeout and returns 0 for both successful
 * and failed initialization. Call ::ksceLcdGetDDB to check whether it succeeded.
 *
 * @return 0 after initialization succeeds or fails.
 */
int ksceLcdWaitReady(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LCD_H_ */
