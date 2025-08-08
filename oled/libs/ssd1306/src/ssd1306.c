/**
 * @file ssd1306.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2025-08-06
 *
 * @copyright Copyright (c) 2025
 *
 * @brief
 */

#include "ssd1306.h"
#include <string.h>

#include "i2c.h"

// OLED definitions
#define OLED_ADDR 0x78     // OLED write address (0x3C << 1)
#define OLED_CMD_MODE 0x00 // set command mode
#define OLED_DAT_MODE 0x40 // set data mode

// OLED commands
#define OLED_COLUMN_LOW 0x00  // set lower 4 bits of start column (0x00 - 0x0F)
#define OLED_COLUMN_HIGH 0x10 // set higher 4 bits of start column (0x10 - 0x1F)
#define OLED_MEMORYMODE 0x20  // set memory addressing mode (following byte)
#define OLED_COLUMNS 0x21     // set start and end column (following 2 bytes)
#define OLED_PAGES 0x22       // set start and end page (following 2 bytes)
#define OLED_SCROLL_OFF 0x2E  // deactivate scroll command
#define OLED_STARTLINE 0x40   // set display start line (0x40-0x7F = 0-63)
#define OLED_CONTRAST 0x81    // set display contrast (following byte)
#define OLED_CHARGEPUMP 0x8D  // (following byte - 0x14:enable, 0x10: disable)
#define OLED_XFLIP_OFF 0xA0   // don't flip display horizontally
#define OLED_XFLIP 0xA1       // flip display horizontally
#define OLED_INVERT_OFF 0xA6  // set non-inverted display
#define OLED_INVERT 0xA7      // set inverse display
#define OLED_MULTIPLEX 0xA8   // set multiplex ratio (following byte)
#define OLED_DISPLAY_OFF 0xAE // set display off (sleep mode)
#define OLED_DISPLAY_ON 0xAF  // set display on
#define OLED_PAGE 0xB0        // set start page (following byte)
#define OLED_YFLIP_OFF 0xC0   // don't flip display vertically
#define OLED_YFLIP 0xC8       // flip display vertically
#define OLED_OFFSET 0xD3      // set display offset (y-scroll: following byte)
#define OLED_COMPINS 0xDA     // set COM pin config (following byte)

// OLED initialisation sequence
const uint8_t OLED_INIT_CMD[] = {
    OLED_MULTIPLEX, 0x3F,     // set multiplex ratio
    OLED_CHARGEPUMP, 0x14,    // set DC-DC enable
    OLED_MEMORYMODE, 0x00,    // set horizontal addressing mode
    OLED_COLUMNS, 0x00, 0x7F, // set start and end column
    OLED_PAGES, 0x00, 0x3F,   // set start and end page
    OLED_COMPINS, 0x12,       // set com pins
    OLED_XFLIP, OLED_YFLIP,   // flip screen
    OLED_DISPLAY_ON           // display on
};

static void ssd1306_write_cmd(uint8_t cmd)
{
    uint8_t buff[2] = {OLED_CMD_MODE, cmd};

    HAL_I2C_Master_Transmit(&hi2c2, OLED_ADDR, buff, 2, HAL_MAX_DELAY);
}

static void ssd1306_write_data(uint8_t *pdata, uint16_t len)
{
    HAL_I2C_Mem_Write(&hi2c2, OLED_ADDR, OLED_DAT_MODE, I2C_MEMADD_SIZE_8BIT, pdata, len, HAL_MAX_DELAY);
}

void ssd1306_init(void)
{
    for (uint32_t i = 0; i < sizeof(OLED_INIT_CMD); i++)
    {
        ssd1306_write_cmd(OLED_INIT_CMD[i]);
    }
}

void ssd1306_set_pos(uint8_t x, uint8_t y)
{
    ssd1306_write_cmd(OLED_PAGE | y);
    ssd1306_write_cmd(x & 0x0f);
    ssd1306_write_cmd(OLED_COLUMN_HIGH | (x >> 4));
}

void ssd1306_test_bar()
{

    static uint8_t mem_buff[8][128];

    // clear
    memset(mem_buff, 0, sizeof(mem_buff));

    for (uint8_t x = 0; x < 8; x++)
    {
        // set cloumn 0-63
        for (uint8_t i = 0; i < 64; i++)
        {
            mem_buff[x][i] = 0x0f;
        }
        // set column 64-127
        for (uint8_t i = 64; i < 128; i++)
        {
            mem_buff[x][i] = 0xf0;
        }
    }

    // write to all
    for (uint8_t i = 0; i < 8; i++)
    {
        ssd1306_set_pos(0, i);
        ssd1306_write_data(mem_buff[i], 128);
    }
}
