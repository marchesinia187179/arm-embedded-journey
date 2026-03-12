/* UART (Serial Port) address definition */
#define UART0_ADDR 0x101f1000
/* Data Register: where we write and read the data */
#define UART0_DR ((volatile unsigned int *)(UART0_ADDR + 0x00))
/* Flag Register: where we have the UART status (full, empty, busy) */
#define UART0_FR ((volatile unsigned int *)(UART0_ADDR + 0x18))

void print_uart(const char *s) {
    while(*s != '\0') {
        *UART0_DR = (unsigned int)(*s);
        s++;
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

int main() {
    print_uart("Echo System actived\n");
    print_uart("Type a key on the keyboard...\n");

    while (1) {
        char c = uart_getc();

        print_uart("Recived: ");

        /* Build a string for the print_uart.
         * An array of two characters: the pressed character + the null terminator */
        char echo_str[2] = {c, '\0'};
        print_uart(echo_str);
        print_uart("\n");

        /* Easter egg */
        if (c == '!') {
            print_uart("You actived the secret command!\n");
        }
    }

    return 0;
}