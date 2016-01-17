#include <unistd.h>
#include <stdarg.h>
#include <dayos.h>
#include <driver.h>
#include <string.h>
#include <stdlib.h>

// In fcntl.c
extern FILE* fd2file(int fd);

int ioctl(int d, int request, ...)
{
	message_t msg;
	FILE* f = fd2file(d);

	if(!f) return -1;

	pid_t pid = f->native_file.device;
	int num = 0;
	va_list ap;
	va_start(ap, request);

	// Get number of args
	num = va_arg(ap, int);

	// Send ioctl command
	msg.signal = DEVICE_IOCTL;
	msg.size = request;
	send_message(&msg, pid);

	// Send number of arguments
	msg.signal = SIGNAL_OK;
	msg.size = num;
	send_message(&msg, pid);

	// Send args themselves
	for(int i = 0; i < num; i++)
	{
		strcpy(msg.message, va_arg(ap, const char*));
		send_message(&msg, pid);
	}

	// End transmission
	if(num)
	{
		msg.size = 0;
		send_message(&msg, pid);
	}

	va_end(ap);

	if(receive_message_timeout(&msg, pid, 10, 3) != MESSAGE_RECEIVED) return -1;
	return msg.signal;
}

char** ioctl_handle(pid_t who)
{
	message_t msg;
	if(receive_message_timeout(&msg, who, 10, 3) != MESSAGE_RECEIVED)
		return NULL;

	if(msg.size == 0)
		return NULL;

	int num = msg.size;
	char** argv = malloc((msg.size + 1) * sizeof(char*));
	for(int i = 0; i < num; i++)
	{
		// FIXME: Error handling!
		if(receive_message_timeout(&msg, who, 10, 3) != MESSAGE_RECEIVED)
			return argv;
		
		argv[i] = strdup(msg.message);
	}

	argv[num] = NULL;
	return argv;
}

void ioctl_free(char** argv)
{
	if(!argv)
		return;

	char** iter = argv;
	while(*iter++)
		free(*iter);

	free(argv);
}
