/**
 * @file st7789.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#include "st7789.h"

void st7789_init()
{
    tft_port_init();

    tft_port_delay(100);
    tft_port_write_cmd(0x11);
    tft_port_delay(120);
    tft_port_write_cmd(0x36);
    tft_port_write_dat8(0x00);
    tft_port_write_cmd(0x3a);
    tft_port_write_dat8(0x05);
    tft_port_write_cmd(0x29);
}

void st7789_set_pos(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{

    tft_port_write_cmd(0x2a);
    tft_port_write_dat16(x1);
    tft_port_write_dat16(x2);

    tft_port_write_cmd(0x2b);
    tft_port_write_dat16(y1);
    tft_port_write_dat16(y2);

    tft_port_write_cmd(0x2c);
}

void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT))
    {
        return;
    }

    st7789_set_pos(x, y, x, y);

    tft_port_write_dat16(color);
}

void st7789_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{

    st7789_set_pos(x, y, x + w - 1, y + h - 1);

    for (uint32_t i = 0; i < w * h; i++)
    {
        tft_port_write_dat16(color);
    }
}
