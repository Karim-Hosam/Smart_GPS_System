#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stdbool.h>         //  LCD
#include "TM4C123.h"

#define LED_PIN     0x04  // PA2 (bit 2)
#define BUZZER_PIN  0x08  // PA3 (bit 3)
#define ALERT_DISTANCE 15.0 // meters

extern bool IsNear;
void Alert_If_Close(int distance);


#endif // LED_H