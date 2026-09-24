/**
 * \kernelgroup{SceSyscon}
 * \usage{psp2kern/kernel/syscon.h,SceSysconForDriver_stub}
 */

#ifndef _PSP2KERN_SYSCON_H_
#define _PSP2KERN_SYSCON_H_

#include <vitasdk/build_utils.h>
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
} SceSysconPacket;
VITASDK_BUILD_ASSERT_EQ(0x80, SceSysconPacket);

/** A set of debug handlers for syscon, that you can set in ksceSysconSetDebugHandlers(). */
typedef struct SceSysconDebugHandlers {
	/** Structure size (probably, unused). */
	int size;
	/** Callback ran right before running a packet, with a pointer to it passed as the first argument. */
	void (*start)(SceSysconPacket *packet);
	/** Callback ran right after finishing running a packet, with a pointer to it passed as the first argument. */
	void (*end)(SceSysconPacket *packet);
} SceSysconDebugHandlers;
VITASDK_BUILD_ASSERT_EQ(0xC, SceSysconDebugHandlers);

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
 * @param cb The packet callback. Check the callback member of SceSysconPacket.
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

#define SCE_SYSCON_BATTERY_BL_MAX_TRANSFER_SIZE 0x10
#define SCE_SYSCON_NVS_SIZE                     0xB60
#define SCE_SYSCON_UPDATER_DIGEST_SIZE          0x14

/** Touch-panel vendor IDs and firmware revisions returned by ::ksceSysconGetTouchpanelDeviceInfo. */
typedef struct SceKernelTouchpanelDeviceInfo {
	SceUInt16 front_vendor_id;      //!< Front touch-panel vendor ID.
	SceUInt16 front_firmware_rev;   //!< Front touch-panel firmware revision.
	SceUInt16 rear_vendor_id;       //!< Rear touch-panel vendor ID.
	SceUInt16 rear_firmware_rev;    //!< Rear touch-panel firmware revision.
} SceKernelTouchpanelDeviceInfo;
VITASDK_BUILD_ASSERT_EQ(0x8, SceKernelTouchpanelDeviceInfo); // size is from FW 3.60

/**
 * Execute the current battery-bootloader command context.
 *
 * FW 3.60 uses Syscon command 0x09B3. On Baryon versions through 0x00070503
 * it uses the legacy command 0x08B3. SceSblUpdateMgr numbers script records
 * starting at 1 and uses each record's number as the command context.
 *
 * @param[in] command_context Battery-bootloader command context.
 *
 * @return 0 on success, or a negative Syscon error.
 */
int ksceSysconBatteryExecBLCommand(SceUInt16 command_context);

/**
 * Read data from a battery-bootloader command response.
 *
 * FW 3.60 uses Syscon command 0x09B4, or legacy command 0x08B4 on Baryon
 * versions through 0x00070503. The two request bytes are transmitted
 * independently and unmodified; their individual purposes are unknown.
 *
 * @param[in] command_context Battery-bootloader command context.
 * @param[in] request0 First raw request byte.
 * @param[in] request1 Second raw request byte.
 * @param[out] dst Required buffer that receives \a size bytes.
 * @param[in] size Number of bytes to read, from 1 through
 *                 ::SCE_SYSCON_BATTERY_BL_MAX_TRANSFER_SIZE.
 *
 * @return 0 on success, 0x80250001 for an invalid size, or a negative Syscon
 *         error.
 */
int ksceSysconBatteryReadBLCommand(SceUInt16 command_context, SceUInt8 request0, SceUInt8 request1, void *dst, SceUInt8 size);

/**
 * Request a battery-controller software reset.
 *
 * FW 3.60 uses Syscon command 0x0989. Baryon versions through 0x00070503 do
 * not support this operation and return 0x8025023F without sending a command.
 *
 * @return 0 on success, or a negative Syscon error.
 */
int ksceSysconBatterySWReset(void);

