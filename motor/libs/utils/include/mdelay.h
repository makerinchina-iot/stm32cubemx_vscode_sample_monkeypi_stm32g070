/**
 * @file mdelay.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2025-08-06
 * 
 * @copyright Copyright (c) 2025
 * 
 * @brief 
 */

#ifndef _MDELAY_HEAD_H_
#define _MDELAY_HEAD_H_

//include dependencies file here

#include "stm32g0xx.h"

#ifdef __cplusplus
extern "C" {
#endif

    void delay_us(uint32_t us);
    void delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif //!_MDELAY_HEAD_H_