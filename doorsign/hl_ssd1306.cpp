#include "Arduino.h"
#include "doorsign.h"
#include "hl_ssd1306.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

HL_SSD1306::HL_SSD1306 (long interval)
{
  this->setInterval (interval);
  this->setState(this->getRainbowState());
}

uint8_t HL_SSD1306::getRainbowState() {
  return 6;
}

void HL_SSD1306::Init()
{
  int8_t f;

#if defined(ESP32) || defined(ESP32C3_DEV)
  Wire.setPins(10, 9);  //Pin 8 is used by internal LED
#endif // #if defined(ESP32) || defined(ESP32C3_DEV) 

  display = Adafruit_SSD1306 (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  Serial.println("\n\nConstructor called...");
  display.begin();

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 2 seconds
  display.clearDisplay();
  display.setRotation(0);

  // Initialize 'snowflake' positions
  for (f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);

  }
  resetPosX();
}

void HL_SSD1306::setPosX(int16_t posX) {
  _posX = posX;
}

int16_t HL_SSD1306::getPosX() {
  return _posX;
}

void HL_SSD1306::updatePosX() {
  _posX--;//setPosX(getPosX() - 1);// = pos_x - 1; //scroll left
  if (_posX < getMinX()) resetPosX();//(display.width();
}

void HL_SSD1306::resetPosX(void) {
  _posX = SCREEN_WIDTH;
}

void HL_SSD1306::setMinX(int16_t minX) {
  _minX = -12 * minX;
}

int16_t HL_SSD1306::getMinX() {
  return _minX;
}

void HL_SSD1306::Update()
{
  unsigned long currentMillis = millis();
  int8_t f;

  if (currentMillis - previousMillis >= this->getInterval()) {
    // save the last time update
    previousMillis = currentMillis;

    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for (f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    // Then update coordinates of each flake...
    for (f = 0; f < NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}

void HL_SSD1306::scrollMsg(void)
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= this->getInterval() / 5)
  {
    // save the last time update
    previousMillis = currentMillis;

    setMinX (strlen (message[this->getState()]));

    display.clearDisplay();
    display.setCursor(0, 6);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print(msg_title);
    display.setTextSize (2);
    display.setCursor(getPosX(), 16);
    display.print(message[this->getState()]);
    display.display();
    updatePosX();
  }
}

void HL_SSD1306::startScrollLeftMsg(void)
{
  //  Serial.println(getMsgIndex());
  //  Serial.println(message[getMsgIndex()]);
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  //display.setTextWrap(false);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 16);
  ////  display.print(message[getMsgIndex()]);
  display.print(message[this->getState()]);
  display.display();      // Show initial text
  //delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollleft(0x00, 0x0F);
}

void HL_SSD1306::testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void HL_SSD1306::testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

void HL_SSD1306::testanimate() {
  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
}
void HL_SSD1306::testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];
  int8_t i;

  // Initialize 'snowflake' positions
  for (f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    /*    Serial.print(F("x: "));
        Serial.print(icons[f][XPOS], DEC);
        Serial.print(F(" y: "));
        Serial.print(icons[f][YPOS], DEC);
        Serial.print(F(" dy: "));
        Serial.println(icons[f][DELTAY], DEC);
    */
  }

  for (i = 0; i < 25; i++)  { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for (f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(100);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for (f = 0; f < NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
  //  display.clearDisplay();
  //  display.display();
}
