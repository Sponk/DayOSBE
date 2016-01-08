#include <service.h>
#include <message.h>
#include <string.h>
#include <sleep.h>

int register_service(const char* name)
{
	message_t msg;
	msg.signal = SERVICE_REGISTER;
	strcpy(msg.message, name);

	send_message(&msg, 0);
	while (receive_message(&msg, 0) != MESSAGE_RECEIVED)
		sleep(1);
	return msg.signal;
}

/**
 * Holt die PID eines angemeldeten Prozesses
 * @param name Der Name des Services
 * @return Die PID des Services oder 0 wenn kein Service vorhanden
 */
pid_t get_service_pid(const char* name)
{
	message_t msg;

	msg.signal = SERVICE_REQUEST;
	strcpy(msg.message, name);

	send_message(&msg, 0);

	if(receive_message_timeout(&msg, 0, 10, 3) != MESSAGE_RECEIVED)
		return 0;
	
	return msg.signal;
}
