#include "disp_driver.h"

#ifdef SSUD_DISP_CONTROLLER_ILI9163C

void ssud_ili9163c_init(void)
{
    lcd_init_cmd_t ili_init_cmds[] = {
        {ILI9163C_SWRESET, {0}, 0x80},       // Software reset, 0 args, w/delay 120ms
        {ILI9163C_SLPOUT, {0}, 0x80},        // Out of sleep mode, 0 args, w/delay 5ms
        {ILI9163C_CMD_GAMST, {0x04}, 1},     // Gamma Curve
        {ILI9163C_FRMCTR1, {0x0C, 0x14}, 2}, // Frame rate ctrl - normal mode
        {ILI9163C_INVCTR, {0x07}, 1},        // Display inversion ctrl, 1 arg, no delay:No inversion
        {ILI9163C_PWCTR1, {0x0C, 0x05}, 2},  // Power control, 2 args, no delay
        {ILI9163C_PWCTR2, {0x02}, 1},        // Power control, 1 arg
        {ILI9163C_PWCTR3, {0x02}, 1},        // Power control, 1 arg
        {ILI9163C_VMCTR1, {0x20, 0x55}, 2},  // Power control, 1 arg, no delay:
        {ILI9163C_VMCOFFS, {0x40}, 1},       // VCOM Offset
#ifdef SSUD_DISP_INVERT_COLORS
        {ILI9163C_INVON, {0}, 0}, // set inverted mode
#else
        {ILI9163C_INVOFF, {0}, 0}, // set non-inverted mode
#endif /* SSUD_DISP_INVERT_COLORS */
        {ILI9163C_COLMOD, {0x5}, 1},                                                                                        // set color mode, 1 arg, no delay: 16-bit color
        {ILI9163C_SDDC, {0}, 1},                                                                                            // set source driver direction control
        {ILI9163C_GAMCTL, {0x01}, 1},                                                                                       // set source driver direction control
        {ILI9163C_GMCTRP1, {0x36, 0x29, 0x12, 0x22, 0x1C, 0x15, 0x42, 0xB7, 0x2F, 0x13, 0x12, 0x0A, 0x11, 0x0B, 0x06}, 16}, // 16 args, no delay:
        {ILI9163C_GMCTRN1, {0x09, 0x16, 0x2D, 0x0D, 0x13, 0x15, 0x40, 0x48, 0x53, 0x0C, 0x1D, 0x25, 0x2E, 0x34, 0x39}, 16}, // 16 args, no delay:
        {ILI9163C_NORON, {0}, 0x80},                                                                                        // Normal display on, no args, w/delay 10 ms delay
        {ILI9163C_DISPON, {0}, 0x80},                                                                                       // Main screen turn on, no args w/delay 100 ms delay
        {0, {0}, 0xff}
    };

    // Send all the commands
    rt_uint16_t cmd = 0;
    while (ili_init_cmds[cmd].databytes != 0xff)
    {
        ssud_spi_write_cmd(ili_init_cmds[cmd].cmd);
        ssud_spi_write_data(ili_init_cmds[cmd].data, ili_init_cmds[cmd].databytes & 0x1F);
        if (ili_init_cmds[cmd].databytes & 0x80)
        {
            rt_thread_mdelay(100);
        }
        cmd++;
    }

    ssud_ili9163c_set_orientation(SSUD_DISP_ORIENTATION);
}

void ssud_ili9163c_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
    rt_uint8_t data[4];

    /*Column addresses*/
    ssud_spi_write_cmd(ILI9163C_CASET);
    data[0] = (x_start >> 8) & 0xFF;
    data[1] = x_start & 0xFF;
    data[2] = (x_end >> 8) & 0xFF;
    data[3] = x_end & 0xFF;
    ssud_spi_write_data(data, 4);

    /*Page addresses*/
    ssud_spi_write_cmd(ILI9163C_RASET);
    data[0] = (y_start >> 8) & 0xFF;
    data[1] = y_start & 0xFF;
    data[2] = (y_end >> 8) & 0xFF;
    data[3] = y_end & 0xFF;
    ssud_spi_write_data(data, 4);

    /*Memory write*/
    ssud_spi_write_cmd(ILI9163C_RAMWR);
    ssud_spi_write_color(x_start, y_start, x_end, y_end, pcolor);
}

void ssud_ili9163c_set_orientation(rt_uint8_t orientation)
{
    rt_uint8_t data[] = {0x48, 0x88, 0xA8, 0x68};
    ssud_spi_write_cmd(ILI9163C_MADCTL);
    ssud_spi_write_data((void *)&data[orientation], 1);
}

#endif /* SSUD_DISP_CONTROLLER_ILI9163C */
