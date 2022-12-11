#include "disp_driver.h"

#ifdef SSUD_DISP_CONTROLLER_ILI9341

void ssud_ili9341_init(void)
{
	lcd_init_cmd_t ili_init_cmds[]={
		{0xCF, {0x00, 0x83, 0X30}, 3},
		{0xED, {0x64, 0x03, 0X12, 0X81}, 4},
		{0xE8, {0x85, 0x01, 0x79}, 3},
		{0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
		{0xF7, {0x20}, 1},
		{0xEA, {0x00, 0x00}, 2},
		{0xC0, {0x26}, 1},          /*Power control*/
		{0xC1, {0x11}, 1},          /*Power control */
		{0xC5, {0x35, 0x3E}, 2},    /*VCOM control*/
		{0xC7, {0xBE}, 1},          /*VCOM control*/
		{0x36, {0x28}, 1},          /*Memory Access Control*/
		{0x3A, {0x55}, 1},			/*Pixel Format Set*/
		{0xB1, {0x00, 0x1B}, 2},
		{0xF2, {0x08}, 1},
		{0x26, {0x01}, 1},
		{0xE0, {0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00}, 15},
		{0XE1, {0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F}, 15},
		{0x2A, {0x00, 0x00, 0x00, 0xEF}, 4},
		{0x2B, {0x00, 0x00, 0x01, 0x3f}, 4},
		{0x2C, {0}, 0},
		{0xB7, {0x07}, 1},
		{0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
		{0x11, {0}, 0x80},
		{0x29, {0}, 0x80},
		{0, {0}, 0xff},
	};

	//Send all the commands
	rt_uint16_t cmd = 0;
	while (ili_init_cmds[cmd].databytes!=0xff) {
		ssud_spi_write_cmd(ili_init_cmds[cmd].cmd);
		ssud_spi_write_data(ili_init_cmds[cmd].data, ili_init_cmds[cmd].databytes&0x1F);
		if (ili_init_cmds[cmd].databytes & 0x80) {
			rt_thread_mdelay(100);
		}
		cmd++;
	}

    ssud_ili9341_set_orientation(SSUD_DISP_ORIENTATION);

#ifdef SSUD_DISP_INVERT_COLORS
	ssud_spi_write_cmd(0x21);
#else
	ssud_spi_write_cmd(0x20);
#endif
}


void ssud_ili9341_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
	rt_uint8_t data[4];

	/*Column addresses*/
	ssud_spi_write_cmd(0x2A);
	data[0] = (x_start >> 8) & 0xFF;
	data[1] = x_start & 0xFF;
	data[2] = (x_end >> 8) & 0xFF;
	data[3] = x_end & 0xFF;
	ssud_spi_write_data(data, 4);

	/*Page addresses*/
	ssud_spi_write_cmd(0x2B);
	data[0] = (y_start >> 8) & 0xFF;
	data[1] = y_start & 0xFF;
	data[2] = (y_end >> 8) & 0xFF;
	data[3] = y_end & 0xFF;
	ssud_spi_write_data(data, 4);

	/*Memory write*/
	ssud_spi_write_cmd(0x2C);
	ssud_spi_write_color(x_start, y_start, x_end, y_end, pcolor);
}

void ssud_ili9341_set_orientation(rt_uint8_t orientation)
{

    rt_uint8_t data[] = {0x48, 0x88, 0x28, 0xE8};
    ssud_spi_write_cmd(0x36);
    ssud_spi_write_data((void *) &data[orientation], 1);
}

#endif /* SSUD_DISP_CONTROLLER_ILI9341 */
