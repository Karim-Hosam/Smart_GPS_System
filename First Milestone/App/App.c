//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Name: Mariam Tarek Samir || ID: 2200167 || Department: ECE
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "app.h"

int main(void)
{
    // Init UART0 and Port F using your GPIO function
    UART0_Init();
    GPIO_InitPort('F');

    // Configure PF0 and PF4 as inputs (SW2 and SW1)
    GPIO_SetPinDirection('F', 0, 'I');
    GPIO_SetPinDirection('F', 4, 'I');
    GPIO_PORTF_PUR_R |= (SW1 | SW2); // Enable pull-ups for switches

    // Configure PF1, PF2, PF3 as outputs (RGB LEDs)
    GPIO_SetPinDirection('F', 1, 'O');
    GPIO_SetPinDirection('F', 2, 'O');
    GPIO_SetPinDirection('F', 3, 'O');

    while (1)
    {
        uint8_t buttons = GPIO_PORTF_DATA_R & (SW1 | SW2);

        if (!(buttons & SW1))
        { // SW1 Pressed
            GPIO_SetPortValue('F', RED_LED);
            UART0_StringTX("Red LED ON for 3 seconds\r\n");
            wait_ms(3000);
            GPIO_SetPortValue('F', 0);
        }

        if (!(buttons & SW2))
        { // SW2 Pressed
            for (int i = 0; i < 5; i++)
            {
                GPIO_SetPortValue('F', GREEN_LED);
                UART0_StringTX("Green LED ON\r\n");
                wait_ms(500);
                GPIO_SetPortValue('F', BLUE_LED);
                UART0_StringTX("Blue LED ON\r\n");
                wait_ms(500);
            }
            GPIO_SetPortValue('F', 0);
        }
    }
}
