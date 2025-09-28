ENTRY(_start)

MEMORY
{
  ROM (rx)  : ORIGIN = 0x0000, LENGTH = 32K
  RAM (rwx) : ORIGIN = 0x8000, LENGTH = 32K
}

SECTIONS
{
  .text : { *(.text*) } > ROM

  .data : { *(.data*) } > RAM AT > ROM
  .bss  : { *(.bss*) *(COMMON) } > RAM

  _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
