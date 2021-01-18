/*
 * Transpose ofa Matrix.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	int r,c,i,j;
	float a [10][10];
	printf("Enter rows and column of matrix: ");
	fflush(stdout);
	scanf("%d%d",&r,&c);
	printf("Enter elements of matrix:\n");
	while(r>10 || c>10 || r<0 || c<0)
	{
		printf( "  number must be in range of (1*1 to 10*10)\n TRY AGAIN: ");
		fflush(stdout);
		scanf("%d%d",&r,&c);
	}
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("Enter elements a%d%d: ",i+1,j+1);
			fflush(stdout);
			scanf("%f",&a[i][j]);
		}
	}
	printf("Entered Matrix:\n ");

	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%.1f   ",a[i][j]);
		}

		printf("\n ");
	}

	printf("\nTranspose of Matrix:\n ");

	for(i=0;i<c;i++)
	{
		for(j=0;j<r;j++)
		{
			printf("%.1f  ",a[j][i]);
		}

		printf("\n ");
	}

}
