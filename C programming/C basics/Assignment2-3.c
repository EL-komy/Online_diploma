/*
 * Assignment2-3.c
 *
 *  Created on: Jan 14, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	float x,y,z;
	printf("Enter three numbbers:");
	fflush(stdout);
	scanf("%f%f%f",&x,&y,&z);
	if(x>y)
	{
		if(x>z)
		{
			printf("Largest number = %.2f",x);
		}
		else
		{
			printf("Largest number = %.2f",z);
		}
	}
	else if(y>x)
	{
		if(y>z)
		{
			printf("Largest number = %.2f",y);
		}
		else
		{
			printf("Largest number = %.2f",z);
		}
	}
}
