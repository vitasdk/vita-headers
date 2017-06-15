/**
 * \kernelgroup{SceI2c}
 * \usage{psp2kern/lowio/i2c.h,SceI2cForDriver_stub}
 */

#ifndef _PSP2_LOWIO_I2C_H_
#define _PSP2_LOWIO_I2C_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceI2cErrorCode {
	SCE_I2C_ERROR_INVALID_BUS	= 0x803F0300,
	SCE_I2C_ERROR_INVALID_SIZE	= 0x803F0302,
	SCE_I2C_ERROR_INVALID_DEVICE	= 0x803F0303
} SceI2cErrorCode;

typedef struct SceI2cDebugHandlers {
	unsigned int size;
	void (*write_start)(int bus, int device, unsigned char *buffer, int size);
	void (*write_error)(int bus, int error, int result);
	void (*read_start)(int bus, int device, unsigned char *buffer, int size);
	void (*read_error)(int bus, int error, int result);
	void (*write_read_start)(int bus, int write_device, unsigned char *write_buffer, int write_size);
	void (*write_read_error)(int bus, int error, int result);
} SceI2cDebugHandlers;

int ksceI2cTransferRead(int bus, unsigned int address, unsigned char *buffer, int size);
int ksceI2cTransferWrite(int bus, unsigned int device, const unsigned char *buffer, int size);
int ksceI2cTransferWriteRead(int bus,
	unsigned int write_device, const unsigned char *write_buffer, int write_size,
	unsigned int read_device, unsigned char *read_buffer, int read_size);

int ksceI2cSetDebugHandlers(int bus, SceI2cDebugHandlers *debug_handlers);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_LOWIO_I2C_H_ */

