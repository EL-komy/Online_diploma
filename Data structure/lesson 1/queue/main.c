/*
 * main.c
 *
 *  Created on: Jul 7, 2021
 *      Author: Mohamed_ELkomy
 */

#include"fifo.h"
#define length_buffer 5
elment_type buffer[length_buffer];
void main()
{
	int i,temp=0;
	FIFO_buf_t uart;
	if(FIFO_init(&uart,buffer,length_buffer)==FIFO_no_error)
		printf("===the init is done\n");
	for(i=0;i<7;i++)
	{
		if(FIFO_enqueue(&uart,i)==FIFO_no_error)
			printf("add %d is done\n",i);
		else
			printf("add %d is failed\n",i);
	}
	FIFO_print(&uart);
	FIFO_dequeue(&uart,&temp);
	printf("remove %d is done\n",temp);
	FIFO_dequeue(&uart,&temp);
	printf("remove %d is done\n",temp);
	FIFO_dequeue(&uart,&temp);
	printf("remove %d is done\n",temp);
	FIFO_print(&uart);
	for(i=5;i<8;i++)
	{
		if(FIFO_enqueue(&uart,i)==FIFO_no_error)
			printf("add %d is done\n",i);
		else
			printf("add %d is failed\n",i);
	}
	FIFO_print(&uart);
}
