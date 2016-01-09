#ifndef SIGNAL_H
#define SIGNAL_H

#define SIG_ERR 1
#define SIGINT 2
#define SIGILL 4
#define SIGFPE 8
#define SIGSEGV 11
#define SIGTERM 15
#define SIGBREAK 21
#define SIGABRT 22
#define NSIG 23

#define SIG_DFL 0
#define SIG_IGN 1

#ifdef __cplusplus
extern "C" {
#endif

typedef int sig_atomic_t; 

void (*signal(int sig, void (*func)(int)))(int);
int raise(int sig);

#ifdef __cplusplus
}
#endif

#endif