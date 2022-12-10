#ifndef __BACKLIGHT_PORT_H_
#define __BACKLIGHT_PORT_H_

#include <rtdevice.h>
#include <rtthread.h>

static void backlight_switch_init(void);
static void backlight_pwm_init(void);
void backlight_init(void);
void backlight_light_set(rt_int8_t light);
void backlight_bool_set(rt_uint8_t status);

#endif // !__BACKLIGHT_PORT_H_
