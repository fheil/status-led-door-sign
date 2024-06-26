# status-led-door-sign

A WS2812B LED stripe based door sign to show your office status.

In my office I have a glass pane with a frame next to the door. An LED strip panel is clamped under the frame to display the status outside (through the glass pane). 

This project is based on a Wemos/Lolin D1 mini with a WS2812B LED-Strip, a touch LED-Button (to change status) and a 0.96 OLED-Display, to show the status inside my office. 

- 20231203: added support for esp32c3 supermini.

I've added some STL-files für 3D printing. Beside the base carrier plate (made for my glass pane) you probably can reuse the housing.

![image](https://github.com/fheil/status-led-door-sign/assets/5410264/5d101d8a-6d45-43f9-a4ec-51eeb84ef93c)

on the left: view from inside with control unit, on the right: visitors view

![image](https://github.com/fheil/status-led-door-sign/assets/5410264/137c1508-5a4b-41eb-8841-d309b6f06d29)

cycling rainbow, just for fun and for checking the LEDs

## wiring
![image](https://github.com/fheil/status-led-door-sign/assets/5410264/aa7d8198-a6e0-4e58-bf38-db58aa44233e)

## prerequisites
In the arduino-ide go to File - Preferences ... - Settings. Use the following additional boards manager URLs:
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
You need at least the following libraries (Tool - Manage Libraries... ) to compile the code:
```
https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/Adafruit_NeoPixel
```
search for them in the arduino-ide and add the libraries (there are plenty of tutorials in the www, so this is skipped here...). 

## adjustments
There is one file, where the status and your name is configured. See [hl_state3034.h](./doorsign/hl_state3034.h).

I already added OTA (over the air) update to the code https://github.com/fheil/status-led-door-sign/blob/dde38e1420725f109ad70f99372021c18aa49832/doorsign/doorsign.ino#L41

But this will not work for your first upload or if your are not in the WiFi. The routine loops forever to get into the WiFi, so this could be a deadlock. To inhibt this, there is a define to enable or disable OTA: https://github.com/fheil/status-led-door-sign/blob/72b7999178189b431ecba22cc7655f0e8b36273f/doorsign/doorsign.h#L3

If not commented, OTA will be available. If you don't need/want OTA, just comment out the define.
