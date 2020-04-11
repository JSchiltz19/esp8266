
#ifndef EFFECTS_H
#define EFFECTS_H
#include "ledDriver.h"

//TODO: normalize #defines among files

//TODO: set up class


class effect{
  public:
    effect(){

      ledDriver strip;
      
      
    }
    
    uint8_t setEffect(uint8_t effect);
    void changeEffect();
    
  private:
    uint8_t selectedEffect = 0;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void RGBLoop();
    void fadeInOut(uint8_t red, uint8_t green, uint8_t blue);
    void strobe(uint8_t red, uint8_t green, uint8_t blue, int StrobeCount, int FlashDelay, int EndPause);
    void halloweenEyes(uint8_t red, uint8_t green, uint8_t blue, 
												int EyeWidth, int EyeSpace, 
												boolean Fade, int Steps, int FadeDelay,
												int EndPause);
    void cylonBounce(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void newKITT(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void centerToOutside(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void outsideToCenter(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void leftToRight(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void rightToLeft(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void twinkle(uint8_t red, uint8_t green, uint8_t blue, int Count, int SpeedDelay, boolean OnlyOne);
    void twinkleRandom(int Count, int SpeedDelay, boolean OnlyOne);
    void sparkle(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay);
    void snowSparkle(uint8_t red, uint8_t green, uint8_t blue, int SparkleDelay, int SpeedDelay);
    void runningLights(uint8_t red, uint8_t green, uint8_t blue, int WaveDelay);
    void colorWipe(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay);
    void rainbowCycle(int SpeedDelay);
    uint8_t wheel(uint8_t WheelPos);
    void theaterChase(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay);
    void theaterChaseRainbow(int SpeedDelay);
    void fire(int Cooling, int Sparking, int SpeedDelay);
    void setPixelHeatColor (int Pixel, uint8_t temperature);
    void bouncingColoredBalls(int BallCount, uint8_t colors[][3], boolean continuous);
    void meteorRain(uint8_t red, uint8_t green, uint8_t blue, uint8_t meteorSize, uint8_t meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);
    void fadeToBlack(int ledNo, uint8_t fadeValue);
};

#endif