// vim: set ts=2 expandtab:
// Please don't move or delete the line above!  Thx, Holly
#include <Adafruit_NeoPixel.h>

#define PIN 		6	
#define NUM_PIXELS	7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
  NUM_PIXELS,			// how many pixels on strip?
  PIN,				// output pin?
  NEO_GRB + NEO_KHZ800		// type of pixels?
);

int brightness = 0;

// This is code was adapted from code from Adafruit
// Makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// This is code from Adafruit
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


void setup() {
	pixels.begin();
	pixels.setBrightness(50);
	
}


void loop() {
  rainbowCycle(5);
	
}
