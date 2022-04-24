/**
 * \usergroup{SceAppUtil}
 * \usage{psp2/apputil.h,SceAppUtil_stub,SCE_SYSMODULE_APPUTIL}
 */


#ifndef _PSP2_APPUTIL_H_
#define _PSP2_APPUTIL_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAppUtilSaveDataRemoveMode {
	SCE_APPUTIL_SAVEDATA_DATA_REMOVE_MODE_DEFAULT = 0,
	SCE_APPUTIL_SAVEDATA_DATA_REMOVE_MODE_NO_SLOT = 1
} SceAppUtilSaveDataDataRemoveMode;

typedef enum SceAppUtilSaveDataSaveMode {
	SCE_APPUTIL_SAVEDATA_DATA_SAVE_MODE_FILE = 0,
	SCE_APPUTIL_SAVEDATA_DATA_SAVE_MODE_DIRECTORY = 2
} SceAppUtilSaveDataDataSaveMode;

typedef enum SceAppUtilErrorCode {
	SCE_APPUTIL_ERROR_PARAMETER                   = 0x80100600,
	SCE_APPUTIL_ERROR_NOT_INITIALIZED             = 0x80100601,
	SCE_APPUTIL_ERROR_NO_MEMORY                   = 0x80100602,
	SCE_APPUTIL_ERROR_BUSY                        = 0x80100603,
	SCE_APPUTIL_ERROR_NOT_MOUNTED                 = 0x80100604,
	SCE_APPUTIL_ERROR_NO_PERMISSION               = 0x80100605,
	SCE_APPUTIL_ERROR_PASSCODE_MISMATCH           = 0x80100606,
	SCE_APPUTIL_ERROR_APPEVENT_PARSE_INVALID_DATA = 0x80100620,
	SCE_APPUTIL_ERROR_SAVEDATA_SLOT_EXISTS        = 0x80100640,
	SCE_APPUTIL_ERROR_SAVEDATA_SLOT_NOT_FOUND     = 0x80100641,
	SCE_APPUTIL_ERROR_SAVEDATA_NO_SPACE_QUOTA     = 0x80100642,
	SCE_APPUTIL_ERROR_SAVEDATA_NO_SPACE_FS        = 0x80100643,
	SCE_APPUTIL_ERROR_DRM_NO_ENTITLEMENT          = 0x80100660,
	SCE_APPUTIL_ERROR_PHOTO_DEVICE_NOT_FOUND      = 0x80100680,
	SCE_APPUTIL_ERROR_MUSIC_DEVICE_NOT_FOUND      = 0x80100685,
	SCE_APPUTIL_ERROR_MOUNT_LIMIT_OVER            = 0x80100686,
	SCE_APPUTIL_ERROR_STACKSIZE_TOO_SHORT         = 0x801006A0
} SceAppUtilErrorCode;

typedef unsigned int SceAppUtilBootAttribute;
typedef unsigned int SceAppUtilAppEventType;
typedef unsigned int SceAppUtilSaveDataSlotId;
typedef unsigned int SceAppUtilSaveDataSlotStatus;
typedef unsigned int SceAppUtilAppParamId;
typedef unsigned int SceAppUtilBgdlStatusType;

typedef struct SceAppUtilBgdlStatus {
	SceAppUtilBgdlStatusType type;
	SceUInt32 addcontNumReady;
	SceUInt32 addcontNumNotReady;
	SceUInt32 licenseReady;
	SceChar8 reserved[28];
} SceAppUtilBgdlStatus;

typedef struct SceAppUtilInitParam {
	SceSize workBufSize;  //!< Buffer size
	uint8_t reserved[60]; //!< Reserved range
} SceAppUtilInitParam;

typedef struct SceAppUtilBootParam {
	SceAppUtilBootAttribute attr;   //!< Boot attribute
	unsigned int appVersion;        //!< App version
	uint8_t reserved[32];           //!< Reserved range
} SceAppUtilBootParam;

typedef struct SceAppUtilSaveDataMountPoint {
	uint8_t data[16];
} SceAppUtilSaveDataMountPoint;

typedef struct SceAppUtilAppEventParam {
	SceAppUtilAppEventType type; //!< Event type
	uint8_t dat[1024];           //!< Event parameter
} SceAppUtilAppEventParam;

typedef struct SceAppUtilMountPoint {
	int8_t data[16]; //!< Mount point
} SceAppUtilMountPoint;

typedef struct SceAppUtilSaveDataSlotEmptyParam {
	SceWChar16 *title;     //!< Title string
	char *iconPath;        //!< Path to icon
	void *iconBuf;         //!< Icon buffer
	SceSize iconBufSize;   //!< Icon buffer size
	uint8_t reserved[32];  //!< Reserved range
} SceAppUtilSaveDataSlotEmptyParam;

typedef struct SceAppUtilSaveDataSlot {
	SceAppUtilSaveDataSlotId id;                  //!< Slot id
	SceAppUtilSaveDataSlotStatus status;          //!< Slot status
	int userParam;                                //!< Param for free usage
	SceAppUtilSaveDataSlotEmptyParam *emptyParam; //!< Settings for empty slot
} SceAppUtilSaveDataSlot;

