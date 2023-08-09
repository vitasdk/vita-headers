/**
 * \usergroup{SceUsbd}
 * \usage{psp2/usbd.h,SceUsbd_stub}
 */


#ifndef _PSP2_USBD_H_
#define _PSP2_USBD_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/usbd.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceUsbdDeviceInfo {
	unsigned int port;
	unsigned int device_num;
	unsigned int unk3; // handled? 0, 1, 2
} SceUsbdDeviceInfo;
VITASDK_BUILD_ASSERT_EQ(0xC, SceUsbdDeviceInfo);

typedef struct SceUsbdTransferData {
	unsigned int pipe; // 0x00
	const void *data; // 0x04
	unsigned int data_size;  // 0x08
	void *transferred; //  // 0x0C // ptr to 8 bytes?
	unsigned int timeout;  // 0x10 // size of above ptr? only 8 allowed?
} SceUsbdTransferData;
VITASDK_BUILD_ASSERT_EQ(0x14, SceUsbdTransferData);

typedef struct SceUsbdReceiveEvent {
	unsigned int unk0; // 0
	unsigned int unk1; // next ptr?
	unsigned int unk2; // != 8, set to 1, 2, 4? // transfer flags? type?
	unsigned int unk3;
	unsigned int unk4;
	unsigned int unk5;
	unsigned int transfer_id;
} SceUsbdReceiveEvent;
VITASDK_BUILD_ASSERT_EQ(0x1C, SceUsbdReceiveEvent);

#define USB_DESCRIPTOR_DEVICE                   0x01    // bDescriptorType for a Device Descriptor.
#define USB_DESCRIPTOR_CONFIGURATION            0x02    // bDescriptorType for a Configuration Descriptor.
#define USB_DESCRIPTOR_STRING                   0x03    // bDescriptorType for a String Descriptor.
#define USB_DESCRIPTOR_INTERFACE                0x04    // bDescriptorType for an Interface Descriptor.
#define USB_DESCRIPTOR_ENDPOINT                 0x05    // bDescriptorType for an Endpoint Descriptor.

#define USB_DESCRIPTOR_DEVICE_QUALIFIER         0x06    // bDescriptorType for a Device Qualifier.
#define USB_DESCRIPTOR_OTHER_SPEED              0x07    // bDescriptorType for a Other Speed Configuration.
#define USB_DESCRIPTOR_INTERFACE_POWER          0x08    // bDescriptorType for Interface Power.
#define USB_DESCRIPTOR_OTG                      0x09    // bDescriptorType for an OTG Descriptor.

/**
 * Init usb subsystem
 *
 * @return 0 on success, < 0 on error
 *
 * @param[out] uid Pointer to uid
 *
 */
int sceUsbdInit(SceUID *uid);

/**
 * Stop usb subsystem
 *
 * @return 0 on success, < 0 on error
 *
 * @param uid uid
 *
 */
int sceUsbdEnd(SceUID uid);

/**
 * Get usb devices list
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] num max number of devices to return (8 max)
 * @param[out] info pointer to receive device info
 *
 */
int sceUsbdGetDeviceList(SceUID uid, SceSize num, SceUsbdDeviceInfo *info); // 8 devices max


/**
 * Get usb device descriptors data size
 *
 * @return size on success, < 0 on error
 *
 * @param uid uid
 * @param device_id device id
 *
 */
int sceUsbdGetDescriptorSize(SceUID uid, unsigned int device_id);

/**
 * Get usb device descriptors (all)
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] device_id device id
 * @param[out] descriptor buffer for descriptor data
 * @param[in] size buffer size
 *
 */
int sceUsbdGetDescriptor(SceUID uid, SceUID device_id, unsigned char *descriptor, SceSize size);


/**
 * Get usb device speed
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] device_id device id
 * @param[out] speed device speed
 *
 */
int sceUsbdGetDeviceSpeed(SceUID uid, SceUID device_id, unsigned int *speed);
#define SCE_USBD_DEVICE_SPEED_LS   (0)
#define SCE_USBD_DEVICE_SPEED_FS   (1)
#define SCE_USBD_DEVICE_SPEED_HS   (2)

/**
 * Register callback to usb event
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] cbid callback uid
 * @param[in] flag if 1 - trigger events immediately
 *
 * @note there may be only one callback registered through whole system.
 *       And it's currently taken up by shell.
 *
 */
int sceUsbdRegisterCallback(SceUID cbid, int flag);

/**
 * Remove callback to usb event
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] cbid callback uid
 *
 * @note this checks process id
 *
 */
int sceUsbdUnregisterCallback(SceUID cbid);

/**
 * Reset usb device
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] device_id device id
 *
 */
int sceUsbdResetDevice(SceUID uid, SceUID device_id);

/**
 * Attach specified driver to device
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] driver_id driver id (result of Register(Composite)Ldd)
 * @param[in] bus usb port number
 * @param[in] device usb device number
 *
 * @note device_id = (bus << 16) + device
 */
int sceUsbdAttach(SceUID uid, SceUID driver_id, SceUInt bus, SceUInt device);

