#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Arduino.h>

#define LED_PIN 0x8000 //D8
#define NUM_LEDS 100

class ledDriver{
	public:
		ledDriver(int numLeds);
        ~ledDriver();
		void resetLEDArray();
		void showStrip();
		void setPixel(int pixel, byte r, byte g,  byte b);
    uint32_t getPixel(int pixel);
		void setAll(byte r, byte g, byte b);

	private:
<<<<<<< HEAD
    int numLeds;
	//  const int ledPin;
=======
>>>>>>> parent of 14fd36c... added dynamic led number
    byte* ledR;
    byte* ledG;
    byte* ledB;
		void writeStrip(byte Color);
		void reset();
};

#endif