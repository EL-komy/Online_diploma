#include<stdint.h>

extern uint32_t _E_text;
extern uint32_t _S_data;
extern uint32_t _E_data;
extern uint32_t _S_bss;
extern uint32_t _E_bss;
extern uint32_t _stack_top;

extern void main();

void reset_handler()
{
	uint32_t data_size = (unsigned char*)&_E_data - (unsigned char*)& _S_data;
    unsigned char * p_scr= (unsigned char*)& _E_text;
	unsigned char * p_dst= (unsigned char*)& _S_data;
    int i;
    for(i=0;i<data_size;i++)
    {
    	*(unsigned char*) p_dst++ = * (unsigned char*) p_scr++;
    }

    uint32_t bss_size = (unsigned char*)&_E_bss - (unsigned char*)& _S_bss;
    p_dst= (unsigned char*)& _S_bss;
	
    for(i=0;i<bss_size;i++)
    {
    	*(unsigned char*) p_dst++ = (unsigned char) 0;
    }

	main();
}

void default_handler()
{
	reset_handler();
}
void nmi_handler() __attribute__((weak,alias("default_handler")));
void h_fault_handler() __attribute__((weak,alias("default_handler")));
void bus_fault() __attribute__((weak,alias("default_handler")));

uint32_t vectors[] __attribute__((section(".vectors"))) ={
	(uint32_t) &_stack_top,
	(uint32_t) &reset_handler,
	(uint32_t) &nmi_handler,
	(uint32_t) &h_fault_handler,
	(uint32_t) &bus_fault,
};

