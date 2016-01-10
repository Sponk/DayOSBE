#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>

typedef void (*sig_func)(int);

#define SIGNAL_TABLE_SIZE 24
static sig_func signal_table[SIGNAL_TABLE_SIZE];

static const char* sig_to_name(int sig)
{
	switch(sig)
	{
		case SIGSEGV: return "SIGSEGV";		
		case SIGINT: return "SIGINT";
		case SIGILL: return "SIGILL";
		case SIGFPE: return "SIGFPE";
		case SIGTERM: return "SIGTERM";
		case SIGBREAK: return "SIGBREAK";
		case SIGABRT: return "SIGABRT";
		default: return "Unknown";
	};
}

void sig_term(int val)
{
	exit(val);
}

void sig_dfl(int val)
{
	printf("Received signal %d (%s) and will terminate!\n", val, sig_to_name(val));
	exit(val);
}

#define DEFAULT_TABLE_SIZE 1
static sig_func default_table[] = {
	sig_term
};

void (*signal(int sig, void (*func)(int)))(int)
{
	if(sig >= SIGNAL_TABLE_SIZE || sig < 0)
	{
		errno = EINVAL;
		return (sig_func) SIG_ERR;
	}
	
	uintptr_t funcptr = (uintptr_t) func;
	if(funcptr == SIG_DFL)
	{
		if(sig < DEFAULT_TABLE_SIZE)
			signal_table[sig] = default_table[sig];
		else
			signal_table[sig] = sig_dfl;
	}
	else if(funcptr == SIG_IGN)
	{
		signal_table[sig] = NULL;
	}
	else
	{
		signal_table[sig] = func;
	}
	
	return signal_table[sig];
}

int raise(int sig)
{
	return syscall2(12, sig, -1);
}


void c_os_signal_handler(int signal)
{
	if(signal < SIGNAL_TABLE_SIZE &&
		signal >= 0 &&
		signal_table[signal])
	{
		signal_table[signal](signal);
	}
	else
		exit(-1);
}

extern void os_signal_handler();
void init_signals()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGILL, SIG_DFL);
	signal(SIGFPE, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGBREAK, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	
	syscall1(11, (uintptr_t) os_signal_handler);
}