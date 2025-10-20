/* Entry Point */
ENTRY(Reset_Handler)


M_VECTOR_RAM_SIZE = 0x0400;

/* Specify the memory areas */
MEMORY
{

  ITCM                  (RW)  : ORIGIN = 0x00000000, LENGTH = 0x00008000  /* 32KB */

  SRAM0                 (RW)  : ORIGIN = 0x21000000, LENGTH = 0x00010000  /* 64KB */
  SRAM1                 (RW)  : ORIGIN = 0x21010000, LENGTH = 0x00008000  /* 32KB */

  DFLASH                (RW)  : ORIGIN = 0x04000000, LENGTH = 0x00020000  /* 128KB */

  NVR0                   (RW)  : ORIGIN = 0x04400000, LENGTH = 0x00004000  /* 16KB */
  NVR1                   (RW)  : ORIGIN = 0x04408000, LENGTH = 0x00004000  /* 16KB */
  NVR2                   (RW)  : ORIGIN = 0x04410000, LENGTH = 0x00002000  /* 8KB */

  /* DTCM */
  DTCM                     (RW)  : ORIGIN = 0x20000000, LENGTH = 0x0001FA00    /* 128K - 0x600  */
  DTCM_STACK               (RW)  : ORIGIN = 0x2001FA00, LENGTH = 0x00000600    /* 0x600  */


}

/* Define output sections */
SECTIONS
{

      /* The program code and other data goes into internal flash */
      .text :
      {
        . = ALIGN(1024); /* VTOR must be align to 1K */
        __vector_table = .;
        __interrupts_start__ = .;
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        __interrupts_end__ = .;
        . = ALIGN(4);
        
        *(.text)                 /* .text sections (code) */
        *(.text*)                /* .text* sections (code) */
        *(.rodata)               /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
        *(.init)                 /* section used in crti.o files */
        *(.fini)                 /* section used in crti.o files */
        *(.eh_frame)             /* section used in crtbegin.o files */
        . = ALIGN(4);
      } > SRAM0

    .data :
    {
        __ram_data_start = .;
        . = ALIGN(4);
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __ram_data_end = .;

    } > DTCM AT > SRAM0

    .ncache_data :
    {
        . = ALIGN(4);
        __ram_ncache_data_start = .;
        *(.nocacheable_data*)
        __ram_ncache_data_end = .;
        . = ALIGN(4);
    } > SRAM1 AT > SRAM0

    .bss(NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
        . = ALIGN(4);
    } > DTCM

    .ncache_bss(NOLOAD) :
    {
        . = ALIGN(4);
        __ncache_bss_start = .;
        *(.nocacheable_bss*)
        __ncache_bss_end = .;
        . = ALIGN(4);
    } > SRAM1


    __HeapBegin = ORIGIN(DTCM_STACK);
    __HeapLimit = ORIGIN(DTCM_STACK) + 0x200 - 8;
    
    __StackLimit = ORIGIN(DTCM_STACK)+0x200;
    __StackTop = ORIGIN(DTCM_STACK) + LENGTH(DTCM_STACK) - 8;

    __rom_data_start = LOADADDR(.data);
    __rom_ncache_data_start = LOADADDR(.ncache_data);

}

