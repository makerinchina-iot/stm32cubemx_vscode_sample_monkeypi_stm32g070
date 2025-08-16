/**
 * @file log_config.h
 * @author MonkeyMaker
 * @brief
 * @version 0.01
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __LOG_CONFIG_H_
#define __LOG_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define LOG_USE_COLOR
    // #define LOG_CONFIG_FULL_FILE_NAME

#define LOG_CONFIG_RTT_EN
    // #define LOG_CONFIG_SERIAL_EN
    // #define LOG_CONFIG_FILE_EN
    // #define LOG_CONFIG_TIME_EN

#ifdef LOG_CONFIG_FILE_EN
#define LOG_CONFIG_FILE_NAME "log.txt"
#endif

#ifdef LOG_CONFIG_SERIAL_EN
//    #include "uart.h"
#endif

#ifdef LOG_CONFIG_RTT_EN
#define LOG_CONFIG_RTT_CH_INDEX 0
#include "SEGGER_RTT.h"
#endif

#ifdef LOG_CONFIG_TIME_EN
#include <time.h>
#endif

#ifdef __cplusplus
}
#endif

#endif //!_LOG_CONFIG_H_
