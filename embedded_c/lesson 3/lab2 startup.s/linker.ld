MEMORY
{
	flash(rx) : o = 0X08000000, l = 128M
	sram(rwx):  o = 0X20000000, l = 20K
}

SECTIONS
{
	.text : {
	  *(.vectors*)
	  *(.text*)
	}>flash

	.data :{
	  *(.data*)
	}>flash

	.bss :{
	  *(.bss*)
	}>sram
}