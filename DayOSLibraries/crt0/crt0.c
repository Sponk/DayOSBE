#include <stdlib.h>
#include <stdio.h>
#include <dayos.h>

extern int main(int argc, char* argv[]);
extern void setup_stack_chk();
extern void init_libdayos();
extern void run_constructors();
extern void run_destructors();

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

extern void _init();

// TODO: Parameteruebergabe!
void _start()
{
	setup_stack_chk();
	init_libdayos();
	
	//printf("CTORS: 0x%x\n", __CTOR_LIST__);
	
	_init();
		
	pid_t vfs_service = get_service_pid("vfs");
	// FIXME: Get from kernel somehow!
	if(vfs_service)
	{
		stdin = fopen("/dayos/dev/tty", "r");
		stdout = fopen("/dayos/dev/tty", "w");
		stderr = fopen("/dayos/dev/tty", "w");
	}
	else
		printf("No VFS available!\n\n");
	
	int retval = 0;
//	run_constructors();
	retval = main(0, NULL);
//	run_destructors();
	
	exit(retval);
}

void print_stuff()
{
	debug_printf("THIS IS DEBUG STUFF\n");
}

void* __stack_chk_guard = NULL;

void setup_stack_chk()
{
	//uint32_t* p;
	//p = (uint32_t*) &__stack_chk_guard;
 
	//*p =  0x00000aff;
}
 
void __attribute__((noreturn)) __stack_chk_fail()
{ 
	printf("Stack overflow/corruption detected!");
	
	//asm("int $0x1");
	exit(-1);
}
