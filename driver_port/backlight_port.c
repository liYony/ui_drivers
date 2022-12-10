#include "backlight_port.h"

#if defined(PKG_DISP_BACKLIGHT_SWITCH) || defined(PKG_DISP_BACKLIGHT_PWM)

struct rt_device_pwm *backlight_pwm;

void backlight_init(void)
{
#if defined PKG_DISP_BACKLIGHT_PWM
    backlight_pwm_init();
#elif defined PKG_DISP_BACKLIGHT_SWITCH
    backlight_switch_init();
#endif
}

static void backlight_switch_init(void)
{
#ifdef PKG_BACKLIGHT_SWITCH_PIN
    rt_pin_mode(PKG_BACKLIGHT_SWITCH_PIN, PIN_MODE_OUTPUT);
#endif /* PKG_BACKLIGHT_SWITCH_PIN */
}

static void backlight_pwm_init(void)
{
#ifdef PKG_BACKLIGHT_PWM_NAME
    backlight_pwm = (struct rt_device_pwm *)rt_device_find(PKG_BACKLIGHT_PWM_NAME);
    if (backlight_pwm == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PKG_BACKLIGHT_PWM_NAME);
        return;
    }
#endif /* PKG_BACKLIGHT_PWM_NAME */
}

void backlight_light_set(rt_int8_t light)
{
    rt_uint32_t period = 1000000; /* 1ms */
    light = light >= 100 ? 100 : (light < 0 ? 0 : light);
#ifdef PKG_DISP_ACTIVE_ISLOW
    light = 100 - light;
#endif /* PKG_DISP_ACTIVE_ISLOW */

#if defined(PKG_DISP_BACKLIGHT_SWITCH)
    if (light >= 50)
        rt_pin_write(PKG_BACKLIGHT_SWITCH_PIN, PIN_HIGH);
    else
        rt_pin_write(PKG_BACKLIGHT_SWITCH_PIN, PIN_LOW);
#elif defined(PKG_DISP_BACKLIGHT_PWM)
    rt_pwm_set(backlight_pwm, PKG_BACKLIGHT_PWM_CH, period, light * 10000);
    rt_pwm_enable(backlight_pwm, PKG_BACKLIGHT_PWM_CH);
#endif
}

void backlight_bool_set(rt_uint8_t status)
{
    status = status == 0 ? 0 : 100;
    backlight_light_set(status);
}

#endif /* defined(PKG_DISP_BACKLIGHT_SWITCH) || defined(PKG_DISP_BACKLIGHT_PWM) */
