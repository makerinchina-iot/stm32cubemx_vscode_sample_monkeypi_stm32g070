/**
 * @file mrand.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 * @brief
 */

#ifndef _MRAND_HEAD_H_
#define _MRAND_HEAD_H_

// include dependencies file here
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    uint32_t mrand(void);
    uint32_t mrand32(uint32_t max);

#ifdef __cplusplus
}
#endif

#endif //!_MRAND_HEAD_H_