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
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpActivationKey(void);

/**
 * Set the 32-bit CP physical RTC value and corresponding key.
 *
 * @param[in] rtc - New physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpRtcPhysicalAndKey(int rtc);

/**
 * Get the CP serial identifier.
 *
 * @param[out] serial_id - Receives exactly 0x80 bytes.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrGetCpSerialId(void *serial_id);

/**
 * Set the 32-bit CP physical RTC value.
 *
 * @param[in] rtc - New physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrSetCpRtcPhysicalForUser(int rtc);

/**
 * Get the 32-bit CP physical RTC value.
 *
 * @param[out] rtc - Receives the physical RTC value.
 *
 * @return SCE_OK on success, < 0 on error.
 */
int sceSblRtcMgrGetCpRtcPhysicalForUser(int *rtc);

/**
 * Set the 32-bit CP logical RTC value.
 *
 * @param[in] rtc - New logical RTC value.
 *
 * @note FW 3.60 validates the value but does not set the RTC; it returns
 * 0x800F1025 for a valid value.
 */
int sceSblRtcMgrSetCpRtcLogical(int rtc);

/**
 * Get the 32-bit CP logical RTC value.
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
