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


const uint32_t colors[] = {
	0x2F0000,
	0x2F2F00,
	0x002F00,
	0x002F4F,
	0x00002F,
	0x2F002F,
};

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t
Wheel(uint16_t WheelPos) {
	const unsigned num_colors = sizeof(colors) / sizeof(*colors);
	unsigned num1 = (WheelPos / 256) % num_colors;
	unsigned num2 = (num1 + 1) % num_colors;
	uint32_t c1 = colors[num1];
	uint32_t c2 = colors[num2];
	unsigned ratio2 = WheelPos % 256;
	unsigned ratio1 = 255 - ratio2;

	unsigned r1 = (c1 >> 16) & 0xFF;
	unsigned g1 = (c1 >>  8) & 0xFF;
	unsigned b1 = (c1 >>  0) & 0xFF;
	unsigned r2 = (c2 >> 16) & 0xFF;
	unsigned g2 = (c2 >>  8) & 0xFF;
	unsigned b2 = (c2 >>  0) & 0xFF;

	uint32_t r = ((r1 * ratio1 + r2 * ratio2) / 256) & 0xFF;
	uint32_t g = ((g1 * ratio1 + g2 * ratio2) / 256) & 0xFF;
	uint32_t b = ((b1 * ratio1 + b2 * ratio2) / 256) & 0xFF;

	return (r << 16) | (g << 8) | (b << 0);
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
	delay(10);
	uint32_t color = Wheel(color_phase += 3);

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
