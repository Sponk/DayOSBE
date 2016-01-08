#include <stdlib.h>

void exit(int status)
{
	asm("int $0x30" : : "a" (2), "b"(status));
	for(;;);
}

void abort()
{
	exit(-1);
}