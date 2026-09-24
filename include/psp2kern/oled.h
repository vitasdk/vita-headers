/**
 * \kernelgroup{SceOled}
 * \usage{psp2kern/oled.h,SceOledForDriver_stub}
 */

#ifndef _PSP2KERN_OLED_H_
#define _PSP2KERN_OLED_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** OLED driver error codes observed on FW 3.60. */
typedef enum SceOledErrorCode {
	SCE_OLED_ERROR_INVALID_ARGUMENT      = 0x803F0A02,
	SCE_OLED_ERROR_INITIALIZATION_FAILED = 0x803F0A03,
	SCE_OLED_ERROR_NOT_READY             = 0x803F0A04,
	SCE_OLED_ERROR_INVALID_STATE         = 0x803F0A05
} SceOledErrorCode;
VITASDK_BUILD_ASSERT_EQ(4, SceOledErrorCode); // size is from FW 3.60

/** OLED color-space modes. Their visual effects are unknown. */
typedef enum SceOledColorSpaceMode {
	SCE_OLED_COLOR_SPACE_MODE_0 = 0,
	SCE_OLED_COLOR_SPACE_MODE_1 = 1
} SceOledColorSpaceMode;
VITASDK_BUILD_ASSERT_EQ(1, SceOledColorSpaceMode); // size is from FW 3.60

/**
 * Queue the OLED display-off sequence.
 *
 * The sequence sends DCS display-off command 0x28, waits 16 ms, sends sleep-in
 * command 0x10, and waits 96 ms. The cached brightness is set to 0.
 * SPI and initialization errors from individual commands are not returned
 * to the caller.
 *
 * @return 0 on success, or ::SCE_OLED_ERROR_INVALID_STATE if another command
 *         sequence is pending.
 */
int ksceOledDisplayOff(void);

/**
 * Queue the OLED display-on sequence.
 *
 * The sequence waits 64 ms, sends DCS sleep-out command 0x11, waits 208 ms,
 * sends display-on command 0x29, and waits 16 ms. It does not restore the
 * cached brightness. SPI and initialization errors from individual commands
 * are not returned to the caller.
 *
 * @return 0 on success, or ::SCE_OLED_ERROR_INVALID_STATE if another command
 *         sequence is pending.
 */
int ksceOledDisplayOn(void);

/** Get the exact wide-brightness value most recently accepted by the driver. */
SceUInt32 ksceOledGetBrightness(void);

/**
 * Get the Device Descriptor Block values cached during OLED initialization.
 *
 * Initialization reads five bytes with MIPI DSI command 0xA1. Either output
 * pointer may be NULL.
 *
 * @param[out] supplier_id - Receives the first 16-bit DDB value when non-NULL.
 * @param[out] supplier_elective_data - Receives the second 16-bit DDB value when
 *                                     non-NULL. Its low byte selects the panel
 *                                     calibration table on FW 3.60.
 *
 * @return 0 on success, ::SCE_OLED_ERROR_NOT_READY while initialization is
 *         pending, or ::SCE_OLED_ERROR_INITIALIZATION_FAILED after a failed
 *         panel probe.
 */
int ksceOledGetDDB(SceUInt16 *supplier_id, SceUInt16 *supplier_elective_data);

/** Get the cached OLED color-space mode. */
SceOledColorSpaceMode ksceOledGetDisplayColorSpaceMode(void);

/**
 * Set the wide OLED brightness.
 *
 * Valid values range from 0 through 0x10000. Zero queues the display-off
 * sequence. One selects a special dimmed calibration. Values from 2 through
 * 0x10000 map to one of 16 panel-calibrated hardware levels. The exact
 * requested value remains available through ::ksceOledGetBrightness.
 * Changing from zero to a nonzero value appends the display-on sequence.
 * SPI and initialization errors from individual commands are not returned
 * to the caller.
 *
 * @param[in] brightness - Wide brightness from 0 through 0x10000.
 *
 * @return 0 on success, ::SCE_OLED_ERROR_INVALID_STATE when the panel
 *         calibration is unavailable or another sequence is pending, or
 *         ::SCE_OLED_ERROR_INVALID_ARGUMENT for a value greater than 0x10000
 *         after calibration is available.
 */
int ksceOledSetBrightness(SceUInt32 brightness);

/**
 * Set the OLED color-space mode.
 *
 * If brightness is zero, the new mode is cached without sending a command.
 * Otherwise the driver sends DCS command 0xB3 with the selected mode. Before
 * panel calibration has been installed, the function returns success without
 * changing the cached mode. SPI and initialization errors from individual
 * commands are not returned to the caller.
 *
 * @param[in] mode - One of ::SceOledColorSpaceMode.
 *
 * @return 0 on success, ::SCE_OLED_ERROR_INVALID_ARGUMENT for an unsupported
 *         mode, or ::SCE_OLED_ERROR_INVALID_STATE if brightness is nonzero
 *         and another sequence is pending.
 */
int ksceOledSetDisplayColorSpaceMode(SceOledColorSpaceMode mode);

/**
 * Wait until the asynchronous OLED initialization attempt has completed.
 *
 * This function busy-waits and returns 0 for both successful and failed
 * initialization. Call ::ksceOledGetDDB to check whether initialization succeeded.
 *
 * @return 0 once initialization is no longer pending, whether it succeeded
 *         or failed.
 */
int ksceOledWaitReady(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_OLED_H_ */
