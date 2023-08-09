/**
 * \kernelgroup{SceUsbd}
 * \usage{psp2kern/usbd.h,SceUsbdForDriver_stub}
 */


#ifndef _PSP2KERN_USBD_H_
#define _PSP2KERN_USBD_H_

#include <vitasdk/build_utils.h>
#include <psp2common/types.h>
#include <psp2common/usbd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_USBD_PROBE_SUCCEEDED       (0)
#define SCE_USBD_PROBE_FAILED          (-1)
#define SCE_USBD_ATTACH_SUCCEEDED      (0)
#define SCE_USBD_ATTACH_FAILED         (-1)
#define SCE_USBD_DETACH_SUCCEEDED      (0)
#define SCE_USBD_DETACH_FAILED         (-1)

#define SCE_USBD_MAX_LS_CONTROL_PACKET_SIZE      8
#define SCE_USBD_MAX_FS_CONTROL_PACKET_SIZE      64
#define SCE_USBD_MAX_ISOCHRONOUS_PACKET_SIZE     1023
#define SCE_USBD_MAX_LS_INTERRUPT_PACKET_SIZE    8
#define SCE_USBD_MAX_FS_INTERRUPT_PACKET_SIZE    64
#define SCE_USBD_MAX_BULK_PACKET_SIZE            64

#define SCE_USBD_FEATURE_ENDPOINT_HALT               0x00
#define SCE_USBD_FEATURE_DEVICE_REMOTE_WAKEUP        0x01


typedef struct SceUsbdDriver {
	const char *name;
	int (*probe)(int device_id);
	int (*attach)(int device_id);
	int (*detach)(int device_id);
} SceUsbdDriver;
VITASDK_BUILD_ASSERT_EQ(0x10, SceUsbdDriver);

typedef struct SceUsbdCompositeDriver {
	const char *name;
	int (*probe)(int device_id, SceUsbdEndpointDescriptor* desc); // endpoint descriptor should be interface one
	int (*attach)(int device_id);
	int (*detach)(int device_id);
} SceUsbdCompositeDriver;
VITASDK_BUILD_ASSERT_EQ(0x10, SceUsbdCompositeDriver);

typedef struct SceUsbdDeviceRequest {
	uint8_t bmRequestType;
	uint8_t bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
} SceUsbdDeviceRequest;
VITASDK_BUILD_ASSERT_EQ(8, SceUsbdDeviceRequest);

typedef enum SceUsbdReqtype {
	SCE_USBD_REQTYPE_DIR_BITS                  = 0x80,
	SCE_USBD_REQTYPE_DIR_TO_DEVICE             = 0x00,
	SCE_USBD_REQTYPE_DIR_TO_HOST               = 0x80,
	SCE_USBD_REQTYPE_TYPE_BITS                 = 0x60,
	SCE_USBD_REQTYPE_TYPE_STANDARD             = 0x00,
	SCE_USBD_REQTYPE_TYPE_CLASS                = 0x20,
	SCE_USBD_REQTYPE_TYPE_VENDOR               = 0x40,
	SCE_USBD_REQTYPE_TYPE_RESERVED             = 0x60,
	SCE_USBD_REQTYPE_RECIP_BITS                = 0x1f,
	SCE_USBD_REQTYPE_RECIP_DEVICE              = 0x00,
	SCE_USBD_REQTYPE_RECIP_INTERFACE           = 0x01,
	SCE_USBD_REQTYPE_RECIP_ENDPOINT            = 0x02,
	SCE_USBD_REQTYPE_RECIP_OTHER               = 0x03
} SceUsbdReqtype;

typedef enum SceUsbdRequest {
	SCE_USBD_REQUEST_GET_STATUS                = 0x00,
	SCE_USBD_REQUEST_CLEAR_FEATURE             = 0x01,
	SCE_USBD_REQUEST_SET_FEATURE               = 0x03,
	SCE_USBD_REQUEST_SET_ADDRESS               = 0x05,
	SCE_USBD_REQUEST_GET_DESCRIPTOR            = 0x06,
	SCE_USBD_REQUEST_SET_DESCRIPTOR            = 0x07,
	SCE_USBD_REQUEST_GET_CONFIGURATION         = 0x08,
	SCE_USBD_REQUEST_SET_CONFIGURATION         = 0x09,
	SCE_USBD_REQUEST_GET_INTERFACE             = 0x0a,
	SCE_USBD_REQUEST_SET_INTERFACE             = 0x0b,
	SCE_USBD_REQUEST_SYNCH_FRAME               = 0x0c
} SceUsbdRequest;

