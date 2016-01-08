#include <errno.h>

#define MESSAGES 4
char* messages[MESSAGES] = {
	"No error!",
	"Out of domain error!",
	"Out of range error!",
	"Illegal byte sequence!"
};

int errno = 0;
char* strerror(int errnum)
{
	if(errno > MESSAGES || errno < 0)
		return "Unknown Error!";
	
	return messages[errno];
}