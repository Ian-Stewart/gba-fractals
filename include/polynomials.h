#ifndef __POLYNOMIALS_H__
#define __POLYNOMIALS_H__

#include "gba_mathUtil.h"
#include "gba_types.h"

/**
 * Polynomial stored in the following manner:
 * (ex 3x^5 -4x^4 - x^3 + 7x^2 + 6x + 5)
 * degree = 5
 * coefficients = [5, 6, 7, -1, -4, 3] (so, the coefficient of the c_5 * x ^5 is coefficients[5] )
 **/
typedef struct Polynomial {
    u8 degree;
    double* coefficients;
}Polynomial;

typedef struct Complex {
    double real;
    double imaginary;
}Complex;


extern void derivative(Polynomial* p, Polynomial* d);

extern double value(Polynomial* p, double x);
extern Complex value_imaginary(Polynomial* p, Complex* complex);
extern double int_power(double base, u8 exponent);
extern Complex int_power_imaginary(Polynomial* p, Complex* base, u8 exponent);
extern Complex division(Complex* numerator, Complex* denominator);

#endif