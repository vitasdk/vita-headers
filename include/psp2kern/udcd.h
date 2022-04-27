/**
 * \kernelgroup{SceUdcd}
 * \usage{psp2kern/udcd.h,SceUdcdForDriver_stub}
 */


#ifndef _PSP2KERN_UDCD_H_
#define _PSP2KERN_UDCD_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Enumeration for Device and/or Interface Class codes
 */
typedef enum SceUdcdUsbClass {
	USB_CLASS_PER_INTERFACE       = 0x00,  //!< for DeviceClass
	USB_CLASS_AUDIO               = 0x01,
	USB_CLASS_COMM                = 0x02,
	USB_CLASS_HID                 = 0x03,
	USB_CLASS_PTP                 = 0x06,
	USB_CLASS_PRINTER             = 0x07,
	USB_CLASS_MASS_STORAGE        = 0x08,
	USB_CLASS_HUB                 = 0x09,
	USB_CLASS_DATA                = 0x0A,
	USB_CLASS_VIDEO               = 0x0E,
	USB_CLASS_VENDOR_SPEC         = 0xFF
} SceUdcdUsbClass;

/** Enumeration for descriptor types
 */
typedef enum SceUdcdUsbDt {
	USB_DT_DEVICE         = 0x01,
	USB_DT_CONFIG         = 0x02,
	USB_DT_STRING         = 0x03,
	USB_DT_INTERFACE      = 0x04,
	USB_DT_ENDPOINT       = 0x05
} SceUdcdUsbDt;

/** Enumeration for standard requests
 */
typedef enum SceUdcdUsbReq {
	USB_REQ_GET_STATUS      = 0x00,
	USB_REQ_CLEAR_FEATURE   = 0x01,
	USB_REQ_SET_FEATURE     = 0x03,
	USB_REQ_SET_ADDRESS     = 0x05,
	USB_REQ_GET_DESCRIPTOR  = 0x06,
	USB_REQ_SET_DESCRIPTOR  = 0x07,
	USB_REQ_GET_CONFIG      = 0x08,
	USB_REQ_SET_CONFIG      = 0x09,
	USB_REQ_GET_INTERFACE   = 0x0A,
	USB_REQ_SET_INTERFACE   = 0x0B,
	USB_REQ_SYNC_FRAME      = 0x0C
} SceUdcdUsbReq;

/**
 * Descriptor sizes per descriptor type
 */
#define USB_DT_DEVICE_SIZE		18
#define USB_DT_CONFIG_SIZE		9
#define USB_DT_INTERFACE_SIZE		9
#define USB_DT_ENDPOINT_SIZE		7
#define USB_DT_ENDPOINT_AUDIO_SIZE	9	//!< Audio extension
#define USB_DT_HUB_NONVAR_SIZE		7

/** Control message request type bitmask
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

/** Endpoint types and masks
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

/** Class-Specific Requests
 */
typedef enum SceUdcdHidRequest {
	HID_REQUEST_GET_REPORT     = 0x01,
	HID_REQUEST_GET_IDLE       = 0x02,
	HID_REQUEST_GET_PROTOCOL   = 0x03,
	HID_REQUEST_SET_REPORT     = 0x09,
	HID_REQUEST_SET_IDLE       = 0x0A,
	HID_REQUEST_SET_PROTOCOL   = 0x0B
} SceUdcdHidRequest;

/** Class Descriptor Types
 */
typedef enum SceUdcdHidDescriptor {
	HID_DESCRIPTOR_HID     = 0x21,
	HID_DESCRIPTOR_REPORT  = 0x22,
	HID_DESRIPTOR_PHY      = 0x23
} SceUdcdHidDescriptor;

/** Protocol Selection
 */
typedef enum SceUdcdProtocol {
	BOOT_PROTOCOL  = 0x00,
	RPT_PROTOCOL   = 0x01
} SceUdcdProtocol;

/** HID Interface Class Code
 */
#define HID_INTF			0x03

/** HID Interface Class SubClass Codes
 */
#define BOOT_INTF_SUBCLASS		0x01

/** HID Interface Class Protocol Codes
 */
typedef enum SceUdcdHidProtocol {
	HID_PROTOCOL_NONE      = 0x00,
	HID_PROTOCOL_KEYBOARD  = 0x01,
	HID_PROTOCOL_MOUSE     = 0x02
} SceUdcdHidProtocol;

