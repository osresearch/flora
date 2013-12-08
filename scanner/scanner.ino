#include <Adafruit_NeoPixel.h>

#define PIN		6
#define NUM_PIXELS	7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ400		// type of pixels?
);

int position = 0;
int direction = 1;
unsigned skip = 0;

void setup() {
	pixels.begin();
}

void loop() {
	// fade all the pixels
	for(int i = 0 ; i < NUM_PIXELS ; i++)
	{
		uint32_t c = pixels.getPixelColor(i);
		int r = (c >> 16) & 0xFF;
		int g = (c >>  8) & 0xFF;
		int b = (c >>  0) & 0xFF;

		r = (r * 7) / 8;
		g = (g * 7) / 8;
		b = (b * 7) / 8;
		pixels.setPixelColor(i, r, g, b);
	}

	// and now turn on just the one at position
	pixels.setPixelColor(position, 255, 0, 0);

	if (skip++ % 8 == 0)
	{
		position = (position + NUM_PIXELS + direction) % NUM_PIXELS;
		if (position == 0 || position == NUM_PIXELS-1)
			direction = -direction;
	}

	pixels.show();
	delay(10);
}
