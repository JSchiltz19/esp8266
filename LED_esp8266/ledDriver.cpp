
#include "ledDriver.h"


//#define SHORT 5
//#define LONG  13
#define SHORT 14      //24 - 10 for function call
#define LONG  72

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
LED_PIN = GPIO15;
D9 = GPIO3;
D10 = GPIO1;

PERIPHS_IO_MUX_GPIO0_U,   /* 0 - D3 
PERIPHS_IO_MUX_U0TXD_U,   /* 1 - uart 
PERIPHS_IO_MUX_GPIO2_U,   /* 2 - D4 
PERIPHS_IO_MUX_U0RXD_U,   /* 3 - uart 
PERIPHS_IO_MUX_GPIO4_U,   /* 4 - D2 
PERIPHS_IO_MUX_GPIO5_U,   /* 5 - D1 
Z, /* 6 
Z, /* 7 
Z, /* 8 
PERIPHS_IO_MUX_SD_DATA2_U, /* 9 - D11 (SD2) 
PERIPHS_IO_MUX_SD_DATA3_U, /* 10 - D12 (SD3) 
Z, /* 11 
PERIPHS_IO_MUX_MTDI_U,    /* 12 - D6 
PERIPHS_IO_MUX_MTCK_U,    /* 13 - D7 
PERIPHS_IO_MUX_MTMS_U,    /* 14 - D5 
PERIPHS_IO_MUX_MTDO_U     /* 15 - D8
*/ //////////////////////////////////////////////////9/////////////////////////////////////////////////
  
  /*
  //timing code  
  static inline int32_t asm_ccount(void) {
    int32_t r;
    asm volatile ("rsr %0, ccount" : "=r"(r));
    return r;
  }
  int32_t count_now;
  uint32_t total_time_to_run;
  int32_t btime, etime;
  btime = asm_ccount();
  etime = asm_ccount();
  Serial.print("Number of Ticks = ");
  total_time_to_run =((uint32_t)(etime - btime));
  Serial.println(total_time_to_run);
  delay(100);
  // 1 tick = 0.0125 us
  */
  const byte PROGMEM gamma8[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
    2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
    5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
    115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
    144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
    177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
    215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 
  };

#define delay24Ticks ({\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
  asm volatile ("nop");\
})

#define delay72Ticks ({\
  delay24Ticks;\
  delay24Ticks;\
  delay24Ticks;\
})

//#define ARRAY_LENGTH NUM_LEDS*3
//byte ledR[NUM_LEDS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128};  //store all 3 bits rgb 
//byte ledG[NUM_LEDS] = {128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,1280,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  
  
  ledDriver::ledDriver(int numLeds){
    //this->numLeds = numLeds;
    if(numLeds > 1000){
      numLeds = 100;
      }
    ledR = new byte[numLeds];
    ledG = new byte[numLeds];
    ledB = new byte[numLeds];
}

 ledDriver::~ledDriver(){
  delete[] ledR;
  delete[] ledG;
  delete[] ledB;
  ledR = 0;
  ledG = 0;
  ledB = 0;
 }

void ledDriver::resetLEDArray(){ 
  for(uint32_t i = 0; i < NUM_LEDS; i++){
	ledB[i] = 0;
	ledR[i] = 0;
	ledB[i] = 0;
  }
}

void ledDriver::showStrip(){
  //reset();
  for(int i = NUM_LEDS-1; i >= 0; i--){
	writeStrip(ledB[i]);
	writeStrip(ledR[i]);
	writeStrip(ledG[i]);
  }
}

void ledDriver::setPixel(int pixel, byte r, byte g,  byte b){
  ledR[pixel] = pgm_read_byte(&gamma8[r]);
  ledG[pixel] = pgm_read_byte(&gamma8[g]);
  ledB[pixel] = pgm_read_byte(&gamma8[b]);
}

uint32_t ledDriver::getPixel(int pixel){
  uint32_t pixelColor = ledR[pixel];
  pixelColor << 8;
  pixelColor = pixelColor | ledG[pixel];
  pixelColor << 8;
  pixelColor = pixelColor | ledB[pixel];

  return pixelColor;
}

void ledDriver::setAll(byte r, byte g, byte b){
  for(int pixel = NUM_LEDS-1; pixel >= 0; pixel--){
	ledR[pixel] = r;
	ledG[pixel] = g;
	ledB[pixel] = b;
  } 
}


void ledDriver::writeStrip(byte Color){
  noInterrupts();                         // disable interrupts to maintain timing
  for(int i = 7; i >= 0; i--){            // loop through byte
	bool temp = bitRead(Color,i);         // get MSB and left shift by 1

	if(temp == 0){
	  // 0 code
	  
	  GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, LED_PIN);      // set pin 5 HIGH and all others LOW   2 Ticks
	  
	  delay24Ticks;      //24 tics = .3 us
	  
	  GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, LED_PIN);      // set all pins LOW   2 Ticks

	  delay72Ticks;   //72 tics = .9 us
 
	}
	else{
	  // 1 code
	  //GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, GPIO_REG_READ(GPIO_OUT_ADDRESS) | 0x0800); use if other pins are being used 
	  
	  GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, LED_PIN);    // can use this instead of directly putting in hex 1 << GPIO_pin number
	  
	  delay72Ticks; //72 tics = .9 us
	  
	  GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, LED_PIN);

	  delay24Ticks;; //24 tics = .3 us
	}
  }
  interrupts();                           // renable interrupts 

}


void ledDriver::reset(){
	// reset code
	GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, GPIO_REG_READ(GPIO_OUT_ADDRESS) | LED_PIN); //only sets pin 5 LOW
	//delayMicroseconds(80);      //has 51 tick overhead
	delayMicroseconds(79);      //has 20 ticks behind
}