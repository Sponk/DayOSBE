#include <dlfcn.h>

void* dlopen(const char *path, int mode)
{
	return 0;
}

const char* dlerror(void)
{
	return "";
}

int dlclose(void* handle)
{
	return 0;
}

int dladdr(const void* dl_restrict, Dl_info* dl_info)
{
	return 0;
}