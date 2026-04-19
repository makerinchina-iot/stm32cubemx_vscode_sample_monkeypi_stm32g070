/**
 * @file st7789.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#ifndef _ST7789_HEAD_H_
#define _ST7789_HEAD_H_

// include dependencies file here
#include "tft_port.h"
#include "tft_color.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void st7789_init();
    void st7789_set_pos(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
    void st7789_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

#ifdef __cplusplus
}
#endif

#endif //!_ST7789_HEAD_H_