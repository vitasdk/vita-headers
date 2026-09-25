/**
 * \usergroup{SceLsdb}
 * \usage{psp2/lsdb.h,SceLsdb_stub}
 */

#ifndef _PSP2_LSDB_H_
#define _PSP2_LSDB_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>
#include <psp2common/kernel/rtc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Errors returned by the FW 3.60 SceLsdb implementation.
 */
typedef enum SceLsdbErrorCode {
	SCE_LSDB_ERROR_OUT_OF_RANGE                    = 0x80101000,
	SCE_LSDB_ERROR_INVALID_ARGUMENT                = 0x80101001,
	SCE_LSDB_ERROR_NO_MEMORY                       = 0x80101002,
	SCE_LSDB_ERROR_INVALID_HANDLE                  = 0x80101003,
	SCE_LSDB_ERROR_DATABASE_CONSTRAINT             = 0x80101004,
	SCE_LSDB_ERROR_NOT_FOUND                       = 0x80101005, //!< No matching database row or no requested change.
	SCE_LSDB_ERROR_INVALID_FILTER                   = 0x80101007, //!< Invalid filter operator/value-type combination.
	SCE_LSDB_ERROR_INVALID_NEW_EVENT_IDENTIFIER    = 0x80101008, //!< Neither title_id/item_id nor row_id identifies a NewEvent row.
	SCE_LSDB_ERROR_REQUIRED_APPINFO_FIELD_MISSING  = 0x80101009, //!< A required AppInfo field, such as TITLE_ID, is missing.
	SCE_LSDB_ERROR_PAGE_NUMBER_OUT_OF_RANGE        = 0x8010100B, //!< A nonnegative insertion page exceeds the current page count.
	SCE_LSDB_ERROR_ICON_POSITION_OCCUPIED          = 0x8010100C, //!< An icon already occupies the page and position.
	SCE_LSDB_ERROR_PROTECTED_APPINFO_KEY           = 0x80101011, //!< SUPPORT_URI and the foreground/background title-ID keys cannot be changed through the masked setter.
	SCE_LSDB_ERROR_DATABASE_LANGUAGE_MISMATCH      = 0x801010F0,
	SCE_LSDB_ERROR_DATABASE_CONFIGURATION_MISMATCH = 0x801010F1,
	SCE_LSDB_ERROR_DATABASE_SCHEMA_TOO_NEW         = 0x801010F2,
	SCE_LSDB_ERROR_DATABASE_VERSION_MISMATCH       = 0x801010F3,
	SCE_LSDB_ERROR_INVALID_DATABASE_VERSION        = 0x801010F4,
	SCE_LSDB_ERROR_DATABASE_UNK_F5                 = 0x801010F5, //!< Its purpose is unknown.
	SCE_LSDB_ERROR_DATABASE_UNK_FE                 = 0x801010FE, //!< Its purpose is unknown.
	SCE_LSDB_ERROR_DATABASE_CORRUPT                = 0x801010FF
} SceLsdbErrorCode;

/** Values accepted by ::sceLsdbOpen on FW 3.60. */
typedef enum SceLsdbOpenMode {
	SCE_LSDB_OPEN_MODE_NORMAL  = 59,  //!< Open and validate the existing AppDB.
	SCE_LSDB_OPEN_MODE_REBUILD = -59  //!< Remove, rebuild, and open the AppDB.
} SceLsdbOpenMode;

/**
 * String object used by SceLsdb.
 *
 * This is the PAF string ABI used on FW 3.60, not a plain NUL-terminated
 * string. A const input string must remain valid until the call returns.
 * SceLsdb does not modify its buffer or use it after the call.
 *
 * A nonempty standalone string returned by SceLsdb owns a writable
 * `length + 1` byte PAF allocation. Release its \a data with ::sce_paf_free,
 * then clear the object. An empty returned string points to shared immutable
 * storage and must not be freed. Strings nested in a reference-counted object
 * are owned by that parent object and must not be freed separately.
 *
 * There is no spare capacity beyond the terminating NUL. The \a reserved word
 * is not a capacity or ownership flag.
 */
typedef struct SceLsdbString {
	char *data;          //!< NUL-terminated string data.
	SceSize length;      //!< String length, excluding the terminating NUL.
	SceUInt32 reserved;  //!< Not read or written on FW 3.60.
} SceLsdbString;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbString); // size is from FW 3.60

/**
 * UTF-16 string object used by localized SceLsdb records.
 *
 * It follows the ::SceLsdbString rules for input lifetime and use, nested
 * strings owned by a parent object, and standalone output-buffer cleanup.
 */
typedef struct SceLsdbUtf16String {
	SceUInt16 *data;
	SceSize length;      //!< Number of UTF-16 code units, excluding the terminator.
	SceUInt32 reserved;  //!< Not read or written on FW 3.60.
} SceLsdbUtf16String;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbUtf16String); // size is from FW 3.60

/**
 * Handle passed as the first argument to AppDB functions that require it.
 *
 * Call ::sceLsdbOpen before ::sceLsdbAppDatabaseInit. Keep the initialized
 * handle valid for every call that uses it, then call ::sceLsdbAppDatabaseEnd
 * when finished. It uses the process's shared AppDB connection; it does not
 * open or own a separate connection.
 */
typedef struct SceLsdbAppDatabase {
	void *token;
} SceLsdbAppDatabase;
VITASDK_BUILD_ASSERT_EQ(0x4, SceLsdbAppDatabase); // size is from FW 3.60

/**
 * Query and change-notification context for the process's shared AppDB.
 *
 * ::sceLsdbQueryContextOpen allocates this internal state and registers an
 * AppInfo observer which sets its change flag. It does not own or open a
 * separate database connection.
 */
typedef struct SceLsdbQueryContext {
	void *state;
} SceLsdbQueryContext;
VITASDK_BUILD_ASSERT_EQ(0x4, SceLsdbQueryContext); // size is from FW 3.60

/**
 * Reference-counted map of AppDB values for one title.
 *
 * The value getters return pointers owned by this object. Keep the object alive
 * until the returned value is no longer used.
 *
 * This type and every two-word `SceLsdb*Ref` type in this header use the FW
 * 3.60 PAF shared-reference ABI. An output object transfers one strong
 * reference to the caller. The object and its nested values remain mutable
 * while that reference is held; mutations are visible through every other
 * reference to the same object.
 *
 * A newly returned reference has a 16-byte PAF-allocated control block. It
 * stores the object pointer, strong-reference count, weak-reference count, and
 * deleter at byte offsets 0, 4, 8, and 12, initially using counts 1 and 1.
 * Copying a nonempty reference requires an atomic increment of the strong
 * count. Releasing it requires an atomic decrement; when that count reaches
 * zero, invoke the deleter on the object, decrement the weak count, and free
 * the control block with ::sce_paf_free when the weak count reaches zero. Then
 * clear both words in the holder. An empty reference has a NULL control block
 * and needs no release. Never free the object, its nested values, or the
 * control block directly. A structure assignment or `memcpy` does not
 * increment the reference count. Releasing either copy can free an object
 * still used by the other copy; releasing both can free it twice.
 *
 * SceLsdb exports no generic C retain/release entry point for this or the other
 * reference types, so their callers must use a PAF-compatible
 * shared-reference wrapper.
 */
typedef struct SceLsdbAppInfo {
	void *data;
	void *control;
} SceLsdbAppInfo;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbAppInfo); // size is from FW 3.60

/**
 * Extended-memory modes returned by ::sceLsdbGetExtendedMemoryMode.
 *
 * On FW 3.60, these select additional game main RAM, not CDRAM. The values
 * identify modes; they are not sizes in bytes.
 */
typedef enum SceLsdbExtendedMemoryMode {
	SCE_LSDB_EXTENDED_MEMORY_MODE_DEFAULT = 0, //!< No additional memory requested by this setting.
	SCE_LSDB_EXTENDED_MEMORY_MODE_29_MIB  = 1, //!< Request 29 MiB of additional main RAM.
	SCE_LSDB_EXTENDED_MEMORY_MODE_77_MIB  = 2, //!< Request 77 MiB of additional main RAM.
	SCE_LSDB_EXTENDED_MEMORY_MODE_109_MIB = 3  //!< Request 109 MiB of additional main RAM.
} SceLsdbExtendedMemoryMode;

/** AppInfo operation reported to an ::SceLsdbAppInfoObserverCallback. */
typedef enum SceLsdbAppInfoEventType {
	SCE_LSDB_APP_INFO_EVENT_INSERT_APPLICATION = 0, //!< Follows ::sceLsdbInsertApplication.
	SCE_LSDB_APP_INFO_EVENT_DELETE_TITLE_DATA   = 1, //!< Follows ::sceLsdbDeleteTitleData.
	SCE_LSDB_APP_INFO_EVENT_UPDATE_APPLICATION = 2, //!< Follows ::sceLsdbUpdateApplication.
	SCE_LSDB_APP_INFO_EVENT_UPDATE_APP_INFO     = 3  //!< Follows AppInfo-only refresh or masked-update operations.
} SceLsdbAppInfoEventType;

/**
 * AppInfo observer callback for the calling process.
 *
 * Do not release \a app_info. It remains valid only for the duration of the
 * callback. The callback runs synchronously on the thread performing the
 * database operation while SceLsdb holds its observer-list lock. It must not
 * register or unregister observers or invoke another operation which calls
 * AppInfo observers. FW 3.60 SceShell performs a read-only icon query from
 * this callback.
 */
typedef void (*SceLsdbAppInfoObserverCallback)(SceLsdbAppInfoEventType event_type, const SceLsdbAppInfo *app_info, void *user_data);

/**
 * Storage for one AppInfo observer in the calling process.
 *
 * Initialize both fields to zero before the first registration. SceLsdb keeps
 * the address of this object, so it must remain allocated at the same address
 * until ::sceLsdbUnregisterAppInfoObserver returns. It is not a
 * reference-counted object.
 */
typedef struct SceLsdbAppInfoObserver {
	SceLsdbAppInfoObserverCallback callback;
	void *user_data;
} SceLsdbAppInfoObserver;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbAppInfoObserver); // size is from FW 3.60

/**
 * PAF vector of ::SceLsdbAppInfo objects.
 *
 * An output vector owns its data allocation and every reference it contains.
 * Release each element according to the shared-reference rules above, then
 * release \a data with ::sce_paf_free and clear the vector.
 */
typedef struct SceLsdbAppInfoArray {
	SceLsdbAppInfo *data;
	SceSize count;
	SceSize capacity;
} SceLsdbAppInfoArray;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbAppInfoArray); // size is from FW 3.60

/**
 * PAF vector of signed 32-bit values used by the AppDB page operations.
 * Release an output vector's \a data with ::sce_paf_free, then clear it.
 */
typedef struct SceLsdbInt32Array {
	SceInt32 *data;
	SceSize count;
	SceSize capacity;
} SceLsdbInt32Array;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbInt32Array); // size is from FW 3.60

/**
 * PAF vector of ::SceLsdbString objects.
 *
 * For an output vector, release every nonempty standalone string buffer, then
 * release \a data with ::sce_paf_free and clear the vector.
 */
typedef struct SceLsdbStringArray {
	SceLsdbString *data;
	SceSize count;
	SceSize capacity;
} SceLsdbStringArray;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbStringArray); // size is from FW 3.60

/** One row of tbl_appinfo_page. */
typedef struct SceLsdbPageInfo {
	SceLsdbString theme_file;
	SceUInt32 background_color;
	SceUInt32 texture_width;
	SceUInt32 texture_height;
	SceUInt32 image_width;
	SceUInt32 image_height;
	SceUInt32 reserved01; //!< Low 24-bit theme color and bit-24 flag used by FW 3.60 themes.
} SceLsdbPageInfo;
VITASDK_BUILD_ASSERT_EQ(0x24, SceLsdbPageInfo); // size is from FW 3.60

/**
 * Reference-counted AppDB page-information object.
 * See ::SceLsdbAppInfo for the shared-reference ownership and cleanup rules.
 */
typedef struct SceLsdbPageInfoRef {
	SceLsdbPageInfo *object;
	void *control;
} SceLsdbPageInfoRef;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbPageInfoRef); // size is from FW 3.60

/**
 * PAF vector of ::SceLsdbPageInfoRef objects. An output vector owns its
 * data allocation and every strong reference it contains.
 */
typedef struct SceLsdbPageInfoRefArray {
	SceLsdbPageInfoRef *data;
	SceSize count;
	SceSize capacity;
} SceLsdbPageInfoRefArray;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbPageInfoRefArray); // size is from FW 3.60

/** Information associated with an icon on a special negative page. */
typedef struct SceLsdbSpecialPageInfo {
	SceLsdbStringArray title_ids; //!< Type-zero icon title IDs associated with this special page by Shell.
	SceUInt32 reserved;          //!< Not initialized or accessed on FW 3.60.
	SceSize child_count;          //!< Number of icon rows on the special page.
	SceInt32 page_no;             //!< Special page number from -20000000 through -10000001.
} SceLsdbSpecialPageInfo;
VITASDK_BUILD_ASSERT_EQ(0x18, SceLsdbSpecialPageInfo); // size is from FW 3.60

/**
 * Reference-counted ::SceLsdbSpecialPageInfo object.
 * See ::SceLsdbAppInfo for the shared-reference ownership and cleanup rules.
 */
typedef struct SceLsdbSpecialPageInfoRef {
	SceLsdbSpecialPageInfo *object;
	void *control;
} SceLsdbSpecialPageInfoRef;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbSpecialPageInfoRef); // size is from FW 3.60

/** Known values of ::SceLsdbIconInfo::type on FW 3.60. */
typedef enum SceLsdbIconType {
	SCE_LSDB_ICON_TYPE_APPLICATION = 0, //!< Application bubble; used by AppInfo-filtered title queries.
	SCE_LSDB_ICON_TYPE_FOLDER = 5, //!< Folder bubble/layout category.
	SCE_LSDB_ICON_TYPE_POWER  = 6  //!< Built-in power bubble/layout category.
} SceLsdbIconType;

/** Known values of ::SceLsdbIconInfo::icon0_type on FW 3.60. */
typedef enum SceLsdbIcon0Type {
	SCE_LSDB_ICON0_TYPE_FOLDER = 7, //!< Folder icon0 source classification.
	SCE_LSDB_ICON0_TYPE_POWER  = 8  //!< Built-in power icon source classification.
} SceLsdbIcon0Type;

/**
 * One row of tbl_appinfo_icon.
 *
 * \a type selects the icon's database/layout category. \a icon0_type is a
 * separate metadata classification for the icon0 source; it does not select
 * path storage versus BLOB storage or describe the image encoding. FW 3.60
 * also uses values 1 through 4, but their individual meanings are unknown.
 *
 * The table also contains five reserved columns which are not represented as
 * five direct structure members. For a folder row, `reserved01` is its
 * associated special negative child-page number, as returned by
 * ::sceLsdbGetFolderPageNosByTitle. It also serves as the numeric selector
 * accepted by ::sceLsdbGetIconInfoById.
 * `reserved02` is an alternate icon path which can override \a icon_path when a
 * query requests it. No FW 3.60 reader or writer for `reserved03` or
 * `reserved04` was found. `reserved05` stores a serialized, rendered PAF icon
 * cache and is returned by ::sceLsdbGetIconReservedBlob.
 *
 * The source icon remains a path in \a icon_path, or in `reserved02` when an
 * alternate path is selected. The `reserved05` blob is generated after the
 * source image is decoded and rendered; it is not a copy of `icon0.png`. The
 * path and rendered-cache BLOB can coexist in the same row.
 *
 * \a status is an integer stored and updated separately. None of the FW 3.60
 * code examined during this analysis interprets its value, and database
 * recovery does not copy it; its purpose and valid values are unknown.
 */
typedef struct SceLsdbIconInfo {
	SceInt64 row_id; //!< SQLite row ID; this is distinct from `reserved01`.
	SceInt32 position; //!< Position within the containing page.
	SceLsdbString title; //!< Localized bubble title stored in the icon table.
	SceLsdbString icon_path; //!< Source-image path.
	SceInt32 type; //!< One of the known ::SceLsdbIconType values, or another FW-defined value.
	SceLsdbString title_id;
	SceInt32 icon0_type; //!< One of the known ::SceLsdbIcon0Type values, or another FW-defined value.
	SceLsdbString command;
	SceInt32 parental_lock_level;
	SceInt32 status; //!< Stored icon status; its purpose and valid values are unknown.
	SceLsdbSpecialPageInfoRef special_page; //!< Derived special-page relationship, when present.
} SceLsdbIconInfo;
VITASDK_BUILD_ASSERT_EQ(0x58, SceLsdbIconInfo); // size is from FW 3.60

/**
 * Reference-counted AppDB icon-information object.
 * See ::SceLsdbAppInfo for the shared-reference ownership and cleanup rules.
 */
typedef struct SceLsdbIconInfoRef {
	SceLsdbIconInfo *object;
	void *control;
} SceLsdbIconInfoRef;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbIconInfoRef); // size is from FW 3.60

