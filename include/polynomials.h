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
    float* coefficients;
}Polynomial;

typedef struct Complex {
    float real;
    float imaginary;
}Complex;

extern void derivative(Polynomial* p, Polynomial* d);

extern float value(Polynomial* p, float x);
extern float int_power(float base, u8 exponent);

extern Complex value_imaginary(Polynomial* p, Complex* complex);
extern Complex int_power_imaginary(Complex* base, u8 exponent);
extern Complex division(Complex* numerator, Complex* denominator);
extern Complex multiply(Complex* c1, Complex* c2);

#endif