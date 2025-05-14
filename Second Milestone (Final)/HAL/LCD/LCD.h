#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "../../MCAL/Systick/Systick.h"
#include "TM4C123.h"

// Function prototypes
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_String(char *str);

#endif
