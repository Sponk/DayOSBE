#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dayos.h>
#include <driver.h>
#include <memory.h>
#include <sys/ioctl.h>
#include "framebuffer.h"

#define BUFFER_SIZE 512
#define TRUE 1
#define FALSE 0

#define MIN(x, y) (x < y ? x : y)

unsigned char kbdgerman[128] = {
	'0',  '0', '1', '2', '3',  '4',  '5', '6', '7',  '8',
	'9',  '0', '-', '=', '\b', '\t',					  /* Tab */
	'q',  'w', 'e', 'r',								  /* 19 */
	't',  'z', 'u', 'i', 'o',  'p',  '[', ']', '\n',	  /* Enter key */
	'0',												  /* 29   - Control */
	'a',  's', 'd', 'f', 'g',  'h',  'j', 'k', 'l',  ';', /* 39 */
	'\'', '`', '0',										  /* Left shift */
	'\\', 'y', 'x', 'c', 'v',  'b',  'n',				  /* 49 */
	'm',  ',', '.', '-', '0',							  /* Right shift */
	'*',  '0',											  /* Alt */
	' ',												  /* Space bar */
	'0',												  /* Caps lock */
	'0',											/* 59 - F1 key ... > */
	'0',  '0', '0', '0', '0',  '0',  '0', '0', '0', /* < ... F10 */
	'0',											/* 69 - Num lock*/
	'0',											/* Scroll Lock */
	'0',											/* Home key */
	'0',											/* Up Arrow */
	'0',											/* Page Up */
	'-',  '0',										/* Left Arrow */
	'0',  '0',										/* Right Arrow */
	'+',  '0',										/* 79 - End key*/
	'0',											/* Down Arrow */
	'0',											/* Page Down */
	'0',											/* Insert Key */
	'0',											/* Delete Key */
	'0',  '0', '0', '0',							/* F11 Key */
	'0',											/* F12 Key */
	'0',											/*undefined */
};

unsigned char kbdgermanshift[128] = {
	'0',  '0', '!', '"', '0',  '$',  '%', '&', '/',  '(',
	')',  '=', '?', '=', '\b', '\t',					  /* Tab */
	'Q',  'W', 'E', 'R',								  /* 19 */
	'T',  'Z', 'U', 'I', 'O',  'P',  '[', ']', '\n',	  /* Enter key */
	'0',												  /* 29   - Control */
	'A',  'S', 'D', 'F', 'G',  'H',  'J', 'K', 'L',  ';', /* 39 */
	'\'', '`', '0',										  /* Left shift */
	'\\', 'Y', 'X', 'C', 'V',  'B',  'N',				  /* 49 */
	'M',  ';', ':', '_', '0',							  /* Right shift */
	'*',  '0',											  /* Alt */
	' ',												  /* Space bar */
	'0',												  /* Caps lock */
	'0',											/* 59 - F1 key ... > */
	'0',  '0', '0', '0', '0',  '0',  '0', '0', '0', /* < ... F10 */
	'0',											/* 69 - Num lock*/
	'0',											/* Scroll Lock */
	'0',											/* Home key */
	'0',											/* Up Arrow */
	'0',											/* Page Up */
	'-',  '0',										/* Left Arrow */
	'0',  '0',										/* Right Arrow */
	'+',  '0',										/* 79 - End key*/
	'0',											/* Down Arrow */
	'0',											/* Page Down */
	'0',											/* Insert Key */
	'0',											/* Delete Key */
	'0',  '0', '0', '0',							/* F11 Key */
	'0',											/* F12 Key */
	'0',											/*undefined */
};

