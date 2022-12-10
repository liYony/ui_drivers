#include <board.h>
#include <drv_spi.h>
#include "disp_driver.h"

#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))
#define PIN_STPORT(pin) ((GPIO_TypeDef *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_STPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))

/* Because each bsp of RT-Thread handles rt_spi_bus_attach_device differently as a private variable, it is 
difficult to get consistency here. You will need to complete the following function according to your bsp */
void ssud_spi_device_attach(void)
{
    /* Please complete according to your bsp */
    rt_hw_spi_device_attach(SSUD_DRV_SPI_BUS_NAME, SSUD_DRV_SPI_DEV_NAME, PIN_STPORT(SSUD_DRV_SPI_CS_PIN), PIN_STPIN(SSUD_DRV_SPI_CS_PIN));
}

static int hw_driver_port_init(void)
{
    ssud_spi_device_attach();
    ssud_spi_port_config();
    ssud_spi_gpio_config();
#if defined(SSUD_BACKLIGHT_SWITCH) || defined(SSUD_BACKLIGHT_PWM)
    ssud_backlight_init();
#endif
    ssud_disp_driver_init();
    return 0;
}

INIT_COMPONENT_EXPORT(hw_driver_port_init);
