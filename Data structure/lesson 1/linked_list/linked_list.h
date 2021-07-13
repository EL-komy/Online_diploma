/*
 * linked_list.h
 *
 *  Created on: Jul 8, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define dprintf(...) {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}


struct sdata{
	int id;
	float hight;
	char name[40];
};

struct ssudent{
	struct sdata student;
	struct ssudent* pNextstudent;
};

struct ssudent* head;

void fill_the_record (struct ssudent* new_student);
void add_student();
int delet_student();
void view_student();
void delet_all();
void value_of_item();
int get_count(struct ssudent* Pslectedstudent);
void node_valuo_from_end();
void get_middle();
void detect_loop();
void reverse();

#endif /* LINKED_LIST_H_ */
