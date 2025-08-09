/**
 * @file log2file.c
 * @author MonkeyMaker
 * @brief
 * @version 0.01
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "log2file.h"

static void log_file_callback(log_Event *ev)
{
    char buf[64];
#ifdef LOG_CONFIG_TIME_EN
    buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ev->time)] = '\0';
#endif
    fprintf(
        ev->udata, "%s %-5s %s, %s:%d: ",
        buf, log_level_string(ev->level), ev->file, ev->func, ev->line);
    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);
}

int log_add_fp(FILE *fp, int level)
{
    return log_add_callback(log_file_callback, fp, level);
}
