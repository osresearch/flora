/** \file
 * Log data from the accelerometer and then print it
 * to the serial port.
 */
#include <Wire.h>
#include <Adafruit_LSM303.h>
#include <Adafruit_NeoPixel.h>

Adafruit_LSM303 lsm;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
	1,
	6,
	NEO_GRB + NEO_KHZ800
);


#define NUM_SAMPLES 256
int16_t accel[NUM_SAMPLES][3];

void
setup(void)
{
	Serial1.begin(115200);
	lsm.begin();
	pixels.begin();
}


void
lsm_read_accel(void)
{
  // Read the accelerometer
  Wire.beginTransmission((uint8_t)LSM303_ADDRESS_ACCEL);
  Wire.write(Adafruit_LSM303::LSM303_REGISTER_ACCEL_OUT_X_L_A | 0x80);
  Wire.endTransmission();
  Wire.requestFrom((byte)LSM303_ADDRESS_ACCEL, (byte)6);

  // Wait around until enough data is available
  while (Wire.available() < 6);

  uint8_t xlo = Wire.read();
  uint8_t xhi = Wire.read();
  uint8_t ylo = Wire.read();
  uint8_t yhi = Wire.read();
  uint8_t zlo = Wire.read();
  uint8_t zhi = Wire.read();

  // Shift values to create properly formed integer (low byte first)
  lsm.accelData.x = (xlo | (xhi << 8)) >> 4;
  lsm.accelData.y = (ylo | (yhi << 8)) >> 4;
  lsm.accelData.z = (zlo | (zhi << 8)) >> 4;
}



int x = 0;

void
loop(void)
{
	// wait for the user to input something
	while (!Serial1.available())
	{
		lsm_read_accel();
		Serial1.print((int)lsm.accelData.x);
		Serial1.print(" ");
		Serial1.print((int)lsm.accelData.y);
		Serial1.print(" ");
		Serial1.print((int)lsm.accelData.z);
		Serial1.println();
		delay(100);
	}

	// read from the user
	while (Serial1.available())
		Serial1.read();

buffering:
	Serial1.println("delay");
	for (int i = 0 ; i < 3 ; i++)
	{
		pixels.setPixelColor(0, 0xFF0000);
		pixels.show();
		delay(300);
		pixels.setPixelColor(0, 0);
		pixels.show();
		delay(300);
	}


	Serial1.println("buffering data");
	int free_fall_count = 0;

	for (int i = 0 ; i < NUM_SAMPLES ; i++)
	{
		lsm_read_accel();
		accel[i][0] = lsm.accelData.x;
		accel[i][1] = lsm.accelData.y;
		accel[i][2] = lsm.accelData.z;

		float sum = sqrt(
			+ lsm.accelData.x * lsm.accelData.x
			+ lsm.accelData.y * lsm.accelData.y
			+ lsm.accelData.z * lsm.accelData.z
			);
		int free_fall = -100 < sum && sum < 100;
		if (free_fall)
		{
			free_fall_count++;
			if (free_fall_count > 10)
				pixels.setPixelColor(0, 0xFFFFFF);
			else
			if (free_fall_count > 5)
				pixels.setPixelColor(0, 0x0000FF);
		} else {
			free_fall_count = 0;
			pixels.setPixelColor(0, 0x000400);
		}

		pixels.show();

		delay(50);
	}

	pixels.setPixelColor(0, 0x440000);
	pixels.show();

	while (!Serial1.available())
	{
		Serial1.println("done");
		delay(1000);
	}

	while (Serial1.available())
		Serial1.read();

reprint:
	for (int i = 0 ; i < NUM_SAMPLES ; i++)
	{
		Serial1.print(i);
		Serial1.print(" ");
		Serial1.print(accel[i][0]);
		Serial1.print(" ");
		Serial1.print(accel[i][1]);
		Serial1.print(" ");
		Serial1.print(accel[i][2]);
		Serial1.println();
	}
	
	while (!Serial1.available())
	{
		Serial1.println("n to reprint, y to rescan");
		delay(1000);
	}

	while (1)
	{
		if (!Serial1.available())
			continue;
		char c = Serial1.read();
		if (c == 'n')
			goto reprint;
		if (c == 'y')
			goto buffering;
	}
}
