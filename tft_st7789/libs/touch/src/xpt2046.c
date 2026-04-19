/**
 * @file xpt2046.c
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-14
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#include "xpt2046.h"
#include "log.h"

void xpt2046_init()
{
    touch_port_init();
}

bool xpt2046_touched()
{
    return touch_get_pen();
}

static uint16_t xpt2046_read_ad(uint8_t cmd)
{
    uint8_t cmd_xy[3] = {cmd, 0x00, 0x00};
    uint8_t res_xy[3] = {0};

    // dumy read noisy ignore
    touch_read(cmd_xy, res_xy, 3);

    // get xy ad
    touch_read(cmd_xy, res_xy, 3);
    uint16_t raw_ad = ((res_xy[1] << 8) | res_xy[2]) >> 3; // only 12bit

    // log_info("ad:%d", raw_ad);

    return raw_ad;
}

static uint16_t xpt2046_filter_ad(uint8_t cmd)
{
    uint16_t sample_buff[SAMPLE_TIMES] = {0};
    for (uint8_t i = 0; i < SAMPLE_TIMES; i++)
    {
        sample_buff[i] = xpt2046_read_ad(cmd);
    }
    uint16_t sum = 0;
    uint16_t tmp = 0;
    for (uint16_t i = 0; i < SAMPLE_TIMES - 1; i++)
    {
        for (uint16_t j = i + 1; j < SAMPLE_TIMES; j++)
        {
            if (sample_buff[i] > sample_buff[j])
            {
                tmp = sample_buff[i];
                sample_buff[i] = sample_buff[j];
                sample_buff[j] = tmp;
            }
        }
    }
    // get range (1,sample-1), lost min,max
    for (uint16_t i = 1; i < SAMPLE_TIMES - 1; i++)
    {
        sum += sample_buff[i];
    }

    uint16_t value = sum / (SAMPLE_TIMES - 2);

    // log_debug("ad=%d", value);

    return value;
}

#define ERR_RANGE 50
#define ADC_MIN_VAL 100
#define ADC_MAX_VAL 4000
#define ZPRESS_THRESHOLD 150
bool xpt2046_read_xy(uint16_t *x, uint16_t *y)
{
    // z press
    uint16_t z1 = xpt2046_read_ad(XPT2046_CMD_Z1POS);
    uint16_t z2 = xpt2046_read_ad(XPT2046_CMD_Z2POS);
    // from XPT2046_Touchscreen
    int16_t z = z1 + 4095 - z2;
    if (z < ZPRESS_THRESHOLD)
    {
        return false;
    }

    uint16_t px1 = xpt2046_filter_ad(XPT2046_CMD_XPOS);
    uint16_t py1 = xpt2046_filter_ad(XPT2046_CMD_YPOS);

    uint16_t px2 = xpt2046_filter_ad(XPT2046_CMD_XPOS);
    uint16_t py2 = xpt2046_filter_ad(XPT2046_CMD_YPOS);

    if ((((px2 <= px1) && (px1 < px2 + ERR_RANGE)) || ((px1 <= px2) && (px2 < px1 + ERR_RANGE))) && (((py2 <= py1) && (py1 < py2 + ERR_RANGE)) || ((py1 <= py2) && (py2 < py1 + ERR_RANGE))))
    {
        *x = (px1 + px2) / 2;
        *y = (py1 + py2) / 2;

        if ((*x < ADC_MIN_VAL) || (*x > ADC_MAX_VAL) || (*y < ADC_MIN_VAL) || (*y > ADC_MAX_VAL))
        {
            // log_error("adc out of range, %d, %d", *x, *y);
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool xpt2046_get_pos(uint16_t *x, uint16_t *y)
{

    // with factory adjust map
    float xfac = 0.0651714;
    short xoff = -13;
    float yfac = 0.087914;
    short yoff = -10;

    uint16_t px = 0;
    uint16_t py = 0;

    bool ret = xpt2046_read_xy(&px, &py);

    // log_debug("raw:%d, %d", px, py);

    *x = xfac * px + xoff;
    *y = yfac * py + yoff;

    return ret;
}