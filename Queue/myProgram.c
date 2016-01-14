/*********************************************************************
 * FILE NAME: myProgram.c
 * PURPOSE: Test program for Student Queue implementations.
 * AUTHOR: Ben Walker
 * DATE: 07/11/2015
 * NOTES: This program uses test data recorded in a text file
 *        (see test.txt). 
 *********************************************************************/


#include "QueueInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static void showQueueSize (Queue *Q) {
	if(Empty(Q)) printf("Queue is empty; ");
	else printf("Queue is not empty; ");
	if(Full(Q)) printf("Queue is full; ");
	else printf("Queue is not full; ");
	printf("Queue is of size %d:\n",Size(Q));
}
	
	
static void showQueueContent (Queue *Q) {
	int i;
	Student S;
	for(i=0;i<Size(Q);i++) {
		Head(Q, &S);
		printf("\t%s %d%%\n",NameOfStudent(S),GradeOfStudent(S));
		FreeStudent(&S);
	}
	for(i = 0;i<Size(Q);i++) {
		Tail(Q, &S);
		FreeStudent(&S);
	}
}

			   

int main(void) {
	FILE *test;
	char s[20];
	int grade;
	
	Student S;
	Queue Q; 
	
	Initialize(&Q);
	showQueueSize(&Q);
	showQueueContent(&Q);
	
	test=fopen("test.txt","r");
	while(fscanf(test,"%s",s)==1) {
		if(strcmp(s,"Enqueue")==0) {
			fscanf(test,"%s %d",s,&grade);
			InitializeStudent(s,grade,&S);
			Enqueue(S, &Q);
			FreeStudent(&S);
		}
		if(strcmp(s,"Dequeue")==0)
			Dequeue(&Q);
		showQueueSize(&Q);
		showQueueContent(&Q);
	}
	
	fclose(test);
	Destroy(&Q);
	return EXIT_SUCCESS;
}

