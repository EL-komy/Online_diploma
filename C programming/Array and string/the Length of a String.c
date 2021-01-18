/*
 * the Length of a String.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Mohamed_ELkomy
 */

#include<stdio.h>

void main()
{
	char str [100],i=0,count=0;
	printf("Enter a string: ");
	fflush(stdout);
	gets(str);
	while(str[i]!=0)
	{
		count++;
		i++;
	}
	printf("Length of string: %d",count);
}
