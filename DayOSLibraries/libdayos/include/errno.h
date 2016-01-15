#ifndef __ERRNO_H
#define __ERRNO_H

#define EDOM 1
#define ERANGE 2
#define EILSEQ 3
#define EINTR 4
#define EBADF 5
#define EAGAIN 6
#define EACCES 7
#define ENOENT 8
#define EEXIST 9
#define EAFNOSUPPORT 10
#define EADDRINUSE 11
#define EADDRNOTAVAIL 12
#define EISCONN 13
#define E2BIG 14
#define EFAULT 15
#define EINVAL 16
#define ESPIPE 17
#define EIO 18
#define EISDIR 19
#define EMSGSIZE 20
#define ENETDOWN 21
#define ENETRESET 22
#define ENETUNREACH 23
#define ENOBUFS 24
#define ECHILD 25
#define ENOLCK 26
#define ENOMSG 27
#define ENOPROTOOPT 28
#define ENOSPC 29
#define ENXIO 30
#define ENODEV 31
#define ESRCH 32
#define ENOTDIR 33
#define ENOTCONN 34
#define ENOMEM 35
#define EINPROGRESS 36
#define EPERM 37
#define EOPNOSUPP 38
#define EWOULDBLOCK 39
#define EPROTONOSUPPORT 40
#define EROFS 41
#define EDEADLK 42
#define ETIMEOUT 43
#define ENFILE 44
#define EMFILE 45
#define EMLINK 46
#define ELOOP 47
#define EPROTOTYPE 48
#define EPIPE 49
#define ECONNABORTED 50
#define EALREADY 51
#define ECONNREFUSED 52
#define ECONNRESET 53
#define EXDEV 54
#define EDESTADDRREQ 55
#define EBUSY 56
#define ENOTEMPTY 57
#define ENOEXEC 58
#define EFBIG 59
#define ENAMETOOLONG 60
#define ENOSYS 61
#define EHOSTUNREACH 62
#define ENOTTY 63
#define ENOTSOCK 64
#define EOPNOTSUPP 65
#define ETIMEDOUT 66

#ifdef __cplusplus
extern "C" {
#endif

extern int errno;

	
#ifdef __cplusplus
}
#endif

#endif