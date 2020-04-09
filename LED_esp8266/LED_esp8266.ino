
#include "ledDriver.h"

byte data[NUM_LEDS];

void setup() {
  Serial.begin(115200);

  //PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U,FUNC_GPIO15); 
  pinMode(D8, OUTPUT);
  reset();

}


void loop() { 




}
