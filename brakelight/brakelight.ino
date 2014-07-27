/**
 * 24-pixel ring on my backpack.
 * Cycles through a few patterns.
 */
#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 24
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;
uint8_t pos = 0;
uint8_t skip = 0;


static const uint8_t palette[][4] PROGMEM =
{
#if 0
	{ 128,   0,   0 },
	{ 128, 128,   0 },
	{   0, 128,   0 },
	{   0, 128, 128 },
	{ 128, 128, 128 },
	{ 128,   0, 128 },
#endif

#if 0
	{  50,   0,   0 },
	{ 100,   0,   0 },
	{   0,  50,   0 },
	{   0, 100,   0 },
	{   0,   0,  50 },
	{   0,   0, 100 },
#endif

#if 1
	//http://www.colourlovers.com/palette/1473/Ocean_Five
	{ 0, 160, 176 },
	{ 0, 160, 176 },
	{ 0, 160, 176 },
	{ 106, 74, 60 },
	{ 106, 74, 60 },
	{ 106, 74, 60 },
	{ 204, 51, 63 },
	{ 204, 51, 63 },
	{ 204, 51, 63 },
	{ 235, 104, 65 },
	{ 235, 104, 65 },
	{ 235, 104, 65 },
	{ 237, 201, 81 },
	{ 237, 201, 81 },
	{ 237, 201, 81 },
#endif

#if 0
	// http://www.colourlovers.com/palette/3419536/Hot_Pink_Print_Short
	{ 226, 31, 128 },
	{ 73, 1, 51 },
	{ 214, 140, 204 },
	{ 227, 252, 160 },
	{ 71, 219, 253 },
#endif
};


static void
blend(
	unsigned i,
	int smooth,
	int red,
	int green,
	int blue
)
{
	uint32_t c = strip.getPixelColor(i);
	int r = (c >> 16) & 0xFF;
	int g = (c >>  8) & 0xFF;
	int b = (c >>  0) & 0xFF;

	r = (r * smooth + red) / (smooth+1);
	g = (g * smooth + green) / (smooth+1);
	b = (b * smooth + blue) / (smooth+1);

	strip.setPixelColor(i, r, g, b);
}


static void
sparkle(
	int chance
)
{
	if (random(chance) == 0)
		strip.setPixelColor(random(NUM_PIXELS), 255, 255, 255);
}


void circle_pattern(void)
{
	for (int i = 0 ; i < NUM_PIXELS ; i++)
	{
		blend(i, 30, red, green, blue);
	}

	blend(pos, 30, 128, 128, 128);

	red = (red + 1) % 64;
	//green++;

	if (++skip >= 8)
	{
		skip = 0;
		if (++pos == NUM_PIXELS)
			pos = 0;
	}

	strip.show();
	delay(10);
}


static const uint32_t colors[] =
{
	0x400000,
	0x400000,
	0x402000,
	0x402000,
	0x400020,
	0x400020,
};

void multichase_pattern(void)
{
	red = 64;
	blue = 0;
	green = 0;

	for (int i = 0 ; i < NUM_PIXELS ; i++)
	{
		if (i % 6 == pos)
			blend(i, 8, 64, 20, 0);
		else
			blend(i, 100, 0, 0, 0);
	}

	if (++skip >= 16)
	{
		pos = (pos + 1) % 6;
		skip = 0;
	}

	sparkle(400);

	strip.show();
	delay(1);
}


static unsigned start_pixel = 0;

void pulse_pattern(void)
{
	red = 64;
	blue = 0;
	green = 0;

	++skip;

	if ((0 <= skip && skip < 48) || (96 <= skip && skip < 96+48))
	{
		unsigned phase = skip % 48;
		if (phase == 0)
			start_pixel = random(NUM_PIXELS);

		if (phase > NUM_PIXELS)
			phase = NUM_PIXELS;

		for (int i = 0 ; i < phase ; i++)
			blend(
				(i+start_pixel) % NUM_PIXELS,
				8,
				red, green, blue
			);
	} else
	{
		if (skip > 300)
			skip = 0;
		for (int i = 0 ; i < NUM_PIXELS ; i++)
			blend(i, 30, 0, 0, 0);
	}

	sparkle(200);

	strip.show();
	delay(1);
}


typedef void (*function_t)(void);

static function_t patterns[] = {
	circle_pattern,
	multichase_pattern,
	pulse_pattern,
};

static const unsigned num_patterns = sizeof(patterns)/sizeof(*patterns);


void
loop()
{
	for (int i = 0 ; i < num_patterns; i++)
	{
		function_t pattern = patterns[random(num_patterns)];
		//function_t pattern = patterns[i];
	
		for (int len = 0 ; len < 2048 ; len++)
			pattern();
	}
}
