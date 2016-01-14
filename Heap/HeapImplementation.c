#include "HeapInterface.h"
#include <string.h>
#include <stdlib.h>

int Initialize (Heap *H, int capacity, void * (*copyValue) (void *, void *), void (*destroyValue) (void *), int (*compareValues) (void *, void *)) {
	H->heap = malloc(sizeof(void*)*capacity);
	if(H == NULL)
		return 0;
	H->capacity = capacity;
	H->copyValue = copyValue;
	H->destroyValue = destroyValue;
	H->compareValues = compareValues;
	H->numberOfValues = 0;
	return 1;
}

int Insert (Heap *H, void *I) {
	void *temp;
	int child, parent;
	int num = H->numberOfValues;
	if(H->numberOfValues == H->capacity)
		return 0;
	H->heap[num + 1] = H->copyValue(NULL, I);
	H->numberOfValues = H->numberOfValues + 1;

	/*up-heapify*/
	child = num + 1;
	parent = num / 2;
	while(parent >= 1) {
		if(H->compareValues(H->heap[child], H->heap[parent]) == 1) {
			temp = H->copyValue(NULL, H->heap[parent]);
			H->heap[parent] = H->heap[child];
			H->heap[child] = temp;
		} else
			break;
		child = parent;
		parent = parent / 2;
	}

	return 1;
}

void Remove (Heap *H) {
	void *temp;
	int child, parent;
	H->destroyValue(H->heap[1]);
	H->heap[1] = H->heap[H->numberOfValues];
	H->destroyValue(H->heap[H->numberOfValues]);
	H->numberOfValues = H->numberOfValues - 1;

	/*down-heapify*/
	parent = 1;
	child = parent * 2;
	while((parent * 2) + 1 <= H->numberOfValues) {
		if(H->compareValues(H->heap[child], H->heap[parent]) == 1) {
			temp = H->copyValue(NULL, H->heap[child]);
			H->heap[child] = H->heap[parent];
			H->heap[parent] = temp;
		} else if(H->compareValues(H->heap[child + 1], H->heap[parent]) == 1) {
			temp = H->copyValue(NULL, H->heap[child + 1]);
			H->heap[child + 1] = H->heap[parent];
			H->heap[parent] = temp;
		} else
			break;
		parent++;
		child = parent * 2;
	}
}

void Top (Heap *H, void *I) {
	I = H->copyValue(I, H->heap[1]);
}

int Full (Heap *H) {
	if(H->numberOfValues == H->capacity)
		return 1;
	return 0;
}

int Empty (Heap *H) {
	if(H->numberOfValues == 0)
		return 1;
	return 0;
}

void Destroy (Heap *H) {
	free(H->heap);
}


