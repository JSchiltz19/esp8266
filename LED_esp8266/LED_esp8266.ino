
#include "effects.h"

effect ledStrip = effect(100, D8);

void setup() {
  Serial.begin(115200);
  pinMode(D8, OUTPUT);

  pinMode(BUTTON,INPUT_PULLUP);  // internal pull-up resistor
  //attachInterrupt (digitalPinToInterrupt (BUTTON), ledStrip.changeEffect, CHANGE); // pressed
  //reset();

}


void loop() { 
  for(int i = 0; i<= 18; i++){

// #1(fadeInOut)
    Serial.println(i);
    if(i != 1){
      ledStrip.setEffect(i);
    }
    ledStrip.resetEffect();
  }
}
