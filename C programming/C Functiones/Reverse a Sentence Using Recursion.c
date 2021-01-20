/*
 * Reverse a Sentence Using Recursion.c
 *
 *  Created on: Jan 19, 2021
 *      Author: Mohamed_ELkomy
 */
#include<stdio.h>
void reverse( char c[]);
void main()
{
	char c[100],l;
	printf("Enter a sentence:");
	fflush(stdout);
	gets(c);
	reverse(c);
}
void reverse( char c[])
{
	if(c[1]!=0)
	{
		reverse(&c[1]);
	}
	printf("%c",c[0]);
}
/*
#include <stdio.h>
void Reverse();
int main()
{

	printf ( "Enter a sentence: ");
	Reverse();
	return 0;
}
void Reverse()
{

	char c;
	scanf( "%c " ,&c);
	if( c != '\n')
	{
		Reverse();
		printf( "%c",c);
	}
}
*/