void outb(unsigned short port, unsigned char value)
{
	asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

/* Liest einen byte aus einem Port */

unsigned char inb(unsigned short port)
{
	unsigned char ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
	return ret;
}

void SendKBCCommand(uint8_t cmd)
{
	while ((inb(0x64) & 0x2))
		;

	outb(0x60, cmd);
}

void EmptyKBCBuffer()
{
	// Tastaturpuffer leeren
	while (inb(0x64) & 0x1)
	{
		inb(0x60);
	}
}

void GetKeyboardInfo()
{
	EmptyKBCBuffer();
	SendKBCCommand(0xF2);

	uint8_t c = inb(0x60);

	if(c == 0xFA)
		debug_printf("[ TTY ] You have an AT keyboard (0x%x).\n", c);
	else
		debug_printf("[ TTY ] You have an unknown keyboard (0x%x).\n", c);
}

char* buffer;
uint32_t len = 0;

void UpdateBuffer(char c, Framebuffer& fb)
{

	// if(c == '\b')
	//{
	// putch('\b');//printf("BACK\n");
	//}

	if (c == '\b' && len > 0)
	{
		len--;
	}

	if (len < BUFFER_SIZE && c != '\b')
	{
		buffer[len] = c;
		len++;
	}

	if (len > 0)
		fb.putch(c);
	
	buffer[len] = 0;
}

void moveBufferLeft(char* s, size_t amount = 1)
{
	for (int i = 0; i < len - amount; i++)
	{
		buffer[i] = buffer[i + amount];
	}

	len -= amount;
	buffer[len] = 0;
}

int main()
{
	pid_t read_request = 0;
	message_t msg;
	buffer = (char*)malloc(BUFFER_SIZE);

	sleep(100);

	int retval = vfs_create_device("/dayos/dev/tty", VFS_MODE_RW, VFS_CHARACTER_DEVICE);
	if (retval == SIGNAL_FAIL)
	{
		debug_printf("[ TTY ] Could not create device file!\n");
		while (1)
			;
		return -1;
	}

	registerHandlerProcess(0x21);

	GetKeyboardInfo();
	EmptyKBCBuffer();
	SendKBCCommand(0xF4);

	uint8_t shifted;
	char lastChar = 0;
	
	request_mem_region("VIDMEM", 0xB8000);
	Framebuffer fb;
	
	day_buffer_t* input = construct_day_buffer(512, 0, FLUSH_FULL);
	
	struct vfs_request* rq = (struct vfs_request*) &msg.message;
	struct vfs_request current_request;
	while (1)
	{
		msg.signal = 0;
		while (receive_message(&msg, MESSAGE_ANY) != MESSAGE_RECEIVED);

		switch (msg.signal)
		{
			case 0x21:
			{
				uint8_t scancode;
				scancode = inb(0x60);

				if (scancode & 0x80)
				{
					// Release Event

					switch (scancode)
					{
						// L-Shift
						case 0xaa:
						case 0xb6:
							shifted = FALSE;
							break;
					}
				}
				else
				{
					// Press Event
					switch (scancode)
					{
						// L-Shift
						case 0x2a:
						case 0x36:
							shifted = TRUE;
							break;

						default:
							if (!shifted)
								lastChar = kbdgerman[scancode];
							else
								lastChar = kbdgermanshift[scancode];

							if(lastChar == '\b')
							{
								if(input->content_size > 0)
								{
									input->memory[input->cursor] = 0;
									
									input->cursor--;
									input->content_size--;
								}
							}
							else
								day_buffer_putchar(input, lastChar);
							
							fb.putch(lastChar);
							//UpdateBuffer(lastChar, fb);

							if (read_request)
							{
								switch(current_request.param)
								{
									case _IOFBF:
										if(input->content_size >= current_request.size)
										{
											write_message_stream(input->memory, current_request.size, read_request);
											input->cursor -= current_request.size;
											input->content_size -= current_request.size;
											//moveBufferLeft(buffer, current_request.size);
											read_request = 0;
										}
									break;
									
									case _IOLBF:
									{
										if(lastChar == '\n' || input->content_size >= current_request.size)
										{
											size_t sz = MIN(input->content_size, current_request.size);
											size_t sent = write_message_stream(input->memory, sz, read_request);
											
											//debug_printf("contentsize: %d reqsize: %d\n", input->content_size, current_request.size);
											//debug_printf("Sending: sz %d sent %d %s\n", sz, sent, input->memory);
											
											// Tell the client that the stream is over regardless of its expectations
											// regarding size
											msg.signal = SIGNAL_FAIL;
											send_message(&msg, read_request);
											
											input->cursor -= sz;
											input->content_size -= sz;
											input->memory[0] = 0;
											
											read_request = 0;
										}
									}
									break;
								}
							}
					}
				}
			}
			break;

			case DEVICE_READ:
				
				if (read_request != 0 && msg.sender != read_request)
				{
					msg.signal = SIGNAL_FAIL;
					send_message(&msg, msg.sender);
					break;
				}

				/*moveBufferLeft(buffer);
				msg.signal = SIGNAL_OK;
				send_message(&msg, msg.sender);*/
				
				switch(rq->param)
				{
					case _IOFBF:
						if(input->content_size <= rq->size)
						{
							read_request = msg.sender;
							current_request = *rq;
							current_request.size = msg.size;
							break;
						}
						else
						{
							write_message_stream(input->memory, rq->size, msg.sender);
							//moveBufferLeft(buffer, rq->size);
							input->cursor -= msg.size;
						}
					break;
					
					case _IOLBF:
					{
						char* newline = strchr(input->memory, '\n');
						if(newline == NULL)
						{
							read_request = msg.sender;
							current_request = *rq;
							current_request.size = msg.size;
						}
						else
						{
							size_t size = MIN(newline - input->memory, msg.size);
							write_message_stream(input->memory, size, msg.sender);
							
							// Tell the client that the stream is over regardless of its expectations
							// regarding size
							msg.signal = SIGNAL_FAIL;
							send_message(&msg, read_request);
							
							// moveBufferLeft(buffer, size);
							input->cursor -= size;
							input->content_size -= size;
						}
					}
					break;
				}
				
				break;

			case DEVICE_WRITE: {
				
				char* data = (char*) malloc(msg.size + 1);
				read_message_stream(data, msg.size, msg.sender);
				
				data[msg.size] = 0;
				fb << data;

				free(data);
			}
			break;

		    case DEVICE_IOCTL: {
				pid_t who = msg.sender;
				int what = msg.size;
				char** argv = ioctl_handle(who);

				debug_printf("[ TTY ] Received an IOCTL command 0x%x\n", what);
				ioctl_free(argv);

				msg.signal = 0;
				send_message(&msg, who);
			}
			break;
		}
	}

	for (;;);
}
