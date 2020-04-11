
#include "effects.h"
#define BUTTON 2
//#define NUM_LEDS 100;

void setup() {
  effect ledStrip;
  Serial.begin(115200);
  pinMode(D8, OUTPUT);

  pinMode(BUTTON,INPUT_PULLUP);  // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), ledStrip.changeEffect, CHANGE); // pressed
  //reset();

}


void loop() { 




}
