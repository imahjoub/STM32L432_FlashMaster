
ENTRY(__my_startup)

INPUT(libc.a libm.a libgcc.a)

/* Set up a stack */
__initial_stack_pointer = 0x20005000;

MEMORY
{
  FLASH (RX) : ORIGIN = 0x08000000, LENGTH = 0x10000
  RAM (RWX)  : ORIGIN = 0x20000000, LENGTH = 0x05000
}

SECTIONS
{
  .isr_vector 0x08000000 :
  {
    isr_vector = .;
    KEEP(*(.isr_vector))
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    _stext = .;
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);
    _etext = .;
  } >FLASH

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >FLASH

  .ARM : {
    *(.ARM.exidx*)
  } >FLASH

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM AT >FLASH

  _ldata = LOADADDR(.data);

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

}