typedef struct SceAppUtilSaveDataSlotParam {
	SceAppUtilSaveDataSlotStatus status; //!< Status
	SceWChar16 title[32];                //!< Title name
	SceWChar16 subTitle[64];             //!< Subtitle
	SceWChar16 detail[256];              //!< Detail info
	char iconPath[64];                   //!< Icon path
	int userParam;                       //!< User param
	SceSize sizeKB;                      //!< Data size (In KB)
	SceDateTime modifiedTime;            //!< Last modified time
	uint8_t reserved[48];                //!< Reserved range
} SceAppUtilSaveDataSlotParam;

typedef struct SceAppUtilSaveDataSaveItem {
	const char *dataPath;             //!< Path to savedata
	const void *buf;                  //!< Buffer of savedata file
	uint32_t pad;                     //!< Padding
	SceOff offset;                    //!< Offset of savedata file
	int mode;                         //!< Savedata save mode (One of ::SceAppUtilSaveDataSaveMode)
	uint8_t reserved[36];             //!< Reserved range
} SceAppUtilSaveDataSaveItem;

typedef struct SceAppUtilSaveDataFile {
	const char *filePath;
	void *buf;
	SceSize bufSize;
	SceOff offset;
	unsigned int mode;
	unsigned int progDelta;
	uint8_t reserved[32];
} SceAppUtilSaveDataFile;

typedef struct SceAppUtilSaveDataFileSlot {
	unsigned int id;
	SceAppUtilSaveDataSlotParam *slotParam;
	uint8_t reserved[32];
} SceAppUtilSaveDataFileSlot;

typedef struct SceAppUtilSaveDataRemoveItem {
	const char *dataPath;               //!< Path to savedata data
	int mode;                           //!< Savedata remove mode (One of ::SceAppUtilSaveDataRemoveMode)
	uint8_t reserved[36];               //!< Reserved range
} SceAppUtilSaveDataRemoveItem;

typedef struct SceAppUtilStoreBrowseParam {
	unsigned int type;          //!< Store browse type
	const char *id;             //!< Target id
} SceAppUtilStoreBrowseParam;

typedef struct SceAppUtilWebBrowserParam {
	const char *str;            //!< String that's passed to command specified by launchMode
	SceSize strlen;	            //!< Length of str
	unsigned int launchMode;    //!< Browser mode
	unsigned int reserved;      //!< Reserved area
} SceAppUtilWebBrowserParam;

/**
 * Initializes the AppUtil library. Call this before any of the other functions.
 *
 * @param[out] initParam - App init info. Must be initialized with zeros.
 * @param[out] bootParam - App boot info. Must be initialized with zeros.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppUtilInit(SceAppUtilInitParam *initParam, SceAppUtilBootParam *bootParam);

//! Shutdown AppUtil library
int sceAppUtilShutdown();

//! Receive app event
int sceAppUtilReceiveAppEvent(SceAppUtilAppEventParam *eventParam);

//! Parse received app event from LiveArea
int sceAppUtilAppEventParseLiveArea(const SceAppUtilAppEventParam *eventParam, char *buffer);

//! Create savedata slot
int sceAppUtilSaveDataSlotCreate(unsigned int slotId,
	SceAppUtilSaveDataSlotParam *param,
	SceAppUtilSaveDataMountPoint *mountPoint);

//! Delete savedata slot
int sceAppUtilSaveDataSlotDelete(unsigned int slotId,
	SceAppUtilSaveDataMountPoint *mountPoint);

//! Set savedata slot param
int sceAppUtilSaveDataSlotSetParam(unsigned int slotId,
	SceAppUtilSaveDataSlotParam *param,
	SceAppUtilSaveDataMountPoint *mountPoint);

//! Get savedata slot param
int sceAppUtilSaveDataSlotGetParam(unsigned int slotId,
	SceAppUtilSaveDataSlotParam *param,
	SceAppUtilSaveDataMountPoint *mountPoint);

//!< Write savedata files and directories
int sceAppUtilSaveDataDataSave(SceAppUtilSaveDataFileSlot *slot,
	SceAppUtilSaveDataFile *files, unsigned int fileNum,
	SceAppUtilSaveDataMountPoint *mountPoint,
	SceSize *requiredSizeKB);

//!< Delete savedata files
int sceAppUtilSaveDataDataRemove(SceAppUtilSaveDataFileSlot *slot,
	SceAppUtilSaveDataRemoveItem *files, unsigned int fileNum,
	SceAppUtilSaveDataMountPoint *mountPoint);

//! Mount music data
int sceAppUtilMusicMount();

//! Unmount music data
int sceAppUtilMusicUmount();

//! Mount photo data
int sceAppUtilPhotoMount();

//! Unmount photo data
int sceAppUtilPhotoUmount();

//! Get system parameters for int type
int sceAppUtilSystemParamGetInt(unsigned int paramId, int *value);

//! Get application parameters for string type
int sceAppUtilSystemParamGetString(unsigned int paramId,
	SceChar8 *buf, SceSize bufSize);

//! Get application parameters for int type
int sceAppUtilAppParamGetInt(SceAppUtilAppParamId paramId, int *value);

//! Save safe memory
int sceAppUtilSaveSafeMemory(void *buf, SceSize bufSize, SceOff offset);

//! Load safe memory
int sceAppUtilLoadSafeMemory(void *buf, SceSize bufSize, SceOff offset);

//! Launch PSN Store
int sceAppUtilStoreBrowse(SceAppUtilStoreBrowseParam *param);

//! Get background download status
int sceAppUtilBgdlGetStatus(SceAppUtilBgdlStatus *stat);

//! Launch web browser app
int sceAppUtilLaunchWebBrowser(SceAppUtilWebBrowserParam *param);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_APPUTIL_H_ */

