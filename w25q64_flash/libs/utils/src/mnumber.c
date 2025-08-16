/**
 * @file mnumber.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2025-08-04
 *
 * @copyright Copyright (c) 2025
 *
 * @brief
 */

#include "mnumber.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief 拆分浮点数为整数和小数部分
 * @param num       输入的浮点数
 * @param decimal   输出的小数部分（已乘以10^decimals）
 * @param decimals  要保留的小数位数（如2表示保留两位）
 * @return 整数部分
 */
int32_t float_to_int_decimal(float num, int32_t *decimal, uint8_t decimals)
{
    // 处理负数
    float abs_num = fabsf(num);

    // 计算整数部分（向零取整）
    int32_t integer_part = (int32_t)abs_num;
    if (num < 0)
    {
        integer_part = -integer_part;
    }

    // 计算小数部分（四舍五入）
    float decimal_float = abs_num - floorf(abs_num);    // 取小数部分
    float scale = powf(10.0f, (float)decimals);         // 缩放因子（如100对应2位小数）
    *decimal = (int32_t)(decimal_float * scale + 0.5f); // 四舍五入

    // 处理小数位溢出（如99.999→100.00）
    if (*decimal >= (int32_t)scale)
    {
        *decimal = 0;
        integer_part += (num >= 0 ? 1 : -1);
    }

    return integer_part;
}

/**
 * @brief  convert float to string buff
 * @param  buf             result
 * @param  num             float number
 */
void float_to_string(char *buf, float num)
{
    int32_t integer, decimal;

    // 设置保留小数为 2, 修改 decimals 和 sprintf 中的 %02d
    int decimals = 2;
    integer = float_to_int_decimal(num, &decimal, decimals);
    sprintf(buf, "%ld.%02ld", integer, decimal);
}
