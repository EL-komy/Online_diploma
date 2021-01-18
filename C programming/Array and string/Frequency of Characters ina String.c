/*
 * Frequency of Characters ina String.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	char str [100],i=0,c,count=0;
	printf("Enter a string: ");
	fflush(stdout);
	gets(str);
	printf("Enter a character to find frequency: ");
	fflush(stdout);
	scanf("%c",&c);
	while(str[i]!=0)
	{
		if(str[i]==c ||str[i]==c-32 )
			count++;
		i++;
	}
	printf("frequency of %c = %d",c,count);
}
