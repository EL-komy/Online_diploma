/*
 * print all the alphabets using a pointer.c
 *
 *  Created on: Feb 15, 2021
 *      Author: Mohamed_ELkomy
 */

#include<stdio.h>

void main()
{
	char s[27],i;
	char *pt=s;
	for(i=0;i<26;i++)
	{
		*pt=(i+'A');
		pt++;
	}
	pt=&s;

	for(i=0;i<26;i++)
	{
		printf("%c  ",*(pt+i));
	}
}
