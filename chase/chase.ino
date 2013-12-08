#include <Adafruit_NeoPixel.h>

#define PIN		12
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
	// turn them all off
	for(int i = 0 ; i < NUM_PIXELS ; i++)
		pixels.setPixelColor(i, 0, 0, 0);

	// and now turn on the one at position and the next few
	pixels.setPixelColor(position, 0, 128, 0);

	pixels.show();
	delay(20);

	// increment the position, wrapping at the number of pixels
	//position = (position + 1) % NUM_PIXELS;
	position = (position + NUM_PIXELS - 1) % NUM_PIXELS;
}
