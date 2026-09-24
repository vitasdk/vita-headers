/**
 * \kernelgroup{SceSblAuthMgr}
 * \usage{psp2kern/kernel/authmgr.h,SceSblAuthMgrForKernel_stub SceSblAuthMgrForDriver_stub}
 */


#ifndef _PSP2KERN_SBLAUTHMGR_H_
#define _PSP2KERN_SBLAUTHMGR_H_

#include <psp2kern/types.h>
#include <psp2common/sblpostssmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Clear a DMAC5 key slot.
 *
 * AuthMgr does not validate \a slot_id before forwarding it to secure command
 * 6. SceSblSsMgr manages slots 12 through 23, but no FW 3.60 module that
 * imports this function calls it directly.
 *
 * @param[in] slot_id DMAC5 key slot identifier.
 * @param[in] zero Must be 0; forwarded in the secure command.
 *
 * @return 0 on success, 0x800F0516 when \a zero is not 0, or a negative
 *         synchronization or secure-module error.
 */
int ksceSblAuthMgrClearDmac5Key(int slot_id, int zero);

/**
 * Set a DMAC5 key slot.
 *
 * FW 3.60 does not validate \a slot_id before forwarding it to secure command
 * 5. SceSblSsMgr allocates slots 12 through 23.
 *
 * @param[in] key Non-NULL pointer to the key data.
 * @param[in] keylen Key size, either 0x10 or 0x20 bytes.
 * @param[in] slot_id DMAC5 key slot identifier.
 * @param[in] key_id Key identifier: 0, 0x10000, 0x10001, 0x20000, or
 *                   0x20001.
 *
 * @return 0 on success, 0x800F0516 for an invalid pointer, key size, or key
 *         identifier, or a negative synchronization or secure-module error.
 */
int ksceSblAuthMgrSetDmac5Key(const void *key, SceSize keylen, int slot_id, int key_id);

/**
 * Authenticate a SELF header.
 *
 * Call this function after ::ksceSblAuthMgrOpen. The complete
 * ::SceAuthInfo context is sent to secure command 1. On success, only
 * ::SceAuthInfo::response is copied back from the secure-module response.
 *
 * When the system license state is uninitialized, expired, or reports a
 * backup-battery failure, FW 3.60 sets the four-bit field at bits 8 through 11
 * of ::SceAuthInfo::self_type to 1 before authentication. For media types 13
 * and 14, the verified SPSFO system version is written to
 * ::SceSelfAuthInfo::program_sceversion in the response SELF authorization
 * information; other media types receive zero in that field.
 *
 * When the upper 12 bits of the authenticated program-authority ID equal
 * 0x2F0, a registered Utoken override can replace the response program-authority
 * ID, capability, attribute, and first 0x10 bytes of the shared secret. The
 * no-override error 0x800F1A02 is ignored; other negative Utoken errors are
 * returned.
 *
 * @param[in] handle Authentication session handle. Must be 1.
 * @param[in] self_header_addr Non-NULL address of the mapped SELF header.
 * @param[in] self_header_size Size of the mapped SELF header in bytes.
 * @param[in,out] auth_info Non-NULL pointer to the SELF authentication context.
 *
 * @return 0 on success, 0x800F0509 for an invalid handle, 0x800F0516 for an
 *         invalid pointer, or a negative address-translation, Utoken, or
 *         secure-module error.
 */
int ksceSblAuthMgrAuthHeader(int handle, const void *self_header_addr, SceSize self_header_size, SceAuthInfo *auth_info);

/**
 * Close a SELF authentication session.
 *
 * This releases the single session acquired by ::ksceSblAuthMgrOpen and the
 * suspend lock held while the session is open. FW 3.60 clears the internal
 * session only when stopping the secure module succeeds, but it does not
 * return a secure module stop error to the caller.
 *
 * @param[in] handle Authentication session handle. Must be 1.
 *
 * @return 0 on success, 0x800F0509 for an invalid handle, or a negative mutex
 *         or semaphore error.
 */
int ksceSblAuthMgrClose(int handle);

/**
 * Check whether a software version is supported.
 *
 * SceKernelModulemgr applies this check to the authenticated software version
 * of a game process image after loading it.
 *
 * @param[in] version Software-version bit pattern. The value -1 is always
 *                    accepted. Otherwise, the low 12 bits are cleared and the
 *                    unsigned result must not exceed 0x03600000 on FW 3.60.
 *
 * @return 0 when accepted, otherwise 0x800F0537.
 */
int ksceSblAuthMgrCompareSwVersion(int version);

