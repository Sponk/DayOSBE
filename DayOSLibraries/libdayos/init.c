#include <dayos.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <string.h>

extern void InitHeap();
extern void init_signals();

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

static void send_args(const char* path, int argc, char* argv[], pid_t pid)
{
	message_t msg;
	msg.signal = SIGNAL_OK;
	msg.size = argc + 1;
	send_message(&msg, pid);
	
	strcpy(msg.message, path);
	send_message(&msg, pid);
	
	if(!argv)
		return;
	
	for(int i = 0; i < argc; i++)
	{
		if(argv[i])
		{
			strcpy(msg.message, argv[i]);
			send_message(&msg, pid);
		}
	}
}

#define RECEIVE(msg, pid) while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);
static char** receive_args(int* argc)
{
	if(!argc)
		return NULL;
	
	message_t msg;
	if (receive_message_timeout(&msg, MESSAGE_ANY, 10, 1) == MESSAGE_ERR_RECEIVE)
		return NULL;
	
	*argc = msg.size;
	char** argv = malloc(sizeof(char*) * msg.size);
	
	for(int i = 0; i < msg.size; i++)
	{
		RECEIVE(msg, MESSAGE_ANY);
		argv[i] = strdup(msg.message);
	}
	
	return argv;
}

int execute_program(const char* path, int argc, char* argv[])
{
	FILE* exec = fopen(path, "r");
	
	if(!exec)
	{
		perror("Could not open executable");
		// printf("Could not find program %s!\n", path);
		return 1;
	}
	
	char* content;
	fseek(exec, 0, SEEK_END);
	size_t sz = ftell(exec);
	fseek(exec, 0, SEEK_SET);

	content = (char*) malloc(sz);
	fread(content, sz, 1, exec);
	
	pid_t pid = syscall1(9, (uintptr_t) content);
	
	fclose(exec);
	free(content);
	
	send_args(path, argc, argv, pid);
	
	return pid;
}

char** init_libdayos(int* argc)
{
	setup_stack_chk();
	InitHeap();
	init_signals();

	char** argv = NULL;
	pid_t vfs_service = get_service_pid("vfs");
	
	// FIXME: Get from kernel somehow!
	if(vfs_service)
	{
		argv = receive_args(argc);

		stdin = fopen("/dayos/dev/tty", "r");
		stdout = fopen("/dayos/dev/tty", "w");
		stderr = fopen("/dayos/dev/tty", "w");
	}
	else
		debug_printf("No VFS available!\n");
	
	return argv;
}