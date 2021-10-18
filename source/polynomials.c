#include "polynomials.h"
#include <math.h>

double int_power(double base, u8 exponent) {
    double power = 1;
    for (int i = 0; i < exponent; i++) {
        power *= base;
    }
    return power;
}

Complex int_power_imaginary(Polynomial* p, Complex* base, u8 exponent) {
    // TODO
}

double value(Polynomial* p, double x) {
    double value = 0;
    for (int i = 0; i <= p->degree; i++) {
        double power = int_power(x, i);
        value += p->coefficients[i] * power;
    }
    return value;
}

Complex value_imaginary(Polynomial* p, Complex* complex) {
    for (int i = 0; i <= p->degree; i++) {
        // TODO
    }
    return value;
}

void derivative(Polynomial* p, Polynomial* d) {
    d->degree = p->degree - 1;
    for (int i = 0; i < p->degree; i++) {
        d->coefficients[i] = p->coefficients[i  + 1] * (i + 1);
    }
}

Complex division(Complex* numerator, Complex* denominator) {
    Complex temporary;
    // Set as conjugate of denominator
    temporary.real = denominator->real;
    temporary.imaginary = -denominator->imaginary;
    Complex temporaryNumerator = multiply(numerator, &temporary);
    Complex temporaryDenominator = multiply(denominator, &temporary);

    // Set to restult, conjugate is not needed
    temporary.real = temporaryNumerator.real/temporaryDenominator.real;
    temporary.imaginary = temporaryNumerator.imaginary/temporaryDenominator.real;
    return temporary; 
}

Complex multiply(Complex* c1, Complex* c2) {
    Complex result;
    // (x+yi)(u+vi) = (xu - yv) + (xv+yu)i
    result.real = (c1->real * c2->real) - (c1->imaginary * c2->imaginary);
    result.imaginary = (c1->real * c2->imaginary) + (c1->imaginary * c2->real);
    return result;
}