#include <stdio.h>
#include <string.h>
#include <service.h>
#include <message.h>
#include <stdlib.h>
#include <vfs.h>
#include <sleep.h>
#include <driver.h>
#include <errno.h>
#include <sys/stat.h>

#define TIMEOUT 10

FILE* stdin;
FILE* stdout;
FILE* stderr;

int fileno(FILE* stream)
{
	
}

FILE* fdopen(int fd, const char* mode)
{
	return NULL;
}

FILE* fopen(const char* filename, const char* mode)
{
	if (!filename || !mode)
		return NULL;

	message_t msg;
	struct vfs_request* request = (struct vfs_request*)msg.message;
	struct vfs_file* vfile = (struct vfs_file*)msg.message;

	pid_t pid = get_service_pid("vfs");

	if (pid == 0)
		return NULL;

	uint32_t intmode = 0;
	while (*mode)
	{
		if (*mode == 'r')
			intmode |= VFS_MODE_RO;
		else if (*mode == 'w')
			intmode |= VFS_MODE_WO;
		mode++;
	}

	FILE* f = malloc(sizeof(FILE));
	if (!f)
		return NULL;

	request->magic = VFS_MAGIC;

	// FIXME: STRNCPY!
	strcpy(request->path, filename);
	request->mode = intmode;

	msg.signal = VFS_SIGNAL_OPEN;
	send_message(&msg, pid);
	if (receive_message_timeout(&msg, pid, 100, 5) == MESSAGE_ERR_RECEIVE)
	{
		free(f);
		return NULL;
	}

	if (msg.signal == SIGNAL_FAIL)
	{
		free(f);
		return NULL;
	}

	// Tell the FS driver (in case of a mounted device)
	if (vfile->type == VFS_MOUNTPOINT)
	{
		message_t mountmsg;
		struct vfs_request* fs_req = (struct vfs_request*)&mountmsg.message;
		mountmsg.signal = FS_SIGNAL_OPEN;
		strcpy(fs_req->path, vfile->path);
		fs_req->mode = intmode;

		send_message(&mountmsg, vfile->device);

		if (receive_message_timeout(&mountmsg, vfile->device, 100, 5) ==
				MESSAGE_ERR_RECEIVE ||
			mountmsg.signal != SIGNAL_OK)
		{
			free(f);
			return NULL;
		}

		vfs_stat(vfile, &f->stat);
	}

	f->ungetc_data = 0;
	f->error = 0;
	f->native_file = *vfile;
	f->native_file.offset = 0;

	setvbuf(f, NULL, _IOFBF, 512);
	return f;
}

int ferror(FILE* stream)
{
	if (stream)
		return stream->error;

	return 1;
}

// FIXME: Unsure...
FILE* freopen(const char* filename, const char* mode, FILE* stream)
{
	if (!filename)
		filename = stream->native_file.path;

	FILE* tmp = fopen(filename, mode);
	if (!tmp)
		return NULL;

	stream->native_file = tmp->native_file;
	free(tmp);

	return stream;
}

int fclose(FILE* stream)
{
	// if(stream->buffer)
	//	free(stream->buffer);

	free(stream);
	return 0;
}

int fputc(int character, FILE* stream)
{
	if (!stream)
		return 0;
	
}

int fgetc(FILE* stream)
{
	if (!stream)
		return 0;

	if (stream->ungetc_data)
	{
		stream->ungetc_data = 0;
		stream->native_file.offset++;
		return stream->ungetc_data;
	}

	message_t msg;
	struct vfs_request* rq = (struct vfs_request*)&msg.message;
	msg.size = 1;

	if (stream->native_file.type == VFS_MOUNTPOINT)
		msg.signal = FS_SIGNAL_READ;
	else
		msg.signal = DEVICE_READ;

	rq->offset = stream->native_file.offset;

	strcpy(rq->path, stream->native_file.path);
	send_message(&msg, stream->native_file.device);

	while (receive_message(&msg, stream->native_file.device) !=
		   MESSAGE_RECEIVED)
		sleep(1);
	stream->native_file.offset++;

	return msg.message[0];
}

int getc(FILE* stream) { return fgetc(stream); }

int ungetc(int character, FILE* stream)
{
	if (!stream || stream->native_file.offset == 0)
		return EOF;

	stream->ungetc_data = character;
	stream->native_file.offset--;

	return character;
}

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
	if (!ptr || !size || !nmemb || !stream)
		return 0;

	message_t msg;
	struct vfs_request* rq = (struct vfs_request*)&msg.message;

	if (stream->native_file.type == VFS_MOUNTPOINT)
		msg.signal = FS_SIGNAL_READ;
	else
		msg.signal = DEVICE_READ;

	msg.size = size * nmemb;

	rq->offset = stream->native_file.offset;
	strcpy(rq->path, stream->native_file.path);
	send_message(&msg, stream->native_file.device);

	size_t sz = read_message_stream(ptr, msg.size, stream->native_file.device);
	stream->native_file.offset += sz;
	return sz;
}

