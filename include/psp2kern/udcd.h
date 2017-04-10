/**
 * \kernelgroup{SceUdcd}
 * \usage{psp2kern/udcd.h,SceUdcdForDriver_stub}
 */


#ifndef _PSP2_KERNEL_UDCD_H_
#define _PSP2_KERNEL_UDCD_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Device and/or Interface Class codes
 */
#define USB_CLASS_PER_INTERFACE         0       /* for DeviceClass */
#define USB_CLASS_AUDIO                 1
#define USB_CLASS_COMM                  2
#define USB_CLASS_HID                   3
#define USB_CLASS_PRINTER               7
#define USB_CLASS_PTP                   6
#define USB_CLASS_MASS_STORAGE          8
#define USB_CLASS_HUB                   9
#define USB_CLASS_DATA                  10
#define USB_CLASS_VENDOR_SPEC           0xff

/*
 * Descriptor types
 */
#define USB_DT_DEVICE			0x01
#define USB_DT_CONFIG			0x02
#define USB_DT_STRING			0x03
#define USB_DT_INTERFACE		0x04
#define USB_DT_ENDPOINT			0x05

/*
 * Standard requests
 */
#define USB_REQ_GET_STATUS		0x00
#define USB_REQ_CLEAR_FEATURE		0x01
#define USB_REQ_SET_FEATURE		0x03
#define USB_REQ_SET_ADDRESS		0x05
#define USB_REQ_GET_DESCRIPTOR		0x06
#define USB_REQ_SET_DESCRIPTOR		0x07
#define USB_REQ_GET_CONFIG		0x08
#define USB_REQ_SET_CONFIG		0x09
#define USB_REQ_GET_INTERFACE		0x0a
#define USB_REQ_SET_INTERFACE		0x0b
#define USB_REQ_SYNC_FRAME		0x0c

/*
 * Descriptor sizes per descriptor type
 */
#define USB_DT_DEVICE_SIZE		18
#define USB_DT_CONFIG_SIZE		9
#define USB_DT_INTERFACE_SIZE		9
#define USB_DT_ENDPOINT_SIZE		7
#define USB_DT_ENDPOINT_AUDIO_SIZE	9	/* Audio extension */
#define USB_DT_HUB_NONVAR_SIZE		7

/*
 * Control message request type bitmask
 */
#define USB_CTRLTYPE_DIR_MASK		0x80
#define USB_CTRLTYPE_DIR_HOST2DEVICE	(0 << 7)
#define USB_CTRLTYPE_DIR_DEVICE2HOST	(1 << 7)
#define USB_CTRLTYPE_TYPE_MASK		0x60
#define USB_CTRLTYPE_TYPE_STANDARD	(0 << 5)
#define USB_CTRLTYPE_TYPE_CLASS		(1 << 5)
#define USB_CTRLTYPE_TYPE_VENDOR	(2 << 5)
#define USB_CTRLTYPE_TYPE_RESERVED	(3 << 5)
#define USB_CTRLTYPE_REC_MASK		0x1f
#define USB_CTRLTYPE_REC_DEVICE		0
#define USB_CTRLTYPE_REC_INTERFACE	1
#define USB_CTRLTYPE_REC_ENDPOINT	2
#define USB_CTRLTYPE_REC_OTHER		3

/*
 * Endpoint types and masks
 */
#define USB_ENDPOINT_ADDRESS_MASK       0x0f    /* in bEndpointAddress */
#define USB_ENDPOINT_DIR_MASK           0x80

#define USB_FEATURE_ENDPOINT_HALT	0

#define USB_ENDPOINT_IN			0x80
#define USB_ENDPOINT_OUT		0x00

#define USB_ENDPOINT_TYPE_MASK          0x03    /* in bmAttributes */
#define USB_ENDPOINT_TYPE_CONTROL       0
#define USB_ENDPOINT_TYPE_ISOCHRONOUS   1
#define USB_ENDPOINT_TYPE_BULK          2
#define USB_ENDPOINT_TYPE_INTERRUPT     3

/* HID constants. Not part of chapter 9 */

