/*
 * print a string in reverse using a pointer.c
 *
 *  Created on: Feb 16, 2021
 *      Author: Mohamed_ELkomy
 */

#include<stdio.h>
#include"string.h"

void main()
{
	char str[20],l,*pstr,i;
	printf("Input a string : ");
	fflush(stdout);
	gets(str);
	l=strlen(str)-1;
	pstr=&str[l];
	printf("Reverse of the string is : ");
	for(i=0;i<=l;i++,pstr--)
	{
		printf("%c",*pstr);
	}
}
