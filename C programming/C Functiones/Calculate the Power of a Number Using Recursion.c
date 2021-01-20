/*
 * Calculate the Power of a Number Using Recursion.c
 *
 *  Created on: Jan 19, 2021
 *      Author: Mohamed_ELkomy
 */
#include<stdio.h>

int power(int x, int y);

void main()
{
	int x,y;
	printf("Enter base number: ");
	fflush(stdout);
	scanf("%d",&x);
	printf("Enter power number(positive integer): ");
	fflush(stdout);
	scanf("%d",&y);
	printf("%d^%d = %d",x,y,power(x,y));
}
int power(int x, int y)
{
	int p=1;
	if(y==1)
	{
		return x;
	}
	p=x*power(x,y-1);
	return p;

}
