#ifndef __STAT_H
#define __STAT_H

#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

typedef long int ssize_t;

typedef uint32_t mode_t;
typedef uint32_t ino_t;
typedef uint32_t dev_t;
typedef uint32_t off_t;

typedef uint32_t ino_t;
typedef uint32_t nlink_t;
typedef uint32_t uid_t;
typedef uint32_t gid_t;
typedef uint32_t blksize_t;
typedef uint32_t blkcnt_t;

struct stat
{
	mode_t st_mode;
	ino_t st_ino;
	dev_t st_dev;
	dev_t st_rdev;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	off_t st_size;
	struct timespec st_atim;
	struct timespec st_mtim;
	struct timespec st_ctim;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
};
#ifdef __cplusplus
extern "C" {
#endif

int chmod(const char* name, mode_t mode);
int fchmod(int fd, mode_t mode);
int fstat(int fd, struct stat* stat);
int lstat(const char* name, struct stat* stat);
int mkdir(const char* name, mode_t mode);
int mkfifo(const char* name, mode_t mode);
int mknod(const char* name, mode_t mode, dev_t dev);
int stat(const char* name, struct stat* stat);
mode_t umask(mode_t mode);

#ifdef __cplusplus
}
#endif
	
#endif