/**
 * PAF vector of ::SceLsdbIconInfoRef objects. An output vector owns its
 * data allocation and every strong reference it contains.
 */
typedef struct SceLsdbIconInfoRefArray {
	SceLsdbIconInfoRef *data;
	SceSize count;
	SceSize capacity;
} SceLsdbIconInfoRefArray;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbIconInfoRefArray); // size is from FW 3.60

/**
 * Reference-counted vector of ::SceLsdbIconInfoRef objects.
 * See ::SceLsdbAppInfo for the shared-reference ownership and cleanup rules.
 */
typedef struct SceLsdbIconInfoRefArrayRef {
	SceLsdbIconInfoRefArray *object;
	void *control;
} SceLsdbIconInfoRefArrayRef;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbIconInfoRefArrayRef); // size is from FW 3.60

/**
 * PAF vector containing one ::SceLsdbIconInfoRefArrayRef for each requested
 * AppDB page.
 */
typedef struct SceLsdbIconInfoRefArrayRefArray {
	SceLsdbIconInfoRefArrayRef *data;
	SceSize count;
	SceSize capacity;
} SceLsdbIconInfoRefArrayRefArray;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbIconInfoRefArrayRefArray); // size is from FW 3.60

/** Field-selection bits accepted by ::sceLsdbUpdateIconInfo. */
typedef enum SceLsdbIconInfoUpdateFlag {
	SCE_LSDB_ICON_INFO_UPDATE_TITLE               = 0x00000001, //!< Update ::SceLsdbIconInfo::title.
	SCE_LSDB_ICON_INFO_UPDATE_ICON_PATH           = 0x00000002, //!< Update ::SceLsdbIconInfo::icon_path.
	SCE_LSDB_ICON_INFO_UPDATE_ICON0_TYPE          = 0x00000004, //!< Update ::SceLsdbIconInfo::icon0_type.
	SCE_LSDB_ICON_INFO_UPDATE_COMMAND             = 0x00000008, //!< Update ::SceLsdbIconInfo::command.
	SCE_LSDB_ICON_INFO_UPDATE_PARENTAL_LOCK_LEVEL = 0x00000010, //!< Update ::SceLsdbIconInfo::parental_lock_level.
	SCE_LSDB_ICON_INFO_UPDATE_STATUS              = 0x00000020, //!< Update ::SceLsdbIconInfo::status.
	SCE_LSDB_ICON_INFO_UPDATE_RENDERED_ICON_BLOB  = 0x40000000, //!< Update `reserved05` from the supplied byte buffer.
	SCE_LSDB_ICON_INFO_UPDATE_ALTERNATE_ICON_PATH = 0x80000000 //!< Update `reserved02` from ::SceLsdbIconInfo::icon_path.
} SceLsdbIconInfoUpdateFlag;

typedef enum SceLsdbDbBlobCallbackPhase {
	SCE_LSDB_DB_BLOB_CALLBACK_PHASE_ACQUIRE = 0,
	SCE_LSDB_DB_BLOB_CALLBACK_PHASE_RELEASE = 1
} SceLsdbDbBlobCallbackPhase;

/**
 * Callback used by a database blob to acquire and release its database handle.
 *
 * \a phase is one of ::SceLsdbDbBlobCallbackPhase. On FW 3.60, when acquiring
 * the handle, \a mode is 1 for reading and 0 for writing. When releasing it,
 * \a mode is 1 after a read or a failed write and 0 after a successful write.
 */
typedef int (*SceLsdbDbBlobCallback)(SceInt32 phase, SceInt32 mode, void *user_data, void **database_handle);

/** Database location and lifetime callback held by a ::SceLsdbDbBlob. */
typedef struct SceLsdbDbBlobConfig {
	SceUInt32 type_tag; //!< Set to 0x102 on FW 3.60.
	SceLsdbString database_name;
	SceLsdbString table_name;
	SceLsdbString column_name;
	SceInt64 row_id;
	SceBool writable;
	SceLsdbDbBlobCallback callback;
	void *user_data;
} __attribute__((packed, aligned(4))) SceLsdbDbBlobConfig;
VITASDK_BUILD_ASSERT_EQ(0x3C, SceLsdbDbBlobConfig); // size is from FW 3.60

/**
 * Database-backed PAF stream returned by the blob accessors.
 *
 * The database and blob handles are acquired only when needed. Reads and
 * writes advance the stream's current byte position; seeks change it.
 */
typedef struct SceLsdbDbBlob {
	void *vtable; //!< Internal FW 3.60 PAF stream virtual-function table.
	SceUInt32 reserved; //!< Not initialized on FW 3.60.
	SceUInt8 mutex[0x20]; //!< Internal PAF mutex.
	SceLsdbDbBlobConfig *config;
	void *database_handle;
	void *blob_handle;
	SceSize position;
} SceLsdbDbBlob;
VITASDK_BUILD_ASSERT_EQ(0x38, SceLsdbDbBlob); // size is from FW 3.60

/**
 * Reference-counted database blob returned by SceLsdb.
 * See ::SceLsdbAppInfo for the shared-reference ownership and cleanup rules.
 */
typedef struct SceLsdbDbBlobRef {
	SceLsdbDbBlob *object;
	void *control;
} SceLsdbDbBlobRef;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbDbBlobRef); // size is from FW 3.60

#define SCE_LSDB_THEME_PAGE_LAYOUT_COUNT        10
#define SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_COUNT 20
#define SCE_LSDB_THEME_LOCALIZED_STRING_COUNT   20

/** Fields parsed from one `BackgroundParam` entry in a Shell theme. */
typedef struct SceLsdbThemePageLayout {
	SceLsdbString image_file_path; //!< `m_imageFilePath`, relative to ::SceLsdbThemeLayout::theme_root_path.
	SceLsdbString thumbnail_file_path; //!< `m_thumbnailFilePath`; used by Shell but ignored by SceLsdb.
	SceInt32 wave_type; //!< `m_waveType`, stored in ::SceLsdbPageInfo::background_color.
	SceUInt32 font_color; //!< `m_fontColor`, stored in the low 24 bits of ::SceLsdbPageInfo::reserved01.
	SceUInt8 font_shadow; //!< `m_fontShadow`; nonzero sets bit 24 of ::SceLsdbPageInfo::reserved01.
	SceUInt8 padding[3];
} SceLsdbThemePageLayout;
VITASDK_BUILD_ASSERT_EQ(0x24, SceLsdbThemePageLayout); // size is from FW 3.60

/** One `IconParam` entry parsed from a Shell theme. */
typedef struct SceLsdbThemeSystemIconLayout {
	SceLsdbString icon_file_path; //!< `m_iconFilePath`, relative to ::SceLsdbThemeLayout::theme_root_path.
	SceInt32 page_position; //!< `m_pagePos`; used by Shell but ignored by SceLsdb.
	SceInt32 icon_position; //!< `m_iconPos`; used by Shell but ignored by SceLsdb.
} SceLsdbThemeSystemIconLayout;
VITASDK_BUILD_ASSERT_EQ(0x14, SceLsdbThemeSystemIconLayout); // size is from FW 3.60

/** Indices used by ::SceLsdbThemeLayout::system_icon_layouts on FW 3.60. */
typedef enum SceLsdbThemeSystemIconLayoutIndex {
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_BROWSER       = 0,  //!< `m_browser`; NPXS10003.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_VIDEO         = 1,  //!< `m_video`; NPXS10010.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_MUSIC         = 2,  //!< `m_music`; NPXS10009.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_PS3_LINK      = 3,  //!< `m_ps3Link`; NPXS10012.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_PARTY         = 4,  //!< `m_party`; NPXS10001.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_TROPHY        = 5,  //!< `m_trophy`; NPXS10008.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_MAP           = 6,  //!< `m_map`; NPXS10005.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_NEAR          = 7,  //!< `m_near`; NPXS10000.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_HOST_COLLABO  = 8,  //!< `m_hostCollabo`; NPXS10026.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_WELCOME_PARK  = 9,  //!< `m_welcomePark`; NPXS10007.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_PS4_LINK      = 10, //!< `m_ps4Link`; NPXS10013 or NPXS10098.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_FRIEND        = 11, //!< `m_friend`; NPXS10006.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_EMAIL         = 12, //!< `m_email`; NPXS10072.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_CALENDAR      = 13, //!< `m_calendar`; NPXS10091.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_STORE         = 14, //!< `m_store`; SceLsdb maps NPXS10002 and Shell maps NPXS10034.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_MESSAGE       = 15, //!< `m_message`; NPXS10014.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_PARENTAL      = 16, //!< `m_parental`; NPXS10094.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_CAMERA        = 17, //!< `m_camera`; NPXS10004.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_SETTINGS      = 18, //!< `m_settings`; NPXS10015.
	SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_POWER         = 19  //!< `m_power`; the icon row whose type is 6.
} SceLsdbThemeSystemIconLayoutIndex;

/** Fields selected by ::sceLsdbUpdateThemeLayout. */
typedef enum SceLsdbThemeLayoutUpdateFlag {
	SCE_LSDB_THEME_LAYOUT_UPDATE_SYSTEM_ICONS = 0x1,
	SCE_LSDB_THEME_LAYOUT_UPDATE_PAGES        = 0x2
} SceLsdbThemeLayoutUpdateFlag;

/** Selected and per-language strings parsed from a Shell theme. */
typedef struct SceLsdbLocalizedThemeStrings {
	SceLsdbUtf16String selected; //!< String selected by Shell for the current language.
	SceLsdbUtf16String localized[SCE_LSDB_THEME_LOCALIZED_STRING_COUNT]; //!< Values stored for language indices 0 through 19.
} SceLsdbLocalizedThemeStrings;
VITASDK_BUILD_ASSERT_EQ(0xFC, SceLsdbLocalizedThemeStrings); // size is from FW 3.60

/** `StartScreenProperty` fields parsed from a Shell theme. */
typedef struct SceLsdbThemeStartScreenLayout {
	SceLsdbString file_path;
	SceInt32 date_layout;
	SceUInt32 date_color;
	SceUInt32 notification_background_color;
	SceUInt32 notification_border_color;
	SceUInt32 notification_font_color;
} SceLsdbThemeStartScreenLayout;
VITASDK_BUILD_ASSERT_EQ(0x20, SceLsdbThemeStartScreenLayout); // size is from FW 3.60

/** `InfomationBarProperty` fields parsed from a Shell theme. */
typedef struct SceLsdbThemeInformationBarLayout {
	SceUInt32 bar_color;
	SceUInt32 indicator_color;
	SceUInt32 notice_font_color;
	SceUInt32 notice_glow_color;
	SceLsdbString no_notice_file_path;
	SceLsdbString new_notice_file_path;
} SceLsdbThemeInformationBarLayout;
VITASDK_BUILD_ASSERT_EQ(0x28, SceLsdbThemeInformationBarLayout); // size is from FW 3.60

/**
 * Shell theme-layout object read by ::sceLsdbUpdateThemeLayout.
 *
 * ::sceLsdbUpdateThemeLayout reads only the root path, page layouts, and
 * system-icon layouts. Shell uses the later fields to construct the arguments
 * passed to ::sceLsdbReplaceTheme.
 */
typedef struct SceLsdbThemeLayout {
	SceLsdbString theme_root_path;
	SceInt32 package_flag; //!< `package` attribute from the `theme` element; either 0 or 1.
	SceLsdbThemePageLayout page_layouts[SCE_LSDB_THEME_PAGE_LAYOUT_COUNT];
	SceLsdbString background_music_file_path; //!< `m_bgmFilePath`; used by Shell but ignored by SceLsdb.
	SceLsdbString base_page_file_path; //!< `m_basePageFilePath`; used by Shell but ignored by SceLsdb.
	SceLsdbString current_page_file_path; //!< `m_curPageFilePath`; used by Shell but ignored by SceLsdb.
	SceLsdbThemeSystemIconLayout system_icon_layouts[SCE_LSDB_THEME_SYSTEM_ICON_LAYOUT_COUNT];
	SceLsdbThemeStartScreenLayout start_screen;
	SceLsdbThemeInformationBarLayout information_bar;
	SceUInt32 content_version;
	SceLsdbLocalizedThemeStrings localized_titles;
	SceLsdbLocalizedThemeStrings localized_providers;
	SceLsdbString package_image_file_path;
	SceLsdbString start_preview_file_path;
	SceLsdbString home_preview_file_path;
	SceLsdbString format_version; //!< `format-ver` attribute from the `theme` element.
	SceInt32 parsed_format_version; //!< Numeric form of a format_version.
	SceRtcTick last_modified_time;
} SceLsdbThemeLayout;
VITASDK_BUILD_ASSERT_EQ(0x5B0, SceLsdbThemeLayout); // size is from FW 3.60

/**
 * Reference-counted shell theme-layout object.
 * See ::SceLsdbAppInfo for the shared-reference ownership and cleanup rules.
 */
typedef struct SceLsdbThemeLayoutRef {
	SceLsdbThemeLayout *object;
	void *control;
} SceLsdbThemeLayoutRef;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbThemeLayoutRef); // size is from FW 3.60

/** One localized row of tbl_theme. */
typedef struct SceLsdbThemeInfo {
	void *vtable; //!< Internal FW 3.60 Shell theme-information virtual-function table; SceLsdb leaves it untouched.
	SceLsdbString theme_id;
	SceInt32 type; //!< Must be 100 when passed to ::sceLsdbReplaceTheme on FW 3.60.
	SceLsdbString package_image_file_path;
	SceLsdbString home_preview_file_path;
	SceLsdbString start_preview_file_path;
	SceLsdbUtf16String title;
	SceLsdbUtf16String provider;
	SceUInt32 content_version;
	SceUInt32 padding;
	SceRtcTick last_modified_time;
	SceSize size;
} __attribute__((packed, aligned(4))) SceLsdbThemeInfo;
VITASDK_BUILD_ASSERT_EQ(0x64, SceLsdbThemeInfo); // size is from FW 3.60

typedef enum SceLsdbValueType {
	SCE_LSDB_VALUE_TYPE_INT64  = 0,
	SCE_LSDB_VALUE_TYPE_STRING = 1
} SceLsdbValueType;

/**
 * Integer-or-string value stored in tbl_appinfo or tbl_config.
 *
 * A string output owns the ::SceLsdbString object addressed by `data.string`
 * as well as its nonempty buffer. Release the buffer according to the
 * ::SceLsdbString rules, release the object with ::sce_paf_free, and clear the
 * value. An integer output owns no allocation. FW 3.60 reuses an existing
 * string object when an output value already has string type.
 */
typedef struct SceLsdbValue {
	SceInt32 type; //!< One of ::SceLsdbValueType.
	union {
		SceInt64 int64;
		SceLsdbString *string;
	} data;
} SceLsdbValue;
VITASDK_BUILD_ASSERT_EQ(0x10, SceLsdbValue); // size is from FW 3.60

/**
 * PAF vector of ::SceLsdbValue objects. An output vector owns its data
 * allocation and the string object and buffer owned by each string element.
 */
typedef struct SceLsdbValueArray {
	SceLsdbValue *data;
	SceSize count;
	SceSize capacity;
} SceLsdbValueArray;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbValueArray); // size is from FW 3.60

/** Comparison performed by an ::SceLsdbAppInfoFilter node. */
typedef enum SceLsdbFilterOperator {
	SCE_LSDB_FILTER_OPERATOR_EQUAL         = 0, //!< Compare for equality.
	SCE_LSDB_FILTER_OPERATOR_PREFIX        = 1, //!< Match a string prefix using SQL LIKE with escaping.
	SCE_LSDB_FILTER_OPERATOR_NOT_EQUAL     = 2, //!< Compare for inequality.
	SCE_LSDB_FILTER_OPERATOR_BITMASK_EQUAL = 3  //!< Test `(storedValue & mask) == value` for integer values.
} SceLsdbFilterOperator;

/**
 * One condition used to filter AppInfo records.
 *
 * Values within one node are joined with OR. Nodes linked through \a next are
 * joined with AND. An empty \a values array tests only whether \a key exists.
 * The prefix operator accepts string values, while the bit-mask operator
 * accepts integer values and uses \a mask.
 */
typedef struct SceLsdbAppInfoFilter {
	SceUInt32 key;                         //!< FNV-1a hash of the AppInfo key.
	SceLsdbValueArray values;              //!< Values to compare against.
	SceUInt32 reserved;                    //!< Ignored on FW 3.60.
	SceInt32 operation;                    //!< One of ::SceLsdbFilterOperator.
	SceUInt64 mask;                        //!< Mask used by ::SCE_LSDB_FILTER_OPERATOR_BITMASK_EQUAL.
	const struct SceLsdbAppInfoFilter *next;
} __attribute__((packed, aligned(4))) SceLsdbAppInfoFilter;
VITASDK_BUILD_ASSERT_EQ(0x24, SceLsdbAppInfoFilter); // size is from FW 3.60

