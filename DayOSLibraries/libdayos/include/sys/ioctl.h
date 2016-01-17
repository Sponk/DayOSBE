#ifndef __IOCTL_H
#define __IOCTL_H

#ifdef __cplusplus
extern "C" {
#endif

int ioctl(int d, int request, ...);

// ATTENTION: Non standard!
char** ioctl_handle(pid_t who);
void ioctl_free(char** argv);

#ifdef __cplusplus
}
#endif

#endif