typedef struct ksceUsbdIsochPswLen {
	uint16_t len:12;
	uint16_t PSW:4;
} ksceUsbdIsochPswLen;
VITASDK_BUILD_ASSERT_EQ(2, ksceUsbdIsochPswLen);

typedef struct ksceUsbdIsochTransfer {
	void *buffer_base;
	int32_t relative_start_frame;
	int32_t num_packets;
	ksceUsbdIsochPswLen packets[8];
} ksceUsbdIsochTransfer;
VITASDK_BUILD_ASSERT_EQ(0x1C, ksceUsbdIsochTransfer);

/**
 * Register USB driver
 *
 * @return 0 on success, < 0 on error
 *
 * @param driver driver struct
 *
 */
int ksceUsbdRegisterDriver(const SceUsbdDriver *driver);

/**
 * Register USB driver for composite devices
 *
 * @return 0 on success, < 0 on error
 *
 * @param driver driver struct
 *
 */
int ksceUsbdRegisterCompositeLdd(const SceUsbdCompositeDriver *driver);

/**
 * De-register USB driver
 *
 * @return 0 on success, < 0 on error
 *
 * @param driver driver struct
 *
 */
int ksceUsbdUnregisterDriver(const SceUsbdDriver *driver);

/**
 * De-register USB driver for composite devices
 *
 * @return 0 on success, < 0 on error
 *
 * @param driver driver struct
 *
 */
int ksceUsbdUnregisterCompositeLdd(const SceUsbdCompositeDriver *driver);


/**
 * Return usb descriptor
 *
 * @return descriptor data on success, NULL on error
 *
 * @param device_id device id
 * @param start pointer to descriptor to start scanning from (may be NULL)
 * @param type descriptor type
 *
 */
void *ksceUsbdScanStaticDescriptor(SceUID device_id, void *start, SceUsbdDescriptorType type);

/**
 * Open communication pipe to endpoint
 *
 * @return pipe uid on success, < 0 on error
 *
 * @param device_id device id
 * @param endpoint endpoint (may be null for default configuration endpoint)
 *
 */
SceUID ksceUsbdOpenPipe(int device_id, SceUsbdEndpointDescriptor *endpoint);

/**
 * Close communication pipe to endpoint
 *
 * @return 0 on success, < 0 on error
 *
 * @param pipe_id pipe id
 *
 */
int ksceUsbdClosePipe(SceUID pipe_id);

typedef void (*ksceUsbdDoneCallback)(int32_t result, int32_t count, void* arg);
typedef void (*ksceUsbdIsochDoneCallback)(int32_t result, ksceUsbdIsochTransfer *req, void *arg);

/**
 * Transfer data to/from endpoint
 *
 * @return 0 on success, < 0 on error
 *
 * @param pipe_id pipe id
 * @param req transfer request
 * @param buffer data
 * @param cb transfer callback
 * @param user_data userdata to pass to callback
 *
 */
int ksceUsbdControlTransfer(SceUID pipe_id,
	const SceUsbdDeviceRequest *req,
	unsigned char *buffer,
	ksceUsbdDoneCallback cb,
	void *user_data);

/**
 * Transfer data to/from interrupt endpoint
 *
 * @return 0 on success, < 0 on error
 *
 * @param pipe_id pipe id
 * @param buffer data
 * @param length data length
 * @param cb transfer callback
 * @param user_data userdata to pass to callback
 *
 */
int ksceUsbdInterruptTransfer(SceUID pipe_id,
	unsigned char *buffer,
	SceSize length,
	ksceUsbdDoneCallback cb,
	void *user_data);

/**
 * Transfer isochronous data to/from endpoint
 *
 * @return 0 on success, < 0 on error
 *
 * @param pipe_id pipe id
 * @param transfer transfer request
 * @param cb transfer callback
 * @param user_data userdata to pass to callback
 *
 */
int ksceUsbdIsochronousTransfer(SceUID pipe_id,
	ksceUsbdIsochTransfer* transfer,
	ksceUsbdIsochDoneCallback cb,
	void *user_data);

