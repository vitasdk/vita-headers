/**
 * \kernelgroup{SceSyscon}
 * \usage{psp2kern/syscon.h,SceSysconForDriver_stub}
 */

#ifndef _PSP2KERN_SYSCON_H_
#define _PSP2KERN_SYSCON_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_SYSCON_PACKET_TX_CMD_LO	0
#define SCE_SYSCON_PACKET_TX_CMD_HI	1
#define SCE_SYSCON_PACKET_TX_LENGTH	2
#define SCE_SYSCON_PACKET_TX_DATA(i)	(3 + (i))

#define SCE_SYSCON_PACKET_RX_STATUS_LO	0
#define SCE_SYSCON_PACKET_RX_STATUS_HI	1
#define SCE_SYSCON_PACKET_RX_LENGTH	2
#define SCE_SYSCON_PACKET_RX_RESULT	3
#define SCE_SYSCON_PACKET_RX_DATA(i)	(4 + (i))

typedef enum SceSysconCmd {
	SCE_SYSCON_CMD_RESET_DEVICE = 0x0C
} SceSysconCmd;

typedef enum SceSysconResetType {
	SCE_SYSCON_RESET_TYPE_POWEROFF		= 0x00,
	SCE_SYSCON_RESET_TYPE_SUSPEND		= 0x01,
	SCE_SYSCON_RESET_TYPE_COLD_RESET	= 0x02,
	SCE_SYSCON_RESET_TYPE_SOFT_RESET	= 0x11
} SceSysconResetType;

typedef struct SceSysconPacket {
	struct SceSysconPacket *next;
	unsigned int status;
	SceUID semaId;
	unsigned int unk;
	unsigned char tx[32];
	unsigned char rx[32];
	unsigned int unk1[4];
	int (*callback)(struct SceSysconPacket *packet, void *argp);
	void *argp;
	unsigned int time;
	unsigned int unk2[5];
} SceSysconPacket; /* size 0x80 */

/** A set of debug handlers for syscon, that you can set in ksceSysconSetDebugHandlers(). */
typedef struct SceSysconDebugHandlers {
	/** Structure size (probably, unused). */
	int size;
	/** Callback ran right before running a packet, with a pointer to it passed as the first argument. */
	void (*start)(SceSysconPacket *packet);
	/** Callback ran right after finishing running a packet, with a pointer to it passed as the first argument. */
	void (*end)(SceSysconPacket *packet);
} SceSysconDebugHandlers;

typedef int (*SceSysconCmdExecAsyncCallback)(SceSysconPacket *packet, void *argp);

typedef void (*SceSysconCallback)(int enable, void *argp);

/**
 * Waits until the syscon is initialized.
 *
 * @return 0 on success.
 */
int ksceSysconWaitInitialized(void);

/**
 * Execute synchronously a syscon packet.
 *
 * @param packet The packet to execute. Its tx member needs to be initialized.
 * @param flags The packet flags. Check SceSysconPacketFlags.
 *
 * @return 0 on success.
 */
int ksceSysconCmdExec(SceSysconPacket *packet, unsigned int flags);

/**
 * Execute asynchronously a syscon packet.
 *
 * @param packet The packet to execute. Its tx member needs to be initialized.
 * @param flags The packet flags. Check SceSysconPacketFlags.
 * @param callback The packet callback. Check the callback member of SceSysconPacket.
 * @param argp The second argument that will be passed to the callback when executed.
 *
 * @return 0 on success.
 */
int ksceSysconCmdExecAsync(SceSysconPacket *packet, unsigned int flags, SceSysconCmdExecAsyncCallback cb, void *argp);

/**
 * Wait for the currently queued syscon packets to be executed, or check if any are in the queue.
 *
 * @param packet The packet you want to check or wait for, or NULL if you want to check or wait for all the currently running packets.
 * @param noWait Set to 1 if you just want to check the packet status, or 0 if you want the function to return only when the packet queue is empty.
 *
 * @return 1 if packets are still running (and noWait was set to 1), 0 on success, < 0 otherwise.
 */
int ksceSysconCmdSync(SceSysconPacket *packet, int noWait);

/**
 * Reset the device.
 *
 * @param type The reset type value, one of SceSysconResetType.
 * @param mode The resetting mode (?).
 *
 * @return 0 on success.
 */
int ksceSysconSetPowerMode(int type, int mode);

int ksceSysconReadCommand(unsigned short cmd, void *buffer, SceSize size);
int ksceSysconSendCommand(unsigned short cmd, const void *buffer, SceSize size);

/**
 * Set the debug handlers.
 *
 * @return 0.
 */
int ksceSysconSetDebugHandlers(const SceSysconDebugHandlers *handlers);

