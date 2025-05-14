#ifndef SWITCH_BTN_H
#define SWITCH_BTN_H

#include <stdint.h>
#include <stdbool.h>         //  LCD
#include "TM4C123.h"


extern volatile int state;

void switch_state(void);
void select_state(char selected_state);

#endif // SWITCH_BTN_H