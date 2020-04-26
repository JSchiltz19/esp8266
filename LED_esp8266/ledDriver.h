#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Arduino.h>

#define LED_PIN 0x8000 //D8

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
    int numLeds;
	const inline int ledPin;
    byte* ledR;
    byte* ledG;
    byte* ledB;
		void writeStrip(byte Color);
		void reset();
};

#endif