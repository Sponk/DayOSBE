#ifndef __FCNTL_H
#define __FCNTL_H

#include <stdint.h>
#include <stddef.h>

#include <dirent.h>

#define S_IRWXU (00700)
#define S_IRUSR (00400)
#define S_IWUSR (00200)
#define S_IXUSR (00100)
#define S_IRWXG (00070)
#define S_IRGRP (00040)
#define S_IWGRP (00020)
#define S_IXGRP (00010)
#define S_IRWXO (00007)
#define S_IROTH (00004)
#define S_IWOTH (00002)
#define S_IXOTH (00001)

#define O_ACCMODE	0003
#define O_RDONLY	00
#define O_WRONLY	01
#define O_RDWR 		02

#define O_CREAT	   	0100
#define O_EXCL		0200
#define O_NOCTTY	0400
#define O_TRUNC		01000
#define O_APPEND	02000
#define O_NONBLOCK	04000
#define O_NDELAY	O_NONBLOCK
#define O_SYNC		04010000
#define O_FSYNC		O_SYNC
#define O_ASYNC		020000

#define F_DUPFD 0
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4

#define FD_CLOEXEC 1

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// int open(const char *pathname, int flags, mode_t mode);
int open(const char *pathname, int flags, ...);

int creat(const char *pathname, mode_t mode);
int close(int fd);

off_t lseek(int fd, off_t offset, int whence); 
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count); 

int fsync(int fd);
int fdatasync(int fd); 

int fcntl(int fd, int cmd, ...);

#ifdef  __cplusplus
}
#endif
#endif