/*
 * multidimensional1.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

void main()
{
	float a[2][2] , b[2][2];
	int i,j;
	printf("Enter the elements of 1st matrix\n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("Enter a%d%d: ",i+1,j+1);
			fflush(stdout);
			scanf("%f",&a[i][j]);
		}
	}
	printf("Enter the elements of 2st matrix\n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("Enter b%d%d: ",i+1,j+1);
			fflush(stdout);
			scanf("%f",&b[i][j]);
		}
	}
	printf("Sum Of Matrix:\n");
	printf("%.1f   %.1f\n%.1f   %.1f",a[0][0]+b[0][0] ,a[0][1]+b[0][1],a[1][0]+b[1][0],a[1][1]+b[1][1]);

}
