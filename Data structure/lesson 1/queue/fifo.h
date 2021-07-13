/*
 * fifo.h
 *
 *  Created on: Jul 7, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <stdint.h>

//user configuration
//select the elment type (uint8_t,unit16_t,uint32_t)
#define elment_type uint8_t
//create a static buffer 1
//#define length 5
//elment_type buffer [length]

//queue data_type
typedef struct{
	unsigned int length;
	unsigned int count;
	elment_type* base;
	elment_type* tail;
	elment_type* head;
}FIFO_buf_t;

typedef enum{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_null
}Bfffer_status;

//APIs

Bfffer_status FIFO_init (FIFO_buf_t* fifo ,elment_type* buf,int length);
Bfffer_status FIFO_enqueue (FIFO_buf_t* fifo ,elment_type item);
Bfffer_status FIFO_dequeue (FIFO_buf_t* fifo ,elment_type* item);
Bfffer_status FIFO_is_full (FIFO_buf_t* fifo );
void FIFO_print (FIFO_buf_t* fifo );

#endif /* FIFO_H_ */
