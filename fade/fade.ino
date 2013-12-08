#include <Adafruit_NeoPixel.h>

#define PIN		6
#define NUM_PIXELS	16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);

int position = 0;
int direction = 1;

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

		r = (r * 3) / 4;
		g = (g * 3) / 4;
		b = (b * 3) / 4;
		pixels.setPixelColor(i, r, g, b);
	}

	// and now turn on just the one at position
	pixels.setPixelColor(position, 0, 128, 0);
	position = (position + NUM_PIXELS + direction) % NUM_PIXELS;
	if (random(100) == 0)
		direction = -direction;

	// Make flashes; 5% the time, turn on pixel on full brightness
	if (random(20) == 0)
		pixels.setPixelColor(random(0, NUM_PIXELS), 255, 255, 255);

	pixels.show();
	delay(50);

}