/*
 * Class-Specific Requests
 */
#define HID_REQUEST_GET_REPORT		0x01
#define HID_REQUEST_GET_IDLE		0x02
#define HID_REQUEST_GET_PROTOCOL	0x03
#define HID_REQUEST_SET_REPORT		0x09
#define HID_REQUEST_SET_IDLE		0x0A
#define HID_REQUEST_SET_PROTOCOL	0x0B

/*
 * Class Descriptor Types
 */
#define HID_DESCRIPTOR_HID		0x21
#define HID_DESCRIPTOR_REPORT		0x22
#define HID_DESRIPTOR_PHY		0x23

/*
 * Protocol Selection
 */
#define BOOT_PROTOCOL			0x00
#define RPT_PROTOCOL			0x01

/*
 * HID Interface Class Code
 */
#define HID_INTF			0x03

/*
 * HID Interface Class SubClass Codes
 */
#define BOOT_INTF_SUBCLASS		0x01

/*
 * HID Interface Class Protocol Codes
 */
#define HID_PROTOCOL_NONE		0x00
#define HID_PROTOCOL_KEYBOARD		0x01
#define HID_PROTOCOL_MOUSE		0x02


/*
 * USB Status
 */
#define SCE_UDCD_STATUS_CONNECTION_NEW		0x0001
#define SCE_UDCD_STATUS_CONNECTION_ESTABLISHED	0x0002
#define SCE_UDCD_STATUS_CONNECTION_SUSPENDED	0x0004
#define SCE_UDCD_STATUS_CABLE_DISCONNECTED	0x0010
#define SCE_UDCD_STATUS_CABLE_CONNECTED		0x0020
#define SCE_UDCD_STATUS_DEACTIVATED		0x0100
#define SCE_UDCD_STATUS_ACTIVATED		0x0200
#define SCE_UDCD_STATUS_IS_CHARGING		0x0400
#define SCE_UDCD_STATUS_USE_USB_CHARGING	0x0800
#define SCE_UDCD_STATUS_UNKNOWN_1000		0x1000
#define SCE_UDCD_STATUS_UNKNOWN_2000		0x2000

/*
 * USB Driver status
 */
#define SCE_UDCD_STATUS_DRIVER_STARTED         0x01
#define SCE_UDCD_STATUS_DRIVER_REGISTERED      0x02

/*
 * USB limits
 */
#define SCE_UDCD_MAX_INTERFACES     8
#define SCE_UDCD_MAX_ENDPOINTS      9
#define SCE_UDCD_MAX_ALTERNATE      2

#define SCE_UDCD_RETCODE_CANCEL             -1
#define SCE_UDCD_RETCODE_CANCEL_ALL         -2
#define SCE_UDCD_RETCODE_CANCELTRANSMISSION -3
#define SCE_UDCD_RETCODE_SUCCESS       0
#define SCE_UDCD_RETCODE_SEND          1
#define SCE_UDCD_RETCODE_RECV          2

/*
 * Error codes
 */
#define SCE_UDCD_ERROR_ALREADY_DONE		0x80243001
#define SCE_UDCD_ERROR_INVALID_ARGUMENT		0x80243002
#define SCE_UDCD_ERROR_ARGUMENT_EXCEEDED_LIMIT 	0x80243003
#define SCE_UDCD_ERROR_MEMORY_EXHAUSTED		0x80243004
#define SCE_UDCD_ERROR_DRIVER_NOT_FOUND		0x80243005
#define SCE_UDCD_ERROR_DRIVER_IN_PROGRESS	0x80243006
#define SCE_UDCD_ERROR_BUS_DRIVER_NOT_STARTED	0x80243007
#define SCE_UDCD_ERROR_WAIT_TIMEOUT		0x80243008
#define SCE_UDCD_ERROR_WAIT_CANCEL 		0x80243009
#define SCE_UDCD_ERROR_INVALID_POINTER 		0x80000103
#define SCE_UDCD_ERROR_INVALID_FLAG		0x80000105
#define SCE_UDCD_ERROR_INVALID_VALUE 		0x800001FE
#define SCE_UDCD_ERROR_ILLEGAL_CONTEXT		0x80000030
#define SCE_UDCD_ERROR_USBDRIVER_INVALID_DRIVER	0x80243200
#define SCE_UDCD_ERROR_USBDRIVER_INVALID_NAME	0x80243201
#define SCE_UDCD_ERROR_USBDRIVER_INVALID_FUNCS	0x80243202


