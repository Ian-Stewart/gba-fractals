#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_gfx.h"
#include "gba_drawing.h"
#include "gba_mathUtil.h"
#include "gba_input.h"
#include "polynomials.h"
#include "newton.h"

//include the header file for the bitmap image
#include "img_mario_walk_1.h"
#include "img_mario_walk_2.h"
#include "img_mario_walk_3.h"

#include <string.h>

void copyBitmapToPageLocation( u16* a_vidPage, const u16* bitmap, s16 w, s16 h, s16 x, s16 y);

u16* vid_page = vid_page_back;

u16* page_flip()
{
	vid_page = (u16*)((u32)vid_page ^ VRAM_PAGE_SIZE);
	REG_DISPCNT ^= VIDEO_PAGE;	// update control register	
	return vid_page;
}

void test() {
	Polynomial degree_five;
	Polynomial degree_four;

	degree_five.degree = 5;
	degree_four.degree = 4;

	float coefficients[6];
	coefficients[5] = 1.5;
	coefficients[4] = -2.0;
	coefficients[3] = 3.0;
	coefficients[2] = -2.0;
	coefficients[1] = 1.0;
	coefficients[0] = 0.5;
	degree_five.coefficients = coefficients;
	derivative(&degree_five, &degree_four);

	Polynomial degree_two;
	degree_two.degree = 2;
	degree_two.coefficients = &coefficients[3];

	Roots roots;
	Complex complex_roots[5];
	u16 colors[5];

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

	Complex result_of_value = value_imaginary(&degree_five, complex_roots);

	float test = 0.0;
}

int main()
{

	register_vblank_isr();
	//Mario bitmap image sizes
	s8 marioH = 90;
	s8 marioW = 70;

	//copy colour palette into memory
	memcpy(MEM_PALETTE, img_mario_walk_1Pal, img_mario_walk_1PalLen);
	//set background memory to palette colour 1. Fill screen with white.
	memset(vid_page_front, img_mario_walk_1Bitmap[0], SCREEN_W * SCREEN_H);
	memset(vid_page_back, img_mario_walk_1Bitmap[0], SCREEN_W * SCREEN_H);
	
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = VIDEOMODE_4 | BGMODE_2;

	copyBitmapToPageLocation( vid_page_front, img_mario_walk_1Bitmap, marioW, marioH, 10, 10);
	copyBitmapToPageLocation( vid_page_back, img_mario_walk_2Bitmap, marioW, marioH, 10, 10);
	s8 keyFrame = 0;

	test();

	while (1) { //loop forever
		vblank_intr_wait();

		PollKeys();

		if( keyReleased(A) )
		{
			++keyFrame;
			keyFrame = keyFrame & 0x3;
			switch (keyFrame)
			{
				case 1:
				{
					copyBitmapToPageLocation( vid_page_back, img_mario_walk_2Bitmap, marioW, marioH, 10, 10);
					break;
				}
				case 3:
				{
					copyBitmapToPageLocation( vid_page_back, img_mario_walk_3Bitmap, marioW, marioH, 10, 10);
					break;
				}
				
				default:
					break;
			}
			page_flip();
		}
		
	}
	
	return 0;
}
//Function to copy bitmap data to screen based on width and height
void copyBitmapToPageLocation( u16* a_vidPage, const u16* bitmap, s16 w, s16 h, s16 x, s16 y)
{
	u16 screenLocation = 0;
	u16 bitmapLocation = 0;
	for( s16 i = 0; i < h; ++i )
	{
		screenLocation =  (y + i) * 120 + x; 
		bitmapLocation = (i * w>>1)+i;

		memcpy( &a_vidPage[screenLocation], &bitmap[bitmapLocation], w);
	}
}