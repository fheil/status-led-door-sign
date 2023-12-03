/**************************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x32 pixel display using I2C to communicate
  3 pins are required to interface (two I2C and one reset).

  Adafruit invests time and resources providing this open
  source code, please support Adafruit and open-source
  hardware by purchasing products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries,
  with contributions from the open source community.
  BSD license, check license.txt for more information
  All text above, and the splash screen below must be
  included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include "doorsign.h"
#include "hl_ssd1306.h"
#include "rainbow.h"

#if defined(ESP8266) || defined(ESP8266_WEMOS_D1MINIPRO)
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

int TouchSensor = D5; //OUT-Pin an D3
#endif // #if defined(ESP8266) || defined(ESP8266_WEMOS_D1MINIPRO) 

#if defined(ESP32) || defined(ESP32C3_DEV)
#include "WiFi.h"

int TouchSensor = 3; //OUT-Pin an D3
#endif // #if defined(ESP32) || defined(ESP32C3_DEV) 

#ifdef USE_OTA
#include <ArduinoOTA.h>
#endif // #ifdef USE_OTA

//#define USE_BUILD_IN_SCROLLTEXT

//uint8_t c = 6;
int state = LOW;
int laststate = LOW;

// constants won't change:
const long interval_wled =  50;  // interval at which to blink (milliseconds)
const long interval_oled = 100;  // interval at which to scroll (milliseconds)

#ifdef USE_OTA
const char* ssid = STASSID;
const char* password = STAPSK;
#endif // #ifdef USE_OTA

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest

Rainbow rbStrip(interval_wled);
HL_SSD1306 oled_display(interval_oled);

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
#ifdef USE_OTA
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    //ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif //USE_OTA

  pinMode(LED_BUILTIN, OUTPUT); // Deklarieren der Pins
  pinMode(TouchSensor, INPUT);

  oled_display.Init();
  rbStrip.setState(oled_display.getState());

  rbStrip.SetPixelColor();

  laststate = state = digitalRead(TouchSensor);
}

void loop() {
#ifdef USE_OTA
  ArduinoOTA.handle();
#endif //USE_OTA

  state = digitalRead(TouchSensor);

  if (laststate != state)
  {
    oled_display.cycleState();
    rbStrip.setState(5 - oled_display.getState());

    rbStrip.SetPixelColor();
#ifdef USE_BUILD_IN_SCROLLTEXT
    oled_display.startScrollLeftMsg();
#else
    oled_display.resetPosX();
#endif // #ifdef USE_BUILD_IN_SCROLLTEXT    

    laststate = state;
  }

  if (oled_display.getState() == oled_display.getRainbowState()) {
    oled_display.Update(); // Animate bitmaps
    rbStrip.Update();

  }

#ifndef USE_BUILD_IN_SCROLLTEXT
  else {
    oled_display.scrollMsg();
  }
#endif // #ifndef USE_BUILD_IN_SCROLLTEXT
}
