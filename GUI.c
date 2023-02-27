/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-21     ZXY       the first version
 */
#include "disp_driver.h"
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
    ssud_disp_driver_fill(x_start, y_start, x_end, y_end, &pcolor);
}

void draw_circle(int x, int y, int r, void *pcolor)
{
    int a, b, num;
    a = 0;
    b = r;
    while(22 * b * b >= r * r)          // 1/8r
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
