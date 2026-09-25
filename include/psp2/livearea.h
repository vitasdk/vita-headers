/**
 * \usergroup{SceLiveAreaUtil}
 * \usage{psp2/livearea.h,SceLiveArea_stub SceLiveAreaUtilBgApp_stub,SCE_SYSMODULE_LIVEAREA}
 */

#ifndef _PSP2_LIVEAREA_H_
#define _PSP2_LIVEAREA_H_

#include <psp2/types.h>
#include <psp2common/kernel/rtc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * LiveArea frame database layer.
 *
 * Pass the source directory separately to the update function. The
 * paths below are the conventional source locations. Retail frames take
 * precedence over normal frames when both variants of the same frame exist.
 */
typedef enum SceLiveAreaTargetType {
	SCE_LIVEAREA_TARGET_TYPE_NORMAL = 0, //!< Normal layer, conventionally from `sce_sys/livearea/contents`.
	SCE_LIVEAREA_TARGET_TYPE_RETAIL = 1  //!< Retail override layer, usually from `sce_sys/retail/livearea/contents`.
} SceLiveAreaTargetType;

/**
 * Poll an asynchronous LiveArea operation.
 *
 * Only one LiveArea operation can be pending in a process at a time.
 * SceShell runs the operation independently; this function only checks whether
 * it has finished and returns its result. The final result is returned once,
 * then the pending request is cleared for the process. Later calls report no
 * request until another operation is submitted.
 *
 * @retval 1 The operation is still pending.
 * @retval 0 The operation completed successfully. The pending request is
 * cleared.
 * @retval 0x80104001 No operation is pending. This is also returned after a
 * final result has already been returned.
 * @return Another negative value is the final error returned by SceShell;
 * returning it also clears the pending request.
 */
int sceLiveAreaGetStatus(void);

/**
 * Replace all LiveArea data for the calling title synchronously.
 *
 * Normally the target is the title associated with the calling process. After
 * ::sceLiveAreaEnableBgAppMode is called, the target title is instead read
 * from the caller's `_fg_title_id` LSDB property.
 *
 * @param[in] contents_path - Directory containing the replacement LiveArea data.
 * The path must contain at most 255 characters.
 *
 * @note On retail FW 3.60, this implicit-title variant requires the original
 * source path to begin with `app0:` or `savedata0:`. An `app0:` path under
 * `/sce_` is limited to `sce_sys/livearea/contents` or
 * `sce_sys/retail/livearea/contents`. Use
 * ::sceLiveAreaReplaceAllForTitleSync with a non-empty title ID for a source
 * staged under `ux0:data`.
 *
 * @retval 0 The replacement completed successfully.
 * @retval 0x80104002 \a contents_path is NULL or longer than 255 characters.
 * @retval 0x80104003 SceShell could not resolve the source path through the
 * caller's FIOS overlays.
 * @retval 0x8010400B The source path is not permitted by the implicit-title
 * path policy.
 * @return Another negative error code returned by SceShell or LSDB.
 */
int sceLiveAreaReplaceAllSync(const char *contents_path);

/**
 * Replace all LiveArea data for the calling title asynchronously.
 *
 * Normally the target is the title associated with the calling process. After
 * ::sceLiveAreaEnableBgAppMode is called, the target title is instead read
 * from the caller's `_fg_title_id` LSDB property.
 *
 * Poll ::sceLiveAreaGetStatus to obtain the final result.
 *
 * @param[in] contents_path - Directory containing the replacement LiveArea data.
 * The path must contain at most 255 characters.
 *
 * @note The source-path restrictions documented for
 * ::sceLiveAreaReplaceAllSync also apply to this function.
 *
 * You may reuse or free the \a contents_path string after this function returns,
 * even if the operation is still running.
 *
 * @retval 0 The operation was submitted.
 * @retval 0x80104001 Another asynchronous operation is still pending.
 * @retval 0x80104002 \a contents_path is NULL or longer than 255 characters.
 * @return Another negative submission error.
 */
int sceLiveAreaReplaceAllAsync(const char *contents_path);

