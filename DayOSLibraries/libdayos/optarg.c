#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define ERROR(msg, c)                                     \
	{                                                     \
		if (opterr)                                       \
			fprintf(stderr, "%s%s%c\n", argv[0], msg, c); \
	}

char* optarg = NULL;
int optind = 1, opterr = 1, optopt = 0;

int getopt(int argc, char* argv[], const char* opts)
{
	static int idx = 1;
	int c = 0;
	char* iter = NULL;

	if (idx == 1)
	{
		if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == 0)
			return EOF;
		else if (!strcmp(argv[optind], "--"))
			return EOF;
	}

	optopt = c = argv[optind][idx];

	if (c == ':' || (iter = strchr(opts, c)) == NULL)
	{
		ERROR(": Illegal option -- ", c);

		if (argv[optind][++idx] == 0)
		{
			optind++;
			idx = 1;
		}

		return '?';
	}

	if (*(iter + 1) == ':')
	{
		if (argv[optind][idx + 1] != 0)
		{				
			optarg = &argv[optind++][idx + 1];
		}
		else if (++optind >= argc)
		{
			ERROR(": Option requires an argument -- ", c);
			idx = 1;
			return '?';
		}
		else
			optarg = argv[optind];
	}
	else
	{
		if (argv[optind][++idx] == 0)
		{
			idx = 1;
			optind++;
		}

		optarg = NULL;
	}

	return c;
}
