#include "disp_driver.h"

#ifdef SSUD_DISP_CONTROLLER_ST7735S

void ssud_st7735s_init(void)
{
    lcd_init_cmd_t init_cmds[] = {
        {ST7735_SWRESET, {0}, 0x80},                               // Software reset, 0 args, w/delay 150
        {ST7735_SLPOUT, {0}, 0x80},                                // Out of sleep mode, 0 args, w/delay 500
        {ST7735_FRMCTR1, {0x01, 0x2C, 0x2D}, 3},                   // Frame rate ctrl - normal mode, 3 args: Rate = fosc/(1x2+40) * (LINE+2C+2D)
        {ST7735_FRMCTR2, {0x01, 0x2C, 0x2D}, 3},                   // Frame rate control - idle mode, 3 args:Rate = fosc/(1x2+40) * (LINE+2C+2D)
        {ST7735_FRMCTR3, {0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D}, 6}, // Frame rate ctrl - partial mode, 6 args:Dot inversion mode. Line inversion mode
        {ST7735_INVCTR, {0x07}, 1},                                // Display inversion ctrl, 1 arg, no delay:No inversion
        {ST7735_PWCTR1, {0xA2, 0x02, 0x84}, 3},                    // Power control, 3 args, no delay:-4.6V AUTO mode
        {ST7735_PWCTR2, {0xC5}, 1},                                // Power control, 1 arg, no delay:VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
        {ST7735_PWCTR3, {0x0A, 0x00}, 2},                          // Power control, 2 args, no delay: Opamp current small, Boost frequency
        {ST7735_PWCTR4, {0x8A, 0x2A}, 2},                          // Power control, 2 args, no delay: BCLK/2, Opamp current small & Medium low
        {ST7735_PWCTR5, {0x8A, 0xEE}, 2},                          // Power control, 2 args, no delay:
        {ST7735_VMCTR1, {0x0E}, 1},                                // Power control, 1 arg, no delay:
#ifdef SSUD_DISP_INVERT_COLORS
        {ST7735_INVON, {0}, 0}, // set inverted mode
#else
        {ST7735_INVOFF, {0}, 0}, // set non-inverted mode
#endif /* SSUD_DISP_INVERT_COLORS */
        {ST7735_COLMOD, {0x05}, 1},                                                                                             // set color mode, 1 arg, no delay: 16-bit color
        {ST7735_GMCTRP1, {0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2d, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10}, 16}, // 16 args, no delay:
        {ST7735_GMCTRN1, {0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10}, 16}, // 16 args, no delay:
        {ST7735_NORON, {0}, TFT_INIT_DELAY},                                                                                    // Normal display on, no args, w/delay 10 ms delay
        {ST7735_DISPON, {0}, TFT_INIT_DELAY},                                                                                   // Main screen turn on, no args w/delay 100 ms delay
        {0, {0}, 0xff}
    };

    // Send all the commands
    rt_uint16_t cmd = 0;
    while (init_cmds[cmd].databytes != 0xff)
    {
        ssud_spi_write_cmd(init_cmds[cmd].cmd);
        ssud_spi_write_data(init_cmds[cmd].data, init_cmds[cmd].databytes & 0x1F);
        if (init_cmds[cmd].databytes & 0x80)
        {
            rt_thread_mdelay(100);
        }
        cmd++;
    }

    ssud_st7735s_set_orientation(SSUD_DISP_ORIENTATION);
}

void ssud_st7735s_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
    rt_uint8_t data[4];

// For 160 x 80 display (BGR, inverted, 26 / 1 offset)
#if (SSUD_DISP_HOR_RES == 80) && (SSUD_DISP_VER_RES == 160)
    #if defined (SSUD_DISP_ORIENTATION_PORTRAIT) || defined (SSUD_DISP_ORIENTATION_PORTRAIT_INVERTED)
        x_start += 26;
        x_end += 26;
        y_start += 1;
        y_end += 1;
    #elif defined (SSUD_DISP_ORIENTATION_LANDSCAPE) || defined (SSUD_DISP_ORIENTATION_LANDSCAPE_INVERTED)
        x_start += 1;
        x_end += 1;
        y_start += 26;
        y_end += 26;
    #endif
#elif (SSUD_DISP_HOR_RES == 160) && (SSUD_DISP_VER_RES == 80)
    #if defined (SSUD_DISP_ORIENTATION_PORTRAIT) || defined (SSUD_DISP_ORIENTATION_PORTRAIT_INVERTED)
        x_start += 26;
        x_end += 26;
        y_start += 1;
        y_end += 1;
    #elif defined (SSUD_DISP_ORIENTATION_LANDSCAPE) || defined (SSUD_DISP_ORIENTATION_LANDSCAPE_INVERTED)
        x_start += 1;
        x_end += 1;
        y_start += 26;
        y_end += 26;
    #endif
#endif

    /*Column addresses*/
    ssud_spi_write_cmd(0x2A);
    data[0] = (x_start >> 8) & 0xFF;
    data[1] = (x_start & 0xFF) ;
    data[2] = (x_end >> 8) & 0xFF;
    data[3] = (x_end & 0xFF) ;
    ssud_spi_write_data(data, 4);

    /*Page addresses*/
    ssud_spi_write_cmd(0x2B);
    data[0] = (y_start >> 8) & 0xFF;
    data[1] = (y_start & 0xFF) ;
    data[2] = (y_end >> 8) & 0xFF;
    data[3] = (y_end & 0xFF) ;
    ssud_spi_write_data(data, 4);

    /*Memory write*/
    ssud_spi_write_cmd(ST7735_RAMWR);
    ssud_spi_write_color(x_start, y_start, x_end, y_end, pcolor);
}

void ssud_st7735s_set_orientation(rt_uint8_t orientation)
{
    /*
        Portrait:  0xC8 = ST77XX_MADCTL_MY| ST77XX_MADCTL_MX | ST77XX_MADCTL_RGB
        Portrait inverted:  0x08 = ST77XX_MADCTL_RGB
        Landscape: 0xA8 = ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB
        Landscape inverted: 0x68 = ST77XX_MADCTL_MX | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB
    */
    rt_uint8_t data[] = {0xC8, 0x08, 0xA8, 0x68};
    ssud_spi_write_cmd(ST7735_MADCTL);
    ssud_spi_write_data((void *)&data[orientation], 1);
}

#endif /* SSUD_DISP_CONTROLLER_ST7735S */
