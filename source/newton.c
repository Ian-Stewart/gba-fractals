#include "newton.h"

Complex findComplexForPixel(u16 px, Complex* center, float width) {
    u16 accross = (px % SCREEN_W);
    u16 down = (px / SCREEN_W);
    float fractionAccross = (float)accross/SCREEN_W;
    float fractionDown = (float)down/SCREEN_H;
    Complex value;
    value.real = -(1.2) + (fractionAccross * 2.4);
    value.imaginary = 0.8 - (fractionDown * 1.6);
    value.real *= width;
    value.imaginary *= width;
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
    float smallestDistance = 1000000.0;
    float dist = 0.0;
    u16 color = roots->colors[p->degree];
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