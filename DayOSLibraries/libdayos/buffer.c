#include <buffer.h>
#include <stdlib.h>
#include <dayos.h>
#include <stdio.h>

#define CLAMP(x, min, max) ((x < min) ? min : (x > max) ? max : x)

static void default_flush(day_buffer_t* buffer)
{
	debug_printf("Flushing buffer: sz = %d content_size = %d memory = %s csr = %d\n", buffer->size, buffer->content_size, buffer->memory, buffer->cursor);
	int i = 12 / 0;
}

day_buffer_t* construct_day_buffer(size_t size, void (*flush)(day_buffer_t* buffer), DAYBUFFER_FLUSHMODE mode)
{
	if(size == 0)
		return NULL;
	
	day_buffer_t* buffer = malloc(sizeof(day_buffer_t));
	buffer->memory = malloc(size);
	
	buffer->size = size;
	buffer->cursor = 0;
	buffer->content_size = 0;
	buffer->mode = mode;
	
	buffer->flush = (flush) ? flush : default_flush;
	
	return buffer;
}

void destroy_day_buffer(day_buffer_t* buf)
{
	if(!buf)
		return;
	
	if(buf->memory)
		free(buf->memory);
	
	free(buf);
}

void day_buffer_putchar(day_buffer_t* buffer, int character)
{
	if(!buffer)
		return;
	
	buffer->memory[buffer->cursor++] = character;
	buffer->content_size++;
	
	// Flush!
	switch(buffer->mode)
	{
		case FLUSH_LINE:
			if(character == '\n' || buffer->content_size >= buffer->size)
			{
				buffer->memory[buffer->cursor] = 0;
				buffer->flush(buffer);
				buffer->content_size = 0;
				buffer->cursor = 0;
			}
		break;
		
		case FLUSH_FULL:
			if(buffer->content_size >= buffer->size)
			{
				buffer->memory[buffer->cursor] = 0;
				buffer->flush(buffer);
				buffer->content_size = 0;
				buffer->cursor = 0;
			}
		break;
	}
	
	buffer->memory[buffer->cursor] = 0;
}

int day_buffer_getchar(day_buffer_t* buffer)
{
	if(!buffer)
		return EOF;
		
	// Flush!
	if(buffer->content_size <= 0)
	{
		buffer->flush(buffer);
		buffer->cursor = buffer->content_size;
	}

	if(buffer->content_size > 0 || buffer->cursor > 0)
	{
		buffer->content_size--;
		return buffer->memory[--buffer->cursor];
	}
	
	return EOF;
}

int day_buffer_resize(day_buffer_t* buffer, size_t newsize)
{
	if(!buffer)
		return 0;
	
	if(newsize < buffer->size)
	{
		if(buffer->content_size > newsize)
			newsize = buffer->content_size;
	}
	
	buffer->memory = realloc(buffer->memory, newsize);
	buffer->cursor = CLAMP(buffer->cursor, 0, newsize);
	return newsize;
}