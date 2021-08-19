/*
 * Search an element in Array.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	int i,n,ser,a[20];
	printf("Enter no of elements: ");
	fflush(stdout);
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}

	printf("Enter the element to be searched: ");
	fflush(stdout);
	scanf("%d",&ser);

	for(i=0;i<n;i++)
	{
		if(a[i]==ser)
		{
			printf("Number found at the location= %d",i+1);
			break;
		}
	}
	if(i==n)
	{
		printf("Number (%d) is not found in the list",ser);
	}
}
