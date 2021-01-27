/*
 * Store Information of Students Using Structure.c
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
void enter(struct s_student s[])
{
	char i;
	for(i=0;i<3;i++)
	{
		printf("Enter name(%d): ",i);
		fflush(stdout);
		fflush(stdin);
		gets(s[i].name);
		printf("Enter roll number(%d): ",i);
		fflush(stdout);
		scanf("%d",&s[i].roll);
		printf("Enter marks(%d): ",i);
		fflush(stdout);
		scanf("%f",&s[i].marks);
	}
}

void print(struct s_student s[])
{
	char i;
	for(i=0;i<3;i++)
	{
		printf("roll: %d \nname: %s \nmarks: %.3f\n",s[i].roll,s[i].name,s[i].marks);
	}
}

void main()
{
	struct s_student s[3];
	enter(s);
	printf("Displaying Information\n");
	print(s);
}


