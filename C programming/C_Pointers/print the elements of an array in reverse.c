/*
 * print the elements of an array in reverse.c
 *
 *  Created on: Feb 16, 2021
 *      Author: Mohamed_ELkomy
 */

#include<stdio.h>

void main()
{
	char num[15],l,*pnum,i;
	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdout);
	scanf("%d",&l);
	printf("Input &d number of elements in the array :\n",l);
	for(i=0;i<l;i++)
	{
		printf("element - %d : ",i+1);
		fflush(stdout);
		scanf("%d",&num[i]);
	}
	pnum=&num[l-1];
	printf("The elements of array in reverse order are :\n",l);
	for(i=l;i>0;i--,pnum--)
	{
		printf("element - %d : %d\n ",i,*pnum);
	}
}
