/**
 * @file tft_port.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#ifndef _TFT_PORT_HEAD_H_
#define _TFT_PORT_HEAD_H_

// include dependencies file here

#include <stdint.h>
#include <stdbool.h>

#define TFT_WIDTH 240
#define TFT_HEIGHT 320

#ifdef __cplusplus
extern "C"
{
#endif

    void tft_port_init();
    void tft_port_delay(uint32_t ms);
    void tft_port_select();
    void tft_port_release();
    void tft_port_write_cmd(uint8_t cmd);
    void tft_port_write_dat8(uint8_t dat);
    void tft_port_write_dat16(uint16_t dat);
    void tft_port_write_multi_dat8(uint8_t *dat, uint16_t len);
    void tft_port_write_multi_dat16(uint8_t *dat, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif //!_TFT_PORT_HEAD_H_