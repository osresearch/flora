/** Use the capacitive sensor to control the brightness of the LEDs.
 */
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PIN		6
#define NUM_PIXELS	1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	NUM_PIXELS,			// how many pixels on strip?
	PIN,				// output pin?
	NEO_GRB + NEO_KHZ800		// type of pixels?
);

CapacitiveSensor capsensor = CapacitiveSensor(9,10);

void setup() {
	pixels.begin();
	//capsensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
	Serial.begin(9600);
}

long smooth = 0;

void loop() {
	long val = capsensor.capacitiveSensor(100);
/*
	if (val < 200 && smooth < 200)
	{
		// small values make very small changes
		smooth = (smooth * 127 + val) / 128;
	} else
	if (val > smooth)
	{
		smooth = (smooth * 3 + val) / 4;
	} else {
*/
	{
		smooth = (smooth * 31 + val) / 32;
	}

	Serial.print(val);
	Serial.print(" ");
	Serial.println(smooth);

	for(int i = 0 ; i < NUM_PIXELS ; i++)
	{
		int v = smooth / 8;
		if (v > 255)
			v = 255;
		pixels.setPixelColor(i, v, 0, 0);
	}

	pixels.show();
	delay(10);
}
