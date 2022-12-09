#include "disp_driver.h"

static int fill_test(int argc, char **argv)
{
    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = RED;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    rt_uint16_t xend, yend;
#if defined(PKG_DISP_BACKLIGHT_SWITCH) || defined(PKG_DISP_BACKLIGHT_PWM)
    backlight_light_set(atoi(argv[1]));
#endif

#if defined(PKG_DISPLAY_ORIENTATION_PORTRAIT) || defined(PKG_DISPLAY_ORIENTATION_PORTRAIT_INVERTED)
    xend = PKG_DISPLAY_HOR_RES_MAX > PKG_DISPLAY_VER_RES_MAX ? PKG_DISPLAY_VER_RES_MAX :PKG_DISPLAY_HOR_RES_MAX; 
    yend = PKG_DISPLAY_HOR_RES_MAX > PKG_DISPLAY_VER_RES_MAX ? PKG_DISPLAY_HOR_RES_MAX :PKG_DISPLAY_VER_RES_MAX; 
#elif defined(PKG_DISPLAY_ORIENTATION_LANDSCAPE) || defined(PKG_DISPLAY_ORIENTATION_LANDSCAPE_INVERTED)
    xend = PKG_DISPLAY_HOR_RES_MAX > PKG_DISPLAY_VER_RES_MAX ? PKG_DISPLAY_HOR_RES_MAX :PKG_DISPLAY_VER_RES_MAX;
    yend = PKG_DISPLAY_HOR_RES_MAX > PKG_DISPLAY_VER_RES_MAX ? PKG_DISPLAY_VER_RES_MAX :PKG_DISPLAY_HOR_RES_MAX; 
#endif

    disp_driver_fill(0, 0, xend-1, yend-1, &color1);
    disp_driver_fill(0, 0, xend/2-1, yend/2-1, &color2);
    disp_driver_fill(xend/2, yend/2, xend-1, yend-1, &color3);
    disp_driver_fill(xend/4, yend/4, xend/4*3-1, yend/4*3-1, &color4);
    return 0;
}

MSH_CMD_EXPORT(fill_test, fill_test);
