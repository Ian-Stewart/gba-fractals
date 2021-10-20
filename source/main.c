#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_gfx.h"
#include "gba_drawing.h"
#include "gba_mathUtil.h"
#include "gba_input.h"
#include "polynomials.h"
#include "newton.h"

#include <string.h>

void configureMath();
void zoomIn();

// Math things
Polynomial degree_five;
Polynomial degree_four;
float coefficients[6];
float derivative_coefficients[5];
Roots roots;
Complex complex_roots[5];
u16 colors[6];
Complex center;
float width = 2.0;

u16 lastUpdatedPixel = 0;
u8 iterations = 5;

int main() {
	register_vblank_isr();

	configureMath();

	//Fill buffers with black
	memset(vid_page_front, 0x0404, SCREEN_W * SCREEN_H);
	memset(vid_page_back, 0x0404, SCREEN_W * SCREEN_H);
	
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = VIDEOMODE_3 | BGMODE_2;

	while (1) { //loop forever
		vblank_intr_wait();
		updateFractalsForFrame();
	}
	
	return 0;
}

void updateFractalsForFrame() {
	if (iterations > MAX_ITERATIONS) {
		return;
	}
 	// As iterations deepen, do fewer pixels per frame
	for (u32 i = 0; (i * iterations) < TOTAL_ITERATIONS_PER_FRAME; i++) {
		if (lastUpdatedPixel >= SCREEN_W * SCREEN_H) {
			lastUpdatedPixel = 0;
			zoomIn();
		} else {
			Complex valueToEstimate = findComplexForPixel(lastUpdatedPixel +1, &center, width);
			newton(&degree_five, &degree_four, &valueToEstimate, iterations);
			vid_page_front[lastUpdatedPixel + 1] = nearestRoot(&roots, &valueToEstimate, &degree_five);
			lastUpdatedPixel++;
		}
	}
}

void configureMath() {
	degree_five.degree = 5;
	degree_four.degree = 4;

	coefficients[5] = 1.1;
	coefficients[4] = 2.2;
	coefficients[3] = -3.0;
	coefficients[2] = -2.0;
	coefficients[1] = 1.0;
	coefficients[0] = -20.0;
	degree_five.coefficients = coefficients;
	degree_four.coefficients = derivative_coefficients;

	complex_roots[0].real = -0.279059;
	complex_roots[0].imaginary = 0.0;

	complex_roots[1].real = -2.24099;
	complex_roots[1].imaginary = -0.370451;
	
	complex_roots[2].real = -2.24099;
	complex_roots[2].imaginary = 0.370451;

	complex_roots[3].real = 0.35289;
	complex_roots[3].imaginary = 1.36364;

	complex_roots[4].real = 0.35289;
	complex_roots[4].imaginary = -1.36364;

	colors[0] = setColor(242/8, 231/8, 80/8);
	colors[1] = setColor(242/8, 184/8, 7/8);
	colors[2] = setColor(242/8, 135/8, 5/8);
	colors[3] = setColor(197/8, 33/8, 4/8);
	colors[4] = setColor(113/8, 3/8, 1/8);
	colors[5] = setColor(0, 0, 0);

	roots.colors = colors;
	roots.root = complex_roots;

	center.real = 0.0;
	center.imaginary = 0.0;

	derivative(&degree_five, &degree_four);
}

void zoomIn() {
	width /= 2.0;
	// TODO track towards interesting stuff
}