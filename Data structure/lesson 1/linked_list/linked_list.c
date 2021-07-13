/*
 * linked_list.c
 *
 *  Created on: Jul 8, 2021
 *      Author: Mohamed_ELkomy
 */
#include "linked_list.h"

void add_student()
{
	struct ssudent* PNewstudent;
	struct ssudent* Plaststudent;
	if(head ==NULL)
	{
		PNewstudent=(struct ssudent*) malloc(sizeof(struct ssudent));
		head =PNewstudent;
	}
	else
	{
		Plaststudent=head;
		while(Plaststudent->pNextstudent)
			Plaststudent=Plaststudent->pNextstudent;

		PNewstudent=(struct ssudent*) malloc(sizeof(struct ssudent));
		Plaststudent->pNextstudent=PNewstudent;
	}
	fill_the_record(PNewstudent);
	PNewstudent->pNextstudent= NULL;
}
void fill_the_record (struct ssudent* new_student)
{
	char temp[40];
	dprintf("\nENTER the id");
	gets(temp);
	new_student->student.id=atoi(temp);
	dprintf("\nENTER the name");
	gets(new_student->student.name);
	dprintf("\nENTER the hight");
	gets(temp);
	new_student->student.hight=atof(temp);
}
int delet_student()
{
	char temp[40];
	int slected;
	struct ssudent* Pslectedstudent=head;
	struct ssudent* Plaststudent =NULL;

	dprintf("\nENTER the id");
	gets(temp);
	slected=atoi(temp);
	if(head)
	{
		while(Pslectedstudent)
		{
			if(Pslectedstudent->student.id==slected)
			{
				if(Plaststudent)
				{
					Plaststudent->pNextstudent=Pslectedstudent->pNextstudent;
				}
				else
				{
					head=Pslectedstudent->pNextstudent;
				}
				free (Pslectedstudent);
				return 1;
			}
			Plaststudent=Pslectedstudent;
			Pslectedstudent=Pslectedstudent->pNextstudent;
		}

		dprintf("\n cannot find this id");
		return 0;
	}
	else
	{
		dprintf("\n the list is empty");
		return 0;
	}

}
void view_student()
{
	struct ssudent* Pslectedstudent=head;
	int count=1;
	if(head==NULL)
		dprintf("/n the list is empty");
	while(Pslectedstudent)
	{
		dprintf("\n the student number= %d",count);
		dprintf("\n the student id= %d",Pslectedstudent->student.id);
		dprintf("\n the student name= %s",Pslectedstudent->student.name);
		dprintf("\n the student id= %.2f",Pslectedstudent->student.hight);
		Pslectedstudent=Pslectedstudent->pNextstudent;
		count++;
	}
}
void delet_all()
{
	struct ssudent* Pslectedstudent=head;
	struct ssudent* Ptemp=Pslectedstudent;
	if(head==NULL)
		dprintf("/n the list is empty");
	while(Pslectedstudent)
	{
		Ptemp=Pslectedstudent;
		Pslectedstudent= Pslectedstudent->pNextstudent;
		free(Ptemp);
	}
	head=NULL;
}

void value_of_item()
{
	char temp[40];
	int n,count=0;
	struct ssudent* Pslectedstudent=head;

	dprintf("\nENTER the number of item");
	gets(temp);
	n=atoi(temp);
	for(count=0;count<n;count++)
	{
		Pslectedstudent=Pslectedstudent->pNextstudent;
	}
	dprintf("\n the id of %d is : %d",n,Pslectedstudent->student.id);
	dprintf("\n the id of %d is : %s",n,Pslectedstudent->student.name);
	dprintf("\n the id of %d is : %.2f",n,Pslectedstudent->student.hight);
}

int get_count(struct ssudent* Pslectedstudent)
{
	if( Pslectedstudent)
	{
		Pslectedstudent=Pslectedstudent->pNextstudent;
		return 1+ get_count(Pslectedstudent);
	}
	return 0;
}

void node_valuo_from_end()
{
	char temp[40];
	int n,count=0;
	struct ssudent* Pslectedstudent=head;
	struct ssudent* Plast=Pslectedstudent;

	dprintf("\nENTER the number of item from end");
	gets(temp);
	n=atoi(temp);
	for(count=0;count<n;count++)
	{
		Plast=Plast->pNextstudent;
	}
	while(Plast)
	{
		Plast=Plast->pNextstudent;
		Pslectedstudent=Pslectedstudent->pNextstudent;
	}
	dprintf("\n the id of %d from the end is : %d",n,Pslectedstudent->student.id);
	dprintf("\n the id of %d from the end is : %s",n,Pslectedstudent->student.name);
	dprintf("\n the id of %d from the end is : %.2f",n,Pslectedstudent->student.hight);

}

void get_middle()
{
	int n,i;
	struct ssudent* Pslectedstudent=head;
	n=get_count(head)/2;
	for(i=0;i<n;i++)
	{
		Pslectedstudent=Pslectedstudent->pNextstudent;
	}
	dprintf("\n the middle item id is : %d",Pslectedstudent->student.id);
	dprintf("\n the middle item name is : %s",Pslectedstudent->student.name);
	dprintf("\n the middle item hight is : %.2f",Pslectedstudent->student.hight);

}

void detect_loop()
{
	struct ssudent* Pfast=head;
	struct ssudent* Pslow=head;
	while(Pfast && Pslow && (Pfast->pNextstudent))
	{
		Pslow=Pslow->pNextstudent;
		Pfast=Pfast->pNextstudent->pNextstudent;
		if(Pfast==Pslow)
		{
			dprintf("\n find loop");
		}
	}
	dprintf("\n do not find loop");
}

void reverse()
{
	struct ssudent* Pprev=NULL;
	struct ssudent* Pcurrent=head;
	struct ssudent* Pnext=Pcurrent->pNextstudent;
	while(Pcurrent)
	{
		Pnext=Pcurrent->pNextstudent;
		Pcurrent->pNextstudent=Pprev;
		Pprev=Pcurrent;
		Pcurrent=Pnext;
	}
	head=Pprev;
}
