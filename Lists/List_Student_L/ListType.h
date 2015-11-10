#include "StudentInterface.h"
typedef Student Item;

#define MAXLISTSIZE 4
typedef struct ListNodeTag{
	Item item;
	struct ListNodeTag * next;
}ListNode;

typedef struct {
	int size;
	ListNode * first;
}List;