int fseek(FILE* stream, long int offset, int origin)
{
	if (stream == NULL)
		return 1;

	switch (origin)
	{
		case SEEK_SET:
			stream->native_file.offset = offset;
			return 0;

		case SEEK_CUR:
			stream->native_file.offset += offset;
			return 0;

		case SEEK_END:
		{
			struct stat stat;
			if (vfs_stat(&stream->native_file, &stat))
				return 1;

			stream->native_file.offset = stat.st_size;
			return 0;
		}
	}

	return 1;
}

size_t ftell(FILE* stream) { return stream->native_file.offset; }

int feof(FILE* stream)
{
	if (!stream)
		return 0;

	struct stat stat;
	if (vfs_stat(&stream->native_file, &stat))
		return 0;

	return (stream->native_file.offset >= stat.st_size);
}

int fprintf(FILE* stream, const char* fmt, ...)
{
	printf("STUB: %s\n", __func__);
}

int vfprintf(FILE* stream, const char* fmt, va_list ap)
{
	printf("STUB: %s\n", __func__);
}

int fflush(FILE* stream) { printf("STUB: %s\n", __func__); }

size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream)
{
	if (!ptr || !size || !count || !stream)
		return 0;

	message_t msg;
	struct vfs_request* rq = (struct vfs_request*) &msg.message;

	if (stream->native_file.type == VFS_MOUNTPOINT)
		msg.signal = FS_SIGNAL_WRITE;
	else
		msg.signal = DEVICE_WRITE;

	msg.size = size * count;

	rq->offset = stream->native_file.offset;
	strcpy(rq->path, stream->native_file.path);
	send_message(&msg, stream->native_file.device);

	size_t sz = write_message_stream(ptr, msg.size, stream->native_file.device);
	stream->native_file.offset += sz;
	return sz;
}

// FIXME: Implementation!
int fputs(const char* str, FILE* stream)
{
	// printf("STUB: %s\n", __func__);
	printf("%s", str);
	return 0;
}

char* fgets(char* str, int num, FILE* stream)
{
	if (!str || !num || !stream)
		return NULL;
	for (int i = 0; i < num - 1; i++)
	{
		str[i] = fgetc(stream);
		if (str[i] == '\n')
		{
			str[i + 1] = '\0';
			return str;
		}
	}

	return str;
}

int fgetpos(FILE* stream, fpos_t* pos)
{
	if(!stream || !pos) return 1;
	
	*pos = ftell(stream);
	return 0;
}

int fsetpos(FILE* stream, fpos_t* pos)
{
	if(!stream || !pos) return 1;
	
	fseek(stream, SEEK_SET, *pos);
	return 0;
}

int fscanf(FILE* stream, const char* format, ...)
{
	printf("STUB: %s\n", __func__);
	return 0;
}

void rewind(FILE* stream)
{
	fseek(stream, 0, SEEK_SET);
}

int scanf(const char* format, ...)
{
	printf("STUB: %s\n", __func__);
	return 0;
}

int getchar()
{
	return fgetc(stdin);
}

int putc(int c, FILE* stream)
{
	return fputc(c, stream);
}

void perror(const char* str)
{
	fprintf(stderr, "%s:%s\n", strerror(errno), str);
}

int remove(const char* filename)
{
	printf("STUB: %s\n", __func__);
	return 1;
}

int rename(const char* oldname, const char* newname)
{
	printf("STUB: %s\n", __func__);
	return 1;
}

void clearerr(FILE* stream)
{
	if (stream)
		stream->error = 0;
}

FILE* tmpfile() { return fopen(tmpnam(NULL), "wb+"); }

int setvbuf(FILE* stream, char* buffer, int mode, size_t size)
{
	if (!stream)
		return 1;

	// Check if mode is valid!
	if (stream->buffer)
		free(stream->buffer);

	if (buffer)
		stream->buffer = buffer;
	else
		stream->buffer = malloc(size);

	stream->buffer_mode = mode;
	stream->buffer_size = size;
	return 0;
}

void setbuf(FILE* stream, char* buffer)
{
	setvbuf(stream, buffer, _IOFBF, BUFSIZ);
}

static size_t tmpnam_num = 0;
static char tmpnam_buf[L_tmpnam];
char* tmpnam(char* str)
{
	if (str == NULL)
	{
		snprintf(tmpnam_buf, L_tmpnam, "tmpname%d", tmpnam_num);
		return tmpnam_buf;
	}

	strncpy(tmpnam_buf, L_tmpnam, str);
	snprintf(str, L_tmpnam, "%s%d", tmpnam_buf, tmpnam_num);
	return str;
}
