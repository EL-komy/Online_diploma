/*
 * Add Two Distances System.c
 *
 *  Created on: Jan 27, 2021
 *      Author: Mohamed_ELkomy
 */
#include <stdio.h>

struct unit{
	int feet;
	float inch;
};
struct unit add (struct unit a,struct unit b)
{
	struct unit c;
	c.feet=a.feet+b.feet;
	c.inch=a.inch+b.inch;
	return c;
}

void main()
{
	struct unit sa,sb,sc;
	printf("Enter information for 1st distance\nEnter feet: ");
	fflush(stdout);
	scanf("%d",&sa.feet);
	printf("Enter inch:");
	fflush(stdout);
	scanf("%f",&sa.inch);

	printf("Enter information for 2st distance\nEnter feet: ");
	fflush(stdout);
	scanf("%d",&sb.feet);
	printf("Enter inch:");
	fflush(stdout);
	scanf("%f",&sb.inch);
	sc=add(sa,sb);
	printf("Sum of distances= %d  %.2f",sc.feet,sc.inch);
}


