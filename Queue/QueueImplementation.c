/*********************************************************************
 * FILE NAME: QueueImplementation.c
 * PURPOSE: Sequential implementation of the Student Queue ADT.
 * AUTHOR: Ben Walker
 * DATE: 07/11/2015
 * NOTES: . Some functions are static (they are auxiliary functions
 *          with local scope; they are not visible outside the file).
 *        . Only these static functions will need to be modified
 *          if the type of the Queue items (here, Student) changes. 
 *        . Only the other functions will need to be modified if
 *          the implementation of the Queue ADT changes.
 *        . As we will see, there is a better way to check whether
 *          the preconditions and postconditions are met.
 *********************************************************************/


#include "QueueInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define DEBUG


static void copyItem (Item *Y, Item X) {
	InitializeStudent(NameOfStudent(X),GradeOfStudent(X),Y);
}


static void destroyItem (Item *X) {
	FreeStudent(X);
}


void Initialize (Queue *Q) {
	Q->size=0;
	Q->head = 0;
#ifdef DEBUG
	if(!Empty(Q) || Full(Q) || Size(Q)!=0) {
		printf("Violated postcondition for Initialize!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


void Enqueue (Item I, Queue *Q) {
  	int newSpot;
#ifdef DEBUG
	int oldSize=Size(Q);
	if(Full(Q)) {
		printf("Violated precondition for Enqueue!\n");
		exit(EXIT_FAILURE);
	}
#endif
	newSpot = Q->head + Size(Q);
	if(newSpot >= MAXQUEUESIZE)
		newSpot = newSpot - MAXQUEUESIZE;
	copyItem(&Q->items[newSpot],I);
	Q->size++;
#ifdef DEBUG
	if(Empty(Q) || Size(Q)!=oldSize+1) {
		printf("Violated postcondition for Enqueue!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


void Dequeue (Queue *Q) {
#ifdef DEBUG
	int oldSize=Size(Q);
	if(Empty(Q)) {
		printf("Violated precondition for Dequeue!\n");
		exit(EXIT_FAILURE);
	}
#endif
	destroyItem(&Q->items[Q->head]);
	Q->head++;
	if(Q->head >= MAXQUEUESIZE)
		Q->head = Q->head - MAXQUEUESIZE;
	Q->size--;
#ifdef DEBUG
	if(Full(Q) || Size(Q)!=oldSize-1) {
		printf("Violated postcondition for Dequeue!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


int Full (Queue *Q) {
	return Q->size==MAXQUEUESIZE;
}


int Empty (Queue *Q) {
	return Q->size==0;
}


int Size (Queue *Q) {
	return Q->size;
}


void Head (Queue *Q, Item *I) {
#ifdef DEBUG
	if(Empty(Q)) {
		printf("Violated precondition for Head!\n");
		exit(EXIT_FAILURE);
	}
#endif
	copyItem(I,Q->items[Q->head]);
	Q->head++;
	if(Q->head >= MAXQUEUESIZE)
		Q->head = Q->head - MAXQUEUESIZE;
}

void Tail (Queue *Q, Item *I) {
int newSpot;
#ifdef DEBUG
	if(Empty(Q)) {
		printf("Violated precondition for Tail!\n");
		exit(EXIT_FAILURE);
	}
#endif
	newSpot = Q->head + Size(Q) - 1;
	if(newSpot >= MAXQUEUESIZE)
		newSpot = newSpot - MAXQUEUESIZE;
	copyItem(I,Q->items[newSpot]);
	Q->head--;
	if(Q->head < 0)
		Q->head = Q->head + MAXQUEUESIZE;

}


void Destroy (Queue *Q) {
	int i;
	for(i=0;i<Q->size;i++)
		destroyItem(&Q->items[i]);
}

