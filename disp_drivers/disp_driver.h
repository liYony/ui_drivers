#ifndef __DISP_DRIVER_H_
#define __DISP_DRIVER_H_

#include <rtdevice.h>
#include <rtthread.h>
#include "spi_port.h"
#include "backlight_port.h"

#if defined SSUD_DISP_CONTROLLER_ILI9341
#include "ili9341.h"
#elif defined SSUD_DISP_CONTROLLER_ILI9481
#include "ili9481.h"
#elif defined SSUD_DISP_CONTROLLER_ILI9488
#include "ili9488.h"
#elif defined SSUD_DISP_CONTROLLER_ST7789
#include "st7789.h"
#elif defined SSUD_DISP_CONTROLLER_ST7796S
#include "st7796s.h"
#elif defined SSUD_DISP_CONTROLLER_ST7735S
#include "st7735s.h"
#elif defined SSUD_DISP_CONTROLLER_HX8357
#include "hx8357.h"
#elif defined SSUD_DISP_CONTROLLER_ILI9486
#include "ili9486.h"
#elif defined SSUD_DISP_CONTROLLER_SH1107
#include "sh1107.h"
#elif defined SSUD_DISP_CONTROLLER_SSD1306
#include "ssd1306.h"
#elif defined SSUD_DISP_CONTROLLER_FT81X
#include "FT81x.h"
#elif defined SSUD_DISP_CONTROLLER_IL3820
#include "il3820.h"
#elif defined SSUD_DISP_CONTROLLER_RA8875
#include "ra8875.h"
#elif defined SSUD_DISP_CONTROLLER_GC9A01
#include "GC9A01.h"
#elif defined SSUD_DISP_CONTROLLER_JD79653A
#include "jd79653a.h"
#elif defined SSUD_DISP_CONTROLLER_UC8151D
#include "uc8151d.h"
#elif defined SSUD_DISP_CONTROLLER_ILI9163C
#include "ili9163c.h"
#elif defined SSUD_DISP_CONTROLLER_PCD8544
#include "pcd8544.h"
#endif

#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN            0XBC40
#define BRRED            0XFC07
#define GRAY             0X8430
#define GRAY175          0XAD75
#define GRAY151          0X94B2
#define GRAY187          0XBDD7
#define GRAY240          0XF79E

typedef struct
{
    rt_uint8_t cmd;
    rt_uint8_t data[16];
    rt_uint8_t databytes; // No of data in data; bit 7 = delay after set; 0xFF = end of cmds.
} lcd_init_cmd_t;

void ssud_disp_driver_init(void);
void ssud_disp_driver_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor);

#endif // !__DISP_DRIVER_H_
