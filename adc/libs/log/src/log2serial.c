/**
 * @file log2serial.c
 * @author MonkeyMaker
 * @brief
 * @version 0.01
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "log2serial.h"

static void serial_log_callback(log_Event *ev)
{
#ifdef LOG_CONFIG_TIME_EN
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';
#else
    char buf[1];
    buf[0] = '\0';
#endif
#ifdef LOG_USE_COLOR
    fprintf(
        ev->udata, "%s %s%-5s\x1b[0m \x1b[90m%s, %s:%d:\x1b[0m ",
        buf, log_level_color(ev->level), log_level_string(ev->level),
        ev->file, ev->func, ev->line);
#else
    fprintf(
        ev->udata, "%s %-5s %s, %s:%d: ",
        buf, log_level_string(ev->level), ev->file, ev->func, ev->line);
#endif
    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\r\n");
    fflush(ev->udata);
}

int log_add_serial(int level)
{
    return log_add_callback(serial_log_callback, stderr, level);
}
