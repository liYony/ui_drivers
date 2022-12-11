/**
 * @file lv_templ.h
 *
 */

#ifndef ILI9341_H
#define ILI9341_H

#ifdef SSUD_DISP_CONTROLLER_ILI9341

#include <rtdevice.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

void ssud_ili9341_init(void);
void ssud_ili9341_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor);
void ssud_ili9341_set_orientation(rt_uint8_t orientation);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SSUD_DISP_CONTROLLER_ILI9341 */

#endif /*ILI9341_H*/
