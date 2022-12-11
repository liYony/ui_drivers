#include "disp_driver.h"

#ifdef SSUD_DISP_CONTROLLER_ST7789

void ssud_st7789_init(void)
{
    lcd_init_cmd_t st7789_init_cmds[] = {
        {0xCF, {0x00, 0x83, 0X30}, 3},
        {0xED, {0x64, 0x03, 0X12, 0X81}, 4},
        {ST7789_PWCTRL2, {0x85, 0x01, 0x79}, 3},
        {0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
        {0xF7, {0x20}, 1},
        {0xEA, {0x00, 0x00}, 2},
        {ST7789_LCMCTRL, {0x26}, 1},
        {ST7789_IDSET, {0x11}, 1},
        {ST7789_VCMOFSET, {0x35, 0x3E}, 2},
        {ST7789_CABCCTRL, {0xBE}, 1},
        {ST7789_MADCTL, {0x00}, 1}, // Set to 0x28 if your display is flipped
        {ST7789_COLMOD, {0x55}, 1},

#ifdef SSUD_DISP_INVERT_COLORS
        {ST7789_INVON, {0}, 0}, // set inverted mode
#else
        {ST7789_INVOFF, {0}, 0}, // set non-inverted mode
#endif /* SSUD_DISP_INVERT_COLORS */

        {ST7789_RGBCTRL, {0x00, 0x1B}, 2},
        {0xF2, {0x08}, 1},
        {ST7789_GAMSET, {0x01}, 1},
        {ST7789_PVGAMCTRL, {0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x32, 0x44, 0x42, 0x06, 0x0E, 0x12, 0x14, 0x17}, 14},
        {ST7789_NVGAMCTRL, {0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x31, 0x54, 0x47, 0x0E, 0x1C, 0x17, 0x1B, 0x1E}, 14},
        {ST7789_CASET, {0x00, 0x00, 0x00, 0xEF}, 4},
        {ST7789_RASET, {0x00, 0x00, 0x01, 0x3f}, 4},
        {ST7789_RAMWR, {0}, 0},
        {ST7789_GCTRL, {0x07}, 1},
        {0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
        {ST7789_SLPOUT, {0}, 0x80},
        {ST7789_DISPON, {0}, 0x80},
        {0, {0}, 0xff},
    };

#if defined(SSUD_DISP_SOFT_RESET)
    ssud_spi_write_cmd(ST7789_SWRESET);
#endif

    rt_uint16_t cmd = 0;
    while (st7789_init_cmds[cmd].databytes != 0xff)
    {
        ssud_spi_write_cmd(st7789_init_cmds[cmd].cmd);
        ssud_spi_write_data(st7789_init_cmds[cmd].data, st7789_init_cmds[cmd].databytes & 0x1F);
        if (st7789_init_cmds[cmd].databytes & 0x80)
        {
            rt_thread_delay(RT_TICK_PER_SECOND / 10);
        }
        cmd++;
    }
    
    ssud_st7789_set_orientation(SSUD_DISP_ORIENTATION);
}

void ssud_st7789_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
    rt_uint8_t data[4];

#if (SSUD_DISP_HOR_RES == 240) && (SSUD_DISP_VER_RES == 240)
    #if defined (SSUD_DISP_ORIENTATION_PORTRAIT)
        x_start += 80;
        x_end += 80;
    #elif defined (SSUD_DISP_ORIENTATION_LANDSCAPE_INVERTED)
        y_start += 80;
        y_end += 80;
    #endif
#elif (SSUD_DISP_HOR_RES == 240) && (SSUD_DISP_VER_RES == 135)
    #if defined (SSUD_DISP_ORIENTATION_PORTRAIT) || \
        (SSUD_DISP_ORIENTATION_PORTRAIT_INVERTED)
        x_start += 40;
        x_end += 40;
        y_start += 53;
        y_end += 53;
    #endif
#elif (SSUD_DISP_HOR_RES == 135) && (SSUD_DISP_VER_RES == 240)
    #if defined (SSUD_DISP_ORIENTATION_LANDSCAPE) || \
        (SSUD_DISP_ORIENTATION_LANDSCAPE_INVERTED)
        x_start += 52;
        x_end += 52;
        y_start += 40;
        y_end += 40;
    #endif
#endif

    /*Column addresses*/
    ssud_spi_write_cmd(0x2A);
    data[0] = (x_start >> 8) & 0xFF;
    data[1] = (x_start & 0xFF);
    data[2] = (x_end >> 8) & 0xFF;
    data[3] = (x_end & 0xFF);
    ssud_spi_write_data(data, 4);

    /*Page addresses*/
    ssud_spi_write_cmd(0x2B);
    data[0] = (y_start >> 8) & 0xFF;
    data[1] = (y_start & 0xFF);
    data[2] = (y_end >> 8) & 0xFF;
    data[3] = (y_end & 0xFF);
    ssud_spi_write_data(data, 4);

    /*Memory write*/
    ssud_spi_write_cmd(ST7789_RAMWR);
    ssud_spi_write_color(x_start, y_start, x_end, y_end, pcolor);
}

void ssud_st7789_set_orientation(rt_uint8_t orientation)
{
    rt_uint8_t data[] = {0xC0, 0x00, 0x60, 0xA0};
    ssud_spi_write_cmd(ST7789_MADCTL);
    ssud_spi_write_data((void *)&data[orientation], 1);
}

#endif /* SSUD_DISP_CONTROLLER_ST7789 */
