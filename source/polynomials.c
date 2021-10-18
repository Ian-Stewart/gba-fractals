#include "polynomials.h"

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
    // TODO
}