#include <stdio.h>
#include <stdlib.h>

void assert_func(const char* msg)
{
	printf("%s\n\n", msg);
	exit(-1);
}
