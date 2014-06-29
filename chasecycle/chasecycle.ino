/** Ramp all of the pixels out of phase with each other
 *
 */
#include <Adafruit_NeoPixel.h>

#define PIN		6
#define NUM_PIXELS	4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t
Wheel(byte WheelPos) {
	if(WheelPos < 85) {
		return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} else
	if(WheelPos < 170) {
		WheelPos -= 85;
		return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}

int bright[NUM_PIXELS];

void setup() {
	pixels.begin();

	// turn off all the pixels
	for(int i = 0 ; i < NUM_PIXELS ; i++)
	{
		pixels.setPixelColor(i, 0, 0, 0);
		bright[i] = i * 512 / NUM_PIXELS;
	}
}


unsigned phase;
unsigned color_phase;

void loop() {
	delay(20);
	uint32_t color = Wheel((color_phase++) % 256);

	for (unsigned i = 0 ; i < NUM_PIXELS ; i++)
	{
		// make the one pixel be bright and smoothly color shifting
		int r = (color >> 16) & 0xFF;
		int g = (color >>  8) & 0xFF;
		int b = (color >>  0) & 0xFF;

		// ramp the brightness up and down
		bright[i] = (bright[i] + 1) % 512;
		int v = bright[i];
		if (v >= 256)
			v = 511 - v;

		r = (r * v) / 256;
		g = (g * v) / 256;
		b = (b * v) / 256;

		pixels.setPixelColor(i, r, g, b);
		//pixels.setPixelColor(i, 0, 10, 0);
	}

	// add some random sparkles
	if (random(1000) < 2)
		pixels.setPixelColor(random(NUM_PIXELS), 255, 255, 255);

	pixels.show();
}
