#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <vfs.h>
#include <sys/stat.h>

typedef struct
{
	struct vfs_file native_file;
	struct stat stat;
	uint32_t error;
	int ungetc_data;
	
	uint32_t mode;
	uint32_t buffer_mode;
	size_t buffer_size;
	size_t buffer_index;
	char* buffer;
}FILE;

typedef unsigned long fpos_t;

#ifdef __cplusplus
extern "C" {
#endif

int vprintf(const char* fmt, va_list ap);
int printf(const char* fmt, ...);
void putch(int c);
int putchar(int character);

int fileno(FILE* stream);
FILE* fdopen(int fd, const char* mode);
FILE* freopen(const char* filename, const char* mode, FILE* stream);
FILE* fopen(const char* filename, const char* mode);
int fclose(FILE* stream);
int ferror(FILE* stream);
int ungetc(int character, FILE* stream);

int fputc(int character, FILE* stream);
int fgetc(FILE* stream);
int getc(FILE* stream);

int vfprintf(FILE* stream, const char* fmt, va_list ap);
int fprintf(FILE* stream, const char* fmt, ...);
int feof(FILE* stream);

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);

int fseek(FILE* stream, long int offset, int origin);
size_t ftell(FILE* stream);
int fgetpos(FILE* stream, fpos_t* pos);
int fsetpos(FILE* stream, fpos_t* pos);

int fscanf(FILE* stream, const char* format, ...);
int fflush(FILE* stream);

char* tmpnam(char* str);
#define L_tmpnam 32

FILE* tmpfile();
void clearerr(FILE* stream);
int setvbuf(FILE* stream, char* buffer, int mode, size_t size);
void setbuf(FILE* stream, char* buffer);

void srand(unsigned int seed);
int fputs(const char* str, FILE* stream);
char* fgets(char* str, int num, FILE* stream);

int remove(const char* filename);
int rename(const char* oldname, const char* newname);

void rewind(FILE* stream);

int scanf(const char* format, ...);
int puts(const char* str);
int putc(int c, FILE* stream);
int getchar();
void perror(const char* str);

int sprintf(char* dest, const char* fmt, ...);
int snprintf(char* dest, size_t size, const char* fmt, ...);
int vsnprintf(char* dest, size_t size, const char* fmt, va_list ap);
int vsprintf(char* dest, const char* fmt, va_list ap);

int asprintf(char** str, const char* fmt, ...);
int vasprintf(char** str, const char* fmt, va_list ap);
int sscanf(const char* str, const char* format, ...);

#ifdef __cplusplus
}
#endif

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define BUFSIZ MESSAGE_STRING_SIZE
#define EOF (-1)

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define BUFSIZ MESSAGE_STRING_SIZE

#endif
