#include"uart.h"

char arr[100]="learn-in-depth:ELKOMY";

void main(void)
{
	uart_send_string(arr);
}