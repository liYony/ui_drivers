#include "disp_driver.h"

static int fill_test(int argc, char **argv)
{
    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = GRAY;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    rt_uint16_t color5 = RED;
    rt_uint16_t xend, yend;
#if defined(SSUD_BACKLIGHT_SWITCH) || defined(SSUD_BACKLIGHT_PWM)
    if (argc == 2)
    {
        ssud_backlight_light_set(atoi(argv[1]));
    }
    else
    {
        ssud_backlight_light_set(100);
    }
#endif

#if defined(SSUD_DISP_ORIENTATION_PORTRAIT) || defined(SSUD_DISP_ORIENTATION_PORTRAIT_INVERTED)
    xend = SSUD_DISP_HOR_RES > SSUD_DISP_VER_RES ? SSUD_DISP_VER_RES :SSUD_DISP_HOR_RES;
    yend = SSUD_DISP_HOR_RES > SSUD_DISP_VER_RES ? SSUD_DISP_HOR_RES :SSUD_DISP_VER_RES;
#elif defined(SSUD_DISP_ORIENTATION_LANDSCAPE) || defined(SSUD_DISP_ORIENTATION_LANDSCAPE_INVERTED)
    xend = SSUD_DISP_HOR_RES > SSUD_DISP_VER_RES ? SSUD_DISP_HOR_RES :SSUD_DISP_VER_RES;
    yend = SSUD_DISP_HOR_RES > SSUD_DISP_VER_RES ? SSUD_DISP_VER_RES :SSUD_DISP_HOR_RES;
#endif

    ssud_disp_driver_fill(0, 0, xend-1, yend-1, &color1);
    ssud_disp_driver_fill(0, 0, xend/2-1, yend/2-1, &color2);
    ssud_disp_driver_fill(xend/2, yend/2, xend-1, yend-1, &color3);
    ssud_disp_driver_fill(xend/4, yend/4, xend/4*3-1, yend/4*3-1, &color4);

    ssud_disp_driver_fill(0, 0, 0, yend-1, &color5);
    ssud_disp_driver_fill(0, 0, xend-1, 0, &color5);
    ssud_disp_driver_fill(xend-1, 0, xend-1, yend-1, &color5);
    ssud_disp_driver_fill(0, yend-1, xend-1, yend-1, &color5);

    ssud_disp_driver_fill(xend/8, yend/8, xend/4, yend/4, &color4);
    return 0;
}

MSH_CMD_EXPORT(fill_test, fill_test);
