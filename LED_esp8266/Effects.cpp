
#include "Effects.h"
#include <EEPROM.h>

#define Num_OF_EFFECTS 18

  effect::effect(int _numLeds, int _ledPin){
    this->numLeds = _numLeds;
    strip = new ledDriver(_numLeds, _ledPin);
  
  }

byte effect::setEffect(byte effect) { 

  if(effect > 18){
    effect = 0;
  }
  selectedEffect = effect;
  
  //EEPROM.get(0,selectedEffect); 
  /*
  if(selectedEffect > Num_OF_EFFECTS) { 
    selectedEffect = 0;
    EEPROM.put(0,0); 
  } 
  */
 // Serial.println("\n\nBeginning Case \n\n");
 
  switch(selectedEffect) {
    
    case 0  : {
                // RGBLoop - no parameters
                RGBLoop();
                break;
              }

    case 1  : {
                // FadeInOut - Color (red, green. blue)
               // Serial.println("inside Case 1");
                fadeInOut(0xff, 0x00, 0x00); // red
                fadeInOut(0xff, 0xff, 0xff); // white 
                fadeInOut(0x00, 0x00, 0xff); // blue
                break;
              }
              
    case 2  : {
                // Strobe - Color (red, green, blue), number of flashes, flash speed, end pause
                strobe(0xff, 0xff, 0xff, 10, 50, 1000);
                break;
              }

    case 3  : {
                // HalloweenEyes - Color (red, green, blue), Size of eye, space between eyes, fade (true/false), steps, fade delay, end pause
                halloweenEyes(0xff, 0x00, 0x00, 
                              1, 4, 
                              true, random(5,50), random(50,150), 
                              random(1000, 10000));
                halloweenEyes(0xff, 0x00, 0x00, 
                              1, 4, 
                              true, random(5,50), random(50,150), 
                              random(1000, 10000));
                break;
              }
              
    case 4  : {
                // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
                cylonBounce(0xff, 0x00, 0x00, 4, 10, 50);
                break;
              }
              
    case 5  : {
                // NewKITT - Color (red, green, blue), eye size, speed delay, end pause
                newKITT(0xff, 0x00, 0x00, 8, 10, 50);
                break;
              }
              
    case 6  : {
                // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false) 
                twinkle(0xff, 0x00, 0x00, numLeds, 100, false);
                twinkle(0x00, 0x00, 0x00, numLeds, 100, false);
                break;
              }
              
    case 7  : { 
                // TwinkleRandom - twinkle count, speed delay, only one (true/false)
                twinkleRandom(numLeds*2, 100, false);
                break;
              }
              
    case 8  : {
                // Sparkle - Color (red, green, blue), speed delay, count
                sparkle(0xff, 0xff, 0xff, 10, 2);
                break;
              }
               
    case 9  : { 
                // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay, count
                snowSparkle(0x5A, 0x5A, 0x5A, 20, random(100,1000), 2);
                break;
              }
              
    case 10 : {
                // Running Lights - Color (red, green, blue), wave dealy
                runningLights(0xff,0x00,0x00, 50);  // red
                runningLights(0xff,0xff,0xff, 50);  // white
                runningLights(0x00,0x00,0xff, 50);  // blue
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
                fire(55,120,15, numLeds);
                break;
              }


                // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
                // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
                // CAUTION: If set to continuous then this effect will never stop!!! 

    case 16 : {
                // mimic BouncingBalls
                byte onecolor[1][3] = { {0xff, 0x00, 0x00} };
                bouncingColoredBalls(1, onecolor, false);
                break;
              }

    case 17 : {
                // multiple colored balls
                byte colors[3][3] = { {0xff, 0x00, 0x00}, 
									  {0xff, 0xff, 0xff}, 
									  {0x00, 0x00, 0xff} };
                bouncingColoredBalls(3, colors, false);
                break;
              }

    case 18 : {
                // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay 
                meteorRain(0xff,0xff,0xff,10, 64, true, 30);
                break;
              }
  }
 // Serial.println("\n\nend\n\n");
  return selectedEffect;
}

