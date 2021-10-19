#include "polynomials.h"
#include <math.h>

float int_power(float base, u8 exponent) {
    float power = 1;
    for (int i = 0; i < exponent; i++) {
        power *= base;
    }
    return power;
}

Complex int_power_imaginary(Complex* base, u8 exponent) {
     Complex power;
     power.real = 1;
     power.imaginary = 0;
     for (int i = 0; i < exponent; i++) {
         power = multiply(base, &power);
     }
     return power;
}

float value(Polynomial* p, float x) {
    float value = 0;
    for (int i = 0; i <= p->degree; i++) {
        float power = int_power(x, i);
        value += p->coefficients[i] * power;
    }
    return value;
}

Complex value_imaginary(Polynomial* p, Complex* complex) {
    Complex value;
    value.real = 0;
    value.imaginary = 0;
    for (int i = 0; i <= p->degree; i++) {
        Complex power = int_power_imaginary(complex, i);
        value.real += p->coefficients[i] * power.real;
        value.imaginary += p->coefficients[i] * power.imaginary;
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