/*
 *  USB string descriptor
 */
typedef struct SceUdcdStringDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	short         bString[31];
} SceUdcdStringDescriptor;  /* Size 64 */

/*
 *  USB device descriptor
 */
typedef struct SceUdcdDeviceDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short bcdUSB;
	unsigned char  bDeviceClass;
	unsigned char  bDeviceSubClass;
	unsigned char  bDeviceProtocol;
	unsigned char  bMaxPacketSize0;
	unsigned short idVendor;
	unsigned short idProduct;
	unsigned short bcdDevice;
	unsigned char  iManufacturer;
	unsigned char  iProduct;
	unsigned char  iSerialNumber;
	unsigned char  bNumConfigurations;
} __attribute__ ((aligned(4))) SceUdcdDeviceDescriptor; /* size 20 */

/*
 *  USB device qualifier descriptor
 */
typedef struct SceUdcdDeviceQualifierDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short bcdUSB;
	unsigned char  bDeviceClass;
	unsigned char  bDeviceSubClass;
	unsigned char  bDeviceProtocol;
	unsigned char  bMaxPacketSize0;
	unsigned char  bNumConfigurations;
	unsigned char  bReserved;
} __attribute__ ((aligned(4))) SceUdcdDeviceQualifierDescriptor; /* size 12 */

/*
 *  USB configuration descriptor
 */
typedef struct SceUdcdConfigDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short wTotalLength;
	unsigned char  bNumInterfaces;
	unsigned char  bConfigurationValue;
	unsigned char  iConfiguration;
	unsigned char  bmAttributes;
	unsigned char  bMaxPower;

	struct SceUdcdInterfaceSettings *settings;

	unsigned char *extra;   /* Extra descriptors */
	int extraLength;
} SceUdcdConfigDescriptor; /* size 24 */

/*
 *  USB driver interfaces structure
 */
typedef struct SceUdcdInterfaceSettings {
	/* Pointers to the individual interface descriptors */
	struct SceUdcdInterfaceDescriptor *descriptors;

	unsigned int alternateSetting;

	/* Number of interface descriptors */
	unsigned int numDescriptors;
} SceUdcdInterfaceSettings;

/*
 *  USB Interface descriptor
 */
typedef struct SceUdcdInterfaceDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned char bInterfaceNumber;
	unsigned char bAlternateSetting;
	unsigned char bNumEndpoints;
	unsigned char bInterfaceClass;
	unsigned char bInterfaceSubClass;
	unsigned char bInterfaceProtocol;
	unsigned char iInterface;

	struct SceUdcdEndpointDescriptor *endpoints;

	unsigned char *extra;   /* Extra descriptors */
	int extraLength;
} SceUdcdInterfaceDescriptor; /* size 24 */

/*
 *  USB endpoint descriptor
 */
typedef struct SceUdcdEndpointDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned char  bEndpointAddress;
	unsigned char  bmAttributes;
	unsigned short wMaxPacketSize;
	unsigned char  bInterval;

	unsigned char *extra;   /* Extra descriptors */
	int extraLength;
} SceUdcdEndpointDescriptor; /* size 16 */

/*
 *  USB driver interface
 */
typedef struct SceUdcdInterface {
	/* Expectant interface number (interface number or -1) */
	int expectNumber;
	/* End interface  */
	int interfaceNumber;
	/* Number of interfaces */
	int numInterfaces;
} SceUdcdInterface;

/*
 *  USB driver endpoint
 */
