/*
  hl_ssd1306.h

  Written by F. Heil, March 15th, 2023
*/
#ifndef HL_SSD1306_h
#define HL_SSD1306_h

#include "Arduino.h"
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "hl_state3034.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 //4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

class HL_SSD1306 : public HL_State_3034
{
  public:
    HL_SSD1306 (long);

    void Update();
    void Init();
    /*    void Clear(void);*/
    void scrollMsg(void);
    void startScrollLeftMsg(void);
    void testscrolltext(void);
    void testdrawbitmap(void);
    void testanimate();
    void testanimate(const uint8_t *, uint8_t, uint8_t);
    uint8_t getRainbowState();
    void resetPosX(void);


  private:
    const unsigned char /*PROGMEM*/ logo_bmp[32] =
    { 0b00000000, 0b11000000,
      0b00000001, 0b11000000,
      0b00000001, 0b11000000,
      0b00000011, 0b11100000,
      0b11110011, 0b11100000,
      0b11111110, 0b11111000,
      0b01111110, 0b11111111,
      0b00110011, 0b10011111,
      0b00011111, 0b11111100,
      0b00001101, 0b01110000,
      0b00011011, 0b10100000,
      0b00111111, 0b11100000,
      0b00111111, 0b11110000,
      0b01111100, 0b11110000,
      0b01110000, 0b01110000,
      0b00000000, 0b00110000
    };

    // Generally, you should use "unsigned long" for variables that hold time
    // The value will quickly become too large for an int to store
    unsigned long previousMillis = 0;  // will store last time LED was updated

    uint8_t _msg_idx;
    int8_t icons[NUMFLAKES][3];
    int16_t _posX, _minX;

    Adafruit_SSD1306 display;

    void setPosX(int16_t);
    int16_t getPosX(void);
    void updatePosX(void);
    void setMinX(int16_t);
    int16_t getMinX(void);
};

#endif //#ifndef HL_SSD1306_h
