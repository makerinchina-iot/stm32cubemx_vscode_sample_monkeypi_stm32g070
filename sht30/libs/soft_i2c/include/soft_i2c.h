/********************************************************************************
 * @author: MonkeyPi
 * @website: makerinchina.cn
 * @date: 2022/8/21 9:46
 * @version: 0.1
 * @description:
 ********************************************************************************/

#ifndef TEMP_CONTROLER_SOFT_I2C_H
#define TEMP_CONTROLER_SOFT_I2C_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief init the soft i2c
 */
void soft_i2c_init();

/**
 * @brief i2c write and read function
 * @param dev_addr
 * @param tx_buffer
 * @param tx_size
 * @param rx_buffer
 * @param rx_size
 * @return
 */
bool soft_i2c_transfer(uint8_t dev_addr, uint8_t *tx_buffer, uint16_t tx_size, uint8_t *rx_buffer, uint16_t rx_size);

/**
 * @brief scan i2c device
 * @param from_addr
 * @param to_addr
 * @param callback
 * @param delay_cb
 */
void scan_i2c_bus(uint8_t from_addr, uint8_t to_addr,
                  void (*callback)(uint8_t address, bool result));

#endif // TEMP_CONTROLER_SOFT_I2C_H
