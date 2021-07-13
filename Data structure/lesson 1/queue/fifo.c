/*
 * fifo.c
 *
 *  Created on: Jul 7, 2021
 *      Author: Mohamed_ELkomy
 */
#include "fifo.h"

Bfffer_status FIFO_init (FIFO_buf_t* fifo ,elment_type* buf,int length)
{
	fifo->base=buf;
	fifo->tail=buf;
	fifo->head=buf;
	fifo->length=length;
	fifo->count=0;
	if(fifo->base && fifo->length)
		return FIFO_no_error;
	return FIFO_null;
}
Bfffer_status FIFO_enqueue (FIFO_buf_t* fifo ,elment_type item)
{
	if(FIFO_is_full(fifo)==FIFO_full)
		return FIFO_full;
	fifo->count++;
	*fifo->head=item;
	if(fifo->head==(fifo->base +( fifo->length * sizeof (elment_type))))
		fifo->head=fifo->base ;
	else
		fifo->head++;
	return FIFO_no_error;

}

Bfffer_status FIFO_dequeue (FIFO_buf_t* fifo ,elment_type* item )
{
	if(!fifo->base ||!fifo->head || !fifo->tail )
		return FIFO_null;
	if(fifo->count ==0 )
		return FIFO_empty;
	*item=*fifo->tail;
	fifo->count--;
	if(fifo->tail==(fifo->base +( fifo->length * sizeof (elment_type))))
		fifo->tail=fifo->base ;
	else
		fifo->tail++ ;
}
Bfffer_status FIFO_is_full (FIFO_buf_t* fifo )
{
	if(!fifo->base ||!fifo->head || !fifo->tail )
		return FIFO_null;
	if(fifo->count >= fifo->length)
	{
		return FIFO_full;
	}
	return FIFO_no_error;
}
void FIFO_print (FIFO_buf_t* fifo )
{
	elment_type* item;
	int i;
	if(fifo->count ==0 )
	{
		printf("the queue is empty\n");
	}
	item=fifo->tail;
	printf("====print the queue======\n");
	for(i=0;i<fifo->count;i++)
	{
		printf("\t%d\n",*item);
		if(item==(fifo->base +( fifo->length * sizeof (elment_type))))
			item=fifo->base ;
		else
			item++;
	}
	printf("==========\n");
}