/**
 * Decrypt NPDRM bind data in place using a read-only request.
 *
 * Both buffers must be physically contiguous and 0x40-byte aligned. NpDrm
 * calls this with a 0x10-byte output and a 0x90-byte request assembled from a
 * 0x20-byte bind seed followed by a 0x70-byte RIF header.
 *
 * @param[in,out] klicensee Non-NULL output buffer.
 * @param[in] klicensee_len Output size, from 0 through 0x1000 bytes and a
 *                          multiple of 0x10.
 * @param[in] request Non-NULL read-only request buffer.
 * @param[in] request_len Request size, from 0x10 through 0x1000 bytes and a
 *                        multiple of 0x10.
 * @param[in] zero Must be 0.
 *
 * @return 0 on success, 0x800F0516 for invalid pointers, alignment, sizes, or
 *         \a zero, or a negative address-translation, synchronization, or
 *         secure-module error.
 */
int ksceSblAuthMgrDecBindData(void *klicensee, SceSize klicensee_len, const void *request, SceSize request_len, int zero);

/**
 * Process NPDRM EKc key material in place.
 *
 * The secure module may return a different number of bytes than supplied.
 * AuthMgr rejects counts above 0x100; otherwise, it copies the reported number
 * of bytes back to \a data. NpDrm uses key identifier 0 to process its 0xC0-byte
 * encrypted key-material table.
 *
 * @param[in,out] data Non-NULL input/output buffer.
 * @param[in] size Input size, from 0x10 through 0x100 bytes and a multiple of
 *                 0x10.
 * @param[in] key_id Key identifier, from 0 through 2.
 *
 * @return 0 on success, 0x800F0516 for an invalid pointer, size, key
 *         identifier, or secure-module output size, or a negative
 *         synchronization or secure-module error.
 */
int ksceSblAuthMgrGetEKc(void *data, SceSize size, int key_id);

/**
 * Authenticate and decrypt a SELF segment block in place.
 *
 * The input and output use the same list of physical address ranges. Cache
 * maintenance is rounded up to 0x40 bytes. SceKernelModulemgr submits stream
 * chunks of up to 0x10000 bytes.
 *
 * @param[in] handle Authentication session handle. Must be 1.
 * @param[in,out] buffer Non-NULL, 0x20-byte-aligned block buffer.
 * @param[in] buffer_size Nonzero block size in bytes.
 *
 * @return 0 on success, 0x800F0509 for an invalid handle, 0x800F0516 for an
 *         invalid buffer, size, or alignment, or a negative
 *         address-translation or secure-module error.
 */
int ksceSblAuthMgrLoadBlock(int handle, void *buffer, SceSize buffer_size);

/**
 * Open a SELF authentication session.
 *
 * FW 3.60 supports one session for the whole system. A successful call starts
 * the Auth secure module, writes handle 1 to \a handle, and holds a suspend
 * lock until the matching ::ksceSblAuthMgrClose call.
 *
 * @param[out] handle Non-NULL pointer that receives handle 1.
 *
 * @return 0 on success, 0x800F0501 when a session is already open,
 *         0x800F0516 for an invalid pointer or internal session state, or a
 *         negative synchronization or secure-module scheduler error.
 */
int ksceSblAuthMgrOpen(int *handle);

/**
 * Select and initialize a SELF segment for authentication.
 *
 * The segment index is forwarded unchanged to secure command 2.
 * SceKernelModulemgr treats return value 1 as an uncompressed segment and
 * every other nonnegative value as a deflate-compressed segment.
 *
 * @param[in] handle Authentication session handle. Must be 1.
 * @param[in] segment_index SELF segment index.
 *
 * @return The secure-module segment mode, 0x800F0509 for an invalid handle,
 *         or another negative secure-module error.
 */
int ksceSblAuthMgrSetupAuthSegment(int handle, int segment_index);

/**
 * Verify a signed SPSFO context.
 *
 * The mapped file is passed to secure command 8. After successful secure
 * verification, FW 3.60 checks the embedded signed-header offset and saves
 * a copy of the 0x200-byte header in AuthMgr for later SELF authentication.
 *
 * @param[in,out] ctx Non-NULL pointer to the SPSFO mapping. Its memory-block
 *                    base must be non-NULL and 0x20-byte aligned, and its exact
 *                    file size must not exceed 0x8000 bytes.
 *
 * @return 0 on success, 0x800F0516 for an invalid context, base, or size,
 *         0x800F0524 for an invalid signed-header range after verification,
 *         or a negative address-translation, synchronization, or
 *         secure-module error.
 */
int ksceSblAuthMgrVerifySpfsoCtx(SceSblSpsfoContext *ctx);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_SBLAUTHMGR_H_ */
