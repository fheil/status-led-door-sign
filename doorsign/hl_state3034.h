/*
  hl_state3034.h

  Written by F. Heil, March 15th, 2023
*/
#ifndef HL_STATE3034_h
#define HL_STATE3034_h

#include "Arduino.h"

class HL_State_3034
{
  public:
    void setState(uint8_t);
    uint8_t getState();
    void cycleState();

    void setInterval(long interval);
    long getInterval();

    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
      return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
    }
    char msg_title[32] = {" room 1.234 - J. Doe"};   // GERMAN with Umlaut-example
    char message[6][24] = {"admission free",         // "Eintritt frei"
                           "do not disturb",         // "Bitte nicht st\224ren"
                           "phone/video conference", // "Tel./Videokonferenz",
                           "on the way",             // "Unterwegs"
                           "home office",            // "HomeOffice"
                           "out of office"           // "Nicht im Dienst"

                           uint32_t msg_color[6] = {Color(0, 255, 0),
                                                    Color(255, 0, 0),
                                                    Color(255, 64, 0),
                                                    Color(0, 0, 255),
                                                    Color(0, 255, 255),
                                                    Color(255, 0, 255),
                                                   };
                           private:
                           uint8_t _state;
                           long _interval;  // interval at which to scroll (milliseconds)
                          };

#endif //#ifndef HL_STATE3034_h
