#include <sys/utsname.h>
#include <syscall.h>
#include <string.h>

int uname(struct utsname* name)
{
	if(!name)
		return -1;
	
	return syscall1(10, (uintptr_t) name);
}