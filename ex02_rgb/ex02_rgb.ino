/** Flash the first pixel red, green and blue.
 *
 * This demonstrates the pixel strip definition, the setup and main loop
 * code for the FLORA and a NeoPixel ring.
 *
 */
#include <Adafruit_NeoPixel.h>

#define PIN		6
#define NUM_PIXELS	16

/*
 * The pixel ring is defined "at compile" time.  Since the hardware
 * probably doesn't that often, it is ok that the number of pixels
 * and pin wired to the pixels is fixed.
 */
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);


/*
 * This function is called when the FLORA "boots up" and is
 * responsible for initializing the hardware, setting any globals
 * and getting ready to run.
 */
void setup() {
	pixels.begin();
}


/*
 * This function is called continuously once the FLORA is running.
 * It doesn't need to ever return, but if it does it will be called
 * again.
 *
 * The pixels.setPixelColor() function takes four arguments:
 * 1. The pixel number (0 is the very first)
 * 2. The red intensity (0 is off, 255 is max)
 * 3. The green intensity
 * 4. The blue intensity
 */
void loop() {
	// Red on, green off, blue, off
	pixels.setPixelColor(0, 255, 0, 0);
	pixels.show();
	delay(500);

	// Green
	pixels.setPixelColor(0, 0, 255, 0);
	pixels.show();
	delay(500);

	// Blue
	pixels.setPixelColor(0, 0, 0, 255);
	pixels.show();
	delay(500);

	// Off
	pixels.setPixelColor(0, 0, 0, 0);
	pixels.show();
	delay(500);
}