/**
 * Turn a LED on or off.
 *
 * @param led The LED id.
 * @param enable Set this value to 1 if you want the LED to turn on, or 0 if you want it to turn off.
 *
 * @return 0 on success.
 */
int ksceSysconCtrlLED(int led, int enable);

/**
 * Set the memory stick power.
 *
 * @param power The new power value.
 *
 * @return 0 on success.
 */
int ksceSysconCtrlRMRPower(int power);

/**
 * Set the SD power.
 *
 * @param power The new power value.
 *
 * @return 0 on success.
 */
int ksceSysconCtrlSdPower(int power);

/**
 * Set the ADV7533 HDMI CEC power.
 *
 * @param power The new power value.
 *
 * @return 0 on success.
 */
int ksceSysconCtrlHdmiCecPower(int power);

int ksceSysconCtrlManualChargeMode(int);

int ksceSysconEnableHibernateIO(int);

int ksceSysconIduModeClear(void);
int ksceSysconIduModeSet(void);
int ksceSysconIsDownLoaderMode(void);

int ksceSysconLogStart(void);
int ksceSysconLogStartWaiting(void);
int ksceSysconLogReadData(unsigned short, void *buff, SceSize size);

int ksceSysconShowModeClear(void);
int ksceSysconShowModeSet(void);

/**
 * Get the baryon version.
 *
 * @return The baryon version.
 */
int ksceSysconGetBaryonVersion(void);

/**
 * Get the baryon timestamp.
 *
 * @return The baryon timestamp.
 */
unsigned long long ksceSysconGetBaryonTimestamp();

int ksceSysconGetBatteryCalibData(int *, int *, int *, int *);
int ksceSysconGetHardwareInfo(void);
int ksceSysconGetHardwareInfo2(int *, int *, int *);
int ksceSysconGetLogInfo(int *);
int ksceSysconGetManualChargeMode(int *);
int ksceSysconGetManufacturesStatus(int *);
int ksceSysconGetTemperatureLog(int *);
int ksceSysconGetUsbDetStatus(int *);

int ksceSysconClearTemperatureLog(int);

int ksceSysconBeginConfigstorageTransaction(void);
int ksceSysconCommitConfigstorageTransaction(void);
int ksceSysconEndConfigstorageTransaction(void);
int ksceSysconLoadConfigstorageScript(unsigned short, const void *buff, SceSize size);
int ksceSysconVerifyConfigstorageScript(unsigned short, const void *buff, SceSize size);

/**
 * Set the alarm callback, that will be ran when the alarm timer is passed.
 *
 * @param callback The callback function.
 * @param argp The second argument that will be passed to the callback.
 *
 * @return 0.
 */
int ksceSysconSetAlarmCallback(SceSysconCallback callback, void *argp);

/**
 * Set the low battery callback, that will be ran when the battery is low.
 *
 * @param callback The callback function.
 * @param argp The second argument that will be passed to the callback.
 *
 * @return 0.
 */
int ksceSysconSetLowBatteryCallback(SceSysconCallback callback, void *argp);

/**
 * Set the thermal alert callback, that will be ran when the temperature reaches a critical point.
 *
 * @param callback The callback function.
 * @param argp The second argument that will be passed to the callback.
 *
 * @return 0.
 */
int ksceSysconSetThermalAlertCallback(SceSysconCallback callback, void *argp);

typedef enum SceSysconControl {
	SCE_SYSCON_CTRL_UP        = 0x1,
	SCE_SYSCON_CTRL_RIGHT     = 0x2,
	SCE_SYSCON_CTRL_DOWN      = 0x4,
	SCE_SYSCON_CTRL_LEFT      = 0x8,
	SCE_SYSCON_CTRL_TRIANGLE  = 0x10,
	SCE_SYSCON_CTRL_CIRCLE    = 0x20,
	SCE_SYSCON_CTRL_CROSS     = 0x40,
	SCE_SYSCON_CTRL_SQUARE    = 0x80,
	SCE_SYSCON_CTRL_SELECT    = 0x100,
	SCE_SYSCON_CTRL_LTRIGGER  = 0x200,
	SCE_SYSCON_CTRL_RTRIGGER  = 0x400,
	SCE_SYSCON_CTRL_START     = 0x800,
	SCE_SYSCON_CTRL_PSBUTTON  = 0x1000,
	SCE_SYSCON_CTRL_POWER     = 0x4000,
	SCE_SYSCON_CTRL_VOLUP     = 0x10000,
	SCE_SYSCON_CTRL_VOLDOWN   = 0x20000,
	SCE_SYSCON_CTRL_HEADPHONE = 0x8000000
} SceSysconControl;

/**
 * Get physics button control info
 *
 * @param[out] ctrl - The pointer of physics button control info output
 *
 * @return 0 on success.
 */
int ksceSysconGetControlsInfo(SceUInt32 *ctrl);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_SYSCON_H_ */

