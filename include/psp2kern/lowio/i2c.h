/**
 * \kernelgroup{SceI2c}
 * \usage{psp2kern/lowio/i2c.h,SceI2cForDriver_stub}
 */

#ifndef _PSP2KERN_LOWIO_I2C_H_
#define _PSP2KERN_LOWIO_I2C_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceI2cErrorCode {
	SCE_I2C_ERROR_INVALID_BUS	= 0x803F0300,
	SCE_I2C_ERROR_INVALID_SIZE	= 0x803F0302,
	SCE_I2C_ERROR_INVALID_ADDR	= 0x803F0303
} SceI2cErrorCode;

typedef struct SceI2cDebugHandlers {
	unsigned int size;
	void (*write_start)(int bus, int addr, unsigned char *buffer, int size);
	void (*write_end)(int bus, int error, int result);
	void (*read_start)(int bus, int addr, unsigned char *buffer, int size);
	void (*read_end)(int bus, int error, int result);
	void (*write_read_start)(int bus, int write_addr, unsigned char *write_buffer, int write_size,
		unsigned int read_addr, unsigned char *read_buffer, int read_size);
	void (*write_read_end)(int bus, int error, int result);
} SceI2cDebugHandlers;

int ksceI2cInit(int bus);
int ksceI2cReset(int bus);
int ksceI2cTransferRead(int bus, unsigned int addr, unsigned char *buffer, int size);
int ksceI2cTransferWrite(int bus, unsigned int addr, const unsigned char *buffer, int size);
int ksceI2cTransferWriteRead(int bus,
	unsigned int write_addr, unsigned char *write_buffer, int write_size,
	unsigned int read_addr, unsigned char *read_buffer, int read_size);

int ksceI2cSetDebugHandlers(int bus, SceI2cDebugHandlers *debug_handlers);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2KERN_LOWIO_I2C_H_ */