typedef struct SceUdcdEndpoint {
	/* 0x80 = in, 0x00 = out */
	int direction;
	/* Driver Endpoint number (must be filled in sequentially) */
	int driverEndpointNumber;
	/* Endpoint number (Filled in by the bus driver) */
	int endpointNumber;
	/* Number of transmitted bytes */
	int transmittedBytes;
} SceUdcdEndpoint;

/*
 *  USB driver configuration
 */
typedef struct SceUdcdConfiguration {
	/* Pointer to the configuration descriptors */
	SceUdcdConfigDescriptor *configDescriptors;
	/* USB driver interface settings */
	SceUdcdInterfaceSettings *settings;
	/* Pointer to the first interface descriptor */
	SceUdcdInterfaceDescriptor *interfaceDescriptors;
	/* Pointer to the first endpoint descriptor */
	SceUdcdEndpointDescriptor *endpointDescriptors;
} SceUdcdConfiguration;

/*
 *  USB EP0 Device Request
 */
typedef struct SceUdcdEP0DeviceRequest {
	unsigned char  bmRequestType;
	unsigned char  bRequest;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;
} SceUdcdEP0DeviceRequest;

/*
 *  USB driver structure
 */
typedef struct SceUdcdDriver {
	/* Name of the USB driver */
	const char *driverName;
	/* Number of endpoints in this driver (including default control) */
	int numEndpoints;
	/* List of endpoint structures (used when calling other functions) */
	SceUdcdEndpoint *endpoints;
	/* Interface list */
	SceUdcdInterface *interface;
	/* Pointer to hi-speed device descriptor */
	SceUdcdDeviceDescriptor *descriptor_hi;
	/* Pointer to hi-speed device configuration */
	SceUdcdConfiguration *configuration_hi;
	/* Pointer to full-speed device descriptor */
	SceUdcdDeviceDescriptor *descriptor;
	/* Pointer to full-speed device configuration */
	SceUdcdConfiguration *configuration;
	/* Unk0 */
	SceUdcdStringDescriptor *stringDescriptorsUnk0;
	/* Default String descriptor */
	SceUdcdStringDescriptor *stringDescriptorsUnk1;
	/* String descriptors (unknown) */
	SceUdcdStringDescriptor *stringDescriptorsUnk2;
	/* Received a control request  */
	int (*processRequest) (int recipient, int arg /* endpoint number or interface number */, SceUdcdEP0DeviceRequest *req);
	/* Change alternate setting */
	int (*changeSetting) (int interfaceNumber, int alternateSetting);
	/* Configuration set (attach) function */
	int (*attach) (int usb_version);
	/* Configuration unset (detach) function */
	void (*detach) (void);
	/* Configure the device */
	void (*configure) (int usb_version, int desc_count, SceUdcdInterfaceSettings *settings);
	/* Function called when the driver is started */
	int (*start) (int size, void *args);
	/* Function called when the driver is stopped */
	int (*stop) (int size, void *args);
	/* Unk */
	unsigned int unk1;
	unsigned int unk2;
	/* Link to next USB driver in the chain, set to NULL */
	struct SceUdcdDriver *link;
} SceUdcdDriver;

/*
 *  USB device request
 */
typedef struct SceUdcdDeviceRequest {
	/* Pointer to the endpoint to queue request on */
	SceUdcdEndpoint *endpoint;
	/* Pointer to the data buffer to use in the request */
	void *data;
	/* Unknown */
	unsigned int unk;
	/* Size of the data buffer */
	int  size;
	/* Is a control request? */
	int  isControlRequest;
	/* Pointer to the function to call on completion */
	void (*onComplete)(struct SceUdcdDeviceRequest *req);
	/* Number of transmitted bytes  */
	int  transmitted;
	/* Return code of the request, 0 == success, -3 == canceled */
	int  returnCode;
	/* Link pointer to next request used by the driver, set it to NULL */
	struct SceUdcdDeviceRequest *next;
	/* An unused value (maybe an argument) */
	void *unused;
	/* Physical address */
	void *physicalAddress;
} SceUdcdDeviceRequest;

/*
 *  USB driver name
 */
