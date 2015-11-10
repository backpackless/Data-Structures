#include "ListInterface.h"

void Initialize (List *L) {
	/*set list values equal to 0/NULL*/
	L->size = 0;
	L->first = NULL;
	#ifdef DEBUG
		if (Empty(L) != 1 || Size(L) != 0) {
			printf("ERROR In function: Initialize()\nPostconditions: Size(%d) || Empty(%d)\n", Size(L), Empty(L));
			exit(1);
		}
	#endif
}

void Insert (Item X, int position, List *L) {
	int dump;
	int i;
	ListNode * newNode, * l1, * l2;
	newNode = (ListNode *)malloc(sizeof(ListNode));
	#ifdef DEBUG
		if (position < 0 || position > Size(L) + 1 || Full(L) == 1) {
			printf("ERROR In function: Insert()\nPreconditions: Position(%d) || Full(%d)\n", position, Full(L));
			exit(1);
		}
	#endif
	if (Full(L) == 1) {
		printf("ERROR: list is full\n");
		exit(0);
	} else if (position < 0 || position > Size(L) + 1) {
		printf("ERROR: position is outside of the list\n");
		exit(0);
	} else {
		newNode->item = X;
		if (position == 0) {
			if (L->first == NULL) {
				L->first = newNode;
			} else {
				newNode->next = L->first;
				L->first = newNode;
			}
		} else {
			l1 = L->first;
			for (i = 0; i < position - 1; i++) {
				l1 = l1->next;
			}
			l2 = l1->next;
			l1->next = newNode;
			newNode->next = l2;
		}
		dump = Size(L);
	}
	L->size++;
	dump++;
	#ifdef DEBUG
		Peek(position, L, &X);
		if (Empty(L) == 1 || L->size != dump) {
			printf("ERROR In function: Insert()\nPostconditions: Empty(%d) || Size(%d) || Peek(%s %d%%)\n", Empty(L), Size(L), X.name, X.grade);
			exit(1);
		}
	#endif
}

void Remove (int position, List *L) {
	int dump;	
	#ifdef DEBUG
		if (position > Size(L) || position < 0 || Empty(L) == 1) {
			printf("ERROR In function: Remove()\nPreconditions: Position(%d) || Size(%d) || Empty(%d)\n", position, Size(L), Empty(L));
			exit(1);
		}
	#endif
	if (Empty(L) == 1) {
		printf("ERROR: list is empty\n");
		exit(0);
	} else if (position < 0 || position > Size(L)){
		printf("ERROR: position is outside of the list\n");
		exit(0);
	} else {
		dump = L->size;
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
	ListNode * temp;
	int i;
	#ifdef DEBUG
		if (position < 0 || position > Size(L) || Empty(L) == 1) {
			printf("ERROR In function: Peek()\nPreconditions: Position(%d) || Size(%d) || Empty(%d)\n", position, Size(L), Empty(L));
			exit(1);
		}
	#endif
	if (Empty(L) == 1) {
		printf("ERROR: list is empty\n");
		exit(0);
	} else if (position < 0) {
		printf("ERROR: position is outside of the list\n");
		exit(0);
	} else {
		temp = L->first;
		/*transfer the name and grade of the student into the struct*/
		for (i = 0; i < position; i++) {
			temp = temp->next;
		}
		X = &temp->item;
	}
}

void Destroy (List *L) {
	free(L->first->item.name);
	free(L->first);
	free(L);
}
