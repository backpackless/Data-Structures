/*********************************************************************
 * FILE NAME: StackType.h
 * PURPOSE: Concrete data structure definition of Stack
 * AUTHOR: Ben Walker (CIS2520, Assignment 2)
 * DATE: 15/10/2015
 *********************************************************************/


typedef int Item;

typedef struct ListNodeTag {
	Item item;
	struct ListNodeTag *next;
} StackNode;

typedef struct {
	int size;
	StackNode *first;
} Stack;
