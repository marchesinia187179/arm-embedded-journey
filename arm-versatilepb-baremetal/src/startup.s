.section .vector_table, "a"
.global _Reset
_Reset:
    ldr sp, =stack_top @ Set the Stack Pointer
    mov r0, #0
    bl main @ Jump to the main function in C
    b . @ If the main comes out, it stays here in a infinite loop

.section .stack
.align 3
stack_bottom:
    .space 0x1000
stack_top:
.global stack_top
