/**
 * @file log2rtt.h
 * @author MonkeyMaker
 * @brief
 * @version 0.01
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __LOG2RTT_H_
#define __LOG2RTT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "log.h"

#ifndef LOG_CONFIG_RTT_CH_INDEX
#define LOG_CONFIG_RTT_CH_INDEX 0 // default
#endif                            // !LOG_CONFIG_RTT_CH_INDEX

    int log_add_rtt(int level);

#ifdef __cplusplus
}
#endif

#endif //!_LOG2RTT_H_
