#ifndef __WAIT_H
#define __WAIT_H

#ifdef __cplusplus
extern "C" {
#endif

pid_t wait(int* stat_loc);
int waitid(idtype_t, id_t, siginfo_t*, int);
pid_t waitpid(pid_t pid, int* stat_loc, int options);

#ifdef __cplusplus
}
#endif

#endif