/**
 * Write one chunk of battery-bootloader command data.
 *
 * FW 3.60 uses Syscon command 0x09B2, or legacy command 0x08B2 on Baryon
 * versions through 0x00070503. SceSblUpdateMgr uses \a offset as the byte
 * offset of this chunk within the current script record.
 *
 * @param[in] command_context Battery-bootloader command context.
 * @param[in] offset Byte offset of the chunk within the command data.
 * @param[in] src Required source buffer.
 * @param[in] size Number of bytes to write, from 1 through
 *                 ::SCE_SYSCON_BATTERY_BL_MAX_TRANSFER_SIZE.
 *
 * @return 0 on success, 0x80250001 for an invalid size, or a negative Syscon
 *         error.
 */
int ksceSysconBatterySetBLCommand(SceUInt16 command_context, SceUInt8 offset, const void *src, SceUInt8 size);

/**
 * Enter battery-bootloader mode.
 *
 * Uses Syscon command 0x09B0, or legacy command 0x08B0 on Baryon versions
 * through 0x00070503.
 *
 * @return 0 on success, or a negative Syscon error.
 */
int ksceSysconBatteryStartBLMode(void);

/**
 * Leave battery-bootloader mode.
 *
 * Uses Syscon command 0x09B1, or legacy command 0x08B1 on Baryon versions
 * through 0x00070503.
 *
 * @return 0 on success, or a negative Syscon error.
 */
int ksceSysconBatteryStopBLMode(void);

/**
 * Control accessory-port power with Syscon command 0x0889.
 *
 * The low 16 bits are sent without validation. Observed FW 3.60 callers use
 * ::SCE_FALSE and ::SCE_TRUE.
 *
 * @param[in] enable Requested accessory-power state.
 *
 * @return 0 on success, or a negative Syscon/context error.
 */
int ksceSysconCtrlAccPower(SceBool enable);

/**
 * Control DevKit USB power with Syscon command 0x089C.
 *
 * The low 16 bits are sent without validation. Observed FW 3.60 callers use
 * ::SCE_FALSE and ::SCE_TRUE.
 *
 * @param[in] enable Requested DevKit USB-power state.
 *
 * @return 0 on success, or a negative Syscon/context error.
 */
int ksceSysconCtrlDevKitUsbPower(SceBool enable);

/**
 * Control PSTV/Dolce USB power with Syscon command 0x08C5.
 *
 * The low 16 bits are sent without validation. Observed FW 3.60 callers use
 * ::SCE_FALSE and ::SCE_TRUE.
 *
 * @param[in] enable Requested PSTV USB-power state.
 *
 * @return 0 on success, or a negative Syscon/context error.
 */
int ksceSysconCtrlDolceUsbPower(SceBool enable);

/**
 * Control host diagnostic output through the Jig dongle.
 *
 * Syscon command 0x00B2 receives the low 16 bits without validation. The
 * PostSs manager disables this output while it owns the Jig port and restores
 * it afterward on newer hardware.
 *
 * @param[in] enable Requested host-output state.
 *
 * @return 0 on success, or a negative Syscon/context error.
 */
int ksceSysconCtrlHostOutputViaDongle(SceBool enable);

/**
 * Get the battery hardware, firmware, and data-flash versions.
 *
 * Each output may be NULL. For each non-NULL output, FW 3.60 stores the
 * 16-bit response value in a 32-bit word with the upper 16 bits set to zero.
 * It uses command 0x0980, or legacy command 0x0882 on Baryon versions through
 * 0x00070503.
 *
 * @param[out] hardware_version Battery hardware version, or NULL.
 * @param[out] firmware_version Battery firmware version, or NULL.
 * @param[out] data_flash_version Battery data-flash version, or NULL.
 *
 * @return 0 on success, or a negative Syscon error.
 */
int ksceSysconGetBatteryVersion(SceUInt32 *hardware_version, SceUInt32 *firmware_version, SceUInt32 *data_flash_version);

