/**
 * @file xpt2046.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-14
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#ifndef _XPT2046_HEAD_H_
#define _XPT2046_HEAD_H_

// include dependencies file here
#include "touch_port.h"

#define XPT2046_CMD_XPOS 0xd0
#define XPT2046_CMD_YPOS 0x90
#define XPT2046_CMD_Z1POS 0xb0
#define XPT2046_CMD_Z2POS 0xc0

#define SAMPLE_TIMES 5

#ifdef __cplusplus
extern "C"
{
#endif

    void xpt2046_init();
    bool xpt2046_touched();
    bool xpt2046_read_xy(uint16_t *x, uint16_t *y);
    bool xpt2046_get_pos(uint16_t *x, uint16_t *y);

#ifdef __cplusplus
}
#endif

#endif //!_XPT2046_HEAD_H_