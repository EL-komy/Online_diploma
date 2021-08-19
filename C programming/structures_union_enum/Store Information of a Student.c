/*
 * Store Information of a Student.c
 *
 *  Created on: Jan 27, 2021
 *      Author: Mohamed_ELkomy
 */

#include <stdio.h>

struct s_student{
	char name[15];
	char roll;
	float marks;
};

void main()
{
	struct s_student s;
	printf("Enter information of students:\nEnter name:");
	fflush(stdout);
	gets(s.name);
	printf("Enter roll number:");
	fflush(stdout);
	scanf("%d",&s.roll);
	printf("Enter marks:");
	fflush(stdout);
	scanf("%f",&s.marks);
	printf("Displaying Information\n");
	printf("name: %s \nroll: %d \nmarks: %.3f",s.name,s.roll,s.marks);
}
