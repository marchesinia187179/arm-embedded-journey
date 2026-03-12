#include "../include/uart.h"

int main() {
    uart_init();
    uart_puts("Echo System actived\n");
    uart_puts("Type a key on the keyboard...\n");

    while (1) {
        char c = uart_getc();

        uart_puts("Recived: ");

        /* Build a string for the uart_puts.
         * An array of two characters: the pressed character + the null terminator */
        char echo_str[2] = {c, '\0'};
        uart_puts(echo_str);
        uart_putc('\n');

        /* Easter egg */
        if (c == '!') {
            uart_puts("You actived the secret command!\n");
        }
    }

    return 0;
}
