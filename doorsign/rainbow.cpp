#include "Arduino.h"
#include "doorsign.h"
#include "rainbow.h"

#if defined(ESP8266) || defined(ESP8266_WEMOS_D1MINIPRO)
#define PIN D4
#endif // #if defined(ESP8266) || defined(ESP8266_WEMOS_D1MINIPRO) 

#if defined(ESP32) || defined(ESP32C3_DEV)
#define PIN 7
#endif // #if defined(ESP32) || defined(ESP32C3_DEV) 

Rainbow::Rainbow (long n)
{
  this->setInterval(n);

  strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800);

  strip.begin();
  strip.setBrightness(50);
#if defined(ESP8266) || defined(ESP8266_WEMOS_D1MINIPRO)
  strip.show(); // Initialize all pixels to 'off'
#endif // #if defined(ESP8266) || defined(ESP8266_WEMOS_D1MINIPRO)
}

void Rainbow::Update()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= this->getInterval()) {
    // save the last time update
    previousMillis = currentMillis;

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    (j++) & 255;
  }
}

void Rainbow::SetPixelColor (uint8_t r, uint8_t g, uint8_t b)
{
  AllOff();
  strip.setPixelColor(strip.numPixels() - (this->getState() + 1), strip.Color(r, g, b));
  strip.show();
}

void Rainbow::SetPixelColor (uint32_t c)
{
  AllOff();
  strip.setPixelColor(strip.numPixels() - (this->getState() + 1), c);
  strip.show();
}

void Rainbow::SetPixelColor ()
{
  AllOff();
  strip.setPixelColor(strip.numPixels() - (this->getState() + 1), msg_color[this->getState()]);
  strip.show();
}
// Fill the dots one after the other with a color
void Rainbow::AllOff() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
    strip.show();
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Rainbow::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
