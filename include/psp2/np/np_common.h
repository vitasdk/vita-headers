/**
 * \usergroup{SceNp}
 * \usage{psp2/np/np_common.h}
 */


#ifndef _PSP2_NP_COMMON_H_
#define _PSP2_NP_COMMON_H_

#include <vitasdk/build_utils.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceNpCommunicationId {
	char data[9];
	char term;
	SceUChar8 num;
	char dummy;
} SceNpCommunicationId;
VITASDK_BUILD_ASSERT_EQ(0xC, SceNpCommunicationId);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NP_COMMON_H_ */
