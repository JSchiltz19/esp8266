
#include "ledDriver.h"

byte data[NUM_LEDS];

void setup() {
  Serial.begin(115200);

  //PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U,FUNC_GPIO15); 
  pinMode(D8, OUTPUT);
  reset();

}


void loop() { 

byte colors[3][3] = { {0xff, 0,    0},
                      {0xff, 0xff, 0xff},
                      {0   , 0   , 0xff} 
                    };

  BouncingColoredBalls(3, colors);
  /*
  cycleColors(1,15,128);
 
  FadeLED(2,5,128);
  
  crossFade(1,15,128);
*/
}

int readSerial(){
  if(Serial){                           //make sure serial is open
    if(Serial.available() >= NUM_LEDS){ //when a full array of data is loaded read it
      while(Serial.available()){        //read untill empty
        data[NUM_LEDS - Serial.available()] = Serial.read();
      }
      if(Fletcher16(data, NUM_LEDS) == 0) return 1; // return 1 if data is usable
      else return -1;                               // return -1 if data is unusable
    }
    Serial.write(B10101010);                        // tell sender to transmit array
  }
  else return -1;                                   //return -1 to indicate no new data
}
  
uint16_t Fletcher16( uint8_t *data, int count ){
   uint16_t sum1 = 0;
   uint16_t sum2 = 0;
   int index;

   for ( index = 0; index < count; ++index ){
      sum1 = (sum1 + data[index]) % 255;
      sum2 = (sum2 + sum1) % 255;
   }

   return (sum2 << 8) | sum1;
}


void rainbow(byte _step, byte _delay, byte _brightness){

  resetLEDArray();

  if(_step <= 0) _step = 1;
  if(_delay <= 0) _delay = 10;
  if(_brightness <= 0) _brightness = 128;
  byte ledR_2[_brightness*3];
  byte ledG_2[_brightness*3];
  byte ledB_2[_brightness*3];

  for(uint32_t i = 0; i <= _brightness; i += _step){
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = i;
      ledG[j] = _brightness - i;
      ledB[j] = 0;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = _brightness - i;
      ledG[j] = 0;
      ledB[j] = i;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = 0;
      ledG[j] = i;
      ledB[j] = _brightness - i;
    }
    showStrip();
    delay(_delay);
  }


}

void cycleColors(byte _step, byte _delay, byte _brightness){
  resetLEDArray();
  
  if(_step <= 0) _step = 1;
  if(_delay <= 0) _delay = 10;
  if(_brightness <= 0) _brightness = 128;
  
  for (int i = 0; i < NUM_LEDS; i++) {
    ledR[i] = _brightness;
    ledG[i] = 0;
    ledB[i] = 0;
    showStrip();
    delay(_delay);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    ledR[i] = 0;
    ledG[i] = 0;
    ledB[i] = _brightness;
    showStrip();
    delay(_delay);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    ledR[i] = 0;
    ledG[i] = _brightness;
    ledB[i] = 0;
    showStrip();
    delay(_delay);
  }
}

void FadeLED(byte _step, byte _delay, byte _brightness){
  resetLEDArray();

  if(_step <= 0) _step = 1;
  if(_delay <= 0) _delay = 10;
  if(_brightness <= 0) _brightness = 128;

  
  for(uint32_t i = 0; i <= _brightness; i += _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = i;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = _brightness; i >=1 ; i -= _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = i;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledG[j] = i;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = _brightness; i >=1 ; i -= _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledG[j] = i;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledB[j] = i;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = _brightness; i >=1 ; i -= _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledB[j] = i;
    }
    showStrip();
    delay(_delay);
  }
}

void crossFade(byte _step, byte _delay, byte _brightness) {
  resetLEDArray();

  if(_step <= 0) _step = 1;
  if(_delay <= 0) _delay = 10;
  if(_brightness <= 0) _brightness = 128;

  for(uint32_t i = 0; i <= _brightness; i += _step){
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = i;
      ledG[j] = _brightness - i;
      ledB[j] = 0;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = _brightness - i;
      ledG[j] = 0;
      ledB[j] = i;
    }
    showStrip();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = 0;
      ledG[j] = i;
      ledB[j] = _brightness - i;
    }
    showStrip();
    delay(_delay);
  }
}

void BouncingColoredBalls(int BallCount, byte colors[][3]) {
  float Gravity = -9.81;
  int StartHeight = 1;
 
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
 
  for (int i = 0 ; i < BallCount ; i++) {  
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
 
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }
 
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],colors[i][0],colors[i][1],colors[i][2]);
    }
   
    showStrip();
    setAll(0,0,0);
  }
}