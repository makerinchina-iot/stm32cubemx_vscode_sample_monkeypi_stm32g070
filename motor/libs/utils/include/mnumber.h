/**
 * @file mnumber.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2025-08-04
 *
 * @copyright Copyright (c) 2025
 *
 * @brief
 */

#ifndef _MNUMBER_HEAD_H_
#define _MNUMBER_HEAD_H_

// include dependencies file here

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int32_t float_to_int_decimal(float num, int32_t *decimal, uint8_t decimals);
    void float_to_string(char *buf, float num);

#ifdef __cplusplus
}
#endif

#endif //!_MNUMBER_HEAD_H_