/** Flags accepted by the filtered-title queries. */
typedef enum SceLsdbFilterFlags {
	SCE_LSDB_FILTER_FLAG_APPINFO_ONLY                   = 0x1, //!< Query tbl_appinfo without requiring an icon record.
	SCE_LSDB_FILTER_FLAG_INCLUDE_PAGE_MINUS_100000000   = 0x2, //!< Do not exclude icon records on page -100000000.
	SCE_LSDB_FILTER_FLAG_OMIT_ICON_TITLE_SORT           = 0x4  //!< Omit the icon-title ORDER BY clause.
} SceLsdbFilterFlags;

/**
 * NewEvent change-notification wrapper for the calling process.
 *
 * This object does not own a separate database connection. Open allocates a
 * four-byte atomic flag and registers it with the process's shared NewEvent
 * manager; any NewEvent change sets the flag to one.
 */
typedef struct SceLsdbNewEventDatabase {
	SceUInt32 *notification_flag;
} SceLsdbNewEventDatabase;
VITASDK_BUILD_ASSERT_EQ(0x4, SceLsdbNewEventDatabase); // size is from FW 3.60

/**
 * Selector accepted by the NewEvent update and deletion operations.
 *
 * A selector uses either both \a title_id and \a item_id, or a nonzero \a row_id.
 * A nonzero row ID takes precedence when both forms are supplied.
 */
typedef struct SceLsdbNewEventSelector {
	SceLsdbString title_id;
	SceLsdbString item_id;
	SceInt64 row_id;
} SceLsdbNewEventSelector;
VITASDK_BUILD_ASSERT_EQ(0x20, SceLsdbNewEventSelector); // size is from FW 3.60

/**
 * One row of the FW 3.60 tbl_newEvent database.
 *
 * The action type is stored as two 32-bit words in the ABI. It must not be
 * treated as a contiguous SceUInt64 field.
 *
 * String and icon-data inputs must remain valid until an insert or update
 * call returns; they are not used afterwards.
 * A standalone object filled by ::sceLsdbGetNewEvent or
 * ::sceLsdbGetFirstPopupNewEvent owns each nonempty string buffer and must
 * release them according to the ::SceLsdbString rules. A NewEvent held by a
 * ::SceLsdbNewEventRef instead owns its nested strings through the parent
 * reference; do not release them separately.
 */
typedef struct SceLsdbNewEvent {
	SceLsdbString title_id;
	SceLsdbString item_id;
	SceInt64 row_id;
	SceInt64 message_type; //!< Values at least 80 are eligible for automatic pruning and selective deletion.
	SceUInt32 action_type_low;
	SceUInt8 new_flag;
	SceUInt8 popup_flag; //!< Nonzero requests a sequenced popup number; reads convert popup_no to 0 or 1.
	SceUInt8 padding[2];
	SceLsdbString icon_path;
	void *icon_data; //!< Input image bytes; query operations leave this NULL.
	SceSize icon_data_size; //!< Input byte count, or stored BLOB length on output.
	SceLsdbString message_args[9];
	SceLsdbString title;
	SceLsdbString description;
	SceUInt32 exec_mode;
	SceLsdbString exec_title_id;
	SceLsdbString exec_argument;
	SceLsdbString update_time;
	SceInt32 sound_id;
	float sound_volume;
	SceUInt32 hash; //!< Randomized on insertion and incremented by field updates.
	SceUInt32 action_type_high; //!< High word of the stored 64-bit action type; derived during insertion.
} SceLsdbNewEvent;
VITASDK_BUILD_ASSERT_EQ(0x100, SceLsdbNewEvent); // size is from FW 3.60

/**
 * Reference-counted ::SceLsdbNewEvent object.
 * See ::SceLsdbAppInfo for the shared-reference ownership and cleanup rules.
 */
typedef struct SceLsdbNewEventRef {
	SceLsdbNewEvent *object;
	void *control;
} SceLsdbNewEventRef;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbNewEventRef); // size is from FW 3.60

/**
 * PAF vector of ::SceLsdbNewEventRef objects. An output vector owns its
 * data allocation and every strong reference it contains.
 */
typedef struct SceLsdbNewEventRefArray {
	SceLsdbNewEventRef *data;
	SceSize count;
	SceSize capacity;
} SceLsdbNewEventRefArray;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbNewEventRefArray); // size is from FW 3.60

/** Field-selection bits accepted by ::sceLsdbUpdateNewEvents. */
typedef enum SceLsdbNewEventUpdateFlag {
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_ICON_PATH   = 0x00000001, //!< Compare and update icon_path.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_ICON_DATA   = 0x00000002, //!< Compare and update icon_data.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_MESSAGE     = 0x00000004, //!< Compare and update message_type and message_args.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_ACTION_TYPE = 0x00000008, //!< Compare action_type_low and store its signed 64-bit form.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_TITLE       = 0x00000010, //!< Compare and update title.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_DESCRIPTION = 0x00000020, //!< Compare and update description.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_EXECUTION   = 0x00000040, //!< Compare and update exec_mode, exec_title_id, and exec_argument.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_NEW_FLAG    = 0x00000080, //!< Compare and update new_flag.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_TIME        = 0x00000100, //!< Compare and update update_time.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_SOUND       = 0x00000200, //!< Compare and update sound_id and sound_volume.
	SCE_LSDB_NEW_EVENT_UPDATE_FLAG_POPUP       = 0x00000400  //!< Compare popup_flag and assign popup_no.
} SceLsdbNewEventUpdateFlag;

/** Start and end RTC ticks used by ::sceLsdbIsCurrentTimeInRange. */
typedef struct SceLsdbTimeRange {
	SceRtcTick start; //!< Inclusive lower bound unless the caller requests an end-only check.
	SceRtcTick end; //!< Inclusive upper bound.
} SceLsdbTimeRange;
VITASDK_BUILD_ASSERT_EQ(0x10, SceLsdbTimeRange); // size is from FW 3.60

/** PCC state stored in tbl_livearea for one title. */
typedef struct SceLsdbLiveAreaPccInfo {
	SceRtcTick update_date;
	SceInt32 resource_status; //!< API value; FW 3.60 stores this value minus one in pccResStatus.
	SceInt32 sign_off;
} SceLsdbLiveAreaPccInfo;
VITASDK_BUILD_ASSERT_EQ(0x10, SceLsdbLiveAreaPccInfo); // size is from FW 3.60

/** Fields selected by ::sceLsdbUpdateLiveAreaPccInfo. */
typedef enum SceLsdbLiveAreaPccUpdateFlag {
	SCE_LSDB_LIVEAREA_PCC_UPDATE_FLAG_DATE            = 0x00000001,
	SCE_LSDB_LIVEAREA_PCC_UPDATE_FLAG_RESOURCE_STATUS = 0x00000002,
	SCE_LSDB_LIVEAREA_PCC_UPDATE_FLAG_SIGN_OFF        = 0x00000004
} SceLsdbLiveAreaPccUpdateFlag;

/** Change bits returned by the LiveArea replacement and frame-update exports. */
typedef enum SceLsdbLiveAreaChangeFlag {
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_1              = 0x00000001,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_2              = 0x00000002,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_3              = 0x00000004,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_4              = 0x00000008,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_5              = 0x00000010,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_6              = 0x00000020,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_7              = 0x00000040,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_8              = 0x00000080,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_9              = 0x00000100,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_FRAME_10             = 0x00000200,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_BACKGROUND_IMAGE     = 0x00010000,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_SYSTEM_FUNCTION_ZONE = 0x00020000,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_STARTUP_IMAGE        = 0x00040000,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_TITLE_COLOR          = 0x00080000,
	SCE_LSDB_LIVEAREA_CHANGE_FLAG_STYLE                = 0x00100000
} SceLsdbLiveAreaChangeFlag;

/** One sfType/sfTarg pair stored in tbl_livearea. */
typedef struct SceLsdbLiveAreaSfEntry {
	SceInt32 type;
	SceLsdbString target;
} SceLsdbLiveAreaSfEntry;
VITASDK_BUILD_ASSERT_EQ(0x10, SceLsdbLiveAreaSfEntry); // size is from FW 3.60

/** Object types stored in a parsed LiveArea frame list. */
typedef enum SceLsdbLiveAreaObjectType {
	SCE_LSDB_LIVEAREA_OBJECT_TYPE_BACKGROUND_IMAGE     = 1,
	SCE_LSDB_LIVEAREA_OBJECT_TYPE_SYSTEM_FUNCTION_ZONE = 2,
	SCE_LSDB_LIVEAREA_OBJECT_TYPE_STARTUP_IMAGE        = 3,
	SCE_LSDB_LIVEAREA_OBJECT_TYPE_FRAME                = 4,
	SCE_LSDB_LIVEAREA_OBJECT_TYPE_TITLE_COLOR          = 5
} SceLsdbLiveAreaObjectType;

/** Common prefix of every object in a parsed LiveArea object list. */
typedef struct SceLsdbLiveAreaObject {
	void *vtable; //!< Internal FW 3.60 virtual-function table.
	SceInt32 type; //!< One of ::SceLsdbLiveAreaObjectType.
} SceLsdbLiveAreaObject;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbLiveAreaObject); // size is from FW 3.60

/** Parsed LiveArea background image. */
typedef struct SceLsdbLiveAreaBackgroundImage {
	void *vtable; //!< Internal FW 3.60 virtual-function table.
	SceInt32 type; //!< ::SCE_LSDB_LIVEAREA_OBJECT_TYPE_BACKGROUND_IMAGE.
	SceLsdbString source_path;
} SceLsdbLiveAreaBackgroundImage;
VITASDK_BUILD_ASSERT_EQ(0x14, SceLsdbLiveAreaBackgroundImage); // size is from FW 3.60

/** Parsed system-function-zone entries. */
typedef struct SceLsdbLiveAreaSystemFunctionZone {
	void *vtable; //!< Internal FW 3.60 virtual-function table.
	SceInt32 type; //!< ::SCE_LSDB_LIVEAREA_OBJECT_TYPE_SYSTEM_FUNCTION_ZONE.
	SceLsdbLiveAreaSfEntry *entries;
	SceSize entry_count;
	SceSize entry_capacity;
	SceUInt32 reserved; //!< Not initialized or interpreted on FW 3.60.
} SceLsdbLiveAreaSystemFunctionZone;
VITASDK_BUILD_ASSERT_EQ(0x18, SceLsdbLiveAreaSystemFunctionZone); // size is from FW 3.60

/** Parsed gate startup image. */
typedef struct SceLsdbLiveAreaStartupImage {
	void *vtable; //!< Internal FW 3.60 virtual-function table.
	SceInt32 type; //!< ::SCE_LSDB_LIVEAREA_OBJECT_TYPE_STARTUP_IMAGE.
	SceLsdbString source_path;
} SceLsdbLiveAreaStartupImage;
VITASDK_BUILD_ASSERT_EQ(0x14, SceLsdbLiveAreaStartupImage); // size is from FW 3.60

/**
 * Parsed LiveArea title color, with each component scaled to 0.0 through 1.0.
 *
 * FW 3.60 parses `#RRGGBBAA`. The initialized default is white with alpha 0.5.
 */
typedef struct SceLsdbLiveAreaTitleColor {
	void *vtable; //!< Internal FW 3.60 virtual-function table.
	SceInt32 type; //!< ::SCE_LSDB_LIVEAREA_OBJECT_TYPE_TITLE_COLOR.
	float red;
	float green;
	float blue;
	float alpha;
} SceLsdbLiveAreaTitleColor;
VITASDK_BUILD_ASSERT_EQ(0x18, SceLsdbLiveAreaTitleColor); // size is from FW 3.60

/** Node in the parsed LiveArea object list. The list head has no object. */
typedef struct SceLsdbLiveAreaObjectListNode {
	struct SceLsdbLiveAreaObjectListNode *previous;
	struct SceLsdbLiveAreaObjectListNode *next;
	SceLsdbLiveAreaObject *object;
} SceLsdbLiveAreaObjectListNode;
VITASDK_BUILD_ASSERT_EQ(0xC, SceLsdbLiveAreaObjectListNode); // size is from FW 3.60

/** Element types stored in a parsed LiveArea frame item. */
typedef enum SceLsdbLiveAreaFrameElementType {
	SCE_LSDB_LIVEAREA_FRAME_ELEMENT_TYPE_TARGET     = 3,
	SCE_LSDB_LIVEAREA_FRAME_ELEMENT_TYPE_BACKGROUND = 4,
	SCE_LSDB_LIVEAREA_FRAME_ELEMENT_TYPE_IMAGE      = 5,
	SCE_LSDB_LIVEAREA_FRAME_ELEMENT_TYPE_TEXT       = 6
} SceLsdbLiveAreaFrameElementType;

/** Horizontal alignment values used by parsed LiveArea visual elements. */
typedef enum SceLsdbLiveAreaHorizontalAlignment {
	SCE_LSDB_LIVEAREA_HORIZONTAL_ALIGNMENT_CENTER        = 0,
	SCE_LSDB_LIVEAREA_HORIZONTAL_ALIGNMENT_LEFT          = 1,
	SCE_LSDB_LIVEAREA_HORIZONTAL_ALIGNMENT_RIGHT         = 2,
	SCE_LSDB_LIVEAREA_HORIZONTAL_ALIGNMENT_OUTSIDE_LEFT  = 3,
	SCE_LSDB_LIVEAREA_HORIZONTAL_ALIGNMENT_OUTSIDE_RIGHT = 4
} SceLsdbLiveAreaHorizontalAlignment;

/** Vertical alignment values used by parsed LiveArea visual elements. */
typedef enum SceLsdbLiveAreaVerticalAlignment {
	SCE_LSDB_LIVEAREA_VERTICAL_ALIGNMENT_CENTER         = 0,
	SCE_LSDB_LIVEAREA_VERTICAL_ALIGNMENT_TOP            = 1,
	SCE_LSDB_LIVEAREA_VERTICAL_ALIGNMENT_BOTTOM         = 2,
	SCE_LSDB_LIVEAREA_VERTICAL_ALIGNMENT_OUTSIDE_TOP    = 3,
	SCE_LSDB_LIVEAREA_VERTICAL_ALIGNMENT_OUTSIDE_BOTTOM = 4
} SceLsdbLiveAreaVerticalAlignment;

/** Coordinate origin accepted by parsed LiveArea image and text elements. */
typedef enum SceLsdbLiveAreaElementOrigin {
	SCE_LSDB_LIVEAREA_ELEMENT_ORIGIN_FRAME      = 2,
	SCE_LSDB_LIVEAREA_ELEMENT_ORIGIN_BACKGROUND = 4,
	SCE_LSDB_LIVEAREA_ELEMENT_ORIGIN_IMAGE      = 5
} SceLsdbLiveAreaElementOrigin;

/** Selection mode derived from a LiveArea frame's `multi` attribute. */
typedef enum SceLsdbLiveAreaFrameMultiMode {
	SCE_LSDB_LIVEAREA_FRAME_MULTI_MODE_ORDERED = 0, //!< `multi="o"`; select items cyclically in document order.
	SCE_LSDB_LIVEAREA_FRAME_MULTI_MODE_RANDOM  = 1  //!< `multi="r"`; select an item randomly, avoiding the current item when possible.
} SceLsdbLiveAreaFrameMultiMode;

/** Compatibility selector used for a LiveArea liveitem's `pokesute` attribute. */
typedef enum SceLsdbLiveAreaCompatibilityMode {
	SCE_LSDB_LIVEAREA_COMPATIBILITY_MODE_ANY         = 0, //!< Disable `pokesute` filtering.
	SCE_LSDB_LIVEAREA_COMPATIBILITY_MODE_UNSPECIFIED = 1, //!< No recognized `pokesute` attribute.
	SCE_LSDB_LIVEAREA_COMPATIBILITY_MODE_ON          = 2, //!< `pokesute="on"`.
	SCE_LSDB_LIVEAREA_COMPATIBILITY_MODE_OFF         = 3  //!< `pokesute="off"`.
} SceLsdbLiveAreaCompatibilityMode;

/** Common prefix of a parsed target, background, image, or text element. */
typedef struct SceLsdbLiveAreaFrameElement {
	void *vtable; //!< Internal FW 3.60 virtual-function table.
	SceInt32 type; //!< One of ::SceLsdbLiveAreaFrameElementType.
} SceLsdbLiveAreaFrameElement;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbLiveAreaFrameElement); // size is from FW 3.60

/** Common prefix of parsed background, image, and text elements. */
typedef struct SceLsdbLiveAreaVisualElement {
	void *vtable; //!< Internal FW 3.60 virtual-function table.
	SceInt32 type; //!< One of ::SceLsdbLiveAreaFrameElementType.
	SceInt32 horizontal_alignment; //!< One of ::SceLsdbLiveAreaHorizontalAlignment.
	SceInt32 vertical_alignment; //!< One of ::SceLsdbLiveAreaVerticalAlignment.
	SceInt32 width; //!< Parsed `width`; initialized to zero.
	SceInt32 height; //!< Parsed `height`; initialized to zero.
	SceInt32 x; //!< Parsed `x` coordinate.
	SceInt32 y; //!< Parsed `y` coordinate.
	SceUInt8 has_x; //!< Nonzero when the XML element specifies `x`.
	SceUInt8 has_y; //!< Nonzero when the XML element specifies `y`.
	SceUInt8 padding[2];
} SceLsdbLiveAreaVisualElement;
VITASDK_BUILD_ASSERT_EQ(0x24, SceLsdbLiveAreaVisualElement); // size is from FW 3.60

