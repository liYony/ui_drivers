#include "backlight_port.h"

#if defined(SSUD_BACKLIGHT_SWITCH) || defined(SSUD_BACKLIGHT_PWM)

struct rt_device_pwm *backlight_pwm;

void ssud_backlight_init(void)
{
#if defined SSUD_BACKLIGHT_PWM
    ssud_backlight_pwm_init();
#elif defined SSUD_BACKLIGHT_SWITCH
    ssud_backlight_switch_init();
#endif
    ssud_backlight_light_set(SSUD_BACKLIGHT_PWM_BRIGHTNESS);
}

static void ssud_backlight_switch_init(void)
{
#ifdef SSUD_BACKLIGHT_SWITCH_PIN
    rt_pin_mode(SSUD_BACKLIGHT_SWITCH_PIN, PIN_MODE_OUTPUT);
#endif /* SSUD_BACKLIGHT_SWITCH_PIN */
}

static void ssud_backlight_pwm_init(void)
{
#ifdef SSUD_BACKLIGHT_PWM_DEVNAME
    backlight_pwm = (struct rt_device_pwm *)rt_device_find(SSUD_BACKLIGHT_PWM_DEVNAME);
#endif /* SSUD_BACKLIGHT_PWM_DEVNAME */
}

void ssud_backlight_light_set(rt_int8_t light)
{
    rt_uint32_t period = 1000000; /* 1ms */
    light = light >= 100 ? 100 : (light < 0 ? 0 : light);
#ifdef SSUD_BACKLIGHT_ACTIVE_ISLOW
    light = 100 - light;
#endif /* SSUD_BACKLIGHT_ACTIVE_ISLOW */

#if defined(SSUD_BACKLIGHT_SWITCH)
    if (light >= 50)
        rt_pin_write(SSUD_BACKLIGHT_SWITCH_PIN, PIN_HIGH);
    else
        rt_pin_write(SSUD_BACKLIGHT_SWITCH_PIN, PIN_LOW);
#elif defined(SSUD_BACKLIGHT_PWM)
    rt_pwm_set(backlight_pwm, SSUD_BACKLIGHT_PWM_CHANNEL, period, light * 10000);
    rt_pwm_enable(backlight_pwm, SSUD_BACKLIGHT_PWM_CHANNEL);
#endif
}

void ssud_backlight_bool_set(rt_uint8_t status)
{
    status = status == 0 ? 0 : 100;
    ssud_backlight_light_set(status);
}

#endif /* defined(SSUD_BACKLIGHT_SWITCH) || defined(SSUD_BACKLIGHT_PWM) */
