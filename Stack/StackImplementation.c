/*********************************************************************
 * FILE NAME: StackImplementation.c
 * PURPOSE: One-way linked implementation of the Stack ADT.
 * AUTHOR: Ben Walker (CIS2520, Assignment 2)
 * DATE: 15/10/2015
 *********************************************************************/


#include "StackInterface.h"
#include <stdlib.h>
#include <assert.h>


static void copyItem (Item *Y, Item X) {
	*Y = X;
}


static void destroyItem (Item *X) {
	free(X);
}


static StackNode *moveTo (Stack *S) {
	StackNode *p=S->first;
	return p;
}


void Initialize (Stack *S) {
	S->size=0;
	S->first=NULL;
	#ifndef NDEBUG
		assert(Empty(S) != 0 && Size(S) == 0);
	#endif
}


void Push (Item X, Stack *S) {
	#ifndef NDEBUG
		assert(Full(S) == 0);
	#endif
	StackNode *p, *q;
	int track;

	track = Size(S);
	S->size++;
	q=(StackNode *)malloc(sizeof(StackNode));
	copyItem(&q->item,X);
			 
	q->next=S->first;
	S->first=q;
	#ifndef NDEBUG
		assert(Empty(S) == 0);
		assert(Size(S) > track);
	#endif
}


void Pop (Stack *S) {
	#ifndef NDEBUG
		assert(Empty(S) == 0);
	#endif
	StackNode *p, *q;
	int track;

	track = Size(S);
	q=S->first;
	S->first=q->next;
	
	destroyItem(&q->item);

	S->size--;
	#ifndef NDEBUG
		assert(Full(S) == 0);
		assert(Size(S) < track);
	#endif
}


int Full (Stack *S) {
	return 0;
}


int Empty (Stack *S) {
	return S->size==0;
}

int Size (Stack *S) {
	return S->size;
}


void Top (Stack *S, Item *X) {
	#ifndef NDEBUG
		assert(Empty(S) == 0);
	#endif
	StackNode *p;
	p=moveTo(S);
	copyItem(X,p->item);
}


void Destroy (Stack *S) {
	int i;
	
	for(i=0;i<S->size;i++) {
		Pop(S);
	}
}

