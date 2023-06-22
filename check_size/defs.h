
#ifndef _VITASDK_CHECKER_DEFS_H_
#define _VITASDK_CHECKER_DEFS_H_

#ifdef __cplusplus
extern "C" {
#endif


int taiGetModuleInfo(const char *module_name, void *info);
int taiGetModuleInfoForKernel(signed int pid, const char *module_name, void *info);

#ifndef VITASDK_BUILD_ASSERT
#define VITASDK_BUILD_ASSERT(condition) ((void)sizeof(char[1 - (2*!(condition))]))
#endif


#ifdef __cplusplus
}
#endif

#endif /* _VITASDK_CHECKER_DEFS_H_ */
