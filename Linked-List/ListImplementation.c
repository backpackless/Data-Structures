/*********************************************************************
 * FILE NAME: ListImplementation.c
 * PURPOSE: One-way linked implementation of the Student List ADT.
 * AUTHOR: Ben Walker
 * DATE: 04/11/2015
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
#include <stdio.h>

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
}


void Insert (Item X, int position, List *L) {
	ListNode *p, *q;
	
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
}


void Remove (int position, List *L) {
	ListNode *p, *q;
	
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
	ListNode *p;
	p=moveTo(position,L);
	copyItem(X,p->item);
}

void Reverse (List *L) {
	ListNode *n = (ListNode *)malloc(sizeof(ListNode));

	/*if the list is terminated, call return and fall back through stack frames*/
	if(L->first == NULL) {
		return;
	}

	/*copy the item from the list into n, gets stored in stack frame*/
	copyItem(&n->item, L->first->item);
	/*remove the item from the list*/
	Remove(0, L);
	/*recursive call to Reverse()*/
	Reverse(L);
	/*when program falls back through stack, add the current n item from the stack onto the end of the list*/
	Insert(n->item, Size(L), L);
	free(n);
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

