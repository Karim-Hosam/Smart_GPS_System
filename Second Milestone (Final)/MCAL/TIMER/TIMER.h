#ifndef TIMER_H
#define TIMER_H

#include "../../../Services - Utilities/TM4C123.h"
#include <stdint.h>
#include "../../HAL/LCD/LCD.h"
// #include "../SYSTICK/SYSTICK.h"

extern volatile unsigned int seconds;
extern volatile unsigned int minutes;
extern volatile unsigned char timer_running;

void Timer0A_Init(void);
void Timer_Start(void);
void Timer_Pause(void);
void Timer_Reset(void);

#endif
