/********************************************************************************
 * @author: MonkeyPi
 * @website: makerinchina.cn
 * @date: 2022/8/21 9:46
 * @version: 0.1
 * @description:
 ********************************************************************************/

#include "soft_i2c.h"
#include "soft_i2c_port.h"

/**
 * @brief I2C总线启动信号
 */
static void soft_i2c_start(void)
{
    /* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
    soft_i2c_sda_set();
    soft_i2c_scl_set();
    soft_i2c_delay();
    soft_i2c_sda_clear();
    soft_i2c_delay();
    soft_i2c_scl_clear();
    soft_i2c_delay();
}

/**
 * @brief I2C总线停止信号
 */
static void soft_i2c_stop(void)
{
    /* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
    soft_i2c_sda_clear();
    soft_i2c_delay();
    soft_i2c_scl_set();
    soft_i2c_delay();
    soft_i2c_sda_set();
}

/**
 * @brief 向I2C总线设备发送1个字节
 * @param _ucByte 等待发送的字节
 */
static void soft_i2c_send_byte(uint8_t _ucByte)
{
    uint8_t i;

    /* 先发送字节的高位bit7 */
    for (i = 0; i < 8; i++)
    {
        soft_i2c_delay();
        soft_i2c_scl_clear();

        if (_ucByte & 0x80)
        {
            soft_i2c_sda_set();
        }
        else
        {
            soft_i2c_sda_clear();
        }

        soft_i2c_delay();
        soft_i2c_scl_set();

        _ucByte <<= 1; /* 左移一个bit */
    }
}

/**
 * @brief CPU产生一个时钟，并读取器件的ACK应答信号
 * @return 返回true表示正确应答，false表示无器件响应
 */
static bool soft_i2c_wait_ack(void)
{
    bool res;

    soft_i2c_delay();
    soft_i2c_scl_clear();

    soft_i2c_sda_set_input();

    soft_i2c_delay();
    soft_i2c_scl_set(); /* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
    soft_i2c_delay();
    if (soft_i2c_sda_read_input() == false)
    { /* CPU读取SDA口线状态 */
        res = true;
    }
    else
    {
        res = false;
    }
    soft_i2c_scl_clear();
    soft_i2c_sda_set_output();
    soft_i2c_delay();

    return res;
}

/**
 * @brief CPU产生一个ACK信号
 */
static void soft_i2c_ack(void)
{
    soft_i2c_sda_clear(); /* CPU驱动SDA = 0 */
    soft_i2c_delay();
    soft_i2c_scl_set(); /* CPU产生1个时钟 */
    soft_i2c_delay();
    soft_i2c_scl_clear();
    soft_i2c_delay();
    soft_i2c_sda_set(); /* CPU释放SDA总线 */
}

/**
 * @brief CPU产生1个NACK信号
 */
static void soft_i2c_nack(void)
{
    soft_i2c_sda_set(); /* CPU驱动SDA = 1 */
    soft_i2c_delay();
    soft_i2c_scl_set(); /* CPU产生1个时钟 */
    soft_i2c_delay();
    soft_i2c_scl_clear();
    soft_i2c_delay();
}

/**
 * @brief CPU从I2C总线设备读取8bit数据
 * 读1个字节，ack=1时，发送ACK，ack=0，发送nACK
 * @return
 */
static uint8_t soft_i2c_read_byte(unsigned char ack)
{
    uint8_t i;
    uint8_t value;

    /* 读到第1个bit为数据的bit7 */
    value = 0;
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        soft_i2c_scl_set();
        soft_i2c_delay();
        if (soft_i2c_sda_read_input() == true)
        {
            value++;
        }
        soft_i2c_scl_clear();
        soft_i2c_delay();
    }

    if (ack)
    {
        soft_i2c_ack(); // 发送ACK
    }
    else
    {
        soft_i2c_nack(); // 发送nACK
    }

    return value;
}

/* Function to setup and execute I2C transfer request */
bool soft_i2c_transfer(uint8_t dev_addr,
                       uint8_t *tx_buffer,
                       uint16_t tx_size,
                       uint8_t *rx_buffer,
                       uint16_t rx_size)
{
    uint16_t i;

    if (tx_size == 0 && rx_size == 0)
    {
        /* start */
        soft_i2c_start();

        /* address + read for test*/
        soft_i2c_send_byte(dev_addr << 1 | 1);

        if (soft_i2c_wait_ack() == false)
        {
            goto error_device_nack;
        }
    }

    if (tx_size > 0)
    {
        /* start */
        soft_i2c_start();
        /* address + write */
        soft_i2c_send_byte(dev_addr << 1);
        if (soft_i2c_wait_ack() == false)
        {
            goto error_device_nack;
        }
        /* write data */
        for (i = 0; i < tx_size; i++)
        {
            soft_i2c_send_byte(tx_buffer[i]);
            if (soft_i2c_wait_ack() == false)
            {
                goto error_device_nack;
            }
        }
    }
    if (rx_size > 0)
    {
        /* start */
        soft_i2c_start();
        /* address + read */
        soft_i2c_send_byte(dev_addr << 1 | 1);
        if (soft_i2c_wait_ack() == false)
        {
            goto error_device_nack;
        }
        /* read data */
        for (i = 0; i < rx_size; i++)
        {
            rx_buffer[i] = soft_i2c_read_byte(i + 1 < rx_size);
        }
    }
    soft_i2c_stop();
    return true;

error_device_nack:
    soft_i2c_stop();
    return false;
}
