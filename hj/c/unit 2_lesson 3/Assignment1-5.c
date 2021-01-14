/*
 * main.c
 *
 *  Created on: Jan 6, 2021
 *      Author: Mohamed_ELkomy
 */


# include "stdio.h"

void main()
{
	int a;
	printf("Enter a character:");
	fflush (stdout);
	fflush (stdin);
	scanf("%c",&a);
	printf("ASCII value of %c = %d",a,a);

}
