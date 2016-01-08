#if !defined(MESSAGE_H) && !defined(__KMESSAGE_H)
#define MESSAGE_H

#include "stdint.h"
#include "stddef.h"

#define MESSAGE_ERR_SEND 1
#define MESSAGE_SENT 0
#define MESSAGE_RECEIVED 0
#define MESSAGE_ERR_RECEIVE 2
#define MESSAGE_ANY -1

#include <kernelconfig.h>

typedef struct message
{
	uint32_t sender;
	uint32_t receiver;

	uint32_t size;
	int signal;
	char message[MESSAGE_STRING_SIZE];

	struct message* next;
} message_t;

#ifdef __cplusplus
extern "C" {
#endif

int send_message(message_t* msg, uint32_t pid);
int receive_message(message_t* msg, pid_t who);
int receive_message_timeout(message_t* msg, pid_t who, uint32_t tries, uint32_t delay);

int read_message_stream(void* data, size_t size, pid_t who);
int write_message_stream(const char* data, size_t size, pid_t who);

#ifdef __cplusplus
}
#endif

#endif
