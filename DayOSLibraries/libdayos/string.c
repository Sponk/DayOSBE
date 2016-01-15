#include <string.h>
#include <stdarg.h>
#include <malloc.h>

int strcmp(const char *str1, const char *str2)
{
	if (str1 == str2)
		return 0;
	size_t i;

	for (i = 0; (str1[i] || str2[i]); i++)
	{
		if (str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}
	}
	return 0;
}

int strcasecmp(const char *str1, const char *str2)
{
	size_t i;
	for (i = 0; (str1[i] != 0 && str2[i] != 0); i++)
	{
		if (str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}
	}
	return 0;
}

char *strcat(char *str1, const char *str2)
{
	return strcpy(str1 + strlen(str1), str2);
}

char *strchr(const char *str, int chr)
{
	size_t i;
	for (i = 0; (str[i] != 0 && str[i] != (char) chr); i++);
	return str[i] == chr ? ((char *)str + i) : NULL;
}

int strcoll(const char *str1, const char *str2) { return strcmp(str1, str2); }

char *strcpy(char *dest, const char *src)
{
	size_t i;
	for (i = 0; src[i]; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = 0;
	return dest;
}

size_t strcspn(const char *s1, const char *s2)
{
	const char *sc1;
	for (sc1 = s1; *sc1 != '\0'; sc1++)
	{
		if (strchr(s2, *sc1) != NULL)
		{
			return (sc1 - s1);
		}
	}
	return sc1 - s1;
}

size_t strlen(const char *str)
{
	if (str == NULL)
	{
		return 0;
	}
	size_t i;
	for (i = 0; str[i]; i++)
		;
	return i;
}

int strncasecmp(const char *str1, const char *str2, size_t n)
{
	size_t i;
	for (i = 0; (str1[i] != 0 && str2[i] != 0 && i < n); i++)
	{
		if (str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}
	}
	return 0;
}

char *strncat(char *src1, const char *src2, size_t n)
{
	size_t src2len = strlen(src2);
	src2len = n < src2len ? n : src2len;
	size_t src1len = strlen(src1);
	uint32_t i;

	for (i = 0; i < src2len; i++)
	{
		src1[src1len + i] = src2[i];
	}
	src1[src1len + src2len] = 0;
	return src1;
}

int strncmp(const char *str1, const char *str2, size_t n)
{
	if (str1 == str2)
	{
		return 0;
	}
	size_t i;

	for (i = 0; (str1[i] || str2[i]) && i < n; i++)
	{
		if (str1[i] != str2[i])
			return str1[i] - str2[i];
	}
	return 0;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	size_t len = strlen(src) + 1;
	if (n < len)
	{
		len = n;
	}
	memcpy(dest, src, len - 1);
	dest[len - 1] = 0;
	return dest;
}

char *strpbrk(const char *s1, const char *s2)
{
	const char *sc1;
	for (sc1 = s1; *sc1 != '\0'; sc1++)
		if (strchr(s2, *sc1) != NULL)
			return (char *)sc1;
	return NULL;
}

char *strrchr(const char *s, int c)
{
	char *l = NULL;
	size_t i;
	for (i = 0; s[i]; i++)
	{
		if (s[i] == c)
		{
			l = (char *)s + i;
		}
	}
	return l;
}

size_t strspn(const char *string, const char *spanset)
{
	const char *sc1;
	for (sc1 = string; *sc1 != '\0'; sc1++)
		if (strchr(spanset, *sc1) == NULL)
		{
			return (sc1 - string);
		}
	return sc1 - string;
}

char *strstr(const char *haystack, const char *needle)
{
	size_t needlelen;
	/* Check for the null needle case.  */
	if (*needle == '\0')
	{
		return (char *)haystack;
	}
	needlelen = strlen(needle);
	for (; (haystack = strchr(haystack, *needle)) != NULL; haystack++)
		if (strncmp(haystack, needle, needlelen) == 0)
		{
			return (char *)haystack;
		}
	return NULL;
}

char *strsep(char **stringp, const char *delim)
{
	char *begin, *end;

	begin = *stringp;
	if (begin == NULL)
		return NULL;

	if (delim[0] == '\0' || delim[1] == '\0')
	{
		char ch = delim[0];

		if (ch == '\0')
		{
			end = NULL;
		}
		else
		{
			if (*begin == ch)
			{
				end = begin;
			}
			else if (*begin == '\0')
			{
				end = NULL;
			}
			else
			{
				end = strchr(begin + 1, ch);
			}
		}
	}
	else
	{
		end = strpbrk(begin, delim);
	}

	if (end)
	{
		*end++ = '\0';
		*stringp = end;
	}
	else
		*stringp = NULL;

	return begin;
}

char *strtok(char *s, const char *delim)
{
	static char *holder;

	if (s)
	{
		holder = s;
	}
	do
	{
		s = strsep(&holder, delim);
	} while (s && !*s);

	return s;
}

void *memccpy(void *dest, const void *src, int c, size_t n)
{
	uint8_t *dest8 = (uint8_t *)dest;
	uint8_t *src8 = (uint8_t *)src;
	uint32_t i;

	for (i = 0; i < n; i++)
	{
		dest8[i] = src8[i];
		if (src8[i] == ((uint8_t)c))
		{
			break;
		}
	}
	return dest;
}

void *memcpy(void *dest, const void *src, int n)
{
	if (dest == src)
	{
		return dest;
	}
	size_t fast_count = n / sizeof(int);
	size_t byte_count = n % sizeof(int);
	int *fast_dest = (int *)dest;
	int *fast_src = (int *)src;
	uint8_t *byte_dest = ((uint8_t *)dest) + fast_count * sizeof(int);
	uint8_t *byte_src = ((uint8_t *)src) + fast_count * sizeof(int);
	size_t i;

	for (i = 0; i < fast_count; i++)
		fast_dest[i] = fast_src[i];
	for (i = 0; i < byte_count; i++)
		byte_dest[i] = byte_src[i];
	return dest;
}

void *memset(void *dest, int val, size_t n)
{
	size_t i;
	uint8_t *byte_dest = (uint8_t *)dest;
	for (i = 0; i < n; i++)
		byte_dest[i] = val;
	return dest;
}

void *memchr(const void *src, int c, size_t n)
{
	uint8_t *src8 = (uint8_t *)src;
	uint32_t i;

	for (i = 0; i < n; i++)
	{
		if (src8[i] == ((uint8_t)c))
		{
			return (void *)(src8 + i);
		}
	}
	return NULL;
}

int memcmp(const void *srca, const void *srcb, size_t n)
{
	if (srca == srcb)
		return 0;
	size_t fast_count = n / sizeof(int);
	size_t byte_count = n % sizeof(int);
	int *fast_srca = (int *)srca;
	int *fast_srcb = (int *)srcb;
	uint8_t *byte_srca = ((uint8_t *)srca) + fast_count * sizeof(int);
	uint8_t *byte_srcb = ((uint8_t *)srcb) + fast_count * sizeof(int);
	size_t i;

	for (i = 0; i < fast_count; i++)
	{
		if (fast_srca[i] != fast_srcb[i])
		{
			return fast_srca[i] - fast_srcb[i];
		}
	}
	for (i = 0; i < byte_count; i++)
	{
		if (byte_srca[i] != byte_srcb[i])
		{
			return byte_srca[i] - byte_srcb[i];
		}
	}
	return 0;
}

void *memmove(void *dest, const void *src, size_t n)
{
	if (dest == src)
	{
		return dest;
	}
	size_t fast_count = n / sizeof(int);
	size_t byte_count = n % sizeof(int);
	int *fast_dest = (int *)dest;
	int *fast_src = (int *)src;
	uint8_t *byte_dest = ((uint8_t *)dest) + fast_count * sizeof(int);
	uint8_t *byte_src = ((uint8_t *)src) + fast_count * sizeof(int);
	size_t i;

	if (src > dest)
	{
		for (i = 0; i < fast_count; i++)
			fast_dest[i] = fast_src[i];
		for (i = 0; i < byte_count; i++)
			byte_dest[i] = byte_src[i];
	}
	else
	{
		for (i = byte_count; i > 0; i--)
			byte_dest[i - 1] = byte_src[i - 1];
		for (i = fast_count; i > 0; i--)
			fast_dest[i - 1] = fast_src[i - 1];
	}
	return dest;
}

/*int atoi(char *s)
{
	int ret = 0;
	while (*s)
	{
		ret = (ret << 3) + (ret << 1) + (*s) - '0';
		s++;
	}
	return ret;
}*/

char *strdup(const char *s)
{
	if (!s)
		return NULL;
	size_t len = strlen(s) + 1;

	char *nstr = (char *)malloc(len);
	if (nstr)
		memcpy(nstr, s, len);

	return nstr;
}

char *strndup(const char *s, size_t n) {}

char *strdupa(const char *s) {}

char *strndupa(const char *s, size_t n) {}

size_t strxfrm (char* destination, const char* source, size_t num)
{
	return 0;
}

/*int isspace(int x)
{
	return (x == ' ' || x == '\t' || x == '\n' || x == '\v' || x == '\f' || x == '\r');
}

int isdigit(int x)
{
	return (x >= '0' && x <= '9');
}

int isxdigit(int x)
{
	return ((x >= 'A' && x <= 'F') && (x >= 'a' && x <= 'f') && (x >= '0' && x <= '9'));
}

int isalpha(int x) { return (x >= 'A' && x <= 'z'); }

int toupper(int x) { return (x + 26); }
int tolower(int x) { return (x - 26); }
int isprint(int x) { return (x >= 0x1f || x == 0x7f); }
int isalnum(int x) { return (isdigit(x) || isalpha(x)); }

int iscntrl(int x) { return !isprint(x); }
int isgraph(int x) { return (isprint(x) && x != ' '); }

int isupper(int x) { return (x >= 'A' && x <= 'Z'); }
int islower(int x) { return (x >= 'a' && x <= 'z'); }
int ispunct(int x) { return (isgraph(x) && !isalnum(x)); }*/
