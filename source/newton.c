#include "newton.h"

Complex findComplexForPixel(u16 px) {
    float fractionAccross = (float)(px % SCREEN_W)/SCREEN_W;
    float fractionDown = (float)(px / SCREEN_W)/SCREEN_H;
    Complex value;
    value.real = -1.0 + (fractionAccross * 2.0);
    value.imaginary = 1.0 - (fractionDown * 2.0);
    return value;
}

void newton(Polynomial* polynomial, Polynomial* derivative, Complex* complex, u8 iterations) {
    // To estimate: z2 = z1 - (P(z1)/P'(z1))
    Complex numerator;
    Complex denominator;
    while (iterations > 0) {
        numerator = value_imaginary(polynomial, complex);
        denominator = value_imaginary(derivative, complex);
        *complex = division(&numerator, &denominator);
        iterations--;
    }
}

u16 nearestRoot(Roots* roots, Complex* complex, Polynomial* p) {
    float smallestDistance = 1000.0;
    float dist = 0.0;
    u16 color;
    for (int i = 0; i < p->degree; i++) {
        dist = distance(complex, &roots->root[i]);
        if (dist < smallestDistance) {
            color = roots->colors[i];
            smallestDistance = dist;
        }
    }
    return color;
}

float distance(Complex* c1, Complex* c2) {
    float a_sq = int_power((c1->real - c2->real), 2);
    float b_sq = int_power((c1->imaginary - c2->imaginary), 2);
    return a_sq + b_sq;
}