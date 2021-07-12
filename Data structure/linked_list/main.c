/*
 * main.c
 *
 *  Created on: Jul 8, 2021
 *      Author: Mohamed_ELkomy
 */

#include"linked_list.h"

void main()
{
	head=NULL;
	int n;
	char temp[40];
	while(1)
	{
		dprintf("\n===============");
		dprintf("\n\t choose one of the following options:");
		dprintf("\n 1: Add student");
		dprintf("\n 2: delete student");
		dprintf("\n 3: view students");
		dprintf("\n 4: delete all");
		dprintf("\n 5: view the value of item");
		dprintf("\n 6: the length of list");
		dprintf("\n 7: view the value of item from the end");
		dprintf("\n 8: view the middle item");
		dprintf("\n 9: detect_loop");
		printf("\n 10: reverse");
		dprintf("\n Enter option number:");
		gets(temp);
		dprintf("\n===============");
		switch(atoi(temp))
		{
		case 1:
			add_student();
			break;
		case 2:
			delet_student();
			break;
		case 3:
			view_student();
			break;
		case 4:
			delet_all();
			break;
		case 5:
			value_of_item();
			break;
		case 6:
			n=get_count(head);
			dprintf("\n the length is %d",n);
			break;
		case 7:
		    node_valuo_from_end();
			break;
		case 8:
			get_middle();
			break;
		case 9:
			detect_loop();
			break;
		case 10:
			reverse();
			break;
		default:
			dprintf("\n wrong option");
			break;
		}
	}
}
