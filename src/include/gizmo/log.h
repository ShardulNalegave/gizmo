
#ifndef GIZMO_LOG_H
#define GIZMO_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

typedef enum {
    LOG_LEVEL_TRACE = 0,
    LOG_LEVEL_DEBUG = 1,
    LOG_LEVEL_INFO  = 2,
    LOG_LEVEL_WARN  = 3,
    LOG_LEVEL_ERROR = 4,
    LOG_LEVEL_CRITICAL = 5,
    LOG_LEVEL_OFF   = 6
} log_level_t;

int log_init(const char* filename);
void log_shutdown(void);

int log_print(log_level_t level, const char* fmt, ...);
int log_set_level(log_level_t level);

#ifdef __cplusplus
}
#endif

#define TRACE(...)    log_print(LOG_LEVEL_TRACE, __VA_ARGS__)
#define DEBUG(...)    log_print(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define INFO(...)     log_print(LOG_LEVEL_INFO,  __VA_ARGS__)
#define WARN(...)     log_print(LOG_LEVEL_WARN,  __VA_ARGS__)
#define ERROR(...)    log_print(LOG_LEVEL_ERROR, __VA_ARGS__)
#define CRITICAL(...) log_print(LOG_LEVEL_CRITICAL, __VA_ARGS__)

#endif
