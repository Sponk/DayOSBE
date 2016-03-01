#include <cstdio>
#include <dayos.h>
#include <vector>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <cstdlib>
#include <cstring>

void handle_command(char* cmd, std::vector<char*>* args)
{
	char program[512];
	snprintf(program, sizeof(program), "%s/%s", "/drives/roramdisk", cmd);
	pid_t pid;

	if(args->size() > 0)
	{
		pid = execute_program(program, args->size(), &(*args)[0]);
	}	
	else
	{
		pid = execute_program(program, 0, NULL);
	}

	if(pid)
		waitpid(pid, NULL, 0);
	else
		std::cerr << "Could not execute command '" << cmd << "': " << strerror(errno) << std::endl;

	for(int i = 0; i < args->size(); i++)
		free((*args)[i]);

	free(cmd);
	delete args;
}

int lalamain(int argc, char* argv[])
{
	while(!feof(stdin))
	{
		debug_printf("ITERATioN!!!\n");
		putchar(fgetc(stdin));
		fflush(stdout);	
	}

	debug_printf("LALALA_DAADADA\n");
}

