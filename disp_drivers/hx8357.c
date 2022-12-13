#include "disp_driver.h"

#ifdef SSUD_DISP_CONTROLLER_HX8357

static uint8_t displayType = HX8357D;

static const uint8_t
    initb[] = {
        HX8357B_SETPOWER, 3,
        0x44, 0x41, 0x06,
        HX8357B_SETVCOM, 2,
        0x40, 0x10,
        HX8357B_SETPWRNORMAL, 2,
        0x05, 0x12,
        HX8357B_SET_PANEL_DRIVING, 5,
        0x14, 0x3b, 0x00, 0x02, 0x11,
        HX8357B_SETDISPLAYFRAME, 1,
        0x0c, // 6.8mhz
        HX8357B_SETPANELRELATED, 1,
        0x01,    // BGR
        0xEA, 3, // seq_undefined1, 3 args
        0x03, 0x00, 0x00,
        0xEB, 4, // undef2, 4 args
        0x40, 0x54, 0x26, 0xdb,
        HX8357B_SETGAMMA, 12,
        0x00, 0x15, 0x00, 0x22, 0x00, 0x08, 0x77, 0x26, 0x66, 0x22, 0x04, 0x00,
        HX8357_MADCTL, 1,
        0xC0,
        HX8357_COLMOD, 1,
        0x55,
        HX8357_PASET, 4,
        0x00, 0x00, 0x01, 0xDF,
        HX8357_CASET, 4,
        0x00, 0x00, 0x01, 0x3F,
        HX8357B_SETDISPMODE, 1,
        0x00,                          // CPU (DBI) and internal oscillation ??
        HX8357_SLPOUT, 0x80 + 120 / 5, // Exit sleep, then delay 120 ms
        HX8357_DISPON, 0x80 + 10 / 5,  // Main screen turn on, delay 10 ms
        0                              // END OF COMMAND LIST
},
    initd[] = {
        HX8357_SWRESET, 0x80 + 100 / 5,                          // Soft reset, then delay 10 ms
        HX8357D_SETC, 3, 0xFF, 0x83, 0x57, 0xFF, 0x80 + 500 / 5, // No command, just delay 300 ms
        HX8357_SETRGB, 4, 0x80, 0x00, 0x06, 0x06,                // 0x80 enables SDO pin (0x00 disables)
        HX8357D_SETCOM, 1,
        0x25, // -1.52V
        HX8357_SETOSC, 1,
        0x68, // Normal mode 70Hz, Idle mode 55 Hz
        HX8357_SETPANEL, 1,
        0x05, // BGR, Gate direction swapped
        HX8357_SETPWR1, 6,
        0x00, // Not deep standby
        0x15, // BT
        0x1C, // VSPR
        0x1C, // VSNR
        0x83, // AP
        0xAA, // FS
        HX8357D_SETSTBA, 6,
        0x50, // OPON normal
        0x50, // OPON idle
        0x01, // STBA
        0x3C, // STBA
        0x1E, // STBA
        0x08, // GEN
        HX8357D_SETCYC, 7,
        0x02, // NW 0x02
        0x40, // RTN
        0x00, // DIV
        0x2A, // DUM
        0x2A, // DUM
        0x0D, // GDON
        0x78, // GDOFF
        HX8357D_SETGAMMA, 34, 0x02, 0x0A, 0x11, 0x1d, 0x23, 0x35, 0x41, 0x4b, 0x4b, 0x42, 0x3A, 0x27, 0x1B, 0x08, 0x09, 0x03, 0x02, 0x0A, 0x11, 0x1d, 0x23, 0x35, 0x41, 0x4b, 0x4b, 0x42, 0x3A, 0x27, 0x1B, 0x08, 0x09, 0x03, 0x00, 0x01, HX8357_COLMOD, 1,
        0x55, // 16 bit
        HX8357_MADCTL, 1, 0xC0, HX8357_TEON, 1,
        0x00,                                                          // TW off
        HX8357_TEARLINE, 2, 0x00, 0x02, HX8357_SLPOUT, 0x80 + 150 / 5, // Exit Sleep, then delay 150 ms
        HX8357_DISPON, 0x80 + 50 / 5,                                  // Main screen turn on, delay 50 ms
        0,                                                             // END OF COMMAND LIST
};

void ssud_hx8357_init(void)
{
    // Send all the commands
    const uint8_t *addr = (displayType == HX8357B) ? initb : initd;
    uint8_t cmd, x, numArgs;
    while ((cmd = *addr++) > 0)
    { // '0' command ends list
        x = *addr++;
        numArgs = x & 0x7F;
        if (cmd != 0xFF)
        { // '255' is ignored
            if (x & 0x80)
            { // If high bit set, numArgs is a delay time
                ssud_spi_write_cmd(cmd);
            }
            else
            {
                ssud_spi_write_cmd(cmd);
                ssud_spi_write_data((void *)addr, numArgs);
                addr += numArgs;
            }
        }
        if (x & 0x80)
        {                                               // If high bit set...
            rt_thread_mdelay(100); // numArgs is actually a delay time (5ms units)
        }
    }

    ssud_hx8357_set_orientation(SSUD_DISP_ORIENTATION);

#ifdef SSUD_DISP_INVERT_COLORS
    ssud_spi_write_cmd(HX8357_INVON);
#else
    ssud_spi_write_cmd(HX8357_INVOFF);
#endif
}

void ssud_hx8357_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
    rt_uint8_t data[4];

    /*Column addresses*/
    ssud_spi_write_cmd(HX8357_CASET);
    data[0] = (x_start >> 8) & 0xFF;
    data[1] = (x_start & 0xFF);
    data[2] = (x_end >> 8) & 0xFF;
    data[3] = (x_end & 0xFF);
    ssud_spi_write_data(data, 4);

    /*Page addresses*/
    ssud_spi_write_cmd(HX8357_PASET);
    data[0] = (y_start >> 8) & 0xFF;
    data[1] = (y_start & 0xFF);
    data[2] = (y_end >> 8) & 0xFF;
    data[3] = (y_end & 0xFF);
    ssud_spi_write_data(data, 4);

    /*Memory write*/
    ssud_spi_write_cmd(HX8357_RAMWR);
    ssud_spi_write_color(x_start, y_start, x_end, y_end, pcolor);
}

void ssud_hx8357_set_orientation(uint8_t r)
{
    r = r & 3; // can't be higher than 3

    switch (r)
    {
    case 0:
        r = MADCTL_MX | MADCTL_MY | MADCTL_RGB;
        break;
    case 1:
        r = MADCTL_MV | MADCTL_MY | MADCTL_RGB;
        break;
    case 2:
        r = MADCTL_RGB;
        break;
    case 3:
        r = MADCTL_MX | MADCTL_MV | MADCTL_RGB;
        break;
    }

    ssud_spi_write_cmd(HX8357_MADCTL);
    ssud_spi_write_data(&r, 1);
}

#endif /* SSUD_DISP_CONTROLLER_HX8357 */
