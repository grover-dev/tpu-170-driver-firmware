/* Linker Script based off of https://www.youtube.com/watch?v=B7oKdUvRhQQ */
ENTRY(reset_handler)

MEMORY
{
	FLASH(rx) : ORIGIN = 0x00, LENGTH = 0x8000
    RAM(rwx) : ORIGIN =  0x10000000, LENGTH = 0x2000
    /*RAM0(rwx) : ORIGIN = 0x10000000, LENGTH = 0x1000
    RAM1(rwx) : ORIGIN = 0x10001000, LENGTH = 0x1000
    ROM(rx) : ORIGIN = 0x1FFF0000, LENGTH = 0x3000*/ 
}

SECTIONS 
{
    .text : ALIGN(4)
    {   
        __vectors_start__ = ABSOLUTE(.);
        KEEP(*(.isr_vector))
        /* Global Section Table */
           . = ALIGN(4) ;
           __section_table_start = .;
           __data_section_table = .;
           LONG(LOADADDR(.data));
           LONG(    ADDR(.data));
           LONG(  SIZEOF(.data));
          __data_section_table_end = .;
           __bss_section_table = .;
           LONG(    ADDR(.bss));
          LONG(  SIZEOF(.bss));
           __bss_section_table_end = .;
           __section_table_end = . ;
         /* End of Global Section Table */
 

        
        *(.after_vectors*)

        . = 0x02FC;


        *(.text*)
        *(.rodata)
        _etext = .;
    }> FLASH /* >vma AT> lma */


    .data :
    {
        __data_start__ = .;
        *(.data)
        __data_end__ = .;
    }> RAM AT> FLASH
 
    .bss :
    {
        __bss_start__ = .;
        *(.bss)
        __bss_end__ = .;
    }> RAM



    .noinit (NOLOAD): ALIGN(4)
      {
          _noinit = .;
          PROVIDE(__start_noinit_RAM = .) ;
          PROVIDE(__start_noinit_RamLoc8 = .) ;
          *(.noinit*)
           . = ALIGN(4) ;
          _end_noinit = .;
         PROVIDE(__end_noinit_RAM = .) ;
         PROVIDE(__end_noinit_RamLoc8 = .) ;
      } > RAM
    PROVIDE(_vStackTop = 0x10000000 + 0x2000);



}
