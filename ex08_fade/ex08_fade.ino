/** Fade all the pixels.
 *
 * 
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
int direction = 1;

void setup() {
	pixels.begin();
}

void loop() {
	// fade all the pixels
	for(int i = 0 ; i < NUM_PIXELS ; i++)
	{
		// Query each pixel on the ring in turn.
		// For each pixel, grab the numerical value (0-255)
		// associated with the pixel based on it's 32-bit
		// representation in the machine.
		uint32_t c = pixels.getPixelColor(i);
		int r = (c >> 16) & 0xFF;
		int g = (c >>  8) & 0xFF;
		int b = (c >>  0) & 0xFF;

		// Reduce that value by 1/4 intensity (for each pixel).
		// So that each pixels fades from it's previous setting.
		r = (r * 3) / 4;
		g = (g * 3) / 4;
		b = (b * 3) / 4;
		pixels.setPixelColor(i, r, g, b);
	}

	// and now turn on the new lead pixel
	pixels.setPixelColor(position, 0, 128, 0);
	position = (position + NUM_PIXELS + direction) % NUM_PIXELS;

	// Randomly change direction
	if (random(100) == 0)
		direction = -direction;

	// Make a flash; 5% the time, turn on pixel on full brightness
	if (random(20) == 0)
		pixels.setPixelColor(random(0, NUM_PIXELS), 255, 255, 255);

	pixels.show();
	delay(50);
}
