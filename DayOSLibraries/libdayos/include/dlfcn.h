#ifndef __DLFCN_H
#define __DLFCN_H

#define RTLD_LAZY 0x1
#define RTLD_NOW 0x2
#define RTLD_LOCAL 0x4
#define RTLD_GLOBAL 0x8
#define RTLD_NOLOAD 0x10
#define RTLD_NODELETE 0x80

#define RTLD_NEXT ((void *) -1)
#define RTLD_DEFAULT ((void *) -2)

typedef struct dl_info
{
	const char* dli_fname;
	void* dli_fbase;
	const char* dli_sname;
	void* dli_saddr;
} Dl_info;

#ifdef __cplusplus
extern "C" {
#endif

void* dlopen(const char *path, int mode);
const char* dlerror(void);
int dlclose(void* handle);
int dladdr(const void* dl_restrict, Dl_info* dl_info);

#ifdef __cplusplus
}
#endif
	
#endif