#ifndef GC9A01_H
#define GC9A01_H

#ifdef SSUD_DISP_CONTROLLER_GC9A01

#include <rtdevice.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

void ssud_GC9A01_init(void);
void ssud_GC9A01_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor);
void ssud_GC9A01_set_orientation(rt_uint8_t orientation);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SSUD_DISP_CONTROLLER_GC9A01 */

#endif /*GC9A01_H*/
