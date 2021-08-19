/*
 * Prime Numbers Between two Intervals.c
 *
 *  Created on: Jan 19, 2021
 *      Author: Mohamed_ELkomy
 */

#include<stdio.h>

void prime(int x, int y);

void main()
{
	int a,b;
	printf("Enter twooo numbers(intervals):");
	fflush(stdout);
	scanf("%d%d",&a,&b);
	prime(a,b);
}

void prime(int x, int y)
{
	int i,j,m;
	printf("Prime numbers between %d and %d are: ",x,y);
	for(i=x;i<=y;i++)
	{
		if(i==2 || i==3)
		{
			printf("%d ",i);
		}
		for(j=2;j<=i/2 ;j++)
		{
			m=0;
			if(i%j==0)
			{
				m=1;
				break;
			}
		}
		if(m==0)
		{
			printf("%d ",i);
		}
	}
}
