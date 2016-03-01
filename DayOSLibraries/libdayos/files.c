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
#include <stdarg.h>

#include <dayos.h>

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
	{
		errno = ENOENT;
		return NULL;
	}
	
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
	{
		errno = ENOMEM;
		return NULL;
	}
	
	f->mode = intmode;
	request->magic = VFS_MAGIC;

	// FIXME: STRNCPY!
	strcpy(request->path, filename);
	request->mode = intmode;

	msg.signal = VFS_SIGNAL_OPEN;
	send_message(&msg, pid);
	if (receive_message_timeout(&msg, pid, 100, 5) == MESSAGE_ERR_RECEIVE)
	{
		free(f);
		errno = ENOENT;
		return NULL;
	}

	if (msg.signal == SIGNAL_FAIL)
	{
		free(f);
		errno = ENOENT;
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
			errno = ENOENT;
			free(f);
			return NULL;
		}
	}

	if(intmode & VFS_MODE_RO)
	{
		vfs_stat(vfile, &f->stat);
	}

	f->ungetc_data = 0;
	f->error = 0;
	f->native_file = *vfile;
	f->native_file.offset = 0;
	
	f->buffer = NULL;
	f->buffer_index = 0;
	f->buffer_content_size = 0;

	setvbuf(f, NULL, _IOLBF, 512);
	errno = 0;
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
	 if(stream->buffer)
		free(stream->buffer);

	free(stream);
	return 0;
}

int fputc(int character, FILE* stream)
{
	if (!stream || !stream->buffer)
		return 0;
	
	switch(stream->buffer_mode)
	{
		case _IOFBF:
			stream->buffer[stream->buffer_index] = character;
			stream->buffer_content_size++;
			stream->buffer_index++;

			if(stream->buffer_index >= stream->buffer_size - 1)
			{
				if(!fflush(stream)) return character;
				return 0;
			}
			
			stream->buffer[stream->buffer_index] = 0;
			return character;
		break;
			
		case _IOLBF:
			stream->buffer[stream->buffer_index] = character;
			stream->buffer_index++;
			stream->buffer_content_size++;

			if(stream->buffer_index >= stream->buffer_size - 1 || character == '\n')
			{
				if(!fflush(stream)) return character;
				return 0;
			}
			
			stream->buffer[stream->buffer_index] = 0;
			return character;
		break;
			
		case _IONBF:
			if(fwrite(&character, 1, 1, stream))
				return character;
			
			return EOF;
	}
}

static void reverse_memory(char* begin, char* end)
{
	if(!begin || !end)
		return;
	
	if(begin > end)
	{
		char* tmp = begin;
		begin = end;
		end = tmp;
	}
	
	while(begin < end)
	{
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		
		begin++;
		end--;
	}
}

int fgetc(FILE* stream)
{
	if(!stream)
		return 0;
	
	int character = EOF;
	switch(stream->buffer_mode)
	{
		case _IOLBF:
		case _IOFBF:
			// Flush!
			if(stream->buffer_content_size == 0)
			{
				stream->buffer_content_size = fread(stream->buffer, stream->buffer_size-1, 1, stream);
				stream->buffer_index = stream->buffer_content_size - 1;
				reverse_memory(stream->buffer, stream->buffer + stream->buffer_index);
			}
			
			//debug_printf("Got line: cs = %d idx = %d %s\n", stream->buffer_content_size, stream->buffer_index, stream->buffer);
			//debug_printf("stream->buffer[%d] == %c\n", stream->buffer_index, stream->buffer[stream->buffer_index]);

			if(stream->buffer_content_size > 0)
			{
				character = stream->buffer[stream->buffer_index];
				stream->buffer[stream->buffer_index--] = 0;
				stream->buffer_content_size--;
			}
			
			return character;
		
		case _IONBF:
			if(fread(&character, 1, 1, stream))
				return character;
			
			return EOF;
	}
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
	struct vfs_request* rq = (struct vfs_request*) &msg.message;

	if (stream->native_file.type == VFS_MOUNTPOINT)
		msg.signal = FS_SIGNAL_READ;
	else
		msg.signal = DEVICE_READ;

	msg.size = size * nmemb;

	rq->param = stream->buffer_mode;
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
		return 1;

	return (stream->native_file.offset >= stream->stat.st_size);
}

