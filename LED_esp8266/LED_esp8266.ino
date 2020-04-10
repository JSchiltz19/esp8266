
#include "ledDriver.h"

byte data[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  pinMode(D8, OUTPUT);
  reset();

}


void loop() { 




}
