#ifndef _VITASDK_UTILS_H_
#define _VITASDK_UTILS_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <psp2/types.h>

/**
 * @brief vitasdk_get_tls_data - Get pointer to memory location to store TLS data
 * @param thid - The thread UID to access TLS
 * @return A pointer to a memory location containing the pointer to TLS data
 */
void *vitasdk_get_tls_data(SceUID thid);

/**
 * @brief vitasdk_get_pthread_data - Get pointer to memory to store pthread metadata
 * @param thid - The thread UID where the TLS will be based on
 * @return A pointer to a memory location within the TLS
 */
void *vitasdk_get_pthread_data(SceUID thid);

/**
 * @brief vitasdk_delete_thread_reent delete the internal reent data for the specified thread
 * @param thid - The UID for the thread to delete reent data
 * @return non-zero if reent data is deleted
 */
int vitasdk_delete_thread_reent(SceUID thid);

#ifdef __cplusplus
}
#endif
#endif /* _VITASDK_UTILS_H_ */
