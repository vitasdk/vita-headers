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
	unsigned int timestamp;			//!< Local timestamp of the device
	SceFVector3 acceleration;		//!< Accelerometer data
	SceFVector3 angularVelocity;	//!< Angular velocity data
	uint8_t reserved1[12];			//!< Reserved data
	SceFQuaternion deviceQuat;		//!< Orientation data as a Quaternion
	SceFMatrix4 rotationMatrix;		//!< Orientation data as a rotation matrix
	SceFMatrix4 nedMatrix;			//!< Magnetometer orientation matrix
	uint8_t reserved2[4];			//!< Reserved data
	SceFVector3 basicOrientation;	//!< Orientation of the device in reference to gravity
	SceULong64 hostTimestamp;		//!< Timestamp of the data in microseconds
	uint8_t reserved3[36];			//!< Reserved data
	uint8_t magFieldStrength;		//!< Either 0 or 2 depending on surrounding metal objects
	uint8_t unknown;				//!< Unknown
	uint8_t reserved4[2];			//!< Reserved data
} SceMotionState;

typedef struct SceMotionSensorState {
	SceFVector3 accelerometer;		//!< Accelerometer data
	SceFVector3 gyro;				//!< Angular velocity data
	uint8_t reserved1[12];			//!< Reserved data
	unsigned int timestamp;			//!< Timestamp of the data in microseconds
	unsigned int counter;			//!< Number of requested state
	uint8_t reserved2[4];			//!< Reserved data
	SceULong64 hostTimestamp;		//!< Timestamp of the data in microseconds
	uint8_t unknown;				//!< Unknown
	uint8_t reserved3[7];			//!< Reserved data
} SceMotionSensorState;

typedef struct SceMotionDeviceLocation{
	SceFVector3 accelerometer;		//!< Location of te accelerometer in relation to the center of the device (in mm)
	SceFVector3	gyro;				//!< Location of te gyroscope in relation to the center of the device (in mm)
	uint8_t reserved[24];			//!< Reserved data
} SceMotionDeviceLocation;

/* prototypes */

/**
 * Gets the current motion state.
 *
 * @param[out] *motionState - See ::SceMotionState
 *
 * @return 0, <0 on error.
 */
int sceMotionGetState(SceMotionState *motionState);

/**
 * Gets the current motion sensor state
 *
 * @param[in] numRecords - Amount of records to get
 * @param[out] *motionSensorState - See ::SceMotionSensorState
 *
 * @return 0, <0 on error
 */
int sceMotionGetSensorState(SceMotionSensorState *sensorState, int numRecords);

/**
 * Gets the location of the device's sensors in relation to its center point (in mm)
 *
 * @param[out] *deviceLocation - See ::SceMotionDeviceLocation
 *
 * @return 0, <0 on error
 */
int sceMotionGetDeviceLocation(SceMotionDeviceLocation *deviceLocation);

/**
 * Gets the basic orientation of the device in relation to gravity
 *
 * @param[out] *basicOrientation
 *
 * @return 0, <0 on error
 */
int sceMotionGetBasicOrientation(SceFVector3 *basicOrientation);

/**
 * Rotate the yaw axis
 *
 * @param[in] radians - Rotation angle in radians
 *
 * @return 0
 */
int sceMotionRotateYaw(float radians);

/**
 * Get Status of tilt correction
 *
 * @return 1 if enabled, 0 if disabled
 */
int sceMotionGetTiltCorrection(void);

/**
 * Activate/deactivate tilt correction
 *
 * @param[in] setValue - 1 to enable, 0 to disable
 *
 * @return 0
 */
int sceMotionSetTiltCorrection(int setValue);

/**
 * Get status of deadbanding
 *
 * @return 1 if enabled, 0 if disabled
 */
int sceMotionGetDeadband(void);

/**
 * Activate/deactivate deadbanding (comparable to deadzoning but for motion)
 *
 * @param[in] setValue - 1 to enable, 0 to disable
 *
 * @return 0
 */
int sceMotionSetDeadband(int setValue);

/**
 * Get status of gyroscope bias correction
 *
 * @return 1 if enabled, 0 if disabled
 */
int	sceMotionGetGyroBiasCorrection(void);

/**
 * Activate/deactivate gyroscope bias correction
 *
 * @param[in] setValue - 1 to enable, 0 to disable
 *
 * @return 0
 */
int sceMotionSetGyroBiasCorrection(int setValue);

/**
 * Define the angle threshold for basic orientation
 *
 * @param[in] angle - range of 0 to 45 degrees
 *
 * @return 0
 */
int sceMotionSetAngleThreshold(float angle);

/**
 * Get the angle threshold for basic orientation
 *
 * @return angle in degrees
 */
float sceMotionGetAngleThreshold(void);

/**
 * Set current orientation as origin
 *
 * @return 0, <0 on error
 */
int sceMotionReset(void);

/**
 * Start magnetometer sampling
 *
 * @return 0, <0 on error
 */
int sceMotionMagnetometerOn(void);

/**
 * Stop magnetometer sampling
 *
 * @return 0, <0 on error
 */
int sceMotionMagnetometerOff(void);

/**
 * Get status of magnetometer sampling
 *
 * @return 1 if enabled, 0 if disabled
 */
int sceMotionGetMagnetometerState(void);

/**
 * Start sampling
 *
 * @return 0, <0 on error
 */
int sceMotionStartSampling(void);

/**
 * Stop sampling
 *
 * @return 0, <0 on error
 */
int sceMotionStopSampling(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_MOTION_H_ */

