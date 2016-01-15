#include <iostream>
#include <stdio.h>
#include <dayos.h>
#include <string.h>
#include "tinytest.h"

using namespace std;

void test_buffer_creation()
{
	day_buffer_t* buffer = construct_day_buffer(0, NULL, FLUSH_LINE);
	ASSERT_EQUALS(buffer, NULL);
	
	buffer = construct_day_buffer(12, NULL, FLUSH_LINE);
	ASSERT_NOT_EQUALS(buffer, NULL);
	ASSERT_EQUALS(buffer->size, 12);
	
	destroy_day_buffer(buffer);
}

void test_buffer_putchar()
{
	day_buffer_t* buffer = construct_day_buffer(12, NULL, FLUSH_LINE);
	ASSERT_NOT_EQUALS(buffer, NULL);
	
	memset(buffer->memory, 12, 0xDE);
	
	day_buffer_putchar(buffer, 'H');
	day_buffer_putchar(buffer, 'e');
	day_buffer_putchar(buffer, 'l');
	day_buffer_putchar(buffer, 'l');
	day_buffer_putchar(buffer, 'o');
	day_buffer_putchar(buffer, '!');
	
	ASSERT_STRING_EQUALS("Hello!", buffer->memory);
	ASSERT_EQUALS(strlen(buffer->memory), buffer->content_size);
	
	destroy_day_buffer(buffer);
}

static int flag = 0;
static void flush(day_buffer_t* buffer)
{
	flag = 1;
}

void test_buffer_flush_line()
{
	flag = 0;
	day_buffer_t* buffer = construct_day_buffer(12, flush, FLUSH_LINE);
	ASSERT_NOT_EQUALS(buffer, NULL);
	
	memset(buffer->memory, 12, 0xDE);
	
	day_buffer_putchar(buffer, 'H');
	day_buffer_putchar(buffer, 'e');
	day_buffer_putchar(buffer, 'l');
	day_buffer_putchar(buffer, 'l');
	day_buffer_putchar(buffer, 'o');
	day_buffer_putchar(buffer, '!');
	day_buffer_putchar(buffer, '\n');
	
	ASSERT_EQUALS(strlen(buffer->memory), 0);
	ASSERT_EQUALS(0, buffer->content_size);
	ASSERT("Flush callback was called", flag);
	
	destroy_day_buffer(buffer);
}

void test_buffer_flush_full()
{
	flag = 0;
	day_buffer_t* buffer = construct_day_buffer(4, flush, FLUSH_FULL);
	ASSERT_NOT_EQUALS(buffer, NULL);
	
	memset(buffer->memory, 4, 0xDE);
	
	day_buffer_putchar(buffer, 'H');
	day_buffer_putchar(buffer, 'e');
	day_buffer_putchar(buffer, 'l');
	day_buffer_putchar(buffer, 'l');
	day_buffer_putchar(buffer, 'o');
	day_buffer_putchar(buffer, '!');
	day_buffer_putchar(buffer, '\n');
	
	ASSERT_EQUALS(3, strlen(buffer->memory));
	ASSERT_EQUALS(3, buffer->content_size);
	ASSERT("Flush callback was called", flag);
	
	destroy_day_buffer(buffer);
}

void test_buffer_getchar()
{
	flag = 0;
	day_buffer_t* buffer = construct_day_buffer(4, flush, FLUSH_FULL);
	ASSERT_NOT_EQUALS(buffer, NULL);
	
	memset(buffer->memory, 4, 0xDE);
	
	day_buffer_putchar(buffer, 'H');
	ASSERT_EQUALS('H', day_buffer_getchar(buffer));
	
	destroy_day_buffer(buffer);
}

static void fill(day_buffer_t* buffer)
{
	day_buffer_putchar(buffer, 'H');
}

void test_buffer_fillbuffer()
{
	flag = 0;
	day_buffer_t* buffer = construct_day_buffer(4, fill, FLUSH_FULL);
	ASSERT_NOT_EQUALS(buffer, NULL);
	
	memset(buffer->memory, 4, 0xDE);	
	ASSERT_EQUALS('H', day_buffer_getchar(buffer));
	
	destroy_day_buffer(buffer);
}

void test_buffer_resize()
{
	flag = 0;
	day_buffer_t* buffer = construct_day_buffer(4, fill, FLUSH_FULL);
	ASSERT_NOT_EQUALS(buffer, NULL);
	
	memset(buffer->memory, 4, 0xDE);	
	
	// Make it bigger
	ASSERT_EQUALS(5, day_buffer_resize(buffer, 5));
	
	// Make it smaller
	ASSERT_EQUALS(3, day_buffer_resize(buffer, 3));
	
	// Fill it and make it smaller
	buffer->content_size = 2;
	buffer->cursor = 3;
	ASSERT_EQUALS(2, day_buffer_resize(buffer, 1));
	ASSERT_EQUALS(2, buffer->cursor);
	
	destroy_day_buffer(buffer);
}


int main(int argc, char* argv[])
{
	printf("\n");
	printf(" _  _  _     ______               _____  _____   _____           _   \n"
		"| |(_)| |    |  _  \\             |  _  |/  ___| |_   _|         | |  \n"
		"| | _ | |__  | | | | __ _  _   _ | | | |\\ `--.    | |  ___  ___ | |_ \n"
		"| || || '_ \\ | | | |/ _` || | | || | | | `--. \\   | | / _ \\/ __|| __|\n"
		"| || || |_) || |/ /| (_| || |_| |\\ \\_/ //\\__/ /   | ||  __/\\__ \\| |_ \n"
		"|_||_||_.__/ |___/  \\__,_| \\__, | \\___/ \\____/    \\_/ \\___||___/ \\__|\n"
		"                            __/ |                                    \n"
		"                           |___/                                     \n"
		"\n\n");
	
	RUN(test_buffer_creation);
	RUN(test_buffer_putchar);
	RUN(test_buffer_flush_line);
	RUN(test_buffer_flush_full);
	RUN(test_buffer_getchar);
	RUN(test_buffer_fillbuffer);
	RUN(test_buffer_resize);

	return TEST_REPORT();
}