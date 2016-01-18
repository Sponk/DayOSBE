#ifndef __TYPES_H
#define __TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef unsigned long tls_t;
typedef int handle_t;
typedef pid_t idtype_t;
typedef pid_t id_t;

typedef long int ssize_t;

typedef uint32_t mode_t;
typedef uint32_t ino_t;
typedef uint32_t dev_t;
typedef uint32_t off_t;

typedef uint32_t ino_t;
typedef uint32_t nlink_t;
typedef uint32_t uid_t;
typedef uint32_t gid_t;
typedef uint32_t blksize_t;
typedef uint32_t blkcnt_t;


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif

#endif
