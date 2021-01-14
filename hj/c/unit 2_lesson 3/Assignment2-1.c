/*
 * Assignment2-1.c
 *
 *  Created on: Jan 14, 2021
 *      Author: Mohamed_ELkomy
 */

#include "stdio.h"

void main()
{
	int x;
	printf("Enter an integer you want to check: ");
	fflush(stdout);
	scanf("%d",&x);

	if(x%2==0)
	{
		printf("%d is even",x);
	}
	else
	{
		printf("%d is odd",x);
	}


}