/** USB Status
 */
typedef enum SceUdcdStatus {
	SCE_UDCD_STATUS_CONNECTION_NEW          = 0x0001,
	SCE_UDCD_STATUS_CONNECTION_ESTABLISHED  = 0x0002,
	SCE_UDCD_STATUS_CONNECTION_SUSPENDED    = 0x0004,
	SCE_UDCD_STATUS_CABLE_DISCONNECTED      = 0x0010,
	SCE_UDCD_STATUS_CABLE_CONNECTED         = 0x0020,
	SCE_UDCD_STATUS_DEACTIVATED             = 0x0100,
	SCE_UDCD_STATUS_ACTIVATED               = 0x0200,
	SCE_UDCD_STATUS_IS_CHARGING             = 0x0400,
	SCE_UDCD_STATUS_USE_USB_CHARGING        = 0x0800,
	SCE_UDCD_STATUS_UNKNOWN_1000            = 0x1000,
	SCE_UDCD_STATUS_UNKNOWN_2000            = 0x2000
} SceUdcdStatus;

/** USB Driver status
 */
typedef enum SceUdcdStatusDriver {
	SCE_UDCD_STATUS_DRIVER_STARTED         = 0x01,
	SCE_UDCD_STATUS_DRIVER_REGISTERED      = 0x02
} SceUdcdStatusDriver;

/** USB limits
 */
#define SCE_UDCD_MAX_INTERFACES     8
#define SCE_UDCD_MAX_ENDPOINTS      9
#define SCE_UDCD_MAX_ALTERNATE      2

typedef enum SceUdcdRetcode {
	SCE_UDCD_RETCODE_CANCEL              = -1,
	SCE_UDCD_RETCODE_CANCEL_ALL          = -2,
	SCE_UDCD_RETCODE_CANCEL_TRANSMISSION = -3,
	SCE_UDCD_RETCODE_SUCCESS             =  0,
	SCE_UDCD_RETCODE_SEND                =  1,
	SCE_UDCD_RETCODE_RECV                =  2
} SceUdcdRetcode;

/** Error codes
 */
typedef enum SceUdcdErrorCode {
	SCE_UDCD_ERROR_ILLEGAL_CONTEXT          = 0x80000030,
	SCE_UDCD_ERROR_INVALID_POINTER          = 0x80000103,
	SCE_UDCD_ERROR_INVALID_FLAG             = 0x80000105,
	SCE_UDCD_ERROR_INVALID_VALUE            = 0x800001FE,
	SCE_UDCD_ERROR_ALREADY_DONE             = 0x80243001,
	SCE_UDCD_ERROR_INVALID_ARGUMENT         = 0x80243002,
	SCE_UDCD_ERROR_ARGUMENT_EXCEEDED_LIMIT  = 0x80243003,
	SCE_UDCD_ERROR_MEMORY_EXHAUSTED         = 0x80243004,
	SCE_UDCD_ERROR_DRIVER_NOT_FOUND         = 0x80243005,
	SCE_UDCD_ERROR_DRIVER_IN_PROGRESS       = 0x80243006,
	SCE_UDCD_ERROR_BUS_DRIVER_NOT_STARTED   = 0x80243007,
	SCE_UDCD_ERROR_WAIT_TIMEOUT             = 0x80243008,
	SCE_UDCD_ERROR_WAIT_CANCEL              = 0x80243009,
	SCE_UDCD_ERROR_USBDRIVER_INVALID_DRIVER = 0x80243200,
	SCE_UDCD_ERROR_USBDRIVER_INVALID_NAME   = 0x80243201,
	SCE_UDCD_ERROR_USBDRIVER_INVALID_FUNCS  = 0x80243202
} SceUdcdErrorCode;

/** SceUdcdDeviceRequest Flags
 */
typedef enum SceUdcdDeviceRequestAttr {
	SCE_UDCD_DEVICE_REQUEST_ATTR_PHYCONT = 0x00000001
} SceUdcdDeviceRequestAttr;

/**  USB string descriptor
 */
typedef struct SceUdcdStringDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	short         bString[31];
} SceUdcdStringDescriptor;

/**  USB device descriptor
 */
typedef struct SCE_ALIGN(4) SceUdcdDeviceDescriptor {
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
} SceUdcdDeviceDescriptor;

