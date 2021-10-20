#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_gfx.h"
#include "gba_drawing.h"
#include "gba_mathUtil.h"
#include "gba_input.h"
#include "polynomials.h"
#include "newton.h"
#include "img_mario_walk.h"

#include <string.h>

void copyBitmapToPageLocation( u16* a_vidPage, const u16* bitmap, s16 w, s16 h, s16 x, s16 y);
void configureMath();
u16* page_flip();

u16* vid_page = vid_page_back;

// Math things
Polynomial degree_five;
Polynomial degree_four;
float coefficients[6];
float derivative_coefficients[5];
Roots roots;
Complex complex_roots[5];
u16 colors[5];

u16 lastUpdatedPixel = 0;
u8 iterations = 8;

int main() {
	register_vblank_isr();

	configureMath();

	memcpy(MEM_PALETTE, pallette, 16);

	//Fill buffers with black
	memset(vid_page_front, 0x0404, SCREEN_W * SCREEN_H);
	//memset(vid_page_back, 0x0404, SCREEN_W * SCREEN_H);
	
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = VIDEOMODE_4 | BGMODE_2;

	while (1) { //loop forever
		vblank_intr_wait();
		updateFractalsForFrame();
		//page_flip();
	}
	
	return 0;
}

void updateFractalsForFrame() {
	if (iterations > MAX_ITERATIONS) {
		return;
	}
 	// As iterations deepen, do fewer pixels per frame
	for (u8 i = 0; (i * iterations) < TOTAL_ITERATIONS_PER_FRAME; i++) {
		if (lastUpdatedPixel >= SCREEN_W * SCREEN_H) {
			lastUpdatedPixel = 0;
			iterations += 1;
		} else {
			Complex valueToEstimate = findComplexForPixel(lastUpdatedPixel +1);
			newton(&degree_five, &degree_four, &valueToEstimate, iterations);
			vid_page_front[lastUpdatedPixel + 1] = nearestRoot(&roots, &valueToEstimate, &degree_five);
			lastUpdatedPixel++;
		}
	}
}

void configureMath() {
	degree_five.degree = 5;
	degree_four.degree = 4;

	coefficients[5] = 1.5;
	coefficients[4] = -2.0;
	coefficients[3] = 3.0;
	coefficients[2] = -2.0;
	coefficients[1] = 1.0;
	coefficients[0] = 0.5;
	degree_five.coefficients = coefficients;
	degree_four.coefficients = derivative_coefficients;

	complex_roots[0].real = -0.274183;
	complex_roots[0].imaginary = 0.0;

	complex_roots[1].real = 0.072592;
	complex_roots[1].imaginary = -1.126704;

	complex_roots[2].real = 0.072592;
	complex_roots[2].imaginary = 1.126704;

	complex_roots[3].real = -0.274183;
	complex_roots[3].imaginary = 0.0;

	complex_roots[4].real = -0.274183;
	complex_roots[4].imaginary = 0.0;

	complex_roots[5].real = -0.274183;
	complex_roots[5].imaginary = 0.0;

	colors[0] = 0x0202;
	colors[1] = 0x0400;
	colors[2] = 0x0404;
	colors[3] = 0x0303;
	colors[4] = 0x0002;

	roots.colors = colors;
	roots.root = complex_roots;
	
	derivative(&degree_five, &degree_four);
}

u16* page_flip() {
	vid_page = (u16*)((u32)vid_page ^ VRAM_PAGE_SIZE);
	REG_DISPCNT ^= VIDEO_PAGE;	// update control register	
	return vid_page;
}