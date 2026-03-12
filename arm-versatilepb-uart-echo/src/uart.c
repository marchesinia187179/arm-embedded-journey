#include "../include/uart.h"
/* UART (Serial Port) address definition */
#define UART0_ADDR 0x101f1000
/* Data Register: where we write and read the data */
#define UART0_DR ((volatile unsigned int *)(UART0_ADDR + 0x00))
/* Flag Register: where we have the UART status (full, empty, busy) */
#define UART0_FR ((volatile unsigned int *)(UART0_ADDR + 0x18))
/* Control Register */
#define UART0_CR ((volatile unsigned int *)(UART0_ADDR + 0x30))
#define UART_CR_UARTEN (1 << 0)
#define UART_CR_TXE    (1 << 8)
#define UART_CR_RXE    (1 << 9)

void uart_init(void) {
    /* Abilita la UART */
    *UART0_CR = 0x0; 
    *UART0_CR = UART_CR_UARTEN | UART_CR_TXE | UART_CR_RXE;
}

void uart_putc(char c) {
    *UART0_DR = (unsigned int)c;
}

void uart_puts(const char *s) {
    while(*s != '\0') {
        uart_putc(*s++);
    }
}

/* Polling communication where the CPU queries the hardware until something happens */
char uart_getc() {
    /* Check the fourth bit of the Flag Register (RXFE - Receive FIFO Empty) 
     * It is 1 if the "tank" is empty, 0 otherwise (data arrived) */
    while (*UART0_FR & (1 << 4));

    /* We read the data arrived masking the first 8 bits */
    return (char)(*UART0_DR & 0xFF);
}