/**  USB device qualifier descriptor
 */
typedef struct SCE_ALIGN(4) SceUdcdDeviceQualifierDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short bcdUSB;
	unsigned char  bDeviceClass;
	unsigned char  bDeviceSubClass;
	unsigned char  bDeviceProtocol;
	unsigned char  bMaxPacketSize0;
	unsigned char  bNumConfigurations;
	unsigned char  bReserved;
} SceUdcdDeviceQualifierDescriptor;

/**  USB configuration descriptor
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
	unsigned char *extra;                       //!< Extra descriptors
	int extraLength;
} SceUdcdConfigDescriptor;

/**  USB driver interfaces structure
 */
typedef struct SceUdcdInterfaceSettings {
	struct SceUdcdInterfaceDescriptor *descriptors; //!< Pointers to the individual interface descriptors
	unsigned int alternateSetting;
	unsigned int numDescriptors;                    //!< Number of interface descriptors
} SceUdcdInterfaceSettings;

/**  USB Interface descriptor
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
	unsigned char *extra;                         //!< Extra descriptors
	int extraLength;
} SceUdcdInterfaceDescriptor;

/**  USB endpoint descriptor
 */
typedef struct SceUdcdEndpointDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned char  bEndpointAddress;
	unsigned char  bmAttributes;
	unsigned short wMaxPacketSize;
	unsigned char  bInterval;
	unsigned char *extra;              //!< Extra descriptors
	int extraLength;
} SceUdcdEndpointDescriptor;

/**  USB driver interface
 */
typedef struct SceUdcdInterface {
	int expectNumber;     //!< Expectant interface number (interface number or -1)
	int interfaceNumber;  //!< End interface
	int numInterfaces;    //!< Number of interfaces
} SceUdcdInterface;

/**  USB driver endpoint
 */
typedef struct SceUdcdEndpoint {
	int direction;            //!< USB_ENDPOINT_IN /  USB_ENDPOINT_OUT
	int driverEndpointNumber; //!< Driver Endpoint number (must be filled in sequentially)
	int endpointNumber;       //!< Endpoint number (Filled in by the bus driver)
	int transmittedBytes;     //!< Number of transmitted bytes
} SceUdcdEndpoint;

/**  USB driver configuration
 */
typedef struct SceUdcdConfiguration {
	SceUdcdConfigDescriptor   *configDescriptors;     //!< Pointer to the configuration descriptors
	SceUdcdInterfaceSettings  *settings;              //!< USB driver interface settings
	SceUdcdInterfaceDescriptor *interfaceDescriptors;  //!< Pointer to the first interface descriptor
	SceUdcdEndpointDescriptor *endpointDescriptors;   //!< Pointer to the first endpoint descriptor
} SceUdcdConfiguration;

/**  USB EP0 Device Request
 */
typedef struct SceUdcdEP0DeviceRequest {
	unsigned char  bmRequestType;
	unsigned char  bRequest;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;
} SceUdcdEP0DeviceRequest;

/**  USB driver structure
 */
typedef struct SceUdcdDriver {
	const char *driverName;                         //!< Name of the USB driver
	int numEndpoints;                               //!< Number of endpoints in this driver (including default control)
	SceUdcdEndpoint *endpoints;                     //!< List of endpoint structures (used when calling other functions)
	SceUdcdInterface *interface;                    //!< Interface list
	SceUdcdDeviceDescriptor *descriptor_hi;         //!< Pointer to hi-speed device descriptor
	SceUdcdConfiguration *configuration_hi;         //!< Pointer to hi-speed device configuration
	SceUdcdDeviceDescriptor *descriptor;            //!< Pointer to full-speed device descriptor
	SceUdcdConfiguration *configuration;            //!< Pointer to full-speed device configuration
	SceUdcdStringDescriptor *stringDescriptors; //!< Default string descriptors
	SceUdcdStringDescriptor *stringDescriptorProduct; //!< Product string descriptor (iProduct has to be 2)
	SceUdcdStringDescriptor *stringDescriptorSerial; //!< Serial string descriptor (iSerial has to be 3)
	int (*processRequest)(int recipient, int arg /* endpoint number or interface number */, SceUdcdEP0DeviceRequest *req, void *user_data); //!< Received a control request
	int (*changeSetting)(int interfaceNumber, int alternateSetting, int bus); //!< Change alternate setting
	int (*attach)(int usb_version, void *user_data);                                  //!< Configuration set (attach) function
	void (*detach)(void *user_data);                                            //!< Configuration unset (detach) function
	void (*configure)(int usb_version, int desc_count, SceUdcdInterfaceSettings *settings, void *user_data); //!< Configure the device
	int (*start)(int size, void *args, void *user_data); //!< Function called when the driver is started
	int (*stop)(int size, void *args, void *user_data);  //!< Function called when the driver is stopped
	void *user_data;                   //!< User data
	int bus;                   //!< USB bus
	struct SceUdcdDriver *link;          //!< Link to next USB driver in the chain, set to NULL
} SceUdcdDriver;

