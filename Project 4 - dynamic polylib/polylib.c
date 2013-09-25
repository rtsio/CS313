/*
  File: polylib.c
  Name: Rostislav Tsiomenko
  Date: 04/06/2012
  Sect: 01
  Mail: tsiomr1@umbc.edu

  This is the polynomial functions library
  for Project 4.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "polylib.h"
#include <assert.h>
#define MAX_TERMS 20

/*
  makePoly returns a pointer to a new dynamically allocated
  polynomial struct, complete with a dynamically allocated
  array of term structs, all initialized to 0.
  Returns a pointer to an empty, initialized polynomial struct.
*/
POLYNOMIAL* makePoly() {
   
   // Allocate memory for new polynomial
   POLYNOMIAL* p = calloc (1, sizeof(POLYNOMIAL));
   assert(p != NULL);

   p->size = 0;

   // Allocate memory for array of TERM pointers
   p->terms = calloc (MAX_TERMS, sizeof(TERM*));
   assert(p->terms != NULL);

   // Allocate memory for TERM structs
   for (int i = 0; i < MAX_TERMS; i++) {

      p->terms[i] = calloc (1, sizeof(TERM));
      assert(p->terms[i] != NULL);

      p->terms[i]->coeff = 0;
      p->terms[i]->exp = 0;
   }
   return p;
}

/*
  destroyPoly goes through the polynomial struct
  pointed to by p and frees all memory associated
  with that struct.
*/
void destroyPoly (POLYNOMIAL* p) {
   
   // Free all TERM structs
   for (int i = 0; i < MAX_TERMS; i++) {
      free(p->terms[i]);
   }
   // Free TERM pointer array
   free(p->terms);
   // Free the polynomial pointer
   free(p);
}

/*
  printPolynomial prints out the polynomial
  according to the project rules.
  int index - array index of the polynomial being printed
  POLYNOMIAL *polynomial - pointer to polynomial struct to be printed
*/
void printPolynomial(int index, POLYNOMIAL *polynomial) {
  

   sortPolynomial(polynomial);
   printf("Polynomial #%d = ", index);

   //Deal with 0 value polynomials
   if (polynomial->terms[0]->coeff == 0 && polynomial->terms[0]->exp == 0) {
     
      printf("0\n\n");

   } else {

      for (int i = 0; i < polynomial->size; i++) {

	 int coeff;

	 // If we're at the first term, don't suppress the negative sign
	 if (i == 0) {
	    coeff = polynomial->terms[i]->coeff;
	 } else {
	    // Otherwise, suppress it and we'll deal with it later
	    coeff = abs(polynomial->terms[i]->coeff);
	 }

	 int exp = polynomial->terms[i]->exp;
	
	 if (coeff != 0) {

	    if (exp == 0) {
	       // constant
	       printf("%d", coeff);
	    } else if (coeff == 1 && exp == 1) {
	       // special 'x' case
	       printf("x");
	    } else if (coeff == 1) {
	       // suppress 1 in coefficient
	       printf("x^%d", exp);
	    } else if (exp == 1) {
	       // suppress 1 in exponent
	       printf("%dx", coeff);
	    } else {
	       printf("%dx^%d", coeff, exp);
	    }

	    // If we're not at the end of the polynomial and the next term is positive..
	    if ((polynomial->size - (i+1)) != 0 && (polynomial->terms[i+1]->coeff > 0)) {
	       //..print a plus
	       printf(" + ");
	    } else if ((polynomial->size - (i+1)) != 0){
	       // if we're not at the end but the next term is negative, print a minus
	       printf(" - ");
	    } else {
	       printf("\n\n");
	    }
	 }
      }
   }
}

/*
  addTerm adds a term to the given polynomial.
  POLYNOMIAL *polynomial - pointer to polynomial struct to be modified
  int coefficient - coefficient of new term
  int exponent - exponent of new term
*/
void addTerm(POLYNOMIAL *polynomial, int coefficient, int exponent) {

   bool foundLikeTerm = false;

   // Search for like terms and sum coefficients if found
   for (int i = 0; i < polynomial->size; i++) {
      if (polynomial->terms[i]->exp == exponent) {
	 polynomial->terms[i]->coeff += coefficient;
	 foundLikeTerm = true;
      }
   }
   
   // Otherwise, create a new term and increment size
   if (foundLikeTerm == false) {
      polynomial->terms[polynomial->size]->exp = exponent;
      polynomial->terms[polynomial->size]->coeff = coefficient;
      polynomial->size += 1;
   }
}

