#ifndef __DAYOS_BUFFER_H
#define __DAYOS_BUFFER_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes buffering modes for a day_buffer_t object.
 */
typedef enum
{
	FLUSH_LINE, /// Flushes for every line
	FLUSH_FULL /// Flushes only when buffer is full
} DAYBUFFER_FLUSHMODE;
	
typedef struct DAY_BUFFER_STRUCT
{
	void (*flush)(struct DAY_BUFFER_STRUCT* buffer); /// A callback that is called when the buffer needs to be emptied or refilled
	size_t size; /// The size of the buffer in bytes
	size_t cursor; /// The current reading/writing position
	size_t content_size; /// The current size of the content
	DAYBUFFER_FLUSHMODE mode; /// The flushing mode
	char* memory; /// The memory buffer
}day_buffer_t;

/**
 * @brief Constructs a new day_buffer_t
 * @param size The size in bytes.
 * @param flush The function used to fill/empty the buffer.
 * @param mode The flushing mode that shall be used.
 * @return A new day_buffer_t object.
 */
day_buffer_t* construct_day_buffer(size_t size, void (*flush)(day_buffer_t* buffer), DAYBUFFER_FLUSHMODE mode);

/**
 * @brief Destroys an existing day_buffer_t object.
 * @param buf The buffer to destroy.
 */
void destroy_day_buffer(day_buffer_t* buf);

void day_buffer_putchar(day_buffer_t* buffer, int character);
int day_buffer_getchar(day_buffer_t* buffer);
int day_buffer_resize(day_buffer_t* buffer, size_t newsize);

#ifdef __cplusplus
}
#endif

#endif