#include <memory.h>
#include <syscall.h>

void request_mem_region(const char* name, uintptr_t addr)
{
	syscall2(13, (uintptr_t) name, addr);
}