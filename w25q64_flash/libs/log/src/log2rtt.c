/**
 * @file log2rtt.c
 * @author MonkeyMaker
 * @brief
 * @version 0.01
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "log2rtt.h"

static void rtt_log_callback(log_Event *ev)
{
#ifdef LOG_CONFIG_TIME_EN
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';
#else
    char buf[1];
    buf[0] = '\0';
#endif
#ifdef LOG_USE_COLOR
    SEGGER_RTT_printf(LOG_CONFIG_RTT_CH_INDEX, "%s %s%-5s\x1b[0m \x1b[90m%s, %s:%d:\x1b[0m ",
                      buf, log_level_color(ev->level), log_level_string(ev->level),
                      ev->file, ev->func, ev->line);

#else
    SEGGER_RTT_printf(LOG_CONFIG_RTT_CH_INDEX,
                      "%s %-5s %s, %s:%d: ",
                      buf, log_level_string(ev->level), ev->file, ev->func, ev->line);
#endif

    SEGGER_RTT_vprintf(LOG_CONFIG_RTT_CH_INDEX, ev->fmt, &(ev->ap));

    SEGGER_RTT_printf(LOG_CONFIG_RTT_CH_INDEX, "\r\n");
}

int log_add_rtt(int level)
{
    return log_add_callback(rtt_log_callback, NULL, level);
}
