/**
 * @file tft_color.h
 * @author MonkeyPi (makerinchina.cn)
 * @version 0.01
 * @date 2026-03-14
 *
 * @copyright Copyright (c) 2026
 *
 * @brief
 */

#ifndef _TFT_COLOR_HEAD_H_
#define _TFT_COLOR_HEAD_H_

// include dependencies file here

#ifdef __cplusplus
extern "C"
{
#endif

#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0xF81F
#define GRED 0xFFE0
#define GBLUE 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0xBC40      // 棕色
#define BRRED 0xFC07      // 棕红色
#define GRAY 0x8430       // 灰色
#define DARKBLUE 0x01CF   // 深蓝色
#define LIGHTBLUE 0x7D7C  // 浅蓝色
#define GRAYBLUE 0x5458   // 灰蓝色
#define LIGHTGREEN 0x841F // 浅绿色
#define LGRAY 0xC618      // 浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE 0xA651  // 浅灰蓝色(中间层颜色)
#define LBBLUE 0x2B12     // 浅棕蓝色(选择条目的反色)

#ifdef __cplusplus
}
#endif

#endif //!_TFT_COLOR_HEAD_H_