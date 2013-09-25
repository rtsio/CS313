#ifndef CIRCLEUTIL_H
#define CIRCLEUTIL_H

/*
 File: polylib.h
 Author: Rostislav Tsiomenko
 Date: 3/12/12
 Section: 01
 Email: tsiomr1@umbc.edu

 This is the header file required for Project 3, 
 with all the typedefs and function prototypes.

*/

#define TERM_LIMIT 20

typedef struct term {
   int coefficient;
   int exponent;
} TERM;

typedef struct polynomial {
   TERM terms[TERM_LIMIT];
   int size;
 } POLYNOMIAL;

/*
  addTerm adds a term to the given polynomial.
  POLYNOMIAL polynomial - polynomial struct to be modified
  int coefficient - coefficient of new term
  int exponent - exponent of new term
  Returns the updated struct
*/
struct polynomial addTerm(POLYNOMIAL polynomial, int coefficient, int exponent);

/*
  printPolynomial prints out the polynomial
  according to the project rules.
  int index - array index of the polynomial being printed
  POLYNOMIAL polynomial - struct to be printed
*/
void printPolynomial(int index, POLYNOMIAL polynomial);

/*
  sortPolynomial sorts the terms of a polynomial in descending
  order (i.e. first term (index 0) has highest exponent) using insertion sort
  POLYNOMIAL polynomial - polynomial struct to sort
  Returns sorted struct
*/
struct polynomial sortPolynomial(POLYNOMIAL polynomial);

/*
  add returns the resulting polynomial struct from the summation of two passed in polynomial structs.
  POLYNOMIAL poly1 - first polynomial
  POLYNOMIAL poly2 - polynomial to be added to the first 
  Returns a sum POLYNOMIAL struct
*/
struct polynomial add(POLYNOMIAL poly1, POLYNOMIAL poly2);

/*
  subtract returns the resulting polynomial struct from the difference of two passed in polynomial structs.
  POLYNOMIAL poly1 - first polynomial
  POLYNOMIAL poly2 - polynomial to be subtracted from the first 
  Returns a difference POLYNOMIAL struct
*/
struct polynomial subtract(POLYNOMIAL poly1, POLYNOMIAL poly2);

/*
  multiply() multiplies a given polynomial struct by a given scalar value
  int scalar - scalar value to multiply all coefficients
  POLYNOMIAL polynomial - struct to be modified
  Returns multiplied struct
*/
struct polynomial multiply(int scalar, POLYNOMIAL polynomial);

#endif
