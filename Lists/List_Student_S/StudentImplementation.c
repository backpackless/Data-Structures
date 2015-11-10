#include "StudentInterface.h"

void InitializeStudent (char *name, int grade, Student *S) {
	/*copy student values into the struct*/
	S->grade = grade;
	strncpy(S->name, name, MAXNAMESIZE);
	#ifdef DEBUG
		if (strcmp(S->name, NameOfStudent(*S)) != 0 || S->grade != GradeOfStudent(*S)) {
			printf("ERROR In function InitializeStudent()\nPostconditions: NameOfStudent(%s) || GradeOfStudent(%d)\n", NameOfStudent(*S), GradeOfStudent(*S));
			exit(1);
		}
	#endif
}

char *NameOfStudent (Student S) {
	/*copy the name from the struct into a new string and return it*/
	char *name;
	name = malloc(strlen(S.name) + 1);
	strcpy(name, S.name);
	return name;
}

int GradeOfStudent (Student S) {
	return S.grade;
}
void FreeStudent (Student *S) {
	free(S);
}
