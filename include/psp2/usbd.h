/**
 * \usergroup{SceUsbd}
 * \usage{psp2/usbd.h,SceUsbd_stub}
 */


#ifndef _PSP2_USBD_H_
#define _PSP2_USBD_H_

#include <psp2common/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceUsbdErrorCode {
	SCE_USBD_ERROR_NOT_INITIALIZED     = 0x80240001,
	SCE_USBD_ERROR_ALREADY_INITIALIZED = 0x80240002,
	SCE_USBD_ERROR_INVALID_PARAM       = 0x80240003,

	SCE_USBD_ERROR_PIPE_NOT_FOUND      = 0x80240004,

	SCE_USBD_ERROR_NO_MEMORY           = 0x80240005,
	SCE_USBD_ERROR_DEVICE_NOT_FOUND    = 0x80240006,

	SCE_USBD_ERROR_80240007            = 0x80240007,
	SCE_USBD_ERROR_80240009            = 0x80240009,
	SCE_USBD_ERROR_8024000A            = 0x8024000A,

	SCE_USBD_ERROR_FATAL               = 0x802400FF
} SceUsbdErrorCode;

typedef struct SceUsbdDeviceInfo {
	unsigned int port;
	unsigned int device_num;
	unsigned int unk3; // handled? 0, 1, 2
} SceUsbdDeviceInfo;

typedef struct SceUsbdTransferData {
	unsigned int pipe; // 0x00
	const void *data; // 0x04
	unsigned int data_size;  // 0x08
	void *transferred; //  // 0x0C // ptr to 8 bytes?
	unsigned int timeout;  // 0x10 // size of above ptr? only 8 allowed?
} SceUsbdTransferData; /* size = 0x14 */

typedef struct SceUsbdReceiveEvent {
	unsigned int unk0; // 0
	unsigned int unk1; // next ptr?
	unsigned int unk2; // != 8, set to 1, 2, 4? // transfer flags? type?
	unsigned int unk3;
	unsigned int unk4;
	unsigned int unk5;
	unsigned int transfer_id;
} SceUsbdReceiveEvent; /* size = 0x1C */

typedef struct SceUsbdDeviceAddress {
	unsigned int unk0;
	unsigned short unk1;
} SceUsbdDeviceAddress; /* size = 0x6 */

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

#define SCE_USBD_CLASS_PER_INTERFACE                 0x00
#define SCE_USBD_CLASS_AUDIO                         0x01
#define SCE_USBD_CLASS_COMMUNICATIONS                0x02
#define SCE_USBD_CLASS_HID                           0x03
#define SCE_USBD_CLASS_MONITOR                       0x04
#define SCE_USBD_CLASS_PHYSICAL                      0x05
#define SCE_USBD_CLASS_POWER                         0x06
#define SCE_USBD_CLASS_PRINTER                       0x07
#define SCE_USBD_CLASS_STORAGE                       0x08
#define SCE_USBD_CLASS_HUB                           0x09
#define SCE_USBD_CLASS_DATA                          0x0a
#define SCE_USBD_CLASS_VENDOR_SPECIFIC               0xff

typedef enum SceUsbdDescriptorType {
	SCE_USBD_DESCRIPTOR_DEVICE            = 0x01,    // bDescriptorType for a Device Descriptor.
	SCE_USBD_DESCRIPTOR_CONFIGURATION     = 0x02,    // bDescriptorType for a Configuration Descriptor.
	SCE_USBD_DESCRIPTOR_STRING            = 0x03,    // bDescriptorType for a String Descriptor.
	SCE_USBD_DESCRIPTOR_INTERFACE         = 0x04,    // bDescriptorType for an Interface Descriptor.
	SCE_USBD_DESCRIPTOR_ENDPOINT          = 0x05,    // bDescriptorType for an Endpoint Descriptor.

	SCE_USBD_DESCRIPTOR_DEVICE_QUALIFIER  = 0x06,    // bDescriptorType for a Device Qualifier.
	SCE_USBD_DESCRIPTOR_OTHER_SPEED       = 0x07,    // bDescriptorType for a Other Speed Configuration.
	SCE_USBD_DESCRIPTOR_INTERFACE_POWER   = 0x08,    // bDescriptorType for Interface Power.
	SCE_USBD_DESCRIPTOR_OTG               = 0x09,    // bDescriptorType for an OTG Descriptor.
	SCE_USBD_DESCRIPTOR_HID               = 0x21,    // bDescriptorType for an HID descriptor.
	SCE_USBD_DESCRIPTOR_REPORT            = 0x22     // bDescriptorType for an HID report descriptor.
} SceUsbdDescriptorType;

