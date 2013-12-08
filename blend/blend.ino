#include <Adafruit_NeoPixel.h>

#define PIN		12
#define NUM_PIXELS	16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);

float g_pos = 0;
float r_pos = 0;
unsigned beat = 0;

void setup() {
	pixels.begin();
}

int limit(int x)
{
	if (x > 255)
		return 255;
	if (x < 0)
		return 0;
	return x;
}

void
blend_pixel(
	int n,
	int blending,
	int new_r,
	int new_g,
	int new_b
)
{
	uint32_t c = pixels.getPixelColor(n);
	int r = (c >> 16) & 0xFF;
	int g = (c >>  8) & 0xFF;
	int b = (c >>  0) & 0xFF;

	r = (r * blending + new_r) / (blending+1);
	g = (g * blending + new_g) / (blending+1);
	b = (b * blending + new_b) / (blending+1);

	pixels.setPixelColor(n, limit(r), limit(g), limit(b));
}

void loop() {
	// fade all the pixels pretty fast
	for(int i = 0 ; i < NUM_PIXELS ; i++)
		blend_pixel(i, 7, 0, 0, 0);

	blend_pixel(int(g_pos), 1, 85, 0, 30);
	g_pos = (g_pos + 0.63);
	if (g_pos > NUM_PIXELS)
		g_pos = 0;
	else if (g_pos < 0)
		g_pos = NUM_PIXELS-1;

	blend_pixel(int(r_pos), 1, 128, 0, 0);
	r_pos = (r_pos - 0.23);
	if (r_pos > NUM_PIXELS)
		r_pos = 0;
	else if (r_pos < 0)
		r_pos = NUM_PIXELS-1;

	// and once in a while flash all of them
	beat++;
	if (beat % 100 == 0 || beat % 100 == 12)
	{
		for(int i = 0 ; i < NUM_PIXELS ; i++)
			blend_pixel(i, 1, 200, 80, 0);
	}

	pixels.show();
	delay(20);
}
