/**
 * \usergroup{SceMtpIfDriver}
 * \usage{psp2/mtpif.h,SceMtpIfDriver_stub}
 */


#ifndef _PSP2_MTPIF_H_
#define _PSP2_MTPIF_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Start MTP driver
 *
 * @param[in] flags - Set to 1
 *
 * @return 0 on success, < 0 on error.
*/
int sceMtpIfStartDriver(int flags);

/**
 * Stop MTP driver
 *
 * @param[in] flags - Set to 1
 *
 * @return 0 on success, < 0 on error.
*/
int sceMtpIfStopDriver(int flags);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_MTPIF_H_ */
