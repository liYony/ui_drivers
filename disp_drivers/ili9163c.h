#ifndef ILI9163C_H
#define ILI9163C_H

#ifdef SSUD_DISP_CONTROLLER_ILI9163C

#include <rtdevice.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

// ILI9163C specific commands used in init
#define ILI9163C_NOP 0x00
#define ILI9163C_SWRESET 0x01
#define ILI9163C_RDDID 0x04
#define ILI9163C_RDDST 0x09

#define ILI9163C_SLPIN 0x10
#define ILI9163C_SLPOUT 0x11
#define ILI9163C_PTLON 0x12
#define ILI9163C_NORON 0x13

#define ILI9163C_INVOFF 0x20
#define ILI9163C_INVON 0x21
#define ILI9163C_CMD_GAMST 0x26
#define ILI9163C_DISPOFF 0x28
#define ILI9163C_DISPON 0x29
#define ILI9163C_CASET 0x2A
#define ILI9163C_RASET 0x2B
#define ILI9163C_RAMWR 0x2C
#define ILI9163C_COLORSET 0x2D
#define ILI9163C_RAMRD 0x2E

#define ILI9163C_PTLAR 0x30
#define ILI9163C_VSCRDEF 0x33
#define ILI9163C_COLMOD 0x3A
#define ILI9163C_MADCTL 0x36
#define ILI9163C_VSCRSADD 0x37

#define ILI9163C_FRMCTR1 0xB1
#define ILI9163C_FRMCTR2 0xB2
#define ILI9163C_FRMCTR3 0xB3
#define ILI9163C_INVCTR 0xB4
#define ILI9163C_DISSET5 0xB6
#define ILI9163C_SDDC 0xB7

#define ILI9163C_PWCTR1 0xC0
#define ILI9163C_PWCTR2 0xC1
#define ILI9163C_PWCTR3 0xC2
#define ILI9163C_PWCTR4 0xC3
#define ILI9163C_PWCTR5 0xC4
#define ILI9163C_VMCTR1 0xC5
#define ILI9163C_VMCOFFS 0xC7

#define ILI9163C_GAMCTL 0xF2

#define ILI9163C_GMCTRP1 0xE0
#define ILI9163C_GMCTRN1 0xE1

void ssud_ili9163c_init(void);
void ssud_ili9163c_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor);
void ssud_ili9163c_set_orientation(rt_uint8_t orientation);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SSUD_DISP_CONTROLLER_ILI9163C */

#endif /*ILI9163C_H*/
