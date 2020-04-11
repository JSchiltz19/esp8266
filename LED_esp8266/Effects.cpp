
#include "Effects.h"

#define Num_OF_EFFECTS 18

uint8_t effect::setEffect(uint8_t effect) { 

//TODO: move to .cpp
//TODO: put inside of some loop
  selectedEffect = effect;
  
  EEPROM.get(0,selectedEffect); 
  
  if(selectedEffect > Num_OF_EFFECTS) { 
    selectedEffect = 0;
    EEPROM.put(0,0); 
  } 
  switch(selectedEffect) {
    
    case 0  : {
                // RGBLoop - no parameters
                RGBLoop();
                break;
              }

    case 1  : {
                // FadeInOut - Color (red, white. blue)
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
                uint8_t onecolor[1][3] = { {0xff, 0x00, 0x00} };
                BouncingColoredBalls(1, onecolor, false);
                break;
              }

    case 17 : {
                // multiple colored balls
                uint8_t colors[3][3] = { {0xff, 0x00, 0x00}, 
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
  return selectedEffect;
}

void effect::changeEffect() {
  if (digitalRead (BUTTON) == HIGH) {
    selectedEffect++;
    EEPROM.put(0, selectedEffect);
    asm volatile ("  jmp 0");
  }
}

// *************************
// ** LEDEffect Functions **
// *************************

void effect::RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    // Fade IN
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

void effect::fadeInOut(uint8_t red, uint8_t green, uint8_t blue){
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
}

void effect::strobe(uint8_t red, uint8_t green, uint8_t blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void effect::halloweenEyes(uint8_t red, uint8_t green, uint8_t blue, 
                   int EyeWidth, int EyeSpace, 
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause){
  randomSeed(analogRead(0));
  
  int i;
  int StartPoint  = random( 0, NUM_LEDS - (2*EyeWidth) - EyeSpace );
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;
  
  for(i = 0; i < EyeWidth; i++) {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
  }
  
  showStrip();
  
  if(Fade==true) {
    float r, g, b;
  
    for(int j = Steps; j >= 0; j--) {
      r = j*(red/Steps);
      g = j*(green/Steps);
      b = j*(blue/Steps);
      
      for(i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }
      
      showStrip();
      delay(FadeDelay);
    }
  }
  
  setAll(0,0,0); // Set all black
  
  delay(EndPause);
}

void effect::cylonBounce(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}

void effect::newKITT(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  rightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  leftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  outsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  centerToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  leftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  rightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  outsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  centerToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

// used by NewKITT
void effect::centerToOutside(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i =((NUM_LEDS-EyeSize)/2); i>=0; i--) {
    setAll(0,0,0);
    
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue); 
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
    
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void effect::outsideToCenter(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2); i++) {
    setAll(0,0,0);
    
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue); 
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
    
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void effect::leftToRight(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void effect::rightToLeft(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void effect::twinkle(uint8_t red, uint8_t green, uint8_t blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),red,green,blue);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void effect::twinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void effect::sparkle(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}

void effect::snowSparkle(uint8_t red, uint8_t green, uint8_t blue, int SparkleDelay, int SpeedDelay) {
  setAll(red,green,blue);
  
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,0xff,0xff,0xff);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
}

void effect::runningLights(uint8_t red, uint8_t green, uint8_t blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
  }
}

void effect::colorWipe(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      setPixel(i, red, green, blue);
      showStrip();
      delay(SpeedDelay);
  }
}

void effect::rainbowCycle(int SpeedDelay) {
  uint8_t *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

// used by rainbowCycle and theaterChaseRainbow
uint8_t effect::wheel(uint8_t WheelPos) {
  static uint8_t c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void effect::theaterChase(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, red, green, blue);    //turn every third pixel on
      }
      showStrip();
     
      delay(SpeedDelay);
     
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, 0,0,0);        //turn every third pixel off
      }
    }
  }
}

void effect::theaterChaseRainbow(int SpeedDelay) {
  uint8_t *c;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NUM_LEDS; i=i+3) {
          c = Wheel( (i+j) % 255);
          setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < NUM_LEDS; i=i+3) {
          setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

void effect::fire(int Cooling, int Sparking, int SpeedDelay) {
  static uint8_t heat[NUM_LEDS];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void effect::setPixelHeatColor (int Pixel, uint8_t temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  uint8_t t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  uint8_t heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void effect::bouncingColoredBalls(int BallCount, uint8_t colors[][3], boolean continuous) {
  float Gravity = -9.81;
  int StartHeight = 1;
  
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  boolean ballBouncing[BallCount];
  boolean ballsStillBouncing = true;
  
  for (int i = 0 ; i < BallCount ; i++) {   
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0; 
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
    ballBouncing[i]=true; 
  }

  while (ballsStillBouncing) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
  
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
  
        if ( ImpactVelocity[i] < 0.01 ) {
          if (continuous) {
            ImpactVelocity[i] = ImpactVelocityStart;
          } else {
            ballBouncing[i]=false;
          }
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    ballsStillBouncing = false; // assume no balls bouncing
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],colors[i][0],colors[i][1],colors[i][2]);
      if ( ballBouncing[i] ) {
        ballsStillBouncing = true;
      }
    }
    
    showStrip();
    setAll(0,0,0);
  }
}

void effect::meteorRain(uint8_t red, uint8_t green, uint8_t blue, uint8_t meteorSize, uint8_t meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}

// used by meteorrain
void effect::fadeToBlack(int pixel, uint8_t fadeValue) {
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = getPixel(pixel);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    setPixelColor(pixel, r,g,b);
}