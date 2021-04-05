/*
 * demonstrate how to handle the pointers in the program.c
 *
 *  Created on: Feb 15, 2021
 *      Author: Mohamed_ELkomy
 */

#include<stdio.h>

void main()
{
	int m=29;
	in* ptm=&m,u=5;
	printf("Address of m : %p \n Value of m : %d\n\n",&m,m );

	printf("Address of pointer ptm : %p \n Content of pointer ptm : %d\n\n",ptm,*ptm );

	*ptm=34;
	printf("Address of pointer ptm : %p \n Content of pointer ptm : %d\n\n",ptm,*ptm );

	*ptm=7;
	printf("Address of pointer ptm : %p \n Content of pointer ptm : %d\n\n",ptm,*ptm );
}
