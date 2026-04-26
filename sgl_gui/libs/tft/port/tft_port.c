/**
 * @file tft_port.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#include "tft_port.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
#define TFT_SPI_HANDLE (&hspi1)

void tft_port_set_speed()
{
    __HAL_SPI_DISABLE(TFT_SPI_HANDLE);

    TFT_SPI_HANDLE->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    HAL_SPI_Init(TFT_SPI_HANDLE);
    __HAL_SPI_ENABLE(TFT_SPI_HANDLE);
}

void tft_port_set_data_bits(uint8_t db)
{
    __HAL_SPI_DISABLE(TFT_SPI_HANDLE);

    if (db == 8)
    {
        TFT_SPI_HANDLE->Init.DataSize = SPI_DATASIZE_8BIT;
    }
    else
    {
        TFT_SPI_HANDLE->Init.DataSize = SPI_DATASIZE_16BIT;
    }
    HAL_SPI_Init(TFT_SPI_HANDLE);
    __HAL_SPI_ENABLE(TFT_SPI_HANDLE);
}

void tft_port_init()
{
    // hard reset
    HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET);
    HAL_Delay(150);
    HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET);
    HAL_Delay(150);
    HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET);
    HAL_Delay(150);

    // backlight
    HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_SET);
}

void tft_port_delay(uint32_t ms)
{
    HAL_Delay(ms);
}

void tft_port_select()
{
    tft_port_set_speed();

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

void tft_port_release()
{
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void tft_port_write_cmd(uint8_t cmd)
{
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(TFT_SPI_HANDLE, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
}
void tft_port_write_dat8(uint8_t dat)
{
    tft_port_select();
    HAL_SPI_Transmit(TFT_SPI_HANDLE, &dat, 1, HAL_MAX_DELAY);
    tft_port_release();
}
void tft_port_write_dat16(uint16_t dat)
{
    uint8_t buf[2] = {dat >> 8, dat & 0xff};

    tft_port_select();
    HAL_SPI_Transmit(TFT_SPI_HANDLE, buf, 2, HAL_MAX_DELAY);
    tft_port_release();
}

void tft_port_write_multi_dat8(uint8_t *dat, uint16_t len)
{
    // tft_port_set_data_bits(8);
    tft_port_select();
    HAL_SPI_Transmit(TFT_SPI_HANDLE, dat, len, HAL_MAX_DELAY);
    tft_port_release();
}

void tft_port_write_multi_dat16(uint8_t *dat, uint16_t len)
{
    tft_port_set_data_bits(16);
    tft_port_select();
    HAL_SPI_Transmit(TFT_SPI_HANDLE, dat, len, HAL_MAX_DELAY);
    tft_port_release();
    tft_port_set_data_bits(8);
}