/**
 * \usergroup{SceSblRtcMgr}
 * \usage{psp2/sblrtcmgr.h,SceSblRtcMgr_stub}
 */

#ifndef _PSP2_SBLRTCMGR_H_
#define _PSP2_SBLRTCMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the CP activation key from the activation data managed by the service.
 *
 * The calling process must be a system program.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpActivationKey(void);

/**
 * Set the 32-bit CP physical RTC value and corresponding key.
 *
 * The calling process must be a system program, and manufacturing mode is
 * required. FW 3.60 accepts values from 1262314800 through 2145927600 inclusive.
 *
 * @param[in] rtc - New physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpRtcPhysicalAndKey(int rtc);

/**
 * Get the CP serial identifier.
 *
 * The calling process must be a system program, and manufacturing mode is
 * required.
 *
 * @param[out] serial_id - Receives exactly 0x80 bytes.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrGetCpSerialId(void *serial_id);

/**
 * Set the 32-bit CP physical RTC value.
 *
 * The calling process must be a system program, and manufacturing mode is
 * required. FW 3.60 accepts values from 1262314800 through 2145927600 inclusive.
 *
 * @param[in] rtc - New physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpRtcPhysicalForUser(int rtc);

/**
 * Get the 32-bit CP physical RTC value.
 *
 * The calling process must be a system program, and manufacturing mode is
 * required.
 *
 * @param[out] rtc - Receives the physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrGetCpRtcPhysicalForUser(int *rtc);

/**
 * Request a new 32-bit CP logical RTC value.
 *
 * The calling process must be a system program. FW 3.60 treats \a rtc as an
 * unsigned 32-bit value and checks that it is from 946652400 through
 * 4102412399. It does not change the RTC, even when the value is valid.
 *
 * @param[in] rtc - Requested logical RTC value.
 *
 * @return 0x800F1025 for a valid value on FW 3.60.
 */
int sceSblRtcMgrSetCpRtcLogical(int rtc);

/**
 * Get the 32-bit CP logical RTC value.
 *
 * The calling process must be a system program.
 *
 * @param[out] rtc - Receives the logical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrGetCpRtcLogical(int *rtc);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SBLRTCMGR_H_ */
