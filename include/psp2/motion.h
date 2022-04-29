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

/* enum */

typedef enum SceMotionMagFieldStability {
	SCE_MOTION_MAGFIELD_UNSTABLE    = 0,
	SCE_MOTION_MAGFIELD_UNUSED      = 1,
	SCE_MOTION_MAGFIELD_STABLE      = 2
} SceMotionMagFieldStability;

typedef enum SceMotionErrorCode {
	SCE_MOTION_ERROR_DATA_INVALID       = 0x80360200,
	SCE_MOTION_ERROR_READING            = 0x80360201,
	SCE_MOTION_ERROR_NON_INIT_ERR       = 0x80360202,
	SCE_MOTION_ERROR_STATE_INVALID      = 0x80360203,
	SCE_MOTION_ERROR_CALIB_READ_FAIL    = 0x80360204,
	SCE_MOTION_ERROR_OUT_OF_BOUNDS      = 0x80360205,
	SCE_MOTION_ERROR_NOT_SAMPLING       = 0x80360206,
	SCE_MOTION_ERROR_ALREADY_SAMPLING   = 0x80360207,
	SCE_MOTION_ERROR_MEM_IN_USE         = 0x80360208
} SceMotionErrorCode;


/* struct */

/** Returned motion state */
typedef struct SceMotionState {
	unsigned int timestamp;         //!< Local timestamp of the device
	SceFVector3 acceleration;       //!< Accelerometer data
	SceFVector3 angularVelocity;    //!< Angular velocity data
	uint8_t reserved1[12];          //!< Reserved data
	SceFQuaternion deviceQuat;      //!< Orientation data as a Quaternion
	SceFMatrix4 rotationMatrix;     //!< Orientation data as a rotation matrix
	SceFMatrix4 nedMatrix;          //!< Magnetometer orientation matrix
	uint8_t reserved2[4];           //!< Reserved data
	SceFVector3 basicOrientation;   //!< Orientation of the device in reference to gravity
	SceULong64 hostTimestamp;       //!< Timestamp of the data in microseconds
	uint8_t reserved3[36];          //!< Reserved data
	uint8_t magFieldStability;      //!< One of ::SceMotionMagFieldStability
	uint8_t unknown;                //!< Unknown
	uint8_t reserved4[2];           //!< Reserved data
} SceMotionState;

/** Returned motion sensor state 
* @note - ::SceMotionSensorState holds actual sensor data as opposed to ::SceMotionState which uses a calculated state
*/
typedef struct SceMotionSensorState {
	SceFVector3 accelerometer;      //!< Accelerometer data
	SceFVector3 gyro;               //!< Angular velocity data
	uint8_t reserved1[12];          //!< Reserved data
	unsigned int timestamp;         //!< Timestamp of the data in microseconds
	unsigned int counter;           //!< Number of requested state
	uint8_t reserved2[4];           //!< Reserved data
	SceULong64 hostTimestamp;       //!< Timestamp of the data in microseconds
	uint8_t unknown;                //!< Unknown
	uint8_t reserved3[7];           //!< Reserved data
} SceMotionSensorState;

/** Returned location of both the accelerometer and gyroscope in mm
* @note - Axies are fixed with z axis being straight perpendicular through the screen and x axis being parallel to the screen's bottom and top edge
* @note - Direction of the z axis is as if the device were laying on a flat surface, oled/lcd side facing upwards
* @note - OLED models should return the following values:
* @note - Accelerometer: x == -32; y == 12; z == -8
* @note - Gyroscope: x == -33; y == 6; z == -8
* @note - LCD models should return the following values:
* @note - Accelerometer: x == 13; y == 19; z == -8
* @note - Gyroscope: x == 13; y == 19; z == -8
*/
typedef struct SceMotionDeviceLocation {
	SceFVector3 accelerometer;      //!< Location of te accelerometer in relation to the center of the device (in mm)
	SceFVector3 gyro;               //!< Location of te gyroscope in relation to the center of the device (in mm)
	uint8_t reserved[24];           //!< Reserved data
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
 * Gets the location of the device's sensors in relation to its center point (in mm).
 *
 * @param[out] *deviceLocation - See ::SceMotionDeviceLocation
 *
 * @return 0, <0 on error
 */
int sceMotionGetDeviceLocation(SceMotionDeviceLocation *deviceLocation);

/**
 * Gets the basic orientation of the device in relation to gravity
 * @note - Possible values in the output vector are -1, 0 and 1
 * @note - Using the same coordinate system as ::SceMotionDeviceLocation  these values are set in the vector depending on if the axies' positive or negative directions are facing away from gravitational pull
 * @note - For example if the vita is laying on a flat and level surface, with the OLED/LCD side facing upwards, the Z part of the vector will be 1
 * @note - Now flipping the device upwards, taking hold of the right joystick's side, until it forms a 90 degree angle to the surface will result in the X part of the vector being 1 instead
 * @note - Both examples would result in the returned value being -1 if flipped 180 degrees, swapping their top and bottom sides in correlation to gravity
 * @note - The angle of rotation in relation to being in a centered state on an axis (returned as 0) after which the device will change the value is determined by ::SceMotionSetAngleThreshold
 * @note - In order for this function to return up to date data, ::sceMotionGetState must be called prior to call this function.
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
 * @note - With tilt correction enabled the data for roll and pitch movements of the device get recalculated to not distort the yaw movements in relation to gravity
 * @note - Enabled by default
 * @return 1 if enabled, 0 if disabled
 */
int sceMotionGetTiltCorrection(void);

/**
 * Activate/deactivate tilt correction
 * @note - For more information see ::sceMotionGetTiltCorrection
 * @param[in] setValue - 1 to enable, 0 to disable
 *
 * @return 0
 */
int sceMotionSetTiltCorrection(int setValue);

/**
 * Get status of deadbanding
 * @note - With deadbanding enabled the device will filter out small movements to reduce jitter
 * @note - Potentially decreaces accuracy of fine movements
 * @note - Enabled by default
 * @return 1 if enabled, 0 if disabled
 */
int sceMotionGetDeadband(void);

/**
 * Activate/deactivate deadbanding
 * @note - For more information see ::sceMotionGetDeadbanding
 * @param[in] setValue - 1 to enable, 0 to disable
 *
 * @return 0
 */
int sceMotionSetDeadband(int setValue);

/**
 * Get status of gyroscope bias correction
 * @note - With gyroscope bias correction enabled the device will attempt to adjust for outside influences that could impact calibration
 * @note - Enabled by default
 * @return 1 if enabled, 0 if disabled
 */
int sceMotionGetGyroBiasCorrection(void);

/**
 * Activate/deactivate gyroscope bias correction
 * @note - For more information see ::sceMotionGetGyroBiasCorrection
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
