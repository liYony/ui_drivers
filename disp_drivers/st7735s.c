#include "disp_driver.h"

#ifdef PKG_DISPLAY_CONTROLLER_ST7735S
#include "st7735s.h"

rt_uint8_t st7735s_portrait_mode = 0;

void st7735s_init(void)
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
#if ST7735S_INVERT_COLORS == 1
        {ST7735_INVON, {0}, 0}, // set inverted mode
#else
        {ST7735_INVOFF, {0}, 0}, // set non-inverted mode
#endif
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
        spi_write_cmd(init_cmds[cmd].cmd);
        spi_write_data(init_cmds[cmd].data, init_cmds[cmd].databytes & 0x1F);
        if (init_cmds[cmd].databytes & 0x80)
        {
            rt_thread_delay(RT_TICK_PER_SECOND / 10);
        }
        cmd++;
    }

#if (PKG_INDEX_DISPLAY_ORIENTATION == 0) || (PKG_INDEX_DISPLAY_ORIENTATION == 1)
    st7735s_portrait_mode = 1;
#else
    st7735s_portrait_mode = 0;
#endif

    st7735s_set_orientation(PKG_INDEX_DISPLAY_ORIENTATION);
}

void st7735s_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
    rt_uint8_t data[4];

    /*Column addresses*/
    spi_write_cmd(0x2A);
    data[0] = (x_start >> 8) & 0xFF;
    data[1] = (x_start & 0xFF) + (st7735s_portrait_mode ? COLSTART : ROWSTART);
    data[2] = (x_end >> 8) & 0xFF;
    data[3] = (x_end & 0xFF) + (st7735s_portrait_mode ? COLSTART : ROWSTART);
    spi_write_data(data, 4);

    /*Page addresses*/
    spi_write_cmd(0x2B);
    data[0] = (y_start >> 8) & 0xFF;
    data[1] = (y_start & 0xFF) + (st7735s_portrait_mode ? ROWSTART : COLSTART);
    data[2] = (y_end >> 8) & 0xFF;
    data[3] = (y_end & 0xFF) + (st7735s_portrait_mode ? ROWSTART : COLSTART);
    spi_write_data(data, 4);

    /*Memory write*/
    spi_write_cmd(ST7735_RAMWR);
    spi_write_color(x_start, y_start, x_end, y_end, pcolor);
}

void st7735s_set_orientation(rt_uint8_t orientation)
{
    /*
        Portrait:  0xC8 = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST77XX_MADCTL_BGR
        Landscape: 0xA8 = ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST77XX_MADCTL_BGR
        Remark: "inverted" is ignored here
    */
    rt_uint8_t data[] = {0xC8, 0xC8, 0xA8, 0xA8};
    spi_write_cmd(ST7735_MADCTL);
    spi_write_data((void *)&data[orientation], 1);
}

#endif /* PKG_DISPLAY_CONTROLLER_ST7735S */
