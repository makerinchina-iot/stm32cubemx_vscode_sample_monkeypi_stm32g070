/**
 * @file touch_port.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-14
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#ifndef _TOUCH_PORT_HEAD_H_
#define _TOUCH_PORT_HEAD_H_

// include dependencies file here
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void touch_port_init();
    void touch_port_delay(uint32_t ms);
    void touch_port_select();
    void touch_port_release();
    bool touch_get_pen();
    uint8_t touch_read(uint8_t *tx, uint8_t *rx, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif //!_TOUCH_PORT_HEAD_H_