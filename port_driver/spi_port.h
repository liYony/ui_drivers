#ifndef __SPI_PORT_H_
#define __SPI_PORT_H_

#include <rtdevice.h>
#include <rtthread.h>

#define TFT_QUICK_BUF_SIZE PKG_DISPLAY_HOR_RES_MAX *PKG_DISPLAY_VER_RES_MAX / 20

void spi_gpio_config(void);
void spi_port_config(void);
void spi_write_cmd(const rt_uint8_t cmd);
void spi_write_data(rt_uint8_t *data, rt_size_t length);
void spi_write_color(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint8_t *color);

#endif // !__SPI_PORT_H_
