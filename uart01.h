#include <LPC21xx.h>

void UART0_CONFIG(void);
void UART0_TX(unsigned char d);
void UART0_STR(char *s);
unsigned char UART0_RX(void);
int UART0_RX_CHECK(void);

void UART0_CONFIG(void)
{
    PINSEL0 |= 0x00000005;      // P0.0 -> TXD0, P0.1 -> RXD0

    U0LCR = 0x83;               // 8-bit data, 1 stop bit, DLAB = 1

    U0DLL = 97;                 // 9600 baud rate for 15 MHz PCLK
    U0DLM = 0;

    U0LCR = 0x03;               // DLAB = 0
}

void UART0_TX(unsigned char d)
{
    while((U0LSR & (1<<5)) == 0);

    U0THR = d;
}

void UART0_STR(char *s)
{
    while(*s)
    {
        UART0_TX(*s++);
    }
}

unsigned char UART0_RX(void)
{
    while((U0LSR & 1) == 0);

    return U0RBR;
}

int UART0_RX_CHECK(void)
{
    if(U0LSR & 1)
    {
        return U0RBR;
    }

    return -1;                  // No data available
}
