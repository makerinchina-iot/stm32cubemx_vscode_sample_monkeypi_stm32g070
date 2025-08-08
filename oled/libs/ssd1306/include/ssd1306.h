/**
 * @file ssd1306.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2025-08-06
 *
 * @copyright Copyright (c) 2025
 *
 * @brief
 */

#ifndef _SSD1306_HEAD_H_
#define _SSD1306_HEAD_H_

// include dependencies file here
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void ssd1306_init(void);
    void ssd1306_set_pos(uint8_t x, uint8_t y);
    void ssd1306_test_bar();

#ifdef __cplusplus
}
#endif

#endif //!_SSD1306_HEAD_H_