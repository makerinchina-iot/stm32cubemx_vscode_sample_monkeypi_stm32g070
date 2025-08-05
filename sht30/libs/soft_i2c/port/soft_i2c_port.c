/********************************************************************************
 * @author: MonkeyPi
 * @website: makerinchina.cn
 * @date: 2022/8/21 10:30
 * @version: 0.1
 * @description:
 ********************************************************************************/

#include "soft_i2c_port.h"

void soft_i2c_init(void)
{

#ifdef _USE_PLATFORM_LIBOPENCM3_
    /* 打开GPIO时钟 */
    rcc_periph_clock_enable(SOFT_I2C_SCL_CLOCK);
    rcc_periph_clock_enable(SOFT_I2C_SDA_CLOCK);

    /* 禁用默认上拉，使SCL, SDA保持高阻状态 */
    gpio_mode_setup(SOFT_I2C_SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SOFT_I2C_SCL_PIN);
    gpio_mode_setup(SOFT_I2C_SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SOFT_I2C_SDA_PIN);
    // gpio_set_output_options(SOFT_I2C_SCL_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_2MHZ, SOFT_I2C_SCL_PIN);
    gpio_set_output_options(SOFT_I2C_SDA_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_2MHZ, SOFT_I2C_SDA_PIN);

    /* 设置SCL, SDA为输出 */
    gpio_set(SOFT_I2C_SCL_PORT, SOFT_I2C_SCL_PIN);
    gpio_set(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN);

#else
    /* 打开GPIO时钟 */
    SOFT_I2C_SCL_CLOCK_EN();
    SOFT_I2C_SDA_CLOCK_EN();

    /* 设置SCL, SDA为输出 */

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = SOFT_I2C_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(SOFT_I2C_SCL_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SOFT_I2C_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(SOFT_I2C_SDA_PORT, &GPIO_InitStruct);

#endif

    /* 拉高SCL和SDA */
    soft_i2c_scl_set();
    soft_i2c_sda_set();
}
