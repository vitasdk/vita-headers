/**
 * \kernelgroup{SceTouch}
 * \usage{psp2common/touch.h}
 */

#ifndef _PSP2COMMON_TOUCH_H_
#define _PSP2COMMON_TOUCH_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Cached touch-panel identity and firmware information.
 *
 * On FW 3.60, the extended Syscon record supplies the first eight bytes. The
 * legacy path supplies the vendor and firmware revisions, obtains the
 * configuration revision separately when supported, and leaves the hardware
 * version and vendor information at zero. The public and kernel getters always
 * set ::SceTouchDeviceInfo::reserved to zero.
 */
typedef struct SceTouchDeviceInfo {
	SceUInt16 vendor_id;       //!< Touch-controller vendor ID.
	SceUInt16 firmware_rev;    //!< Controller firmware revision.
	SceUInt16 config_rev;      //!< Controller configuration revision.
	SceUInt8 hw_version;       //!< Hardware version used for firmware compatibility.
	SceUInt8 vendor_info;      //!< Vendor-specific value used for firmware compatibility.
	SceUInt8 reserved[4];     //!< Set to zero on FW 3.60.
} SceTouchDeviceInfo;
VITASDK_BUILD_ASSERT_EQ(0xC, SceTouchDeviceInfo); // size is from FW 3.60

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_TOUCH_H_ */
