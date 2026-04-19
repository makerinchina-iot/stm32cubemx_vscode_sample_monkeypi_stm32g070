/**
 * @file mdelay.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2025-08-06
 *
 * @copyright Copyright (c) 2025
 *
 * @brief
 */

#include "mdelay.h"

static inline void delay_systick(uint32_t ticks)
{
    uint32_t start = SysTick->VAL;
    uint32_t end = start - ticks;
    if (end > start)
    {
        while (SysTick->VAL > end)
        {
        }
    }
    while (SysTick->VAL < start && SysTick->VAL > end)
    {
    }
}

void delay_us(uint32_t us)
{
    uint32_t ticks = us * (HAL_RCC_GetHCLKFreq() / 1000000UL);
    delay_systick(ticks);
}

void delay_ms(uint32_t ms)
{
    while (ms--)
        delay_us(1000);
}