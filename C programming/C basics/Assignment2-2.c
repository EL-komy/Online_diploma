/*
 * Assignment2-2.c
 *
 *  Created on: Jan 14, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	char x;
	printf("enter an alphabet: ");
	fflush(stdout);
	scanf("%c",&x);
	switch(x)
	{
	case 'a':
	case 'e':
	case 'o':
	case 'i':
	case 'u':
	case 'A':
	case 'E':
	case 'O':
	case 'I':
	case 'U':
	{
		printf("%c is a vowel.",x);
	}
	break;
	default:
	    printf("%c is a consonant.",x);
	}

}
