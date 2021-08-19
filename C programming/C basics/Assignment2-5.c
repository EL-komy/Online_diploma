/*
 * Assignment2-5.c
 *
 *  Created on: Jan 14, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	char x;
	printf("enter a character: ");
	fflush(stdout);
	scanf("%c",&x);
	switch(x)
	{
	case 'a'...'z':
	case 'A'...'Z':
	{
		printf("%c is an alphabet ",x);
	}
	break;
	default:
		printf("%c is not an alphabet ",x);
	}
}
