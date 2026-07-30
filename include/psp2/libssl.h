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

typedef enum SceSslCertIssuer {
	SCE_SSLCERT_ISSUER_ALL         = 0, //!< Select every issuer group.
	SCE_SSLCERT_ISSUER_SCE         = 1,
	SCE_SSLCERT_ISSUER_VERISIGN    = 2,
	SCE_SSLCERT_ISSUER_GEOTRUST    = 3,
	SCE_SSLCERT_ISSUER_THAWTE      = 4,
	SCE_SSLCERT_ISSUER_COMODO      = 5,
	SCE_SSLCERT_ISSUER_GLOBALSIGN  = 6,
	SCE_SSLCERT_ISSUER_CYBERTRUST  = 7,
	SCE_SSLCERT_ISSUER_ENTRUST     = 8,
	SCE_SSLCERT_ISSUER_DIGICERT    = 9,
	SCE_SSLCERT_ISSUER_GODADDY     = 10,
	SCE_SSLCERT_ISSUER_RSA         = 11,
	SCE_SSLCERT_ISSUER_STARTCOM    = 12,
	SCE_SSLCERT_ISSUER_SECOM       = 13,
	SCE_SSLCERT_ISSUER_TRUSTWAVE   = 14,
	SCE_SSLCERT_ISSUER_AFFIRMTRUST = 15
} SceSslCertIssuer;

typedef void SceSslCert;
typedef void SceSslCertName;

typedef struct SceSslCertificateAuthorityEntry {
	char *pemCertificate; //!< NUL-terminated PEM certificate stored in the caller's buffer.
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
 * Retrieve built-in certificate-authority certificates.
 *
 * The certificates are loaded from `vs0:/data/external/cert/CA_LIST.cer` and
 * checked against built-in SHA-1 digests.
 *
 * If either \p certificateList is 0 or \p buffer is NULL, the function only
 * computes the required storage size and ignores \p bufferSize. Output mode is
 * used only when both are supplied.
 *
 * @param[in] issuerId - One of ::SceSslCertIssuer.
 * @param[in] certificateMask - Issuer-specific certificate-selection bitmask.
 *                              For a nonzero \p issuerId, -1 selects that
 *                              issuer's firmware default mask. With
 *                              ::SCE_SSLCERT_ISSUER_ALL, -1 selects every
 *                              known certificate.
 * @param[out] certificateList - Address of a ::SceSslCertificateAuthorityEntry
 *                               pointer, represented as an int.
 * @param[out] buffer - Buffer receiving PEM certificates and list entries.
 * @param[in] bufferSize - Size of \a buffer in bytes. Value of type ::SceSize.
 * @param[out] resultSize - Optional total storage required or used on success.
 *
 * @return Number of selected certificates, or a negative error code.
 */
int sceSslInternalGetCertificateAuthority(int issuerId, int certificateMask, int certificateList, char *buffer, int bufferSize, size_t *resultSize);

#ifdef __cplusplus
}
#endif

#endif
