#ifndef _VITASDK_BUILD_UTILS_H_
#define _VITASDK_BUILD_UTILS_H_

#ifndef VITASDK_BUILD_ASSERT
#define VITASDK_BUILD_ASSERT(condition) ((void)sizeof(char[1 - (2*!(condition))]))
#endif

#ifdef ENABLE_VITASDK_BUILD_ASSERT
#define VITASDK_BUILD_ASSERT_EX(__name__, __cond__) inline void __vitasdk_check_ex_ ## __name__ (void){VITASDK_BUILD_ASSERT((__cond__));}
#define VITASDK_BUILD_ASSERT_EQ(__size__, __name__) inline void __vitasdk_check_eq_ ## __name__ (void){VITASDK_BUILD_ASSERT(((__size__) == sizeof(__name__)));}
#else
#define VITASDK_BUILD_ASSERT_EX(__name__, __cond__)
#define VITASDK_BUILD_ASSERT_EQ(__size__, __name__)
#endif

#ifdef  __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* _VITASDK_BUILD_UTILS_H_ */
