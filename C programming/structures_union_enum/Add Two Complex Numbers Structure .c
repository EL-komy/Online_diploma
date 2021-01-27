/*
 * Add Two Complex Numbers Structure .c
 *
 *  Created on: Jan 27, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

struct complex{
	float real;
	float imaginary;
};
struct complex add (struct complex a,struct complex b)
{
	struct complex c;
	c.real=a.real+b.real;
	c.imaginary=a.imaginary+b.imaginary;
	return c;
}

void main()
{
	struct complex sa,sb,sc;
	printf("For 1st complex number\nEnter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f%f",&sa.real,&sa.imaginary);

	printf("For 2st complex number\nEnter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f%f",&sb.real,&sb.imaginary);
	sc=add(sa,sb);
	printf("Sum= %.2f+%.2fi",sc.real,sc.imaginary);
}


