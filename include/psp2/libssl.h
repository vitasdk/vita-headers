/**
 * \usergroup{SceLibSsl}
 * \usage{psp2/libssl.h,SceSsl_stub}
 */


#ifndef _PSP2_SSL_LIBSSL_H
#define _PSP2_SSL_LIBSSL_H

#include <vitasdk/build_utils.h>
#include <psp2/rtc.h>

typedef enum SceSslErrorCode {
	SCE_SSL_ERROR_BEFORE_INIT    = 0x80435001,
	SCE_SSL_ERROR_ALREADY_INITED = 0x80435020,
	SCE_SSL_ERROR_OUT_OF_MEMORY  = 0x80435022,
	SCE_SSL_ERROR_NOT_FOUND      = 0x80435025,
	SCE_SSL_ERROR_INTERNAL       = 0x80435026,
	SCE_SSL_ERROR_INVALID_FORMAT = 0x80435108,
	SCE_SSL_ERROR_INVALID_VALUE  = 0x804351FE
} SceSslErrorCode;

/** Built-in certificate-authority issuer groups. */
typedef enum SceSslCertIssuer {
	SCE_SSLCERT_ISSUER_ALL         = 0, //!< Select every issuer group.
	SCE_SSLCERT_ISSUER_SCE         = 1,  //!< FW 3.60 supports certificate mask 0x1F.
	SCE_SSLCERT_ISSUER_VERISIGN    = 2,  //!< FW 3.60 supports certificate mask 0x1F.
	SCE_SSLCERT_ISSUER_GEOTRUST    = 3,  //!< FW 3.60 supports certificate mask 0x0F.
	SCE_SSLCERT_ISSUER_THAWTE      = 4,  //!< FW 3.60 supports certificate mask 0x07.
	SCE_SSLCERT_ISSUER_COMODO      = 5,  //!< FW 3.60 supports certificate mask 0x07.
	SCE_SSLCERT_ISSUER_GLOBALSIGN  = 6,  //!< FW 3.60 supports certificate mask 0x03.
	SCE_SSLCERT_ISSUER_CYBERTRUST  = 7,  //!< FW 3.60 supports certificate mask 0x07.
	SCE_SSLCERT_ISSUER_ENTRUST     = 8,  //!< FW 3.60 supports certificate mask 0x0F.
	SCE_SSLCERT_ISSUER_DIGICERT    = 9,  //!< FW 3.60 supports certificate mask 0x07.
	SCE_SSLCERT_ISSUER_GODADDY     = 10, //!< FW 3.60 supports certificate mask 0x7F.
	SCE_SSLCERT_ISSUER_RSA         = 11, //!< FW 3.60 supports certificate mask 0x03.
	SCE_SSLCERT_ISSUER_STARTCOM    = 12, //!< FW 3.60 supports certificate mask 0x03.
	SCE_SSLCERT_ISSUER_SECOM       = 13, //!< FW 3.60 supports certificate mask 0x07.
	SCE_SSLCERT_ISSUER_TRUSTWAVE   = 14, //!< FW 3.60 supports certificate mask 0x01.
	SCE_SSLCERT_ISSUER_AFFIRMTRUST = 15  //!< FW 3.60 supports certificate mask 0x07.
} SceSslCertIssuer;

typedef void SceSslCert;
typedef void SceSslCertName;

/**
 * Certificate list node stored inside the caller's output buffer.
 *
 * The caller owns both this node and the string referenced by
 * ::SceSslCertificateAuthorityEntry::pem_certificate. They remain valid for as
 * long as the output buffer remains valid. No separate list cleanup is needed.
 */
typedef struct SceSslCertificateAuthorityEntry {
	char *pem_certificate; //!< NUL-terminated PEM certificate stored in the caller's buffer.
	struct SceSslCertificateAuthorityEntry *next; //!< Next selected certificate, or NULL.
} SceSslCertificateAuthorityEntry;
VITASDK_BUILD_ASSERT_EQ(0x8, SceSslCertificateAuthorityEntry); // size is from FW 3.60

