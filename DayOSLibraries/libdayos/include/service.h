#ifndef SERVICE_H
#define SERVICE_H

#include "stdint.h"

#define SERVICE_REQUEST 2
#define SERVICE_REGISTER 1

#ifdef __cplusplus
extern "C" {
#endif

int register_service(const char* name);
pid_t get_service_pid(const char* name);

#ifdef __cplusplus
}
#endif

#endif
