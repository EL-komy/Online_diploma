/*
 * lifo.c
 *
 *  Created on: Jul 4, 2021
 *      Author: Mohamed_ELkomy
 */

#include"lifo.h"

life_satus LIFO_INIT(LIFO_BUF* lifo_name,unsigned int* buf,unsigned int length)
{
	if(buf==NULL)
		return lifo_null;
	lifo_name->base=buf;
	lifo_name->head=buf;
	lifo_name->count=0;
	lifo_name->length=length;
	return lifo_no_error;
}
life_satus LIFO_ADD_ITME(LIFO_BUF* lifo_name,unsigned int item)
{
	if(!lifo_name->base || !lifo_name->head)
			return lifo_null;
	if(lifo_name->count==lifo_name->length)
		return lifo_full;
	*(lifo_name->head) = item;
	lifo_name->head++;
	lifo_name->count++;
	return lifo_no_error;
}
life_satus LIFO_GET_ITME(LIFO_BUF* lifo_name,unsigned int* item)
{
	if(!lifo_name->base || !lifo_name->head)
				return lifo_null;
	if(lifo_name->count==0)
		return lifo_empty;

	lifo_name->head--;
	*item=*(lifo_name->head);
	lifo_name->count--;
	return lifo_no_error;
}


