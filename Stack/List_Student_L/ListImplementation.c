/*********************************************************************
 * FILE NAME: ListImplementation.c
 * PURPOSE: One-way linked implementation of the Student List ADT.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 21/09/2015
 * NOTES: . Some functions are static (they are auxiliary functions
 *          with local scope; they are not visible outside the file).
 *        . Only the first two functions will need to be modified
 *          if the type of the list items (here, Student) changes. 
 *        . Only the other functions will need to be modified if
 *          the implementation of the List ADT changes.
 *        . For preconditions and postconditions,
 *          see the sequential implementation (no changes).
 *********************************************************************/


#include "ListInterface.h"
#include <stdlib.h>
#include <assert.h>

static void copyItem (Item *Y, Item X) {
	InitializeStudent(NameOfStudent(X),GradeOfStudent(X),Y);
}


static void destroyItem (Item *X) {
	FreeStudent(X);
}


static ListNode *moveTo (int position, List *L) {
	int i;
	ListNode *p=L->first;
	for(i=0;i<position;i++) p=p->next;
	return p;
}


void Initialize (List *L) {
	L->size=0;
	L->first=NULL;
	assert(Empty(L) != 0 && Size(L) == 0);
}


void Insert (Item X, int position, List *L) {
	assert(position >= 0 && position <= Size(L) && Full(L) == 0);
	ListNode *p, *q;
	int track;

	track = Size(L);
	L->size++;
	q=(ListNode *)malloc(sizeof(ListNode));
	copyItem(&q->item,X);
			 
	if(position==0) {
		q->next=L->first;
		L->first=q;
	}
	else {
		p=moveTo(position-1,L);
		q->next=p->next;
		p->next=q;
	}
	assert(Empty(L) == 0 && Size(L) == (track++));
}


void Remove (int position, List *L) {
	assert(position >= 0 && position < Size(L) && Empty(L) == 0);
	ListNode *p, *q;
	int track;

	track = Size(L);
	if(position==0) {
		q=L->first;
		L->first=q->next;
	}
	else {
		p=moveTo(position-1,L);
		q=p->next;
		p->next=q->next;
	}
	
	destroyItem(&q->item);
	free(q);
	L->size--;
	assert(Full(L) == 0 && Size(L) == (track--));
}


int Full (List *L) {
	return 0;
}


int Empty (List *L) {
	return L->size==0;
}


int Size (List *L) {
	return L->size;
}


void Peek (int position, List *L, Item *X) {
	assert(position >= 0 && position < Size(L) && Empty(L) == 0);
	ListNode *p;
	p=moveTo(position,L);
	copyItem(X,p->item);
}


void Destroy (List *L) {
	int i;
	ListNode *p, *q;
	
	p=L->first;
	for(i=0;i<L->size;i++) {
		q=p;
		p=p->next;
		destroyItem(&q->item);
		free(q);
	}
}