/** Parsed LiveArea target element. */
typedef struct SceLsdbLiveAreaTargetElement {
	SceLsdbLiveAreaFrameElement element;
	SceLsdbString target;
	SceLsdbString required_app_version; //!< Value of `req-appver` for template formats newer than 1.00.
} SceLsdbLiveAreaTargetElement;
VITASDK_BUILD_ASSERT_EQ(0x20, SceLsdbLiveAreaTargetElement); // size is from FW 3.60

/** Parsed LiveArea background element. */
typedef struct SceLsdbLiveAreaBackgroundElement {
	SceLsdbLiveAreaVisualElement visual;
	SceLsdbString source_path;
} SceLsdbLiveAreaBackgroundElement;
VITASDK_BUILD_ASSERT_EQ(0x30, SceLsdbLiveAreaBackgroundElement); // size is from FW 3.60

/** Parsed LiveArea image element. */
typedef struct SceLsdbLiveAreaImageElement {
	SceLsdbLiveAreaVisualElement visual;
	SceLsdbString source_path;
	SceInt32 origin; //!< ::SCE_LSDB_LIVEAREA_ELEMENT_ORIGIN_FRAME or ::SCE_LSDB_LIVEAREA_ELEMENT_ORIGIN_BACKGROUND.
} SceLsdbLiveAreaImageElement;
VITASDK_BUILD_ASSERT_EQ(0x34, SceLsdbLiveAreaImageElement); // size is from FW 3.60

/** Parsed LiveArea text element. */
typedef struct SceLsdbLiveAreaTextElement {
	SceLsdbLiveAreaVisualElement visual;
	SceInt32 text_alignment; //!< One of ::SceLsdbLiveAreaHorizontalAlignment.
	SceInt32 vertical_text_alignment; //!< One of ::SceLsdbLiveAreaVerticalAlignment.
	SceInt32 line_alignment; //!< One of ::SceLsdbLiveAreaHorizontalAlignment.
	SceInt32 origin; //!< ::SCE_LSDB_LIVEAREA_ELEMENT_ORIGIN_FRAME, ::SCE_LSDB_LIVEAREA_ELEMENT_ORIGIN_BACKGROUND, or ::SCE_LSDB_LIVEAREA_ELEMENT_ORIGIN_IMAGE.
	SceInt32 line_spacing;
	SceUInt8 line_break; //!< Line-breaking flag; initialized to one.
	SceUInt8 word_wrap; //!< Word-wrapping flag; initialized to one.
	SceUInt8 ellipsis; //!< Ellipsis flag; initialized to zero.
	SceUInt8 word_scroll; //!< Word-scrolling flag; initialized to zero.
	SceUInt8 pre_break; //!< Internal pre-break flag; initialized to one.
	SceUInt8 padding[3];
	SceInt32 margin_top;
	SceInt32 margin_bottom;
	SceInt32 margin_left;
	SceInt32 margin_right;
	SceInt32 title_segment_index; //!< Index of the `title` segment, or -1 when absent.
	SceUInt8 text_layout[0x1C]; //!< Internal FW 3.60 PAF text-layout state.
} SceLsdbLiveAreaTextElement;
VITASDK_BUILD_ASSERT_EQ(0x70, SceLsdbLiveAreaTextElement); // size is from FW 3.60

/** One liveitem parsed from a LiveArea frame. */
typedef struct SceLsdbLiveAreaFrameItem {
	SceLsdbTimeRange time_range; //!< Inclusive `from` and `until` interval.
	SceUInt8 is_default; //!< Nonzero when the XML liveitem has `default="on"`.
	SceUInt8 padding;
	SceUInt16 minimum_age; //!< Selected `age-limit`, or 0 when absent.
	SceUInt16 maximum_age; //!< Selected `uage-limit`, or 255 when absent.
	SceUInt16 compatibility_mode; //!< One of ::SceLsdbLiveAreaCompatibilityMode, derived from `pokesute`.
	SceLsdbLiveAreaTargetElement *target; //!< Selected target element, or NULL.
	SceLsdbLiveAreaFrameElement **elements;
	SceSize element_count;
	SceSize element_capacity;
	SceUInt32 reserved1[2]; //!< Not initialized or interpreted on FW 3.60.
} SceLsdbLiveAreaFrameItem;
VITASDK_BUILD_ASSERT_EQ(0x30, SceLsdbLiveAreaFrameItem); // size is from FW 3.60

/** One parsed row of tbl_livearea_frame. */
typedef struct SceLsdbLiveAreaFrame {
	void *vtable; //!< Internal FW 3.60 virtual-function table.
	SceInt32 object_type; //!< ::SCE_LSDB_LIVEAREA_OBJECT_TYPE_FRAME.
	SceLsdbString frame_id;
	SceInt32 multi_mode; //!< One of ::SceLsdbLiveAreaFrameMultiMode.
	SceUInt32 auto_flip_interval; //!< Automatic item-rotation interval from the `autoflip` attribute.
	SceInt64 revision;
	SceUInt8 is_retail_override; //!< Nonzero for a database row whose type is 0.
	SceLsdbString user_data; //!< `userdata`, truncated to at most 1023 bytes.
	SceLsdbLiveAreaFrameItem **items;
	SceSize item_count;
	SceSize item_capacity;
} SceLsdbLiveAreaFrame;
VITASDK_BUILD_ASSERT_EQ(0x48, SceLsdbLiveAreaFrame); // size is from FW 3.60

/** Parsed LiveArea template and its list of objects of different types. */
typedef struct SceLsdbLiveAreaFrameList {
	SceLsdbString style;
	SceLsdbString format_version;
	SceInt64 content_revision;
	SceInt32 parsed_format_version; //!< Result of ::sceLsdbParseVersion.
	SceLsdbLiveAreaObjectListNode *object_list_head; //!< List head, with no object. Start at `object_list_head->next` and stop when you reach `object_list_head` again.
	SceSize object_count;
	SceRtcTick modified_date;
} SceLsdbLiveAreaFrameList;
VITASDK_BUILD_ASSERT_EQ(0x38, SceLsdbLiveAreaFrameList); // size is from FW 3.60

/**
 * Reference-counted ::SceLsdbLiveAreaFrameList object.
 * See ::SceLsdbAppInfo for the shared-reference ownership and cleanup rules.
 */
typedef struct SceLsdbLiveAreaFrameListRef {
	SceLsdbLiveAreaFrameList *object;
	void *control;
} SceLsdbLiveAreaFrameListRef;
VITASDK_BUILD_ASSERT_EQ(0x8, SceLsdbLiveAreaFrameListRef); // size is from FW 3.60

/** State used while parsing one LiveArea template. */
typedef struct SceLsdbLiveAreaParser {
	SceLsdbString contents_path;
	SceUInt8 filter_hardware_model; //!< Apply XML `model` selectors and enable title-color parsing.
	SceUInt8 fallback_to_default_template; //!< Use the default system template when \a contents_path cannot be opened.
	SceUInt8 using_default_template; //!< Set when the parser selects the default system template.
	SceUInt8 padding;
	SceLsdbLiveAreaFrameList *parsed_frames;
	void *parsed_frames_control; //!< Reference-count control block for parsed_frames.
	const SceInt32 *language_index;
	const char *country;
	SceInt32 content_rating;
	SceUInt8 filter_by_current_time; //!< Apply the liveitem `until` time when liveitem filtering is enabled.
	SceUInt8 disable_live_item_filtering; //!< Bypass locale, age, model, compatibility, time, and five-item-limit filtering.
	SceUInt8 unused; //!< Written by SceShell but ignored by SceLsdb on FW 3.60.
	SceUInt8 use_ad_network_clock; //!< Use the ad-network clock for liveitem time checks.
	SceInt32 compatibility_mode; //!< One of ::SceLsdbLiveAreaCompatibilityMode; selects liveitems by their `pokesute` value.
	SceInt32 selected_language_index;
	SceLsdbString selected_country;
} SceLsdbLiveAreaParser;
VITASDK_BUILD_ASSERT_EQ(0x3C, SceLsdbLiveAreaParser); // size is from FW 3.60

/** Entry stored in ux0:iconlayout.ini. */
typedef struct SceLsdbIconLayoutEntry {
	SceInt32 page_no; //!< Normal page 0 through 9, or special page -20000000 through -10000001.
	SceInt32 position; //!< Position 0 through 9.
	SceInt32 parent_page_no; //!< Parent page 0 through 9 for a special-page entry.
	SceInt32 parent_position; //!< Parent position 0 through 9 for a special-page entry.
	char *parent_title_id; //!< PAF-allocated parent title ID returned for a special-page entry.
	SceSize parent_title_id_length; //!< Length of parent_title_id; ignored by the INI writer.
} SceLsdbIconLayoutEntry;
VITASDK_BUILD_ASSERT_EQ(0x18, SceLsdbIconLayoutEntry); // size is from FW 3.60

/**
 * Callback used to obtain the current content-rating configuration.
 *
 * Return zero after writing whether content-rating restrictions are enabled
 * and the configured rating. A nonzero result makes
 * ::sceLsdbGetUserContentRating calculate the user's age from the registered
 * date of birth instead.
 */
typedef int (*SceLsdbContentRatingCallback)(SceInt32 *enabled, SceInt32 *rating);

/** Callback invoked once for each title enumerated by ::sceLsdbGetAllAppInfo. */
typedef void (*SceLsdbAppInfoCallback)(const SceLsdbAppInfo *app_info, void *user_data);

/**
 * Initialize an AppDB wrapper.
 *
 * Both this function and ::sceLsdbAppDatabaseInit2 allocate the same
 * one-byte ownership token on FW 3.60. First call ::sceLsdbOpen; this function
 * does not open a database connection. The reason for exporting two entry
 * points is unknown.
 */
SceLsdbAppDatabase *sceLsdbAppDatabaseInit(SceLsdbAppDatabase *database);
SceLsdbAppDatabase *sceLsdbAppDatabaseInit2(SceLsdbAppDatabase *database);

/**
 * Release an AppDB wrapper's ownership token.
 *
 * Both entry points free a non-NULL token and return \a database. They do not
 * close the process's shared AppDB or clear ::SceLsdbAppDatabase::token.
 */
SceLsdbAppDatabase *sceLsdbAppDatabaseEnd(SceLsdbAppDatabase *database);
SceLsdbAppDatabase *sceLsdbAppDatabaseEnd2(SceLsdbAppDatabase *database);

/**
 * Query icon records for consecutive AppDB pages.
 *
 * The requested pages start at \a first_page_no and end before
 * `first_page_no + page_count`. Before the call,
 * \a icons_by_page must contain at least \a page_count elements, and each element
 * must hold a valid reference to an ::SceLsdbIconInfoRefArray object. FW 3.60
 * clears those inner vectors and then fills element `i` with the icons from
 * page `first_page_no + i`, ordered by position. At most ten icons are retained
 * for each page.
 *
 * @retval SCE_LSDB_ERROR_INVALID_ARGUMENT \a page_count is zero or the outer
 *         vector contains fewer than \a page_count elements.
 */
int sceLsdbGetIconsInPageRange(SceLsdbAppDatabase *database, SceInt32 first_page_no, SceSize page_count, SceLsdbIconInfoRefArrayRefArray *icons_by_page);

/**
 * Query \a page_count consecutive page records beginning at \a first_page_no.
 *
 * Before the call, \a pages must contain at least \a page_count elements. FW
 * 3.60 releases any references already held by those elements, then writes
 * one ::SceLsdbPageInfoRef for each requested page number.
 *
 * @retval SCE_LSDB_ERROR_INVALID_ARGUMENT \a page_count is zero or \a pages
 *         contains fewer than \a page_count elements.
 */
int sceLsdbGetPageInfo(SceLsdbAppDatabase *database, SceInt32 first_page_no, SceSize page_count, SceLsdbPageInfoRefArray *pages);

/**
 * Replace all icon records on one or more pages.
 *
 * \a page_nos and \a icons_by_page must have the same nonzero element count.
 * Element `i` of \a icons_by_page is the replacement icon vector for
 * `page_nos[i]`. FW 3.60 deletes every existing icon on each page, then inserts
 * the supplied icons in vector order with positions beginning at zero. An
 * empty inner vector therefore clears that page.
 *
 * Valid page numbers are nonnegative, -100000000, or in the range -20000000
 * through -10000001.
 */
int sceLsdbReplaceIconsInPages(SceLsdbAppDatabase *database, const SceLsdbInt32Array *page_nos, const SceLsdbIconInfoRefArrayRefArray *icons_by_page);

/**
 * Update selected fields of one icon record.
 *
 * The record is selected by \a page_no and ::SceLsdbIconInfo::position. Only
 * ::SceLsdbIconInfoUpdateFlag bits are interpreted; unlisted bits must not be
 * set. The selected integer and string fields are read from \a icon_info.
 *
 * ::SCE_LSDB_ICON_INFO_UPDATE_RENDERED_ICON_BLOB stores \a icon_data and
 * \a icon_data_size in `tbl_appinfo_icon.reserved05`.
 * ::SCE_LSDB_ICON_INFO_UPDATE_ALTERNATE_ICON_PATH stores
 * ::SceLsdbIconInfo::icon_path as `reserved02`; it does not use \a icon_data.
 * Input objects and buffers must remain valid until the call returns; they
 * are not used afterwards.
 *
 * @param[in] database - Initialized AppDB wrapper; the AppDB must be open.
 * @param[in] page_no - Page containing the icon.
 * @param[in] icon_info - Icon object whose position and selected fields are read.
 * @param[in] update_mask - Bitwise OR of ::SceLsdbIconInfoUpdateFlag values.
 * @param[in] icon_data - Rendered PAF icon-cache bytes, or NULL when the blob
 *                       update bit is not set.
 * @param[in] icon_data_size - Size of \a icon_data in bytes.
 *
 * @retval 0 The record was updated.
 * @retval SCE_LSDB_ERROR_INVALID_ARGUMENT \a icon_info is invalid or
 *         \a update_mask is zero.
 * @retval SCE_LSDB_ERROR_INVALID_HANDLE The database is not open or the
 *         transaction could not be started.
 * @retval SCE_LSDB_ERROR_NOT_FOUND No matching row was changed.
 * @retval SCE_LSDB_ERROR_NO_MEMORY An internal allocation failed.
 * @return Other negative ActivityDb/SQLite errors can also be returned.
 */
int sceLsdbUpdateIconInfo(SceLsdbAppDatabase *database, SceInt32 page_no, const SceLsdbIconInfoRef *icon_info, SceUInt32 update_mask, const void *icon_data, SceSize icon_data_size);

/**
 * Insert one icon record on \a page_no.
 *
 * Valid pages are nonnegative, -100000000, or special pages from -20000000
 * through -10000001. Page -100000000 appends the icon after existing rows;
 * other pages use ::SceLsdbIconInfo::position. On success the SQLite row ID is
 * written to ::SceLsdbIconInfo::row_id. A type-zero icon must have a nonempty
 * title ID. A title whose `#_org_path` begins with `ux0:` also receives an
 * `ux0:iconlayout.ini` entry.
 *
 * FW 3.60 returns 0 without inserting anything for another negative
 * page number, including -1.
 */
int sceLsdbInsertIcon(SceLsdbAppDatabase *database, SceInt32 page_no, const SceLsdbIconInfoRef *icon_info);

/**
 * Delete the icon record belonging to \a title_id.
 *
 * The corresponding `ux0:iconlayout.ini` entry is also removed when the
 * title's `#_org_path` begins with `ux0:`.
 *
 * @retval 0 One or more icon rows were deleted.
 * @retval SCE_LSDB_ERROR_NOT_FOUND No icon row has this title ID.
 */
int sceLsdbDeleteIconByTitleId(SceLsdbAppDatabase *database, const SceLsdbString *title_id);

/**
 * Move corresponding source page/position entries to their destinations.
 *
 * All four vectors must have the same nonzero count. Element `i` identifies
 * one source and destination pair. A destination page must be nonnegative,
 * -100000000, or in the special-page range from -20000000 through -10000001.
 * FW 3.60 first moves each row to position
 * `~destination_positions[i]` on the destination page to avoid duplicate
 * page/position pairs, then moves it to the requested position.
 *
 * An otherwise invalid destination page instead requests deletion when it is
 * the bitwise complement of the destination position. For example, the pair
 * `(-1, 0)` deletes the source icon. Another invalid pair returns
 * ::SCE_LSDB_ERROR_INVALID_ARGUMENT. Final coordinates are reflected in
 * `ux0:iconlayout.ini`.
 */
int sceLsdbMoveIcons(SceLsdbAppDatabase *database, const SceLsdbInt32Array *source_page_nos, const SceLsdbInt32Array *source_positions, const SceLsdbInt32Array *destination_page_nos, const SceLsdbInt32Array *destination_positions);

