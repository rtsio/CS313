/*
  File: polylib.c
  Name: Rostislav Tsiomenko
  Date: 03/13/2012
  Sect: 01
  Mail: tsiomr1@umbc.edu

  This is the polynomial functions library
  for Project 3.
  
  See http://www.csee.umbc.edu/courses/undergraduate/313/spring12/Projects/p3/index.shtml

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "polylib.h"

/*
  printPolynomial prints out the polynomial
  according to the project rules.
  int index - array index of the polynomial being printed
  POLYNOMIAL polynomial - struct to be printed
*/
void printPolynomial(int index, POLYNOMIAL polynomial) {
   
   printf("Polynomial #%d = ", index);

   // Deal with 0 value polynomials
   if (polynomial.terms[0].coefficient == 0 && polynomial.terms[0].exponent == 0) {
     
      printf("0\n\n");

   } else {

      for (int i = 0; i < polynomial.size; i++) {

	 int coeff;

	 // If we're at the first term, don't suppress the negative sign
	 if (i == 0) { 
	    coeff = polynomial.terms[i].coefficient;
	 } else {
	    // Otherwise, suppress it and we'll deal with it later
	    coeff = abs(polynomial.terms[i].coefficient);
	 }
	 int exp = polynomial.terms[i].exponent;
	
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
	    if ((polynomial.size - (i+1)) != 0 && (polynomial.terms[i+1].coefficient >= 0)) {
	       //..print a plus
	       printf(" + ");
	    } else if ((polynomial.size - (i+1)) != 0){
	       // if we're at the end but the next term is negative, print a minus
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
  POLYNOMIAL polynomial - polynomial struct to be modified
  int coefficient - coefficient of new term
  int exponent - exponent of new term
  Returns the updated struct
*/
struct polynomial addTerm(POLYNOMIAL polynomial, int coefficient, int exponent) {

   bool foundLikeTerm = false;
   // Search for like terms and sum coefficients if found
   for (int i = 0; i < polynomial.size; i++) {
      if (polynomial.terms[i].exponent == exponent) {
	 polynomial.terms[i].coefficient += coefficient;
	 foundLikeTerm = true;
      }
   }
   
   // Otherwise, create a new term and increment size
   if (foundLikeTerm == false) {
      polynomial.terms[polynomial.size].exponent = exponent;
      polynomial.terms[polynomial.size].coefficient = coefficient;
      polynomial.size++;
   }

   // Keep it sorted
   polynomial = sortPolynomial(polynomial);
   return polynomial;

}

/*
  sortPolynomial sorts the terms of a polynomial in descending
  order (i.e. first term (index 0) has highest exponent) using insertion sort
  POLYNOMIAL polynomial - polynomial struct to sort
  Returns sorted struct
*/
struct polynomial sortPolynomial(POLYNOMIAL polynomial) {

   // Simple insertion sort comparing exponents
   for (int i = 0; i < polynomial.size; i++) {

      TERM temp = polynomial.terms[i];
      int j = i-1;

      while (j >= 0 && polynomial.terms[j].exponent < temp.exponent) {
	 polynomial.terms[j+1] = polynomial.terms[j];
	 j = j-1;
      }

      polynomial.terms[j+1] = temp;
   }

   return polynomial;
}

/*
  add returns the resulting polynomial struct from the summation of two passed in polynomial structs.
  POLYNOMIAL poly1 - first polynomial
  POLYNOMIAL poly2 - polynomial to be added to the first 
  Returns a sum POLYNOMIAL struct
*/
struct polynomial add(POLYNOMIAL poly1, POLYNOMIAL poly2) {
   
   for (int i = 0; i < poly2.size; i++) {

      int index = 0;
      bool foundLikeTerm = false;
      TERM temp = poly2.terms[i];

      // Look for like terms in the other polynomial 
      for (int j = 0; j < poly1.size; j++) {
	 if (poly1.terms[j].exponent == poly2.terms[i].exponent) {
	    foundLikeTerm = true;
	    // Set the location of like term if found
	    index = j;
	 }
      }

      if (foundLikeTerm == false) {
	 // If we didn't find a like term, create a new one at the end
	 poly1.terms[poly1.size] = temp;
	 poly1.size++;
      } else {
	 // If we DID find a like term, sum coefficients
	 poly1.terms[index].coefficient += temp.coefficient;
      }
   }

   // Keep it sorted
   poly1 = sortPolynomial(poly1);
   return poly1;
}

/*
  subtract returns the resulting polynomial struct from the difference of two passed in polynomial structs.
  POLYNOMIAL poly1 - first polynomial
  POLYNOMIAL poly2 - polynomial to be subtracted from the first 
  Returns a difference POLYNOMIAL struct
*/
struct polynomial subtract(POLYNOMIAL poly1, POLYNOMIAL poly2) {

   for (int i = 0; i < poly2.size; i++) {

      int index = 0;
      bool foundLikeTerm = false;
      TERM temp;
      // Negate the term so we end up subtracting it
      temp.coefficient = -(poly2.terms[i].coefficient);
      temp.exponent = -(poly2.terms[i].exponent);

      // Look for like terms in the other polynomial
      for (int j = 0; j < poly1.size; j++) {
	 if (poly1.terms[j].exponent == poly2.terms[i].exponent) {
	    foundLikeTerm = true;
	    // Set location if we found a like term
	    index = j;
	 }
      }

      if (foundLikeTerm == false) {
	 // If we didn't find a like term, "add" the term (since it's been negated)
	 poly1.terms[poly1.size] = temp;
	 poly1.size++;
      } else {
	 // Otherwise, subtract coefficients
	 poly1.terms[index].coefficient -= temp.coefficient;
 
      }
   }

   // Keep it sorted
   poly1 = sortPolynomial(poly1);
   return poly1;
}

/*
  multiply() multiplies a given polynomial struct by a given scalar value
  int scalar - scalar value to multiply all coefficients
  POLYNOMIAL polynomial - struct to be modified
  Returns multiplied struct
*/
struct polynomial multiply(int scalar, POLYNOMIAL polynomial) {

   // Loop through polynomial and multiply coefficients
   for (int i = 0; i < polynomial.size; i++) {
      polynomial.terms[i].coefficient *= scalar;
   }
  
   return polynomial;
}
