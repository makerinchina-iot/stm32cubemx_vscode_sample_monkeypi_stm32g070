/**
 * @file log2file.h
 * @author MonkeyMaker
 * @brief 
 * @version 0.01
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __LOG2FILE_H_
#define __LOG2FILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "log.h"

#ifndef LOG_CONFIG_FILE_NAME
    #define LOG_CONFIG_FILE_NAME "log.txt"
#endif

int log_add_fp(FILE *fp, int level);

#ifdef __cplusplus
}
#endif

#endif //!_LOG2FILE_H_
