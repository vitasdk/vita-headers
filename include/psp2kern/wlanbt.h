/**
 * \kernelgroup{SceWlanBt}
 * \usage{psp2kern/wlanbt.h,SceWlanBtForDriver_stub}
 */

#ifndef _PSP2KERN_WLANBT_H_
#define _PSP2KERN_WLANBT_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Commands accepted by ::ksceWlanBtSetConfiguration.
 *
 * Pass one command; do not combine commands with `|`. The WLAN and Bluetooth
 * drivers must coordinate before and after reloading their shared Marvell
 * Robin firmware. The retention commands select which Robin function is
 * restored across the shared device power-state transition.
 */
typedef enum SceWlanBtConfig {
	SCE_WLANBT_CONFIG_INITIALIZE           = 1,  //!< Initialize the shared Robin WLAN/Bluetooth firmware.
	SCE_WLANBT_CONFIG_SHUTDOWN             = 2,  //!< Shut down the shared Robin device and clear its state.
	SCE_WLANBT_CONFIG_WLAN_ENABLE          = 3,  //!< Enable the WLAN function.
	SCE_WLANBT_CONFIG_WLAN_DISABLE         = 4,  //!< Disable the WLAN function.
	SCE_WLANBT_CONFIG_BT_ENABLE            = 5,  //!< Enable the Bluetooth function.
	SCE_WLANBT_CONFIG_BT_DISABLE           = 6,  //!< Disable the Bluetooth function.
	SCE_WLANBT_CONFIG_WLAN_RELOAD_BEGIN    = 7,  //!< Mark WLAN ready to reload the shared firmware.
	SCE_WLANBT_CONFIG_WLAN_RELOAD_COMPLETE = 8,  //!< Mark WLAN reinitialization complete.
	SCE_WLANBT_CONFIG_BT_RELOAD_BEGIN      = 10, //!< Mark Bluetooth ready to reload the shared firmware.
	SCE_WLANBT_CONFIG_BT_RELOAD_COMPLETE   = 11, //!< Mark Bluetooth reinitialization complete.
	SCE_WLANBT_CONFIG_WLAN_RETAIN          = 13, //!< Retain WLAN across a shared-device power transition.
	SCE_WLANBT_CONFIG_WLAN_RELEASE         = 14, //!< Release WLAN before a shared-device power transition.
	SCE_WLANBT_CONFIG_BT_RETAIN            = 15, //!< Retain Bluetooth across a shared-device power transition.
	SCE_WLANBT_CONFIG_BT_RELEASE           = 16, //!< Release Bluetooth before a shared-device power transition.
	SCE_WLANBT_CONFIG_WLAN_FORCE_OFF       = 17, //!< Force the shared device off on behalf of WLAN.
	SCE_WLANBT_CONFIG_BT_FORCE_OFF         = 18  //!< Force the shared device off on behalf of Bluetooth.
} SceWlanBtConfig;

/**
 * Configure the shared WLAN/Bluetooth device.
 *
 * The WLAN and Bluetooth functions share one Marvell Robin device and firmware
 * image. The two drivers must coordinate commands 7/10 and 8/11. On FW 3.60,
 * unimplemented commands, including 0, 9, and 12, do nothing and return success.
 *
 * @param[in] config - Configuration command.
 *
 * @return 0 on success, 0x80418004 in Syscon downloader mode, 0x80418007
 *         when a Bluetooth enable or disable command is issued while the
 *         module reports WLAN/Bluetooth unavailable, or an initialization
 *         error from commands that start the shared firmware.
 */
int ksceWlanBtSetConfiguration(SceWlanBtConfig config);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_WLANBT_H_ */
