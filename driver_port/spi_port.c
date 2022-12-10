#include "spi_port.h"

static struct rt_spi_device *lcd_device = RT_NULL;

void spi_port_config(void)
{
    lcd_device = (struct rt_spi_device *)rt_device_find(PKG_SPI_DEV_NAME);
    if (lcd_device == RT_NULL)
    {
        return;
    }
    /* config spi */
    struct rt_spi_configuration cfg = {0};
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_3 | RT_SPI_MSB;

#if defined(PKG_SPI_CLK_DIVIDER_1)
    cfg.max_hz = 80 * 1000 * 1000; /* 80M */
#elif defined(PKG_SPI_CLK_DIVIDER_2)
    cfg.max_hz = 40 * 1000 * 1000; /* 40M */
#elif defined(PKG_SPI_CLK_DIVIDER_3)
    cfg.max_hz = 26.67 * 1000 * 1000; /* 26.67M */
#elif defined(PKG_SPI_CLK_DIVIDER_4)
    cfg.max_hz = 20 * 1000 * 1000; /* 20M */
#elif defined(PKG_SPI_CLK_DIVIDER_5)
    cfg.max_hz = 16 * 1000 * 1000; /* 16M */
#elif defined(PKG_SPI_CLK_DIVIDER_6)
    cfg.max_hz = 13.33 * 1000 * 1000; /* 13.33M */
#elif defined(PKG_SPI_CLK_DIVIDER_7)
    cfg.max_hz = 11.43 * 1000 * 1000; /* 11.43M */
#elif defined(PKG_SPI_CLK_DIVIDER_8)
    cfg.max_hz = 10 * 1000 * 1000; /* 10M */
#elif defined(PKG_SPI_CLK_DIVIDER_9)
    cfg.max_hz = 8.89 * 1000 * 1000; /* 8.89M */
#elif defined(PKG_SPI_CLK_DIVIDER_10)
    cfg.max_hz = 8 * 1000 * 1000; /* 8M */
#elif defined(PKG_SPI_CLK_DIVIDER_12)
    cfg.max_hz = 6.67 * 1000 * 1000; /* 6.67M */
#elif defined(PKG_SPI_CLK_DIVIDER_16)
    cfg.max_hz = 5 * 1000 * 1000; /* 5M */
#elif defined(PKG_SPI_CLK_DIVIDER_20)
    cfg.max_hz = 4 * 1000 * 1000; /* 4M */
#elif defined(PKG_SPI_CLK_DIVIDER_24)
    cfg.max_hz = 3.33 * 1000 * 1000; /* 3.33M */
#elif defined(PKG_SPI_CLK_DIVIDER_32)
    cfg.max_hz = 2.5 * 1000 * 1000; /* 2.5M */
#elif defined(PKG_SPI_CLK_DIVIDER_40)
    cfg.max_hz = 2 * 1000 * 1000; /* 2M */
#elif defined(PKG_SPI_CLK_DIVIDER_48)
    cfg.max_hz = 1.67 * 1000 * 1000; /* 1.67M */
#elif defined(PKG_SPI_CLK_DIVIDER_80)
    cfg.max_hz = 1 * 1000 * 1000; /* 1M */
#else
    cfg.max_hz = 20 * 1000 * 1000; /* 20M */
#endif

    rt_spi_configure(lcd_device, &cfg);
}

void spi_gpio_config(void)
{
    rt_pin_mode(PKG_SPI_DC_PIN, PIN_MODE_OUTPUT);
#if !defined(PKG_DISPLAY_SOFT_RES)
    rt_pin_mode(PKG_SPI_RES_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(PKG_SPI_RES_PIN, PIN_LOW);
    // wait at least 100ms for reset
    rt_thread_delay(RT_TICK_PER_SECOND / 10);
    rt_pin_write(PKG_SPI_RES_PIN, PIN_HIGH);
#endif
}

void spi_write_cmd(const rt_uint8_t cmd)
{
    rt_pin_write(PKG_SPI_DC_PIN, PIN_LOW);
    rt_spi_send(lcd_device, &cmd, 1);
}

void spi_write_data(rt_uint8_t *data, rt_size_t length)
{
    if (length == 0)
        return;

    rt_pin_write(PKG_SPI_DC_PIN, PIN_HIGH);
    rt_spi_send(lcd_device, data, length);
}

static void spi_write_color_16bit(rt_uint8_t *color, rt_size_t size)
{
    rt_size_t i = 0;
    rt_uint8_t color_data[2] = {0};

    color_data[0] = color[1];
    color_data[1] = color[0];

    rt_pin_write(PKG_SPI_DC_PIN, PIN_HIGH);

    for (i = 0; i < size; i++)
    {
        rt_spi_send(lcd_device, color_data, 2);
    }
}

void spi_write_color(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint8_t *color)
{
    rt_uint16_t i = 0;
    rt_uint32_t size = 0, size_remain = 0;
    rt_uint8_t *fill_buf = RT_NULL;

    size = (x_end - x_start + 1) * (y_end - y_start + 1) * 2;

    if (size > TFT_QUICK_BUF_SIZE)
    {
        /* the number of remaining to be filled */
        size_remain = size - TFT_QUICK_BUF_SIZE;
        size = TFT_QUICK_BUF_SIZE;
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
            rt_pin_write(PKG_SPI_DC_PIN, PIN_HIGH);
            rt_spi_send(lcd_device, fill_buf, size);

            /* Fill completed */
            if (size_remain == 0)
                break;

            /* calculate the number of fill next time */
            if (size_remain > TFT_QUICK_BUF_SIZE)
            {
                size_remain = size_remain - TFT_QUICK_BUF_SIZE;
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
        spi_write_color_16bit(color, size);
    }
}
