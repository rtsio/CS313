/*
  File: project4.c
  Name: Rostislav Tsiomenko
  Date: 04/06/2012
  Sect: 01
  Mail: tsiomr1@umbc.edu

  Project 4 - Polynomials. Reads a file specified through
  CL to add, subtract, and multiply polynomials, using pointers.

  See http://www.csee.umbc.edu/courses/undergraduate/313/spring12/Projects/p4/index.shtml

  Other files required:
  polylib.c - polynomial functions.
  polylib.h - header file.

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "polylib.h"
#define MAX_POLYNOMIALS 8
#define MAX_TERMS 20
#define MAX_COMMAND_LENGTH 100

int main( int argc, char *argv[]) {
 
   // Create pointer to array of pointers
   POLYNOMIAL **poly;

   // Allocate array of Polynomial pointers
   poly = calloc(MAX_POLYNOMIALS, sizeof(POLYNOMIAL*));

   for (int i = 0; i < MAX_POLYNOMIALS; i++) {
      // Allocate polynomial structs (and terms)
      poly[i] = makePoly();   
   }

   // open file w/ error checking, etc.
   FILE *cmdFile; 
   if (argc != 2) {
      printf("Usage: %s filename\n", argv[0]);
      exit(-1);
   } else {
      cmdFile = fopen(argv[1], "r");
   }
   if (cmdFile == NULL) {
      printf("Error opening the file.\n");
      exit (-1);
   }
   
   // read through each line in the file 
   char line[MAX_COMMAND_LENGTH];
   while ( fgets(line, MAX_COMMAND_LENGTH, cmdFile) != NULL) {
      
      // Check which command is being used
      if (line[0] == 'A' && line[3] == 'T') {

	 // strtok() and atoi() are usually very bad idea, but input is guaranteed to be well formed
	 char *command =  strtok(line," ");
	 char *index = strtok(NULL," ");
	 char *coeff = strtok(NULL," ");
	 char *exp = strtok(NULL," \n");
	 // convert last symbol on line to int to strip any whitespace from input file
	 int exponent = atoi(exp);
	 printf("CMD: %s, Polynominal #: %s, Coefficient: %s, Exponent: %d\n", command, index, coeff, exponent);
	 int integerIndex = atoi(index);
	 // Adding term and printing the new polynomial 
	 addTerm(poly[integerIndex], atoi(coeff), atoi(exp) );
	 printPolynomial(integerIndex, poly[integerIndex]);

      } else if (line[0] == 'M') {

	 // Scalar multiplication
	 char *command =  strtok(line," ");
	 char *index = strtok(NULL," ");
	 char *value = strtok(NULL," ");
	 int scalar = atoi(value);
	 printf("CMD: %s, Polynominal #: %s, Scalar value: %d\n", command, index, scalar);
	 int integerIndex = atoi(index);
	 multiply(scalar, poly[integerIndex]);
	 printPolynomial(integerIndex, poly[integerIndex]);

      } else if (line[0] == 'A') {
	 
	 // Summation
	 char *command =  strtok(line," ");
	 char *sumIndex = strtok(NULL," ");
	 char *firstIndex = strtok(NULL, " ");
	 char *secondIndex = strtok(NULL," ");
	 int second = atoi(secondIndex);
	 printf("CMD: %s, Sum goes into index #: %s, First operand: %s, Second operand: %d\n", command, sumIndex, firstIndex, second);
	 int sum = atoi(sumIndex);
	 int first = atoi(firstIndex);
	 // Create temporary pointer to the sum
	 POLYNOMIAL *temp = add(poly[first], poly[second]);
	 // Free the memory at the sum destination
	 destroyPoly(poly[sum]);
	 // Place sum pointer into destination
	 poly[sum] = temp;
	 printPolynomial(sum, poly[sum]);

      } else if (line[0] == 'S') {

	 // Subtraction
	 char *command =  strtok(line," ");
	 char *diffIndex = strtok(NULL," ");
	 char *firstIndex = strtok(NULL," ");
	 char *secondIndex = strtok(NULL," ");
	 int second = atoi(secondIndex);
	 printf("CMD: %s, Dif goes into index #: %s, First operand: %s, Second operand: %d\n", command, diffIndex, firstIndex, second);
	 int diff = atoi(diffIndex);
	 int first = atoi(firstIndex);
	 // Create temporary pointer to the difference
	 POLYNOMIAL *temp = subtract(poly[first], poly[second]);
	 // Free the memory at the difference destination
	 destroyPoly(poly[diff]);
	 // Place difference pointer into destination
	 poly[diff] = temp;
	 printPolynomial(diff, poly[diff]);
      }
   }

  // Free all memory to ensure there are no memory leaks
   for (int i = 0; i < 8; i++) {
      destroyPoly(poly[i]);
   }
   free(poly);
   
   fclose(cmdFile);
   return 0;
}