/**
 * Replace all LiveArea data for a title synchronously.
 *
 * @param[in] contents_path - Directory containing the replacement LiveArea data.
 * The path must contain at most 255 characters.
 * @param[in] title_id - Target title ID. If NULL or empty, SceShell normally
 * uses the calling process's title. After ::sceLiveAreaEnableBgAppMode is called,
 * a NULL or empty value instead selects the title in the caller's `_fg_title_id`
 * LSDB property.
 * @param[in] last_modified - Modification time to store with the LiveArea data,
 * or NULL to store a zero tick. Exactly eight bytes are copied into the request
 * during the call.
 *
 * @note On FW 3.60, selecting the ForTitle export bypasses the implicit
 * `app0:`/`savedata0:` source allowlist, independently of whether \a title_id is
 * empty. This permits externally staged sources such as `ux0:data`. Supply a
 * non-empty \a title_id to avoid implicit target resolution.
 *
 * @retval 0 The replacement completed successfully.
 * @retval 0x80104002 \a contents_path is NULL or longer than 255 characters.
 * @retval 0x80104003 SceShell could not resolve the source path through the
 * caller's FIOS overlays.
 * @return Another negative error code returned by SceShell or LSDB.
 */
int sceLiveAreaReplaceAllForTitleSync(const char *contents_path, const char *title_id, const SceRtcTick *last_modified);

/**
 * Replace all LiveArea data for a title asynchronously.
 *
 * Poll ::sceLiveAreaGetStatus to obtain the final result.
 *
 * @param[in] contents_path - Directory containing the replacement LiveArea data.
 * The path must contain at most 255 characters.
 * @param[in] title_id - Target title ID. If NULL or empty, SceShell normally
 * uses the calling process's title. After ::sceLiveAreaEnableBgAppMode is called,
 * a NULL or empty value instead selects the title in the caller's `_fg_title_id`
 * LSDB property.
 * @param[in] last_modified - Modification time to store with the LiveArea data,
 * or NULL to store a zero tick. Exactly eight bytes are copied into the request
 * during the call.
 *
 * @note The source-path and title-resolution behavior documented for
 * ::sceLiveAreaReplaceAllForTitleSync also applies to this function.
 *
 * You may reuse or free all input buffers after this function returns, even if
 * the operation is still running.
 *
 * @retval 0 The operation was submitted.
 * @retval 0x80104001 Another asynchronous operation is still pending.
 * @retval 0x80104002 \a contents_path is NULL or longer than 255 characters.
 * @return Another negative submission error.
 */
int sceLiveAreaReplaceAllForTitleAsync(const char *contents_path, const char *title_id, const SceRtcTick *last_modified);

/**
 * Update one LiveArea frame for the calling title synchronously.
 *
 * The frame ID and frame contents are read from the XML document.
 * After ::sceLiveAreaEnableBgAppMode is called, the target title is read
 * from the caller's `_fg_title_id` LSDB property.
 *
 * @param[in] format_version - LiveArea XML format version. Must be `"01.00"`.
 * @param[in] frame_xml - Frame XML document.
 * @param[in] frame_xml_length - XML size in bytes. A negative value uses the
 * NUL-terminated string length. The resulting size must not exceed 10239 bytes.
 * @param[in] contents_path - Directory containing assets referenced by the XML.
 * The path must contain at most 255 characters.
 * @param[in] target_type - One of ::SceLiveAreaTargetType.
 *
 * @note The implicit-title source-path policy documented for
 * ::sceLiveAreaReplaceAllSync also applies to frame updates.
 *
 * @retval 0 The frame was updated.
 * @retval 0x80104002 An argument, path length, format version, or target type
 * is invalid.
 * @retval 0x80104004 SceShell could not parse the frame XML.
 * @retval 0x80104009 The XML is longer than 10239 bytes.
 * @retval 0x8010400B The source path is not permitted by the implicit-title
 * path policy.
 * @return Another negative error code returned by SceShell or LSDB.
 */
int sceLiveAreaUpdateFrameSync(const char *format_version, const char *frame_xml, SceInt32 frame_xml_length, const char *contents_path, SceLiveAreaTargetType target_type);

