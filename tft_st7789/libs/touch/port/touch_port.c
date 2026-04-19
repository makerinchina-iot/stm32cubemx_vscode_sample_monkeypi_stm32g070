/**
 * @file touch_port.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-14
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#include "touch_port.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
#define TOUCH_SPI_HANDLE (&hspi1)

void touch_port_set_speed()
{
    __HAL_SPI_DISABLE(TOUCH_SPI_HANDLE);

    TOUCH_SPI_HANDLE->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    HAL_SPI_Init(TOUCH_SPI_HANDLE);
    __HAL_SPI_ENABLE(TOUCH_SPI_HANDLE);
}

void touch_port_init()
{
}

void touch_port_delay(uint32_t ms)
{
    HAL_Delay(ms);
}

void touch_port_select()
{
    touch_port_set_speed();

    HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_RESET);
}

void touch_port_release()
{
    HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_SET);
}

bool touch_get_pen()
{
    return (HAL_GPIO_ReadPin(TP_INT_GPIO_Port, TP_INT_Pin) == GPIO_PIN_RESET);
}

uint8_t touch_read(uint8_t *tx, uint8_t *rx, uint16_t len)
{

    uint8_t ret = 0;

    touch_port_select();

    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(TOUCH_SPI_HANDLE, tx, rx, len, HAL_MAX_DELAY);

    touch_port_release();

    if (status == HAL_OK)
    {
        ret = 0;
    }
    else
    {
        ret = 1;
    }
}
