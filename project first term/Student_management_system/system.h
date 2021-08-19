/*
 * system.h
 *
 *  Created on: Jul 26, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef SYSTEM_H_
#define SYSTEM_H

#define dprintf(...) {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}

#include"stdio.h"

#define length_buffer 50


typedef struct{
		char fname [50];
		char lname [50];
		int id;
		float gpa;
		char cid [5];
	}student;

student std[length_buffer];

void add_student_file();
void add_student_manually();
void find_id();
void find_fn();
void find_c();
void tot_s();
void del_s();
void up_s();
void show_s();
void check(int n);

#endif /* SYSTEM_H_ */
