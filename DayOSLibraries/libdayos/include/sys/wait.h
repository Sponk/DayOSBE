#ifndef __WAIT_H
#define __WAIT_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

pid_t wait(int* status);
pid_t waitpid(pid_t pid, int* status, int options);
// int waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options);

#ifdef __cplusplus
}
#endif

#endif