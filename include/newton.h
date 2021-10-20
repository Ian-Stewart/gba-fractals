#ifndef __NEWTON_H__
#define __NEWTON_H__

#include "gba_types.h"
#include "polynomials.h"
#include "gba_drawing.h"
#include "gba_mathUtil.h"

#define MAX_ITERATIONS 16
#define TOTAL_ITERATIONS_PER_FRAME 1024

// Size of roots is given by degree of polynomial
// FUNDAMENTAL THEOREM OF ALGEBGRA, BAYBEE
typedef struct Roots{
    Complex* root;
    u16* colors;
}Roots;


extern void newton(Polynomial* polynomial, Polynomial* derivative, Complex* complex, u8 iterations);
extern u16 nearestRoot(Roots* roots, Complex* complex, Polynomial* p);
extern float distance(Complex* c1, Complex* c2);
extern Complex findComplexForPixel(u16 px);

#endif