/**
 * Return the reference-counted blob in `tbl_appinfo_icon.reserved05` for the
 * supplied SQLite row ID. The returned stream is read-only and opens the
 * database BLOB only when needed. \a error is optional and receives the stream
 * creation result; an error returns an empty reference.
 */
SceLsdbDbBlobRef sceLsdbGetIconReservedBlob(SceLsdbAppDatabase *database, const SceInt64 *row_id, int *error);

/**
 * Update one or more AppDB page records.
 *
 * \a page_nos and \a pages must have the same nonzero element count. Element
 * `i` of \a pages supplies every replacement field for `page_nos[i]`. Page
 * numbers may be nonnegative, -100000000, or in the special-page range from
 * -20000000 through -10000001. A missing page returns success without making
 * changes on FW 3.60.
 */
int sceLsdbUpdatePages(SceLsdbAppDatabase *database, const SceLsdbInt32Array *page_nos, const SceLsdbPageInfoRefArray *pages);

/**
 * Insert a nonnegative page record followed by its icon records.
 *
 * \a page_no may equal the current nonnegative page count to append a page, but
 * may not exceed it. Existing pages at and after the insertion point are
 * shifted upward. Each icon uses its own ::SceLsdbIconInfo::position and
 * receives its SQLite row ID in ::SceLsdbIconInfo::row_id. Corresponding
 * `ux0:iconlayout.ini` page numbers are shifted on success.
 */
int sceLsdbInsertPage(SceLsdbAppDatabase *database, SceInt32 page_no, const SceLsdbIconInfoRefArray *icons, const SceLsdbPageInfo *page_info);

/**
 * Delete a nonnegative or special negative page.
 *
 * Deleting a nonnegative page shifts every later page and icon-layout entry
 * down by one. Deleting a special page also deletes the folder icon whose
 * `reserved01` value references that page.
 */
int sceLsdbDeletePage(SceLsdbAppDatabase *database, SceInt32 page_no);

/**
 * Create a folder icon around an existing child icon.
 *
 * FW 3.60 allocates a previously unused page number from -20000000 through
 * -10000001, assigns it to \a folder_icon_info, and inserts that special page.
 * It then moves the existing row at `(page_no, folder_icon_info->position)` to
 * `(specialPageNo, child_icon_info->position)` and inserts the folder back at
 * `(page_no, folder_icon_info->position)`. Shell normally sets the child's new
 * position to zero. The existing child is selected by coordinates, not by the
 * child reference's row ID or title ID.
 *
 * Both reference holders and their objects must be non-NULL. A type-zero
 * child with a nonempty title ID is recorded in the special-page metadata.
 * The newly inserted folder's SQLite row ID is written to
 * ::SceLsdbIconInfo::row_id.
 *
 * \a icon_data and \a icon_data_size initialize the folder's rendered-icon BLOB
 * only when \a icon_data is non-NULL and \a icon_data_size is nonzero.
 */
int sceLsdbInsertIconWithParent(SceLsdbAppDatabase *database, SceInt32 page_no, const SceLsdbIconInfoRef *child_icon_info, const SceLsdbIconInfoRef *folder_icon_info, const void *icon_data, SceSize icon_data_size);

/** Return the number of nonnegative AppInfo pages. */
int sceLsdbGetPageCount(SceLsdbAppDatabase *database);

/**
 * Count icons on \a page_count consecutive pages beginning at \a first_page_no.
 *
 * A valid starting page is nonnegative, -100000000, or in the special-page
 * range from -20000000 through -10000001. For those values, FW 3.60 counts
 * rows whose page number is between \a first_page_no and
 * `first_page_no + page_count - 1`, inclusive. Any other starting value disables
 * the page filter and counts every icon row; Shell and database recovery use
 * -1 to request that total.
 */
int sceLsdbGetIconCountInPageRange(SceLsdbAppDatabase *database, SceInt32 first_page_no, SceSize page_count);

/**
 * Count icons which count against the Shell top-level icon limit.
 *
 * FW 3.60 excludes folder icons with type 5 and every icon on page
 * -100000000.
 */
int sceLsdbGetCountedIconCount(SceLsdbAppDatabase *database);

/**
 * Return folder child-page numbers for a localized bubble title.
 *
 * FW 3.60 hardcodes icon type 5, finds every matching `title` value, orders
 * the rows by containing page number and position, and appends each row's
 * `reserved01` value to \a page_nos. For a folder, that value identifies its
 * special negative child page.
 *
 * @retval 0 One or more folder page numbers were returned.
 * @retval SCE_LSDB_ERROR_NOT_FOUND No matching folder row exists.
 */
int sceLsdbGetFolderPageNosByTitle(SceLsdbAppDatabase *database, const SceLsdbString *title, SceLsdbInt32Array *page_nos);

/** Load all AppInfo values for one title through an AppDB wrapper. */
int sceLsdbGetAppInfoFromDatabase(SceLsdbAppDatabase *database, const SceLsdbString *title_id, SceLsdbAppInfo *app_info);

/**
 * Read one typed AppInfo value through an AppDB wrapper.
 *
 * @return ::SCE_LSDB_VALUE_TYPE_INT64 or ::SCE_LSDB_VALUE_TYPE_STRING on
 *         success, or a negative error code.
 */
int sceLsdbGetAppInfoValueFromDatabase(SceLsdbAppDatabase *database, const SceLsdbString *title_id, SceUInt32 key, SceLsdbValue *value);

/**
 * Return nonzero when tbl_appinfo contains at least one row for \a title_id.
 * A closed AppDB returns 0 rather than ::SCE_LSDB_ERROR_INVALID_HANDLE.
 */
int sceLsdbAppInfoExists(SceLsdbAppDatabase *database, const SceLsdbString *title_id);

/**
 * Read icon information for \a title_id.
 *
 * When \a use_fallback is nonzero, a nonempty `reserved02` column replaces the
 * returned ::SceLsdbIconInfo::icon_path. If no icon row exists for \a title_id,
 * the title's `BOOT_INSTALL_DIR` AppInfo string is also tried as a second title
 * ID. A zero value disables both fallback behaviors.
 *
 * \a database must not be NULL: FW 3.60 dereferences the wrapper, but performs
 * this query through the process's shared AppDB connection.
 */
int sceLsdbGetIconInfoByTitleId(SceLsdbAppDatabase *database, const SceLsdbString *title_id, SceLsdbIconInfoRef *icon_info, SceInt32 *page_no, SceBool use_fallback);

/**
 * Read the first icon record whose `tbl_appinfo_icon.reserved01` equals
 * the signed 32-bit value at \a reserved01. This selector is distinct from
 * ::SceLsdbIconInfo::row_id. On success \a page_no receives the containing page
 * and \a icon_info receives one strong reference.
 */
int sceLsdbGetIconInfoById(SceLsdbAppDatabase *database, const SceInt32 *reserved01, SceInt32 *page_no, SceLsdbIconInfoRef *icon_info);

/**
 * Return title IDs matching a chain of AppInfo filters.
 *
 * Without ::SCE_LSDB_FILTER_FLAG_APPINFO_ONLY, FW 3.60 returns title IDs from
 * type-zero icon records whose AppInfo rows match \a filter. The other flags
 * affect only that icon-record query. Existing contents of \a title_ids are
 * released before the result is written. \a filter must not be NULL.
 *
 * \a flags is a bitwise OR of ::SceLsdbFilterFlags values.
 */
int sceLsdbGetFilteredTitleIdsFromDatabase(SceLsdbAppDatabase *database, const SceLsdbAppInfoFilter *filter, SceLsdbStringArray *title_ids, SceUInt32 flags);

/**
 * Return recently used titles in any requested application category.
 *
 * Results are ordered by the `#_lltime` AppInfo value in descending order.
 * A \a max_title_count value less than or equal to zero removes the result
 * limit. When \a category_count is zero, \a categories may be NULL and every
 * row which has a CATEGORY value is eligible. Existing contents of \a title_ids
 * are released before the result is written.
 */
int sceLsdbGetRecentlyUsedTitleIdsByCategoriesFromDatabase(SceLsdbAppDatabase *database, const char *const *categories, SceSize category_count, SceInt32 max_title_count, SceLsdbStringArray *title_ids);

/**
 * Resolve a URI to the title whose registered host/path is its longest prefix.
 *
 * Rows with the same prefix are ordered by descending last-launch and creation
 * times. When \a flags is zero, no URI-row flag filter is applied. A nonzero
 * value keeps only rows for which `(storedFlag & flags) != 0`. FW 3.60 sets
 * stored flag bit 0 for the `GDA` category and for application name
 * `PCSI00013`; Shell passes either 0 or 1 to this function.
 */
int sceLsdbResolveUriTitleIdFromDatabase(SceLsdbAppDatabase *database, const char *uri, SceLsdbString *title_id, SceUInt32 flags);

/** Collect distinct `scheme:host/path` prefixes for the requested schemes. */
int sceLsdbGetUriPrefixesFromDatabase(SceLsdbAppDatabase *database, const char *const *schemes, SceSize scheme_count, SceLsdbStringArray *uri_prefixes);

/**
 * Insert the AppInfo, icon, URI, and icon-layout records for one application.
 *
 * The reference holders and \a additional_app_info vector must not be NULL,
 * even when empty. A page number of -1 skips icon insertion. Page -100000000
 * appends the icon after the existing icons on that page; other valid pages
 * use ::SceLsdbIconInfo::position. A successful icon insertion writes its
 * SQLite row ID to ::SceLsdbIconInfo::row_id. An application whose
 * `#_org_path` begins with `ux0:` also receives an `ux0:iconlayout.ini` entry.
 * Observers are called with ::SCE_LSDB_APP_INFO_EVENT_INSERT_APPLICATION after
 * all records have been written.
 */
int sceLsdbInsertApplication(SceLsdbAppDatabase *database, const SceLsdbAppInfo *app_info, SceInt32 page_no, const SceLsdbIconInfoRef *icon_info, const SceLsdbAppInfoArray *additional_app_info);

/**
 * Delete all AppDB data belonging to \a title_id.
 *
 * The icon, AppInfo, URI, and icon-layout records are removed. When
 * \a delete_special_page is nonzero and the icon resides on a special negative
 * page, that page and the folder row which references it are also removed.
 * When \a page_no is non-NULL, it receives the deleted icon's page number.
 */
int sceLsdbDeleteTitleData(SceLsdbAppDatabase *database, const SceLsdbString *title_id, SceBool delete_special_page, SceInt32 *page_no);

/**
 * Update the AppInfo, icon, and URI records for one application.
 *
 * A nonempty \a icon_info updates the existing icon row's title, path,
 * icon0 type, command, parental-lock level, and status, but not its alternate
 * path or rendered-icon BLOB. An empty reference leaves the icon row
 * unchanged. On success, observers are called with
 * ::SCE_LSDB_APP_INFO_EVENT_UPDATE_APPLICATION.
 */
int sceLsdbUpdateApplication(SceLsdbAppDatabase *database, const SceLsdbAppInfo *app_info, const SceLsdbIconInfoRef *icon_info, const SceLsdbAppInfoArray *additional_app_info);

/**
 * Replace the AppInfo and URI records for one application.
 *
 * When \a update_icon_title is nonzero, the icon reference must be nonempty and
 * only ::SceLsdbIconInfo::title is copied to the existing icon row. No icon
 * path, type, command, status, or image BLOB is changed. On success, observers
 * are called with ::SCE_LSDB_APP_INFO_EVENT_UPDATE_APP_INFO.
 */
int sceLsdbReplaceApplication(SceLsdbAppDatabase *database, const SceLsdbAppInfo *app_info, const SceLsdbIconInfoRef *icon_info, SceBool update_icon_title, const SceLsdbAppInfoArray *additional_app_info);

/**
 * Update a title's AppInfo value using a mask through an AppDB wrapper.
 *
 * For integer values, bits selected by \a mask are copied from \a value. String
 * values are replaced. SUPPORT_URI, `_fg_title_id`, and `_bg_title_id` are
 * protected and return ::SCE_LSDB_ERROR_PROTECTED_APPINFO_KEY. On success,
 * observers are called with ::SCE_LSDB_APP_INFO_EVENT_UPDATE_APP_INFO.
 */
int sceLsdbSetAppInfoValueMaskedFromDatabase(SceLsdbAppDatabase *database, const SceLsdbString *title_id, SceUInt32 key, const SceLsdbValue *value, SceUInt64 mask);

/**
 * Return a standalone config string, or a copied \a default_value when the key
 * or the process's shared database is unavailable. The wrapper is required
 * but does not select a separate connection.
 */
SceLsdbString sceLsdbGetConfigStringFromDatabase(SceLsdbAppDatabase *database, SceUInt32 key, const char *default_value);

/**
 * Return a 64-bit config value, or \a default_value when the key or
 * the process's shared database is unavailable. The wrapper does not select
 * a separate connection.
 */
SceInt64 sceLsdbGetConfigInt64FromDatabase(SceLsdbAppDatabase *database, SceUInt32 key, SceInt64 default_value);

/** Store or replace a string in tbl_config through the process's shared AppDB. */
int sceLsdbSetConfigStringFromDatabase(SceLsdbAppDatabase *database, SceUInt32 key, const char *value);

/**
 * Update an integer tbl_config value using a mask through an AppDB wrapper.
 *
 * The resulting value is (oldValue & ~mask) | (value & mask).
 */
int sceLsdbSetConfigInt64MaskedFromDatabase(SceLsdbAppDatabase *database, SceUInt32 key, SceInt64 value, SceUInt64 mask);

/**
 * Update page and system-icon rows from a Shell theme-layout object.
 *
 * \a layout and \a layout->object must not be NULL. \a update_flags is a
 * bitwise OR of ::SceLsdbThemeLayoutUpdateFlag values. Unselected fields of
 * the layout are not read. The system-icon update joins each nonempty
 * ::SceLsdbThemeSystemIconLayout::icon_file_path to the theme root and stores it
 * as the icon row's alternate path. The page update applies one layout entry
 * to each existing nonnegative page:
 * ::SceLsdbThemePageLayout::wave_type becomes `bgColor`,
 * ::SceLsdbThemePageLayout::font_color and
 * ::SceLsdbThemePageLayout::font_shadow are encoded into `reserved01`, and a
 * nonempty ::SceLsdbThemePageLayout::image_file_path becomes `theme_file` with
 * dimensions 960 by 512.
 */
int sceLsdbUpdateThemeLayout(SceLsdbAppDatabase *database, const SceLsdbThemeLayoutRef *layout, SceUInt32 update_flags);

/**
 * Replace or insert one theme record and its localized strings.
 *
 * The selected member at the start of each localized-string collection is not
 * read. The 20 localized members are stored for language indices 0 through 19.
 */
int sceLsdbReplaceTheme(SceLsdbAppDatabase *database, const SceLsdbThemeInfo *theme_info, const SceLsdbLocalizedThemeStrings *localized_titles, const SceLsdbLocalizedThemeStrings *localized_providers);

/** Delete one theme record. */
int sceLsdbDeleteTheme(SceLsdbAppDatabase *database, const SceLsdbString *theme_id);

/** Delete all theme records. */
int sceLsdbDeleteAllThemes(SceLsdbAppDatabase *database);

/** Return the number of theme records. */
int sceLsdbGetThemeCount(SceLsdbAppDatabase *database);

/**
 * Begin an AppDB transaction through a wrapper.
 *
 * @retval 0 The transaction was started.
 * @retval SCE_LSDB_ERROR_INVALID_HANDLE The database is not open.
 * @return Other negative ActivityDb/SQLite errors can also be returned.
 */
int sceLsdbAppDatabaseBeginTransaction(SceLsdbAppDatabase *database);

/**
 * End an AppDB transaction through a wrapper.
 *
 * The second argument is not a notification type, and this function does not
 * send an AppDB notification.
 * Any negative \a database_version_or_rollback rolls the transaction back. A
 * nonnegative value is written as the primary AppDB version before the
 * transaction is committed. Use -1 to roll back or 59 to commit a FW 3.60
 * AppDB. Another nonnegative version can make the database fail its next
 * compatibility check.
 *
 * A successful commit also rotates the previous `<database-path>-err` file and
 * sets `/CONFIG/SHELL/appdb_rebuild_flag` to 1. It does not invalidate
 * SceShell's in-memory icon cache.
 *
 * @retval 0 The transaction was committed or rolled back.
 * @retval SCE_LSDB_ERROR_INVALID_HANDLE The database is not open or no valid
 *         transaction exists.
 * @return Other negative ActivityDb/SQLite errors can also be returned.
 */
int sceLsdbAppDatabaseEndTransaction(SceLsdbAppDatabase *database, SceInt32 database_version_or_rollback);

/**
 * Enumerate all AppInfo objects ordered by title ID.
 *
 * \a callback is invoked once for each title. The callback receives a temporary
 * reference which is released after it returns.
 */
int sceLsdbGetAllAppInfo(SceLsdbAppDatabase *database, SceLsdbAppInfoCallback callback, void *user_data);

