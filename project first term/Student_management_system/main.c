/*
 * main.c
 *
 *  Created on: Jul 7, 2021
 *      Author: Mohamed_ELkomy
 */

#include "system.h"

void main()
{
	char temp[20],i=1;
	while(i)
	{
		dprintf("\n===============");
		dprintf("\n\t choose one of the following options:");
		dprintf("\n 1: Add student from text file");
		dprintf("\n 2: Add student manually");
		dprintf("\n 3: find student by id");
		dprintf("\n 4: find student by first name");
		dprintf("\n 5: find student by course id");
		dprintf("\n 6: find the total number of student");
		dprintf("\n 7: delete student by id");
		dprintf("\n 8: update student by id");
		dprintf("\n 9: show all information");
		dprintf("\n 10: exit");
		dprintf("\n enter your choice :");
		gets(temp);
		dprintf("\n===============\n");
				switch(atoi(temp))
				{
				case 1:
					add_student_file();
					break;
				case 2:
					add_student_manually();
					break;
				case 3:
					find_id();
					break;
				case 4:
					find_fn();
					break;
				case 5:
					find_c();
					break;
				case 6:
					tot_s();
					break;
				case 7:
					del_s();
					break;
				case 8:
					up_s();
					break;
				case 9:
					show_s();
					break;
				case 10:
					i=0;
					break;
				default:
					dprintf("\n wrong option");
					break;
				}
	}
}
