/**
 * \usergroup{SceHttp}
 * \usage{psp2/net/http.h,SceHttp_stub,SCE_SYSMODULE_HTTP}
 */


#ifndef _PSP2_NET_HTTP_H_
#define _PSP2_NET_HTTP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
#define SCE_HTTP_DEFAULT_RESOLVER_TIMEOUT       (1 * 1000 * 1000U)
#define SCE_HTTP_DEFAULT_RESOLVER_RETRY         (5U)
#define SCE_HTTP_DEFAULT_CONNECT_TIMEOUT        (30* 1000 * 1000U)
#define SCE_HTTP_DEFAULT_SEND_TIMEOUT           (120* 1000 * 1000U)
#define SCE_HTTP_DEFAULT_RECV_TIMEOUT           (120* 1000 * 1000U)
#define SCE_HTTP_DEFAULT_RECV_BLOCK_SIZE        (1500U)
#define SCE_HTTP_DEFAULT_RESPONSE_HEADER_MAX    (5000U)
#define SCE_HTTP_DEFAULT_REDIRECT_MAX           (6U)
#define SCE_HTTP_DEFAULT_TRY_AUTH_MAX           (6U)

#define SCE_HTTP_INVALID_ID     0

typedef enum SceHttpErrorCode {
	SCE_HTTP_ERROR_BEFORE_INIT                  = 0x80431001,
	SCE_HTTP_ERROR_ALREADY_INITED               = 0x80431020,
	SCE_HTTP_ERROR_BUSY                         = 0x80431021,
	SCE_HTTP_ERROR_OUT_OF_MEMORY                = 0x80431022,
	SCE_HTTP_ERROR_NOT_FOUND                    = 0x80431025,
	SCE_HTTP_ERROR_INVALID_VERSION              = 0x8043106A,
	SCE_HTTP_ERROR_INVALID_ID                   = 0x80431100,
	SCE_HTTP_ERROR_OUT_OF_SIZE                  = 0x80431104,
	SCE_HTTP_ERROR_INVALID_VALUE                = 0x804311FE,

	SCE_HTTP_ERROR_INVALID_URL                  = 0x80433060,
	SCE_HTTP_ERROR_UNKNOWN_SCHEME               = 0x80431061,
	SCE_HTTP_ERROR_NETWORK                      = 0x80431063,
	SCE_HTTP_ERROR_BAD_RESPONSE                 = 0x80431064,
	SCE_HTTP_ERROR_BEFORE_SEND                  = 0x80431065,
	SCE_HTTP_ERROR_AFTER_SEND                   = 0x80431066,
	SCE_HTTP_ERROR_TIMEOUT                      = 0x80431068,
	SCE_HTTP_ERROR_UNKOWN_AUTH_TYPE             = 0x80431069,
	SCE_HTTP_ERROR_UNKNOWN_METHOD               = 0x8043106B,
	SCE_HTTP_ERROR_READ_BY_HEAD_METHOD          = 0x8043106F,
	SCE_HTTP_ERROR_NOT_IN_COM                   = 0x80431070,
	SCE_HTTP_ERROR_NO_CONTENT_LENGTH            = 0x80431071,
	SCE_HTTP_ERROR_CHUNK_ENC                    = 0x80431072,
	SCE_HTTP_ERROR_TOO_LARGE_RESPONSE_HEADER    = 0x80431073,
	SCE_HTTP_ERROR_SSL                          = 0x80431075,
	SCE_HTTP_ERROR_ABORTED                      = 0x80431080,
	SCE_HTTP_ERROR_UNKNOWN                      = 0x80431081,

	SCE_HTTP_ERROR_PARSE_HTTP_NOT_FOUND         = 0x80432025,
	SCE_HTTP_ERROR_PARSE_HTTP_INVALID_RESPONSE  = 0x80432060,
	SCE_HTTP_ERROR_PARSE_HTTP_INVALID_VALUE     = 0x804321FE,

	SCE_HTTP_ERROR_RESOLVER_EPACKET             = 0x80436001,
	SCE_HTTP_ERROR_RESOLVER_ENODNS              = 0x80436002,
	SCE_HTTP_ERROR_RESOLVER_ETIMEDOUT           = 0x80436003,
	SCE_HTTP_ERROR_RESOLVER_ENOSUPPORT          = 0x80436004,
	SCE_HTTP_ERROR_RESOLVER_EFORMAT             = 0x80436005,
	SCE_HTTP_ERROR_RESOLVER_ESERVERFAILURE      = 0x80436006,
	SCE_HTTP_ERROR_RESOLVER_ENOHOST             = 0x80436007,
	SCE_HTTP_ERROR_RESOLVER_ENOTIMPLEMENTED     = 0x80436008,
	SCE_HTTP_ERROR_RESOLVER_ESERVERREFUSED      = 0x80436009,
	SCE_HTTP_ERROR_RESOLVER_ENORECORD           = 0x8043600A
} SceHttpErrorCode;

