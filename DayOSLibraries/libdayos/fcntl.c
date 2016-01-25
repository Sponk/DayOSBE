#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dayos.h>

static const int vector_alloc_step = 16; 
static int vector_size = 0;
static int vector_allocated_size = 0;
static FILE** vector_array = NULL;

// TODO: Linked list with free entries

int fcntl(int fd, int cmd, ...)
{
	
}

int open(const char *pathname, int flags, ...)
{
	char args[4];
	FILE* file = NULL;
	int idx = -1;

	if(flags & O_RDONLY)
		args[0] = 'r';

	if(flags & O_WRONLY)
		args[1] = 'w';

	if(flags & O_APPEND)
		args[2] = 'a';

	args[3] = 0;
	// TODO: O_TRUNC, O_EXCL, O_CREAT, O_RDWR

	file = fopen(pathname, args);
	if(!file)
		return -1;

	idx = vector_size++;
	if(vector_size > vector_allocated_size)
	{
			vector_allocated_size += vector_alloc_step;
			vector_array = realloc(vector_array, vector_allocated_size * sizeof(FILE*));
	}

	vector_array[idx] = file;
	return idx;
}

// TODO: Implement creat!
int creat(const char *pathname, mode_t mode)
{
	debug_printf("STUB: %s : %d", __FILE__, __LINE__);
}

int close(int fd)
{
	FILE* f = vector_array[fd];
	vector_array[fd] = NULL;
	return fclose(f);
}

off_t lseek(int fd, off_t offset, int whence)
{
	return fseek(vector_array[fd], offset, whence);
}

ssize_t read(int fd, void *buf, size_t count)
{
	return fread(buf, count, 1, vector_array[fd]);
}

ssize_t write(int fd, const void *buf, size_t count)
{
	return fwrite(buf, count, 1, vector_array[fd]);
}

int fsync(int fd)
{
	fflush(vector_array[fd]);
}

int fdatasync(int fd)
{
	fsync(fd);
}

// TODO: Public interface?
FILE* fd2file(int fd)
{
	if(fd < 0 || fd >= vector_size )
		return NULL;

	return vector_array[fd];
}