typedef struct SceUsbdDeviceDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdUSB;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubclass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t iManufacturer;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfigurations;
} SceUsbdDeviceDescriptor;

typedef struct SceUsbdConfigurationDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wTotalLength;
	uint8_t bNumInterfaces;
	uint8_t bConfigurationValue;
	uint8_t iConfiguration;
	uint8_t bmAttributes;
	uint8_t MaxPower;
} SceUsbdConfigurationDescriptor;

#define SCE_USBD_CONFIGURATION_RESERVED_ZERO         0x1f
#define SCE_USBD_CONFIGURATION_REMOTE_WAKEUP         0x20
#define SCE_USBD_CONFIGURATION_SELF_POWERED          0x40
#define SCE_USBD_CONFIGURATION_RESERVED_ONE          0x80

typedef struct SceUsbdInterfaceDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubclass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;
} SceUsbdInterfaceDescriptor;

typedef struct SceUsbdEndpointDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
} SceUsbdEndpointDescriptor;

/* bmAttributes */
#define SCE_USBD_ENDPOINT_TRANSFER_TYPE_BITS         0x03
#define SCE_USBD_ENDPOINT_TRANSFER_TYPE_SHIFT        0
#define SCE_USBD_ENDPOINT_TRANSFER_TYPE_CONTROL      0x00

#define SCE_USBD_ENDPOINT_TRANSFER_TYPE_ISOCHRONOUS  0x01
#define SCE_USBD_ENDPOINT_TRANSFER_TYPE_BULK         0x02
#define SCE_USBD_ENDPOINT_TRANSFER_TYPE_INTERRUPT    0x03

/* bEndpointAddress */
#define SCE_USBD_ENDPOINT_NUMBER_BITS                0x1f
#define SCE_USBD_ENDPOINT_NUMBER_SHIFT               0
#define SCE_USBD_ENDPOINT_DIRECTION_BITS             0x80
#define SCE_USBD_ENDPOINT_DIRECTION_SHIFT            7
#define SCE_USBD_ENDPOINT_DIRECTION_OUT              0x00
#define SCE_USBD_ENDPOINT_DIRECTION_IN               0x80

typedef struct SceUsbdStringDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bString[0];
} SceUsbdStringDescriptor;

typedef struct SceUsbdHidSubDescriptorInfo {
	uint8_t bDescriptorType;
	uint8_t wDescriptorLength0;
	uint8_t wDescriptorLength1;
} SceUsbdHidSubDescriptorInfo;

typedef struct SceUsbdHidDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bcdHID0;
	uint8_t bcdHID1;
	uint8_t bCountryCode;
	uint8_t bNumDescriptors;  /* SubDescriptor count */
	SceUsbdHidSubDescriptorInfo SubDescriptorInfo[0];
} SceUsbdHidDescriptor;


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

typedef struct SceUsbdIsochTransferStatus {
	uint32_t unk0; // < 0x40 - size? pipe? transfer id?
	uint32_t unk1; // unused
	uintptr_t* unk2; // ret up to 0x28 buff. 10 * 4 bytes. or 8*5 bytes
	uint32_t unk3; // ret 4. ptr?
} SceUsbdIsochTransferStatus;

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
} SceUsbdDevicePipe; /* size = 0x18 */

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
} SceUsbdIsochTransfer; /* size = 0x28 */

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
} SceUsbdAttachCompositeParam; /* size = 0x14 */

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
