#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Arduino.h>

//#define NUM_LEDS 100

#define LED_PIN 0x8000 //D8
#define NUM_LEDS 100

class ledDriver{
	public:
		ledDriver(){ //Constructor empty for now
    }
		void resetLEDArray();
		void showStrip();
		void setPixel(int pixel, uint8_t r, uint8_t g,  uint8_t b);
    uint32_t getPixel(int pixel);
		void setAll(uint8_t r, uint8_t g, uint8_t b);

	private:
		uint8_t ledR[NUM_LEDS];
		uint8_t ledG[NUM_LEDS];
		uint8_t ledB[NUM_LEDS];
		void writePixel(uint8_t Color);
		void reset();
};

#endif