typedef enum SceHttpsErrorCode {
	SCE_HTTPS_ERROR_CERT                        = 0x80435060,
	SCE_HTTPS_ERROR_HANDSHAKE                   = 0x80435061,
	SCE_HTTPS_ERROR_IO                          = 0x80435062,
	SCE_HTTPS_ERROR_INTERNAL                    = 0x80435063,
	SCE_HTTPS_ERROR_PROXY                       = 0x80435064
} SceHttpsErrorCode;

typedef enum SceHttpsSslErrorCode {
	SCE_HTTPS_ERROR_SSL_INTERNAL                = (0x01U),
	SCE_HTTPS_ERROR_SSL_INVALID_CERT            = (0x02U),
	SCE_HTTPS_ERROR_SSL_CN_CHECK                = (0x04U),
	SCE_HTTPS_ERROR_SSL_NOT_AFTER_CHECK         = (0x08U),
	SCE_HTTPS_ERROR_SSL_NOT_BEFORE_CHECK        = (0x10U),
	SCE_HTTPS_ERROR_SSL_UNKNOWN_CA              = (0x20U)
} SceHttpsSslErrorCode;

#define SCE_HTTP_ENABLE     (1)
#define SCE_HTTP_DISABLE    (0)

#define SCE_HTTP_USERNAME_MAX_SIZE  256
#define SCE_HTTP_PASSWORD_MAX_SIZE  256

