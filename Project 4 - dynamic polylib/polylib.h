#ifndef CIRCLEUTIL_H
#define CIRCLEUTIL_H

/*
 File: polylib.h
 Author: Rostislav Tsiomenko
 Date: 4/06/12
 Section: 01
 Email: tsiomr1@umbc.edu

 This is the header file required for Project 4, 
 with all the typedefs and function prototypes.

*/

typedef struct term {
   int coeff;
   int exp;
} TERM;

typedef struct polynomial {
   TERM **terms;
   int size;
 } POLYNOMIAL;

/*
  addTerm adds a term to the given polynomial.
  POLYNOMIAL *polynomial - pointer to polynomial struct to be modified
  int coefficient - coefficient of new term
  int exponent - exponent of new term
*/
void addTerm(POLYNOMIAL *polynomial, int coefficient, int exponent);

/*
  printPolynomial prints out the polynomial
  according to the project rules.
  int index - array index of the polynomial being printed
  POLYNOMIAL *polynomial - pointer to polynomial struct to be printed
*/
void printPolynomial(int index, POLYNOMIAL *polynomial);

/*
  sortPolynomial sorts the terms of a polynomial in descending
  order (i.e. first term (index 0) has highest exponent) using insertion sort
  POLYNOMIAL *polynomial - pointer topolynomial struct to sort
*/
void sortPolynomial(POLYNOMIAL *polynomial);

/*
  add returns a pointer to the resulting polynomial struct from the summation of two polynomial structs.
  POLYNOMIAL *poly1 - pointer to first polynomial
  POLYNOMIAL *poly2 - pointer to polynomial to be added to the first 
  Returns a pointer to the sum POLYNOMIAL struct
*/
POLYNOMIAL* add(POLYNOMIAL *poly1, POLYNOMIAL *poly2);

/*
  subtract returns the pointer to the resulting polynomial struct from the difference of two passed in polynomial structs.
  POLYNOMIAL *poly1 - pointer to first polynomial
  POLYNOMIAL *poly2 - pointer to polynomial to be subtracted from the first 
  Returns a pointer to the difference POLYNOMIAL struct
*/
POLYNOMIAL* subtract(POLYNOMIAL *poly1, POLYNOMIAL *poly2);

/*
  multiply() multiplies a given polynomial struct by a given scalar value
  int scalar - scalar value to multiply all coefficients
  POLYNOMIAL *polynomial - pointer to struct to be modified
*/
void multiply(int scalar, POLYNOMIAL *polynomial);

/*
  makePoly returns a pointer to a new dynamically allocated
  polynomial struct, complete with a dynamically allocated
  array of term structs, all initialized to 0.
  Returns a pointer to an empty, initialized polynomial struct.
 */
POLYNOMIAL* makePoly();

/*
  destroyPoly goes through the polynomial struct
  pointed to by p and frees all memory associated
  with that struct.
 */
void destroyPoly (POLYNOMIAL* p);

#endif