/**
 * Register an AppInfo observer for the calling process.
 *
 * Re-registering an initialized \a observer first removes its previous
 * registration. The callback and user-data pointers are stored directly in
 * \a observer; they are not copied into separately owned storage. A NULL
 * \a callback removes an existing registration without adding another one.
 *
 * @param[in,out] observer - Non-NULL, zero-initialized object which must remain
 *                           allocated at the same address until it is
 *                           unregistered.
 * @param[in] callback - Callback invoked synchronously for AppInfo changes.
 * @param[in] user_data - Opaque value passed to \a callback.
 *
 * @retval 0 The observer was registered.
 * @retval SCE_LSDB_ERROR_INVALID_HANDLE The process's shared AppDB is not open.
 */
int sceLsdbRegisterAppInfoObserver(SceLsdbAppInfoObserver *observer, SceLsdbAppInfoObserverCallback callback, void *user_data);

/**
 * Unregister an AppInfo observer in the calling process and clear its two fields.
 *
 * \a observer must be non-NULL. It may already be empty.
 *
 * @retval 0 The observer was unregistered or was already empty.
 */
int sceLsdbUnregisterAppInfoObserver(SceLsdbAppInfoObserver *observer);

/**
 * Initialize a query context without attaching it to the database.
 *
 * Both entry points set ::SceLsdbQueryContext::state to NULL and otherwise
 * have the same behavior on FW 3.60.
 */
SceLsdbQueryContext *sceLsdbQueryContextInit(SceLsdbQueryContext *context);
SceLsdbQueryContext *sceLsdbQueryContextInit2(SceLsdbQueryContext *context);

/**
 * Stop a query context from receiving the process's AppDB change notifications.
 *
 * This unregisters the context's internal AppInfo observer, releases its
 * four-byte state object, and sets ::SceLsdbQueryContext::state to NULL. It
 * succeeds when the context is already detached.
 */
int sceLsdbQueryContextClose(SceLsdbQueryContext *context);

/**
 * Detach and release a query-context object.
 *
 * Both entry points perform the same cleanup as
 * ::sceLsdbQueryContextClose, but return \a context.
 */
SceLsdbQueryContext *sceLsdbQueryContextEnd(SceLsdbQueryContext *context);
SceLsdbQueryContext *sceLsdbQueryContextEnd2(SceLsdbQueryContext *context);

/**
 * Attach a query context to the process's already-open shared AppDB.
 *
 * First call ::sceLsdbOpen. This function does not open a database; it
 * allocates a four-byte change flag and registers an internal AppInfo observer
 * for the calling process. Every AppInfo notification sets the flag to 1.
 * The flag can be read and optionally cleared with
 * ::sceLsdbQueryContextTestAndClearFlag. Call one of the query-context cleanup
 * functions before ::sceLsdbClose.
 *
 * @retval 0 The context was attached.
 * @retval SCE_LSDB_ERROR_INVALID_HANDLE The process's shared AppDB is not open,
 *         or \a context is already attached.
 */
int sceLsdbQueryContextOpen(SceLsdbQueryContext *context);

/** Load all AppInfo values for one title. */
int sceLsdbQueryGetAppInfo(SceLsdbQueryContext *context, const SceLsdbString *title_id, SceLsdbAppInfo *app_info);

/**
 * Read one typed AppInfo value.
 *
 * @return ::SCE_LSDB_VALUE_TYPE_INT64 or ::SCE_LSDB_VALUE_TYPE_STRING on
 *         success, or a negative error code.
 */
int sceLsdbQueryGetAppInfoValue(SceLsdbQueryContext *context, const SceLsdbString *title_id, SceUInt32 key, SceLsdbValue *value);

/**
 * Return nonzero when a title has AppInfo rows. A detached context or closed
 * AppDB returns 0 rather than ::SCE_LSDB_ERROR_INVALID_HANDLE.
 */
int sceLsdbQueryAppInfoExists(SceLsdbQueryContext *context, const SceLsdbString *title_id);

/**
 * Read icon information for a title through a query context.
 *
 * \a use_fallback has the same `reserved02` and `BOOT_INSTALL_DIR` behavior as
 * ::sceLsdbGetIconInfoByTitleId. It does not control whether hidden icons are
 * included.
 */
int sceLsdbQueryGetIconInfo(SceLsdbQueryContext *context, const SceLsdbString *title_id, SceLsdbIconInfoRef *icon_info, SceBool use_fallback);

/**
 * Return title IDs matching a chain of AppInfo filters.
 *
 * This is the query-context version of
 * ::sceLsdbGetFilteredTitleIdsFromDatabase. It uses the process's shared AppDB.
 */
int sceLsdbQueryGetFilteredTitleIds(SceLsdbQueryContext *context, const SceLsdbAppInfoFilter *filter, SceLsdbStringArray *title_ids, SceUInt32 flags);

/**
 * Return recently used titles in any requested application category.
 *
 * This is the query-context version of
 * ::sceLsdbGetRecentlyUsedTitleIdsByCategoriesFromDatabase. It uses the
 * process's shared AppDB.
 */
int sceLsdbQueryGetRecentlyUsedTitleIdsByCategories(SceLsdbQueryContext *context, const char *const *categories, SceSize category_count, SceInt32 max_title_count, SceLsdbStringArray *title_ids);

/** Resolve a URI through the process's shared AppDB connection. */
int sceLsdbQueryResolveUriTitleId(SceLsdbQueryContext *context, const char *uri, SceLsdbString *title_id, SceUInt32 flags);

/** Collect distinct URI prefixes through the process's shared AppDB connection. */
int sceLsdbQueryGetUriPrefixes(SceLsdbQueryContext *context, const char *const *schemes, SceSize scheme_count, SceLsdbStringArray *uri_prefixes);

/**
 * Return a standalone config string, or a copied \a default_value when the key
 * is absent or the query context is detached.
 */
SceLsdbString sceLsdbQueryGetConfigString(SceLsdbQueryContext *context, SceUInt32 key, const char *default_value);

/**
 * Return a 64-bit config value, or \a default_value when the key is absent or
 * the context is detached.
 */
SceInt64 sceLsdbQueryGetConfigInt64(SceLsdbQueryContext *context, SceUInt32 key, SceInt64 default_value);

/**
 * Test the query-context AppInfo-change flag and optionally clear it.
 *
 * Every AppInfo observer event in the calling process sets the flag to 1. When
 * \a clear is nonzero, FW 3.60 atomically changes the exact value 1 to 0. A
 * zero value only tests the flag. A detached context returns 0.
 */
int sceLsdbQueryContextTestAndClearFlag(SceLsdbQueryContext *context, SceBool clear);

/** Return theme IDs ordered by descending modification time. */
int sceLsdbQueryGetThemeIds(SceLsdbQueryContext *context, SceLsdbStringArray *theme_ids);

/**
 * Read one localized theme record.
 *
 * \a language_index selects the `titleN` and `providerN` columns directly. A
 * nonempty localized value replaces the corresponding default value. SceLsdb
 * writes every member except ::SceLsdbThemeInfo::vtable and the natural
 * alignment padding preceding ::SceLsdbThemeInfo::last_modified_time.
 */
int sceLsdbQueryGetTheme(SceLsdbQueryContext *context, const SceLsdbString *theme_id, SceInt32 language_index, SceLsdbThemeInfo *theme_info);

/** Return the sum of tbl_theme.size. */
SceInt64 sceLsdbQueryGetTotalThemeSize(SceLsdbQueryContext *context);

/**
 * Update a title's AppInfo value using a mask.
 *
 * For integer values, bits selected by \a mask are copied from \a value. String
 * values are replaced. SUPPORT_URI, `_fg_title_id`, and `_bg_title_id` are
 * protected and return ::SCE_LSDB_ERROR_PROTECTED_APPINFO_KEY. On success,
 * observers are called with ::SCE_LSDB_APP_INFO_EVENT_UPDATE_APP_INFO.
 */
int sceLsdbSetAppInfoValueMasked(const SceLsdbString *title_id, SceUInt32 key, const SceLsdbValue *value, SceUInt64 mask);

/**
 * Read one AppInfo value through the process's shared AppDB connection.
 *
 * @return ::SCE_LSDB_VALUE_TYPE_INT64 or ::SCE_LSDB_VALUE_TYPE_STRING on
 *         success, or a negative error code.
 */
int sceLsdbGetAppInfoValue(const SceLsdbString *title_id, SceUInt32 key, SceLsdbValue *value);

/** Store a string in tbl_config through the process's shared AppDB connection. */
int sceLsdbSetConfigString(SceUInt32 key, const char *value);

/**
 * Update an integer tbl_config value using a mask.
 *
 * The resulting value is (oldValue & ~mask) | (value & mask).
 */
int sceLsdbSetConfigInt64Masked(SceUInt32 key, SceInt64 value, SceUInt64 mask);

/**
 * Refresh the AppDB rows derived from an AppInfo object.
 *
 * First call ::sceLsdbOpen with ::SCE_LSDB_OPEN_MODE_NORMAL, call this
 * function while the process's shared connection remains open, and then call
 * ::sceLsdbClose. This function does not open or close the AppDB itself.
 *
 * FW 3.60 inserts or updates every key/value pair supplied in \a app_info in
 * `tbl_appinfo`. A TITLE_ID entry is required. SUPPORT_URI values also cause
 * the corresponding derived `tbl_uri` rows to be rebuilt. Localized STITLE
 * keys are updated only when the caller includes them. The function invokes
 * SceLsdb observers in the calling process with
 * ::SCE_LSDB_APP_INFO_EVENT_UPDATE_APP_INFO and commits the operation.
 *
 * This function does not read `sce_sys/icon0.png` or `sce_sys/pic0.png`, copy
 * either image into `ur0:appmeta`, update `tbl_appinfo_icon`, update its
 * localized bubble title, generate the `reserved05` rendered-icon blob,
 * invalidate SceShell's in-memory icon cache, or send the AppDB notification
 * expected by SceShell after a broader database change. App promotion and
 * recovery prepare paths such as `ur0:appmeta/<TITLE_ID>/icon0.png` separately.
 * SceShell's registered FW 3.60 observer for this event re-queries the icon row
 * to apply a changed parental-lock level; it does not discard or rebuild
 * the rendered icon cache.
 *
 * SceShell's separate icon-cache builder reads the path already stored in the
 * icon row, which can be that appmeta path or an application `sce_sys/icon0.png`
 * path, then writes the rendered cache through ::sceLsdbUpdateIconInfo.
 *
 * A pic0-related AppInfo key/path is stored if it is present in \a app_info,
 * but no image is opened, copied, decoded, or cached. There is no dedicated
 * pic0 refresh operation in this entry point. Language-wide localized AppInfo,
 * icon-title, and LiveArea updates use ::sceLsdbUpdateLocalizedData instead.
 *
 * The supplied reference and all nested values must remain valid until the
 * call returns; they are not used afterwards. FW 3.60 performs no process-ID,
 * application-lifecycle, foreground-title, or current-title check, so the
 * currently running or foreground title can be refreshed. The call may run on
 * a worker thread; it has no main-thread restriction. It has the same
 * private-module, AppDB-path, and registry privilege requirements described by
 * ::sceLsdbOpen. Do not call
 * it from an interrupt or exception context, and do not close or reopen the
 * process's shared AppDB concurrently.
 *
 * @param[in] app_info - Non-NULL AppInfo map containing at least TITLE_ID.
 *
 * @retval 0 The supplied rows and derived URI records were refreshed.
 * @retval SCE_LSDB_ERROR_INVALID_HANDLE ::sceLsdbOpen has not established a
 *         usable shared database connection for the process.
 * @retval SCE_LSDB_ERROR_REQUIRED_APPINFO_FIELD_MISSING TITLE_ID is absent.
 * @retval SCE_LSDB_ERROR_NO_MEMORY An internal allocation failed.
 * @return Other negative ActivityDb/SQLite errors can also be returned.
 */
int sceLsdbRefreshAppInfo(const SceLsdbAppInfo *app_info);

/** Return the FNV-1a key for STITLE or STITLE_00 through STITLE_19. */
SceUInt32 sceLsdbGetStitleKeyForLanguage(SceInt32 language_index);

/**
 * AppInfo field accessors.
 *
 * String results point into \a app_info and remain valid only while that object
 * remains alive. Integer fields use their database value or the FW 3.60
 * default selected by the getter.
 */
