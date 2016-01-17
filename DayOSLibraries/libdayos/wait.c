#include <sys/wait.h>
#include <syscall.h>
#include <dayos.h>

pid_t wait(int* status)
{
	
}

// FIXME: Handle options!
pid_t waitpid(pid_t pid, int* status, int options)
{
	if(options != 0)
		debug_printf("%s : %d : Options are not yet implemented!\n", __FILE__, __LINE__);
	
	return syscall1(14, pid);
}

/*int waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options)
{
	
}*/