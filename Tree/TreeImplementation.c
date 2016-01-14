/*********************************************************************
 * FILE NAME: TreeImplementation.c
 * PURPOSE: Implements Tree Interface
 * AUTHOR: Ben Walker (CIS2520, Assignment 4)
 * DATE: 26/11/2015
 *********************************************************************/

#include "TreeInterface.h"
#include <stdlib.h>
#include <stdio.h>


void Initialize (Tree *T,
						void * (*copyValue) (void *, void *),
						void (*destroyValue) (void *),
						int (*compareValues) (void *, void *)) {
	/*initialize tree; root set to null so it is accessible in Insert()*/
	T->root = NULL;
	T->size = 0;
	T->copyValue = copyValue;
	T->destroyValue = destroyValue;
	T->compareValues = compareValues;

}

void Insert (Tree *T, void *I) {
	/*p is used for traversing the tree, n holds the value of the node to insert*/
	TreeNode *p = T->root;
	TreeNode *n = malloc(sizeof(TreeNode));
	/*initializing the new node's data*/
	n->value = T->copyValue(NULL, I);
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;

	/*while the current node doesn't equal null, navigate tree*/
	while(p != NULL) {
		/*if value is equal or greater than node, move to the right*/
		if(T->compareValues(I, p->value) == 1 || T->compareValues(I, p->value) == 0) {
			/*if node to right is null, insert new node here*/
			if(p->right == NULL) {
				p->right = n;
				n->parent = p;
				T->size++;
				return;
			}
			p = p->right;
		} else {
			if(p->left == NULL) {
				p->left = n;
				n->parent = p;
				T->size++;
				return;
			}
			p = p->left;
		}
	}
	/*this code is run if the root node is null, and initializes the root of the tree*/
	T->root = n;
	T->size++;
}

int Minimum (Tree *T, void *I) {
	TreeNode *t = T->root;
	if(Size(T) == 0)
		return 0;
	/*navigate tree to leftmost leaf*/
	while(t->left != NULL)
		t = t->left;

	/*copy leftmost leaf into void *I*/
	T->copyValue(I, t->value);
	T->current = t;
	return 1;
}

int Successor (Tree *T, void *I) {
	TreeNode *t = T->current;
	TreeNode *x;
	/*if node has a right subtree, follow it to its smallest value*/
	if(t->right != NULL) {
		t = t->right;
		while(t->left != NULL)
			t = t->left;
		/*copy successor into, I, set current node to the successor, return 1*/
		T->copyValue(I, t->value);
		T->current = t;
		return 1;
	/*if there is no right subtree, go up the tree until a parent is larger than the original value*/
	} else {
		x = t;
		while(t->parent != NULL) {
			t = t->parent;
			/*if current node is greater than original node, copy current value into successor, return 1*/
			if(T->compareValues(x->value, t->value) == -1) {
				T->copyValue(I, t->value);
				T->current = t;
				return 1;
			}
		}
	}
	return 0;
}

int Size (Tree *T) {
	return T->size;
}

int Height (Tree *T) {
	/*call function to calculate height recursively*/
	int height = RecursiveHeight(T->root);
	return height;
}

int RecursiveHeight (TreeNode *p) {
	int a, b;
	if(p == NULL)
		return -1;
	/*move the node left and right, call recursiveHeight()*/
	a = RecursiveHeight(p->left);
	b = RecursiveHeight(p->right);
	/*return max height plus 1*/
	if(a > b)
		return a + 1;
	else if(b > a)
		return b + 1;
	else
		return a + 1;
}

int Balanced (Tree *T) {
	/*call function to calculate if balanced recursively*/
	int balance = RecursiveBalance(T->root);
	return balance;
}

int RecursiveBalance (TreeNode *p) {
	int a, b;
	if(p == NULL)
		return 1;
	/*move the node left and right, call recursiveBalance()*/
	a = RecursiveHeight(p->left);
	b = RecursiveHeight(p->right);
	/*return true if the values are within 1, false otherwise*/
	if(a <= b + 1 && a >= b - 1)
		return 1;
	return 0;
}

void Destroy (Tree *T) {
	/*make a call to a funciton to recursively destroy the tree*/
	RecursiveDestroy(T->root);
}

void RecursiveDestroy (TreeNode *p) {
	if(p == NULL)
		return;
	RecursiveDestroy(p->left);
	RecursiveDestroy(p->right);
	/*free the value of the node, then the node itself*/
	destroyValue(p->value);
	free(p);
}