byte effect::getEffect(){
return selectedEffect;
}

void effect::changeEffect() {
  if (digitalRead (BUTTON) == HIGH) {
    selectedEffect++;
    EEPROM.put(0, selectedEffect);
    //asm volatile ("  jmp 0"); //software reset
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
        case 0: strip->setAll(k,0,0); break;
        case 1: strip->setAll(0,k,0); break;
        case 2: strip->setAll(0,0,k); break;
      }
      strip->showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: strip->setAll(k,0,0); break;
        case 1: strip->setAll(0,k,0); break;
        case 2: strip->setAll(0,0,k); break;
      }
      strip->showStrip();
      delay(3);
    }
  }
}

void effect::fadeInOut(byte red, byte green, byte blue){
  byte r, g, b;
      
  for(byte k = 0; k < 255; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    strip->setAll(r,g,b);
    strip->showStrip();
    delay(1);
  }
     
  for(byte k = 255; k > 0; k=k-1) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    strip->setAll(r,g,b);
    strip->showStrip();
    delay(1);
  }
}

void effect::strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    strip->setAll(red,green,blue);
    strip->showStrip();
    delay(FlashDelay);
    strip->setAll(0,0,0);
    strip->showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void effect::halloweenEyes(byte red, byte green, byte blue, 
                   int EyeWidth, int EyeSpace, 
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause){
  randomSeed(analogRead(0));
  
  int i;
  int StartPoint  = random( 0, numLeds - (2*EyeWidth) - EyeSpace );
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;
  
  for(i = 0; i < EyeWidth; i++) {
    strip->setPixel(StartPoint + i, red, green, blue);
    strip->setPixel(Start2ndEye + i, red, green, blue);
  }
  
  strip->showStrip();
  
  if(Fade==true) {
    float r, g, b;
  
    for(int j = Steps; j >= 0; j--) {
      r = j*(red/Steps);
      g = j*(green/Steps);
      b = j*(blue/Steps);
      
      for(i = 0; i < EyeWidth; i++) {
        strip->setPixel(StartPoint + i, r, g, b);
        strip->setPixel(Start2ndEye + i, r, g, b);
      }
      
      strip->showStrip();
      delay(FadeDelay);
    }
  }
  
  strip->setAll(0,0,0); // Set all black
  
  delay(EndPause);
}

void effect::cylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < numLeds-EyeSize-2; i++) {
    strip->setAll(0,0,0);
    strip->setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip->setPixel(i+j, red, green, blue); 
    }
    strip->setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip->showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = numLeds-EyeSize-2; i > 0; i--) {
    strip->setAll(0,0,0);
    strip->setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip->setPixel(i+j, red, green, blue); 
    }
    strip->setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip->showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}

void effect::newKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
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
void effect::centerToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i =((numLeds-EyeSize)/2); i>=0; i--) {
    strip->setAll(0,0,0);
    
    strip->setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip->setPixel(i+j, red, green, blue); 
    }
    strip->setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    strip->setPixel(numLeds-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip->setPixel(numLeds-i-j, red, green, blue); 
    }
    strip->setPixel(numLeds-i-EyeSize-1, red/10, green/10, blue/10);
    
    strip->showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void effect::outsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((numLeds-EyeSize)/2); i++) {
    strip->setAll(0,0,0);
    
    strip->setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip->setPixel(i+j, red, green, blue); 
    }
    strip->setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    strip->setPixel(numLeds-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip->setPixel(numLeds-i-j, red, green, blue); 
    }
    strip->setPixel(numLeds-i-EyeSize-1, red/10, green/10, blue/10);
    
    strip->showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void effect::leftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i < numLeds-EyeSize-2; i++) {
    strip->setAll(0,0,0);
    strip->setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip->setPixel(i+j, red, green, blue); 
    }
    strip->setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip->showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void effect::rightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = numLeds-EyeSize-2; i > 0; i--) {
    strip->setAll(0,0,0);
    strip->setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip->setPixel(i+j, red, green, blue); 
    }
    strip->setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip->showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void effect::twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  strip->setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     strip->setPixel(random(numLeds),red,green,blue);
     strip->showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       strip->setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void effect::twinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  strip->setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     strip->setPixel(random(numLeds),random(0,255),random(0,255),random(0,255));
     strip->showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       strip->setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void effect::sparkle(byte red, byte green, byte blue, int SpeedDelay, int count) {

  for(int i = 0; i < count; i++){
    int Pixel = random(numLeds);
    strip->setPixel(Pixel,red,green,blue);
    strip->showStrip();
    delay(SpeedDelay);
    strip->setPixel(Pixel,0,0,0);
  }
}

