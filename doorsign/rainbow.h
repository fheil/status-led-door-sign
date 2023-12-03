/*
  rainbow.h

  Written by F. Heil, March 14th, 2023
*/
#ifndef ADAFRUIT_NEOPIXEL_RAINBOW_h
#define ADAFRUIT_NEOPIXEL_RAINBOW_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "hl_state3034.h"

class Rainbow : public HL_State_3034
{
  public:
    Rainbow (long x);
    void Update();
    void SetPixelColor (uint8_t r, uint8_t g, uint8_t b);
    void SetPixelColor (uint32_t c);
    void SetPixelColor ();
    void AllOff();


  private:
    uint32_t Wheel(byte WheelPos);
    // Generally, you should use "unsigned long" for variables that hold time
    // The value will quickly become too large for an int to store
    unsigned long previousMillis = 0;  // will store last time LED was updated

    uint16_t j = 0;

    Adafruit_NeoPixel strip;
};

#endif //#ifndef ADAFRUIT_NEOPIXEL_RAINBOW_h
