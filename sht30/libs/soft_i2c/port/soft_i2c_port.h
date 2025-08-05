/********************************************************************************
 * @author: MonkeyPi
 * @website: makerinchina.cn
 * @date: 2022/8/21 10:30
 * @version: 0.1
 * @description:
 ********************************************************************************/

#ifndef TEMP_CONTROLER_SOFT_I2C_PORT_H
#define TEMP_CONTROLER_SOFT_I2C_PORT_H

#include <stdint.h>
#include <stdbool.h>

// #define _USE_PLATFORM_LIBOPENCM3_

#ifdef _USE_PLATFORM_LIBOPENCM3_

#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/rcc.h"

#define SOFT_I2C_SCL_CLOCK RCC_GPIOB
#define SOFT_I2C_SCL_PORT GPIOB
#define SOFT_I2C_SCL_PIN GPIO13

#define SOFT_I2C_SDA_CLOCK RCC_GPIOB
#define SOFT_I2C_SDA_PORT GPIOB
#define SOFT_I2C_SDA_PIN GPIO14

/* SCL = 1 */
static inline void soft_i2c_scl_set(void)
{
    gpio_set(SOFT_I2C_SCL_PORT, SOFT_I2C_SCL_PIN);
}

/* SCL = 0 */
static inline void soft_i2c_scl_clear(void)
{
    gpio_clear(SOFT_I2C_SCL_PORT, SOFT_I2C_SCL_PIN);
}

/* SDA = 1 */
static inline void soft_i2c_sda_set(void)
{
    gpio_set(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN);
}

/* SDA = 0 */
static inline void soft_i2c_sda_clear(void)
{
    gpio_clear(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN);
}

static inline void soft_i2c_delay(void)
{
    for (int i = 0; i < 40; i++)
    {
        __asm__ volatile("nop");
    }

    //    delay_ms(1);
}

static inline void soft_i2c_sda_set_input(void)
{
    gpio_mode_setup(SOFT_I2C_SDA_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, SOFT_I2C_SDA_PIN);
}

static inline void soft_i2c_sda_set_output(void)
{
    gpio_mode_setup(SOFT_I2C_SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SOFT_I2C_SDA_PIN);
}

static inline bool soft_i2c_sda_read_input(void)
{
    return gpio_get(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN) ? true : false;
}

#else

// us hal
#include <stm32g0xx_hal.h>

#define SOFT_I2C_SCL_CLOCK_EN __HAL_RCC_GPIOB_CLK_ENABLE
#define SOFT_I2C_SCL_PORT GPIOB
#define SOFT_I2C_SCL_PIN GPIO_PIN_6

#define SOFT_I2C_SDA_CLOCK_EN __HAL_RCC_GPIOB_CLK_ENABLE
#define SOFT_I2C_SDA_PORT GPIOB
#define SOFT_I2C_SDA_PIN GPIO_PIN_7

/* SCL = 1 */
static inline void soft_i2c_scl_set(void)
{
    HAL_GPIO_WritePin(SOFT_I2C_SCL_PORT, SOFT_I2C_SCL_PIN, GPIO_PIN_SET);
}

/* SCL = 0 */
static inline void soft_i2c_scl_clear(void)
{
    HAL_GPIO_WritePin(SOFT_I2C_SCL_PORT, SOFT_I2C_SCL_PIN, GPIO_PIN_RESET);
}

/* SDA = 1 */
static inline void soft_i2c_sda_set(void)
{
    HAL_GPIO_WritePin(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN, GPIO_PIN_SET);
}

/* SDA = 0 */
static inline void soft_i2c_sda_clear(void)
{
    HAL_GPIO_WritePin(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN, GPIO_PIN_RESET);
}

static inline void soft_i2c_delay(void)
{
    for (int i = 0; i < 13; i++)
    {
        __asm__ volatile("nop");
    }

    //    delay_ms(1);
}

static inline void soft_i2c_sda_set_input(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = SOFT_I2C_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SOFT_I2C_SDA_PORT, &GPIO_InitStruct);
}

static inline void soft_i2c_sda_set_output(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = SOFT_I2C_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SOFT_I2C_SDA_PORT, &GPIO_InitStruct);
}

static inline bool soft_i2c_sda_read_input(void)
{
    return (HAL_GPIO_ReadPin(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN) == GPIO_PIN_SET) ? true : false;
}

#endif

#endif // TEMP_CONTROLER_SOFT_I2C_PORT_H
