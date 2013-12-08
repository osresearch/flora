#include <Adafruit_NeoPixel.h>

#define PIN		12
#define NUM_PIXELS	16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);

int brightness = 0;

void setup() {
	pixels.begin();
}

void loop() {
	for(int i = 0 ; i < NUM_PIXELS ; i++)
		pixels.setPixelColor(i, brightness, 0, 0);
	pixels.show();
	delay(10);

	brightness++;
}
