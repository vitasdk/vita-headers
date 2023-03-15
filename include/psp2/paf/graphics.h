/**
 * \usergroup{ScePaf}
 * \usage{psp2/paf/graphics.h,ScePaf_stub}
 */


#ifndef _PSP2_PAF_GRAPHICS_H_
#define _PSP2_PAF_GRAPHICS_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Update the current wave
 *
 * @param[in] index           - The index from 0 to 0x1F within range.
 * @param[in] update_interval - The update interval. 0.0f to it will change soon. 1.0f will slowly turn into an updated wave after 1 second, just like when you change it the normal way.
 *
 * @return 0 on success, <0 otherwise.
 */
int scePafGraphicsUpdateCurrentWave(SceUInt32 index, SceFloat32 update_interval);


extern SceUInt32 scePafGraphicsCurrentWave;


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PAF_GRAPHICS_H_ */