/**
 * Transfer data to/from endpoint
 *
 * @return 0 on success, < 0 on error
 *
 * @param pipe_id pipe id
 * @param buffer data
 * @param length data length
 * @param cb transfer callback
 * @param user_data userdata to pass to callback
 *
 * @note buffer pointer must be 64b aligned
 */
int ksceUsbdBulkTransfer(SceUID pipe_id,
	unsigned char *buffer,
	unsigned int length,
	ksceUsbdDoneCallback cb,
	void *user_data);

/**
 * Transfer data to/from endpoint
 *
 * @return 0 on success, < 0 on error
 *
 * @param pipe_id pipe id
 * @param buffer data
 * @param length data length
 * @param cb transfer callback
 * @param user_data userdata to pass to callback
 *
 * @note buffer pointer must be 64b aligned
 */
int ksceUsbdBulkTransfer2(int pipe_id,
	unsigned char *buffer,
	unsigned int length,
	ksceUsbdDoneCallback cb,
	void *user_data);


/**
 * Get device location
 *
 * @return 0 on success, < 0 on error
 *
 * @param device_id device id
 * @param[out] location device location data (port)
 *
 */
int ksceUsbdGetDeviceLocation(SceUID device_id, uint8_t *location);

int ksceUsbdSuspend(int port);
int ksceUsbdSuspendPhase2(int port, int flag);
int ksceUsbdResume(int port);

int ksceUsbdHostStop(int port);
int ksceUsbdHostStart(int port);

/**
 * Get device speed
 *
 * @return 0 on success, < 0 on error
 *
 * @param device_id device id
 * @param[out] speed device speed
 *
 */
int ksceUsbdGetDeviceSpeed(int device_id, uint8_t *speed);
#define SCE_USBD_DEVICE_SPEED_LS   (0)
#define SCE_USBD_DEVICE_SPEED_FS   (1)
#define SCE_USBD_DEVICE_SPEED_HS   (2)


#define ksceUsbdSetConfiguration(pid, config, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x00; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_CONFIGURATION; \
	_dr.wValue = (config); \
	_dr.wIndex = 0; \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })


#define ksceUsbdClearDeviceFeature(pid, fs, cb, arg) ({  \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x00; \
	_dr.bRequest = SCE_USBD_REQUEST_CLEAR_FEATURE; \
	_dr.wValue = (fs); \
	_dr.wIndex = 0; \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdClearInterfaceFeature(pid, fs, interface, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x01; \
	_dr.bRequest = SCE_USBD_REQUEST_CLEAR_FEATURE; \
	_dr.wValue = (fs); \
	_dr.wIndex = (interface); \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdClearEndpointFeature(pid, fs, endpoint, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x02; \
	_dr.bRequest = SCE_USBD_REQUEST_CLEAR_FEATURE; \
	_dr.wValue = (fs); \
	_dr.wIndex = (endpoint); \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdGetConfiguration(pid, ptr, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x80; \
	_dr.bRequest = SCE_USBD_REQUEST_GET_CONFIGURATION; \
	_dr.wValue = 0; \
	_dr.wIndex = 0; \
	_dr.wLength = 1; \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdGetDescriptor(pid, type, index, lang_id, ptr, len, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x80; \
	_dr.bRequest = SCE_USBD_REQUEST_GET_DESCRIPTOR; \
	_dr.wValue = ((type) << 8) | (index); \
	_dr.wIndex = (lang_id); \
	_dr.wLength = (len); \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdGetInterface(pid, interface, ptr, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x81; \
	_dr.bRequest = SCE_USBD_REQUEST_GET_INTERFACE; \
	_dr.wValue = 0; \
	_dr.wIndex = (interface); \
	_dr.wLength = 1; \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdGetDeviceStatus(pid, ptr, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x80; \
	_dr.bRequest = SCE_USBD_REQUEST_GET_STATUS; \
	_dr.wValue = 0; \
	_dr.wIndex = 0; \
	_dr.wLength = 2; \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdGetInterfaceStatus(pid, interface, ptr, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x81; \
	_dr.bRequest = SCE_USBD_REQUEST_GET_STATUS; \
	_dr.wValue = 0; \
	_dr.wIndex = (interface); \
	_dr.wLength = 2; \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdGetEndpointStatus(pid, endpoint, ptr, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x82; \
	_dr.bRequest = SCE_USBD_REQUEST_GET_STATUS; \
	_dr.wValue = 0; \
	_dr.wIndex = (endpoint); \
	_dr.wLength = 2; \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdSetAddress(pid, address, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x00; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_ADDRESS; \
	_dr.wValue = (address); \
	_dr.wIndex = 0; \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdSetConfiguration(pid, config, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x00; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_CONFIGURATION; \
	_dr.wValue = (config); \
	_dr.wIndex = 0; \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdSetDeviceDescriptor(pid, type, index, lang_id, ptr, len, \
		cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x00; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_DESCRIPTOR; \
	_dr.wValue = ((type) << 8) | (index); \
	_dr.wIndex = (lang_id); \
	_dr.wLength = (len); \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdSetInterfaceDescriptor(pid, type, index, lang_id, ptr, len, \
		cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x01; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_DESCRIPTOR; \
	_dr.wValue = ((type) << 8) | (index); \
	_dr.wIndex = (lang_id); \
	_dr.wLength = (len); \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdSetEndpointDescriptor(pid, type, index, lang_id, ptr, len, \
		cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x02; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_DESCRIPTOR; \
	_dr.wValue = ((type) << 8) | (index); \
	_dr.wIndex = (lang_id); \
	_dr.wLength = (len); \
	ksceUsbdControlTransfer((pid), (&_dr), (ptr), (cb), (arg)); })

#define ksceUsbdSetDeviceFeature(pid, fs, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x00; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_FEATURE; \
	_dr.wValue = (fs); \
	_dr.wIndex = 0; \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdSetInterfaceFeature(pid, fs, interface, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x01; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_FEATURE; \
	_dr.wValue = (fs); \
	_dr.wIndex = (interface); \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdSetEndpointFeature(pid, fs, endpoint, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x02; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_FEATURE; \
	_dr.wValue = (fs); \
	_dr.wIndex = (endpoint); \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdSetInterface(pid, interface, alt_setting, cb, arg) ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x01; \
	_dr.bRequest = SCE_USBD_REQUEST_SET_INTERFACE; \
	_dr.wValue = (alt_setting); \
	_dr.wIndex = (interface); \
	_dr.wLength = 0; \
	ksceUsbdControlTransfer((pid), (&_dr), NULL, (cb), (arg)); })

#define ksceUsbdSynchFrame(pid, endpoint, pfn, cb, arg)  ({ \
	SceUsbdDeviceRequest _dr; \
	_dr.bmRequestType = 0x82; \
	_dr.bRequest = SCE_USBD_REQUEST_SYNCH_FRAME; \
	_dr.wValue = 0; \
	_dr.wIndex = (endpoint); \
	_dr.wLength = 2; \
	ksceUsbdControlTransfer((pid), (&_dr), pfn, (cb), (arg)); })

// OHCI/EHCI completion codes
#define OHCI_CC_NO_ERROR                      0x0
#define OHCI_CC_CRC                           0x1
#define OHCI_CC_BIT_STUFFING                  0x2
#define OHCI_CC_DATA_TOGGLE_MISMATCH          0x3
#define OHCI_CC_STALL                         0x4
#define OHCI_CC_DEVICE_NOT_RESPONDING         0x5
#define OHCI_CC_PID_CHECK_FAILURE             0x6
#define OHCI_CC_UNEXPECTED_PID                0x7
#define OHCI_CC_DATA_OVERRUN                  0x8
#define OHCI_CC_DATA_UNDERRUN                 0x9
#define OHCI_CC_BUFFER_OVERRUN                0xc
#define OHCI_CC_BUFFER_UNDERRUN               0xd
#define OHCI_CC_NOT_ACCESSED1                 0xe
#define OHCI_CC_NOT_ACCESSED2                 0xf
#define EHCI_CC_MISSED_MICRO_FRAME            0x10
#define EHCI_CC_XACT                          0x20
#define EHCI_CC_BABBLE                        0x30
#define EHCI_CC_DATABUF                       0x40
#define EHCI_CC_HALTED                        0x50

// Isochronous transfer(PSW) completion codes
#define USBD_CC_NOERR               0x0
#define USBD_CC_MISSED_MICRO_FRAME  0x1
#define USBD_CC_XACTERR             0x2
#define USBD_CC_BABBLE              0x4
#define USBD_CC_DATABUF             0x8

int ksceUsbd_05073925(SceUID device_id, int* unk1, int* unk2);
int ksceUsbd_7938DAC7(SceUID pipe_id); // clear halt?

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_USBD_H_ */