typedef struct SceUdcdDriverName {
	int  size;
	char name[32];
	int  flags;
} __attribute__ ((aligned(16))) SceUdcdDriverName; /* size 48 */

/*
 *  USB device information
 */
typedef struct SceUdcdDeviceInfo {
	unsigned char info[64];
} SceUdcdDeviceInfo;

/**
  * Start a USB driver.
  *
  * @param driverName - name of the USB driver to start
  * @param size - Size of arguments to pass to USB driver start
  * @param args - Arguments to pass to USB driver start
  *
  * @return 0 on success
  */
int ksceUdcdStart(const char *driverName, int size, void *args);

/**
  * Stop a USB driver.
  *
  * @param driverName - name of the USB driver to stop
  * @param size - Size of arguments to pass to USB driver start
  * @param args - Arguments to pass to USB driver start
  *
  * @return 0 on success
  */
int ksceUdcdStop(const char *driverName, int size, void *args);

/**
  * Activate a USB driver.
  *
  * @param pid - Product ID for the default USB Driver
  *
  * @return 0 on success
  */
int ksceUdcdActivate(unsigned int productId);

/**
  * Deactivate USB driver.
  *
  * @return 0 on success
  */
int ksceUdcdDeactivate(void);

/**
  * Get USB state
  *
  * @return OR'd SCE_UDCD_STATUS_* constants
  */
int ksceUdcdGetDeviceState(void);

/**
 * Get device information
 *
 * @param[out] devInfo - Device information
 *
 * @return 0 on success, < 0 on error.
*/
int ksceUdcdGetDeviceInfo(SceUdcdDeviceInfo *devInfo);

/**
  * Get state of a specific USB driver
  *
  * @param driverName - name of USB driver to get status from
  *
  * @return SCE_UDCD_STATUS_DRIVER_STARTED  if the driver has been started, SCE_UDCD_STATUS_DRIVER_REGISTERED if it is stopped
  */
int ksceUdcdGetDrvState(const char *driverName);

/**
 *  Get the list of drivers
 *  @param flags - combination of SCE_UDCD_STATUS_DRIVER_STARTED or SCE_UDCD_STATUS_DRIVER_REGISTERED
 *  @param list - points to the output list
 *  @param size - number of entries in the output list
 *  @return the number of drivers in the output or < 0 in case of error
 */
int ksceUdcdGetDrvList(unsigned int flags, SceUdcdDriverName *list, int size);

/**
 * Wait for USB state
 * @param state - combination of states(returned by ksceUdcdGetState)
 * @param waitMode - one of the ::SceEventFlagWaitTypes
 * @param timeout - pointer to timeout
 * @return the usb state or < 0 in case of error
 */
int ksceUdcdWaitState(unsigned int state, unsigned int waitMode, SceUInt *timeout);

/**
 * Cancel a pending ksceUdcdWaitState
 * @return 0 on success
 */
int ksceUdcdWaitCancel(void);

/**
 * Register a USB driver.
 *
 * @param drv - Pointer to a filled out USB driver
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdRegister(SceUdcdDriver *drv);

/**
 * Unregister a USB driver
 *
 * @param drv - Pointer to a filled out USB driver
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdUnregister(SceUdcdDriver *drv);

/**
 * Clear the FIFO on an endpoint
 *
 * @param endp - The endpoint to clear
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdClearFIFO(SceUdcdEndpoint *endp);

/**
 * Cancel any pending requests on an endpoint.
 *
 * @param endp - The endpoint to cancel
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdReqCancelAll(SceUdcdEndpoint *endp);

/**
 * Stall an endpoint
 *
 * @param endp - The endpoint to stall
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdStall(SceUdcdEndpoint *endp);

/**
 * Queue a send request(IN from host pov)
 *
 * @param req - Pointer to a filled out SceUdcdDeviceRequest structure.
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdReqSend(SceUdcdDeviceRequest *req);

/**
 * Queue a receive request(OUT from host pov)
 *
 * @param req - Pointer to a filled out SceUdcdDeviceRequest structure
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdReqRecv(SceUdcdDeviceRequest *req);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_UDCD_H_ */
