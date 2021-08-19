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
	  _E_text = .;
	}>flash

	.data :{
	  _S_data = .;
	  *(.data*)
	  _E_data = .;
	}>sram AT> flash

	.bss :{
	  _S_bss = . ;
	  *(.bss*)
	  _E_bss = .;
	  _stack_top = . +0x1000;
	}>sram
}