typedef struct SceSslMemoryPoolStats{
	unsigned poolSize;
	unsigned maxInuseSize;
	unsigned currentInuseSize;
	int  reserved;
} SceSslMemoryPoolStats;
VITASDK_BUILD_ASSERT_EQ(0x10, SceSslMemoryPoolStats);

#ifdef __cplusplus
extern "C" {
#endif

#define sceSslEnd()	sceSslTerm()

int sceSslInit(unsigned poolSize);
int sceSslTerm(void);
int sceSslGetMemoryPoolStats(SceSslMemoryPoolStats* currentStat);
int sceSslGetSerialNumber(SceSslCert *sslCert, const char **sboData, unsigned *sboLen);
int sceSslGetNotBefore(SceSslCert *sslCert, SceRtcTick *begin);
int sceSslGetNotAfter(SceSslCert *sslCert, SceRtcTick *limit);
int sceSslGetNameEntryCount(SceSslCertName *certName);
int sceSslGetNameEntryInfo(SceSslCertName *certName, int entryNum, char *oidname, unsigned maxOidnameLen, char *value, unsigned maxValueLen, unsigned *valueLen);
SceSslCertName *sceSslGetSubjectName(SceSslCert *sslCert);
SceSslCertName *sceSslGetIssuerName (SceSslCert *sslCert);
int sceSslFreeSslCertName(SceSslCertName* certName);

/**
 * Get built-in certificate-authority certificates.
 *
 * The certificates are loaded from `vs0:/data/external/cert/CA_LIST.cer`. In
 * output mode, every loaded certificate is checked against a built-in SHA-1
 * digest before it is returned.
 *
 * If either \p certificate_list or \p buffer is NULL, the function only
 * calculates the required storage size and ignores \p buffer_size. Output mode
 * requires both pointers to be non-NULL. The required size includes every
 * NUL-terminated PEM string, alignment padding, and one embedded
 * ::SceSslCertificateAuthorityEntry per certificate.
 *
 * In output mode, \p certificate_list receives a linked list whose nodes and
 * PEM strings point into \p buffer. The function does not allocate output
 * memory. Callers should first query the size, allocate one buffer of that
 * size, and then call the function again to fill it. If output mode fails
 * after processing begins, the buffer and list may contain partial data and
 * should be discarded.
 *
 * @param[in] issuer_id - One of ::SceSslCertIssuer.
 * @param[in] certificate_mask - Issuer-specific certificate-selection bitmask.
 *                              For a nonzero \p issuer_id, -1 selects that
 *                              issuer's firmware default mask. On FW 3.60 the
 *                              default is the full supported mask only for SCE,
 *                              GeoTrust, Thawte, and GoDaddy; it is zero for
 *                              the other issuer groups. With
 *                              ::SCE_SSLCERT_ISSUER_ALL, -1 selects every
 *                              known certificate.
 * @param[out] certificate_list - Receives the first list node in output mode.
 * @param[out] buffer - Caller-owned buffer receiving PEM strings and list nodes.
 * @param[in] buffer_size - Size of \a buffer in bytes.
 * @param[out] result_size - Optional pointer receiving the total storage required
 *                          or used on success. If non-NULL, the function sets
 *                          the output to zero before validation and leaves it
 *                          zero on error.
 *
 * @return Number of selected certificates on success, including zero when the
 *         mask selects none. Returns `0x80010086` for an invalid issuer or
 *         unsupported mask, `0x8001000C` when the output buffer is too small,
 *         ::SCE_SSL_ERROR_INVALID_VALUE when a certificate digest differs,
 *         or another negative file/path error.
 */
int sceSslInternalGetCertificateAuthority(SceSslCertIssuer issuer_id, int certificate_mask,
	SceSslCertificateAuthorityEntry **certificate_list, char *buffer, SceSize buffer_size,
	SceSize *result_size);

#ifdef __cplusplus
}
#endif

#endif
