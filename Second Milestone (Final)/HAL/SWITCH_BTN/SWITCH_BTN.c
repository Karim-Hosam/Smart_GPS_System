#include "SWITCH_BTN.h"

volatile int state = 0;

void switch_state(void)
{
    state++;
    if (state > 2)
    {
        state = 0;
    }
    
}

void select_state(char selected_state)
{
    state= selected_state;
}



