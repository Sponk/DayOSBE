#ifndef __DRIVER_H
#define __DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include <kernelconfig.h>

#define DEVICE_REQUEST_MAGIC 0xDEADBEEF

typedef enum
{
	FS_SIGNAL_MKDIR = 0,
	FS_SIGNAL_OPEN = 1,
	FS_SIGNAL_CLOSE = 2,
	FS_SIGNAL_READ = 3,
	FS_SIGNAL_WRITE = 4,
	FS_SIGNAL_MOUNT = 5,
	FS_SIGNAL_STAT = 6,
	FS_SIGNAL_OPEN_DIR = 7,
	FS_SIGNAL_READ_DIR = 8
} FS_SIGNALS;

typedef enum
{
	DEVICE_READ = 0x1,
	DEVICE_WRITE = 0x2,
	DEVICE_IOCTL = 0x3
} DEVICE_ACTIONS;

struct device_request
{
	uint32_t magic;
	uint32_t size;
	uint8_t character;
};

#define FS_REQUEST_PATHLEN (MESSAGE_STRING_SIZE - 8)
struct fs_request
{
	uint32_t magic;
	uint32_t param;
	int8_t path[256];
};

#endif
