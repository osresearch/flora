#include <Adafruit_NeoPixel.h>

#define PIN		6
#define NUM_PIXELS	16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);

int position = 0;

void setup() {
	pixels.begin();
}

void loop() {
	// turn off all the pixels
	for(int i = 0 ; i < NUM_PIXELS ; i++)
		pixels.setPixelColor(i, 0, 0, 0);

	// and now turn on the one at position and the next few
	pixels.setPixelColor((position+0) % NUM_PIXELS, 0, 128, 0);
	pixels.setPixelColor((position+1) % NUM_PIXELS, 0, 64, 0);
	pixels.setPixelColor((position+2) % NUM_PIXELS, 0, 32, 0);
	pixels.setPixelColor((position+3) % NUM_PIXELS, 0, 16, 0);
	pixels.setPixelColor((position+4) % NUM_PIXELS, 0, 8, 0);
	pixels.setPixelColor((position+5) % NUM_PIXELS, 0, 4, 0);
	pixels.setPixelColor((position+6) % NUM_PIXELS, 0, 2, 0);

	pixels.show();
	delay(50);

	// go in the opposite direction; note that modular arithmetic
	// does not work right with negative numbers, so add in the modulus
	position = (position + NUM_PIXELS - 1) % NUM_PIXELS;
}