/**  USB device request
 */
typedef struct SceUdcdDeviceRequest {
	SceUdcdEndpoint *endpoint;                            //!< Pointer to the endpoint to queue request on
	void *data;                                           //!< Pointer to the data buffer to use in the request
	unsigned int attributes;                              //!< Request attributes (See ::SceUdcdDeviceRequestAttr)
	int  size;                                            //!< Size of the data buffer
	int  isControlRequest;                                //!< Is a control request?
	void (*onComplete)(struct SceUdcdDeviceRequest *req); //!< Pointer to the function to call on completion
	int  transmitted;                                     //!< Number of transmitted bytes
	int  returnCode;                                      //!< Return code of the request (See ::SceUdcdRetcode)
	struct SceUdcdDeviceRequest *next;                    //!< Link pointer to next request used by the driver, set it to NULL
	void *unused;                                         //!< An unused value (maybe an argument)
	void *physicalAddress;                                //!< Physical address
} SceUdcdDeviceRequest;

/**  USB driver name
 */
typedef struct SCE_ALIGN(16) SceUdcdDriverName {
	int  size;
	char name[32];
	int  flags;
} SceUdcdDriverName;

/**  USB device information
 */
typedef struct SceUdcdDeviceInfo {
	unsigned char info[64];
} SceUdcdDeviceInfo;

typedef struct SceUdcdWaitParam {
	int unk_00;
	int status;
	int unk_08;
	int unk_0C;
	int unk_10;
	const char *driverName;
} SceUdcdWaitParam;

/**
 * Waits until an UDCD bus is initialized
 *
 * @param[in] timeout - Timeout
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdWaitBusInitialized(unsigned int timeout, int bus);

/**
 * Start a USB driver.
 *
 * @param driverName - Name of the USB driver to start
 * @param size - Size of arguments to pass to USB driver start
 * @param args - Arguments to pass to USB driver start
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdStart(const char *driverName, int size, void *args);

/**
 * Start a USB driver for an UDCD bus.
 *
 * @param driverName - Name of the USB driver to start
 * @param size - Size of arguments to pass to USB driver start
 * @param args - Arguments to pass to USB driver start
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdStartInternal(const char *driverName, int size, void *args, int bus);

/**
 * Starts the current USB driver for an UDCD bus.
 *
 * @param[in] unused - Unused
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdStartCurrentInternal(int unused, int bus);

/**
 * Stop a USB driver.
 *
 * @param driverName - Name of the USB driver to stop
 * @param size - Size of arguments to pass to USB driver start
 * @param args - Arguments to pass to USB driver start
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdStop(const char *driverName, int size, void *args);

/**
 * Stop a USB driver for an UDCD bus.
 *
 * @param driverName - Name of the USB driver to stop
 * @param size - Size of arguments to pass to USB driver start
 * @param args - Arguments to pass to USB driver start
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdStopInternal(const char *driverName, int size, void *args, int bus);

/**
 * Stops the current USB driver for an UDCD bus.
 *
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdStopCurrentInternal(int bus);

/**
 * Activate a USB driver.
 *
 * @param pid - Product ID for the default USB Driver
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdActivate(unsigned int productId);

/**
 * Activate a USB driver for an UDCD bus.
 *
 * @param pid - Product ID for the default USB Driver
 * @param[in] bus_powered - Enable USB bus power
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdActivateInternal(unsigned int productId, unsigned int bus_powered, int bus);

/**
 * Deactivate USB driver.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdDeactivate(void);

/**
 * Deactivate USB driver for an UDCD bus.
 *
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
 */
int ksceUdcdDeactivateInternal(int bus);

