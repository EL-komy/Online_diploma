/*
 * Insert an element in an Array.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	int i,n,loc, ins,a[20];
	printf("Enter no of elements: ");
	fflush(stdout);
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}

	printf("Enter the element to be inserted: ");
	fflush(stdout);
	scanf("%d",&ins);

	printf("Enter the location: ");
	fflush(stdout);
	scanf("%d",&loc);
	for(i=n-1;i>=loc-1;i--)
	{
		a[i+1]=a[i];
		if(i==loc-1)
		{
			a[i]=ins;
		}
	}
	for(i=0;i<=n;i++)
	{
		printf("%d ",a[i]);
	}

}