/*
  sortPolynomial sorts the terms of a polynomial in descending
  order (i.e. first term (index 0) has highest exponent) using insertion sort
  POLYNOMIAL *polynomial - pointer topolynomial struct to sort
*/
void sortPolynomial(POLYNOMIAL *polynomial) {

   // Simple insertion sort comparing exponents
   for (int i = 0; i < MAX_TERMS; i++) {

      TERM *temp = polynomial->terms[i];
      int j = i-1;

      while (j >= 0 && polynomial->terms[j]->exp < temp->exp) {
	 polynomial->terms[j+1] = polynomial->terms[j];
	 j = j-1;
      }

      polynomial->terms[j+1] = temp;
   }

   // Since constants have an exponent of 0 and are thus considered
   // the same as 0 value polynomials by insertion sort, we must
   // shift all true 0 value polynomials to the end
   for (int i = 0; i < MAX_TERMS; i++) {
      if (polynomial->terms[i]->coeff == 0 && polynomial->terms[i]->exp == 0) {
	 for (int j = i + 1; j < MAX_TERMS; j++) {
	    if (polynomial->terms[j]->coeff != 0 && polynomial->terms[j]->exp == 0) {
	       polynomial->terms[i]->coeff = polynomial->terms[j]->coeff;
	       polynomial->terms[i]->exp = polynomial->terms[j]->exp;
	       polynomial->terms[j]->coeff = 0;
	       polynomial->terms[j]->exp = 0;
	    }
	 }
      }
   }
}
/*
  add returns a pointer to the resulting polynomial struct from the summation of two polynomial structs.
  POLYNOMIAL *poly1 - pointer to first polynomial
  POLYNOMIAL *poly2 - pointer to polynomial to be added to the first 
  Returns a pointer to the sum POLYNOMIAL struct
*/
POLYNOMIAL* add(POLYNOMIAL *poly1, POLYNOMIAL *poly2) {

   // Allocate a new polynomial struct and first operand into it
   POLYNOMIAL *newPoly = makePoly();
   newPoly->size = poly1->size;
   for (int i = 0; i < MAX_TERMS; i++){
      newPoly->terms[i]->coeff = poly1->terms[i]->coeff;
      newPoly->terms[i]->exp = poly1->terms[i]->exp;
   }

   int sizeCounter = 0;

   for (int i = 0; i < poly2->size; i++) {

      int index = 0;
      bool foundLikeTerm = false;
      int coeff = poly2->terms[i]->coeff;
      int exp = poly2->terms[i]->exp;

      // Look for like terms in the other polynomial
      for (int j = 0; j < newPoly->size; j++) {
	 if (newPoly->terms[j]->exp == exp) {
	    foundLikeTerm = true;
	    // Note location of like term
	    index = j;
	 }
      }

      if (foundLikeTerm == false) {
	 // If we didn't find a like term, create a new one at the end
	 newPoly->terms[newPoly->size]->coeff = coeff;
	 newPoly->terms[newPoly->size]->exp = exp;
	 newPoly->size += 1;
      } else {
	 // If we did find a like term, sum coefficients
	 if (newPoly->terms[index]->coeff == -(coeff)) {

	    // Special case where coefficients cancel each other out
	    // and we get a 0 value polynomial
	    newPoly->terms[index]->exp = 0;
	    // Decreasing size during the loop would mess up indices,
	    // so we leave it for last
	    sizeCounter -= 1;

	 }
	 newPoly->terms[index]->coeff += coeff;
      }
   }

   // Adjust size 
   newPoly->size += sizeCounter;
   // Return the pointer to the sum struct, leaving both operands in original state
   return newPoly;
}

/*
  subtract returns the pointer to the resulting polynomial struct from the difference of two passed in polynomial structs.
  POLYNOMIAL *poly1 - pointer to first polynomial
  POLYNOMIAL *poly2 - pointer to polynomial to be subtracted from the first 
  Returns a pointer to the difference POLYNOMIAL struct
*/
POLYNOMIAL* subtract(POLYNOMIAL *poly1, POLYNOMIAL *poly2) {
   
   // Allocate a new struct and copy the first operand into it
   POLYNOMIAL *newPoly = makePoly();
   newPoly->size = poly1->size;
   for (int i = 0; i < MAX_TERMS; i++){
      newPoly->terms[i]->coeff = poly1->terms[i]->coeff;
      newPoly->terms[i]->exp = poly1->terms[i]->exp;
   }

   int sizeCounter = 0;

   for (int i = 0; i < poly2->size; i++) {

      int index = 0;
      bool foundLikeTerm = false;
      int coeff = poly2->terms[i]->coeff;
      int exp = poly2->terms[i]->exp;

      // Look for like terms in the other polynomial
      for (int j = 0; j < newPoly->size; j++) {
	 if (newPoly->terms[j]->exp == poly2->terms[i]->exp) {
	    foundLikeTerm = true;
	    // Set location if we found a like term
	    index = j;
	 }
      }

      if (foundLikeTerm == false) {
	 // If we didn't find a like term, "add" the negated term
	 newPoly->terms[newPoly->size]->coeff = -(coeff);
	 newPoly->terms[newPoly->size]->exp = exp;
	 newPoly->size += 1;
      } else {
	 // Otherwise, subtract  coefficient
	 if (newPoly->terms[index]->coeff == coeff) {

	    // Special case where substraction would create
	    // a 0 value polynomial
	    newPoly->terms[index]->exp = 0;
	    // Leave size adjusting for later
	    sizeCounter -= 1;

	 }
	 newPoly->terms[index]->coeff -= coeff;
      }
   }

   // Adjust size
   newPoly->size += sizeCounter;
   // Return pointer to the result struct, leaving operands in original state
   return newPoly;
}

/*
  multiply() multiplies a given polynomial struct by a given scalar value
  int scalar - scalar value to multiply all coefficients
  POLYNOMIAL *polynomial - pointer to struct to be modified
*/
void multiply(int scalar, POLYNOMIAL *polynomial) {

   // Loop through polynomial and multiply coefficients
   for (int i = 0; i < polynomial->size; i++) {
      polynomial->terms[i]->coeff *= scalar;
   }
}