/**
 * Get the cached raw Micro-USB connector information.
 *
 * Bits 8 through 15 contain the connector code. SceUsbServ treats code 0x02
 * as permitting USB device mode on FW 3.60.
 *
 * @param[out] info Optional output for the 32-bit information value.
 *
 * @return Always 0 on FW 3.60.
 */
int ksceSysconGetMicroUsbInfo(SceUInt32 *info);

/**
 * Get the cached multi-connector information, with the mappings below.
 *
 * Bits 8 through 15 contain the connector code. On hardware versions below
 * 0x00400000, FW 3.60 maps the raw codes 0x60, 0x51, 0x65, and 0x55 to 0x00,
 * 0x02, 0x04, and 0x05 respectively, and maps every other raw code to 0xFF.
 * A genuine PSTV receives code 0x00 regardless of the cached value.
 *
 * SceUsbServ treats codes 0x00 and 0x04 as permitting USB device mode on the
 * older multi-connector hardware. SceHpremote identifies code 0x03 as an
 * audio-output dock.
 *
 * @param[out] info Optional output for the 32-bit information value after mapping.
 *
 * @return Always 0 on FW 3.60.
 */
int ksceSysconGetMultiCnInfo(SceUInt32 *info);

/**
 * Get the front and rear touch-panel vendor IDs and firmware revisions.
 *
 * Uses Syscon command 0x0380.
 *
 * @param[out] info Required 8-byte output structure.
 *
 * @return 0 on success, 0x80250002 when \a info is NULL, or a negative Syscon
 *         error.
 */
int ksceSysconGetTouchpanelDeviceInfo(SceKernelTouchpanelDeviceInfo *info);

/**
 * Close the Jig port.
 *
 * FW 3.60 holds an internal mutex during the operation and uses Syscon
 * command 0x2081. Closing an already-closed port returns 0x80250001.
 *
 * @return 0 on success, or a negative state, mutex, or Syscon error.
 */
int ksceSysconJigClosePort(void);

/**
 * Open the Jig port.
 *
 * FW 3.60 holds an internal mutex during the operation and uses Syscon
 * command 0x2080. Opening an already-open port returns 0x80250001.
 *
 * @return 0 on success, or a negative state, mutex, or Syscon error.
 */
int ksceSysconJigOpenPort(void);

/**
 * Set the two raw Jig configuration bytes.
 *
 * The port must be open. Syscon command 0x2082 receives the two bytes followed
 * by two zero bytes. Their individual purposes are unknown; the only observed
 * FW 3.60 caller passes zero for both.
 *
 * @param[in] config0 First raw configuration byte.
 * @param[in] config1 Second raw configuration byte.
 *
 * @return 0 on success, 0x80250001 when the port is closed, or a negative
 *         mutex or Syscon error.
 */
int ksceSysconJigSetConfig(SceUInt8 config0, SceUInt8 config1);

/**
 * Read one aligned block from Syscon NVS.
 *
 * Uses Syscon command 0x1082. Valid transfer sizes are 1, 2, 4, 8, and 16
 * bytes. \a offset must be aligned to \a size, and the transfer must remain
 * within ::SCE_SYSCON_NVS_SIZE bytes.
 *
 * @param[in] offset Byte offset in NVS.
 * @param[out] buffer Required destination buffer.
 * @param[in] size Transfer size in bytes.
 *
 * @return 0 on success, 0x80250001 for an invalid size, alignment, or range,
 *         or a negative Syscon error.
 */
int ksceSysconNvsReadData(SceUInt32 offset, void *buffer, SceSize size);

/**
 * Set the Syscon NVS run mode.
 *
 * Syscon command 0x1080 receives the low 16 bits without validation. Observed
 * FW 3.60 callers pass zero before NVS reads and writes.
 *
 * @param[in] mode Raw NVS run-mode value.
 *
 * @return 0 on success, or a negative Syscon/context error.
 */
