/*
 * lifo.h
 *
 *  Created on: Jul 4, 2021
 *      Author: Mohamed_ELkomy
 */
#include<stdio.h>

#ifndef LIFO_H_
#define LIFO_H_

typedef struct {
	unsigned int* base;
	unsigned int* head;
	unsigned int count;
	unsigned int length;
}LIFO_BUF;

typedef enum {
	lifo_no_error,
	lifo_full,
	lifo_empty,
	lifo_null
}life_satus;

//APIs

life_satus LIFO_INIT(LIFO_BUF* lifo_name,unsigned int* buf,unsigned int length);
life_satus LIFO_ADD_ITME(LIFO_BUF* lifo_name,unsigned int item);
life_satus LIFO_GET_ITME(LIFO_BUF* lifo_name,unsigned int* item);

#endif /* LIFO_H_ */
