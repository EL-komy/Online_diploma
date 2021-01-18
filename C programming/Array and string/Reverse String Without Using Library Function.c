/*
 * Reverse String Without Using Library Function.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Mohamed_ELkomy
 */
#include<stdio.h>
#include<string.h>

void main()
{
	char str [100],i;
	printf("Enter the string  : ");
	fflush(stdout);
	gets(str);
	printf("Reverse string is : ");
	for(i=strlen(str)-1;i>=0;i--)
	{
		printf("%c",str[i]);
	}
}
