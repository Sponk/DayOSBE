#include <sleep.h>
#include <syscall.h>

void sleep(unsigned int time)
{
	syscall1(8, time);
}