int ksceSysconNvsSetRunMode(int mode);

/**
 * Write one aligned block to Syscon NVS.
 *
 * Uses Syscon command 0x1083. Valid transfer sizes are 1, 2, 4, 8, and 16
 * bytes. \a offset must be aligned to \a size, and the transfer must remain
 * within ::SCE_SYSCON_NVS_SIZE bytes.
 *
 * @param[in] offset Byte offset in NVS.
 * @param[in] buffer Required source buffer.
 * @param[in] size Transfer size in bytes.
 *
 * @return 0 on success, 0x80250001 for an invalid size, alignment, or range,
 *         or a negative Syscon error.
 */
int ksceSysconNvsWriteData(SceUInt32 offset, const void *buffer, SceSize size);

/**
 * Select the multi-connector port routing with Syscon command 0x0190.
 *
 * Only the low 24 bits are transmitted and the value is not validated. The
 * PostSs manager uses 0 for Jig routing and 0x10000 for normal routing.
 *
 * @param[in] port Raw routing value.
 *
 * @return 0 on success, or a negative Syscon/context error.
 */
int ksceSysconSetMultiCnPort(int port);

/**
 * Calculate the checksum of a Syscon updater firmware segment.
 *
 * This function does not contact Syscon. It adds the unsigned bytes modulo
 * 2^32 and writes the bitwise complement of the sum to \a checksum.
 *
 * @param[in] segment Segment data. Must not be NULL.
 * @param[in] segment_size Number of bytes. Must not be zero.
 * @param[out] checksum Receives the complemented 32-bit byte sum. Must not be
 *                      NULL.
 *
 * @return 0 on success, or 0x80250001 for an invalid pointer or size.
 */
int ksceSysconUpdaterCalcChecksum(const void *segment, SceSize segment_size, SceUInt32 *checksum);

/**
 * Finalize Syscon firmware programming.
 *
 * Syscon command 0x1184 receives the 20-byte digest. SceSblUpdateMgr supplies
 * the digest from the type-0x20 updater record.
 *
 * @param[in] digest Digest data. Must not be NULL.
 * @param[in] size Digest size in bytes. Must be exactly ::SCE_SYSCON_UPDATER_DIGEST_SIZE.
 *
 * @return 0 on success, 0x80250001 for an invalid pointer or size, or a
 *         negative Syscon error.
 */
int ksceSysconUpdaterExecFinalize(const void *digest, SceSize size);

/**
 * Program the selected Syscon firmware segment.
 *
 * Syscon command 0x1182 receives the checksum produced by
 * ::ksceSysconUpdaterCalcChecksum.
 *
 * @param[in] checksum Complemented 32-bit segment checksum.
 *
 * @return 0 on success, or a negative Syscon error.
 */
int ksceSysconUpdaterExecProgramming(SceUInt32 checksum);

/**
 * Set the Syscon updater run mode.
 *
 * FW 3.60 accepts only 0x152E, 0x3665, 0x72BA, 0x9A54, and 0xC5E7. Command
 * 0x1183 receives the 16-bit value. SceSblUpdateMgr begins updates in modes 0,
 * 2, and 3 with 0x9A54, 0x3665, and 0xC5E7 respectively. It ends updates in
 * modes 2 and 3 with 0x72BA. It does not use 0x152E.
 *
 * @param[in] mode Updater run-mode value.
 *
 * @return 0 on success, 0x80250001 for any other value, or a negative Syscon
 *         error.
 */
int ksceSysconUpdaterSetRunMode(int mode);

/**
 * Select a Syscon updater firmware segment.
 *
 * Syscon command 0x1180 receives only the low eight bits of \a segment_no;
 * the value is not range-checked.
 *
 * @param[in] segment_no Segment number.
 *
 * @return 0 on success, or a negative Syscon error.
 */
int ksceSysconUpdaterSetSegment(SceUInt32 segment_no);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_SYSCON_H_ */
