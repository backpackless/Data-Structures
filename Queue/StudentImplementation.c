/*********************************************************************
 * FILE NAME: StudentImplementation.c
 * PURPOSE: A first implementation of the Student ADT.
 * AUTHOR: Ben Walker
 * DATE: 07/11/2015
 *********************************************************************/


#include "StudentInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define DEBUG


void InitializeStudent (char *name, int grade, Student *S) {
	strncpy(S->name,name,MAXNAMESIZE-1);
	S->name[MAXNAMESIZE-1]='\0';
	S->grade=grade;
#ifdef DEBUG
	if(strcmp(name,NameOfStudent(*S))!=0 ||
	   GradeOfStudent(*S)!=grade) {
		printf("Violated postcondition for InitializeStudent!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


char *NameOfStudent (Student S) {
	static char name[MAXNAMESIZE];
	strcpy(name,S.name);
	return name;
}


int GradeOfStudent (Student S) {
	return S.grade;
}


void FreeStudent (Student *S) {
}
