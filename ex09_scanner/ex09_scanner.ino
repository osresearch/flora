/** "Larson scanner" animation for Holly's jacket.
 *
 * Turns the seven LEDs on in a back-and-forth scan pattern
 * with a decaying fade as the scan passes by.
 *
 * Uses the pixels.getPixelColor() to retrieve the current color,
 * and then does bit-manipulation to decay by a factor of 7/8th
 * each time.
 *
 * The speed of the scan is limited to keep it visible.
 * But we want to update the decaying values more frequently,
 * so a skip variable is used.
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

	if (random(50) == 0)
		pixels.setPixelColor(random(NUM_PIXELS), 255, 255, 255);

	if (skip++ % 8 == 0){

	//{
		//position = (position + NUM_PIXELS + direction) % NUM_PIXELS;
		//if (position == 0 || position == NUM_PIXELS-1)
			//direction = -direction;
	//}

		if (position == 0)
			direction = +1;
		if (position == NUM_PIXELS-1)
			direction = -1;
		position = position + direction;
	}

	pixels.show();
	delay(10);
}