typedef enum SceHttpStatusCode {
	SCE_HTTP_STATUS_CODE_CONTINUE                       = 100,
	SCE_HTTP_STATUS_CODE_SWITCHING_PROTOCOLS            = 101,
	SCE_HTTP_STATUS_CODE_PROCESSING                     = 102,
	SCE_HTTP_STATUS_CODE_OK                             = 200,
	SCE_HTTP_STATUS_CODE_CREATED                        = 201,
	SCE_HTTP_STATUS_CODE_ACCEPTED                       = 202,
	SCE_HTTP_STATUS_CODE_NON_AUTHORITATIVE_INFORMATION  = 203,
	SCE_HTTP_STATUS_CODE_NO_CONTENT                     = 204,
	SCE_HTTP_STATUS_CODE_RESET_CONTENT                  = 205,
	SCE_HTTP_STATUS_CODE_PARTIAL_CONTENT                = 206,
	SCE_HTTP_STATUS_CODE_MULTI_STATUS                   = 207,
	SCE_HTTP_STATUS_CODE_MULTIPLE_CHOICES               = 300,
	SCE_HTTP_STATUS_CODE_MOVED_PERMANENTLY              = 301,
	SCE_HTTP_STATUS_CODE_FOUND                          = 302,
	SCE_HTTP_STATUS_CODE_SEE_OTHER                      = 303,
	SCE_HTTP_STATUS_CODE_NOT_MODIFIED                   = 304,
	SCE_HTTP_STATUS_CODE_USE_PROXY                      = 305,
	SCE_HTTP_STATUS_CODE_TEMPORARY_REDIRECT             = 307,
	SCE_HTTP_STATUS_CODE_BAD_REQUEST                    = 400,
	SCE_HTTP_STATUS_CODE_UNAUTHORIZED                   = 401,
	SCE_HTTP_STATUS_CODE_PAYMENT_REQUIRED               = 402,
	SCE_HTTP_STATUS_CODE_FORBIDDDEN                     = 403,
	SCE_HTTP_STATUS_CODE_NOT_FOUND                      = 404,
	SCE_HTTP_STATUS_CODE_METHOD_NOT_ALLOWED             = 405,
	SCE_HTTP_STATUS_CODE_NOT_ACCEPTABLE                 = 406,
	SCE_HTTP_STATUS_CODE_PROXY_AUTHENTICATION_REQUIRED  = 407,
	SCE_HTTP_STATUS_CODE_REQUEST_TIME_OUT               = 408,
	SCE_HTTP_STATUS_CODE_CONFLICT                       = 409,
	SCE_HTTP_STATUS_CODE_GONE                           = 410,
	SCE_HTTP_STATUS_CODE_LENGTH_REQUIRED                = 411,
	SCE_HTTP_STATUS_CODE_PRECONDITION_FAILED            = 412,
	SCE_HTTP_STATUS_CODE_REQUEST_ENTITY_TOO_LARGE       = 413,
	SCE_HTTP_STATUS_CODE_REQUEST_URI_TOO_LARGE          = 414,
	SCE_HTTP_STATUS_CODE_UNSUPPORTED_MEDIA_TYPE         = 415,
	SCE_HTTP_STATUS_CODE_REQUEST_RANGE_NOT_SATISFIBLE   = 416,
	SCE_HTTP_STATUS_CODE_EXPECTATION_FAILED             = 417,
	SCE_HTTP_STATUS_CODE_UNPROCESSABLE_ENTITY           = 422,
	SCE_HTTP_STATUS_CODE_LOCKED                         = 423,
	SCE_HTTP_STATUS_CODE_FAILED_DEPENDENCY              = 424,
	SCE_HTTP_STATUS_CODE_UPGRADE_REQUIRED               = 426,
	SCE_HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR          = 500,
	SCE_HTTP_STATUS_CODE_NOT_IMPLEMENTED                = 501,
	SCE_HTTP_STATUS_CODE_BAD_GATEWAY                    = 502,
	SCE_HTTP_STATUS_CODE_SERVICE_UNAVAILABLE            = 503,
	SCE_HTTP_STATUS_CODE_GATEWAY_TIME_OUT               = 504,
	SCE_HTTP_STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED     = 505,
	SCE_HTTP_STATUS_CODE_INSUFFICIENT_STORAGE           = 507
} SceHttpStatuscode;

typedef enum SceHttpUriBuildType {
	SCE_HTTP_URI_BUILD_WITH_SCHEME      = 0x01,
	SCE_HTTP_URI_BUILD_WITH_HOSTNAME    = 0x02,
	SCE_HTTP_URI_BUILD_WITH_PORT        = 0x04,
	SCE_HTTP_URI_BUILD_WITH_PATH        = 0x08,
	SCE_HTTP_URI_BUILD_WITH_USERNAME    = 0x10,
	SCE_HTTP_URI_BUILD_WITH_PASSWORD    = 0x20,
	SCE_HTTP_URI_BUILD_WITH_QUERY       = 0x40,
	SCE_HTTP_URI_BUILD_WITH_FRAGMENT    = 0x80,
	SCE_HTTP_URI_BUILD_WITH_ALL         = 0xFFFF
} SceHttpUriBuildType;

typedef enum SceHttpsFlag {
	SCE_HTTPS_FLAG_SERVER_VERIFY        = (0x01U),
	SCE_HTTPS_FLAG_CLIENT_VERIFY        = (0x02U),
	SCE_HTTPS_FLAG_CN_CHECK             = (0x04U),
	SCE_HTTPS_FLAG_NOT_AFTER_CHECK      = (0x08U),
	SCE_HTTPS_FLAG_NOT_BEFORE_CHECK     = (0x10U),
	SCE_HTTPS_FLAG_KNOWN_CA_CHECK       = (0x20U)
} SceHttpsFlag;

/* struct */

typedef struct SceHttpMemoryPoolStats {
	unsigned int poolSize;
	unsigned int maxInuseSize;
	unsigned int currentInuseSize;
	int reserved;
} SceHttpMemoryPoolStats;

