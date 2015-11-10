/*********************************************************************
 * FILE NAME: myProgram.c
 * PURPOSE: Test program for Stack implementations.
 * AUTHOR: Ben Walker (CIS2520, Assignment 2)
 * DATE: 15/10/2015
 * NOTES: This program uses test data recorded in a text file
 *        (see test.txt). 
 *********************************************************************/

#include "StackInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>			   


int main(void) {
	/*Declarations*/
	FILE *test;
	Item X;
	int check = 0;
	Item num1;
	Item num2;
	char s;
	int temp;
	int carry = 0;
	int result;
	Stack S1, S2, S3;
	
	/*Init stacks*/
	Initialize(&S1);
	Initialize(&S2);
	Initialize(&S3);

	/*Open test files*/
	test=fopen("test.txt","r");
	while(fscanf(test, "%c", &s) > 0) {
		/*If a newline character is read, start pushing to the second stack*/
		if(s == '\n') {
			check = 1;
			printf("\n");
			/*If check equals 0, push to first stack*/
		} else if(check == 0) {
			X = atoi(&s);
			Push(X, &S1);
			/*If check equals 1, push to second stack*/
		} else if(check == 1) {
			X = atoi(&s);
			Push(X, &S2);
		}
	}

	/*While one of the stacks isn't empty*/
	while(Empty(&S1) == 0 || Empty(&S2) == 0) {
		/*Set the value of number 1*/
		if(Empty(&S1) == 1) {
			num1 = 0;
		} else {
			Top(&S1, &X);
			num1 =X;
			Pop(&S1);
		}

		/*Set the value of number 2*/
		if(Empty(&S2) == 1) {
			num2 = 0;
		} else {
			Top(&S2, &X);
			num2 = X;
			Pop(&S2);
		}
		
		/*Perform addition, find the result (%10) and calculate the carry*/
		temp = num1 + num2 + carry;
		result = (temp % 10);
		Push(result, &S3); /*Push result to stack*/
		if(temp >= 10)
			carry = 1;
		else
			carry = 0;
	}

	/*Print the sum, by popping one element of the stack at a time*/
	printf("The sum is: ");
	while(Empty(&S3) == 0) {
		Top(&S3, &X);
		printf("%d", X);
		Pop(&S3);
	}
	printf("\n");

	/*Close file, free all memory*/
	fclose(test);
	Destroy(&S1);
	Destroy(&S2);
	Destroy(&S3);
	return EXIT_SUCCESS;
}

