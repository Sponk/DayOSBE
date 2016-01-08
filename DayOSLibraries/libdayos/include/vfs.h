#ifndef VFS_H
#define VFS_H

#include <stddef.h>
#include <kernelconfig.h>
#include <sys/stat.h>

typedef enum
{
	VFS_MODE_RO = 1,
	VFS_MODE_WO = 2,
	VFS_MODE_RW = VFS_MODE_RO | VFS_MODE_WO
} VFS_OPEN_MODES;

typedef enum
{
	VFS_SIGNAL_CREATE_DEVICE = 0,
	VFS_SIGNAL_OPEN = 1,
	VFS_SIGNAL_MOUNT_DEVICE = 2,
	VFS_SIGNAL_MOUNT_RAMDISK = 3
} VFS_SIGNALS;

typedef enum
{
	VFS_CHARACTER_DEVICE = 0,
	VFS_BLOCK_DEVICE = 1,
	VFS_MOUNTPOINT = 2,
	VFS_DIRECTORY = 3
} DEVICE_TYPES;

#include <stdint.h>

// One vfs_request has to fit into one message.
// The size of the flags is 6*4byte on 32bit machines => 24bytes in total.
#define VFS_FILENAME_SIZE (MESSAGE_STRING_SIZE - 24)

// Magic number to check for sanity
#define VFS_MAGIC 0xDEADBEEF

// Structures for IA32
struct vfs_request
{
	int8_t path[VFS_FILENAME_SIZE];
	uint32_t mode;
	uint32_t param;
	uint32_t size;
	uint32_t offset;
	uint32_t magic;
	uint32_t id;
};

struct vfs_file
{
	int8_t path[VFS_FILENAME_SIZE];
	pid_t device;

	uint32_t type;
	uint32_t guid;
	uint32_t uid;
	size_t offset;
	size_t size;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates a device descriptor in the VFS that can be opened for reading
 * or writing.
 * @param path The path to the device file.
 * @param mode The mode of the device (@see VFS_OPEN_MODES)
 * @param type The type of the device (@see DEVICE_TYPES)
 *
 * @return SIGNAL_OK if everything went well, SIGNAL_FAIL if not.
 */
int vfs_create_device(const char* path, unsigned int mode, unsigned int type);
int vfs_mount_device(const char* src, const char* dest, const char* fsd,
					 unsigned int mode);
int vfs_mount_ramdisk(const char* dest, unsigned int mode);

int vfs_stat(struct vfs_file* file, struct stat* stat);

#ifdef __cplusplus
}
#endif

#endif
