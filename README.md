# STM32 Knowledge Base
- Projects with drivers: hal/bare/rtos
- Tested using G070 board

Note:
Update to remote the linker error: (READONLY) keyword
.ARM.extab (READONLY) : {
. = ALIGN(4);
*(.ARM.extab* .gnu.linkonce.armextab.*)
. = ALIGN(4);
} >FLASH

 .ARM (READONLY) : {
. = ALIGN(4);
__exidx_start = .;
*(.ARM.exidx*)
__exidx_end = .;
. = ALIGN(4);
} >FLASH

 .preinit_array (READONLY) :
{
. = ALIGN(4);
PROVIDE_HIDDEN (__preinit_array_start = .);
KEEP (*(.preinit_array*))
PROVIDE_HIDDEN (__preinit_array_end = .);
. = ALIGN(4);
} >FLASH

 .init_array (READONLY):
{
. = ALIGN(4);
PROVIDE_HIDDEN (__init_array_start = .);
KEEP (*(SORT(.init_array.*)))
KEEP (*(.init_array*))
PROVIDE_HIDDEN (__init_array_end = .);
. = ALIGN(4);
} >FLASH

 .fini_array (READONLY):
{
. = ALIGN(4);
PROVIDE_HIDDEN (__fini_array_start = .);
KEEP (*(SORT(.fini_array.*)))
KEEP (*(.fini_array*))
PROVIDE_HIDDEN (__fini_array_end = .);
. = ALIGN(4);
} >FLASH