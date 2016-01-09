#include <stdio.h>
#include <sys/utsname.h>

int main()
{
	struct utsname name;
	uname(&name);

	printf("%s %s %s\n", name.sysname, name.release, name.machine);
	return 0;
}
