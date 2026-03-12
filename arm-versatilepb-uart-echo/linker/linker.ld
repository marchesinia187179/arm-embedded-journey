/* Definition of entry points and memory regions */
ENTRY(_Reset)   /* The CPU starts from here */

MEMORY
{
    /* A "VersatilePB" board is emulate */
    FLASH (rx) : ORIGIN = 0x00010000, LENGTH = 128K
    RAM (rwx) : ORIGIN = 0x00030000, LENGTH = 128K
}

SECTIONS
{
    /* This code goes to the Flash */
    .text :
    {
        *(.vector_table)    /* Interrupt table */
        *(.text)    /* C code */
    } > FLASH

    /* Initialized global variables */
    .data :
    {
        *(.data)
    } > RAM AT > FLASH  /* Load in Flash, but use in RAM */

    /* Non-initialized global variables (zeroed at startup) */
    .bss :
    {
        *(.bss)
        *(COMMON)
    } > RAM
}