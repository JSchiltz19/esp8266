
#ifndef EFFECTS_H
#define EFFECTS_H
#include "ledDriver.h"
#define BUTTON 2
//TODO: normalize #defines among files

//TODO: set up class

class effect{
  public:
  
   ledDriver strip = ledDriver(100);
   
    effect(){
    }
    
    byte setEffect(byte effect);
    void changeEffect();
    
  private:
    byte selectedEffect = 0;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void RGBLoop();
    void fadeInOut(byte red, byte green, byte blue);
    void strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause);
    void halloweenEyes(byte red, byte green, byte blue, 
												int EyeWidth, int EyeSpace, 
												boolean Fade, int Steps, int FadeDelay,
												int EndPause);
    void cylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void newKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void centerToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void outsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void leftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void rightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne);
    void twinkleRandom(int Count, int SpeedDelay, boolean OnlyOne);
    void sparkle(byte red, byte green, byte blue, int SpeedDelay);
    void snowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay);
    void runningLights(byte red, byte green, byte blue, int WaveDelay);
    void colorWipe(byte red, byte green, byte blue, int SpeedDelay);
    void rainbowCycle(int SpeedDelay);
    byte * wheel(byte WheelPos);
    void theaterChase(byte red, byte green, byte blue, int SpeedDelay);
    void theaterChaseRainbow(int SpeedDelay);
    void fire(int Cooling, int Sparking, int SpeedDelay);
    void setPixelHeatColor (int Pixel, byte temperature);
    void bouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous);
    void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);
    void fadeToBlack(int ledNo, byte fadeValue);
};

#endif