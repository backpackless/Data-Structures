#include "ListInterface.h"

void Initialize (List *L) {
	/*set list values equal to 0/NULL*/
	L->size = 0;
	#ifdef DEBUG
		if (Empty(L) != 1 || Size(L) != 0) {
			printf("ERROR In function: Initialize()\nPostconditions: Size(%d) || Empty(%d)\n", Size(L), Empty(L));
			exit(1);
		}
	#endif
}

void Insert (Item X, int position, List *L) {
	List copy;
	List temp;
	int dump;
	int i;
	#ifdef DEBUG
		if (position < 0 || position > 3 || Full(L) == 1) {
			printf("ERROR In function: Insert()\nPreconditions: Position(%d) || Full(%d)\n", position, Full(L));
			exit(1);
		}
	#endif
	if (Full(L) == 1) {
		printf("ERROR: list is full\n");
		exit(0);
	} else if (position > 3 || position < 0) {
		printf("ERROR: position is outside of the list\n");
		exit(0);
	} else {
		dump = L->size;
		copy.items[0] = L->items[position];
		L->items[position] = X;
		/*uses two temporary structs to insert the new element, and shuffle
		existing elements forward*/
		for (i = position; i < 3; i++) {
			temp.items[0] = copy.items[0];
			copy.items[0] = L->items[i+1];
			L->items[i+1] = temp.items[0];
		}
	}
	L->size++;
	dump++;
	#ifdef DEBUG
		Peek(position, L, &X);
		if (Empty(L) == 1 || L->size != dump || strcmp(X.name, L->items[position].name) != 0 || X.grade != L->items[position].grade) {
			printf("ERROR In function: Insert()\nPostconditions: Empty(%d) || Size(%d) || Peek(%s %d%%)\n", Empty(L), Size(L), X.name, X.grade);
			exit(1);
		}
	#endif
}

void Remove (int position, List *L) {
	List copy;
	int dump;	
	#ifdef DEBUG
		if (position >= Size(L) || position < 0 || Empty(L) == 1) {
			printf("ERROR In function: Remove()\nPreconditions: Position(%d) || Size(%d) || Empty(%d)\n", position, Size(L), Empty(L));
			exit(1);
		}
	#endif
	if (Empty(L) == 1) {
		printf("ERROR: list is empty\n");
		exit(0);
	} else if (position > 3 || position < 0){
		printf("ERROR: position is outside of the list\n");
		exit(0);
	} else {
		int i;
		dump = L->size;
		/*moves all items ahead of the value to be deleted back one element*/
		for (i = position; i < 3; i++) {
			copy.items[0] = L->items[i+1];
			strcpy(L->items[i+1].name, "");
			L->items[i+1].grade = -1;
			L->items[i] = copy.items[0];
		}
	}
	L->size--;
	dump--;
	#ifdef DEBUG
		if (Full(L) != 0 || L->size != dump) {	
			printf("ERROR In function: Remove()\nPostconditions: Full(%d) || Size(%d)\n", Full(L), Size(L));
			exit(1);
		}
	#endif
}

int Full (List *L) {
	if (L->size == MAXLISTSIZE)
		return 1;
	else
		return 0; 
}

int Empty (List *L) {
	if (L->size == 0)
		return 1;
	else
		return 0;
}

int Size (List *L) {
	return L->size;
}

void Peek (int position, List *L, Item *X) {
	#ifdef DEBUG
		if (position < 0 || position > Size(L) || Empty(L) == 1) {
			printf("ERROR In function: Peek()\nPreconditions: Position(%d) || Size(%d) || Empty(%d)\n", position, Size(L), Empty(L));
			exit(1);
		}
	#endif
	if (Empty(L) == 1) {
		printf("ERROR: list is empty\n");
		exit(0);
	} else if (position > 3 || position < 0) {
		printf("ERROR: position is outside of the list\n");
		exit(0);
	} else {
		/*transfer the name and grade of the student into the struct*/
		strcpy(X->name, L->items[position].name);
		X->grade = L->items[position].grade;
	}
}

void Destroy (List *L) {
	free(L);
}