/**
 * Get USB state
 *
 * @return One or more ::SceUdcdStatus.
 */
int ksceUdcdGetDeviceState(void);

/**
 * Get USB state for an UDCD bus
 *
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return One or more ::SceUdcdStatus.
 */
int ksceUdcdGetDeviceStateInternal(int bus);

/**
 * Get device information
 *
 * @param[out] devInfo - Device information
 *
 * @return 0 on success, < 0 on error.
*/
int ksceUdcdGetDeviceInfo(SceUdcdDeviceInfo *devInfo);

/**
 * Get device information for an UDCD bus
 *
 * @param[out] devInfo - Device information
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
*/
int ksceUdcdGetDeviceInfoInternal(SceUdcdDeviceInfo *devInfo, int bus);

/**
 * Get state of a specific USB driver
 *
 * @param driverName - name of USB driver to get status from
 *
 * @return SCE_UDCD_STATUS_DRIVER_STARTED if the driver has been started, SCE_UDCD_STATUS_DRIVER_REGISTERED if it is stopped
 */
int ksceUdcdGetDrvState(const char *driverName);

/**
 * Get state of a specific USB driver for an UDCD bus
 *
 * @param driverName - name of USB driver to get status from
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return SCE_UDCD_STATUS_DRIVER_STARTED if the driver has been started, SCE_UDCD_STATUS_DRIVER_REGISTERED if it is stopped
 */
int ksceUdcdGetDrvStateInternal(const char *driverName, int bus);

/**
 * Wait for state
 *
 * @param[in] waitParam - Wait parameter
 * @param[in] timeout - Timeout
 *
 * @return 0 on success, < 0 on error.
*/
int ksceUdcdWaitState(SceUdcdWaitParam *waitParam, unsigned int timeout);

/**
 * Wait for state for an UDCD bus
 *
 * @param[in] waitParam - Wait parameter
 * @param[in] timeout - Timeout
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error.
*/
int ksceUdcdWaitStateInternal(SceUdcdWaitParam *waitParam, unsigned int timeout, int bus);

/**
 * Register a USB driver.
 *
 * @param drv - Pointer to a filled out USB driver
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdRegister(SceUdcdDriver *drv);

/**
 * Register a USB driver to a specific USB bus.
 *
 * @param drv - Pointer to a filled out USB driver
 * @param bus - The USB bus index (usually 2)
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdRegisterInternal(SceUdcdDriver *drv, int bus);

/**
 * Unregister a USB driver
 *
 * @param drv - Pointer to a filled out USB driver
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdUnregister(SceUdcdDriver *drv);

/**
 * Unregister a USB driver for an UDCD bus
 *
 * @param drv - Pointer to a filled out USB driver
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdUnregisterInternal(SceUdcdDriver *drv, int bus);

/**
 * Clear the FIFO on an endpoint
 *
 * @param endp - The endpoint to clear
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdClearFIFO(SceUdcdEndpoint *endp);

/**
 * Clear the FIFO on an endpoint for an UDCD bus
 *
 * @param endp - The endpoint to clear
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdClearFIFOInternal(SceUdcdEndpoint *endp, int bus);

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
 * Stall an endpoint for an UDCD bus
 *
 * @param endp - The endpoint to stall
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdStallInternal(SceUdcdEndpoint *endp, int bus);

/**
 * Queue a send request (IN from host pov)
 *
 * @param req - Pointer to a filled out ::SceUdcdDeviceRequest structure.
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdReqSend(SceUdcdDeviceRequest *req);

/**
 * Queue a send request (IN from host pov) for an UDCD bus
 *
 * @param req - Pointer to a filled out ::SceUdcdDeviceRequest structure.
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdReqSendInternal(SceUdcdDeviceRequest *req, int bus);

/**
 * Queue a receive request (OUT from host pov)
 *
 * @param req - Pointer to a filled out ::SceUdcdDeviceRequest structure
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdReqRecv(SceUdcdDeviceRequest *req);

/**
 * Queue a receive request (OUT from host pov) for an UDCD bus
 *
 * @param req - Pointer to a filled out ::SceUdcdDeviceRequest structure
 * @param[in] bus - UDCD bus (default is 2)
 *
 * @return 0 on success, < 0 on error
 */
int ksceUdcdReqRecvInternal(SceUdcdDeviceRequest *req, int bus);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_UDCD_H_ */