const char *sceLsdbGetStitle(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetTitle(const SceLsdbAppInfo *app_info);

/** Return the per-title `#_livearea_path` AppInfo string. */
const char *sceLsdbGetLiveAreaContentsPath(const SceLsdbAppInfo *app_info);

const char *sceLsdbGetOriginalPath(const SceLsdbAppInfo *app_info);
SceInt64 sceLsdbGetAttribute(const SceLsdbAppInfo *app_info);
SceInt64 sceLsdbGetLiveAreaType(const SceLsdbAppInfo *app_info);

/**
 * Return the SELF type-6 total memory budget in 1-KiB units.
 *
 * SceShell converts this value to bytes before passing it to AppMgr.
 */
SceInt64 sceLsdbGetTotalMemoryBudget(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetCategory(const SceLsdbAppInfo *app_info);

/** Return nonzero when CATEGORY is `gda`. */
int sceLsdbIsCategoryGda(const SceLsdbAppInfo *app_info);

SceInt64 sceLsdbGetPromoteAttribute(const SceLsdbAppInfo *app_info);

/** Return the AppMgr application name stored in AppInfo. */
const char *sceLsdbGetName(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetForegroundTitleId(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetBackgroundTitleId(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetTitleId(const SceLsdbAppInfo *app_info);

/**
 * Return SceShell's application-type classification.
 *
 * SceShell stores 0 for `gda`, `gdb`, and `wda` applications; 1 for ordinary
 * applications; and 2 for `NPXS10998`. Code on FW 3.60 also recognizes
 * value 3 for an application record without a SELF path.
 */
SceInt64 sceLsdbGetShellApplicationType(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetSelfPath(const SceLsdbAppInfo *app_info);

/** Return the SELF type-6 physically contiguous memory budget in 1-KiB units. */
SceInt64 sceLsdbGetPhysicalContiguousMemoryBudget(const SceLsdbAppInfo *app_info);

/** Return the attribute word from the SELF type-6 boot parameters. */
SceInt64 sceLsdbGetBootParamAttribute(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetAppVer(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetContentId(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetNpCommunicationId(const SceLsdbAppInfo *app_info);
SceInt64 sceLsdbGetSystemVersion(const SceLsdbAppInfo *app_info);

/**
 * Query game_plugin's application-type classification for \a app_info.
 *
 * FW 3.60 Shell handles value 1 as a native SELF launch, values 2 and 3
 * through the PSP emulator launchers, value 4 through
 * `ux0:app/PCSI00011/eboot.bin`, and value 5 through the per-title
 * `ux0:psm/<name>/runtime/eboot.bin`. A missing game_plugin interface or a
 * failed interface call produces 0.
 */
SceInt32 sceLsdbGetType(const SceLsdbAppInfo *app_info);

/**
 * Query game_plugin's metadata-location classification for \a app_info.
 *
 * Code inspected on FW 3.60 treats 0 as unavailable, reads
 * `ur0:appmeta/<title_id>/param.sfo` for value 1, and obtains `param.sfo`
 * through AppData mount ID 110 for values 2 and 3. The distinction between
 * values 2 and 3 is unknown.
 */
SceInt32 sceLsdbGetAppMetadataLocationType(const SceLsdbAppInfo *app_info);

const char *sceLsdbGetDiscId(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetGameDataId(const SceLsdbAppInfo *app_info);

/** Return PARENTAL_LEVEL, or -1 when it is absent or is not an integer. */
SceInt64 sceLsdbGetParentalLevel(const SceLsdbAppInfo *app_info);

/** Return BOOTABLE, or -1 when it is absent or is not an integer. */
SceInt64 sceLsdbGetBootable(const SceLsdbAppInfo *app_info);

/** Return the LiveArea system-version value stored in ATTRIBUTE bits 13 and 14. */
SceUInt32 sceLsdbGetLiveAreaSystemVersion(const SceLsdbAppInfo *app_info);

/**
 * Get the flag that disables Shell's LiveArea activities for a title.
 *
 * On FW 3.60, ATTRIBUTE bit 15 makes Shell skip activity refreshes and
 * game and system-software activity posts. It does not disable all LiveArea
 * resource updates. Use ::sceLsdbIsLiveAreaActivitySupported to also check
 * the application type.
 *
 * @param[in] app_info - Initialized AppInfo object; must not be NULL.
 *
 * @return ATTRIBUTE bit 15 as 0 or 1; 0 if ATTRIBUTE is absent or not an integer.
 */
SceUInt32 sceLsdbGetLiveAreaActivityDisabled(const SceLsdbAppInfo *app_info);

const char *sceLsdbGetBootInstallDir(const SceLsdbAppInfo *app_info);

/** Return nonzero for a game category or LiveArea system-version value 1 or 2. */
int sceLsdbIsGameCategoryOrLiveAreaSystemVersion1Or2(const SceLsdbAppInfo *app_info);

/** Return nonzero for a game category or the `EG` category. */
int sceLsdbIsGameOrEgCategory(const SceLsdbAppInfo *app_info);

/**
 * Check whether a title supports Shell's LiveArea activities.
 *
 * This checks the application type and metadata, not network availability.
 *
 * @param[in] app_info - Initialized AppInfo object; must not be NULL.
 *
 * @return 1 when ::sceLsdbGetType returns 1 and
 *         ::sceLsdbGetLiveAreaActivityDisabled returns 0; otherwise 0.
 */
int sceLsdbIsLiveAreaActivitySupported(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetContentLocation(const SceLsdbAppInfo *app_info);

/** Return the resolved path to the application's `sce_sys/pic0.png` image. */
const char *sceLsdbGetPic0Path(const SceLsdbAppInfo *app_info);

/**
 * Get the flag that disables Shell's cached application preview in LiveArea.
 *
 * On FW 3.60, Shell checks ATTRIBUTE bit 16 when creating the cached
 * framebuffer preview for the normal LiveArea launch/resume panel. This is
 * not a general screenshot-permission flag. Changing the metadata does not
 * necessarily discard an existing preview.
 *
 * @param[in] app_info - Initialized AppInfo object; must not be NULL.
 *
 * @return ATTRIBUTE bit 16 as 0 or 1; 0 if ATTRIBUTE is absent or not an integer.
 */
int sceLsdbGetLiveAreaPreviewDisabled(const SceLsdbAppInfo *app_info);

const char *sceLsdbGetLastLaunchTime(const SceLsdbAppInfo *app_info);
SceInt64 sceLsdbGetUpdateStatus(const SceLsdbAppInfo *app_info);
const char *sceLsdbGetSupportUri(const SceLsdbAppInfo *app_info);
/** Return the `INSTALL_DIR_SAVEDATA_ADD_1` AppInfo string. */
const char *sceLsdbGetInstallDirSavedataAdd1(const SceLsdbAppInfo *app_info);

/**
 * Get the requested extended game-memory mode.
 *
 * Reads ATTRIBUTE bits 34 through 36, which correspond to SFO ATTRIBUTE2
 * bits 2 through 4. On FW 3.60, these select additional game main RAM; see
 * ::SceLsdbExtendedMemoryMode. Shell also uses the mode to decide whether
 * another application can run alongside the game.
 *
 * This function only reads metadata; it does not allocate memory.
 *
 * @param[in] app_info - Initialized AppInfo object; must not be NULL.
 *
 * @return A value from 0 through 7; 0 if ATTRIBUTE is absent or not an integer.
 *         AppMgr rejects modes 4 through 7 on FW 3.60.
 */
SceInt64 sceLsdbGetExtendedMemoryMode(const SceLsdbAppInfo *app_info);

/**
 * Select the LiveArea compatibility mode for \a title_id.
 *
 * The default is ::SCE_LSDB_LIVEAREA_COMPATIBILITY_MODE_UNSPECIFIED. For a
 * title accepted by SceCompatForVsh, FW 3.60 returns
 * ::SCE_LSDB_LIVEAREA_COMPATIBILITY_MODE_ON when game_plugin state is zero.
 * When that state is nonzero or unavailable, it returns
 * ::SCE_LSDB_LIVEAREA_COMPATIBILITY_MODE_OFF only if the configured NP country
 * is `jp`; otherwise it retains the default.
 *
 * @return One of ::SceLsdbLiveAreaCompatibilityMode.
 */
SceLsdbLiveAreaCompatibilityMode sceLsdbGetLiveAreaCompatibilityMode(const char *title_id);

/**
 * Open the process's shared AppDB connection.
 *
 * Call ::sceLsdbOpen with ::SCE_LSDB_OPEN_MODE_NORMAL before using global
 * query or refresh entry points, keep the connection open until all such work
 * has finished, then call ::sceLsdbClose. Do not call Open twice without an
 * intervening Close. ::SCE_LSDB_OPEN_MODE_REBUILD is destructive: it removes
 * and reconstructs the AppDB before opening it and should be used only for
 * database recovery.
 *
 * FW 3.60 stores the disk database at `ur0:shell/db/app.db`. The absolute value
 * of \a mode is checked and stored as its primary version; the supported value
 * is 59. Other values are not additional access flags and produce an
 * incompatible database.
 *
 * SceLsdb is a private user-mode module at
 * `vs0:vsh/shell/livespace_db.suprx`. It performs no explicit caller-PID check,
 * but the process must be authorized to load that module and access the Shell
 * database and registry state. An ordinary sandboxed application does not
 * have that calling environment. Call from a normal user thread on which
 * blocking filesystem/database work is allowed, not from an interrupt or
 * exception context. Worker threads are supported; there is no main-thread
 * restriction. All threads in a process share one database connection. Do
 * not let opens, closes, reopens, transactions, queries, or refreshes run
 * concurrently.
 *
 * @param[in] mode - One of ::SceLsdbOpenMode.
 *
 * @retval 0 The AppDB was opened.
 * @retval SCE_LSDB_ERROR_NO_MEMORY An internal allocation failed.
 * @retval SCE_LSDB_ERROR_DATABASE_LANGUAGE_MISMATCH The stored system-language
 *         component differs from the current value.
 * @retval SCE_LSDB_ERROR_DATABASE_CONFIGURATION_MISMATCH The stored
 *         region/environment component differs from the current value.
 * @retval SCE_LSDB_ERROR_DATABASE_SCHEMA_TOO_NEW The on-disk schema is newer
 *         than the FW 3.60 implementation supports.
 * @retval SCE_LSDB_ERROR_DATABASE_VERSION_MISMATCH The primary AppDB version
 *         is not 59.
 * @retval SCE_LSDB_ERROR_INVALID_DATABASE_VERSION The primary or schema
 *         version is zero or otherwise uninitialized.
 * @return ActivityDb/Dbutil errors, including 0x801010F5, 0x801010FE, and
 *         0x801010FF, can also be returned; the exact condition for each error
 *         is unknown.
 */
int sceLsdbOpen(SceLsdbOpenMode mode);

/**
 * Close the process's shared AppDB connection and release its model helpers.
 *
 * Do not call this while another thread is using the connection. The FW 3.60
 * wrapper returns 0, including when the connection is already closed.
 */
int sceLsdbClose(void);

/**
 * Replace the process's shared on-disk AppDB connection with an in-memory
 * database.
 *
 * FW 3.60 closes the current handle and opens `:memory:` with version 0. This
 * is not an ordinary reopen of `ur0:shell/db/app.db` and must not be used to
 * implement a normal open/close sequence.
 */
int sceLsdbReopen(void);

/**
 * Rebuild localized AppInfo and LiveArea data for a language index.
 *
 * FW 3.60 updates the ActivityDb language field only when both rebuilds
 * succeed. Once it acquires the database, this function returns 0 even when
 * either rebuild fails.
 */
int sceLsdbUpdateLocalizedData(SceInt32 language_index);

/**
 * Return the language index stored in the open Activity database.
 *
 * An ActivityDb error is returned when the process's shared database is not
 * open or the version information cannot be read.
 */
SceInt32 sceLsdbGetDatabaseLanguageIndex(void);

/**
 * Delete every NewEvent row and rebuild every LiveArea row from its stored
 * contents path.
 *
 * FW 3.60 ignores the delete and per-title refresh results and returns 0 after
 * acquiring the NewEvent database.
 */
int sceLsdbResetNewEventsAndLiveArea(void);

/** Return the AppInfo daemon's most recently recorded AppDB error. */
int sceLsdbGetLastAppDatabaseError(void);

/**
 * Return tbl_config key 1 as a standalone string.
 *
 * A missing value or unavailable database returns an empty string.
 */
SceLsdbString sceLsdbGetLiveAreaPath(void);

/** Store \a value in tbl_config key 1, the LiveArea path shared by the process. */
int sceLsdbSetLiveAreaPath(const SceLsdbString *value);

/** Return the shell's current system-language index, or 1 when unavailable. */
SceInt32 sceLsdbGetSystemLanguageIndex(void);

/**
 * Return the configured system region as a standalone string.
 *
 * Registry failure returns an empty string.
 */
SceLsdbString sceLsdbGetRegion(void);

/**
 * Select the language index used to parse LiveArea content.
 *
 * LiveArea system version 1 ignores \a language_index and maps the registered
 * `/CONFIG/NP/lang` string to an index from 0 through 19; registry failure or
 * an unknown string returns -1. Other LiveArea system versions return an
 * explicit index from 0 through 19 unchanged. Any other value, including -1,
 * selects the shell's current system language, or 1 when shell state is not
 * available.
 */
SceInt32 sceLsdbMapLanguageIndex(SceUInt32 live_area_system_version, SceInt32 language_index);

/**
 * Return `/CONFIG/NP/lang` as a standalone string.
 *
 * Registry failure returns an empty string.
 */
SceLsdbString sceLsdbGetNpLanguage(void);

/**
 * Return the country used to select localized LiveArea content.
 *
 * LiveArea system version 2 first requests the country from the loaded
 * telephony plugin. If the plugin is unavailable or rejects the request, and
 * for every other version, the function returns `/CONFIG/NP/country`.
 * Failure of both sources returns an empty standalone string.
 */
SceLsdbString sceLsdbGetCountry(SceUInt32 live_area_system_version);

/** Convert an integer to 0 or 1. */
SceBool sceLsdbNormalizeBool(SceInt32 value);

/**
 * Install the callback used when obtaining content-rating information.
 *
 * The supplied callback is stored process-wide and is also returned. The
 * previous callback is not returned.
 */
SceLsdbContentRatingCallback sceLsdbSetContentRatingCallback(SceLsdbContentRatingCallback callback);

/**
 * Return the current user's content-rating limit or age.
 *
 * When the content-rating callback succeeds, the configured rating is
 * returned if restrictions are enabled, and -1 is returned if they are
 * disabled. When the callback fails, FW 3.60 calculates the age from the
 * registered year, month, and day of birth. Invalid or unavailable registry
 * data, RTC failure, and a future date of birth return 0.
 */
SceInt32 sceLsdbGetUserContentRating(void);

/**
 * Return `/CONFIG/NP/env` as a standalone string.
 *
 * Registry failure returns an empty string.
 */
SceLsdbString sceLsdbGetNpEnvironment(void);

/**
 * Initialize a NewEvent notification wrapper without attaching it to the
 * database.
 *
 * Both entry points set ::SceLsdbNewEventDatabase::notification_flag to NULL
 * and otherwise have the same behavior on FW 3.60.
 */
SceLsdbNewEventDatabase *sceLsdbNewEventDatabaseInit(SceLsdbNewEventDatabase *database);
SceLsdbNewEventDatabase *sceLsdbNewEventDatabaseInit2(SceLsdbNewEventDatabase *database);

/**
 * Attach a NewEvent notification wrapper to the process's shared database.
 *
 * First call ::sceLsdbOpen. This function allocates a four-byte flag and
 * registers an observer for the calling process; it does not open a separate
 * database.
 * Call ::sceLsdbNewEventDatabaseClose before ::sceLsdbClose.
 *
 * @retval 0 The wrapper was attached.
 * @retval SCE_LSDB_ERROR_INVALID_HANDLE The process's shared AppDB is not open,
 *         or this wrapper is already attached.
 * @retval SCE_LSDB_ERROR_NO_MEMORY The notification flag could not be
 *         allocated.
 */
int sceLsdbNewEventDatabaseOpen(SceLsdbNewEventDatabase *database);

/**
 * Detach a NewEvent notification wrapper and release its flag.
 *
 * This succeeds when the wrapper is already detached.
 */
int sceLsdbNewEventDatabaseClose(SceLsdbNewEventDatabase *database);

/**
 * Insert one NewEvent row.
 *
 * When \a replace_existing is nonzero, an existing row identified by the
 * supplied title/item pair or row ID is deleted before the replacement is
 * inserted. With zero, an existing row returns
 * ::SCE_LSDB_ERROR_DATABASE_CONSTRAINT.
 *
 * Before inserting a new row, FW 3.60 keeps the active-row target at 64 by
 * marking the oldest rows whose message type is at least 80 as deleted. An
 * empty update time stores the current time. The function assigns the row ID,
 * hash, popup number, and derived action-type high word back to \a event.
 * A nonempty update time is validated only for a minimum length of 19 and the
 * separators at byte positions 4, 7, 10, 13, and 16.
 */
int sceLsdbInsertNewEvent(SceLsdbNewEvent *event, SceBool replace_existing);

/**
 * Update selected fields of existing, nondeleted NewEvent rows.
 *
 * Each object identifies a row by a nonzero row_id or by nonempty title_id and
 * item_id strings. Only fields selected by \a update_mask are compared and
 * written. Every changed row receives an incremented hash value.
 *
 * When the time field is selected, a nonempty update_time must contain at least
 * 19 bytes and have `-`, `-`, space, `:`, and `:` at byte positions 4, 7, 10,
 * 13, and 16. FW 3.60 does not validate the other bytes as digits. An empty
 * value stores the current time. When icon data is selected, a nonzero
 * icon_data_size requires a non-NULL icon_data pointer. If both the stored and
 * supplied popup_flag values are nonzero, FW 3.60 preserves a copy of the
 * previous popup row before assigning a new popup number to the updated row.
 * The action-type bit compares only `action_type_low`; changing it stores its
 * signed 64-bit form and does not preserve the supplied `action_type_high`.
 *
 * @param[in] events - Array of reference-counted NewEvent objects.
 * @param[in] count - Number of elements in \a events.
 * @param[in] update_mask - Bitwise OR of ::SceLsdbNewEventUpdateFlag values;
 *                         must not be zero.
 *
 * @return 0 when at least one row changed, or a negative ::SceLsdbErrorCode
 *         value.
 */
int sceLsdbUpdateNewEvents(const SceLsdbNewEventRef *events, SceSize count, SceUInt32 update_mask);

/**
 * Mark selected nondeleted events as deleted.
 *
 * Each selector uses a nonzero row ID or both title and item IDs. Rows whose
 * popup number is already zero are physically removed by the NewEvent table's
 * auto-delete trigger; popup rows remain until their popup number is cleared.
 * The function returns ::SCE_LSDB_ERROR_NOT_FOUND when no selector changes a
 * row.
 */
int sceLsdbMarkNewEventsDeleted(const SceLsdbNewEventSelector *selectors, SceSize count);

/**
 * Delete NewEvent rows.
 *
 * A zero \a selective value deletes every row. A nonzero value marks only
 * nondeleted rows whose message type is at least 80 as deleted; rows with a
 * lower message type are preserved.
 */
int sceLsdbDeleteNewEvents(SceUInt8 selective);

/**
 * Read one nondeleted NewEvent row.
 *
 * On entry, \a event must identify the row with a nonzero row ID or with both
 * a nonempty title ID and item ID. On success, every field in \a event that
 * comes from the database is replaced. `icon_data` remains NULL and
 * `icon_data_size` receives the stored BLOB length; use
 * ::sceLsdbGetNewEventIconData to read the bytes.
 */
int sceLsdbGetNewEvent(SceLsdbNewEventDatabase *database, SceLsdbNewEvent *event);

/**
 * Enumerate nondeleted NewEvent rows.
 *
 * FW 3.60 limits \a max_count to 64. The optional \a total_count and \a new_count
 * outputs are also capped at 64; neither reports database totals above 64.
 * Existing contents of \a events are released before the result is written.
 * When \a clear_notification is nonzero, the calling process's
 * pending-notification flag is cleared after a successful query.
 */
int sceLsdbGetNewEvents(SceLsdbNewEventDatabase *database, SceLsdbNewEventRefArray *events, SceSize max_count, SceSize *total_count, SceSize *new_count, SceBool clear_notification);

/**
 * Return the read-only icon-data BLOB for an existing NewEvent row ID.
 *
 * The returned stream opens the database BLOB only when needed. \a error is
 * optional and receives the stream creation result; an error returns an empty
 * reference.
 */
SceLsdbDbBlobRef sceLsdbGetNewEventIconData(SceLsdbNewEventDatabase *database, const SceInt64 *row_id, int *error);

/** Return whether this wrapper's change flag for the calling process is set. */
SceBool sceLsdbHasPendingNewEventNotification(SceLsdbNewEventDatabase *database);

/**
 * Clear the calling process's pending NewEvent notification state.
 *
 * This function returns no value and does nothing when the wrapper is closed.
 */
void sceLsdbClearPendingNewEventNotification(SceLsdbNewEventDatabase *database);

/**
 * Return the number of rows whose popup number is nonzero.
 *
 * FW 3.60 maintains this process-wide count through the NewEvent table's
 * insert/update triggers. The wrapper must be open.
 */
int sceLsdbGetNewEventPopupCount(SceLsdbNewEventDatabase *database);

/**
 * Read the row with the smallest positive popup number.
 *
 * When no such row exists, FW 3.60 returns ::SCE_LSDB_ERROR_NOT_FOUND and
 * resets the process-wide popup count to zero.
 */
int sceLsdbGetFirstPopupNewEvent(SceLsdbNewEventDatabase *database, SceLsdbNewEvent *event);

/** Set popup_no to zero for the selected row. */
int sceLsdbClearNewEventPopup(SceLsdbNewEventDatabase *database, const SceInt64 *row_id);

/** Set popup_no to zero for all rows. */
int sceLsdbClearNewEventPopups(SceLsdbNewEventDatabase *database);

/**
 * Update new_flag for an array of existing, nondeleted NewEvent rows.
 *
 * Each object identifies a row by a nonzero row_id or by nonempty title_id and
 * item_id strings. Every changed row receives an incremented hash value. Unlike
 * ::sceLsdbUpdateNewEvents, this function does not preserve a copy of the
 * previous popup row.
 */
int sceLsdbUpdateNewEventFlags(SceLsdbNewEventDatabase *database, const SceLsdbNewEventRef *events, SceSize count);

/** Clear new_flag and increment hash for every new row. */
int sceLsdbClearNewEventFlags(SceLsdbNewEventDatabase *database);

/**
 * Derive the high 32 bits of a NewEvent action type for \a title_id.
 *
 * FW 3.60 returns the configured value for `LAUPDATE`, `LOGSTATUS0`,
 * `BGCPSTATUS`, or `NPXS10006`. For another title it reads AppInfo key
 * 0x5142196B and returns bits 1 through 3 when bit 0 is set. The fallback is
 * 0xE, including when \a database is not open.
 */
SceUInt32 sceLsdbGetNewEventActionTypeHigh(SceLsdbNewEventDatabase *database, const SceLsdbString *title_id);

/**
 * Test a time interval against the current RTC or ad-network clock.
 *
 * The interval `{ 0, UINT64_MAX }` always matches without reading a
 * clock. With \a ignore_start_time set to zero, both endpoints are inclusive.
 * With it nonzero, FW 3.60 first rejects an interval whose start is after its
 * end, then tests only whether the current tick is at or before \a range's
 * end. A clock-read error returns false.
 */
SceBool sceLsdbIsCurrentTimeInRange(const SceLsdbTimeRange *range, SceBool ignore_start_time, SceBool use_ad_network_clock);

/**
 * Initialize caller-provided storage for one parsed LiveArea frame.
 *
 * The function initializes the nested strings and item vector and returns
 * \a frame. It does not allocate the structure itself.
 */
SceLsdbLiveAreaFrame *sceLsdbLiveAreaFrameInit(SceLsdbLiveAreaFrame *frame);

/** Return one indexed liveitem from a parsed frame, or NULL. */
SceLsdbLiveAreaFrameItem *sceLsdbLiveAreaFrameGetItem(const SceLsdbLiveAreaFrame *frame, SceSize index);

/**
 * Initialize caller-provided storage for an empty parsed LiveArea object list.
 *
 * The function allocates the circular list's head node, which has no object,
 * and returns \a frame_list.
 */
SceLsdbLiveAreaFrameList *sceLsdbLiveAreaFrameListInit(SceLsdbLiveAreaFrameList *frame_list);

/**
 * Destroy every object and list node owned by a parsed LiveArea frame list.
 *
 * The caller still owns the outer \a frame_list storage.
 */
SceLsdbLiveAreaFrameList *sceLsdbLiveAreaFrameListEnd(SceLsdbLiveAreaFrameList *frame_list);

/**
 * Parse an exact `NN.NN` version string.
 *
 * The four digits are returned as one decimal integer; for example, `01.04`
 * returns 104. Invalid length, digits, or separator return -1. Both exports
 * have identical behavior on FW 3.60.
 */
SceInt32 sceLsdbParseVersion(const SceLsdbString *version);
SceInt32 sceLsdbParseVersion2(const SceLsdbString *version);

/**
 * Initialize a LiveArea parser for \a contents_path.
 *
 * When \a filter_hardware_model is nonzero, XML choices whose `model` attribute
 * does not match the current hardware are discarded. When
 * \a fallback_to_default_template is nonzero and \a contents_path cannot be
 * opened, ::sceLsdbParseLiveAreaTemplate parses the built-in default template
 * and sets ::SceLsdbLiveAreaParser::using_default_template.
 */
SceLsdbLiveAreaParser *sceLsdbLiveAreaParserInit(SceLsdbLiveAreaParser *parser, const char *contents_path, SceBool filter_hardware_model, SceBool fallback_to_default_template);

/** Release a LiveArea parser. */
SceLsdbLiveAreaParser *sceLsdbLiveAreaParserEnd(SceLsdbLiveAreaParser *parser);

/**
 * Parse the template selected by \a parser into a reference-counted frame list.
 *
 * A successful call replaces \a parser's existing parsed-frame reference and
 * returns 0. FW 3.60 rejects a non-fallback input larger than 0x8000 bytes.
 * Negative return values -1 through -6 distinguish file, allocation, XML, and
 * size failures; they are private parser errors, not ::SceLsdbErrorCode values.
 */
int sceLsdbParseLiveAreaTemplate(SceLsdbLiveAreaParser *parser);

/**
 * Apply locale and content-rating selection to a parsed template.
 *
 * \a language_index points to the selected language, \a country is the raw
 * country code, and \a content_rating is the current user rating. A NULL
 * language pointer and a NULL or empty country preserve the existing
 * selections. The function returns true.
 */
SceBool sceLsdbLiveAreaParserSetLocale(SceLsdbLiveAreaParser *parser, const SceInt32 *language_index, const char *country, SceInt32 content_rating);

/**
 * Select the built-in default template in an initialized LiveArea parser.
 *
 * This replaces ::SceLsdbLiveAreaParser::contents_path with
 * `vs0:data/internal/livearea/default/sce_sys/livearea/contents/template.xml`,
 * sets ::SceLsdbLiveAreaParser::using_default_template, and returns true.
 */
SceBool sceLsdbLiveAreaParserSetDefaultTemplate(SceLsdbLiveAreaParser *parser);

/** Read the current RTC tick. */
int sceLsdbGetCurrentRtcTick(SceRtcTick *tick);

/** Read the ad-network RTC tick. The output is written only on success. */
int sceLsdbGetAdNetworkRtcTick(SceRtcTick *tick);

/**
 * Parse one LiveArea frame XML document and return its frame object.
 *
 * On success, \a frame receives a newly allocated frame removed from the
 * temporary parser's object list. The caller owns that frame and its nested
 * objects; FW 3.60 releases such objects through vtable slot 1.
 *
 * \a compatibility_mode is supplied by SceShell for type-3 applications but is
 * ignored by this FW 3.60 export. The function returns false for allocation,
 * XML, or missing-frame failures.
 */
SceBool sceLsdbParseLiveAreaFrame(SceLsdbLiveAreaFrame **frame, const void *xml, SceSize xml_length, const SceInt32 *language_index, const char *country, SceInt32 content_rating, SceBool filter_hardware_model, SceLsdbLiveAreaCompatibilityMode compatibility_mode);

/**
 * Read and parse the stored LiveArea template for one title and target type.
 *
 * \a unused is ignored on FW 3.60. \a target_type is one of
 * ::SceLiveAreaTargetType; the byte-sized declaration matches this export's
 * ABI. The result is filtered for locale, content rating, hardware model, and
 * compatibility mode. Expired database frame rows discovered during a
 * successful read are deleted. \a frames receives an owning strong reference.
 */
int sceLsdbGetLiveAreaFrames(void *unused, SceLsdbLiveAreaFrameListRef *frames, const SceLsdbString *title_id, SceUInt8 target_type);

/**
 * Return one `ur0:`-backed LiveArea title absent from \a title_ids.
 *
 * FW 3.60 performs this lookup only when at least 88 `ur0:` LiveArea rows
 * exist. Candidates are ordered by AppInfo key 0x4C5BFEC6. The first missing
 * title is copied to \a title_id; no candidate returns
 * ::SCE_LSDB_ERROR_NOT_FOUND. \a unused is ignored.
 */
int sceLsdbGetLiveAreaTitleIdNotInList(void *unused, const SceLsdbStringArray *title_ids, SceLsdbString *title_id);

/**
 * Read tbl_livearea_frame.userdata.
 *
 * When both normal and retail rows exist, the row with the lowest database
 * type is selected. No matching title/frame pair returns
 * ::SCE_LSDB_ERROR_NOT_FOUND. Both \a unused and \a activity_db_handle are
 * ignored on FW 3.60.
 */
int sceLsdbGetLiveAreaFrameUserData(void *unused, const SceLsdbString *title_id, const SceLsdbString *frame_id, SceLsdbString *user_data, void *activity_db_handle);

/**
 * Does nothing on FW 3.60.
 *
 * SceShell passes the title ID as a ::SceLsdbString object and the LiveArea
 * contents path as a NUL-terminated string, but FW 3.60 ignores both
 * arguments.
 */
void sceLsdb_29B275BA(const SceLsdbString *title_id, const char *contents_path);

/**
 * Refresh LiveArea rows from their stored contents paths.
 *
 * An empty \a title_id refreshes every title. For a nonempty title,
 * \a original_path receives its stored `org_path` when non-NULL. FW 3.60 returns
 * success even when a per-title refresh fails; database setup failures are
 * returned.
 */
int sceLsdbRefreshLiveAreaRecords(const SceLsdbString *title_id, SceLsdbString *original_path);

/**
 * Replace all stored LiveArea contents for one title.
 *
 * The template at \a contents_path is parsed, its assets are staged in
 * `ur0:appmeta` when necessary, and both the main LiveArea row and frame rows
 * are replaced. \a last_modified is copied into the resulting frame-list
 * metadata. \a change_flags receives a bitwise OR of
 * ::SceLsdbLiveAreaChangeFlag values. \a resolved_title_id receives the title ID
 * selected by SceLsdb. \a unused is ignored on FW 3.60.
 */
int sceLsdbReplaceLiveAreaContents(void *unused, const SceLsdbString *title_id, const SceLsdbString *contents_path, SceUInt32 *change_flags, const SceRtcTick *last_modified, SceLsdbString *resolved_title_id, ScePID process_id);

/**
 * Update one or more already parsed LiveArea frame records.
 *
 * \a target_type is one of ::SceLiveAreaTargetType. Normal target type 0 is
 * stored as database type 1; retail target type 1 is stored as database type
 * 0 and takes precedence in ordered frame queries. \a change_flags receives a
 * bitwise OR of ::SceLsdbLiveAreaChangeFlag values. \a resolved_title_id
 * receives the selected title ID. \a unused is ignored on FW 3.60.
 */
int sceLsdbUpdateLiveAreaFrames(void *unused, const SceLsdbString *title_id, const SceLsdbLiveAreaFrameListRef *frames, const SceLsdbString *contents_path, SceUInt8 target_type, SceUInt32 *change_flags, SceLsdbString *resolved_title_id, ScePID process_id);

/**
 * Return whether a system-function-zone entry has the requested type.
 *
 * \a unused is ignored on FW 3.60.
 */
SceBool sceLsdbLiveAreaSfEntryExists(void *unused, const SceLsdbString *title_id, SceInt32 type);

/**
 * Read pccUpdDate, pccResStatus, and pccSignOff for one title.
 *
 * ::SceLsdbLiveAreaPccInfo::resource_status receives the stored pccResStatus
 * plus one. \a unused is ignored on FW 3.60.
 */
int sceLsdbGetLiveAreaPccInfo(void *unused, const SceLsdbString *title_id, SceLsdbLiveAreaPccInfo *pcc_info);

/**
 * Update PCC information and the empty system-function-zone slot for one title.
 *
 * \a unused is ignored on FW 3.60. When \a include_empty_sf_type0_entry is
 * nonzero, a `{ type = 0, target = "" }` system-function-zone entry is added
 * if needed; when it is zero, one such entry is removed. \a update_flags is a
 * bitwise OR of ::SceLsdbLiveAreaPccUpdateFlag values and selects the fields
 * copied from \a pcc_info.
 */
int sceLsdbUpdateLiveAreaPccInfo(void *unused, const SceLsdbString *title_id, SceBool include_empty_sf_type0_entry, const SceLsdbLiveAreaPccInfo *pcc_info, SceUInt32 update_flags);

/**
 * Add or replace one sfType/sfTarg pair in a title's LiveArea record.
 *
 * A missing system-function-zone object is created. \a unused is ignored.
 */
int sceLsdbSetLiveAreaSfEntry(void *unused, const SceLsdbString *title_id, const SceLsdbLiveAreaSfEntry *entry);

/**
 * Delete the sfType/sfTarg pair whose sfType equals \a type.
 *
 * A missing zone or type returns ::SCE_LSDB_ERROR_NOT_FOUND. \a unused is
 * ignored.
 */
int sceLsdbDeleteLiveAreaSfEntry(void *unused, const SceLsdbString *title_id, SceInt32 type);

/**
 * Read and decode tbl_livearea.modified_date for one title.
 *
 * A missing row returns ::SCE_LSDB_ERROR_NOT_FOUND. \a unused is ignored.
 */
int sceLsdbGetLiveAreaModifiedDate(void *unused, const SceLsdbString *title_id, SceRtcTick *last_modified);

/** Set tbl_livearea.modified_date for one title. */
int sceLsdbSetLiveAreaModifiedDate(void *unused, const SceLsdbString *title_id, const SceRtcTick *last_modified);

/**
 * Rebuild one title's normal-layer frame rows from `template.xml` under
 * \a contents_path.
 */
int sceLsdbUpdateLiveAreaFromContents(const SceLsdbString *title_id, const char *contents_path);

/** Delete the stored LiveArea record for one title. */
int sceLsdbDeleteLiveArea(const SceLsdbString *title_id);

/**
 * Read a stored LiveArea revision.
 *
 * When \a frame_id is non-NULL, \a revision receives the matching frame
 * revision from the lowest database type and \a original_path is not written.
 * Otherwise, \a revision receives the content revision and the optional
 * \a original_path receives tbl_livearea.org_path.
 */
int sceLsdbGetLiveAreaRevision(const SceLsdbString *title_id, const char *frame_id, SceUInt64 *revision, SceLsdbString *original_path);

/**
 * Decrement the icon-layout open count and release the INI context at zero.
 *
 * Calling this at open count zero returns -1. For a nested open it returns the
 * remaining positive count; the final close returns the INI finalization
 * result.
 */
int sceLsdbIconLayoutClose(void);

/**
 * Open or create `ux0:iconlayout.ini` and increment the nested open count.
 * A failed open restores the previous count.
 */
int sceLsdbIconLayoutOpen(void);

/** Delete ux0:iconlayout.ini. A missing file is treated as success. */
int sceLsdbIconLayoutDeleteFile(void);

/** Return whether ux0:iconlayout.ini exists. */
SceBool sceLsdbIconLayoutFileExists(void);

/** Enable or disable icon-layout writes. The supplied value is returned. */
SceBool sceLsdbIconLayoutSetWritesDisabled(SceBool disabled);

/**
 * Read one icon-layout entry by title ID.
 *
 * The return value is false for a missing key, malformed value, or file/open
 * error. A successful special-page result owns the nonempty
 * \a entry->parent_title_id allocation; release it with ::sce_paf_free.
 */
SceBool sceLsdbIconLayoutGetEntry(const char *title_id, SceLsdbIconLayoutEntry *entry);

/**
 * Write one icon-layout entry by title ID.
 *
 * Normal entries store only page and position. Special-page entries also
 * store the parent coordinates and NUL-terminated parent title ID;
 * \a entry->parent_title_id_length is not read. Writes-disabled mode returns 0
 * without changing the file.
 */
int sceLsdbIconLayoutSetEntry(const char *title_id, const SceLsdbIconLayoutEntry *entry);

/** Delete one icon-layout entry. */
int sceLsdbIconLayoutDeleteEntry(const char *title_id);

/**
 * Update selected parent fields of an icon-layout entry selected by page.
 *
 * FW 3.60 updates the first parsed entry whose page number equals \a page_no;
 * it does not select by title ID. No matching entry is treated as success.
 * NULL page, position, or title pointers leave the corresponding field
 * unchanged.
 */
int sceLsdbIconLayoutUpdateParentByPageNo(SceInt32 page_no, const SceInt32 *parent_page_no, const SceInt32 *parent_position, const char *parent_title_id);

/**
 * Increment or decrement each stored page number at or above \a page_no.
 *
 * Only the entry's own page number is changed; parent page numbers are not.
 * When writes are disabled, this function returns success without changing
 * the file.
 */
int sceLsdbIconLayoutShiftPages(SceBool increment, SceInt32 page_no);

/**
 * Return whether any successfully parsed entry exactly matches \a page_no and
 * \a position. The function does not check whether arguments are in range and
 * returns zero for file, open, or parse errors.
 */
SceBool sceLsdbIconLayoutPositionExists(SceInt32 page_no, SceInt32 position);

/**
 * Broken FW 3.60 special-page counter.
 *
 * The implementation intends to collect distinct special negative page
 * numbers, but its insertion condition is inverted while the local vector
 * starts empty. Consequently this export returns 0 for every parsed file on FW
 * 3.60.
 */
int sceLsdbIconLayoutGetSpecialPageCount(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_LSDB_H_ */
