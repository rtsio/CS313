/*
File: project1.c
Name: Rostislav Tsiomenko
Date: 02/14/2012
Sect: 01
Mail: tsiomr1@umbc.edu

Project 1 - Palindromes. Prompts user for a file with candidate
lychrels, then prompts for a number to determine if it is a pal
indrome (or how many iterations are needed to make it one).

See http://www.csee.umbc.edu/courses/undergraduate/313/spring12/Projects/p1/

Needs to be compiled with -std=c99, because C99 makes C slightly
less annoying (and this file won't work otherwise).

*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main() {

   // Declare variables
   unsigned long long  int number = 1, reverse = 0, temp;
   int arraySize;
   int iterations;
   bool isLychrel;
   bool isPalindrome;
   FILE *candidates;
   char fileName[100];
   // Prompt for file
   printf("Enter name of file containing candidate lychrels: ");
   scanf("%s", fileName);
   candidates = fopen(fileName, "r");
   if (candidates == NULL) {
      printf("Error opening the file.\n");
      exit (-1);
   }
   // Read numbers into array and close file
   fscanf(candidates, "%d", &arraySize);
   int lychrels[arraySize];
   for (int x = arraySize; x > 0; x--){
      fscanf(candidates, "%d", &lychrels[x]);
   }
   fclose(candidates);

   while (number != 0) {
      // Reset variables for each new number
      isLychrel = false;
      isPalindrome = false;
      iterations = 0;
      printf("Enter a number to check: ");
      scanf("%llu", &number);
      // Exit if 0
      if (number == 0) {
	 printf("YOU GET NOTHING! GOOD DAY SIR!\n");
	 exit(-1);
      }
      // Check array for candidates
      for (int i = arraySize; i > 0; i--){
	 if (lychrels[i] == number) {
	    printf("Your number is a candidate lychrel.\n");
	    isLychrel = true;
	 }
      }
      if (!isLychrel) {
	 while (!isPalindrome) {
	    // Use "temp" to hold number value and perform calculations
	    temp = number;
	    reverse = 0;
	    // Calculate reverse using modulus operator
	    while (temp != 0){
	       reverse = reverse * 10;
	       reverse = reverse + temp % 10;
	       temp = temp / 10;
	    }
	    if (number == reverse) {
	       isPalindrome = true;
	       if (iterations == 0) {
		  printf("%llu is a palindrome!\n", number);
	       } else {
		  printf("A palindrome was obtained in %d iteration(s).\n", iterations);
	       }
	    } else {
	       // If not a palindrome (yet), we need to print out the math
	       temp = number + reverse;
	       printf("%10llu + %10llu = %10llu\n", number, reverse, temp);
	       number = number + reverse;
	       iterations++;
	    }
	 }
      }
   }  
   return 0;
}

