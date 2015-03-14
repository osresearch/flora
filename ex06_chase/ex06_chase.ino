/** Chase a single pixel around the ring.
 *
 * This example shows how pixels can be changed multiple times
 * between calls to pixels.show();
 */
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
	// turn off all pixels
	for(int i = 0 ; i < NUM_PIXELS ; i++)
		pixels.setPixelColor(i, 0, 0, 0);

	// and now turn on just the one at the current position
	pixels.setPixelColor(position, 128, 128, 0);

	// increment the position, wrapping at the number of pixels
	position = (position + 1) % NUM_PIXELS;

	pixels.show();
	delay(50);
}
