/*
 * Copyright (c) 2020 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "log.h"

#include "log2file.h"
#include "log2rtt.h"
#include "log2serial.h"

#define MAX_CALLBACKS 32

typedef struct
{
    log_LogFn fn;
    void *udata;
    int level;
} Callback;

static struct
{
    void *udata;
    log_LockFn lock;
    int level;
    bool quiet;
    Callback callbacks[MAX_CALLBACKS];
} L;

static const char *level_strings[] = {
    "[T]", "[D]", "[I]", "[W]", "[E]", "[F]"};

#ifdef LOG_USE_COLOR
static const char *level_colors[] = {
    "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};
#endif

static void lock(void)
{
    if (L.lock)
    {
        L.lock(true, L.udata);
    }
}

static void unlock(void)
{
    if (L.lock)
    {
        L.lock(false, L.udata);
    }
}

const char *log_level_string(int level)
{
    return level_strings[level];
}

#ifdef LOG_USE_COLOR
const char *log_level_color(int level)
{
    return level_colors[level];
}
#endif

void log_set_lock(log_LockFn fn, void *udata)
{
    L.lock = fn;
    L.udata = udata;
}

void log_set_level(int level)
{
    L.level = level;
}

void log_set_quiet(bool enable)
{
    L.quiet = enable;
}

int log_add_callback(log_LogFn fn, void *udata, int level)
{
    int i = 0;
    for (i = 0; i < MAX_CALLBACKS; i++)
    {
        if (!L.callbacks[i].fn)
        {
            L.callbacks[i] = (Callback){fn, udata, level};
            return 0;
        }
    }
    return -1;
}

static void init_event(log_Event *ev, void *udata)
{
#ifdef LOG_CONFIG_TIME_EN
    if (!ev->time)
    {
        // time_t t = 133506; //get time
        time_t t = __TIMESTAMP__;
        ev->time = localtime(&t);
    }
#endif
    ev->udata = udata;
}

void log_init(int level, bool quiet)
{
    log_set_quiet(quiet);

#ifdef LOG_CONFIG_FILE_EN
    FILE *fp;
    fp = fopen(LOG_CONFIG_FILE_NAME, "ab");
    log_add_fp(fp, level);
#endif

#ifdef LOG_CONFIG_RTT_EN
    SEGGER_RTT_Init();
    log_add_rtt(level);
#endif

#ifdef LOG_CONFIG_SERIAL_EN
    log_add_serial(level);
#endif
    log_set_level(level);
}

void log_log(int level, const char *file, const char *func, int line, const char *fmt, ...)
{
    log_Event ev = {
        .fmt = fmt,
        .file = file,
        .func = func,
        .line = line,
        .level = level,
    };

    lock();

    //  if (!L.quiet && level >= L.level) {
    //    init_event(&ev, stderr);
    //    va_start(ev.ap, fmt);
    //    stdout_callback(&ev);
    //    va_end(ev.ap);
    //  }

    int i = 0;
    for (i = 0; i < MAX_CALLBACKS && L.callbacks[i].fn; i++)
    {
        Callback *cb = &L.callbacks[i];
        if (level >= cb->level)
        {
            init_event(&ev, cb->udata);
            va_start(ev.ap, fmt);
            cb->fn(&ev);
            va_end(ev.ap);
        }
    }

    unlock();
}
