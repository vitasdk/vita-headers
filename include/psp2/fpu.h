/**
 * \usergroup{SceFpu}
 * \usage{psp2/fpu.h,SceFpu_stub}
 * \staticnote
 */


#ifndef _PSP2_FPU_H_
#define _PSP2_FPU_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform sine calculation of a number
 *
 * @param[in] value - Number to use
 *
 * @return The sine of the number.
*/
float sceFpuSinf(float value);

/**
 * Perform cosine calculation of a number
 *
 * @param[in] value - Number to use
 *
 * @return The cosine of the number.
*/
float sceFpuCosf(float value);

/**
 * Perform tangent calculation of a number
 *
 * @param[in] value - Number to use
 *
 * @return The tangent of the number.
*/
float sceFpuTanf(float value);

/**
 * Perform arc sine calculation of a number
 *
 * @param[in] value - Number to use
 *
 * @return The arc sine of the number.
*/
float sceFpuAsinf(float value);

/**
 * Perform arc cosine calculation of a number
 *
 * @param[in] value - Number to use
 *
 * @return The arc cosine of the number.
*/
float sceFpuAcosf(float value);

/**
 * Perform arc tangent calculation of a number
 *
 * @param[in] value - Number to use
 *
 * @return The arc tangent of the number.
*/
float sceFpuAtanf(float value);

/**
 * Perform arc tangent calculation of x/y
 *
 * @param[in] x - X value to use
 * @param[in] y - Y value to use
 *
 * @return The arc tangent of x/y.
*/
float sceFpuAtan2f(float x, float y);

/**
 * Perform logarithm calculation
 *
 * @param[in] value - Number to use
 *
 * @return The logarithm of the number.
*/
float sceFpuLogf(float value);

/**
 * Perform base 2 logarithm calculation
 *
 * @param[in] value - Number to use
 *
 * @return The logarithm of the number.
*/
float sceFpuLog2f(float value);

/**
 * Perform base 10 logarithm calculation
 *
 * @param[in] value - Number to use
 *
 * @return The logarithm of the number.
*/
float sceFpuLog10f(float value);

/**
 * Perform power elevation of e
 *
 * @param[in] value - Power to use
 *
 * @return The power elevation of e for the given value.
*/
float sceFpuExpf(float value);

/**
 * Perform power elevation of 2
 *
 * @param[in] value - Power to use
 *
 * @return The power elevation of 2 for the given value.
*/
float sceFpuExp2f(float value);

/**
 * Perform power elevation of 10
 *
 * @param[in] value - Power to use
 *
 * @return The power elevation of 10 for the given value.
*/
float sceFpuExp10f(float value);

/**
 * Perform a power elevation
 *
 * @param[in] x - Number to elevate
 * @param[in] y - Power to use
 *
 * @return The resulting number of the operation.
*/
float sceFpuPowf(float x, float y);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FPU_H_ */

