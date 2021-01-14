/*
 * ex 7.c
 *
 *  Created on: Jan 14, 2021
 *      Author: Mohamed_ELkomy
 */

#include "stdio.h"

void main()
{
	float x,y;
	printf("Enter value of x:");
	fflush(stdout);
	scanf("%f",&x);
	printf("Enter value of y:");
	fflush(stdout);
	scanf("%f",&y);
	x+=y;
	y=x-y;
	x-=y;
	printf("After swapping, value of a = %f \n After swapping, value of b = %f",x,y);
}
