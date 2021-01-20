/*
 * Calculate Factorial ofa Number Using Recursion.c
 *
 *  Created on: Jan 19, 2021
 *      Author: Mohamed_ELkomy
 */
#include<stdio.h>

int fact(int n);

void main()
{
	int n;
	printf("Enter an positive integer: ");
	fflush(stdout);
	scanf("%d",&n);
	printf("Factorial of %d = %d",n,fact(n));
}
int fact(int n)
{
	//look at better sol at homework sol;
	int i,f=1;
	if(n==1)
	{
		return 1;
	}
	else
	{
		f=n*fact(n-1);
	}

	return f;
}
/*
#include<stdio.h>
int factorial(int n);
int main()
{
	int n;
	printf( " Enter an positive integer: ");
	scanf( "%d" ,&n);
	printf( "Factorial of %d = %ld" , n, factorial(n));
	return 0;
}
int factorial(int n)
{
	if(n!=1)
		return n*factorial(n-1);
}
*/

