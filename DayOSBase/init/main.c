#include <stdio.h>
#include <string.h>
#include <dayos.h>
#include <stdlib.h>

#define LOG(msg) printf("[ INIT ] %s\n", msg)

void execute_program(const char* path)
{
	FILE* exec = fopen(path, "r");
	
	if(!exec)
	{
		LOG("Could not open executable!");
		return;
	}
	
	char* content;
	fseek(exec, 0, SEEK_END);
	size_t sz = ftell(exec);
	fseek(exec, 0, SEEK_SET);

	content = (char*) malloc(sz);
	fread(content, sz, 1, exec);
	
	syscall1(9, content);
	
	fclose(exec);
	free(content);
}

void execute_config(const char* path)
{
	FILE* config = fopen(path, "r");
	
	if(!config)
	{
		LOG("Could not open config file!");
		while(1) sleep(1000);
	}
	
	char* content;
	fseek(config, 0, SEEK_END);
	size_t sz = ftell(config);
	fseek(config, 0, SEEK_SET);

	content = (char*) malloc(sz+1);
	fread(content, sz, 1, config);
	
	char* p = strtok(content, "\n");
	while(p != NULL)
	{
		
		if(!strcmp(p, "delay"))
		{
			sleep(250);
		}
		else if(strcmp(p, ""))
		{
			LOG(p);
			execute_program(p);
		}
		
		p = strtok(NULL, "\n");
	}
	
	fclose(config);
	free(content);
}

void init_routine()
{
	//sleep(10);
	
	pid_t p = get_service_pid("vfs");
	printf("pid == %d\n", p);

	
	//execute_config("/drives/roramdisk/init.cfg");
	//execute_program("/drives/ramdisk/system/tty.drv");
}

typedef struct service
{
	uint32_t pid;
	char name[255];

	struct service* next;
}service_t;

service_t* service_start = NULL;

void print_services()
{
	service_t* current = service_start;
	while(current) 
	{
		printf("Service: %s %d\n", current->name, current->pid);
		current = current->next;
	}
}

int main()
{
	LOG("Starting INIT system.");
	pid_t pid = 0;

	//sleep(150);
	
	// Wait for VFS to crop up
	while((pid = get_service_pid("vfs")) == 0) sleep(50);
	
	//FILE* config = fopen(");
	
	//sleep(150);
	
	execute_config("/drives/roramdisk/init.cfg");
	execute_program("/drives/ramdisk/system/tty.drv");
	
	message_t msg;
	while(1)
	{
		while(receive_message(&msg, MESSAGE_ANY) != MESSAGE_RECEIVED) sleep(10);
		
		switch(msg.signal)
		{
			// Register service
		case SERVICE_REGISTER: {
				service_t* new_service = malloc(sizeof(service_t));
				new_service->pid = msg.sender;
				strcpy(new_service->name, msg.message);
				
				new_service->next = service_start;
				service_start = new_service;
				
				printf("[ INIT ] Registering service '%s' for %d\n", msg.message, msg.sender);
				
				// FIXME: Check rights and stuff!
				msg.signal = SIGNAL_OK;
				send_message(&msg, msg.sender);
				
				print_services();
				if(!strcmp(msg.message, "vfs"))
					init_routine();
			}
		break;
		
		// Get service PID
		case SERVICE_REQUEST: {
				printf("[ INIT ] Sending service info for service '%s' to %d\n", msg.message, msg.sender);

				service_t* service = service_start;
				while(service != NULL)
				{
					if(!strcmp(service->name, msg.message))
					{
						break;
					}
					service = service->next;
				}
				
				if(service != NULL)
				{
					printf("[ INIT ] Found service with pid %d\n", service->pid);
					
					msg.signal = service->pid;
					send_message(&msg, msg.sender);
				}
				else
				{
					msg.signal = 0;
					send_message(&msg, msg.sender);
				}
			}
			
		break;
		
		// Remove service
		case 3:
			LOG("Remove service is not yet implemented!");
		break;
		
		default:
			printf("[ INIT ] Unknown signal 0x%x!", msg.signal);
		}
	}

	for(;;);
}

extern void setup_stack_chk();
extern void InitHeap();

// TODO: Parameteruebergabe!
void _start()
{
	setup_stack_chk();
	InitHeap();
	
	int retval = 0;
	retval = main(0, NULL);
	exit(retval);
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
