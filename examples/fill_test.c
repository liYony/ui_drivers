#include "disp_driver.h"

    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = GRAY;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    rt_uint16_t color5 = RED;
    rt_uint16_t color6 = WHITE;
    rt_uint16_t color7 = BLACK;
    rt_uint16_t xend, yend;
static int fill_test(int argc, char **argv)
{
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


static int clear_all(int argc, char **argv)
{
    int16_t i;
    rt_uint16_t colorx;
    if (argc == 2)
    {
        i=atoi(argv[1]);
        switch(i)
        {
            case 1:colorx=color1;break;
            case 2:colorx=color2;break;
            case 3:colorx=color3;break;
            case 4:colorx=color4;break;
            case 5:colorx=color5;break;
            case 6:colorx=color6;break;
            case 7:colorx=color7;break;
            default:
            break;

        }
        full_all(colorx);
    }
    else
    {
        full_all(color1);
    }
}
MSH_CMD_EXPORT(clear_all, clear_all);


static void point_tesr(void)
{
    lcd_point(10,10,color5);
}
MSH_CMD_EXPORT(point_tesr, point);


static void circle_line(void)
{
    draw_circle(40,80,40,color5);
    draw_line(0,80,80,100,color4);
}
MSH_CMD_EXPORT(circle_line, draw_circle);


