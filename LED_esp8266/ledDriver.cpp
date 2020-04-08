
#include "ledDriver.h"

#define NUM_LEDS    100

//#define SHORT 5
//#define LONG  13
#define SHORT 14      //24 - 10 for function call
#define LONG  72

#define LED_PIN 0x8000 //D8

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
	writePixel(ledB[i]);
	writePixel(ledR[i]);
	writePixel(ledG[i]);
  }
}

void ledDriver::setPixel(int pixel, byte r, byte g,  byte b){
  ledR[pixel] = r;
  ledG[pixel] = g;
  ledB[pixel] = b;
}

void ledDriver::setAll(byte r, byte g, byte b){
  for(int pixel = NUM_LEDS-1; pixel >= 0; pixel--){
	ledR[pixel] = r;
	ledG[pixel] = g;
	ledB[pixel] = b;
  } 
}


void ledDriver::writePixel(byte Color){
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