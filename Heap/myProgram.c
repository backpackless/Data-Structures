#include "HeapInterface.h"
#include "StudentInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void * copyValue (void * X, void * Y) {
	if(X == NULL)
		X = malloc(sizeof(Student));
	InitializeStudent(NameOfStudent(*(Student *)Y), GradeOfStudent(*(Student *)Y), X);
	return X;
}

static void destroyValue (void * X) {
	X = NULL;
}
static int compareValues (void * X, void * Y) {
	Student *x;
	Student *y;

	x = X;
	y = Y;

	if(GradeOfStudent(*x) < GradeOfStudent(*y))
		return -1;
	else if(GradeOfStudent(*x) > GradeOfStudent(*y))
		return 1;
	else if(GradeOfStudent(*x) == GradeOfStudent(*y))
		return 0;
	else
		return -10;
}

int main(int argc, char *argv[])
{
	int x, mark, i;
	char *p;
	char s[20];
	FILE *test;
	Heap H;
	Student S;

	if(argc != 2) {
		printf("INVALID OPERATION\n");
		exit(0);
	}

	x = strtol(argv[1], &p, 10);
	test=fopen("test.txt","r");
	Initialize(&H, 20, *copyValue, *destroyValue, *compareValues);

	while(fscanf(test,"%s %d",s,&mark)==2) {
		InitializeStudent(s, mark, &S);
		Insert(&H, &S);
	}

	for(i = 0; i < x; i++) {
		Top(&H, &S);
		Remove(&H);
		printf("%s %d\n", NameOfStudent(S), GradeOfStudent(S));
	}

	fclose(test);
	Destroy(&H);
	return EXIT_SUCCESS;
}

