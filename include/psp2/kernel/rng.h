/**
 * \file
 * \brief Functions to generate random numbers
 *
 * Copyright (C) 2015 PSP2SDK Project
 * Copyright (C) 2016 vitasdk
 * This header file is licensed under the MIT license.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
