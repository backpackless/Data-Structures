#include "ListInterface.h"

int main (void) {
	char fName[50]; /*name of the file*/
	FILE *fp; /*pointer to the file name*/
	char *token = NULL;
	char *name = malloc(sizeof(char) * 20);
	char buffer[100];
	int i;
	int position;
	int grade;
	List *L = (List *)malloc(sizeof(List)); /*struct to hold the list*/
	Student *S = (Student *)malloc(sizeof(Student)); /*the struct to hold student data*/

	#ifdef DEBUG
		printf("DEBUG MODE\n");
	#endif
	printf("Enter the name of the file to open: ");
	fgets(fName, 20, stdin);
	strtok(fName, "\n"); /*removes the newline character from the file name*/
	fp = fopen(fName, "r"); /*open the file for reading*/
	Initialize(L);

	/*print info regarding the list (whether it is empty or full, etc.)*/
	if (Empty(L) == 1) {
		printf("List is empty; ");
	} else {
		printf("List is not empty; ");
	}
	if (Full(L) == 1) {
		printf("list is full; ");
	} else {
		printf("list is not full; ");
	}
	printf("list is of size %d:\n", Size(L));

	while (fgets(buffer, 100, fp) != NULL) {

		token = strtok(buffer, " ");
		
		/*checks if the first word is 'Insert', if it is grab other tokens, assign them to
		the relevant data, then pass this info to the Insert() function*/
		if (strcmp(token, "Insert") == 0) {
			position = atoi(strtok(NULL, " ")); /*converts string token to an integer*/
			strcpy(name, strtok(NULL, " "));
			grade = atoi(strtok(NULL, " "));
			InitializeStudent(name, grade, S);
			Insert(*S, position, L);

		/*checks if the first word is 'Remove', if it is grab other tokens, assign them to
		the relevant data, then pass this info to the Remove() function*/
		} else if (strcmp(token, "Remove") == 0) {
			position = atoi(strtok(NULL, " "));
			Remove(position, L);
		}

		if (Empty(L) == 1) {
			printf("List is empty; ");
		} else {
			printf("List is not empty; ");
		}
		if (Full(L) == 1) {
			printf("list is full; ");
		} else {
			printf("list is not full; ");
		}
		printf("list is of size %d:\n", Size(L));
		
		/*prints the list*/
		for (i = 0; i < L->size; i++) {
			Peek(i, L, S);
			printf("%s %d%%\n", NameOfStudent(*S), GradeOfStudent(*S));
		}
	}

	/*calls Destroy(), closes the file, and exits the program*/
	Destroy(L);
	FreeStudent(S);
	free(name);
	fclose(fp);
    return 0;
}
