#include <Adafruit_NeoPixel.h>

#define PIN		12
#define NUM_PIXELS	16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);


int chance = 0;

void setup() {
	pixels.begin();
}

#define NUM_COLORS 6
const uint8_t palette[][3] = {
	{ 255, 255, 255 },
	{ 255, 255, 255 },
	{ 255, 0, 0 },
	{ 255, 100, 0 },
	{ 0, 100, 200 },
	{ 40, 100, 200 },
};

void loop() {
	// fade all the pixels
	for(int i = 0 ; i < NUM_PIXELS ; i++)
	{
		uint32_t c = pixels.getPixelColor(i);
		int r = (c >> 16) & 0xFF;
		int g = (c >>  8) & 0xFF;
		int b = (c >>  0) & 0xFF;

		// chance goes from 0-127, so this limits the
		// blending to 4-12.  4 == fast, 12 == slow
		int blending = 4 + 8 - (chance / 16);

		r = (r * blending) / (blending+1);
		g = (g * blending) / (blending+1);
		b = (b * blending) / (blending+1);
		pixels.setPixelColor(i, r, g, b);
	}

	// Make flashes that increase in frequency
	if (random(90) <= chance)
	{
		chance = (chance + 1) % 128;

		int c = random(NUM_COLORS);
		
		pixels.setPixelColor(
			random(0, NUM_PIXELS),
			palette[c][0],
			palette[c][1],
			palette[c][2]
		);
	}

	pixels.show();
	delay(50);

}