typedef enum SceHttpMethods {
	SCE_HTTP_METHOD_GET,
	SCE_HTTP_METHOD_POST,
	SCE_HTTP_METHOD_HEAD,
	SCE_HTTP_METHOD_OPTIONS,
	SCE_HTTP_METHOD_PUT,
	SCE_HTTP_METHOD_DELETE,
	SCE_HTTP_METHOD_TRACE,
	SCE_HTTP_METHOD_CONNECT
} SceHttpMethods;

typedef struct SceHttpUriElement {
	int  opaque;
	char *scheme;
	char *username;
	char *password;
	char *hostname;
	char *path;
	char *query;
	char *fragment;
	unsigned short port;
	unsigned char  reserved[10];
} SceHttpUriElement;

typedef enum SceHttpVersion {
	SCE_HTTP_VERSION_1_0 = 1,
	SCE_HTTP_VERSION_1_1
} SceHttpHttpVersion;

typedef enum SceHttpProxyMode {
	SCE_HTTP_PROXY_AUTO,
	SCE_HTTP_PROXY_MANUAL
} SceHttpProxyMode;

typedef enum SceHttpAddHeaderMode {
	SCE_HTTP_HEADER_OVERWRITE,
	SCE_HTTP_HEADER_ADD
} SceHttpAddHeaderMode;

typedef enum SceHttpAuthType {
	SCE_HTTP_AUTH_BASIC,
	SCE_HTTP_AUTH_DIGEST,
	SCE_HTTP_AUTH_RESERVED0,
	SCE_HTTP_AUTH_RESERVED1,
	SCE_HTTP_AUTH_RESERVED2
} SceHttpAuthType;

typedef enum SceHttpSslVersion {
	SCE_HTTPS_SSLV23,
	SCE_HTTPS_SSLV2,
	SCE_HTTPS_SSLV3,
	SCE_HTTPS_TLSV1
} SceHttpSslVersion;

typedef struct SceHttpsData {
	char *ptr;
	unsigned int size;
} SceHttpsData;

typedef struct SceHttpsCaList {
	void **caCerts;
	int caNum;
} SceHttpsCaList;

/* callbacks */

typedef int (*SceHttpAuthInfoCallback)(
	int request,
	SceHttpAuthType authType,
	const char *realm,
	char *username,
	char *password,
	int needEntity,
	unsigned char **entityBody,
	unsigned int *entitySize,
	int *save,
	void *userArg);

typedef int (*SceHttpRedirectCallback)(
	int request,
	int statusCode,
	int *method,
	const char *location,
	void *userArg);

typedef int (*SceHttpsCallback)(
	unsigned int verifyEsrr,
	void * const sslCert[],
	int certNum,
	void *userArg);

typedef int (*SceHttpCookieRecvCallback)(
	int request,
	const char *url,
	const char *cookieHeader,
	unsigned int headerLen,
	void *userArg);

typedef int (*SceHttpCookieSendCallback)(
	int request,
	const char *url,
	const char *cookieHeader,
	void *userArg);

/* protos */

// libhttp
int sceHttpInit(unsigned int poolSize);
int sceHttpTerm(void);
int sceHttpGetMemoryPoolStats(SceHttpMemoryPoolStats *currentStat);

int sceHttpSetAuthInfoCallback(int id, SceHttpAuthInfoCallback cbfunc, void *userArg);
int sceHttpSetAuthEnabled(int id, int enable);
int sceHttpGetAuthEnabled(int id, int *enable);
int sceHttpSetRedirectCallback(int id, SceHttpRedirectCallback cbfunc, void *userArg);
int sceHttpSetAutoRedirect(int id, int enable);
int sceHttpGetAutoRedirect(int id, int *enable);
int sceHttpSetResolveTimeOut(int id, unsigned int usec);
int sceHttpSetResolveRetry(int id, int retry);
int sceHttpSetConnectTimeOut(int id, unsigned int usec);
int sceHttpSetSendTimeOut(int id, unsigned int usec);
int sceHttpSetRecvTimeOut(int id, unsigned int usec);

