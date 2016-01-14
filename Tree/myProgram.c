#include "TreeInterface.h"
#include "StudentInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	FILE *test;
	char s[20];
	int mark, i;
	Student S;
	Tree T;

	Initialize(&T, *copyValue, *destroyValue, *compareValues);
	test=fopen("test.txt","r");

	printf("Initialize()\nSize=%d, Height=%d, Balanced=", Size(&T), Height(&T));
	if(Balanced(&T) == 1)
		printf("YES\n\n");
	else
		printf("NO\n\n");

	
	while(fscanf(test,"%s %d",s,&mark)==2) {
		printf("Insert(%s,%d)\n", s, mark);
		InitializeStudent(s, mark, &S);
		Insert(&T, &S);
		printf("Size=%d, Height=%d, Balanced=", Size(&T), Height(&T));
		if(Balanced(&T) == 1)
			printf("YES\n\n");
		else
			printf("NO\n\n");
	}

	fclose(test);
	/*print the tree inorder by first finding minimum value, then its successors*/
	Minimum(&T, &S);
	printf("%-8s %d\n", NameOfStudent(S), GradeOfStudent(S));
	for(i = 0; i < Size(&T) - 1; i++) {
		Successor(&T, &S);
		printf("%-8s %d\n", NameOfStudent(S), GradeOfStudent(S));
	}
	
	Destroy(&T);
	return EXIT_SUCCESS;
}

void * copyValue (void * X, void * Y) {
	Student *x;
	Student *y;
	x = X;
	y = Y;

	if(X == NULL)
		X = malloc(sizeof(Student));
	InitializeStudent(NameOfStudent(*y), GradeOfStudent(*y), X);
	return X;
}

void destroyValue (void * I) {
	free(I);
}

int compareValues (void * X, void * Y) {
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
