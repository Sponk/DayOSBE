#include <stdlib.h>
#include <stdio.h>
#include <dayos.h>

#include "../cpp_crt.c"

extern int main(int argc, char* argv[]);
extern void setup_stack_chk();
extern void InitHeap();

FILE* stdin;
FILE* stdout;
FILE* stderr;

// TODO: Parameteruebergabe!
// TODO: libdayos Initialisierung  (Heap etc.)
void _start()
{
	setup_stack_chk();
	InitHeap();
	
	run_constructors();
	int retval = main(0, NULL);
	run_destructors();
	
	exit(retval);
}
