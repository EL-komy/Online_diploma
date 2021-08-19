/*
 * system.c
 *
 *  Created on: Jul 26, 2021
 *      Author: Mohamed_ELkomy
 */

#include "system.h"
#include "stdlib.h"
#include "string.h"

char s=0;
void add_student_file()
{

	FILE * fp =fopen("data_base.txt","r");
	char i=0,c[5];
	if(fp==NULL)
	{
		dprintf("there is not file");
	}

	while( fscanf(fp, "%s", c) != EOF)
	{
		for(i=0;i<s;i++)
		{
			if(atoi(c)==std[i].id)
			{
				dprintf("id %d is already taken \n",std[i].id);
				while((fgetc(fp))!='\n');
				fscanf(fp, "%s", c);
			}
		}

		std[s].id=atoi(c);
		//dprintf(" %d \n",std[s].id);

		fscanf(fp,"%s",std[s].fname);
		//dprintf("%s  \n",std[s].fname);

		fscanf(fp,"%s",std[s].lname);
		//dprintf("%s  \n",std[s].lname);

		fscanf(fp,"%f",&std[s].gpa);
		//dprintf("  %.1f\n",std[s].gpa);
		i=0;
		while((fgetc(fp))!='\n')
		{
			fscanf(fp,"%d",&std[s].cid[i]);
			//dprintf(" %d\n",std[s].cid[i]);
			i++;
		}
		dprintf("id %d saved successfully \n",std[s].id);
		s++;
	}
	fclose (fp);
	dprintf("student details addes successfully \n");
	tot_s();
}

void add_student_manually()
{
	char temp[20],i,flag=0;
	dprintf("enter student id \n");
	gets(temp);
	for(i=0;i<s;i++)
	{
		if(atoi(temp)==std[i].id)
		{
			dprintf("id %d is already taken \n",std[i].id);
			flag=1;
		}
	}
	if(flag==0)
	{
		std[s].id=atoi(temp);
		dprintf("enter student first name \n");
		gets(std[s].fname);
		dprintf("enter student last name \n");
		gets(std[s].lname);
		dprintf("enter student GPA \n");
		gets(temp);
		std[s].gpa=atof(temp);

		for(i=0;i<5;i++)
		{
			dprintf("enter course %d id:  \n",i+1);
			gets(temp);
			std[s].cid[i]=atoi(temp);
		}
		dprintf("id %d saved successfully \n",std[s].id);
		s++;
		dprintf("student details addes successfully \n");
		tot_s();
	}
}

void find_id()
{
	char temp[20],i,c,flag=0;
	dprintf("enter id of the student \n");
	gets(temp);
	for(i=0;i<s;i++)
	{
		if(atoi(temp)==std[i].id)
		{
			flag=1;
			dprintf("the student details are: \n");
			dprintf("the first name is %s \n",std[i].fname);
			dprintf("the last  name is %s \n",std[i].lname);
			dprintf("the id is %d \n",std[i].id);
			dprintf("the GPA is %.1f \n",std[i].gpa);
			for(c=0;c<5;c++)
			{
				dprintf(" course id:%d  \n",std[i].cid[c]);
			}
		}
	}
	if(flag==0)
		dprintf("[ERROR] ID %d is not found\n",(atoi(temp)));
}

void find_fn()
{
	char temp[20],i,c,flag=0;
	dprintf("enter first name of the student \n");
	gets(temp);
	for(i=0;i<s;i++)
	{
		if(stricmp(temp,std[i].fname)==0)
		{
			flag=1;
			dprintf("the student details are: \n");
			dprintf("the first name is %s \n",std[i].fname);
			dprintf("the last  name is %s \n",std[i].lname);
			dprintf("the id is %d \n",std[i].id);
			dprintf("the GPA is %.1f \n",std[i].gpa);
			for(c=0;c<5;c++)
			{
				dprintf(" course id:%d  \n",std[i].cid[c]);
			}
		}
	}
	if(flag==0)
		dprintf("[ERROR] student %s is not found\n",temp);
}

