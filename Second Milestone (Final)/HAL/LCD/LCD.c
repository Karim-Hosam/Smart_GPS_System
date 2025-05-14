//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Name: Sherif Ahmed Abdelfattah || ID: 2200176 || Department: ECE 
//
//  Name: Mariam Tarek Samir || ID: 2200167 || Department: ECE
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LCD.h"

// Rs = PD0
// Rw = PD1
// En = PD2
// D0 = PA7, D1 = PA6, D2 = PA5, D3 = PB4
// D4 = PE5, D5 = PE4, D6 = PE1, D7 = PD3

static void LCD_WritePins(uint8_t data);

void LCD_Init(void)
{
    GPIO_InitPort('A');
    GPIO_InitPort('B');
    GPIO_InitPort('D');
    GPIO_InitPort('E');

    // Configure Data Pins
    GPIO_SetPinDirection('A', 5, 'O');
    GPIO_SetPinDirection('A', 6, 'O');
    GPIO_SetPinDirection('A', 7, 'O');

    GPIO_SetPinDirection('B', 4, 'O');

    GPIO_SetPinDirection('E', 1, 'O'); // Include PE1 (D6)
    GPIO_SetPinDirection('E', 4, 'O');
    GPIO_SetPinDirection('E', 5, 'O');

    // Control Pins PD0, PD1, PD2, and PD3 (D7)
    GPIO_SetPinDirection('D', 0, 'O');
    GPIO_SetPinDirection('D', 1, 'O');
    GPIO_SetPinDirection('D', 2, 'O');
    GPIO_SetPinDirection('D', 3, 'O');

    wait_ms(50);       // Wait for LCD to power up
    LCD_Command(0x38); // 8-bit, 2-line, 5x7 font
    LCD_Command(0x0C); // Display ON, Cursor OFF
    LCD_Command(0x06); // Entry Mode Set
    LCD_Command(0x01); // Clear Display
    wait_ms(2);        // Extra delay after clear
}

static void LCD_WritePins(uint8_t data)
{
    // D0 -> PA7
    GPIO_SetPinValue('A', 7, (data & (1U << 0)) ? 'S' : 'C');
    // D1 -> PA6
    GPIO_SetPinValue('A', 6, (data & (1U << 1)) ? 'S' : 'C');
    // D2 -> PA5
    GPIO_SetPinValue('A', 5, (data & (1U << 2)) ? 'S' : 'C');
    // D3 -> PB4
    GPIO_SetPinValue('B', 4, (data & (1U << 3)) ? 'S' : 'C');
    // D4 -> PE5
    GPIO_SetPinValue('E', 5, (data & (1U << 4)) ? 'S' : 'C');
    // D5 -> PE4
    GPIO_SetPinValue('E', 4, (data & (1U << 5)) ? 'S' : 'C');
    // D6 -> PE1
    GPIO_SetPinValue('E', 1, (data & (1U << 6)) ? 'S' : 'C');
    // D7 -> PD3
    GPIO_SetPinValue('D', 3, (data & (1U << 7)) ? 'S' : 'C');
}

void LCD_Command(uint8_t cmd)
{
    LCD_WritePins(cmd);
    GPIO_SetPinValue('D', 0, 'C'); // RS = 0
    GPIO_SetPinValue('D', 1, 'C'); // RW = 0
    GPIO_SetPinValue('D', 2, 'S'); // EN = 1
    wait_ms(1);
    GPIO_SetPinValue('D', 2, 'C'); // EN = 0
    wait_ms(2);
}

void LCD_Data(uint8_t data)
{
    LCD_WritePins(data);
    GPIO_SetPinValue('D', 0, 'S'); // RS = 1
    GPIO_SetPinValue('D', 1, 'C'); // RW = 0
    GPIO_SetPinValue('D', 2, 'S'); // EN = 1
    wait_ms(1);
    GPIO_SetPinValue('D', 2, 'C'); // EN = 0
    wait_ms(2);
}

void LCD_String(char *str)
{
    while (*str)
    {
        LCD_Data(*str++);
    }
}
