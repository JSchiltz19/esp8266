#ifndef LEDDRIVER_H
#define LEDDRIVER_H

class ledDriver{
	public:
		ledDriver(){} //Constructor empty for now
		void resetLEDArray();
		void showStrip();
		void setPixel(int pixel, byte r, byte g,  byte b);
		void setAll(byte r, byte g, byte b);

	private:
		byte ledR[NUM_LEDS];
		byte ledG[NUM_LEDS];
		byte ledB[NUM_LEDS];
		void writePixel(byte Color);
		void reset();
}

#endif