void find_c()
{
	char temp[20],i,c=0,flag=0,j;
	dprintf("enter the course id \n");
	gets(temp);
	for(i=0;i<s;i++)
	{
		for(j=0;j<5;j++)
		{
			if((atoi(temp))==std[i].cid[j])
			{
				flag=1;
				c++;
			}
		}
		if(flag==1)
		{
			flag=1;
			dprintf("the student details are: \n");
			dprintf("the first name is %s \n",std[i].fname);
			dprintf("the last  name is %s \n",std[i].lname);
			dprintf("the id is %d \n",std[i].id);
			dprintf("the GPA is %.1f \n",std[i].gpa);
			flag=0;
		}
	}
	if(c==0)
	{
		dprintf("[ERROR] the course id is not found\n");
	}
	else
	{
		dprintf("[INFO] total number of student enrolled: %d \n",c);
	}
}

void tot_s()
{
	dprintf("the total number of students is %d \n",s);
	dprintf("you can add up to 50 \n");
	dprintf("you can add %d to\n",(50-s));
}

void del_s()
{
	char temp[20],i,flag=0,j;
	dprintf("enter the id which you want to delete \n");
	gets(temp);
	for(i=0;i<s;i++)
	{
		if(atoi(temp)==std[i].id)
		{
			flag=1;
			for(j=i;j<s;j++)
			{
				std[j]=std[j+1];
			}
			s--;
		}
	}
	if(flag==0)
	{
		dprintf("[ERROR] this ID is not found \n");
	}
	else
		dprintf("[INFO] this ID is removed successfully \n");
}

void up_s()
{
	char temp[20],c[10],i,flag=0,j;
	dprintf("enter the id to update the entry: \n");
	gets(temp);
		for(i=0;i<s;i++)
		{
			if(atoi(temp)==std[i].id)
			{
				flag=1;
				dprintf("enter the number to update: \n ");
				dprintf("1. frist name \n ");
				dprintf("2. last name \n ");
				dprintf("3. id \n ");
				dprintf("4. GPA\n ");
				dprintf("5. courses \n ");
				gets(c);
				switch(atoi(c))
				{
				case 1:
					dprintf("enter the new first name:");
					gets(std[i].fname);
					break;
				case 2:
					dprintf("enter the new last name:");
					gets(std[i].lname);
					break;
				case 3:
					check(i);
					break;
				case 4:
					dprintf("enter the new GPA:");
					gets(c);
					std[i].gpa=atof(c);
					break;
				case 5:
					dprintf("enter the new courses:");
					for(j=0;j<5;j++)
					{
						dprintf("enter course %d id:  \n",j+1);
						gets(c);
						std[s].cid[j]=atoi(c);
					}
					break;
				}
			}
		}
		if(flag==0)
		{
			dprintf("[ERROR] this ID is not found \n");
		}
		else
			dprintf("[INFO] updated successfully \n");
}

void show_s()
{
	char i,c;
	for(i=0;i<s;i++)
	{
		dprintf("the student details are: \n");
		dprintf("the first name is %s \n",std[i].fname);
		dprintf("the last  name is %s \n",std[i].lname);
		dprintf("the id is %d \n",std[i].id);
		dprintf("the GPA is %.1f \n",std[i].gpa);
		for(c=0;c<5;c++)
		{
			dprintf(" course id:%d  \n",std[i].cid[c]);
		}

	}
}

void check(int n)
{
	char temp[20],i,flag=0;
	dprintf("enter the new id:");
	gets(temp);
	for(i=0;i<s;i++)
	{
		if(atoi(temp)==std[i].id)
		{
			dprintf("[ERROR] this ID is already found \n");
			flag=1;
		}
	}
	if(flag==0)
	{
		std[n].id=atoi(temp);
	}
}

