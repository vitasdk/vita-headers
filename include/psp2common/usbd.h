/**
 * \kernelgroup{SceUsbd}
 * \usage{psp2common/usbd.h}
 */

#ifndef _PSP2COMMON_USBD_H_
#define _PSP2COMMON_USBD_H_

#include <vitasdk/build_utils.h>
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

#define SCE_USBD_CONFIGURATION_RESERVED_ZERO         0x1f
#define SCE_USBD_CONFIGURATION_REMOTE_WAKEUP         0x20
#define SCE_USBD_CONFIGURATION_SELF_POWERED          0x40
#define SCE_USBD_CONFIGURATION_RESERVED_ONE          0x80

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
VITASDK_BUILD_ASSERT_EQ(0x12, SceUsbdDeviceDescriptor);

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
VITASDK_BUILD_ASSERT_EQ(0xA, SceUsbdConfigurationDescriptor);

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
VITASDK_BUILD_ASSERT_EQ(9, SceUsbdInterfaceDescriptor);

typedef struct SceUsbdEndpointDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
} SceUsbdEndpointDescriptor;
VITASDK_BUILD_ASSERT_EQ(8, SceUsbdEndpointDescriptor);

typedef struct SceUsbdStringDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bString[0];
} SceUsbdStringDescriptor;
VITASDK_BUILD_ASSERT_EQ(2, SceUsbdStringDescriptor);

typedef struct SceUsbdHidSubDescriptorInfo {
	uint8_t bDescriptorType;
	uint8_t wDescriptorLength0;
	uint8_t wDescriptorLength1;
} SceUsbdHidSubDescriptorInfo;
VITASDK_BUILD_ASSERT_EQ(3, SceUsbdHidSubDescriptorInfo);

typedef struct SceUsbdHidDescriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bcdHID0;
	uint8_t bcdHID1;
	uint8_t bCountryCode;
	uint8_t bNumDescriptors;  /* SubDescriptor count */
	SceUsbdHidSubDescriptorInfo SubDescriptorInfo[0];
} SceUsbdHidDescriptor;
VITASDK_BUILD_ASSERT_EQ(6, SceUsbdHidDescriptor);

typedef struct SceUsbdDeviceAddress {
	unsigned int unk0;
	unsigned short unk1;
} __attribute__((packed)) SceUsbdDeviceAddress;
VITASDK_BUILD_ASSERT_EQ(6, SceUsbdDeviceAddress);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2COMMON_USBD_H_ */
