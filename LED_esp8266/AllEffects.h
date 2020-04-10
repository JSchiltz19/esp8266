
#include "AllEffects.h"

//TODO: normalize #defines among files
#define NUM_LEDS 60 
#define PIN 5 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define BUTTON 2
byte selectedEffect=0;

//TODO: set up class

void setup()
{
  //TODO: turn into constructor
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON,INPUT_PULLUP);  // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // pressed
}

// *** REPLACE FROM HERE ***
void offline() { 
//TODO: move to .cpp
//TODO: put inside of some loop
  EEPROM.get(0,selectedEffect); 
  
  if(selectedEffect>18) { 
    selectedEffect=0;
    EEPROM.put(0,0); 
  } 
  
  switch(selectedEffect) {
    
    case 0  : {
                // RGBLoop - no parameters
                RGBLoop();
                break;
              }

    case 1  : {
                // FadeInOut - Color (red, green. blue)
                FadeInOut(0xff, 0x00, 0x00); // red
                FadeInOut(0xff, 0xff, 0xff); // white 
                FadeInOut(0x00, 0x00, 0xff); // blue
                break;
              }
              
    case 2  : {
                // Strobe - Color (red, green, blue), number of flashes, flash speed, end pause
                Strobe(0xff, 0xff, 0xff, 10, 50, 1000);
                break;
              }

    case 3  : {
                // HalloweenEyes - Color (red, green, blue), Size of eye, space between eyes, fade (true/false), steps, fade delay, end pause
                HalloweenEyes(0xff, 0x00, 0x00, 
                              1, 4, 
                              true, random(5,50), random(50,150), 
                              random(1000, 10000));
                HalloweenEyes(0xff, 0x00, 0x00, 
                              1, 4, 
                              true, random(5,50), random(50,150), 
                              random(1000, 10000));
                break;
              }
              
    case 4  : {
                // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
                CylonBounce(0xff, 0x00, 0x00, 4, 10, 50);
                break;
              }
              
    case 5  : {
                // NewKITT - Color (red, green, blue), eye size, speed delay, end pause
                NewKITT(0xff, 0x00, 0x00, 8, 10, 50);
                break;
              }
              
    case 6  : {
                // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false) 
                Twinkle(0xff, 0x00, 0x00, 10, 100, false);
                break;
              }
              
    case 7  : { 
                // TwinkleRandom - twinkle count, speed delay, only one (true/false)
                TwinkleRandom(20, 100, false);
                break;
              }
              
    case 8  : {
                // Sparkle - Color (red, green, blue), speed delay
                Sparkle(0xff, 0xff, 0xff, 0);
                break;
              }
               
    case 9  : {
                // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
                SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));
                break;
              }
              
    case 10 : {
                // Running Lights - Color (red, green, blue), wave dealy
                RunningLights(0xff,0x00,0x00, 50);  // red
                RunningLights(0xff,0xff,0xff, 50);  // white
                RunningLights(0x00,0x00,0xff, 50);  // blue
                break;
              }
              
    case 11 : {
                // colorWipe - Color (red, green, blue), speed delay
                colorWipe(0x00,0xff,0x00, 50);
                colorWipe(0x00,0x00,0x00, 50);
                break;
              }

    case 12 : {
                // rainbowCycle - speed delay
                rainbowCycle(20);
                break;
              }

    case 13 : {
                // theatherChase - Color (red, green, blue), speed delay
                theaterChase(0xff,0,0,50);
                break;
              }

    case 14 : {
                // theaterChaseRainbow - Speed delay
                theaterChaseRainbow(50);
                break;
              }

    case 15 : {
                // Fire - Cooling rate, Sparking rate, speed delay
                Fire(55,120,15);
                break;
              }


              // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
              // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
              // CAUTION: If set to continuous then this effect will never stop!!! 
              
    case 16 : {
                // mimic BouncingBalls
                byte onecolor[1][3] = { {0xff, 0x00, 0x00} };
                BouncingColoredBalls(1, onecolor, false);
                break;
              }

    case 17 : {
                // multiple colored balls
                byte colors[3][3] = { {0xff, 0x00, 0x00}, 
                                      {0xff, 0xff, 0xff}, 
                                      {0x00, 0x00, 0xff} };
                BouncingColoredBalls(3, colors, false);
                break;
              }

    case 18 : {
                // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay 
                meteorRain(0xff,0xff,0xff,10, 64, true, 30);
                break;
              }
  }
}

void changeEffect() {
  if (digitalRead (BUTTON) == HIGH) {
    selectedEffect++;
    EEPROM.put(0, selectedEffect);
    asm volatile ("  jmp 0");
  }
}


