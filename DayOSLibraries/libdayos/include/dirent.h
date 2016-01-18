#ifndef __DIRENT_H
#define __DIRENT_H

#include <sys/types.h>
#include <vfs.h>

struct dirent 
{
	ino_t d_ino;
	off_t d_off;
	unsigned short d_reclen;
	unsigned char d_type;
	char d_name[256];
};

typedef struct
{
	ino_t d_ino;
	char d_name[256];
	struct vfs_file file;
	struct dirent current;
} DIR;

#ifdef __cplusplus
extern "C" {
#endif

int closedir(DIR* dir);
DIR* opendir(const char* path);
struct dirent* readdir(DIR* dir);
int readdir_r(DIR* dir, struct dirent* entry, struct dirent** entries);
void rewinddir(DIR* dir);
void seekdir(DIR* dir, long off);
long telldir(DIR* dir);

#ifdef __cplusplus
}
#endif

#endif
