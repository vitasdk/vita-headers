/**
 * \kernelgroup{SceSblAuthMgr}
 * \usage{psp2kern/kernel/authmgr.h,SceSblAuthMgrForKernel_stub SceSblAuthMgrForDriver_stub}
 */


#ifndef _PSP2KERN_SBLAUTHMGR_H_
#define _PSP2KERN_SBLAUTHMGR_H_

#include <psp2kern/types.h>
#include <psp2common/sblpostssmgr.h>
#include <psp2kern/kernel/sm_comm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Clear a DMAC5 key slot.
 *
 * @param[in] slot_id - DMAC5 key slot identifier.
 * @param[in] zero    - Must be 0.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrClearDmac5Key(int slot_id, int zero);

/**
 * Set a DMAC5 key slot.
 *
 * @param[in] key     - Key data.
 * @param[in] keylen  - Key size, either 0x10 or 0x20 bytes.
 * @param[in] slot_id - DMAC5 key slot identifier.
 * @param[in] key_id  - Key identifier: 0, 0x10000, 0x10001, 0x20000, or 0x20001.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrSetDmac5Key(const void *key, SceSize keylen, int slot_id, int key_id);

/**
 * Authenticate a SELF header.
 *
 * @param[in]     handle           - Authentication session handle. Must be 1.
 * @param[in]     self_header_addr - SELF header address.
 * @param[in]     self_header_size - SELF header size.
 * @param[in,out] auth_info        - Authentication context.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrAuthHeader(int handle, const void *self_header_addr, SceSize self_header_size, SceSblSmCommContext130 *auth_info);

/**
 * Close a SELF authentication session.
 *
 * @param[in] handle - Authentication session handle. Must be 1.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrClose(int handle);

/**
 * Check whether a software version is supported.
 *
 * @param[in] version - Software version bit pattern. The value -1 is always
 *                      accepted. Otherwise, the low 12 bits are cleared and
 *                      the result must not exceed 0x03600000 on FW 3.60.
 *
 * @return 0 if the version is supported, < 0 otherwise.
 */
int ksceSblAuthMgrCompareSwVersion(int version);

/**
 * Decrypt NPDRM bind data in place using the request data.
 *
 * @param[in,out] klicensee     - 0x40-aligned buffer, up to 0x1000 bytes.
 * @param[in]     klicensee_len - Klicensee buffer size, which must be a multiple of 0x10.
 * @param[in]     request       - 0x40-aligned request buffer.
 * @param[in]     request_len   - Request buffer size, from 0x10 to 0x1000 bytes and a multiple of 0x10.
 * @param[in]     zero          - Must be 0.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrDecBindData(char *klicensee, int klicensee_len, char *request, int request_len, int zero);

/**
 * Process NPDRM EKc key material in place.
 *
 * @param[in,out] data   - Input/output buffer.
 * @param[in]     size   - Buffer size, from 0x10 to 0x100 bytes and a multiple of 0x10.
 * @param[in]     key_id - Key identifier, from 0 to 2.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrGetEKc(void *data, SceSize size, int key_id);

/**
 * Authenticate and decrypt a SELF segment block in place.
 *
 * @param[in]     handle      - Authentication session handle. Must be 1.
 * @param[in,out] buffer      - 0x20-aligned block buffer.
 * @param[in]     buffer_size - Block buffer size.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrLoadBlock(int handle, void *buffer, SceSize buffer_size);

/**
 * Open a SELF authentication session.
 *
 * @param[out] pHandle - Receives the authentication session handle, which is 1.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrOpen(int *pHandle);

/**
 * Select and initialize a SELF segment for authentication.
 *
 * @param[in] handle        - Authentication session handle. Must be 1.
 * @param[in] segment_index - SELF segment index.
 *
 * @return The secure module's segment mode on success, < 0 on error. The FW
 *         3.60 Module Manager treats mode 1 as an uncompressed segment.
 */
int ksceSblAuthMgrSetupAuthSegment(int handle, int segment_index);

/**
 * Verify a signed PARAM.SFO context.
 *
 * @param[in,out] ctx - SPSFO context. Its memory block base must be 0x20-aligned
 *                      and its exact file size must not exceed 0x8000 bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int ksceSblAuthMgrVerifySpfsoCtx(SceSblSpfsoContext *ctx);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_SBLAUTHMGR_H_ */
