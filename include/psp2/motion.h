/**
 * \usergroup{SceMotion}
 * \usage{psp2/motion.h,SceMotion_stub}
 */


#ifndef _PSP2_MOTION_H_
#define _PSP2_MOTION_H_

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* struct */

typedef struct SceMotionState {
	unsigned int timestamp;
	SceFVector3 acceleration;
	SceFVector3 angularVelocity;
	uint8_t reserved1[12];
	SceFQuaternion deviceQuat;
	SceUMatrix4 rotationMatrix;
	SceUMatrix4 nedMatrix;
	uint32_t reserved2;
	SceFVector3 basicOrientation;
	SceULong64 hostTimestamp;
	uint8_t reserved[40];
} SceMotionState;

typedef struct SceMotionSensorState {
	SceFVector3 accelerometer;
	SceFVector3 gyro;
	uint8_t reserved1[12];
	unsigned int timestamp;
	unsigned int counter;
	uint32_t reserved2;
	SceULong64 hostTimestamp;
	uint8_t reserved3[8];
} SceMotionSensorState;

/* prototypes */

int sceMotionGetState(SceMotionState *motionState);
int sceMotionGetSensorState(SceMotionSensorState *sensorState, int numRecords);
int sceMotionGetBasicOrientation(SceFVector3 *basicOrientation);
int sceMotionRotateYaw(float radians);
int sceMotionGetTiltCorrection(void);
int sceMotionSetTiltCorrection(int setValue);
int sceMotionGetDeadband(void);
int sceMotionSetDeadband(int setValue);
int sceMotionSetAngleThreshold(float angle);
float sceMotionGetAngleThreshold(void);
int sceMotionReset(void);
int sceMotionMagnetometerOn(void);
int sceMotionMagnetometerOff(void);
int sceMotionGetMagnetometerState(void);
int sceMotionStartSampling(void);
int sceMotionStopSampling(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_MOTION_H_ */

