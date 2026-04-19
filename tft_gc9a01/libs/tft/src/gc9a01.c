/**
 * @file gc9a01.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#include "gc9a01.h"

void gc9a01_init()
{
    tft_port_init();

    tft_port_delay(100);

    tft_port_write_cmd(0xEF);
    tft_port_write_cmd(0xEB);
    tft_port_write_dat8(0x14);

    tft_port_write_cmd(0xFE);
    tft_port_write_cmd(0xEF);

    tft_port_write_cmd(0xEB);
    tft_port_write_dat8(0x14);

    tft_port_write_cmd(0x84);
    tft_port_write_dat8(0x40);

    tft_port_write_cmd(0x85);
    tft_port_write_dat8(0xFF);

    tft_port_write_cmd(0x86);
    tft_port_write_dat8(0xFF);

    tft_port_write_cmd(0x87);
    tft_port_write_dat8(0xFF);

    tft_port_write_cmd(0x88);
    tft_port_write_dat8(0x0A);

    tft_port_write_cmd(0x89);
    tft_port_write_dat8(0x21);

    tft_port_write_cmd(0x8A);
    tft_port_write_dat8(0x00);

    tft_port_write_cmd(0x8B);
    tft_port_write_dat8(0x80);

    tft_port_write_cmd(0x8C);
    tft_port_write_dat8(0x01);

    tft_port_write_cmd(0x8D);
    tft_port_write_dat8(0x01);

    tft_port_write_cmd(0x8E);
    tft_port_write_dat8(0xFF);

    tft_port_write_cmd(0x8F);
    tft_port_write_dat8(0xFF);

    tft_port_write_cmd(0xB6);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x20);

    tft_port_write_cmd(0x36);
    tft_port_write_dat8(0x08);

    tft_port_write_cmd(0x3A);
    tft_port_write_dat8(0x05);

    tft_port_write_cmd(0x90);
    tft_port_write_dat8(0x08);
    tft_port_write_dat8(0x08);
    tft_port_write_dat8(0x08);
    tft_port_write_dat8(0x08);

    tft_port_write_cmd(0xBD);
    tft_port_write_dat8(0x06);

    tft_port_write_cmd(0xBC);
    tft_port_write_dat8(0x00);

    tft_port_write_cmd(0xFF);
    tft_port_write_dat8(0x60);
    tft_port_write_dat8(0x01);
    tft_port_write_dat8(0x04);

    tft_port_write_cmd(0xC3);
    tft_port_write_dat8(0x13);
    tft_port_write_cmd(0xC4);
    tft_port_write_dat8(0x13);

    tft_port_write_cmd(0xC9);
    tft_port_write_dat8(0x22);

    tft_port_write_cmd(0xBE);
    tft_port_write_dat8(0x11);

    tft_port_write_cmd(0xE1);
    tft_port_write_dat8(0x10);
    tft_port_write_dat8(0x0E);

    tft_port_write_cmd(0xDF);
    tft_port_write_dat8(0x21);
    tft_port_write_dat8(0x0c);
    tft_port_write_dat8(0x02);

    tft_port_write_cmd(0xF0);
    tft_port_write_dat8(0x45);
    tft_port_write_dat8(0x09);
    tft_port_write_dat8(0x08);
    tft_port_write_dat8(0x08);
    tft_port_write_dat8(0x26);
    tft_port_write_dat8(0x2A);

    tft_port_write_cmd(0xF1);
    tft_port_write_dat8(0x43);
    tft_port_write_dat8(0x70);
    tft_port_write_dat8(0x72);
    tft_port_write_dat8(0x36);
    tft_port_write_dat8(0x37);
    tft_port_write_dat8(0x6F);

    tft_port_write_cmd(0xF2);
    tft_port_write_dat8(0x45);
    tft_port_write_dat8(0x09);
    tft_port_write_dat8(0x08);
    tft_port_write_dat8(0x08);
    tft_port_write_dat8(0x26);
    tft_port_write_dat8(0x2A);

    tft_port_write_cmd(0xF3);
    tft_port_write_dat8(0x43);
    tft_port_write_dat8(0x70);
    tft_port_write_dat8(0x72);
    tft_port_write_dat8(0x36);
    tft_port_write_dat8(0x37);
    tft_port_write_dat8(0x6F);

    tft_port_write_cmd(0xED);
    tft_port_write_dat8(0x1B);
    tft_port_write_dat8(0x0B);

    tft_port_write_cmd(0xAE);
    tft_port_write_dat8(0x77);

    tft_port_write_cmd(0xCD);
    tft_port_write_dat8(0x63);

    tft_port_write_cmd(0x70);
    tft_port_write_dat8(0x07);
    tft_port_write_dat8(0x07);
    tft_port_write_dat8(0x04);
    tft_port_write_dat8(0x0E);
    tft_port_write_dat8(0x0F);
    tft_port_write_dat8(0x09);
    tft_port_write_dat8(0x07);
    tft_port_write_dat8(0x08);
    tft_port_write_dat8(0x03);

    tft_port_write_cmd(0xE8);
    tft_port_write_dat8(0x34);

    tft_port_write_cmd(0x62);
    tft_port_write_dat8(0x18);
    tft_port_write_dat8(0x0D);
    tft_port_write_dat8(0x71);
    tft_port_write_dat8(0xED);
    tft_port_write_dat8(0x70);
    tft_port_write_dat8(0x70);
    tft_port_write_dat8(0x18);
    tft_port_write_dat8(0x0F);
    tft_port_write_dat8(0x71);
    tft_port_write_dat8(0xEF);
    tft_port_write_dat8(0x70);
    tft_port_write_dat8(0x70);

    tft_port_write_cmd(0x63);
    tft_port_write_dat8(0x18);
    tft_port_write_dat8(0x11);
    tft_port_write_dat8(0x71);
    tft_port_write_dat8(0xF1);
    tft_port_write_dat8(0x70);
    tft_port_write_dat8(0x70);
    tft_port_write_dat8(0x18);
    tft_port_write_dat8(0x13);
    tft_port_write_dat8(0x71);
    tft_port_write_dat8(0xF3);
    tft_port_write_dat8(0x70);
    tft_port_write_dat8(0x70);

    tft_port_write_cmd(0x64);
    tft_port_write_dat8(0x28);
    tft_port_write_dat8(0x29);
    tft_port_write_dat8(0xF1);
    tft_port_write_dat8(0x01);
    tft_port_write_dat8(0xF1);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x07);

    tft_port_write_cmd(0x66);
    tft_port_write_dat8(0x3C);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0xCD);
    tft_port_write_dat8(0x67);
    tft_port_write_dat8(0x45);
    tft_port_write_dat8(0x45);
    tft_port_write_dat8(0x10);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x00);

    tft_port_write_cmd(0x67);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x3C);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x01);
    tft_port_write_dat8(0x54);
    tft_port_write_dat8(0x10);
    tft_port_write_dat8(0x32);
    tft_port_write_dat8(0x98);

    tft_port_write_cmd(0x74);
    tft_port_write_dat8(0x10);
    tft_port_write_dat8(0x85);
    tft_port_write_dat8(0x80);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x00);
    tft_port_write_dat8(0x4E);
    tft_port_write_dat8(0x00);

    tft_port_write_cmd(0x98);
    tft_port_write_dat8(0x3e);
    tft_port_write_dat8(0x07);

    tft_port_write_cmd(0x35);
    tft_port_write_cmd(0x21);

    tft_port_write_cmd(0x11);
    tft_port_delay(120);
    tft_port_write_cmd(0x29);
    tft_port_delay(20);
}

void gc9a01_set_pos(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{

    tft_port_write_cmd(0x2a);
    tft_port_write_dat16(x1);
    tft_port_write_dat16(x2);

    tft_port_write_cmd(0x2b);
    tft_port_write_dat16(y1);
    tft_port_write_dat16(y2);

    tft_port_write_cmd(0x2c);
}

void gc9a01_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT))
    {
        return;
    }

    gc9a01_set_pos(x, y, x, y);

    tft_port_write_dat16(color);
}

void gc9a01_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{

    gc9a01_set_pos(x, y, x + w - 1, y + h - 1);

    for (uint32_t i = 0; i < w * h; i++)
    {
        tft_port_write_dat16(color);
    }
}