/**
 * Update one LiveArea frame for the calling title asynchronously.
 *
 * The frame ID and frame contents are read from the XML document. Poll
 * ::sceLiveAreaGetStatus to obtain the final result.
 * After ::sceLiveAreaEnableBgAppMode is called, the target title is read
 * from the caller's `_fg_title_id` LSDB property.
 *
 * @param[in] format_version - LiveArea XML format version. Must be `"01.00"`.
 * @param[in] frame_xml - Frame XML document.
 * @param[in] frame_xml_length - XML size in bytes. A negative value uses the
 * NUL-terminated string length. The resulting size must not exceed 10239 bytes.
 * @param[in] contents_path - Directory containing assets referenced by the XML.
 * The path must contain at most 255 characters.
 * @param[in] target_type - One of ::SceLiveAreaTargetType.
 *
 * @note The implicit-title source-path policy documented for
 * ::sceLiveAreaReplaceAllSync also applies to frame updates.
 *
 * You may reuse or free the XML, path, and other input buffers after this
 * function returns, even if the operation is still running.
 *
 * @retval 0 The operation was submitted.
 * @retval 0x80104001 Another asynchronous operation is still pending.
 * @retval 0x80104002 An argument, path length, format version, or target type
 * is invalid.
 * @retval 0x80104009 The XML is longer than 10239 bytes.
 * @return Another negative submission error.
 */
int sceLiveAreaUpdateFrameAsync(const char *format_version, const char *frame_xml, SceInt32 frame_xml_length, const char *contents_path, SceLiveAreaTargetType target_type);

/**
 * Update one LiveArea frame for a title synchronously.
 *
 * The frame ID and frame contents are read from the XML document.
 *
 * @param[in] format_version - LiveArea XML format version. Must be `"01.00"`.
 * @param[in] frame_xml - Frame XML document.
 * @param[in] frame_xml_length - XML size in bytes. A negative value uses the
 * NUL-terminated string length. The resulting size must not exceed 10239 bytes.
 * @param[in] contents_path - Directory containing assets referenced by the XML.
 * The path must contain at most 255 characters.
 * @param[in] target_type - One of ::SceLiveAreaTargetType.
 * @param[in] title_id - Target title ID. If NULL or empty, SceShell normally
 * uses the calling process's title. After ::sceLiveAreaEnableBgAppMode is called,
 * a NULL or empty value instead selects the title in the caller's `_fg_title_id`
 * LSDB property.
 *
 * @note Selecting the ForTitle export bypasses the implicit
 * `app0:`/`savedata0:` source allowlist, even when \a title_id is NULL or empty.
 *
 * @retval 0 The frame was updated.
 * @retval 0x80104002 An argument, path length, format version, or target type
 * is invalid.
 * @retval 0x80104004 SceShell could not parse the frame XML.
 * @retval 0x80104009 The XML is longer than 10239 bytes.
 * @return Another negative error code returned by SceShell or LSDB.
 */
int sceLiveAreaUpdateFrameForTitleSync(const char *format_version, const char *frame_xml, SceInt32 frame_xml_length, const char *contents_path, SceLiveAreaTargetType target_type, const char *title_id);

/**
 * Update one LiveArea frame for a title asynchronously.
 *
 * The frame ID and frame contents are read from the XML document. Poll
 * ::sceLiveAreaGetStatus to obtain the final result.
 *
 * @param[in] format_version - LiveArea XML format version. Must be `"01.00"`.
 * @param[in] frame_xml - Frame XML document.
 * @param[in] frame_xml_length - XML size in bytes. A negative value uses the
 * NUL-terminated string length. The resulting size must not exceed 10239 bytes.
 * @param[in] contents_path - Directory containing assets referenced by the XML.
 * The path must contain at most 255 characters.
 * @param[in] target_type - One of ::SceLiveAreaTargetType.
 * @param[in] title_id - Target title ID. If NULL or empty, SceShell normally
 * uses the calling process's title. After ::sceLiveAreaEnableBgAppMode is called,
 * a NULL or empty value instead selects the title in the caller's `_fg_title_id`
 * LSDB property.
 *
 * @note Selecting the ForTitle export bypasses the implicit
 * `app0:`/`savedata0:` source allowlist, even when \a title_id is NULL or empty.
 *
 * You may reuse or free all input buffers after this function returns, even if
 * the operation is still running.
 *
 * @retval 0 The operation was submitted.
 * @retval 0x80104001 Another asynchronous operation is still pending.
 * @retval 0x80104002 An argument, path length, format version, or target type
 * is invalid.
 * @retval 0x80104009 The XML is longer than 10239 bytes.
 * @return Another negative submission error.
 */
