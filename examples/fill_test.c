#include "disp_driver.h"

static int fill_test(int argc, char **argv)
{
    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = RED;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    backlight_light_set(atoi(argv[1]));
    disp_driver_fill(0, 0, 239, 239, &color1);
    disp_driver_fill(0, 0, 119, 119, &color2);
    disp_driver_fill(120, 120, 239, 239, &color3);
    disp_driver_fill(60, 60, 179, 179, &color4);
    return 0;
}

MSH_CMD_EXPORT(fill_test, fill_test);
