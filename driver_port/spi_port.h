#ifndef __SPI_PORT_H_
#define __SPI_PORT_H_

#include <rtdevice.h>
#include <rtthread.h>

#define SSUD_QUICK_BUF_SIZE SSUD_DISP_HOR_RES *SSUD_DISP_VER_RES / 20

void ssud_spi_gpio_config(void);
void ssud_spi_port_config(void);
void ssud_spi_write_cmd(const rt_uint8_t cmd);
void ssud_spi_write_data(rt_uint8_t *data, rt_size_t length);
void ssud_spi_write_color(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint8_t *color);

#endif // !__SPI_PORT_H_
