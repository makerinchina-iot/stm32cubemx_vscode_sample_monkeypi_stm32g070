/**
 * @file mrand.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 * @brief
 */

#include "mrand.h"

/* 把编译时间拼成 32-bit 种子：
   bit31..26  年-2000  (0-63)
   bit25..22  月       (1-12)
   bit21..17  日       (1-31)
   bit16..12  时       (0-23)
   bit11..6   分       (0-59)
   bit5..0    秒/2    (0-29)  -> 秒占 6 bit
*/
#define BUILD_SEED ((((__DATE__[7] - '0') * 10 + (__DATE__[8] - '0') - 0) << 26) |                                                   \
                    (((__DATE__[0] == '?' ? 0 : ((__DATE__[0] - '0') * 10 + (__DATE__[1] - '0'))) << 22)) |                          \
                    ((__DATE__[4] == '?' ? 0 : ((__DATE__[4] == ' ' ? 0 : (__DATE__[4] - '0')) * 10 + (__DATE__[5] - '0'))) << 17) | \
                    (((__TIME__[0] - '0') * 10 + (__TIME__[1] - '0')) << 12) |                                                       \
                    (((__TIME__[3] - '0') * 10 + (__TIME__[4] - '0')) << 6) |                                                        \
                    (((__TIME__[6] - '0') * 10 + (__TIME__[7] - '0')) >> 1))

/* 32-bit Xorshift PRNG */
static inline uint32_t xorshift32(uint32_t state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

/* 全局种子，编译时确定 */
static const uint32_t g_seed = BUILD_SEED;

/* 获取 0 ~ max-1 的伪随机数 */
uint32_t mrand32(uint32_t max)
{
    return xorshift32(g_seed) % max;
}

uint32_t mrand(void)
{
    return xorshift32(g_seed);
}
