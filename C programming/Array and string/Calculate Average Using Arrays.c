/*
 * Calculate Average Using Arrays.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	float a[100],sum=0;
	int n,i;
	printf("Enter the numbers of data : ");
	fflush(stdout);
	scanf("%d",&n);
	while(n>100||n<=0)
	{
		printf( "  number must be in range of (1 to 100)\n TRY AGAIN: ");
		fflush(stdout);
		scanf( "%d" ,&n);
	}
	for (i=0;i<n;i++)
	{
		printf("%d. Enter number: ",i+1);
		fflush(stdout);
		scanf("%f",&a[i]);
		sum+=a[i];
	}
	printf("Average=%.2f",sum/n);
}
