#include "spi_port.h"

static struct rt_spi_device *lcd_device = RT_NULL;

void ssud_spi_port_config(void)
{
    lcd_device = (struct rt_spi_device *)rt_device_find(SSUD_DRV_SPI_DEV_NAME);
    if (lcd_device == RT_NULL)
    {
        return;
    }
    /* config spi */
    struct rt_spi_configuration cfg = {0};
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_3 | RT_SPI_MSB;
    cfg.max_hz = SSUD_DRV_SPI_FREQUENCY * 1000 * 1000;

    rt_spi_configure(lcd_device, &cfg);
}

void ssud_spi_gpio_config(void)
{
    rt_pin_mode(SSUD_DRV_SPI_DC_PIN, PIN_MODE_OUTPUT);
#if !defined(SSUD_DISP_SOFT_RESET)
    rt_pin_mode(SSUD_DRV_SPI_RES_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(SSUD_DRV_SPI_RES_PIN, PIN_LOW);
    // wait at least 100ms for reset
    rt_thread_delay(RT_TICK_PER_SECOND / 10);
    rt_pin_write(SSUD_DRV_SPI_RES_PIN, PIN_HIGH);
#endif
}

void ssud_spi_write_cmd(const rt_uint8_t cmd)
{
    rt_pin_write(SSUD_DRV_SPI_DC_PIN, PIN_LOW);
    rt_spi_send(lcd_device, &cmd, 1);
}

void ssud_spi_write_data(rt_uint8_t *data, rt_size_t length)
{
    if (length == 0)
        return;

    rt_pin_write(SSUD_DRV_SPI_DC_PIN, PIN_HIGH);
    rt_spi_send(lcd_device, data, length);
}

static void ssud_spi_write_color_16bit(rt_uint8_t *color, rt_size_t size)
{
    rt_size_t i = 0;
    rt_uint8_t color_data[2] = {0};

    color_data[0] = color[1];
    color_data[1] = color[0];

    rt_pin_write(SSUD_DRV_SPI_DC_PIN, PIN_HIGH);

    for (i = 0; i < size; i++)
    {
        rt_spi_send(lcd_device, color_data, 2);
    }
}

void ssud_spi_write_color(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint8_t *color)
{
    rt_uint16_t i = 0;
    rt_uint32_t size = 0, size_remain = 0;
    rt_uint8_t *fill_buf = RT_NULL;

    size = (x_end - x_start + 1) * (y_end - y_start + 1) * 2;

    if (size > SSUD_QUICK_BUF_SIZE)
    {
        /* the number of remaining to be filled */
        size_remain = size - SSUD_QUICK_BUF_SIZE;
        size = SSUD_QUICK_BUF_SIZE;
    }

    fill_buf = (rt_uint8_t *)rt_malloc(size);

    if (fill_buf)
    {
        /* fast fill */
        while (1)
        {
            for (i = 0; i < size / 2; i++)
            {
                fill_buf[2 * i] = color[1];
                fill_buf[2 * i + 1] = color[0];
            }
            rt_pin_write(SSUD_DRV_SPI_DC_PIN, PIN_HIGH);
            rt_spi_send(lcd_device, fill_buf, size);

            /* Fill completed */
            if (size_remain == 0)
                break;

            /* calculate the number of fill next time */
            if (size_remain > SSUD_QUICK_BUF_SIZE)
            {
                size_remain = size_remain - SSUD_QUICK_BUF_SIZE;
            }
            else
            {
                size = size_remain;
                size_remain = 0;
            }
        }
        rt_free(fill_buf);
    }
    else
    {
        size = (x_end - x_start + 1) * (y_end - y_start + 1);
        ssud_spi_write_color_16bit(color, size);
    }
}
