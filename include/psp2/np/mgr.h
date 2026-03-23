/**
 * \usergroup{SceNpManager}
 * \usage{psp2/np/manager.h}
 */


#ifndef _PSP2_NP_MGR_H_
#define _PSP2_NP_MGR_H_


#include <vitasdk/build_utils.h>
#include <psp2/np/common.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceNpInit(const SceNpCommunicationConfig *config, SceNpOptParam *opt);
void sceNpTerm();
int sceNpManagerGetNpId(SceNpId *np_id);
int sceNpManagerGetAccountRegion(SceNpCountryCode *country_code, int *language_code);


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NP_MGR_H_ */
