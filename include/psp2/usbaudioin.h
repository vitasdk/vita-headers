/**
 * \usergroup{SceUsbAudio}
 * \usage{psp2/usbaudioin.h,SceUsbAudioIn_stub}
 */


#ifndef _PSP2_USBAUDIOIN_H_
#define _PSP2_USBAUDIOIN_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceUsbAudioInErrorCode {
    SCE_USBAUDIO_IN_ERROR_INVALID_ARGUMENT = 0x803e0001,
    SCE_USBAUDIO_IN_ERROR_DUPLICATE_ID = 0x803e0002,
    SCE_USBAUDIO_IN_ERROR_NO_MEMORY = 0x803e0003,
    SCE_USBAUDIO_IN_ERROR_DEVICE_NOT_FOUND = 0x803e0004,
    SCE_USBAUDIO_IN_ERROR_NOT_SUPPORTED = 0x803e0005,
    SCE_USBAUDIO_IN_ERROR_CANNOT_GET_PORT_OWNERSHIP = 0x803e0006,
    SCE_USBAUDIO_IN_ERROR_PORT_IS_ALREADY_OPENED = 0x803e0007,
    SCE_USBAUDIO_IN_ERROR_PROCESS_HAS_NOT_A_DEVICE_OWNERSHIP = 0x803e0008,
    SCE_USBAUDIO_IN_ERROR_FAILED_TO_READ_STREAM = 0x803e0009,
    SCE_USBAUDIO_IN_ERROR_DEVICE_WAS_HALTED = 0x803e000a,
    SCE_USBAUDIO_IN_ERROR_NO_DATA_TO_READ = 0x803e000b,
    SCE_USBAUDIO_IN_ERROR_FAILED_TO_COPY_BUFFER = 0x803e000c,
    SCE_USBAUDIO_IN_ERROR_FAILED_TO_REQUEST_ISOCHRONOUS = 0x803e000d,
    SCE_USBAUDIO_IN_ERROR_TIMEOUT = 0x803e000e,
    SCE_USBAUDIO_IN_ERROR_PROCESS_CANNOT_OPEN_MORE_DEVICE = 0x803e000f,
} SceUsbAudioInErrorCode;

typedef struct SceUsbAudioInDeviceInfo {
    uint16_t vendor;
    uint16_t product;
    SceUInt32 _reserved[5];
} SceUsbAudioInDeviceInfo;

typedef struct SceUsbAudioInDeviceListItem {
    SceUInt32 device_id;
} SceUsbAudioInDeviceListItem;

/**
 * Open usb audio device
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] device_id - Device id
 * @param[in] bits - Bits per sample. Only 16 allowed
 * @param[in] rate - Bitrate in Hz. Only 48000 allowed
 */
SceInt32 sceUsbAudioInOpenDevice(SceUInt32 device_id, int bits, int rate);

/**
 * Close usb audio device
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] device_id - Device id
 */
SceInt32 sceUsbAudioInCloseDevice(SceUInt32 device_id);

/**
 * Get available audio usb devices
 *
 * @return 0 on success, < 0 on error
 *
 * @param[out] list - pointer to array of SceUsbAudioInDeviceListItem
 * @param[out] device_count - connected device count
 * @param[in] list_size - number of items in SceUsbAudioInDeviceListItem array
 *
 * @note While function accepts up to 127 as list_size it can only return maximum 7 devices
 */
SceInt32 sceUsbAudioInGetDeviceIdList(SceUsbAudioInDeviceListItem* list, SceUInt32* device_count, SceUInt32 list_size);

/**
 * Get usb audio device info
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] device_id - Device id
 * @param[out] info - pointer to SceUsbAudioInDeviceInfo
 */
SceInt32 sceUsbAudioInGetDeviceInformation(SceUInt32 device_id, SceUsbAudioInDeviceInfo* info);

/**
 * Get usb audio device max volume
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] device_id - Device id
 * @param[out] volume - maximum device volume
 *
 * @note You should sceUsbAudioInOpenDevice first to use this function
 */
SceInt32 sceUsbAudioInGetMaxValueOfVolume(SceUInt32 device_id, SceUInt32* volume);

/**
 * Get usb audio device min volume
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] device_id - Device id
 * @param[out] volume - minimum device volume
 *
 * @note You should sceUsbAudioInOpenDevice first to use this function
 */
SceInt32 sceUsbAudioInGetMinValueOfVolume(SceUInt32 device_id, SceUInt32* volume);

/**
 * Set usb audio device volume
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] device_id - Device id
 * @param[in] volume - new device volume
 *
 * @note You should sceUsbAudioInOpenDevice first to use this function
 */
SceInt32 sceUsbAudioInSetCurrentValueOfVolume(SceUInt32 device_id, SceUInt32 volume);

/**
 * Receive sound data from usb device
 *
 * @return 0 on success, < 0 on error
 *
 * @param[in] device_id - Device id
 * @param[out] buffer - buffer for received data. Should be 0x600 bytes in size.
 *
 * @note You should call sceUsbAudioInOpenDevice first to use this function
 * @note Data is in S16_MONO format. Granularity is 768 (thus buffer is 768*2)
 */
SceInt32 sceUsbAudioInInput(SceUInt32 device_id, void* buffer);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_USBAUDIOIN_H_ */
