//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Name: Nour Ahmed Khalaf Ahmed || ID: 22000715 || Department: ECE 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LED_BUZZER.h"

bool IsNear = false;

void Alert_If_Close(int distance)
{
    if (distance <= ALERT_DISTANCE)
    {
        if (!IsNear)
        {
            IsNear = true;
            GPIO_PORTA_DATA_R |= (LED_PIN | BUZZER_PIN); // Turn ON
        }
    }
    else
    {
        if (IsNear)
        {
            IsNear = false;
            GPIO_PORTA_DATA_R &= ~(LED_PIN | BUZZER_PIN); // Turn OFF
        }
    }
}