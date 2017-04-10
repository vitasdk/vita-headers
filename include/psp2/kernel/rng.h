/**
 * \usergroup{SceRng}
 * \usage{psp2/kernel/rng.h}
 */


#ifndef _PSP2_KERNEL_RNG_H_
#define _PSP2_KERNEL_RNG_H_

#ifdef __cplusplus
extern "C" {
#endif

/***
 * Fills the output buffer with random data.
 *
 * @param[out] output - Output buffer
 * @param[in] size - Size of the output buffer, 64 bytes maximum
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetRandomNumber(void *output, unsigned size);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_RNG_H_ */