int sceHttpSendRequest(int reqId, const void *postData, unsigned int size);
int sceHttpAbortRequest(int reqId);
int sceHttpGetResponseContentLength(int reqId, unsigned long long int *contentLength);
int sceHttpGetStatusCode(int reqId, int *statusCode);
int sceHttpGetAllResponseHeaders(int reqId, char **header, unsigned int *headerSize);
int sceHttpReadData(int reqId, void *data, unsigned int size);
int sceHttpAddRequestHeader(int id, const char *name, const char *value, unsigned int mode);
int sceHttpRemoveRequestHeader(int id, const char *name);

int sceHttpParseResponseHeader(const char *header, unsigned int headerLen, const char *fieldStr, const char **fieldValue, unsigned int *valueLen);
int sceHttpParseStatusLine(const char *statusLine, unsigned int lineLen, int *httpMajorVer, int *httpMinorVer, int *responseCode, const char **reasonPhrase, unsigned int *phraseLen);

int sceHttpCreateTemplate(const char *userAgent, int httpVer, int autoProxyConf);
int sceHttpDeleteTemplate(int tmplId);
int sceHttpCreateConnection(int tmplId, const char *serverName, const char *scheme, unsigned short port, int enableKeepalive);
int sceHttpCreateConnectionWithURL(int tmplId, const char *url, int enableKeepalive);
int sceHttpDeleteConnection(int connId);
int sceHttpCreateRequest(int connId, int method, const char *path, unsigned long long int contentLength);
int sceHttpCreateRequestWithURL(int connId, int method, const char *url, unsigned long long int contentLength);
int sceHttpDeleteRequest(int reqId);
int sceHttpSetResponseHeaderMaxSize(int id, unsigned int headerSize);
int sceHttpSetRequestContentLength(int id, unsigned long long int contentLength);

// uri
int sceHttpUriEscape(char *out, unsigned int *require, unsigned int prepare, const char *in);
int sceHttpUriUnescape(char *out, unsigned int *require, unsigned int prepare, const char *in);
int sceHttpUriParse(SceHttpUriElement *out, const char *srcUrl, void *pool, unsigned int *require, unsigned int prepare);
int sceHttpUriBuild(char *out, unsigned int *require, unsigned int prepare, const SceHttpUriElement *srcElement, unsigned int option);
int sceHttpUriMerge(char *mergedUrl, const char *url, const char *relativeUrl, unsigned int *require, unsigned int prepare, unsigned int option);
int sceHttpUriSweepPath(char *dst, const char *src , unsigned int srcSize);

// https
/**
 * Register RootCA certificate for HTTPS authentication
 *
 * @param[in] caCertNum - Number of elements of the list referncing to RootCA certificate
 * @param[in] caList - List referencing to RootCA certificate
 * @param[in] cert - Client certificate
 * @param[in] privKey - Private key
 *
 * @return 0 on success, < 0 on error.
 *
 * @note <b>SCE_SYSMODULE_HTTPS</b> module must be loaded with ::sceSysmoduleLoadModule to use this function.
 */
int sceHttpsLoadCert(int caCertNum, const SceHttpsData **caList, const SceHttpsData *cert, const SceHttpsData *privKey);
int sceHttpsUnloadCert(void);
int sceHttpsEnableOption(unsigned int sslFlags);
int sceHttpsDisableOption(unsigned int sslFlags);
int sceHttpsGetSslError(int id, int *errNum, unsigned int *detail);
int sceHttpsSetSslCallback(int id, SceHttpsCallback cbfunc, void *userArg);
int sceHttpsGetCaList(SceHttpsCaList* caList);
int sceHttpsFreeCaList(SceHttpsCaList* caList);

// cookie
int sceHttpSetCookieEnabled(int id, int enable);
int sceHttpGetCookieEnabled(int id, int *enable);
int sceHttpGetCookie(const char *url, char *cookie, unsigned int *cookieLength,unsigned int prepare, int secure);
int sceHttpAddCookie(const char *url, const char *cookie, unsigned int cookieLength);
int sceHttpSetCookieRecvCallback(int id, SceHttpCookieRecvCallback cbfunc, void *userArg);
int sceHttpSetCookieSendCallback(int id, SceHttpCookieSendCallback cbfunc, void *userArg);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NET_HTTP_H_ */

