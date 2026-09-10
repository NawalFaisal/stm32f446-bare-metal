ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Stack starts at the top of RAM and grows downward */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    /* Must be first so it lands at 0x08000000, where the CPU looks on reset.
     * KEEP stops the linker discarding it — nothing references it.
     */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* > FLASH: stored in flash, runs from flash. Code never moves to RAM. */
    .text :
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    /* Two addresses:
     *   > RAM     = where these variables live and get modified
     *   AT> FLASH = where their initial values are stored, since RAM
     *               holds nothing at power-on
     * Startup must copy flash -> RAM. Not written yet.
     */
    .data :
    {    _sdata = .;
        *(.data*)
         _edata = .;
    } > RAM AT> FLASH

    /* No initial values to store — just reserved space in RAM.
     * Costs zero flash. Startup zeroes it.
     */
    .bss :
    {    _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM
}

/*
 * A global initialized to 0 still held garbage. `= 0` doesn't write a zero
 * anywhere — it only tells the compiler to place the variable in .bss.
 * The zeroing has to happen at runtime, and my startup went straight to
 * main without doing it. Fixed by exporting _sbss/_ebss and writing zeros
 * between them in Reset_Handler.
 */