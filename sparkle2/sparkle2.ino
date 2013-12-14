/** Because sparkles.
 *  This is adapted from the "sparkles" program.
 *  It produces a constant rate of sparkles instead of ramping up
 *  sparkle intensity.
 */
#include <Adafruit_NeoPixel.h>

#define PIN		6
#define NUM_PIXELS	7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ400		// type of pixels?
);


int chance = 80;

void setup() {
	pixels.begin();
}

#define NUM_COLORS 6
const uint8_t palette[][3] = {
	{ 255, 255, 255 },
	{ 255, 255, 255 },
	{ 100, 200, 255 },
	{ 200, 100, 100 },
	{ 150, 100, 150 },
	{ 30, 20, 80 },
};

void loop() {
	// fade all the pixels
	for(int i = 0 ; i < NUM_PIXELS ; i++)
	{
		uint32_t c = pixels.getPixelColor(i);
		int r = (c >> 16) & 0xFF;
		int g = (c >>  8) & 0xFF;
		int b = (c >>  0) & 0xFF;

		// blending is constant
		int blending = 15;

		r = (r * blending) / (blending+1);
		g = (g * blending) / (blending+1);
		b = (b * blending) / (blending+1);
		pixels.setPixelColor(i, r, g, b);
	}

	// Make flashes that increase in frequency
	if (random(150) <= 10)
	{
		// we don't use chance in this version
		// chance = (chance + 1) % 128;

		int c = random(NUM_COLORS);
		
		pixels.setPixelColor(
			random(0, NUM_PIXELS),
			palette[c][0],
			palette[c][1],
			palette[c][2]
		);
	 }

	pixels.show();
	delay(10);

}
