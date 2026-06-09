#include <LPC21xx.H>
#include "delay.h"

#define LCD_D 0xf<<14
#define RS 1<<8
#define E  1<<9

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INTEGER(int);
void LCD_STR(unsigned char *);
void LCD_SCROLL(unsigned char *, unsigned char);
void LCD_FLOAT(float);

void LCD_INIT(void)
{
    delay_second(1);

    IODIR0 |= LCD_D | RS | E;

    LCD_COMMAND(0x01);
    LCD_COMMAND(0x02);
    LCD_COMMAND(0x0C);
    LCD_COMMAND(0x28);
}

void LCD_COMMAND(unsigned char cmd)
{
    IOCLR0 = LCD_D;
    IOSET0 = (cmd & 0xf0) << 10;

    IOCLR0 = RS;

    IOSET0 = E;
    delay_millisecond(2);
    IOCLR0 = E;

    IOCLR0 = LCD_D;
    IOSET0 = (cmd & 0x0f) << 14;

    IOCLR0 = RS;

    IOSET0 = E;
    delay_millisecond(2);
    IOCLR0 = E;
}

void LCD_DATA(unsigned char d)
{
    IOCLR0 = LCD_D;
    IOSET0 = (d & 0xf0) << 10;

    IOSET0 = RS;

    IOSET0 = E;
    delay_millisecond(2);
    IOCLR0 = E;

    IOCLR0 = LCD_D;
    IOSET0 = (d & 0x0f) << 14;

    IOSET0 = RS;

    IOSET0 = E;
    delay_millisecond(2);
    IOCLR0 = E;
}

void LCD_STR(unsigned char *s)
{
    int i;

    for(i = 0; s[i]; i++)
    {
        LCD_DATA(s[i]);
    }
}

void LCD_INTEGER(int n)
{
    unsigned char num[20];
    int i = 0;

    if(n < 0)
    {
        LCD_DATA('-');
        n = -n;
    }

    while(n > 0)
    {
        num[i++] = n % 10;
        n = n / 10;
    }

    for(i = i - 1; i >= 0; i--)
    {
        LCD_DATA(num[i] + 48);
    }
}

void LCD_FLOAT(float n)
{
    unsigned int temp = (int)n;

    LCD_INTEGER(temp);

    n = n - temp;

    LCD_DATA('.');

    LCD_INTEGER(n * 100);
}

void LCD_SCROLL(unsigned char *s, unsigned char data)
{
    unsigned char i, j, n;

    for(n = 0; s[n]; n++);

    j = n;

    for(i = 0; i < 16; i++)
    {
        LCD_COMMAND(0x01);

        LCD_COMMAND(data + i);

        LCD_STR(s);

        if((16 - j) < i)
        {
            LCD_COMMAND(data);

            LCD_STR(s + (--n));
        }

        delay_millisecond(500);
    }
}
