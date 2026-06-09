#include <LPC21xx.h>

#include "lcddisp.h"
#include "uart01.h"
#include "delay.h"

#define MOTOR  (1<<4)      // Active LOW LED/Motor
#define SOIL   (1<<5)      // Soil Sensor Digital Output

int data;
int dry_flag = 0;
int wet_flag = 0;

int main()
{
    UART0_CONFIG();
    LCD_INIT();

    /* Motor Output */
    IODIR0 |= MOTOR;

    /* Soil Sensor Input */
    IODIR0 &= ~SOIL;

    /* Motor OFF Initially */
    IOSET0 = MOTOR;

    /* Title Display */
    LCD_COMMAND(0x01);

    LCD_COMMAND(0x80);
    LCD_STR("SMART");

    LCD_COMMAND(0xC0);
    LCD_STR("IRRIGATION");

    delay_second(2);

    LCD_COMMAND(0x01);

    /* GSM Initialization */
    UART0_STR("AT\r\n");
    delay_second(1);

    UART0_STR("AT+CMGF=1\r\n");       // Text mode
    delay_second(1);

    UART0_STR("AT+CNMI=2,2,0,0,0\r\n"); // Forward SMS to UART
    delay_second(1);

    while(1)
    {
        /* SOIL DRY */
        if(((IOPIN0 >> 5) & 1) == 1)
        {
            if(!dry_flag)
            {
                LCD_COMMAND(0x01);

                LCD_COMMAND(0x80);
                LCD_STR("SOIL DRY");

                UART0_STR("AT+CMGS=\"+91xxxxxxxxxx\"\r\n");
                delay_second(1);

                UART0_STR("SOIL DRY");
                UART0_TX(0x0D);
                UART0_TX(0x0A);
                UART0_STR("SEND a TO ON");

                UART0_TX(0x1A);

                delay_second(3);

                dry_flag = 1;
                wet_flag = 0;
            }
        }

        /* SOIL WET */
        else if(((IOPIN0 >> 5) & 1) == 0)
        {
            if(!wet_flag)
            {
                LCD_COMMAND(0x01);

                LCD_COMMAND(0x80);
                LCD_STR("SOIL WET");

                UART0_STR("AT+CMGS=\"+91xxxxxxxxxx\"\r\n");
                delay_second(1);

                UART0_STR("SOIL WET");
                UART0_TX(0x0D);
                UART0_TX(0x0A);
                UART0_STR("SEND b TO OFF");

                UART0_TX(0x1A);

                delay_second(3);

                wet_flag = 1;
                dry_flag = 0;
            }
        }

        /* Check for GSM Commands */
        data = UART0_RX_CHECK();

        /* Motor ON */
        if(data == 'a')
        {
            IOCLR0 = MOTOR;

            LCD_COMMAND(0x01);

            LCD_COMMAND(0x80);
            LCD_STR("MOTOR ON");

            UART0_STR("AT+CMGS=\"+91xxxxxxxxxx\"\r\n");
            delay_second(1);

            UART0_STR("MOTOR ON");

            UART0_TX(0x1A);

            delay_second(2);
        }

        /* Motor OFF */
        else if(data == 'b')
        {
            IOSET0 = MOTOR;

            LCD_COMMAND(0x01);

            LCD_COMMAND(0x80);
            LCD_STR("MOTOR OFF");

            UART0_STR("AT+CMGS=\"+91xxxxxxxxxx\"\r\n");
            delay_second(1);

            UART0_STR("MOTOR OFF");

            UART0_TX(0x1A);

            delay_second(2);
        }
    }
}
