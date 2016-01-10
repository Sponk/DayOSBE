#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <syscall.h>

void debug_putch(int c)
{
	syscall1(1, c);
}

int debug_putchar(int character)
{
	debug_putch(character);
	return character;
}

int debug_puts(const char* s)
{
	int ret = 0;

	while(*s)
	{
		debug_putch(*s);
		ret++;
		s++;
	}

	return ret;
}

int debug_putn(unsigned int x, int base)
{
	char buf[65];
	const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* p;

	if(base > 36)
	{
		return 0;
	}

	memset(buf, 0, 64);

	p = buf + 64;
	*p = '\0';
	do
	{
		*--p = digits[x % base];
		x /= base;
	} while(x);
		
	return debug_puts(p);
}

int debug_printf(const char* fmt, ...)
{
	va_list ap;
	const char* s;
	unsigned long n;
	unsigned int ret = 0;

	va_start(ap, fmt);
	while (*fmt) 
	{
		if (*fmt == '%') 
		{
			fmt++;
			switch (*fmt) 
			{
				case 's':
					s = va_arg(ap, const char*);
					ret += debug_puts(s);
					break;
				case 'c':
					n = va_arg(ap, int);
					debug_putch(n);
					ret++;
					break;
				case 'd':
				case 'u':
					n = va_arg(ap, unsigned long int);
					ret += debug_putn(n, 10);
					break;
				case 'x':
				case 'p':
					n = va_arg(ap, unsigned long int);
					ret += debug_putn(n, 16);
					break;
				case 'l':
					switch(fmt[1])
					{
						case 'd':
							fmt++;
							n = va_arg(ap, long int);
							ret += debug_putn(n, 10);
							break;
					}
					break;
				case '%':
					debug_putch('%');
					ret++;
					break;
				case '\0':
					goto out;
				default:
					debug_putch('%');
					debug_putch(*fmt);
					ret += 2;
					break;
			}
		} 
		else 
		{
			debug_putch(*fmt);
			ret++;
		}
		fmt++;
	}

out:
	va_end(ap);
	return ret;
}

int sputn(char *s, int x, int base)
{
	char buf[65];
	const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *p;

	if (base > 36)
	{
		return 0;
	}

	memset(buf, 0, 64);

	p = buf + 64;
	*p = '\0';
	do
	{
		*--p = digits[x % base];
		x /= base;
	} while (x);

	strcpy(s, p);
	return strlen(p);
}

int sprintf(char *dest, const char *fmt, ...)
{
	va_list ap;
	int ret = 0;
	va_start(ap, fmt);
	ret = vsprintf(dest, fmt, ap);
	va_end(ap);
	return ret;
}

int snprintf(char *dest, size_t size, const char *fmt, ...)
{
	va_list ap;
	int ret = 0;
	va_start(ap, fmt);
	ret = vsnprintf(dest, size, fmt, ap);
	va_end(ap);
	return ret;
}

int vsprintf(char *dest, const char *fmt, va_list ap)
{
	const char *s;
	unsigned long n;
	unsigned int ret = 0;
	unsigned int len = 0;

	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			switch (*fmt)
			{
				case 's':
					s = va_arg(ap, const char *);
					len = strlen(s);
					strcpy(dest, s);
					ret += len;
					dest += len;
					break;
				case 'c':
					n = va_arg(ap, int);
					*dest = n;
					dest++;
					ret++;
					break;
				case 'd':
				case 'u':
					n = va_arg(ap, unsigned long int);
					len = sputn(dest, n, 10);

					dest += len;
					ret += len;
					break;
				case 'x':
				case 'p':
					n = va_arg(ap, unsigned long int);
					len = sputn(dest, n, 16);

					dest += len;
					ret += len;
					break;
				case 'l':
					switch (fmt[1])
					{
						case 'd':
							fmt++;
							n = va_arg(ap, long int);
							len = sputn(dest, n, 10);

							dest += len;
							ret += len;
							break;
					}
					break;
				case '%':
					*dest = '%';
					dest++;
					ret++;
					break;
				case '\0':
					goto out;
				default:
					*dest = '%';
					dest++;
					*dest = *fmt;
					dest++;

					ret += 2;
					break;
			}
		}
		else
		{
			*dest = *fmt;
			dest++;
			ret++;
		}
		fmt++;
	}

out:
	return ret;
}

int vsnprintf(char *dest, size_t size, const char *fmt, va_list ap)
{
	const char *s;
	unsigned long n;
	unsigned int ret = 0;
	unsigned int len = 0;

	while (*fmt && len < size)
	{
		if (*fmt == '%')
		{
			fmt++;
			switch (*fmt)
			{
				case 's':
					s = va_arg(ap, const char *);
					len = strlen(s);
					strcpy(dest, s);
					ret += len;
					dest += len;
					break;
				case 'c':
					n = va_arg(ap, int);
					*dest = n;
					dest++;
					ret++;
					break;
				case 'd':
				case 'u':
					n = va_arg(ap, unsigned long int);
					len = sputn(dest, n, 10);

					dest += len;
					ret += len;
					break;
				case 'x':
				case 'p':
					n = va_arg(ap, unsigned long int);
					len = sputn(dest, n, 16);

					dest += len;
					ret += len;
					break;
				case 'l':
					switch (fmt[1])
					{
						case 'd':
							fmt++;
							n = va_arg(ap, long int);
							len = sputn(dest, n, 10);

							dest += len;
							ret += len;
							break;
					}
					break;
				case '%':
					*dest = '%';
					dest++;
					ret++;
					break;
				case '\0':
					goto out;
				default:
					*dest = '%';
					dest++;
					*dest = *fmt;
					dest++;

					ret += 2;
					break;
			}
		}
		else
		{
			*dest = *fmt;
			dest++;
			ret++;
		}
		fmt++;
	}

out:
	return ret;
}

int asprintf(char **str, const char *fmt, ...) {}
int vasprintf(char **str, const char *fmt, va_list ap) {}
int sscanf(const char* str, const char* format, ...) {}
