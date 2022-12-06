#include "disp_driver.h"

void disp_driver_init(void)
{
#if defined PKG_DISPLAY_CONTROLLER_ILI9341
    ili9341_init();
#elif defined PKG_DISPLAY_CONTROLLER_ILI9481
    ili9481_init();
#elif defined PKG_DISPLAY_CONTROLLER_ILI9488
    ili9488_init();
#elif defined PKG_DISPLAY_CONTROLLER_ST7789
    st7789_init();
#elif defined PKG_DISPLAY_CONTROLLER_ST7796S
    st7796s_init();
#elif defined PKG_DISPLAY_CONTROLLER_ST7735S
    st7735s_init();
#elif defined PKG_DISPLAY_CONTROLLER_HX8357
    hx8357_init();
#elif defined PKG_DISPLAY_CONTROLLER_ILI9486
    ili9486_init();
#elif defined PKG_DISPLAY_CONTROLLER_SH1107
    sh1107_init();
#elif defined PKG_DISPLAY_CONTROLLER_SSD1306
    ssd1306_init();
#elif defined PKG_DISPLAY_CONTROLLER_FT81X
    FT81x_init();
#elif defined PKG_DISPLAY_CONTROLLER_IL3820
    il3820_init();
#elif defined PKG_DISPLAY_CONTROLLER_RA8875
    ra8875_init();
#elif defined PKG_DISPLAY_CONTROLLER_GC9A01
    GC9A01_init();
#elif defined PKG_DISPLAY_CONTROLLER_JD79653A
    jd79653a_init();
#elif defined PKG_DISPLAY_CONTROLLER_UC8151D
    uc8151d_init();
#elif defined PKG_DISPLAY_CONTROLLER_ILI9163C
    ili9163c_init();
#elif defined PKG_DISPLAY_CONTROLLER_PCD8544
    pcd8544_init();
#endif
}

void disp_driver_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
#if defined PKG_DISPLAY_CONTROLLER_ILI9341
    ili9341_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_ILI9481
    ili9481_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_ILI9488
    ili9488_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_ST7789
    st7789_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_ST7796S
    st7796s_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_ST7735S
    st7735s_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_HX8357
    hx8357_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_ILI9486
    ili9486_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_SH1107
    sh1107_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_SSD1306
    ssd1306_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_FT81X
    FT81x_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_IL3820
    il3820_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_RA8875
    ra8875_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_GC9A01
    GC9A01_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_JD79653A
    jd79653a_lv_fb_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_UC8151D
    uc8151d_lv_fb_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_ILI9163C
    ili9163c_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined PKG_DISPLAY_CONTROLLER_PCD8544
    pcd8544_fill(x_start, y_start, x_end, y_end, pcolor);
#endif
}
