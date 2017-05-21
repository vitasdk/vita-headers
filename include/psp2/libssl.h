/**
 * \usergroup{SceLibSsl}
 * \usage{psp2/libssl.h,SceSsl_stub}
 */


#ifndef _PSP2_SSL_LIBSSL_H
#define _PSP2_SSL_LIBSSL_H

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

typedef void SceSslCert;
typedef void SceSslCertName;

typedef struct SceSslMemoryPoolStats{
	unsigned poolSize;
	unsigned maxInuseSize;
	unsigned currentInuseSize;
	int  reserved;
} SceSslMemoryPoolStats;

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

#ifdef __cplusplus
}
#endif
#endif

