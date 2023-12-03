# status-led-door-sign
A WS2812B LED-Stripe based door sign to show your office status.

In my office I have a glass pane with a frame next to the door. An LED strip panel is clamped under the frame to display the status outside (through the glass pane). 

This project is based on a Wemos/Lolin D1 mini with a WS2812B LED-Strip, a touch LED-Button (to change status) and a 0.96 OLED-Display, to show the status inside my office. 

- 20231203: added support for esp32c3 supermini.

I've added some STL-files für 3D printing. Beside the base carrier plate (made for my glass pane) you probably can reuse the housing.

Pictures will follow soon...

# prerequisites
In the arduino-ide go to File - Preferences ... - Settings. Use the following additional boards manager URLs:
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
You need at least the following libraries (Tool - Manage Libraries... -, to compile the code:
```
https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/Adafruit_NeoPixel
```
search for them in the arduino-ide and add the libraries (there are plenty of how-to in the www, so this is skipped here...). 

# adjustments
There is one file, where the status an your name is configured. See [hl_state3034.h](./doorsign/hl_state3034.h).

I already added OTA (over the air) update to the code (see [doorsign.ino](./doorsign/doorsign.ino) line 36). But this will not work for your first upload or if your are not in the WiFi. The routine loops forever to get into the WiFi, so this cut be a deadlock. To inhibt this, there is a define in the doorsign.ino.
```
//#define USE_OTA
```
If not commented, OTA will be available. If you don't need/want OTA, just comment out the define.
