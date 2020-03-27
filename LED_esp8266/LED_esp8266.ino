

#define LED_PIN     7
#define NUM_LEDS    100

//#define SHORT 5
//#define LONG  13
#define SHORT 24
#define LONG  72


//#define ARRAY_LENGTH NUM_LEDS*3
//byte ledR[NUM_LEDS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128};  //store all 3 bits rgb 
//byte ledG[NUM_LEDS] = {128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,1280,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
GPIO code
D0 = GPIO16;
D1 = GPIO5;
D2 = GPIO4;
D3 = GPIO0;
D4 = GPIO2;
D5 = GPIO14;
D6 = GPIO12;
D7 = GPIO13;
D8 = GPIO15;
D9 = GPIO3;
D10 = GPIO1;
*/ ///////////////////////////////////////////////////////////////////////////////////////////////////


byte ledR[NUM_LEDS];
byte ledG[NUM_LEDS];
byte ledB[NUM_LEDS];
byte data[NUM_LEDS];
void setup() {
Serial.begin(9600);       //setup serial for debugging
//DDRD = DDRD | B00010000;  // sets pin 5 to output and all the rest to input
PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12); 

//resetLEDArray();
resetRGB();
}


void loop() { 
  cycleColors(1,15,128);
  
  FadeLED(2,5,128);
  
  crossFade(1,15,128);

}


void resetLEDArray(){
  for(uint32_t i = 0; i < NUM_LEDS; i++){
    ledB[i] = 0;
    ledR[i] = 0;
    ledB[i] = 0;
  }
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

void updateLEDs(){
  //resetRGB();
  for(int i = NUM_LEDS; i >= 0; i--){
  writeColorRGB(ledB[i]);
  writeColorRGB(ledR[i]);
  writeColorRGB(ledG[i]);
  }
}

static inline int32_t asm_ccount(void) {
    int32_t r;
    asm volatile ("rsr %0, ccount" : "=r"(r));
    return r;
}

void writeColorRGB(byte Color){
  int32_t count_now
  noInterrupts();                         // disable interrupts to maintain timing
  for(int i = 7; i >= 0; i--){            // loop through byte
    bool temp = bitRead(Color,i);         // get MSB and left shift by 1

    if(temp == 0){
      // 0 code

      GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 0x0800);      // set pin 5 HIGH and all others LOW
      
      count_now = asm_ccount();
      while( uint32_t(asm_ccount() - count_now) - SHORT);  //24 tics = .3 us
      
      GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 0x0800);      // set pin 5 LOW
     
      count_now = asm_ccount();
      while( uint32_t(asm_ccount() - count_now) - LONG);   //72 tics = .9 us
    }
    else{
      // 1 code
      
      //GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, GPIO_REG_READ(GPIO_OUT_ADDRESS) | 0x0800); use if other pins are being used 
      GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 0x0800);    // can use this instead of directly putting in hex 1 << GPIO_pin number
      
      count_now = asm_ccount();
      while( uint32_t(asm_ccount() - count_now) - LONG); //72 tics = .9 us
      
      GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 0x0800);
      
      count_now = asm_ccount();
      while( uint32_t(asm_ccount() - count_now) - SHORT); //24 tics = .3 us
    }
  }
  interrupts();                           // renable interrupts 
}

void resetRGB(){
// reset code
GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, GPIO_REG_READ(GPIO_OUT_ADDRESS) | 0x0800); //only sets pin 5 LOW
delayMicroseconds(80);
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
    updateLEDs();
    delay(_delay);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    ledR[i] = 0;
    ledG[i] = 0;
    ledB[i] = _brightness;
    updateLEDs();
    delay(_delay);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    ledR[i] = 0;
    ledG[i] = _brightness;
    ledB[i] = 0;
    updateLEDs();
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
    updateLEDs();
    delay(_delay);
  }
  for(uint32_t i = _brightness; i >=1 ; i -= _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = i;
    }
    updateLEDs();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledG[j] = i;
    }
    updateLEDs();
    delay(_delay);
  }
  for(uint32_t i = _brightness; i >=1 ; i -= _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledG[j] = i;
    }
    updateLEDs();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledB[j] = i;
    }
    updateLEDs();
    delay(_delay);
  }
  for(uint32_t i = _brightness; i >=1 ; i -= _step){ 
    for (int j = 0; j < NUM_LEDS; j++) {
      ledB[j] = i;
    }
    updateLEDs();
    delay(_delay);
  }
}


void crossFade(byte _step, byte _delay, byte _brightness) {
  resetLEDArray();

  if(_step <= 0) _step = 1;
  if(_delay <= 0) _delay = 10;
  if(_brightness <= 0) _brightness = 128;

  for(uint32_t i = 0; i <= _brightness; i += _step){ //number of time I want it to fade
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = i;
      ledG[j] = _brightness - i;
      ledB[j] = 0;
    }
    updateLEDs();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){ //number of time I want it to fade
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = _brightness - i;
      ledG[j] = 0;
      ledB[j] = i;
    }
    updateLEDs();
    delay(_delay);
  }
  for(uint32_t i = 0; i <= _brightness; i += _step){ //number of time I want it to fade
    // change the values of the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
      ledR[j] = 0;
      ledG[j] = i;
      ledB[j] = _brightness - i;
    }
    updateLEDs();
    delay(_delay);
  }
}