int sceLiveAreaUpdateFrameForTitleAsync(const char *format_version, const char *frame_xml, SceInt32 frame_xml_length, const char *contents_path, SceLiveAreaTargetType target_type, const char *title_id);

/**
 * Update multiple LiveArea frames for a title synchronously.
 *
 * @param[in] format_version - LiveArea XML format version. Must be `"01.00"`.
 * @param[in] frame_xml_array - Array of NUL-terminated frame XML documents.
 * Every entry must be non-NULL; FW 3.60 reads each string until its NUL
 * terminator, without a length limit.
 * @param[in] frame_count - Number of entries in \a frame_xml_array. Must be nonzero.
 * @param[in] contents_path - Directory containing assets referenced by the XML.
 * The path must contain at most 255 characters.
 * @param[in] target_type - One of ::SceLiveAreaTargetType.
 * @param[in] title_id - Target title ID. NULL or an empty string selects the
 * title associated with the calling process. Background-application mode is
 * not transmitted for this operation on FW 3.60.
 *
 * @note This function always uses the ForTitle source-path policy, including
 * when \a title_id is NULL or empty.
 *
 * The complete IPMI request, including the descriptor-size table and each
 * payload rounded up to 16 bytes, must fit in 0x3F00 bytes on FW 3.60.
 *
 * @retval 0 The frames were updated.
 * @retval 0x80104002 An argument, path length, format version, frame count, or
 * target type is invalid.
 * @retval 0x80104004 SceShell could not parse one of the frame documents.
 * @retval 0x80020588 The serialized IPMI request is larger than 0x3F00 bytes.
 * @return Another negative error code returned by SceShell or LSDB.
 */
int sceLiveAreaUpdateFramesForTitleSync(const char *format_version, const char *const *frame_xml_array, SceUInt32 frame_count, const char *contents_path, SceLiveAreaTargetType target_type, const char *title_id);

/**
 * Update multiple LiveArea frames for a title asynchronously.
 *
 * Poll ::sceLiveAreaGetStatus to obtain the final result.
 *
 * @param[in] format_version - LiveArea XML format version. Must be `"01.00"`.
 * @param[in] frame_xml_array - Array of NUL-terminated frame XML documents.
 * Every entry must be non-NULL; FW 3.60 reads each string until its NUL
 * terminator, without a length limit.
 * @param[in] frame_count - Number of entries in \a frame_xml_array. Must be nonzero.
 * @param[in] contents_path - Directory containing assets referenced by the XML.
 * The path must contain at most 255 characters.
 * @param[in] target_type - One of ::SceLiveAreaTargetType.
 * @param[in] title_id - Target title ID. NULL or an empty string selects the
 * title associated with the calling process. Background-application mode is
 * not transmitted for this operation on FW 3.60.
 *
 * @note This function always uses the ForTitle source-path policy, including
 * when \a title_id is NULL or empty. The 0x3F00-byte serialized-request limit
 * documented for ::sceLiveAreaUpdateFramesForTitleSync also applies.
 *
 * You may reuse or free the pointer array and every XML string after this
 * function returns, even if the operation is still running.
 *
 * @retval 0 The operation was submitted.
 * @retval 0x80104001 Another asynchronous operation is still pending.
 * @retval 0x80104002 An argument, path length, format version, frame count, or
 * target type is invalid.
 * @retval 0x80020588 The serialized IPMI request is larger than 0x3F00 bytes.
 * @return Another negative submission error.
 */
