ENTRY(reset)


MEMORY
{
	mem(rwx) : o = 0x00000000 , l =64M	
}

SECTIONS
{
	. =0x10000;
	.startup . :	
	{
		startup.o (.text)
	}>mem
	.text :
	{
		*(.text) *(.rodata)
	}>mem
	.data :
	{
		*(.data) 
	}>mem
	.bss :
	{
		*(.bss) 
	}>mem
	. = . +0x1000;
	stack_top = .;
}