void effect::snowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay, int count) {
  strip->setAll(red,green,blue);
  
  for(int i = 0; i < count; i++){
    int Pixel = random(numLeds);
    
    strip->setPixel(Pixel,0xff,0xff,0xff);
    strip->showStrip();
    delay(SparkleDelay);
    strip->setPixel(Pixel,red,green,blue);
    strip->showStrip();
    delay(SpeedDelay);
  }
  
}

void effect::runningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<numLeds*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<numLeds; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //strip->setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        strip->setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      strip->showStrip();
      delay(WaveDelay);
  }
}

void effect::colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<numLeds; i++) {
      strip->setPixel(i, red, green, blue);
      strip->showStrip();
      delay(SpeedDelay);
  }
}

void effect::rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< numLeds; i++) {
      c = wheel(((i * 256 / numLeds) + j) & 255);
      strip->setPixel(i, *c, *(c+1), *(c+2));
    }
    strip->showStrip();
    delay(SpeedDelay);
  }
}

// used by rainbowCycle and theaterChaseRainbow
byte* effect::wheel(byte WheelPos) {
  static byte c[3];
  
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

void effect::theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < numLeds; i=i+3) {
        strip->setPixel(i+q, red, green, blue);    //turn every third pixel on
      }
      strip->showStrip();
     
      delay(SpeedDelay);
     
      for (int i=0; i < numLeds; i=i+3) {
        strip->setPixel(i+q, 0,0,0);        //turn every third pixel off
      }
    }
  }
}

void effect::theaterChaseRainbow(int SpeedDelay) {
  byte *c;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < numLeds; i=i+3) {
          c = wheel( (i+j) % 255);
          strip->setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        strip->showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < numLeds; i=i+3) {
          strip->setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

void effect::fire(int Cooling, int Sparking, int SpeedDelay, int count) {

for(int i = 0; i < count; i++){

  static byte* heat = new byte[numLeds];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < numLeds; i++) {
    cooldown = random(0, ((Cooling * 10) / numLeds) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= numLeds - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < numLeds; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  strip->showStrip();
  delay(SpeedDelay);
  }
}

void effect::setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    strip->setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    strip->setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    strip->setPixel(Pixel, heatramp, 0, 0);
  }
}

void effect::bouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous) {
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
      Position[i] = round( Height[i] * (numLeds - 1) / StartHeight);
    }
    ballsStillBouncing = false; // assume no balls bouncing
    for (int i = 0 ; i < BallCount ; i++) {
      strip->setPixel(Position[i],colors[i][0],colors[i][1],colors[i][2]);
      if ( ballBouncing[i] ) {
        ballsStillBouncing = true;
      }
    }
    strip->showStrip();
    strip->setAll(0,0,0);
    delay(1);//added delay to keep from crashing.
  }
}

void effect::meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  strip->setAll(0,0,0);
  
  for(int i = 0; i < numLeds+numLeds; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<numLeds; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <numLeds) && (i-j>=0) ) {
        strip->setPixel(i-j, red, green, blue);
      } 
    }
   
    strip->showStrip();
    delay(SpeedDelay);
  }
}

// used by meteorrain
void effect::fadeToBlack(int pixel, byte fadeValue) {
    uint32_t oldColor;
    byte r, g, b;
    int value;
    
    oldColor = strip->getPixel(pixel);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip->setPixel(pixel, r,g,b);
}

void effect::resetEffect(){
  strip->reset();
}
void effect::setAll(byte r, byte g, byte b){
  strip->setAll(r,g,b);
}