/**
 * \file
 * \brief Header file which defines FPU functions
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_FPU_H_
#define _PSP2_FPU_H_

#ifdef __cplusplus
extern "C" {
#endif

float sceFpuLog2f(float x);
float sceFpuSinf(float x);
float sceFpuExp10f(float x);
float sceFpuAsinf(float x);
float sceFpuAtanf(float x);
float sceFpuAcosf(float x);
float sceFpuTanf(float x);
float sceFpuLogf(float x);
float sceFpuExp2f(float x);
float sceFpuLog10f(float x);
float sceFpuAtan2f(float y, float x);
float sceFpuCosf(float x);
float sceFpuPowf(float base, float exponent);
float sceFpuExpf(float x);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_FPU_H_ */
