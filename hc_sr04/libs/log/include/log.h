/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "log_config.h"

typedef struct
{
    va_list ap;
    const char *fmt;
    const char *file;
    const char *func;
#ifdef LOG_CONFIG_TIME_EN
    struct tm *time;
#endif
    void *udata;
    int line;
    int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum
{
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

#ifdef LOG_CONFIG_FULL_FILE_NAME

#define log_trace(...) log_log(LOG_TRACE, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_info(...) log_log(LOG_INFO, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_log(LOG_WARN, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __func__, __LINE__, __VA_ARGS__)

#else

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#define log_trace(...) log_log(LOG_TRACE, __FILENAME__, __func__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILENAME__, __func__, __LINE__, __VA_ARGS__)
#define log_info(...) log_log(LOG_INFO, __FILENAME__, __func__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_log(LOG_WARN, __FILENAME__, __func__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILENAME__, __func__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILENAME__, __func__, __LINE__, __VA_ARGS__)

#endif

const char *log_level_string(int level);
#ifdef LOG_USE_COLOR
const char *log_level_color(int level);
#endif

void log_init(int level, bool quiet);

void log_set_lock(log_LockFn fn, void *udata);
void log_set_level(int level);
void log_set_quiet(bool enable);
int log_add_callback(log_LogFn fn, void *udata, int level);

void log_log(int level, const char *file, const char *func, int line, const char *fmt, ...);

#endif
