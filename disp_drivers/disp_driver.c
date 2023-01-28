#include "disp_driver.h"

void ssud_disp_driver_init(void)
{
#if defined SSUD_DISP_CONTROLLER_ILI9341
    ssud_ili9341_init();
#elif defined SSUD_DISP_CONTROLLER_ILI9481
    ssud_ili9481_init();
#elif defined SSUD_DISP_CONTROLLER_ILI9488
    ssud_ili9488_init();
#elif defined SSUD_DISP_CONTROLLER_ST7789
    ssud_st7789_init();
#elif defined SSUD_DISP_CONTROLLER_ST7796S
    ssud_st7796s_init();
#elif defined SSUD_DISP_CONTROLLER_ST7735S
    ssud_st7735s_init();
#elif defined SSUD_DISP_CONTROLLER_HX8357
    ssud_hx8357_init();
#elif defined SSUD_DISP_CONTROLLER_ILI9486
    ssud_ili9486_init();
#elif defined SSUD_DISP_CONTROLLER_SH1107
    ssud_sh1107_init();
#elif defined SSUD_DISP_CONTROLLER_SSD1306
    ssud_ssd1306_init();
#elif defined SSUD_DISP_CONTROLLER_FT81X
    ssud_FT81x_init();
#elif defined SSUD_DISP_CONTROLLER_IL3820
    ssud_il3820_init();
#elif defined SSUD_DISP_CONTROLLER_RA8875
    ssud_ra8875_init();
#elif defined SSUD_DISP_CONTROLLER_GC9A01
    ssud_GC9A01_init();
#elif defined SSUD_DISP_CONTROLLER_JD79653A
    ssud_jd79653a_init();
#elif defined SSUD_DISP_CONTROLLER_UC8151D
    ssud_uc8151d_init();
#elif defined SSUD_DISP_CONTROLLER_ILI9163C
    ssud_ili9163c_init();
#elif defined SSUD_DISP_CONTROLLER_PCD8544
    ssud_pcd8544_init();
#endif
}

void ssud_disp_driver_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
#if defined SSUD_DISP_CONTROLLER_ILI9341
    ssud_ili9341_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ILI9481
    ssud_ili9481_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ILI9488
    ssud_ili9488_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ST7789
    ssud_st7789_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ST7796S
    ssud_st7796s_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ST7735S
    ssud_st7735s_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_HX8357
    ssud_hx8357_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ILI9486
    ssud_ili9486_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_SH1107
    ssud_sh1107_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_SSD1306
    ssud_ssd1306_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_FT81X
    ssud_FT81x_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_IL3820
    ssud_il3820_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_RA8875
    ssud_ra8875_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_GC9A01
    ssud_GC9A01_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_JD79653A
    ssud_jd79653a_lv_fb_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_UC8151D
    ssud_uc8151d_lv_fb_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_ILI9163C
    ssud_ili9163c_fill(x_start, y_start, x_end, y_end, pcolor);
#elif defined SSUD_DISP_CONTROLLER_PCD8544
    ssud_pcd8544_fill(x_start, y_start, x_end, y_end, pcolor);
#endif
}

void full_all(void *pcolor)
{
    rt_uint16_t xend, yend;
    xend=SSUD_DISP_HOR_RES;
    yend=SSUD_DISP_VER_RES;
    ssud_disp_driver_fill(0,0,xend,yend,&pcolor);
}

void lcd_point(int x, int y ,void *pcolor)
{
    rt_uint16_t x_end, y_end,x_start,y_start;
    x_start=x_end=x;
    y_start=y_end=y;
    ssud_st7735s_fill(x_start, y_start, x_end, y_end, &pcolor);
}

void draw_circle(int x, int y, int r, void *pcolor)
{
    int a, b, num;
    a = 0;
    b = r;
    while(22 * b * b >= r * r)          // 1/8圆即可
    {
        lcd_point(x + a, y - b,pcolor); // 0~1
        lcd_point(x - a, y - b,pcolor); // 0~7
        lcd_point(x - a, y + b,pcolor); // 4~5
        lcd_point(x + a, y + b,pcolor); // 4~3

        lcd_point(x + b, y + a,pcolor); // 2~3
        lcd_point(x + b, y - a,pcolor); // 2~1
        lcd_point(x - b, y - a,pcolor); // 6~7
        lcd_point(x - b, y + a,pcolor); // 6~5

        a++;
        num = (a * a + b * b) - r*r;
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}

void draw_line(int x1,int y1,int x2,int y2,void *pcolor)
{
    int dx,dy,e;
    dx=x2-x1;
    dy=y2-y1;
    if(dx>=0)
    {
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 1/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){y1+=1;e-=dx;}
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 2/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){x1+=1;e-=dy;}
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 8/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){y1-=1;e-=dx;}
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 7/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){x1+=1;e-=dy;}
                    y1-=1;
                    e+=dx;
                }
            }
        }
    }
    else //dx<0
    {
        dx=-dx;     //dx=abs(dx)
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 4/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){y1+=1;e-=dx;}
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 3/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){x1-=1;e-=dy;}
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 5/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){y1-=1;e-=dx;}
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 6/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){x1-=1;e-=dy;}
                    y1-=1;
                    e+=dx;
                }
            }
        }
    }
}
