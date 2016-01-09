#ifndef __UTSNAME_H
#define __UTSNAME_H

#include <message.h>

struct utsname
{
	char sysname[32];
	char nodename[32];
	char release[32];
	char version[32];
	char machine[32];
};

#ifdef __cplusplus
extern "C" {
#endif

int uname(struct utsname* name);

#ifdef __cplusplus
}
#endif

#endif