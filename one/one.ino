#include <Adafruit_NeoPixel.h>

#define PIN		12
#define NUM_PIXELS	16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);


void setup() {
	pixels.begin();
}

void loop() {
	pixels.setPixelColor(0, 255, 0, 0);
	pixels.show();
	delay(500);
	pixels.setPixelColor(0, 0, 255, 0);
	pixels.show();
	delay(500);
	pixels.setPixelColor(0, 0, 0, 255);
	pixels.show();
	delay(500);
}
