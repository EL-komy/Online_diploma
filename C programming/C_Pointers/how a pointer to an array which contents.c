/*
 * how a pointer to an array which contents.c
 *
 *  Created on: Feb 16, 2021
 *      Author: Mohamed_ELkomy
 */

#include<stdio.h>

struct emp
{
	char name[20];
	int id;
};

void main()
{
	struct emp a={"alex",1002},s={"ali",158},d={"ter",897};
	struct emp *e[4]={&a,&s,&d};
	struct emp *(*pe)[3]=e;
	printf("Exmployee Name : %s \n "
			"Employee ID :%d",(*(*pe))->name,(*(*pe))->id);
}
