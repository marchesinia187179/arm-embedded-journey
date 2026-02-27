/* UART (Serial Port) address definition */
#define UART0_ADDR 0x101f1000
volatile unsigned int * const UART0DR = (unsigned int *)UART0_ADDR;

void print_uart(const char *s) {
    while(*s != '\0') {
        *UART0DR = (unsigned int)(*s);
        s++;
    }
}

int main() {
    print_uart("Hello, World!\n");

    while (1) {
        __asm__("nop");
    }

    return 0;
}