int sceLiveAreaUpdateFramesForTitleAsync(const char *format_version, const char *const *frame_xml_array, SceUInt32 frame_count, const char *contents_path, SceLiveAreaTargetType target_type, const char *title_id);

/**
 * Get the overall LiveArea content revision for the calling title.
 *
 * FW 3.60 queries the LiveArea object currently loaded by SceShell rather than
 * reading the database directly. Background-application mode does not change
 * the target; SceShell always uses the calling application's title. If the
 * object is temporarily unavailable, the query is retried every 16 milliseconds
 * for up to approximately 10 seconds.
 *
 * @param[out] revision - Receives the revision.
 *
 * @retval 0 The revision was returned.
 * @retval 0x80104002 \a revision is NULL.
 * @retval 0x8010400A The target's loaded LiveArea object is unavailable.
 * @return Another negative error code returned by SceShell.
 */
int sceLiveAreaGetRevision(SceUInt64 *revision);

/**
 * Get a LiveArea frame revision for the calling title.
 *
 * If normal and retail variants exist, the retail frame revision is returned.
 * FW 3.60 queries the LiveArea object currently loaded by SceShell rather than
 * reading the database directly. Background-application mode does not change
 * the target; SceShell always uses the calling application's title. If the
 * object is temporarily unavailable, the query is retried every 16 milliseconds
 * for up to approximately 10 seconds.
 *
 * @param[in] frame_id - Non-empty frame ID.
 * @param[out] revision - Receives the revision.
 *
 * @retval 0 The revision was returned.
 * @retval 0x80104002 \a frame_id is NULL or empty, or \a revision is NULL.
 * @retval 0x8010400A The target's loaded LiveArea object or frame is
 * unavailable.
 * @return Another negative error code returned by SceShell.
 */
int sceLiveAreaGetFrameRevision(const char *frame_id, SceUInt64 *revision);

/**
 * Get the user data associated with a LiveArea frame for the calling title.
 *
 * This function queries LSDB directly; it does not require the title's
 * LiveArea object to be loaded. If normal and retail variants exist, the
 * retail frame user data is returned.
 * The result is NUL-terminated. At most
 * `min(buffer_size, 1024) - 1` data bytes are returned; FW 3.60 caps a larger
 * requested transfer to 1024 bytes including the terminator.
 * After ::sceLiveAreaEnableBgAppMode is called, the target title is read
 * from the caller's `_fg_title_id` LSDB property.
 *
 * @param[in] frame_id - Frame ID. A NULL pointer is invalid; an empty string
 * does not match a frame.
 * @param[out] buffer - Destination buffer.
 * @param[in] buffer_size - Destination buffer size. Must be nonzero.
 *
 * @retval 0 The user-data string was returned.
 * @retval 0x80104002 \a frame_id or \a buffer is NULL, or \a buffer_size is zero.
 * @retval 0x8010400A No matching frame exists.
 * @return Another negative error code returned by SceShell or LSDB.
 */
int sceLiveAreaGetFrameUserData(const char *frame_id, char *buffer, SceSize buffer_size);

/**
 * Enable foreground-title selection for a background companion application.
 *
 * By default, an operation without an explicit title ID targets the title
 * associated with the calling process. After this function is called, FW 3.60
 * treats the caller as a background companion and reads the foreground target
 * title from the caller's `_fg_title_id` LSDB property. If that lookup does not
 * produce a title ID, an affected operation can fail with `0x801040FF`.
 *
 * This sets a flag shared by all threads in the process to 1. There is no
 * corresponding function to disable it. On FW 3.60 it changes the target for
 * replace-all, single-frame, and frame user-data operations. Revision requests
 * transmit the flag byte but SceShell ignores it, and multi-frame updates do
 * not transmit it.
 *
 * @warning This does not put the calling application into the background,
 * register an `_fg_title_id` relationship, grant additional privileges, or
 * bypass the replace-all source-path policy. A normal foreground application
 * should generally use an explicit-title function instead.
 *
 * @note Exported by the `SceLiveAreaUtilBgApp` library.
 *
 * @return 0 on FW 3.60.
 */
int sceLiveAreaEnableBgAppMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_LIVEAREA_H_ */
