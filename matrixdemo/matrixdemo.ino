/** Draw a hypno-rainbow on the 16x8 matrix.
 *
 */
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN		6
#define WIDTH		16
#define HEIGHT		8
#define TILES_X		2
#define TILES_Y		1


const char message[] = "Welcome to NYCResistor!";


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
	WIDTH,
	HEIGHT,
	TILES_X,
	TILES_Y,
	PIN,
	NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
	NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
	NEO_GRB + NEO_KHZ800
);


const uint32_t colors[] = {
	0x4F0000,
	0x4F4F00,
	0x004F00,
	0x004F4F,
	0x00004F,
	0x4F004F,
};


uint32_t Color(int r, int g, int b)
{
	if (r < 0) r = 0;
	if (r > 255) r = 255;
	if (g < 0) g = 0;
	if (g > 255) g = 255;
	if (b < 0) b = 0;
	if (b > 255) b = 255;

	return Adafruit_NeoMatrix::Color(r, g, b);
}


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

	// scale to GFX library color space
	return Color(r, g, b);
}


void setup() {
	matrix.begin();
	matrix.fillScreen(0);
}


unsigned phase;
unsigned color_phase;

static uint8_t
hexdigit(
	uint8_t x
)
{
	x &= 0xF;
	if (x < 0xA)
		return '0' + x - 0x0;
	else
		return 'A' + x - 0xA;
}


int x = 0;
#define SPEED 1

void loop() {
	delay(1);
	uint32_t color = Wheel(color_phase++);

	for (int x = 0 ; x < TILES_X * WIDTH ; x++)
	{
		for (int y = 0 ; y < TILES_Y * HEIGHT ; y++)
		{
			matrix.drawPixel(x, y, Wheel(x * 16 + y * 32 - color_phase * 16));
		}
	}

	matrix.setCursor(x/SPEED,1);
	matrix.setTextWrap(false);
	matrix.setTextColor(Color(128,128,128));

	const int message_len = sizeof(message) - 1;

	for (int i = 0 ; i < message_len ; i++)
		matrix.write(message[i]);

	if (x < -message_len * 6 * SPEED)
		x = TILES_X * WIDTH * SPEED;
	else
		x--;
	
	matrix.show();
}
