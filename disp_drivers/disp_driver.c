#include "disp_driver.h"

void ssud_disp_driver_init(void)
{
#if defined SSUD_DISP_CONTROLLER_ILI9341
    ssud_ili9341_init();
#elif defined SSUD_DISP_CONTROLLER_ILI9481
    ssud_ili9481_init();
#elif defined SSUD_DISP_CONTROLLER_ILI9488
    ssud_ili9488_init();
#elif defined SSUD_DISP_CONTROLLER_ST7789
    ssud_st7789_init();
#elif defined SSUD_DISP_CONTROLLER_ST7796S
    ssud_st7796s_init();
#elif defined SSUD_DISP_CONTROLLER_ST7735S
    ssud_st7735s_init();
#elif defined SSUD_DISP_CONTROLLER_HX8357
    ssud_hx8357_init();
#elif defined SSUD_DISP_CONTROLLER_ILI9486
    ssud_ili9486_init();
#elif defined SSUD_DISP_CONTROLLER_SH1107
    ssud_sh1107_init();
#elif defined SSUD_DISP_CONTROLLER_SSD1306
    ssud_ssd1306_init();
#elif defined SSUD_DISP_CONTROLLER_FT81X
    ssud_FT81x_init();
#elif defined SSUD_DISP_CONTROLLER_IL3820
    ssud_il3820_init();
#elif defined SSUD_DISP_CONTROLLER_RA8875
    ssud_ra8875_init();
#elif defined SSUD_DISP_CONTROLLER_GC9A01
    ssud_GC9A01_init();
#elif defined SSUD_DISP_CONTROLLER_JD79653A
    ssud_jd79653a_init();
#elif defined SSUD_DISP_CONTROLLER_UC8151D
    ssud_uc8151d_init();
#elif defined SSUD_DISP_CONTROLLER_ILI9163C
    ssud_ili9163c_init();
#elif defined SSUD_DISP_CONTROLLER_PCD8544
    ssud_pcd8544_init();
#endif
}

void ssud_disp_driver_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
#if defined SSUD_DISP_CONTROLLER_ILI9341
    ssud_ili9341_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ILI9481
    ssud_ili9481_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ILI9488
    ssud_ili9488_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ST7789
    ssud_st7789_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ST7796S
    ssud_st7796s_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ST7735S
    ssud_st7735s_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_HX8357
    ssud_hx8357_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ILI9486
    ssud_ili9486_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_SH1107
    ssud_sh1107_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_SSD1306
    ssud_ssd1306_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_FT81X
    ssud_FT81x_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_IL3820
    ssud_il3820_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_RA8875
    ssud_ra8875_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_GC9A01
    ssud_GC9A01_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_JD79653A
    ssud_jd79653a_lv_fb_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_UC8151D
    ssud_uc8151d_lv_fb_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ILI9163C
    ssud_ili9163c_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_PCD8544
    ssud_pcd8544_fill(x_start, y_start, x_end, y_end, pcolor);
#endif
}