int fprintf(FILE* stream, const char* fmt, ...)
{
	va_list ap;
	int ret = 0;
	va_start(ap, fmt);
	ret = vfprintf(stream, fmt, ap);
	va_end(ap);
	return ret;
}

static int fputn(unsigned int x, int base, FILE* stream)
{
	char buf[65];
	const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* p;

	if(base > 36)
	{
		return 0;
	}

	memset(buf, 0, 64);

	p = buf + 64;
	*p = '\0';
	do
	{
		*--p = digits[x % base];
		x /= base;
	} while(x);
		
	return fputs(p, stream);
}

int vfprintf(FILE* stream, const char* fmt, va_list ap)
{
	if(!stream || !fmt)
		return 0;
	
	const char* s;
	unsigned long n;
	unsigned int ret = 0;

	while (*fmt) 
	{
		if (*fmt == '%') 
		{
			fmt++;
			switch (*fmt) 
			{
				case 's':
					s = va_arg(ap, const char*);
					ret += fputs(s, stream);
					break;
				case 'c':
					n = va_arg(ap, int);
					fputc(n, stream);
					ret++;
					break;
				case 'd':
				case 'u':
					n = va_arg(ap, unsigned long int);
					ret += fputn(n, 10, stream);
					break;
				case 'x':
				case 'p':
					n = va_arg(ap, unsigned long int);
					ret += fputn(n, 16, stream);
					break;
				case 'l':
					switch(fmt[1])
					{
						case 'd':
							fmt++;
							n = va_arg(ap, long int);
							ret += fputn(n, 10, stream);
							break;
					}
					break;
				case '%':
					fputc('%', stream);
					ret++;
					break;
				case '\0':
					goto out;
				default:
					fputc('%', stream);
					fputc(*fmt, stream);
					ret += 2;
					break;
			}
		} 
		else 
		{
			fputc(*fmt, stream);
			ret++;
		}
		fmt++;
	}

out:
	va_end(ap);
	return ret;
}

void putch(int c)
{
	fputc(c, stdout);
}

int putchar(int c)
{
	return fputc(c, stdout);
}

int puts(const char* str)
{
	if(fputs(str, stdout) == EOF) return EOF;
	if(fputc('\n', stdout) == EOF) return EOF;
	return 1;
}

int printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int ret = vprintf(fmt, ap);
	va_end(ap);
	return ret;
}

int vprintf(const char* fmt, va_list ap)
{
	return vfprintf(stdout, fmt, ap);
}

int fflush(FILE* stream) 
{
	if(!stream) return EOF;
	
	int result = 0;
	if(stream->mode == VFS_MODE_WO)
	{
		if(fwrite(stream->buffer, stream->buffer_index, 1, stream) != stream->buffer_index)
		{
			stream->buffer_index = 0;
			stream->buffer_empty = 1;
			return EOF;
		}
	}

	stream->buffer[0] = 0;
	stream->buffer_index = 0;
	stream->buffer_empty = 1;
	return 0;
}

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

int fputs(const char* str, FILE* stream)
{
	if(!str || !stream)
		return 0;

	while(*str)
	{
		if(fputc(*str++, stream) == EOF) return EOF;
	}
	
	return 0;
}

char* fgets(char* str, int num, FILE* stream)
{
	if (!str || !num || !stream)
		return NULL;
	
	for(int i = 0; i < num - 1; i++)
	{
		if ((str[i] = fgetc(stream)) == '\n'
			|| str[i] == EOF)
		{
			str[i+1] = 0;
			return str;
		}
	}

	return str;
}

char* gets(char* str)
{
	if (!str || !stdin)
		return NULL;

	char* iter = str;
	while((*iter++ = fgetc(stdin)) != '\n');
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
	if(errno)
		fprintf(stderr, "%s: %s\n", str, strerror(errno));
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
	stream->buffer_index = 0;
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

	strncpy(tmpnam_buf, str, L_tmpnam);
	snprintf(str, L_tmpnam, "%s%d", tmpnam_buf, tmpnam_num);
	return str;
}