/**
 * Get device address
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] device_id device id
 * @param[out] addr buffer for return value
 *
 * @note it is unknown what that function actually returns in addr, observed only 0
 */
int sceUsbdGetDeviceAddress(SceUID uid, SceUID device_id, SceUsbdDeviceAddress *addr);

typedef struct SceUsbdTransferStatus {
	uint32_t unk0; // < 0x40 - transfer id (result of sceUsbdTransferData)
	uint32_t unk1; // unused
	uint32_t unk2; // ret 4. ptr? // status?
	uint32_t unk3; // ret 4. ptr? // transferred?
} SceUsbdTransferStatus;
VITASDK_BUILD_ASSERT_EQ(0x10, SceUsbdTransferStatus);

typedef struct SceUsbdIsochTransferStatus {
	uint32_t unk0; // < 0x40 - size? pipe? transfer id?
	uint32_t unk1; // unused
	uintptr_t* unk2; // ret up to 0x28 buff. 10 * 4 bytes. or 8*5 bytes
	uint32_t unk3; // ret 4. ptr?
} SceUsbdIsochTransferStatus;
VITASDK_BUILD_ASSERT_EQ(0x10, SceUsbdIsochTransferStatus);

/**
 * Get transfer status
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] transfer_id transfer uid
 * @param[out] status buffer for return value
 *
 * @note it is unknown what that function actually returns in addr, observed only 0
 */
int sceUsbdGetTransferStatus(SceUID transfer_id, SceUsbdTransferStatus* status);

/**
 * Get isochronous transfer status
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] transfer_id transfer uid
 * @param[out] status buffer for return value
 *
 * @note it is unknown what that function actually returns in addr, observed only 0
 */
int sceUsbdGetIsochTransferStatus(SceUID transfer_id, SceUsbdIsochTransferStatus* status);

typedef struct SceUsbdDevicePipe {
	unsigned int device_id;
	unsigned int unk1;
	unsigned int unk2;
	unsigned int unk3;
	unsigned int unk4;
	unsigned int unk5;
} SceUsbdDevicePipe;
VITASDK_BUILD_ASSERT_EQ(0x18, SceUsbdDevicePipe);

/**
 * Open endpoint communication pipe
 *
 * @return pipe_id on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] pipe endpoint to open
 *
 */
SceUID sceUsbdOpenPipe(SceUID uid, SceUsbdDevicePipe* pipe);

/**
 * Open endpoint communication pipe for default config endpoint
 *
 * @return pipe_id on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] device_id device id
 *
 */
SceUID sceUsbdOpenDefaultPipe(SceUID uid, SceUID device_id);

/**
 * Close endpoint communication pipe
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] pipe_id pipe uid
 *
 */
int sceUsbdClosePipe(SceUID uid, SceUID pipe_id);

/**
 * Transfer data to/from endpoint
 *
 * @return transfer_id on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] data data to transfer
 *
 */
SceUID sceUsbdTransferData(SceUID uid, SceUsbdTransferData *data);

typedef struct SceUsbdIsochTransfer {
	unsigned int unk0; // array of num_packets? ptrs to 4
	unsigned int unk1; // num packets?
	unsigned int unk2;
	unsigned int unk3;

	unsigned int unk4;
	unsigned int unk5;
	unsigned int unk6;
	unsigned int unk7;

	unsigned int unk8;
	unsigned int unk9;
} SceUsbdIsochTransfer;
VITASDK_BUILD_ASSERT_EQ(0x28, SceUsbdIsochTransfer);

/**
 * Transfer data to/from endpoint isochronously
 *
 * @return transfer_id on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] pipe_id pipe uid
 * @param[in] transfer data to transfer
 *
 */
int sceUsbdIsochTransferData(SceUID uid, SceUID pipe_id, SceUsbdIsochTransfer* transfer);

/**
 * Receive usb event
 *
 * @return transfer_id on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[out] event
 *
 */
int sceUsbdReceiveEvent(SceUID uid, SceUsbdReceiveEvent *event);

/**
 * Register logical device driver
 *
 * @return driver_id on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] name driver name, 255 max
 *
 */
SceUID sceUsbdRegisterLdd(SceUID uid, char* name);

/**
 * Register logical device driver for composite devices
 *
 * @return driver_id on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] name driver name, 255 max
 *
 */
SceUID sceUsbdRegisterCompositeLdd(SceUID uid, char* name);

/**
 * De-register logical device driver
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] name driver name, 255 max
 *
 */
int sceUsbdUnregisterLdd(SceUID uid, char* name);

typedef struct SceUsbdAttachCompositeParam {
	uint32_t driver_id;
	uint32_t bus;
	uint32_t device;
	uint32_t unk3; // num devices?
	uint32_t unk4;
} SceUsbdAttachCompositeParam;
VITASDK_BUILD_ASSERT_EQ(0x14, SceUsbdAttachCompositeParam);

/**
 * Attach composite driver to device
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] uid uid
 * @param[in] param parameters
 *
 */
int sceUsbdAttachCompositeLdd(SceUID uid, SceUsbdAttachCompositeParam* param);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_USBD_H_ */
